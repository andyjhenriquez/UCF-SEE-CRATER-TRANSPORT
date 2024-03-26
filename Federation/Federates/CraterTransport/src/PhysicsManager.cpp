#include "PhysicsManager.h"

#include <iostream>

namespace Physics {
    PhysicsManager::PhysicsManager() {

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
        
        return true;
    }

    void PhysicsManager::loadSampleScene() {
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

        gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

        PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
        gScene->addActor(*groundPlane);

        // Create the dynamic cube used in our samples
        createDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
    }

    void PhysicsManager::loadSampleEntryScene() {
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

        gScene = gPhysics->createScene(sceneDesc);
        gMaterial = gPhysics->createMaterial(0.1f, 0.1f, 0.1f);

        // Loads triangle mesh
        ModelLoader* moonLoader = new ModelLoader();

        PxTriangleMesh* moonMesh = moonLoader->loadMesh(gPhysics, "../../../Models/shackleton_highres_triangulated_scaled.obj");

        if (moonMesh == NULL) {
            return;
        }
        
        // Cooked triangle mesh neds to be stored in a separate handler
        // that has more robust functionality
        PxTriangleMeshGeometry moonMeshHandler(moonMesh);

        // Creating the rigid actor which will hold the moon crater mesh
        PxRigidStatic* groundActor = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
        PxRigidActorExt::createExclusiveShape(*groundActor, moonMeshHandler, *gMaterial, PxShapeFlag::eSIMULATION_SHAPE);

        groundActor->setGlobalPose(PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxDegToRad(-0.0f), PxVec3(0.0f, 0.0f, 1.0f))));
        gScene->addActor(*groundActor);
        
        ModelLoader* launcherLoader = new ModelLoader();
        PxTriangleMesh* launcherMesh = launcherLoader->loadMesh(gPhysics, "../../../Models/SledCrateExport.obj", true);
        
        if (launcherMesh == NULL) {
            return;
        }

        PxTriangleMeshGeometry launcherMeshHandler;
        launcherMeshHandler.triangleMesh = launcherMesh;
        launcherMeshHandler.scale = PxVec3(1.0f);

        PxRigidDynamic* launcherActor = gPhysics->createRigidDynamic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
        launcherActor->setLinearDamping(0.2f);
        launcherActor->setAngularDamping(0.1f);
        launcherActor->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_GYROSCOPIC_FORCES, true);
        launcherActor->setRigidBodyFlag(PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD, true);
        PxShape* launcherShape = PxRigidActorExt::createExclusiveShape(*launcherActor, launcherMeshHandler, *gMaterial);
        launcherShape->setContactOffset(0.1f);
        launcherShape->setRestOffset(0.02f);

        PxReal density = 100.0f;
        PxRigidBodyExt::updateMassAndInertia(*launcherActor, density);

        gScene->addActor(*launcherActor);
        launcherActor->setSolverIterationCounts(50, 1);
        launcherActor->setMaxDepenetrationVelocity(5.0f);
        launcherActor->setGlobalPose(PxTransform(PxVec3(246.12082f, 1300.63616f, 216.73205f)));
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
}
