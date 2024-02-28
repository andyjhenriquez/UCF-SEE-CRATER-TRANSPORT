#include "CraterTransport_Physics.h"

#include <iostream>

namespace Physics {
    PxDefaultAllocator       CraterTransport_Physics::gAllocator;
    PxDefaultErrorCallback   CraterTransport_Physics::gErrorCallback;
    PxFoundation*            CraterTransport_Physics::gFoundation = nullptr;
    PxPhysics*               CraterTransport_Physics::gPhysics = nullptr;
    PxDefaultCpuDispatcher*  CraterTransport_Physics::gDispatcher = nullptr;
    PxScene*                 CraterTransport_Physics::gScene = nullptr;
    PxMaterial*              CraterTransport_Physics::gMaterial = nullptr;
    PxOmniPvd*               CraterTransport_Physics::gOmniPvd = nullptr;

    CraterTransport_Physics::CraterTransport_Physics() {

    }

    CraterTransport_Physics::~CraterTransport_Physics() {

    }

    bool CraterTransport_Physics::initPhysics() {
        gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);

        if (!gFoundation) {
            printf("Error: could not create PxFoundation!\n");
            return false;
        }

        #if _DEBUG
        gOmniPvd = OmniPvd::initOmniPvd(*gFoundation);
        #endif

        gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(), true, 0, gOmniPvd);

        #if _DEBUG
        if (gPhysics->getOmniPvd()) {
            gPhysics->getOmniPvd()->startSampling();
        }
        else {
            printf("Error: could not start OmniPvd sampling!\n");
            return false;
        }
        #endif

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

        return true;
    }

    void CraterTransport_Physics::simulateStep() {
        gScene->simulate(1.0f / 60.0f);
        gScene->fetchResults(true);
        PxVec3 velocity = defaultActor->getLinearVelocity();
        std::cout << velocity.y << std::endl;
    }

    void CraterTransport_Physics::cleanupPhysics() {
        PX_RELEASE(gScene);
        PX_RELEASE(gDispatcher);
        PX_RELEASE(gPhysics);
        PX_RELEASE(gFoundation);

        printf("Simulation Complete\n");
    }

    PxRigidDynamic* CraterTransport_Physics::createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity) {
        PxRigidDynamic* dynamic = PxCreateDynamic(*gPhysics, t, geometry, *gMaterial, 10.0f);
        dynamic->setAngularDamping(0.5f);
        dynamic->setLinearVelocity(velocity);
        gScene->addActor(*dynamic);
        return dynamic;
    }
}
