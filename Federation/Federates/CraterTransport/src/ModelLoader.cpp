#include "ModelLoader.h"

PxTriangleMesh* ModelLoader::loadMesh(PxPhysics* gPhysics, string filepath) {
    bool status;

    // Attempt to open the specified crater mesh file
    if (fileExists(filepath)) {
        status = loadOBJ(filepath);
    }
    else {
        cout << "Couldn't open crater model, loading sample cube mesh instead.\n\n";
        return loadSampleCubeMesh(gPhysics);
    }

    if (!status) {
        return NULL;
    }

    cout << "Loading .obj into PhysX...\n";

    // Vertices
    meshDesc.points.count = vecv.size();
    meshDesc.points.data = reinterpret_cast<const PxVec3*>(&vecv[0][0]);
    meshDesc.points.stride = sizeof(PxVec3);

    // Faces
    // Note: Mesh being loaded needs to be triangulated due to the inflexible stride
    // value used in PhysX
    meshDesc.triangles.count = vecf.size() / 3;
    meshDesc.triangles.data = vecf.begin();
    meshDesc.triangles.stride = 3 * sizeof(PxU32);
    
    PxTolerancesScale scale;
    PxCookingParams params(scale);

    // Structure used for fast collision calculations
    params.midphaseDesc = PxMeshMidPhase::eBVH33;
    params.suppressTriangleMeshRemapTable = true;

    params.meshPreprocessParams &= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
    params.meshPreprocessParams &= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;

    // Value between 0 and 1 used to determine how much of the mesh is cooked before
    // simulation start
    params.midphaseDesc.mBVH33Desc.meshSizePerformanceTradeOff = 0.55f;

    #if defined(PX_CHECKED) || defined(PX_DEBUG)
    PX_ASSERT(PxValidateTriangleMesh(params, meshDesc));
    #endif

    // Creating output stream to write the cooked triangle mesh into PhysX
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

// Simple scene used as a backup if the crater mesh file isn't found
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
bool ModelLoader::loadOBJ(string filepath) {
    ifstream inFile;

    // Put this model in a folder titled "Models" in the base
    // of the repository.
    inFile.open(filepath);

    string line;

    if (getline(inFile, line)) {
        cout << "successfully opened .obj file\n\n";
    }
    else {
        cout << "failed to read file\n\n";
        return false;
    }

    cout << "Reading .obj file...\n\n";

    // Reading through the obj file, storing lines that
    // start with "v" into vecv and "f" into vecf
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
                vecf.pushBack(atoi(stemp) - 1); // Obj is 1-indexed so we need to subtract
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