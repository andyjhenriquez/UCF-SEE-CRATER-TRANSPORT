#include "PhysicsManager.h"
#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>

#include <iostream>
using namespace std;

using namespace LunarSimulation;

namespace Physics {
    PhysicsManager::PhysicsManager() {

    }

    PhysicsManager::PhysicsManager(HlaWorldPtr hlaPtr) {
        this->hlaWorld = hlaPtr;
    }

    PhysicsManager::~PhysicsManager() {
        delete this;
    }


    bool PhysicsManager::initPhysics() {
        gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

        if (!gFoundation) {
            printf("Error: could not create PxFoundation!\n");
            return false;
        }

        // Initializing cuda
        PxCudaContextManagerDesc cudaContextManagerDesc;
        gCudaContextManager = PxCreateCudaContextManager(*gFoundation, cudaContextManagerDesc, PxGetProfilerCallback());
        if (gCudaContextManager && !gCudaContextManager->contextIsValid()) {
            gCudaContextManager->release();
            gCudaContextManager = NULL;
            printf("Failed to initialize cuda context.\n");
        }

        // OmniPvd only works in debug mode
        #if _DEBUG
        gOmniPvd = OmniPvd::initOmniPvd(*gFoundation);
        #endif

        gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, 0, gOmniPvd);

        // OmniPvd only works in debug mode
        #if _DEBUG
        if (gPhysics->getOmniPvd()) {
            gPhysics->getOmniPvd()->startSampling();
        }
        else {
            printf("Error: could not start OmniPvd sampling!\n");
            return false;
        }
        #endif

        // Base parameters for the PhysX scene
        PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0.0f, -1.62f, 0.0f);
        gDispatcher = PxDefaultCpuDispatcherCreate(2);
        sceneDesc.cpuDispatcher = gDispatcher;
        sceneDesc.filterShader = PxDefaultSimulationFilterShader;

        if (!sceneDesc.cudaContextManager) {
            sceneDesc.cudaContextManager = gCudaContextManager;
        }

        sceneDesc.flags |= PxSceneFlag::eENABLE_GPU_DYNAMICS;
        sceneDesc.flags |= PxSceneFlag::eENABLE_PCM;

        sceneDesc.broadPhaseType = PxBroadPhaseType::eGPU;
        sceneDesc.gpuMaxNumPartitions = 8;

        sceneDesc.solverType = PxSolverType::eTGS;

        gScene = gPhysics->createScene(sceneDesc);
        gMaterial = gPhysics->createMaterial(0.1f, 0.1f, 0.1f);
        
        return true;
    }

    void PhysicsManager::loadSampleScene() {
        PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
        gScene->addActor(*groundPlane);

        // Create the dynamic cube used in our samples
        createDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
    }

    void PhysicsManager::loadSampleEntryScene() {
        // Loads the moon environment model
        ModelLoader* moonLoader = new ModelLoader();

        PxTriangleMesh* moonMesh = moonLoader->loadMesh(gPhysics, "../../../Models/Crater.obj");
        
        // Cooked triangle mesh neds to be stored in a separate handler
        // that has more robust functionality
        PxTriangleMeshGeometry moonMeshHandler(moonMesh);

        // Temporary material property for the crater environment (NEEDS UPDATE)
        PxMaterial* moonMaterial = gPhysics->createMaterial(0.1f, 0.1f, 0.1f);

        // Creating the rigid actor which will hold the moon crater mesh
        PxRigidStatic* groundActor = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
        PxRigidActorExt::createExclusiveShape(*groundActor, moonMeshHandler, *moonMaterial, PxShapeFlag::eSIMULATION_SHAPE);

        groundActor->setGlobalPose(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
        gScene->addActor(*groundActor);
        
        ModelLoader* launcherLoader = new ModelLoader();
        PxTriangleMesh* launcherMesh = launcherLoader->loadMesh(gPhysics, "../../../Models/SledCrateExport.obj", true);

        // -------------------------------------------------------------------------------------------------------------
        // Loading and setting up the sled model
        PxTriangleMeshGeometry launcherMeshHandler;
        launcherMeshHandler.triangleMesh = launcherMesh;
        launcherMeshHandler.scale = PxVec3(1.0f);

        PxRigidDynamic* launcherActor = gPhysics->createRigidDynamic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));

        // Damping values
        launcherActor->setLinearDamping(0.2f);
        launcherActor->setAngularDamping(0.1f);

        // Setting collision related flags
        launcherActor->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_GYROSCOPIC_FORCES, true);
        launcherActor->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, true);

        // Temporary material property for the sled (NEEDS UPDATE)
        PxMaterial* launcherMaterial = gPhysics->createMaterial(0.1f, 0.1f, 0.1f);

        PxShape* launcherShape = PxRigidActorExt::createExclusiveShape(*launcherActor, launcherMeshHandler, *launcherMaterial);

        // Offset from created SDF for collision resolution
        launcherShape->setContactOffset(0.1f);
        launcherShape->setRestOffset(0.02f);

        // Setting mass and density values, mass not currently being set (default 1)
        PxReal density = 100.0f;
        PxRigidBodyExt::updateMassAndInertia(*launcherActor, density);

        gScene->addActor(*launcherActor);

        // Custom settings
        launcherActor->setSolverIterationCounts(50, 1);
        launcherActor->setMaxDepenetrationVelocity(5.0f);
        launcherActor->setGlobalPose(PxTransform(PxVec3(246.12082f, 1300.63616f, 216.73205f), PxQuat(PxPi, PxVec3(0.0f, 1.0f, 0.0f))));
    }

    // Moves the simulation by the specified time-step
    void PhysicsManager::simulateStep(double timeStep) {
        gScene->simulate(timeStep);
        gScene->fetchResults(true);
    }

    void PhysicsManager::cleanupPhysics() {
        PX_RELEASE(gScene);
        PX_RELEASE(gDispatcher);
        PX_RELEASE(gPhysics);
        PX_RELEASE(gFoundation);
        PX_RELEASE(gOmniPvd);
        PX_RELEASE(gCudaContextManager);

        printf("Simulation Complete\n");
    }

    // Creates a PhysX dynamic actor (can move within the scene and responds accordingly to forces)
    PxRigidDynamic* PhysicsManager::createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity) {
        PxRigidDynamic* dynamic = PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
        dynamic->setAngularDamping(0.5f);
        dynamic->setLinearVelocity(velocity);
        gScene->addActor(*dynamic);
        return dynamic;
    }


    // Getters
    const PxDefaultAllocator PhysicsManager::getAllocator() {
        return gAllocator;
    }

    const PxDefaultErrorCallback PhysicsManager::getErrorCallback() {
        return gErrorCallback;
    }

    const PxFoundation* PhysicsManager::getFoundation() {
        return gFoundation;
    }

    const PxPhysics* PhysicsManager::getPhysics() {
        return gPhysics;
    }

    const PxDefaultCpuDispatcher* PhysicsManager::getCpuDispatcher() {
        return gDispatcher;
    }

    const PxScene* PhysicsManager::getScene() {
        return gScene;
    }

    const PxMaterial* PhysicsManager::getMaterial() {
        return gMaterial;
    }

    const PxOmniPvd* PhysicsManager::getOmniPvd() {
        return gOmniPvd;
    }

    const char* PhysicsManager::getOmniPvdPath() {
        return gOmniPvdPath;
    }

    const PxCudaContextManager* PhysicsManager::getCudaContextManager() {
        return gCudaContextManager;
    }
}
