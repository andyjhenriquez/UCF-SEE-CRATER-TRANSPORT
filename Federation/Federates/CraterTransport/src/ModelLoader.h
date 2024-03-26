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
    PxTriangleMesh* loadMesh(PxPhysics *gPhysics, string filepath, bool createSDF = false);
    PxTriangleMesh* loadSampleCubeMesh(PxPhysics* gPhysics);

private:
    bool loadOBJ(string filepath);
    inline bool fileExists(const std::string& name);

    PxTriangleMeshDesc meshDesc;

    // List of points (3D vectors)
    PxArray<PxVec3> vecv;

    // list of faces (indices for vecv)
    PxArray<PxU32> vecf;
};
#endif
