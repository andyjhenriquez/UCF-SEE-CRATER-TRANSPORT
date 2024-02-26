#pragma once

#ifndef SIM_UTILS_H
#define SIM_UTILS_H

#include <PxPhysicsAPI.h>

#include <vector>
#include <iostream>

using namespace physx;

class sim_utils {
public:
    std::vector<double> vec3ToDouble3(PxVec3 vec);
    std::vector<double> mat33ToDouble9(PxMat33 vec);
    std::vector<double> accelerationCalc(double curVel[3], double oldVel[3]);
    std::vector<double> forceCalc(double mass, double acc[3]);
    double realToDouble(PxReal real);
};
#endif