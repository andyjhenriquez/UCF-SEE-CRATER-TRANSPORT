#include "sim_utils.h"

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
std::vector<double> sim_utils::vec3ToDouble3(PxVec3 vec) {
	std::vector<double> conv(3);

	conv[0] = static_cast<double>(vec.x);
	conv[1] = static_cast<double>(vec.y);
	conv[2] = static_cast<double>(vec.z);

	return conv;
}

/*
* Converts PxMat33 to double[9]
*/
std::vector<double> sim_utils::mat33ToDouble9(PxMat33 mat) {
	std::vector<double> conv{ 0, 0, 0, 0, 0, 0, 0, 0 ,0 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			conv[(i * 3) + j] = mat[i][j];
		}
	}

	return conv;
}

// Calculates acceleration 
std::vector<double> sim_utils::accelerationCalc(double curVel[3], double oldVel[3]) {
	// Do not currently have the time step val, so I'm substituting 1
	std::vector<double> acc(3);

	for (int i = 0; i < 3; i++) {
		acc[i] = (curVel - oldVel) / 1;
	}

	return acc;
}

// Calculates force
std::vector<double> sim_utils::forceCalc(double mass, double acc[3]) {
	std::vector<double> force(3);

	for (int i = 0; i < 3; i++) {
		force[i] = mass * acc[i];
	}

	return force;
}

// Calculates
double sim_utils::realToDouble(PxReal real) {
	return static_cast<double>(real);
}