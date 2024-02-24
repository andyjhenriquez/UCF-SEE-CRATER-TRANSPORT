#ifndef CRATERTRANSPORT_PHYSICS_H
#define CRATERTRANSPORT_PHYSICS_H

#include <PhysX/PxConfig.h>
#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

namespace Physics {
    class CraterTransport_Physics {
    public:
        void initPhysics();
        void simulateStep();
        void cleanupPhysics();

        static PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
    private:
        PxDefaultAllocator       gAllocator;
        PxDefaultErrorCallback   gErrorCallback;
        PxFoundation*            gFoundation = nullptr;
        PxPhysics*               gPhysics = nullptr;
        PxDefaultCpuDispatcher*  gDispatcher = nullptr;
        PxScene*                 gScene = nullptr;
        PxMaterial*              gMaterial = nullptr;
    };
}
#endif