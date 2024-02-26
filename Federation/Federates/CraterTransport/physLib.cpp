#include <PxPhysicsAPI.h>
#include <iostream>

using namespace physx;

/*
What function covers what payload class attribute 

vec3ToDoub3:
	Position 
	Velocity
	Center of Mass

vec3toDoub9:
	Inertia

accelerationCalc:
	Acceleration
	Rotational Acceleration

forceCalc:
	Force

realToDouble:
	Mass

No function yet:
	Torque
*/


// Converts PxVec3 invInertia to double[3]
public double[] vec3ToDoub3(PxVec3 vec) {
	double conv[3];

	conv[0] = static_cast<double>(vec.x);
	conv[1] = static_cast<double>(vec.y);
	conv[2] = static_cast<double>(vec.z);

	return conv;
}

/*
* Converts PxMat33 to double[9]
*/
public double[] mat33ToDoub9(PxMat33 mat) {
	double conv[9] = { 0, 0, 0, 0, 0, 0, 0, 0 ,0 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			conv[(i * 3) + j] = mat[i][j];
		}
	}

	return conv;
}

// Calculates acceleration 
public double[] accelerationCalc(double[3] curVel, double[3] oldVel) {
	// Do not currently have the time step val, so I'm substituting 1
	double acc[3];

	for (int i = 0; i < 3; i++) {
		acc[i] = (curVel - oldVel) / 1;
	}

	return acc;
}

// Calculates force
public double[] forceCalc(double mass, double[3] acc) {
	double force[3];

	for (int i = 0; i < 3; i++) {
		force[i] = mass * acc[i];
	}
}

// Calculates
public double realToDouble(PxReal real) {
	return static_cast<double>(real);
}