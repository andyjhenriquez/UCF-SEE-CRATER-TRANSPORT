#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>
#include <LunarSimulation\HlaPayloadManager.h>
#include <LunarSimulation/HlaInteractionManager.h>
#include <LunarSimulation\HlaSynchronizationManager.h>

#include <iostream>
using namespace std;

using namespace LunarSimulation;

void LoadScenario(HlaWorldPtr hlaWorld);
vector<double> convertToDoubleVector(string str);

int main(void) {
    HlaWorldPtr hlaWorld = HlaWorld::Factory::create();

    try {
        hlaWorld->connect();
    }
    catch (std::exception& e) {
        // TODO Auto-generated catch block
        cout << e.what() << endl;
    }
    cout << "Connected to RTI\n";

    
    

    
    bool quit = false;
    //Initial menu
    while (!quit) {
        int in;
        cout << "1 - Load Scenario" << endl
            << "2 - Start Simulation" << endl
            << "3 - Exit" << endl << endl;
        cin >> in;

        switch (in)
        {
            case 1:
                hlaWorld->getHlaSynchronizationManager()->registerSynchronizationPoint(L"ScenarioReady");
                LoadScenario(hlaWorld);
                hlaWorld->getHlaSynchronizationManager()->achieveSynchronizationPoint(L"ScenarioReady");
                break;
            case 2:
                break;
            case 3:
                quit = true;
                break;
            default:
                cout << "Error: Invalid Command";
                break;
        }

        //hlaWorld->advanceToNextFrame();
    }

    hlaWorld->disconnect();
}

void LoadScenario(HlaWorldPtr hlaWorld) {
    int in = 10000;
    string strInput;
    vector<double> posVector;
    HlaLoadScenarioInteractionPtr loadScenario = hlaWorld->getHlaInteractionManager()->getHlaLoadScenarioInteraction();

    cout << "Which scenario?" << endl
        << "1 - Crater Entry" << endl
        << "2 - Crater Exit" << endl;

    cin >> in;
    switch (in)
    {
        //For Entry Simulation
    case 1:
        loadScenario->setSimulationScenario(L"Entry");

        cout << "Enter Rover Mass(kg) (default = 50): ";
        cin >> in;
        loadScenario->setRoverMass(in);

        cout << "Enter Rover Health(default = 100): ";
        cin >> in;
        loadScenario->setRoverHealth(in);

        cout << "Enter Rover start position formatted as x y z (default = 246, 1300, 216): ";
        getline(cin >> ws, strInput);
        posVector = convertToDoubleVector(strInput);
        loadScenario->setRoverInitialPosition(posVector);

        loadScenario->sendInteraction();
        
        break;
        //For Exit Simulation
    case 2:
        loadScenario->setSimulationScenario(L"Exit");
        break;
    default:
        break;
    }
}

vector<double> convertToDoubleVector(string str)
{
    vector<double> out;
    double x = 0.0, y = 0.0, z = 0.0;

    // variable to store token obtained from the original
    // string
    string s;

    // constructing stream from the string
    stringstream ss(str);

    // declaring vector to store the string after split
    vector<string> v;

    // using while loop until the getline condition is
    // satisfied
    // ' ' represent split the string whenever a space is
    // found in the original string
    while (getline(ss, s, ' ')) {

        // store token string in the vector
        v.push_back(s);
    }

    // print the vector
    for (int i = 0; i < v.size(); i++) {
        out.push_back(stod(v[i]));
    }
    return out;
}
