#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>

#include <iostream>

using namespace LunarSimulation;

int main(void) {
    HlaWorldPtr world = HlaWorld::Factory::create();
    try {
        world->connect();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    world->disconnect();
}