#include <LunarSimulation\HlaAllHeaders.h>
#include <LunarSimulation\HlaWorld.h>
#include <LunarSimulation\HlaPayloadManager.h>
#include <LunarSimulation\HlaInteractionListener.h>
#include <LunarSimulation\HlaInteractionManager.h>
#include <LunarSimulation\HlaSynchronizationManager.h>
#include <LunarSimulation\HlaMoonManager.h>
#include <LunarSimulation\HlaTuning.h>

#include "PhysicsManager.h"

#include <iostream>

using namespace LunarSimulation;

//implementation of the HlaInteractionListener interface. 
//This class is used to pull data from interactions that are sent to the RTI
class MyInteractionListener : public HlaInteractionListener::Adapter {
public:
    void loadScenario(bool local,
        HlaLoadScenarioParametersPtr parameters,
        HlaTimeStampPtr timeStamp,
        HlaLogicalTimePtr logicalTime) {

        scenarioData = parameters;
    }

    void startStop(bool local, 
        HlaStartStopParametersPtr parameters, 
        HlaTimeStampPtr timeStamp, 
        HlaLogicalTimePtr logicalTime) {
        startStopData = parameters;
    }

    HlaLoadScenarioParametersPtr scenarioData;
    HlaStartStopParametersPtr startStopData;
};

bool Initialize(HlaWorldPtr hlaWorld, MyInteractionListener* listener, int timeout_s);


int main(void) {
    // Creates federation if this is the first federate connected,
    // connects to existing federation otherwise
    HlaWorldPtr hlaWorld = HlaWorld::Factory::create();
    MyInteractionListener* interactionListener = new MyInteractionListener();
    Physics::PhysicsManager* physicsManager = new Physics::PhysicsManager();

    if (!physicsManager->initPhysics()) {
        return -1;
    }

    physicsManager->loadSampleEntryScene();

    try {
        hlaWorld->connect();
    }
    catch (std::exception& e) {
        // TODO Auto-generated catch block
        std::cout << e.what() << std::endl;
    }
    std::cout << "Connected\n";

    if (Initialize(hlaWorld, interactionListener, 5)) {

    }
    else {
        cout << "No master federate detected. Continue without?(y or n) ";
        char tmp;
        cin >> tmp;

        if(tmp == 'y' || tmp == 'Y'){
        
        }
        else {
            cout << "Alright then. Waiting for Master...\n";
            if (Initialize(hlaWorld, interactionListener, 180)) {
                
            }
            else {
                cout << "\nFailed to find Master Federate\n\n";
                return -1;
            }
            
        }

    }


    //Example of we'd use the MyInteractionListener class to pull data from a hla interaction
    //cout << "Rover Health: " << interactionListener->scenarioData->getRoverHealth() << endl;
    
    // Manages Payload instances, allows you to handle and find different instances
    HlaPayloadManagerPtr payloadManager = hlaWorld->getHlaPayloadManager();

    // Single Payload instance, extends Dynamical Entity and has a number
    // of functions to retrive its values such as acceleration and position
    HlaPayloadPtr payload = payloadManager->createLocalHlaPayload(L"Payload");

    //Waiting for start from master federate
    cout << "Waiting for start from master...\n\n";
    hlaWorld->getHlaSynchronizationManager()->waitForSynchronizationPointRegistration(L"Start", 180 * 1000);
    hlaWorld->getHlaSynchronizationManager()->achieveSynchronizationPointAndWaitForSynchronized(L"Start", 120 * 1000);

    cout << "Starting crater entry simulation";

    // TODO: Find a stopping point for our federate
    while (!interactionListener->startStopData->getHaltSimulation()) {
        try {
            physicsManager->simulateStep();

            // Manages variable/state changes and communicates them to the federation.
            // New instance must be created on every loop.
            HlaPayloadUpdaterPtr updater = payload->getHlaPayloadUpdater();

            // Example of how to update a variable (in this case of a Payload instance)
            // Ideally we'll call something like Physics.calculateAcceleration() or an
            // equivalent function.
            updater->setAcceleration({100.0, 100.0, 100.0});


            // Packages all state/variable changes and sends them out to the federation
            // where other federates can pull the new values in and use them as needed.
            updater->sendUpdate();
        }
        catch (std::exception& e) {
            // TODO Auto-generated catch block
            std::cout << e.what() << std::endl;
        }

        hlaWorld->advanceToNextFrame();
    }

    physicsManager->cleanupPhysics();

    // Here we will do all of the federate cleanup necessary after it has finished running.
    // Unfortunately we can't run this code right now because we don't have a valid stopping
    // condition for our main loop.
    hlaWorld->disconnect();
}

//Syncs this simulation with other simulations in the federation
//Takes in HlaWorldPtr
bool Initialize(HlaWorldPtr hlaWorld, MyInteractionListener* listener, int timeout_s) {
    //adding interaction listener to hlaWorld
    HlaInteractionListenerPtr myInteractionListener(listener);
    hlaWorld->getHlaInteractionManager()->addHlaInteractionListener(myInteractionListener);

    //waiting for user to set scenario in Master before continuing
    cout << "Waiting for scenario info" << endl;
    if (!hlaWorld->getHlaSynchronizationManager()->waitForSynchronizationPointRegistration(L"ScenarioReady", timeout_s * 1000)){
        cout << "Failed to get scenario information" << endl;
        return false;
    }
    if (!hlaWorld->getHlaSynchronizationManager()->achieveSynchronizationPointAndWaitForSynchronized(L"ScenarioReady", timeout_s * 1000)) {
        cout << "Connection to other federates timed out" << endl;
    }
    cout << "Federation synched" << endl;

    return true;
}