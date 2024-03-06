#pragma once

#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <PhysX/PxPhysicsAPI.h>

#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace physx;
using namespace std;

class ModelLoader {
public:
    PxTriangleMesh* loadCraterMesh(PxPhysics *gPhysics);

private:
    bool loadOBJ();

    PxTriangleMeshDesc meshDesc;

    // List of points (3D vectors)
    vector<PxVec3> vecv;

    // List of normals (also 3D vectors)
    vector<PxVec3> vecn;

    // list of faces (indices for vecv and vecn)
    vector<vector<unsigned>> vecf;
};
#endif
