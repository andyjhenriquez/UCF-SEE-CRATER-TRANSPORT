#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>

#include <iostream>

using namespace LunarSimulation;

int main(void) {
    HlaWorldPtr world = HlaWorld::Factory::create();
    std::cout << world << std::endl;
    try {
        world->connect();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}