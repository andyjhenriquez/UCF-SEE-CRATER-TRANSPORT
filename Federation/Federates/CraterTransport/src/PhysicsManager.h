#ifndef CRATERTRANSPORT_PHYSICS_H
#define CRATERTRANSPORT_PHYSICS_H

#include <PhysX/PxConfig.h>
#include <PhysX/PxPhysicsAPI.h>
#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>

#include "OmniPvd.h"
#include "ModelLoader.h"

using namespace physx;
using namespace LunarSimulation;

// Holds most of the PhysX simulation information
namespace Physics {
    class PhysicsManager {
    public:
        // Default constructor
        PhysicsManager();

        PhysicsManager(HlaWorldPtr hlaPtr);

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
        const PxCudaContextManager* getCudaContextManager();

        PxRigidDynamic* createDynamic(const PxTransform& t, const PxGeometry& geometry, const PxVec3& velocity = PxVec3(0));
    private:
        PxDefaultAllocator       gAllocator;
        PxDefaultErrorCallback   gErrorCallback;
        PxFoundation*            gFoundation = nullptr;
        PxPhysics*               gPhysics = nullptr;
        PxDefaultCpuDispatcher*  gDispatcher = nullptr;
        PxScene*                 gScene = nullptr;
        PxMaterial*              gMaterial = nullptr;
        PxOmniPvd*               gOmniPvd = nullptr;
        PxCudaContextManager*    gCudaContextManager = nullptr;
        const char*              gOmniPvdPath = nullptr;
        HlaWorldPtr              hlaWorld;
    };
}
#endif