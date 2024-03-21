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

        gScene = gPhysics->createScene(sceneDesc);
        gMaterial = gPhysics->createMaterial(0.1f, 0.1f, 0.1f);

        // Loads triangle mesh
        ModelLoader* obj = new ModelLoader();
        PxTriangleMesh* moonMesh = obj->loadCraterMesh(gPhysics);

        if (moonMesh == NULL) {
            return;
        }
        
        // Cooked triangle mesh neds to be stored in a separate handler
        // that has more robust functionality
        PxTriangleMeshGeometry moonMeshHandler(moonMesh);

        // Creating the rigid actor which will hold the moon crater mesh
        PxRigidStatic* groundActor = gPhysics->createRigidStatic(PxTransform(PxVec3(0.0f, 0.0f, 0.0f)));
        PxRigidActorExt::createExclusiveShape(*groundActor, moonMeshHandler, *gMaterial, PxShapeFlag::eSIMULATION_SHAPE);

        gScene->addActor(*groundActor);
        groundActor->setGlobalPose(PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxDegToRad(-0.0f), PxVec3(0.0f, 0.0f, 1.0f))));

        // Create the dynamic cube used in our samples using a hard-coded starting position to ensure deterministic outcome
        createDynamic(PxTransform(PxVec3(246.12082f, 1300.63616f, 216.73205f)), PxBoxGeometry(PxVec3(1.0f, 1.0f, 1.0f)), PxVec3(0, 0, 0));
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
