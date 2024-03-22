#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>
#include <LunarSimulation\HlaPayloadManager.h>

#include "PhysicsManager.h"
#include "sim_utils.h"

#include <iostream>

using namespace LunarSimulation;

int main(void) {
    // Creates federation if this is the first federate connected,
    // connects to existing federation otherwise
    HlaWorldPtr hlaWorld = HlaWorld::Factory::create();
    Physics::PhysicsManager* physicsManager = new Physics::PhysicsManager();

    if (!physicsManager->initPhysics()) {
        return -1;
    }

    physicsManager->loadSampleEntryScene();

    try {
        hlaWorld->connect();
    }
    catch (std::exception& e) {
        // TODO Auto-generated catch block
        std::cout << e.what() << std::endl;
    }
    std::cout << "Connected\n";
   
    // Manages Payload instances, allows you to handle and find different instances
    HlaPayloadManagerPtr payloadManager = hlaWorld->getHlaPayloadManager();

    // Single Payload instance, extends Dynamical Entity and has a number
    // of functions to retrive its values such as acceleration and position
    HlaPayloadPtr payload = payloadManager->createLocalHlaPayload(L"Payload");

    // PhysX physics instantce
    const PxScene* gScene = physicsManager->getScene();

    // TODO: Find a stopping point for our federate
    while (true) {
        try {
            // Manages variable/state changes and communicates them to the federation.
            // New instance must be created on every loop.
            HlaPayloadUpdaterPtr updater = payload->getHlaPayloadUpdater();

            PxU32 numActors = gScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
            PxActor* gActors[10];

            gScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, gActors, PxU32(10));

            // Iterating through the actors in the scene and moving the information to the updater
            // TODO: Use a fetchResults() check to make sure that you can safely extract information.
            for (int i = 0; i < numActors; ++i) {
                PxActor* actor = gActors[i];
                if (actor->is<PxRigidDynamic>() != NULL)
                    updater->setPosition(sim_utils::vec3ToDouble3(actor->is<PxRigidDynamic>()->getGlobalPose().p));
                // actor->is<PxRigidDynamic>() ? updateDynamic() : updateStatic();
            }

            // Example of how to update a variable (in this case of a Payload instance)
            // Ideally we'll call something like Physics.calculateAcceleration() or an
            // equivalent function.
            updater->setAcceleration({100.0, 100.0, 100.0});

            // Packages all state/variable changes and sends them out to the federation
            // where other federates can pull the new values in and use them as needed.
            updater->sendUpdate();

            physicsManager->simulateStep();
        }
        catch (std::exception& e) {
            // TODO Auto-generated catch block
            std::cout << e.what() << std::endl;
        }

        hlaWorld->advanceToNextFrame();
    }

    physicsManager->cleanupPhysics();

    // Here we will do all of the federate cleanup necessary after it has finished running.
    // Unfortunately we can't run this code right now because we don't have a valid stopping
    // condition for our main loop.
    hlaWorld->disconnect();
}