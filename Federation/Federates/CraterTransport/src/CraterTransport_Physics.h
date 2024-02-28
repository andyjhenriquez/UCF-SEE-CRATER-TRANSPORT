#ifndef CRATERTRANSPORT_PHYSICS_H
#define CRATERTRANSPORT_PHYSICS_H

#include <PhysX/PxConfig.h>
#include <PhysX/PxPhysicsAPI.h>

#include "OmniPvd.h"

using namespace physx;

namespace Physics {
    class PhysicsManager {
    public:
        PhysicsManager();
        ~PhysicsManager();
        bool initPhysics();
        void simulateStep();
        void cleanupPhysics();
        void loadSampleScene();

        // getters
        const PxDefaultAllocator getAllocator();
        const PxDefaultErrorCallback getErrorCallback();
        const PxFoundation* getFoundation();
        const PxPhysics* getPhysics();
        const PxDefaultCpuDispatcher* getCpuDispatcher();
        const PxScene* getScene();
        const PxMaterial* getMaterial();
        const PxOmniPvd* getOmniPvd();
        const char* getOmniPvdPath();

        PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
    private:
        PxDefaultAllocator       gAllocator;
        PxDefaultErrorCallback   gErrorCallback;
        PxRigidDynamic*          defaultActor = nullptr;
        PxFoundation*            gFoundation = nullptr;
        PxPhysics*               gPhysics = nullptr;
        PxDefaultCpuDispatcher*  gDispatcher = nullptr;
        PxScene*                 gScene = nullptr;
        PxMaterial*              gMaterial = nullptr;
        PxOmniPvd*               gOmniPvd = nullptr;
        const char*              gOmniPvdPath = nullptr;
    };
}
#endif