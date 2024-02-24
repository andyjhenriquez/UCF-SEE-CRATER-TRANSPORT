#ifndef CRATERTRANSPORT_PHYSICS_H
#define CRATERTRANSPORT_PHYSICS_H

#include <PhysX/PxConfig.h>
#include <PhysX/PxPhysicsAPI.h>

using namespace physx;

namespace Physics {
    class CraterTransport_Physics {
    public:
        CraterTransport_Physics();
        ~CraterTransport_Physics();
        void initPhysics();
        void simulateStep();
        void cleanupPhysics();

        static PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
    private:
        static PxDefaultAllocator       gAllocator;
        static PxDefaultErrorCallback   gErrorCallback;
        static PxFoundation*            gFoundation;
        static PxPhysics*               gPhysics;
        static PxDefaultCpuDispatcher*  gDispatcher;
        static PxScene*                 gScene;
        static PxMaterial*              gMaterial;
    };
}
#endif