#ifndef CRATERTRANSPORT_PHYSICS_H
#define CRATERTRANSPORT_PHYSICS_H

#include <PhysX/PxConfig.h>
#include <PhysX/PxPhysicsAPI.h>

#include "OmniPvd.h"

using namespace physx;

// Holds most of the PhysX simulation information
namespace Physics {
    class PhysicsManager {
    public:
        // Default constructor
        PhysicsManager();

        // Default destructor
        ~PhysicsManager();

        // Initlializes physics variables
        bool initPhysics();

        // Moves simulation forward a specified time-step default 60fps
        void simulateStep(double timeStep = 1.0f / 60.0f);

        // Cleans up physics variables
        void cleanupPhysics();

        // Loads a sample scene for debugging
        void loadSampleScene();

        // Sample entry scene using basic shapes
        void loadSampleEntryScene();

        // Sample exit scene using basic shapes
        void loadSampleExitScene();

        // Getters
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