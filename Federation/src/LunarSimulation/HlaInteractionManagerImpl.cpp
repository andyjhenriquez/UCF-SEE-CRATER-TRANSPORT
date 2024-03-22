/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include "HlaInteractionManagerImpl.h"
#include "StringUtil.h"

#include <LunarSimulation/HlaTuning.h>

#include <RtiDriver/Types.h>

#include "HlaWorldImpl.h"
#include "RtiInteractionManager.h"
#include "ParameterValue.h"
#include "HlaLogicalTimeImpl.h"
#include "HlaFederateIdImpl.h"

static const wchar_t HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME[] = L"HLAinteractionRoot";
static const wchar_t START_STOP_INTERACTION_CLASS_NAME[] = L"HLAinteractionRoot.Start_Stop";
static const wchar_t LOAD_SCENARIO_INTERACTION_CLASS_NAME[] = L"HLAinteractionRoot.LoadScenario";
static const wchar_t MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME[] = L"HLAinteractionRoot.ModeTransitionRequest";

using namespace LunarSimulation;
using namespace std;

HlaInteractionManagerImpl::HlaInteractionManagerImpl(RtiInteractionManager *interactionManager, HlaWorldImpl *hlaWorld)
    : _interactionManager(interactionManager),
      _hlaWorld(hlaWorld){
    _enabled.insert(HLAINTERACTION_ROOT);
    _interactionNames.put(HLAINTERACTION_ROOT, HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME);
    _enabled.insert(START_STOP);
    _interactionNames.put(START_STOP, START_STOP_INTERACTION_CLASS_NAME);
    _enabled.insert(LOAD_SCENARIO);
    _interactionNames.put(LOAD_SCENARIO, LOAD_SCENARIO_INTERACTION_CLASS_NAME);
    _enabled.insert(MODE_TRANSITION_REQUEST);
    _interactionNames.put(MODE_TRANSITION_REQUEST, MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME);

    _interactionManager->addManager(this, HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME);
    _interactionManager->addManager(this, START_STOP_INTERACTION_CLASS_NAME);
    _interactionManager->addManager(this, LOAD_SCENARIO_INTERACTION_CLASS_NAME);
    _interactionManager->addManager(this, MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME);
}

bool HlaInteractionManagerImpl::isEnabled(const std::wstring& interactionClassName) {
    Interaction interaction;
    if (find(interaction, interactionClassName)) {
        return _enabled.find(interaction) != _enabled.end();
    }
    return false;
}

bool HlaInteractionManagerImpl::isOptional(const std::wstring& interactionClassName) {
    Interaction interaction;
    if (find(interaction, interactionClassName)) {
        return _optional.find(interaction) != _optional.end();
    }
    return false;
}

void HlaInteractionManagerImpl::connected(const RtiDriver::InteractionClassHandle& interactionClassHandle, const wstring& interactionClassName)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (interactionClassName == HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME) {
        _interactionManager->publish(interactionClassHandle);
        _interactionManager->subscribe(interactionClassHandle);
        _interactions.put(interactionClassName, InteractionClassHandlePtr(interactionClassHandle.clone()));
        return;
    }
    if (interactionClassName == START_STOP_INTERACTION_CLASS_NAME) {
        _interactionManager->publish(interactionClassHandle);
        _interactionManager->subscribe(interactionClassHandle);
        _interactions.put(interactionClassName, InteractionClassHandlePtr(interactionClassHandle.clone()));
        return;
    }
    if (interactionClassName == LOAD_SCENARIO_INTERACTION_CLASS_NAME) {
        _interactionManager->publish(interactionClassHandle);
        _interactionManager->subscribe(interactionClassHandle);
        _interactions.put(interactionClassName, InteractionClassHandlePtr(interactionClassHandle.clone()));
        return;
    }
    if (interactionClassName == MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME) {
        _interactionManager->publish(interactionClassHandle);
        _interactionManager->subscribe(interactionClassHandle);
        _interactions.put(interactionClassName, InteractionClassHandlePtr(interactionClassHandle.clone()));
        return;
    }
}

void HlaInteractionManagerImpl::disconnected(const LunarSimulation::InteractionClassHandlePtr interactionClassHandle) {
    _interactions.removeByValue(interactionClassHandle);
}

void HlaInteractionManagerImpl::sendHLAinteractionRoot(
) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaHLAinteractionRootInteractionPtr interaction = getHlaHLAinteractionRootInteraction();
   interaction->sendInteraction();
}

void HlaInteractionManagerImpl::sendHLAinteractionRoot(
         HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaHLAinteractionRootInteractionPtr interaction = getHlaHLAinteractionRootInteraction();
   interaction->sendInteraction(timeStamp);
}

void HlaInteractionManagerImpl::sendHLAinteractionRoot(
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaHLAinteractionRootInteractionPtr interaction = getHlaHLAinteractionRootInteraction();
   interaction->sendInteraction(logicalTime);
}

void HlaInteractionManagerImpl::sendHLAinteractionRoot(
         HlaTimeStampPtr timeStamp,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaHLAinteractionRootInteractionPtr interaction = getHlaHLAinteractionRootInteraction();
   interaction->sendInteraction(timeStamp, logicalTime);
}

