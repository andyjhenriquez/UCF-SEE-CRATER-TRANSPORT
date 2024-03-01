#include "PhysicsManager.h"

#include <iostream>

namespace Physics {
    PhysicsManager::PhysicsManager() {

    }

    PhysicsManager::~PhysicsManager() {

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

        defaultActor = createDynamic(PxTransform(PxVec3(0, 40, 100)), PxSphereGeometry(10), PxVec3(0, -50, -100));
    }

    void PhysicsManager::loadSampleEntryScene() {
        PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0.0f, -1.62f, 0.0f);
        gDispatcher = PxDefaultCpuDispatcherCreate(2);
        sceneDesc.cpuDispatcher = gDispatcher;
        sceneDesc.filterShader = PxDefaultSimulationFilterShader;
        gScene = gPhysics->createScene(sceneDesc);

        gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

        PxVec3 planeNormal = PxVec3(1.0f, 1.0f, 0.0f).getNormalized(); // PxPlane requires normalized vector
        PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(planeNormal, 0), *gMaterial);
        gScene->addActor(*groundPlane);

        defaultActor = createDynamic(PxTransform(PxVec3(0, 2, 2)), PxBoxGeometry(PxVec3(1.0f, 1.0f, 1.0f)), PxVec3(0, 0, 0));
    }

    void PhysicsManager::loadSampleExitScene() {
        PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
        sceneDesc.gravity = PxVec3(0.0f, -1.62f, 0.0f);
        gDispatcher = PxDefaultCpuDispatcherCreate(2);
        sceneDesc.cpuDispatcher = gDispatcher;
        sceneDesc.filterShader = PxDefaultSimulationFilterShader;
        gScene = gPhysics->createScene(sceneDesc);

        gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.5f);

        PxRigidStatic* groundPlane = PxCreatePlane(*gPhysics, PxPlane(0, 1, 0, 0), *gMaterial);
        gScene->addActor(*groundPlane);

        PxRigidStatic* landingZone = PxCreateStatic(*gPhysics, PxTransform(10000, 0, 0), PxBoxGeometry(1000, 10, 1000), *gMaterial);
        gScene->addActor(*landingZone);

        defaultActor = createDynamic(PxTransform(PxVec3(0, 20, 0)), PxSphereGeometry(10), PxVec3(100, 50, 0));
    }

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
