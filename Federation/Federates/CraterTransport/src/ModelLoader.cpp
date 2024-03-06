#include "ModelLoader.h"

PxTriangleMesh* ModelLoader::loadCraterMesh(PxPhysics* gPhysics) {
    loadOBJ();

    cout << "Loading .obj into PhysX...\n";

    meshDesc.points.count = vecv.size();
    meshDesc.points.data = vecv.data();
    meshDesc.points.stride = sizeof(PxVec3);
    meshDesc.triangles.data = vecf.data();
    meshDesc.triangles.stride = 3 * sizeof(unsigned);

    PxTolerancesScale scale;
    PxCookingParams params(scale);

    params.midphaseDesc = PxMeshMidPhase::eBVH33;
    params.suppressTriangleMeshRemapTable = true;
    params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
    params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
    params.midphaseDesc.mBVH33Desc.meshSizePerformanceTradeOff = 0.55f;

    #if defined(PX_CHECKED) || defined(PX_DEBUG)
    PX_ASSERT(PxValidateTriangleMesh(params, meshDesc));
    #endif

    PxTriangleMesh* triMesh = NULL;
    PxU32 meshSize = 0;

    triMesh = PxCreateTriangleMesh(params, meshDesc, gPhysics->getPhysicsInsertionCallback());
    cout << "Finished loading .obj into PhysX.\n";
    return triMesh;
}

bool ModelLoader::loadOBJ() {
    ifstream inFile;

    inFile.open("C:\\UCF\\Senior Design\\Simulations\\Models\\Terrain\\84 South Project V2\\84S\\84SMosaic_Punchout_100mpp.obj");

    char buffer[512];
    string line;
    
    if (getline(inFile, line)) {
        cout << "successfully opened .obj file" << endl;
    }
    else {
        cout << "failed to read file" << endl;
    }

    cout << "Reading .obj file...\n";
    while (!inFile.eof()) {
        getline(inFile, line);
        stringstream ss(line);
        PxVec3 v;
        string s;
        vector<unsigned> f;
        ss >> s;

        if (s == "v") {
            ss >> v[0] >> v[1] >> v[2];
            vecv.push_back(v);
        }
        else if (s == "vn") {
            ss >> v[0] >> v[1] >> v[2];
            vecn.push_back(v);
        }
        else if (s == "f") {
            vector<unsigned> temp(9, 0);
            char* stemp;

            for (int i = 0; i < 3; ++i) {
                ss >> s;
                stemp = (char*)s.c_str();
                stemp = strtok(stemp, "/");

                int ctr = 0;
                while (stemp != NULL) {
                    temp[i * 3 + ctr] = atoi(stemp);
                    stemp = strtok(NULL, "/");
                    ++ctr;
                }
            }

            vecf.push_back(temp);
        }
    }

    inFile.close();
    cout << "final vertex count: " << vecv.size() << endl;
    cout << "final normal count: " << vecn.size() << endl;
    cout << "final face count: "   << vecf.size() << endl;
    cout << "Finished reading .obj\n";
    return true;
}