void HlaInteractionManagerImpl::sendHLAinteractionRootParams(
   HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   try {
       sendHLAinteractionRootParams(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException&) {
       //Could not happen
   }
}

void HlaInteractionManagerImpl::sendHLAinteractionRootParams(
   HlaTimeStampPtr timeStamp,
   HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {

    InteractionClassHandlePtr handle;
    if (!_interactions.find(HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME, handle)) {
        throw HlaNotConnectedException("Not connected");
    }

    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    RtiDriver::NameValueMap nameValueMap;
    _interactionManager->sendInteraction(*handle, nameValueMap, timeStamp, logicalTime);

    fireHLAinteractionRoot(
        true,
        timeStamp,
        logicalTime
    );
}

void HlaInteractionManagerImpl::sendStartStop(
         bool haltSimulation,
         bool exitSimulation
) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->setHaltSimulation(haltSimulation);
   interaction->setExitSimulation(exitSimulation);
   interaction->sendInteraction();
}

void HlaInteractionManagerImpl::sendStartStop(
         bool haltSimulation,
         bool exitSimulation,
         HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->setHaltSimulation(haltSimulation);
   interaction->setExitSimulation(exitSimulation);
   interaction->sendInteraction(timeStamp);
}

void HlaInteractionManagerImpl::sendStartStop(
         bool haltSimulation,
         bool exitSimulation,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->setHaltSimulation(haltSimulation);
   interaction->setExitSimulation(exitSimulation);
   interaction->sendInteraction(logicalTime);
}

void HlaInteractionManagerImpl::sendStartStop(
         bool haltSimulation,
         bool exitSimulation,
         HlaTimeStampPtr timeStamp,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->setHaltSimulation(haltSimulation);
   interaction->setExitSimulation(exitSimulation);
   interaction->sendInteraction(timeStamp, logicalTime);
}

void HlaInteractionManagerImpl::sendStartStopParams(
   HlaStartStopParametersPtr parameters,
   HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   try {
       sendStartStopParams(parameters, timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException&) {
       //Could not happen
   }
}

void HlaInteractionManagerImpl::sendStartStopParams(
   HlaStartStopParametersPtr parameters,
   HlaTimeStampPtr timeStamp,
   HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {

    InteractionClassHandlePtr handle;
    if (!_interactions.find(START_STOP_INTERACTION_CLASS_NAME, handle)) {
        throw HlaNotConnectedException("Not connected");
    }

    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    RtiDriver::NameValueMap nameValueMap;
    {
        std::unique_lock<std::mutex> lock(_encoderLock);

        if (parameters->hasHaltSimulation()) {
            try {
                _hLAbooleanEncoder.set(parameters->getHaltSimulation());
                RtiDriver::VariableLengthData res;
                _hLAbooleanEncoder.encodeInto(res);
                nameValueMap[L"HaltSimulation"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode HaltSimulation: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasExitSimulation()) {
            try {
                _hLAbooleanEncoder.set(parameters->getExitSimulation());
                RtiDriver::VariableLengthData res;
                _hLAbooleanEncoder.encodeInto(res);
                nameValueMap[L"Exit_Simulation"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode Exit_Simulation: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }
    }

    _interactionManager->sendInteraction(*handle, nameValueMap, timeStamp, logicalTime);

    fireStartStop(
        true,
        parameters,
        timeStamp,
        logicalTime
    );
}

void HlaInteractionManagerImpl::sendLoadScenario(
         double moonFriction,
         std::vector</* 3 */ double > roverInitialPosition,
         double roverHealth,
         double roverMass,
         double payloadMass,
         std::vector</* 3 */ double > launchSpeedVector,
         std::vector</* 3 */ double > roverStartPosition,
         std::wstring simulationScenario,
         std::vector</* 3 */ double > launcherPosition,
         std::vector</* 3 */ double > launchForce
) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaLoadScenarioInteractionPtr interaction = getHlaLoadScenarioInteraction();
   interaction->setMoonFriction(moonFriction);
   interaction->setRoverInitialPosition(roverInitialPosition);
   interaction->setRoverHealth(roverHealth);
   interaction->setRoverMass(roverMass);
   interaction->setPayloadMass(payloadMass);
   interaction->setLaunchSpeedVector(launchSpeedVector);
   interaction->setRoverStartPosition(roverStartPosition);
   interaction->setSimulationScenario(simulationScenario);
   interaction->setLauncherPosition(launcherPosition);
   interaction->setLaunchForce(launchForce);
   interaction->sendInteraction();
}

void HlaInteractionManagerImpl::sendLoadScenario(
         double moonFriction,
         std::vector</* 3 */ double > roverInitialPosition,
         double roverHealth,
         double roverMass,
         double payloadMass,
         std::vector</* 3 */ double > launchSpeedVector,
         std::vector</* 3 */ double > roverStartPosition,
         std::wstring simulationScenario,
         std::vector</* 3 */ double > launcherPosition,
         std::vector</* 3 */ double > launchForce,
         HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaLoadScenarioInteractionPtr interaction = getHlaLoadScenarioInteraction();
   interaction->setMoonFriction(moonFriction);
   interaction->setRoverInitialPosition(roverInitialPosition);
   interaction->setRoverHealth(roverHealth);
   interaction->setRoverMass(roverMass);
   interaction->setPayloadMass(payloadMass);
   interaction->setLaunchSpeedVector(launchSpeedVector);
   interaction->setRoverStartPosition(roverStartPosition);
   interaction->setSimulationScenario(simulationScenario);
   interaction->setLauncherPosition(launcherPosition);
   interaction->setLaunchForce(launchForce);
   interaction->sendInteraction(timeStamp);
}

void HlaInteractionManagerImpl::sendLoadScenario(
         double moonFriction,
         std::vector</* 3 */ double > roverInitialPosition,
         double roverHealth,
         double roverMass,
         double payloadMass,
         std::vector</* 3 */ double > launchSpeedVector,
         std::vector</* 3 */ double > roverStartPosition,
         std::wstring simulationScenario,
         std::vector</* 3 */ double > launcherPosition,
         std::vector</* 3 */ double > launchForce,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaLoadScenarioInteractionPtr interaction = getHlaLoadScenarioInteraction();
   interaction->setMoonFriction(moonFriction);
   interaction->setRoverInitialPosition(roverInitialPosition);
   interaction->setRoverHealth(roverHealth);
   interaction->setRoverMass(roverMass);
   interaction->setPayloadMass(payloadMass);
   interaction->setLaunchSpeedVector(launchSpeedVector);
   interaction->setRoverStartPosition(roverStartPosition);
   interaction->setSimulationScenario(simulationScenario);
   interaction->setLauncherPosition(launcherPosition);
   interaction->setLaunchForce(launchForce);
   interaction->sendInteraction(logicalTime);
}

void HlaInteractionManagerImpl::sendLoadScenario(
         double moonFriction,
         std::vector</* 3 */ double > roverInitialPosition,
         double roverHealth,
         double roverMass,
         double payloadMass,
         std::vector</* 3 */ double > launchSpeedVector,
         std::vector</* 3 */ double > roverStartPosition,
         std::wstring simulationScenario,
         std::vector</* 3 */ double > launcherPosition,
         std::vector</* 3 */ double > launchForce,
         HlaTimeStampPtr timeStamp,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaLoadScenarioInteractionPtr interaction = getHlaLoadScenarioInteraction();
   interaction->setMoonFriction(moonFriction);
   interaction->setRoverInitialPosition(roverInitialPosition);
   interaction->setRoverHealth(roverHealth);
   interaction->setRoverMass(roverMass);
   interaction->setPayloadMass(payloadMass);
   interaction->setLaunchSpeedVector(launchSpeedVector);
   interaction->setRoverStartPosition(roverStartPosition);
   interaction->setSimulationScenario(simulationScenario);
   interaction->setLauncherPosition(launcherPosition);
   interaction->setLaunchForce(launchForce);
   interaction->sendInteraction(timeStamp, logicalTime);
}

void HlaInteractionManagerImpl::sendLoadScenarioParams(
   HlaLoadScenarioParametersPtr parameters,
   HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   try {
       sendLoadScenarioParams(parameters, timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException&) {
       //Could not happen
   }
}

void HlaInteractionManagerImpl::sendLoadScenarioParams(
   HlaLoadScenarioParametersPtr parameters,
   HlaTimeStampPtr timeStamp,
   HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {

    InteractionClassHandlePtr handle;
    if (!_interactions.find(LOAD_SCENARIO_INTERACTION_CLASS_NAME, handle)) {
        throw HlaNotConnectedException("Not connected");
    }

    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    RtiDriver::NameValueMap nameValueMap;
    {
        std::unique_lock<std::mutex> lock(_encoderLock);

        if (parameters->hasMoonFriction()) {
            try {
                _hLAfloat64LEEncoder.set(parameters->getMoonFriction());
                RtiDriver::VariableLengthData res;
                _hLAfloat64LEEncoder.encodeInto(res);
                nameValueMap[L"MoonFriction"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode MoonFriction: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasRoverInitialPosition()) {
            try {
                _positionVectorEncoderEncoder.set(parameters->getRoverInitialPosition());
                RtiDriver::VariableLengthData res;
                res.reserve(_positionVectorEncoderEncoder.getEncodedLength());
                _positionVectorEncoderEncoder.encodeInto(res);
                nameValueMap[L"RoverInitialPosition"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode RoverInitialPosition: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasRoverHealth()) {
            try {
                _hLAfloat64LEEncoder.set(parameters->getRoverHealth());
                RtiDriver::VariableLengthData res;
                _hLAfloat64LEEncoder.encodeInto(res);
                nameValueMap[L"RoverHealth"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode RoverHealth: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasRoverMass()) {
            try {
                _hLAfloat64LEEncoder.set(parameters->getRoverMass());
                RtiDriver::VariableLengthData res;
                _hLAfloat64LEEncoder.encodeInto(res);
                nameValueMap[L"RoverMass"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode RoverMass: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasPayloadMass()) {
            try {
                _hLAfloat64LEEncoder.set(parameters->getPayloadMass());
                RtiDriver::VariableLengthData res;
                _hLAfloat64LEEncoder.encodeInto(res);
                nameValueMap[L"PayloadMass"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode PayloadMass: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasLaunchSpeedVector()) {
            try {
                _velocityVectorEncoderEncoder.set(parameters->getLaunchSpeedVector());
                RtiDriver::VariableLengthData res;
                res.reserve(_velocityVectorEncoderEncoder.getEncodedLength());
                _velocityVectorEncoderEncoder.encodeInto(res);
                nameValueMap[L"LaunchSpeedVector"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode LaunchSpeedVector: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasRoverStartPosition()) {
            try {
                _positionVectorEncoderEncoder.set(parameters->getRoverStartPosition());
                RtiDriver::VariableLengthData res;
                res.reserve(_positionVectorEncoderEncoder.getEncodedLength());
                _positionVectorEncoderEncoder.encodeInto(res);
                nameValueMap[L"RoverStartPosition"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode RoverStartPosition: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasSimulationScenario()) {
            try {
                _hLAunicodeStringEncoder.set(parameters->getSimulationScenario());
                RtiDriver::VariableLengthData res;
                res.reserve(_hLAunicodeStringEncoder.getEncodedLength());
                _hLAunicodeStringEncoder.encodeInto(res);
                nameValueMap[L"SimulationScenario"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode SimulationScenario: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasLauncherPosition()) {
            try {
                _positionVectorEncoderEncoder.set(parameters->getLauncherPosition());
                RtiDriver::VariableLengthData res;
                res.reserve(_positionVectorEncoderEncoder.getEncodedLength());
                _positionVectorEncoderEncoder.encodeInto(res);
                nameValueMap[L"LauncherPosition"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode LauncherPosition: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }

        if (parameters->hasLaunchForce()) {
            try {
                _forceVectorEncoderEncoder.set(parameters->getLaunchForce());
                RtiDriver::VariableLengthData res;
                res.reserve(_forceVectorEncoderEncoder.getEncodedLength());
                _forceVectorEncoderEncoder.encodeInto(res);
                nameValueMap[L"LaunchForce"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode LaunchForce: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }
    }

    _interactionManager->sendInteraction(*handle, nameValueMap, timeStamp, logicalTime);

    fireLoadScenario(
        true,
        parameters,
        timeStamp,
        logicalTime
    );
}

void HlaInteractionManagerImpl::sendModeTransitionRequest(
         MTRMode::MTRMode executionMode
) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaModeTransitionRequestInteractionPtr interaction = getHlaModeTransitionRequestInteraction();
   interaction->setExecutionMode(executionMode);
   interaction->sendInteraction();
}

void HlaInteractionManagerImpl::sendModeTransitionRequest(
         MTRMode::MTRMode executionMode,
         HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaModeTransitionRequestInteractionPtr interaction = getHlaModeTransitionRequestInteraction();
   interaction->setExecutionMode(executionMode);
   interaction->sendInteraction(timeStamp);
}

void HlaInteractionManagerImpl::sendModeTransitionRequest(
         MTRMode::MTRMode executionMode,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaModeTransitionRequestInteractionPtr interaction = getHlaModeTransitionRequestInteraction();
   interaction->setExecutionMode(executionMode);
   interaction->sendInteraction(logicalTime);
}

void HlaInteractionManagerImpl::sendModeTransitionRequest(
         MTRMode::MTRMode executionMode,
         HlaTimeStampPtr timeStamp,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaModeTransitionRequestInteractionPtr interaction = getHlaModeTransitionRequestInteraction();
   interaction->setExecutionMode(executionMode);
   interaction->sendInteraction(timeStamp, logicalTime);
}

void HlaInteractionManagerImpl::sendModeTransitionRequestParams(
   HlaModeTransitionRequestParametersPtr parameters,
   HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   try {
       sendModeTransitionRequestParams(parameters, timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException&) {
       //Could not happen
   }
}

void HlaInteractionManagerImpl::sendModeTransitionRequestParams(
   HlaModeTransitionRequestParametersPtr parameters,
   HlaTimeStampPtr timeStamp,
   HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {

    InteractionClassHandlePtr handle;
    if (!_interactions.find(MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME, handle)) {
        throw HlaNotConnectedException("Not connected");
    }

    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    RtiDriver::NameValueMap nameValueMap;
    {
        std::unique_lock<std::mutex> lock(_encoderLock);

        if (parameters->hasExecutionMode()) {
            try {
                _mTRModeEncoderEncoder.set(parameters->getExecutionMode());
                RtiDriver::VariableLengthData res;
                _mTRModeEncoderEncoder.encodeInto(res);
                nameValueMap[L"execution_mode"] = res;
            } catch (EncodingHelpers::EncoderException & e) {
                HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode execution_mode: " + e.what()));
                _hlaWorld->postException(ex);
            }
        }
    }

    _interactionManager->sendInteraction(*handle, nameValueMap, timeStamp, logicalTime);

    fireModeTransitionRequest(
        true,
        parameters,
        timeStamp,
        logicalTime
    );
}

void HlaInteractionManagerImpl::addHlaInteractionListener(HlaInteractionListenerPtr listener) {
    _interactionListeners.add(listener);
}

void HlaInteractionManagerImpl::removeHlaInteractionListener(HlaInteractionListenerPtr listener) {
    _interactionListeners.remove(listener);
}

std::wstring HlaInteractionManagerImpl::getHlaName(HlaInteractionManager::Interaction interaction) {
    wstring name;
    if (_interactionNames.find(interaction, name)) {
        return name;
    } else {
        return L"";
    }
}

bool HlaInteractionManagerImpl::find(HlaInteractionManager::Interaction& interaction, std::wstring interactionHlaName) {
    return _interactionNames.findByValue(interactionHlaName, interaction);
}

void HlaInteractionManagerImpl::setEnabled(bool enabled, HlaInteractionManager::Interaction interaction) {
    _optional.erase(interaction);
    if (enabled) {
        _enabled.insert(interaction);
    } else {
        _enabled.erase(interaction);
    }
}

void HlaInteractionManagerImpl::setEnabled(bool enabled, std::set<HlaInteractionManager::Interaction> interactions) {
    for (set<Interaction>::iterator it = interactions.begin(); it != interactions.end(); ++it) {
        setEnabled(enabled, *it);
    }
}

void HlaInteractionManagerImpl::setEnabledIfAvailableInFom(std::set<HlaInteractionManager::Interaction> interactions) {
    for (set<Interaction>::iterator it = interactions.begin(); it != interactions.end(); ++it) {
        _optional.insert(*it);
        _enabled.insert(*it);
    }
}

bool HlaInteractionManagerImpl::isEnabled(HlaInteractionManager::Interaction interaction) {
    return _interactions.find(getHlaName(interaction));
}

HlaFederateIdImplPtr HlaInteractionManagerImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

void HlaInteractionManagerImpl::receiveInteraction(
    const RtiDriver::InteractionClassHandle& interactionClassHandle,
    const RtiDriver::NameValueMap& parameters,
    const HlaFederateIdImplPtr producingFederate,
    HlaTimeStampPtr timeStamp,
    HlaLogicalTimeImplPtr logicalTime) {

    wstring interactionName;
    InteractionClassHandlePtr handle(interactionClassHandle.clone());
    bool foundInteractionName = _interactions.findByValue(handle, interactionName);
    if (!foundInteractionName) {
        HlaExceptionPtr ex(new HlaInternalException(L"Received unknown interaction: " + (const std::wstring &)interactionClassHandle));
        _hlaWorld->postException(ex);
        return;
    }

    Interaction interaction;
    if (!find(interaction, interactionName)) {
        HlaExceptionPtr ex(new HlaInternalException(L"Received unknown interaction: " + interactionName));
        _hlaWorld->postException(ex);
        return;
    }

    switch (interaction) {
        case HLAINTERACTION_ROOT: {
            fireHLAinteractionRoot(false, timeStamp, logicalTime);
            return;
        }
        case START_STOP: {
            decodeAndFireStartStop(parameters, producingFederate, timeStamp, logicalTime);
            return;
        }
        case LOAD_SCENARIO: {
            decodeAndFireLoadScenario(parameters, producingFederate, timeStamp, logicalTime);
            return;
        }
        case MODE_TRANSITION_REQUEST: {
            decodeAndFireModeTransitionRequest(parameters, producingFederate, timeStamp, logicalTime);
            return;
        }
        default:
            break;
    }

    HlaExceptionPtr ex(new HlaInternalException(L"Received unknown interaction: " + interactionName));
    _hlaWorld->postException(ex);
}

void HlaInteractionManagerImpl::fireHLAinteractionRoot(
    bool local,
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {
    std::set<HlaInteractionListenerPtr> listeners = _interactionListeners.getListeners();
    for (std::set<HlaInteractionListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaInteractionListener::hLAinteractionRoot, *it, local, hlaTimeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaInteractionManagerImpl::fireStartStop(
    bool local,
    HlaStartStopParametersPtr parameters,
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {
    std::set<HlaInteractionListenerPtr> listeners = _interactionListeners.getListeners();
    for (std::set<HlaInteractionListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaInteractionListener::startStop, *it, local, parameters, hlaTimeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaInteractionManagerImpl::fireLoadScenario(
    bool local,
    HlaLoadScenarioParametersPtr parameters,
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {
    std::set<HlaInteractionListenerPtr> listeners = _interactionListeners.getListeners();
    for (std::set<HlaInteractionListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaInteractionListener::loadScenario, *it, local, parameters, hlaTimeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaInteractionManagerImpl::fireModeTransitionRequest(
    bool local,
    HlaModeTransitionRequestParametersPtr parameters,
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {
    std::set<HlaInteractionListenerPtr> listeners = _interactionListeners.getListeners();
    for (std::set<HlaInteractionListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaInteractionListener::modeTransitionRequest, *it, local, parameters, hlaTimeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaInteractionManagerImpl::postLengthException(const std::wstring& interactionName, const std::wstring& parameterName, const std::size_t expectedSize, const bool includeData, const std::vector<char> & data) {
    HlaExceptionPtr de(new HlaDecodeException(L"Failed to decode parameter " + parameterName + L" in interaction " + interactionName + L": Invalid data length " +
                                              StringUtil::sizeToWstring(data.size()) + L", expected " + StringUtil::sizeToWstring(expectedSize) + L".",
                                              includeData, data));
    _hlaWorld->postException(de);
}

void HlaInteractionManagerImpl::postDecodeException(const std::wstring& interactionName, const std::wstring& parameterName, const std::wstring& message, const bool includeData, const std::vector<char> & data) {
    HlaExceptionPtr de(new HlaDecodeException(L"Failed to decode parameter " + parameterName + L" in interaction " + interactionName + L": " + message, includeData, data));
    _hlaWorld->postException(de);
}

/*
 * Supporting impls for HlaHLAinteractionRoot interaction
 */

namespace LunarSimulation {
    class HlaHLAinteractionRootInteractionImpl : public LunarSimulation::HlaHLAinteractionRootInteraction {
    private:
       HlaInteractionManagerImpl* _outerThis;
    public:
       explicit HlaHLAinteractionRootInteractionImpl(HlaInteractionManagerImpl* outerThis) : _outerThis(outerThis) {}

       void sendInteraction() THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendHLAinteractionRootParams(HlaTimeStampPtr());
       }

       void sendInteraction(HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendHLAinteractionRootParams(timestamp);
       }

       void sendInteraction(HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendHLAinteractionRootParams(HlaTimeStampPtr(), logicalTime);
       }

       void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendHLAinteractionRootParams(timestamp, logicalTime);
       }
    };
}

HlaHLAinteractionRootInteractionPtr HlaInteractionManagerImpl::getHlaHLAinteractionRootInteraction() {
   HlaHLAinteractionRootInteraction* ptr = new HlaHLAinteractionRootInteractionImpl(this);
   return HlaHLAinteractionRootInteractionPtr(ptr);
}

/*
 * Supporting impls for HlaStartStop interaction
 */

namespace LunarSimulation {
    class HlaStartStopParametersImpl : public LunarSimulation::HlaStartStopParameters {
    private:
       LunarSimulation::ParameterValue<bool > _haltSimulation;
       LunarSimulation::ParameterValue<bool > _exitSimulation;
       HlaFederateIdImplPtr _producingFederate;
       bool _isWithinInterest;
    public:
       HlaStartStopParametersImpl(
          LunarSimulation::ParameterValue<bool > haltSimulation,
          LunarSimulation::ParameterValue<bool > exitSimulation,
          const HlaFederateIdImplPtr producingFederate,
          bool isWithinInterest
       ) :
          _haltSimulation(haltSimulation),
          _exitSimulation(exitSimulation),
          _producingFederate(producingFederate),
          _isWithinInterest(isWithinInterest)
       {}

       bool hasHaltSimulation() {
          return _haltSimulation.hasValue();
       }

       bool getHaltSimulation() THROW_SPEC (HlaValueNotSetException) {
          if (hasHaltSimulation()) {
             return *_haltSimulation.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'haltSimulation' not set");
          }
       }

       bool getHaltSimulation(bool defaultValue) {
          if (hasHaltSimulation()) {
             return *_haltSimulation.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasExitSimulation() {
          return _exitSimulation.hasValue();
       }

       bool getExitSimulation() THROW_SPEC (HlaValueNotSetException) {
          if (hasExitSimulation()) {
             return *_exitSimulation.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'exitSimulation' not set");
          }
       }

       bool getExitSimulation(bool defaultValue) {
          if (hasExitSimulation()) {
             return *_exitSimulation.getValue();
          } else {
             return defaultValue;
          }
       }

       HlaFederateIdPtr getProducingFederate() const {
           return _producingFederate;
       }

       bool isWithinInterest() const {
           return _isWithinInterest;
       }
    };

    std::wostream & operator << (std::wostream &o, HlaStartStopParameters &p) {
        o << L"<HlaStartStopParameters:";
        if (p.hasHaltSimulation()) {
           o << L" [" << "HaltSimulation" << L":" << p.getHaltSimulation() << L"]";
        }
        if (p.hasExitSimulation()) {
           o << L" [" << "Exit_Simulation" << L":" << p.getExitSimulation() << L"]";
        }
        o << L">";
        return o;
    }

    std::ostream & operator << (std::ostream &o, HlaStartStopParameters &p) {
        o << "<HlaStartStopParameters:";
        if (p.hasHaltSimulation()) {
           o << " [" << "HaltSimulation" << ":" << p.getHaltSimulation() << "]";
        }
        if (p.hasExitSimulation()) {
           o << " [" << "Exit_Simulation" << ":" << p.getExitSimulation() << "]";
        }
        o << ">";
        return o;
    }

    class HlaStartStopInteractionImpl : public LunarSimulation::HlaStartStopInteraction {
    private:
       HlaInteractionManagerImpl* _outerThis;
       mutable std::recursive_mutex _lock;

       HlaStartStopParametersPtr build() {
          return build(_outerThis->getFederateIdImpl());
       }
    public:
       LunarSimulation::ParameterValue<bool > _haltSimulation;
       LunarSimulation::ParameterValue<bool > _exitSimulation;
       explicit HlaStartStopInteractionImpl(HlaInteractionManagerImpl* outerThis) : _outerThis(outerThis) {}

       HlaStartStopParametersPtr build(const HlaFederateIdImplPtr producingFederate) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          return HlaStartStopParametersPtr(new HlaStartStopParametersImpl(
             _haltSimulation,
             _exitSimulation,
             producingFederate,
             true
          ));
       }

       void setHaltSimulation(bool haltSimulation) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _haltSimulation.setValue(std::shared_ptr<bool >(new bool(haltSimulation)));
       }

       void setExitSimulation(bool exitSimulation) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _exitSimulation.setValue(std::shared_ptr<bool >(new bool(exitSimulation)));
       }

       void sendInteraction() THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(build(), HlaTimeStampPtr());
       }

       void sendInteraction(HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(build(), timestamp);
       }

       void sendInteraction(HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(build(), HlaTimeStampPtr(), logicalTime);
       }

       void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(build(), timestamp, logicalTime);
       }
    };
}

HlaStartStopInteractionPtr HlaInteractionManagerImpl::getHlaStartStopInteraction() {
   HlaStartStopInteraction* ptr = new HlaStartStopInteractionImpl(this);
   return HlaStartStopInteractionPtr(ptr);
}

void HlaInteractionManagerImpl::decodeAndFireStartStop(
    const RtiDriver::NameValueMap& parameters,
    const HlaFederateIdImplPtr producingFederate,
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {

    const bool verifyDataLength = _hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH;
    const bool includeData = _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION;

    RtiDriver::NameValueMap::const_iterator iter;
    HlaStartStopInteractionImplPtr interaction(new HlaStartStopInteractionImpl(this));
    iter = parameters.find(L"HaltSimulation");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _hLAbooleanDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"START_STOP", L"HaltSimulation", encodedSize, includeData, iter->second);
            }
            interaction->setHaltSimulation(_hLAbooleanDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"START_STOP", L"HaltSimulation", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"Exit_Simulation");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _hLAbooleanDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"START_STOP", L"Exit_Simulation", encodedSize, includeData, iter->second);
            }
            interaction->setExitSimulation(_hLAbooleanDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"START_STOP", L"Exit_Simulation", e.what(), includeData, iter->second);
        }
    }

    fireStartStop(false, interaction->build(producingFederate), hlaTimeStamp, logicalTime);
}

/*
 * Supporting impls for HlaLoadScenario interaction
 */

namespace LunarSimulation {
    class HlaLoadScenarioParametersImpl : public LunarSimulation::HlaLoadScenarioParameters {
    private:
       LunarSimulation::ParameterValue<double > _moonFriction;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _roverInitialPosition;
       LunarSimulation::ParameterValue<double > _roverHealth;
       LunarSimulation::ParameterValue<double > _roverMass;
       LunarSimulation::ParameterValue<double > _payloadMass;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _launchSpeedVector;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _roverStartPosition;
       LunarSimulation::ParameterValue<std::wstring > _simulationScenario;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _launcherPosition;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _launchForce;
       HlaFederateIdImplPtr _producingFederate;
       bool _isWithinInterest;
    public:
       HlaLoadScenarioParametersImpl(
          LunarSimulation::ParameterValue<double > moonFriction,
          LunarSimulation::ParameterValue<std::vector</* 3 */ double > > roverInitialPosition,
          LunarSimulation::ParameterValue<double > roverHealth,
          LunarSimulation::ParameterValue<double > roverMass,
          LunarSimulation::ParameterValue<double > payloadMass,
          LunarSimulation::ParameterValue<std::vector</* 3 */ double > > launchSpeedVector,
          LunarSimulation::ParameterValue<std::vector</* 3 */ double > > roverStartPosition,
          LunarSimulation::ParameterValue<std::wstring > simulationScenario,
          LunarSimulation::ParameterValue<std::vector</* 3 */ double > > launcherPosition,
          LunarSimulation::ParameterValue<std::vector</* 3 */ double > > launchForce,
          const HlaFederateIdImplPtr producingFederate,
          bool isWithinInterest
       ) :
          _moonFriction(moonFriction),
          _roverInitialPosition(roverInitialPosition),
          _roverHealth(roverHealth),
          _roverMass(roverMass),
          _payloadMass(payloadMass),
          _launchSpeedVector(launchSpeedVector),
          _roverStartPosition(roverStartPosition),
          _simulationScenario(simulationScenario),
          _launcherPosition(launcherPosition),
          _launchForce(launchForce),
          _producingFederate(producingFederate),
          _isWithinInterest(isWithinInterest)
       {}

       bool hasMoonFriction() {
          return _moonFriction.hasValue();
       }

       double getMoonFriction() THROW_SPEC (HlaValueNotSetException) {
          if (hasMoonFriction()) {
             return *_moonFriction.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'moonFriction' not set");
          }
       }

       double getMoonFriction(double defaultValue) {
          if (hasMoonFriction()) {
             return *_moonFriction.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasRoverInitialPosition() {
          return _roverInitialPosition.hasValue();
       }

       std::vector</* 3 */ double > getRoverInitialPosition() THROW_SPEC (HlaValueNotSetException) {
          if (hasRoverInitialPosition()) {
             return *_roverInitialPosition.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'roverInitialPosition' not set");
          }
       }

       std::vector</* 3 */ double > getRoverInitialPosition(std::vector</* 3 */ double > defaultValue) {
          if (hasRoverInitialPosition()) {
             return *_roverInitialPosition.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasRoverHealth() {
          return _roverHealth.hasValue();
       }

       double getRoverHealth() THROW_SPEC (HlaValueNotSetException) {
          if (hasRoverHealth()) {
             return *_roverHealth.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'roverHealth' not set");
          }
       }

       double getRoverHealth(double defaultValue) {
          if (hasRoverHealth()) {
             return *_roverHealth.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasRoverMass() {
          return _roverMass.hasValue();
       }

       double getRoverMass() THROW_SPEC (HlaValueNotSetException) {
          if (hasRoverMass()) {
             return *_roverMass.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'roverMass' not set");
          }
       }

       double getRoverMass(double defaultValue) {
          if (hasRoverMass()) {
             return *_roverMass.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasPayloadMass() {
          return _payloadMass.hasValue();
       }

       double getPayloadMass() THROW_SPEC (HlaValueNotSetException) {
          if (hasPayloadMass()) {
             return *_payloadMass.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'payloadMass' not set");
          }
       }

       double getPayloadMass(double defaultValue) {
          if (hasPayloadMass()) {
             return *_payloadMass.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasLaunchSpeedVector() {
          return _launchSpeedVector.hasValue();
       }

       std::vector</* 3 */ double > getLaunchSpeedVector() THROW_SPEC (HlaValueNotSetException) {
          if (hasLaunchSpeedVector()) {
             return *_launchSpeedVector.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'launchSpeedVector' not set");
          }
       }

       std::vector</* 3 */ double > getLaunchSpeedVector(std::vector</* 3 */ double > defaultValue) {
          if (hasLaunchSpeedVector()) {
             return *_launchSpeedVector.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasRoverStartPosition() {
          return _roverStartPosition.hasValue();
       }

       std::vector</* 3 */ double > getRoverStartPosition() THROW_SPEC (HlaValueNotSetException) {
          if (hasRoverStartPosition()) {
             return *_roverStartPosition.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'roverStartPosition' not set");
          }
       }

       std::vector</* 3 */ double > getRoverStartPosition(std::vector</* 3 */ double > defaultValue) {
          if (hasRoverStartPosition()) {
             return *_roverStartPosition.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasSimulationScenario() {
          return _simulationScenario.hasValue();
       }

       std::wstring getSimulationScenario() THROW_SPEC (HlaValueNotSetException) {
          if (hasSimulationScenario()) {
             return *_simulationScenario.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'simulationScenario' not set");
          }
       }

       std::wstring getSimulationScenario(std::wstring defaultValue) {
          if (hasSimulationScenario()) {
             return *_simulationScenario.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasLauncherPosition() {
          return _launcherPosition.hasValue();
       }

       std::vector</* 3 */ double > getLauncherPosition() THROW_SPEC (HlaValueNotSetException) {
          if (hasLauncherPosition()) {
             return *_launcherPosition.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'launcherPosition' not set");
          }
       }

       std::vector</* 3 */ double > getLauncherPosition(std::vector</* 3 */ double > defaultValue) {
          if (hasLauncherPosition()) {
             return *_launcherPosition.getValue();
          } else {
             return defaultValue;
          }
       }

       bool hasLaunchForce() {
          return _launchForce.hasValue();
       }

       std::vector</* 3 */ double > getLaunchForce() THROW_SPEC (HlaValueNotSetException) {
          if (hasLaunchForce()) {
             return *_launchForce.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'launchForce' not set");
          }
       }

       std::vector</* 3 */ double > getLaunchForce(std::vector</* 3 */ double > defaultValue) {
          if (hasLaunchForce()) {
             return *_launchForce.getValue();
          } else {
             return defaultValue;
          }
       }

       HlaFederateIdPtr getProducingFederate() const {
           return _producingFederate;
       }

       bool isWithinInterest() const {
           return _isWithinInterest;
       }
    };

    std::wostream & operator << (std::wostream &o, HlaLoadScenarioParameters &p) {
        o << L"<HlaLoadScenarioParameters:";
        if (p.hasMoonFriction()) {
           o << L" [" << "MoonFriction" << L":" << p.getMoonFriction() << L"]";
        }
        if (p.hasRoverInitialPosition()) {
           o << L" [" << "RoverInitialPosition" << L":" << p.getRoverInitialPosition() << L"]";
        }
        if (p.hasRoverHealth()) {
           o << L" [" << "RoverHealth" << L":" << p.getRoverHealth() << L"]";
        }
        if (p.hasRoverMass()) {
           o << L" [" << "RoverMass" << L":" << p.getRoverMass() << L"]";
        }
        if (p.hasPayloadMass()) {
           o << L" [" << "PayloadMass" << L":" << p.getPayloadMass() << L"]";
        }
        if (p.hasLaunchSpeedVector()) {
           o << L" [" << "LaunchSpeedVector" << L":" << p.getLaunchSpeedVector() << L"]";
        }
        if (p.hasRoverStartPosition()) {
           o << L" [" << "RoverStartPosition" << L":" << p.getRoverStartPosition() << L"]";
        }
        if (p.hasSimulationScenario()) {
           o << L" [" << "SimulationScenario" << L":" << StringUtil::towstring(p.getSimulationScenario()) << L"]";
        }
        if (p.hasLauncherPosition()) {
           o << L" [" << "LauncherPosition" << L":" << p.getLauncherPosition() << L"]";
        }
        if (p.hasLaunchForce()) {
           o << L" [" << "LaunchForce" << L":" << p.getLaunchForce() << L"]";
        }
        o << L">";
        return o;
    }

    std::ostream & operator << (std::ostream &o, HlaLoadScenarioParameters &p) {
        o << "<HlaLoadScenarioParameters:";
        if (p.hasMoonFriction()) {
           o << " [" << "MoonFriction" << ":" << p.getMoonFriction() << "]";
        }
        if (p.hasRoverInitialPosition()) {
           o << " [" << "RoverInitialPosition" << ":" << p.getRoverInitialPosition() << "]";
        }
        if (p.hasRoverHealth()) {
           o << " [" << "RoverHealth" << ":" << p.getRoverHealth() << "]";
        }
        if (p.hasRoverMass()) {
           o << " [" << "RoverMass" << ":" << p.getRoverMass() << "]";
        }
        if (p.hasPayloadMass()) {
           o << " [" << "PayloadMass" << ":" << p.getPayloadMass() << "]";
        }
        if (p.hasLaunchSpeedVector()) {
           o << " [" << "LaunchSpeedVector" << ":" << p.getLaunchSpeedVector() << "]";
        }
        if (p.hasRoverStartPosition()) {
           o << " [" << "RoverStartPosition" << ":" << p.getRoverStartPosition() << "]";
        }
        if (p.hasSimulationScenario()) {
           o << " [" << "SimulationScenario" << ":" << StringUtil::tostring(p.getSimulationScenario()) << "]";
        }
        if (p.hasLauncherPosition()) {
           o << " [" << "LauncherPosition" << ":" << p.getLauncherPosition() << "]";
        }
        if (p.hasLaunchForce()) {
           o << " [" << "LaunchForce" << ":" << p.getLaunchForce() << "]";
        }
        o << ">";
        return o;
    }

    class HlaLoadScenarioInteractionImpl : public LunarSimulation::HlaLoadScenarioInteraction {
    private:
       HlaInteractionManagerImpl* _outerThis;
       mutable std::recursive_mutex _lock;

       HlaLoadScenarioParametersPtr build() {
          return build(_outerThis->getFederateIdImpl());
       }
    public:
       LunarSimulation::ParameterValue<double > _moonFriction;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _roverInitialPosition;
       LunarSimulation::ParameterValue<double > _roverHealth;
       LunarSimulation::ParameterValue<double > _roverMass;
       LunarSimulation::ParameterValue<double > _payloadMass;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _launchSpeedVector;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _roverStartPosition;
       LunarSimulation::ParameterValue<std::wstring > _simulationScenario;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _launcherPosition;
       LunarSimulation::ParameterValue<std::vector</* 3 */ double > > _launchForce;
       explicit HlaLoadScenarioInteractionImpl(HlaInteractionManagerImpl* outerThis) : _outerThis(outerThis) {}

       HlaLoadScenarioParametersPtr build(const HlaFederateIdImplPtr producingFederate) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          return HlaLoadScenarioParametersPtr(new HlaLoadScenarioParametersImpl(
             _moonFriction,
             _roverInitialPosition,
             _roverHealth,
             _roverMass,
             _payloadMass,
             _launchSpeedVector,
             _roverStartPosition,
             _simulationScenario,
             _launcherPosition,
             _launchForce,
             producingFederate,
             true
          ));
       }

       void setMoonFriction(double moonFriction) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _moonFriction.setValue(std::shared_ptr<double >(new double(moonFriction)));
       }

       void setRoverInitialPosition(std::vector</* 3 */ double > roverInitialPosition) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _roverInitialPosition.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(roverInitialPosition)));
       }

       void setRoverHealth(double roverHealth) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _roverHealth.setValue(std::shared_ptr<double >(new double(roverHealth)));
       }

       void setRoverMass(double roverMass) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _roverMass.setValue(std::shared_ptr<double >(new double(roverMass)));
       }

       void setPayloadMass(double payloadMass) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _payloadMass.setValue(std::shared_ptr<double >(new double(payloadMass)));
       }

       void setLaunchSpeedVector(std::vector</* 3 */ double > launchSpeedVector) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _launchSpeedVector.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(launchSpeedVector)));
       }

       void setRoverStartPosition(std::vector</* 3 */ double > roverStartPosition) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _roverStartPosition.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(roverStartPosition)));
       }

       void setSimulationScenario(std::wstring simulationScenario) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _simulationScenario.setValue(std::shared_ptr<std::wstring >(new std::wstring(simulationScenario)));
       }

       void setLauncherPosition(std::vector</* 3 */ double > launcherPosition) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _launcherPosition.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(launcherPosition)));
       }

       void setLaunchForce(std::vector</* 3 */ double > launchForce) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _launchForce.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(launchForce)));
       }

       void sendInteraction() THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendLoadScenarioParams(build(), HlaTimeStampPtr());
       }

       void sendInteraction(HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendLoadScenarioParams(build(), timestamp);
       }

       void sendInteraction(HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendLoadScenarioParams(build(), HlaTimeStampPtr(), logicalTime);
       }

       void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendLoadScenarioParams(build(), timestamp, logicalTime);
       }
    };
}

HlaLoadScenarioInteractionPtr HlaInteractionManagerImpl::getHlaLoadScenarioInteraction() {
   HlaLoadScenarioInteraction* ptr = new HlaLoadScenarioInteractionImpl(this);
   return HlaLoadScenarioInteractionPtr(ptr);
}

void HlaInteractionManagerImpl::decodeAndFireLoadScenario(
    const RtiDriver::NameValueMap& parameters,
    const HlaFederateIdImplPtr producingFederate,
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {

    const bool verifyDataLength = _hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH;
    const bool includeData = _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION;

    RtiDriver::NameValueMap::const_iterator iter;
    HlaLoadScenarioInteractionImplPtr interaction(new HlaLoadScenarioInteractionImpl(this));
    iter = parameters.find(L"MoonFriction");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _hLAfloat64LEDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"MoonFriction", encodedSize, includeData, iter->second);
            }
            interaction->setMoonFriction(_hLAfloat64LEDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"MoonFriction", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"RoverInitialPosition");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _positionVectorEncoderDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"RoverInitialPosition", encodedSize, includeData, iter->second);
            }
            interaction->setRoverInitialPosition(_positionVectorEncoderDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"RoverInitialPosition", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"RoverHealth");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _hLAfloat64LEDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"RoverHealth", encodedSize, includeData, iter->second);
            }
            interaction->setRoverHealth(_hLAfloat64LEDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"RoverHealth", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"RoverMass");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _hLAfloat64LEDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"RoverMass", encodedSize, includeData, iter->second);
            }
            interaction->setRoverMass(_hLAfloat64LEDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"RoverMass", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"PayloadMass");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _hLAfloat64LEDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"PayloadMass", encodedSize, includeData, iter->second);
            }
            interaction->setPayloadMass(_hLAfloat64LEDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"PayloadMass", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"LaunchSpeedVector");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _velocityVectorEncoderDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"LaunchSpeedVector", encodedSize, includeData, iter->second);
            }
            interaction->setLaunchSpeedVector(_velocityVectorEncoderDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"LaunchSpeedVector", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"RoverStartPosition");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _positionVectorEncoderDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"RoverStartPosition", encodedSize, includeData, iter->second);
            }
            interaction->setRoverStartPosition(_positionVectorEncoderDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"RoverStartPosition", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"SimulationScenario");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _hLAunicodeStringDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"SimulationScenario", encodedSize, includeData, iter->second);
            }
            interaction->setSimulationScenario(_hLAunicodeStringDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"SimulationScenario", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"LauncherPosition");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _positionVectorEncoderDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"LauncherPosition", encodedSize, includeData, iter->second);
            }
            interaction->setLauncherPosition(_positionVectorEncoderDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"LauncherPosition", e.what(), includeData, iter->second);
        }
    }

    iter = parameters.find(L"LaunchForce");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _forceVectorEncoderDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"LOAD_SCENARIO", L"LaunchForce", encodedSize, includeData, iter->second);
            }
            interaction->setLaunchForce(_forceVectorEncoderDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"LOAD_SCENARIO", L"LaunchForce", e.what(), includeData, iter->second);
        }
    }

    fireLoadScenario(false, interaction->build(producingFederate), hlaTimeStamp, logicalTime);
}

/*
 * Supporting impls for HlaModeTransitionRequest interaction
 */

namespace LunarSimulation {
    class HlaModeTransitionRequestParametersImpl : public LunarSimulation::HlaModeTransitionRequestParameters {
    private:
       LunarSimulation::ParameterValue<MTRMode::MTRMode > _executionMode;
       HlaFederateIdImplPtr _producingFederate;
       bool _isWithinInterest;
    public:
       HlaModeTransitionRequestParametersImpl(
          LunarSimulation::ParameterValue<MTRMode::MTRMode > executionMode,
          const HlaFederateIdImplPtr producingFederate,
          bool isWithinInterest
       ) :
          _executionMode(executionMode),
          _producingFederate(producingFederate),
          _isWithinInterest(isWithinInterest)
       {}

       bool hasExecutionMode() {
          return _executionMode.hasValue();
       }

       MTRMode::MTRMode getExecutionMode() THROW_SPEC (HlaValueNotSetException) {
          if (hasExecutionMode()) {
             return *_executionMode.getValue();
          } else {
             throw HlaValueNotSetException("Parameter 'executionMode' not set");
          }
       }

       MTRMode::MTRMode getExecutionMode(MTRMode::MTRMode defaultValue) {
          if (hasExecutionMode()) {
             return *_executionMode.getValue();
          } else {
             return defaultValue;
          }
       }

       HlaFederateIdPtr getProducingFederate() const {
           return _producingFederate;
       }

       bool isWithinInterest() const {
           return _isWithinInterest;
       }
    };

    std::wostream & operator << (std::wostream &o, HlaModeTransitionRequestParameters &p) {
        o << L"<HlaModeTransitionRequestParameters:";
        if (p.hasExecutionMode()) {
           o << L" [" << "execution_mode" << L":" << p.getExecutionMode() << L"]";
        }
        o << L">";
        return o;
    }

    std::ostream & operator << (std::ostream &o, HlaModeTransitionRequestParameters &p) {
        o << "<HlaModeTransitionRequestParameters:";
        if (p.hasExecutionMode()) {
           o << " [" << "execution_mode" << ":" << p.getExecutionMode() << "]";
        }
        o << ">";
        return o;
    }

    class HlaModeTransitionRequestInteractionImpl : public LunarSimulation::HlaModeTransitionRequestInteraction {
    private:
       HlaInteractionManagerImpl* _outerThis;
       mutable std::recursive_mutex _lock;

       HlaModeTransitionRequestParametersPtr build() {
          return build(_outerThis->getFederateIdImpl());
       }
    public:
       LunarSimulation::ParameterValue<MTRMode::MTRMode > _executionMode;
       explicit HlaModeTransitionRequestInteractionImpl(HlaInteractionManagerImpl* outerThis) : _outerThis(outerThis) {}

       HlaModeTransitionRequestParametersPtr build(const HlaFederateIdImplPtr producingFederate) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          return HlaModeTransitionRequestParametersPtr(new HlaModeTransitionRequestParametersImpl(
             _executionMode,
             producingFederate,
             true
          ));
       }

       void setExecutionMode(MTRMode::MTRMode executionMode) {
          std::lock_guard<std::recursive_mutex> lock(_lock);
          _executionMode.setValue(std::shared_ptr<MTRMode::MTRMode >(new MTRMode::MTRMode(executionMode)));
       }

       void sendInteraction() THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendModeTransitionRequestParams(build(), HlaTimeStampPtr());
       }

       void sendInteraction(HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendModeTransitionRequestParams(build(), timestamp);
       }

       void sendInteraction(HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendModeTransitionRequestParams(build(), HlaTimeStampPtr(), logicalTime);
       }

       void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendModeTransitionRequestParams(build(), timestamp, logicalTime);
       }
    };
}

