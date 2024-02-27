#include <sim_utils.h>
#include <iostream>

using namespace std;

bool testVec3ToDouble3() {
    PxVec3 testVec(1.0f, 1.0f, 1.0f);

    std::vector<double> testArr(3);
    testArr = sim_utils::vec3ToDouble3(testVec);

    if (testVec[0] == testArr[0]) {
        return true;
    }
    else {
        return false;
    }
}

bool testMat33ToDouble9() {
    PxMat33 testMat;
    testMat.column0 = PxVec3(1.0f, 1.0f, 1.0f);
    testMat.column1 = PxVec3(1.0f, 1.0f, 1.0f);
    testMat.column2 = PxVec3(1.0f, 1.0f, 1.0f);

    std::vector<double> testArr9(9);
    testArr9 = sim_utils::mat33ToDouble9(testMat);

    if (testMat[0][2] == testArr9[2]) {
        return true;
    }
    else {
        return false;
    }
}

bool run_tests() {
    cout << "Testing Vec3ToDouble3()..." << endl;
    cout << "Result:" << testVec3ToDouble3() << endl;

    cout << "Testing Mat33ToDouble9()..." << endl;
    cout << "Result" << testMat33ToDouble9() << endl;

    return 0;
}

int main(void) {
    return run_tests();
}
