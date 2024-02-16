#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>

#include <iostream>

using namespace LunarSimulation;

int main(void) {
    HlaWorldPtr world = HlaWorld::Factory::create();
    world->connect();
}