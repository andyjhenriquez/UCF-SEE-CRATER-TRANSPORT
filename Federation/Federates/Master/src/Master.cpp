#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>
#include <LunarSimulation\HlaPayloadManager.h>
#include <LunarSimulation/HlaInteractionManager.h>
#include <LunarSimulation\HlaSynchronizationManager.h>

#include <iostream>
using namespace std;

using namespace LunarSimulation;

void StartSimulation(HlaWorldPtr hlaWorld);
void LoadScenario(HlaWorldPtr hlaWorld);
vector<double> convertToDoubleVector(string str);

int main(void) {
    HlaWorldPtr hlaWorld = HlaWorld::Factory::create();
    //Connecting to rti
    try {
        hlaWorld->connect();
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }
    cout << "Connected to RTI\n";
    
    bool quit = false;
    //Initial menu
    while (!quit) {
        int in;
        hlaWorld->getHlaSynchronizationManager()->
            registerSynchronizationPoint(L"Start");

        cout << "1 - Load Scenario" << endl
            << "2 - Start Simulation" << endl
            << "3 - Exit" << endl << endl;
        cin >> in;

        switch (in)
        {
            //Load Scenario
            case 1:
                hlaWorld->getHlaSynchronizationManager()->
                    registerSynchronizationPoint(L"ScenarioReady");
                LoadScenario(hlaWorld);
                hlaWorld->getHlaSynchronizationManager()->
                    achieveSynchronizationPoint(L"ScenarioReady");
                break;
            //Start simulation
            case 2:
                StartSimulation(hlaWorld);
                break;
            //Exit simulation
            case 3:
                quit = true;
                break;
            default:
                cout << "Error: Invalid Command";
                break;
        }
    }

    hlaWorld->disconnect();
}

void StartSimulation(HlaWorldPtr hlaWorld) {
    int in = 10000;
    string strInput;
    bool paused = false;
    HlaStartStopInteractionPtr simulationPlayback = 
        hlaWorld->getHlaInteractionManager()->getHlaStartStopInteraction();
    simulationPlayback->setHaltSimulation(paused);
    simulationPlayback->sendInteraction();
    hlaWorld->getHlaSynchronizationManager()->
        registerSynchronizationPoint(L"Start");
    hlaWorld->getHlaSynchronizationManager()->
        achieveSynchronizationPoint(L"Start");

    cout << "Running...\n\n";

    cout << "1 - End Simulation\n";

    cin >> in;

    while (in != 1) {
        cin >> in;
    }

    paused = true;
    simulationPlayback->setHaltSimulation(paused);
    simulationPlayback->sendInteraction();

    /*cout << "1 - " << (paused ? "Resume\n" : "Pause\n")
        << "2 - End\n";
    cin >> in;

    switch (in) {
    default:
        system("CLS");
        cout << "Error: Invalid option\n\n";
        break;
    }*/
}

void LoadScenario(HlaWorldPtr hlaWorld) {
    int in = 10000;
    string strInput;
    vector<double> posVector;
    HlaLoadScenarioInteractionPtr loadScenario = 
        hlaWorld->getHlaInteractionManager()->getHlaLoadScenarioInteraction();

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
        system("CLS");
        cout << endl << "-Scenario loaded-\n\n";
        
        break;
        //For Exit Simulation
    case 2:
        loadScenario->setSimulationScenario(L"Exit");

        cout << "Enter Payload Mass(kg): ";
        cin >> in;
        loadScenario->setPayloadMass(in);

        cout << "Enter Launcher position formatted as x y z: ";
        getline(cin >> ws, strInput);
        posVector = convertToDoubleVector(strInput);
        loadScenario->setLauncherPosition(posVector);

        cout << "Enter Launch velocity formatted as x y z: ";
        getline(cin >> ws, strInput);
        posVector = convertToDoubleVector(strInput);
        loadScenario->setLaunchSpeedVector(posVector);

        loadScenario->sendInteraction();
        system("CLS");
        cout << endl << "-Scenario loaded-\n\n";
        break;
    default:
        system("CLS");
        cout << "Error: Invalid option\n\n";
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