HlaModeTransitionRequestInteractionPtr HlaInteractionManagerImpl::getHlaModeTransitionRequestInteraction() {
   HlaModeTransitionRequestInteraction* ptr = new HlaModeTransitionRequestInteractionImpl(this);
   return HlaModeTransitionRequestInteractionPtr(ptr);
}

void HlaInteractionManagerImpl::decodeAndFireModeTransitionRequest(
    const RtiDriver::NameValueMap& parameters,
    const HlaFederateIdImplPtr producingFederate,
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {

    const bool verifyDataLength = _hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH;
    const bool includeData = _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION;

    RtiDriver::NameValueMap::const_iterator iter;
    HlaModeTransitionRequestInteractionImplPtr interaction(new HlaModeTransitionRequestInteractionImpl(this));
    iter = parameters.find(L"execution_mode");
    if (iter != parameters.end()) {
        try {
            const RtiDriver::VariableLengthData& data(iter->second);
            size_t encodedSize = _mTRModeEncoderDecoder.decodeFrom(data, 0);
            if (verifyDataLength && encodedSize != data.size()) {
                postLengthException(L"MODE_TRANSITION_REQUEST", L"execution_mode", encodedSize, includeData, iter->second);
            }
            interaction->setExecutionMode(_mTRModeEncoderDecoder);
        } catch (EncodingHelpers::EncoderException & e) {
            postDecodeException(L"MODE_TRANSITION_REQUEST", L"execution_mode", e.what(), includeData, iter->second);
        }
    }

    fireModeTransitionRequest(false, interaction->build(producingFederate), hlaTimeStamp, logicalTime);
}
