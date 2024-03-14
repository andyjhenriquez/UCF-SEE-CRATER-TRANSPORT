#include "ModelLoader.h"

PxTriangleMesh* ModelLoader::loadCraterMesh(PxPhysics* gPhysics) {
    bool status;

    // Attempt to open the specified crater mesh file
    if (fileExists("../../../Models/AmundsenRim_100mpp_triangulated.obj")) {
        status = loadOBJ();
    }
    else {
        cout << "Couldn't open crater model, loading sample cube mesh instead.\n\n";
        return loadSampleCubeMesh(gPhysics);
    }

    if (!status) {
        return NULL;
    }

    cout << "Loading .obj into PhysX...\n";

    meshDesc.points.count = vecv.size();
    meshDesc.points.data = reinterpret_cast<const PxVec3*>(&vecv[0][0]);
    meshDesc.points.stride = sizeof(PxVec3);

    // Error here: Seems to me that the count should be vecf.size()
    // but it runs into an index out of bounds error that I can't locate
    // the source of. vecv.size() works but with errors in the final look
    // of the mesh.
    meshDesc.triangles.count = vecf.size() / 3;
    meshDesc.triangles.data = vecf.begin();
    meshDesc.triangles.stride = 3 * sizeof(PxU32);
    
    
    PxTolerancesScale scale;
    PxCookingParams params(scale);

    params.midphaseDesc = PxMeshMidPhase::eBVH33;
    params.suppressTriangleMeshRemapTable = true;

    params.meshPreprocessParams &= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
    params.meshPreprocessParams &= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
    params.midphaseDesc.mBVH33Desc.meshSizePerformanceTradeOff = 0.55f;

    #if defined(PX_CHECKED) || defined(PX_DEBUG)
    PX_ASSERT(PxValidateTriangleMesh(params, meshDesc));
    #endif

    PxDefaultMemoryOutputStream writeBuffer;
    PxTriangleMeshCookingResult::Enum result;
    status = PxCookTriangleMesh(params, meshDesc, writeBuffer, &result);
    if (!status) {
        cout << "Failed to create triangle mesh.\n";
        return nullptr;
    }

    PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
    cout << "Finished loading .obj into PhysX.\n\n";
    return gPhysics->createTriangleMesh(readBuffer);
}

// Loading a sample cube I used to understand how PxMesh creation works
PxTriangleMesh* ModelLoader::loadSampleCubeMesh(PxPhysics* gPhysics) {
    cout << "Loading .obj into PhysX...\n\n";

    unsigned int indices[12][3] = {
        //Top
        {2, 6, 7 },
        {2, 3, 7 },

        //Bottom
        {0, 4, 5 },
        {0, 1, 5 },

        //Left
        {0, 2, 6 },
        {0, 4, 6 },

        //Right
        {1, 3, 7 },
        {1, 5, 7 },

        //Front
        {0, 2, 3 },
        {0, 1, 3 },

        //Back
        {4, 6, 7 },
        {4, 5, 7 }
    };

    PxArray<PxU32> PxIndices;
    for (int i = 0; i < 12; ++i) {
        PxIndices.pushBack(indices[i][0]);
        PxIndices.pushBack(indices[i][1]);
        PxIndices.pushBack(indices[i][2]);
    }

    float vertices[8][3] = {
        {-1, -1,  0.5}, //0
        {1, -1,  0.5 }, //1
        { -1,  1,  0.5}, //2
        {1,  1,  0.5 }, //3
        {-1, -1, -0.5 }, //4
        {1, -1, -0.5 }, //5
        {-1,  1, -0.5 }, //6
        {1,  1, -0.5 }  //7
    };

    PxArray<PxVec3> PxVertices;
    for (int i = 0; i < 8; ++i) {
        PxVec3 temp;
        temp.x = vertices[i][0];
        temp.y = vertices[i][1];
        temp.z = vertices[i][2];
        PxVertices.pushBack(temp);
    }

    meshDesc.points.count = 8;
    meshDesc.points.data = reinterpret_cast<const PxVec3*>(&PxVertices[0][0]);
    meshDesc.points.stride = sizeof(PxVec3);
    meshDesc.triangles.count = 12;
    meshDesc.triangles.data = PxIndices.begin();
    meshDesc.triangles.stride = 3 * sizeof(PxU32);

    PxTolerancesScale scale;
    PxCookingParams params(scale);

    params.midphaseDesc = PxMeshMidPhase::eBVH33;
    params.suppressTriangleMeshRemapTable = true;
    params.meshPreprocessParams &= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
    params.meshPreprocessParams &= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
    params.midphaseDesc.mBVH33Desc.meshSizePerformanceTradeOff = 0.55f;

    #if defined(PX_CHECKED) || defined(PX_DEBUG)
    PX_ASSERT(PxValidateTriangleMesh(params, meshDesc));
    #endif

    PxDefaultMemoryOutputStream writeBuffer;
    PxTriangleMeshCookingResult::Enum result;
    bool status = PxCookTriangleMesh(params, meshDesc, writeBuffer, &result);
    if (!status) {
        cout << "Failed to create triangle mesh.\n\n";
        return nullptr;
    }

    PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
    cout << "Finished loading .obj into PhysX.\n\n";
    return gPhysics->createTriangleMesh(readBuffer);
}

// Parses .obj and loads it into two arrays
bool ModelLoader::loadOBJ() {
    ifstream inFile;

    // Put this model in a folder titled "Models" in the base
    // of the repository.
    inFile.open("../../../Models/AmundsenRim_100mpp_triangulated.obj");

    string line;
    if (getline(inFile, line)) {
        cout << "successfully opened .obj file\n\n";
    }
    else {
        cout << "failed to read file\n\n";
        return false;
    }

    cout << "Reading .obj file...\n\n";
    while (!inFile.eof()) {
        getline(inFile, line);
        stringstream ss(line);
        PxVec3 v;
        string s;
        vector<unsigned> f;
        ss >> s;

        if (s == "v") {
            ss >> v[0] >> v[1] >> v[2];
            vecv.pushBack(v);
        }
        else if (s == "f") {
            char* stemp;

            // Loading in only the vertex indicies
            // cause PhysX doesn't care about normals
            for (int i = 0; i < 3; ++i) {
                ss >> s;
                stemp = (char*)s.c_str();
                stemp = strtok(stemp, "/");
                vecf.pushBack(atoi(stemp) - 1);
            }
        }
    }
    inFile.close();

    cout << "Final vecv size: " << vecv.size() << endl;
    cout << "Final vecf size: " << vecf.size() << endl;

    cout << "Finished reading .obj\n\n";
    return true;
}

// Returns true if file exists using the specified filepath
bool ModelLoader::fileExists(const std::string& name) {
    return ifstream(name).good();
}