#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>
#include <LunarSimulation\HlaPayloadManager.h>

#include "PhysX/PxPhysicsAPI.h"

#include <iostream>
#include <vector>

using namespace LunarSimulation;

int main(void) {
    // Creates federation if this is the first federate connected,
    // connects to existing federation otherwise
    HlaWorldPtr hlaWorld = HlaWorld::Factory::create();

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
    std::vector<HlaPayloadPtr> list = payloadManager->getAllHlaPayloads();

    // TODO: Find a stopping point for our federate
    while (true) {
        hlaWorld->advanceToNextFrame();
    }

    // Here we will do all of the federate cleanup necessary after it has finished running.
    // Unfortunately we can't run this code right now because we don't have a valid stopping
    // condition for our main loop.
    hlaWorld->disconnect();
}