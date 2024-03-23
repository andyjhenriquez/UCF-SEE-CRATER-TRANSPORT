#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>
#include <LunarSimulation\HlaPayloadManager.h>
#include <LunarSimulation\HlaMoonManager.h>

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
    HlaMoonManagerPtr moonManager = hlaWorld->getHlaMoonManager();

    // Instantiating an instance of our moon environment object
    HlaPayloadPtr payload = payloadManager->createLocalHlaPayload(L"Payload");
    HlaMoonPtr moon = moonManager->createLocalHlaMoon(L"Moon");

    // Single Payload instance, extends Dynamical Entity and has a number
    // of functions to retrive its values such as acceleration and position
    HlaPayloadUpdaterPtr payloadUpdater = payload->getHlaPayloadUpdater();

    // Set up the reference frames for both objects
    SpaceTimeCoordinateState moonState = SpaceTimeCoordinateState();
    moonState.translationalState.position = { 0.0, 0.0, 0.0 };
    std::vector<double> moonVelocity = { 0.0, 0.0, 0.0 };
    moonState.translationalState.velocity = moonVelocity;
    moonState.rotationalState.angularVelocity = { 0.0, 0.0, 0.0 };
    moonState.rotationalState.attitudeQuaternion = AttitudeQuaternion(0.0, { 0.0, 0.0, 0.0 });
    moonState.time = 0.0f;

    HlaMoonUpdaterPtr moonUpdater = moon->getHlaMoonUpdater();
    moonUpdater->setState(moonState);

    // Set the payloads parent reference frame as the moon entity
    payloadUpdater->setParentReferenceFrame(L"Moon");

    SpaceTimeCoordinateState payloadState = SpaceTimeCoordinateState();

    // TODO: Put these hard-coded variables into a variable because they're also
    // referenced in PhysicsManager.cpp
    payloadState.translationalState.position = { 246.12082f, 1300.63616f, 216.73205f };

    std::vector<double> payloadVelocity = { 0.0, 0.0, 0.0 };
    payloadState.translationalState.velocity = payloadVelocity;
    payloadState.rotationalState.angularVelocity = { 0.0, 0.0, 0.0 };
    payloadState.rotationalState.attitudeQuaternion = AttitudeQuaternion(0.0, { 0.0, 0.0, 0.0 });
    payloadUpdater->setState(payloadState);

    // PhysX physics instantce
    const PxScene* gScene = physicsManager->getScene();

    // TODO: Find a stopping point for our federate
    while (true) {
        try {
            // Manages variable/state changes and communicates them to the federation.
            // New instance must be created on every loop.
            payloadUpdater = payload->getHlaPayloadUpdater();

            PxU32 numActors = gScene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
            PxActor* gActors[10];

            gScene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, gActors, PxU32(10));

            // Iterating through the actors in the scene and moving the information to the updater
            // TODO: Use a fetchResults() check to make sure that you can safely extract information.
            for (int i = 0; i < numActors; ++i) {
                PxActor* actor = gActors[i];
                if (actor->is<PxRigidDynamic>() != NULL) {
                    payloadUpdater->setPosition(sim_utils::vec3ToDouble3(actor->is<PxRigidDynamic>()->getGlobalPose().p));
                    payloadUpdater->setVelocity(sim_utils::vec3ToDouble3(actor->is<PxRigidDynamic>()->getLinearVelocity()));
                }
                // actor->is<PxRigidDynamic>() ? updateDynamic() : updateStatic();
            }

            // Packages all state/variable changes and sends them out to the federation
            // where other federates can pull the new values in and use them as needed.
            payloadUpdater->sendUpdate();
        }
        catch (std::exception& e) {
            // TODO Auto-generated catch block
            std::cout << e.what() << std::endl;
        }

        // Advance both simulations by a set timestep
        // TODO: Line up timesteps for both simulations (IMPORTANT!)
        physicsManager->simulateStep();
        hlaWorld->advanceToNextFrame();
    }

    physicsManager->cleanupPhysics();

    // Here we will do all of the federate cleanup necessary after it has finished running.
    // Unfortunately we can't run this code right now because we don't have a valid stopping
    // condition for our main loop.
    hlaWorld->disconnect();
}