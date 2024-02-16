/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
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
    _enabled.insert(MODE_TRANSITION_REQUEST);
    _interactionNames.put(MODE_TRANSITION_REQUEST, MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME);

    _interactionManager->addManager(this, HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME);
    _interactionManager->addManager(this, START_STOP_INTERACTION_CLASS_NAME);
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
) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->sendInteraction();
}

void HlaInteractionManagerImpl::sendStartStop(
         HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->sendInteraction(timeStamp);
}

void HlaInteractionManagerImpl::sendStartStop(
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->sendInteraction(logicalTime);
}

void HlaInteractionManagerImpl::sendStartStop(
         HlaTimeStampPtr timeStamp,
         HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   HlaStartStopInteractionPtr interaction = getHlaStartStopInteraction();
   interaction->sendInteraction(timeStamp, logicalTime);
}

void HlaInteractionManagerImpl::sendStartStopParams(
   HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   try {
       sendStartStopParams(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException&) {
       //Could not happen
   }
}

void HlaInteractionManagerImpl::sendStartStopParams(
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
    _interactionManager->sendInteraction(*handle, nameValueMap, timeStamp, logicalTime);

    fireStartStop(
        true,
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
            fireStartStop(false, timeStamp, logicalTime);
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
    HlaTimeStampPtr hlaTimeStamp,
    HlaLogicalTimePtr logicalTime) {
    std::set<HlaInteractionListenerPtr> listeners = _interactionListeners.getListeners();
    for (std::set<HlaInteractionListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaInteractionListener::startStop, *it, local, hlaTimeStamp, logicalTime);
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
    class HlaStartStopInteractionImpl : public LunarSimulation::HlaStartStopInteraction {
    private:
       HlaInteractionManagerImpl* _outerThis;
    public:
       explicit HlaStartStopInteractionImpl(HlaInteractionManagerImpl* outerThis) : _outerThis(outerThis) {}

       void sendInteraction() THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(HlaTimeStampPtr());
       }

       void sendInteraction(HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(timestamp);
       }

       void sendInteraction(HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(HlaTimeStampPtr(), logicalTime);
       }

       void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
          _outerThis->sendStartStopParams(timestamp, logicalTime);
       }
    };
}

HlaStartStopInteractionPtr HlaInteractionManagerImpl::getHlaStartStopInteraction() {
   HlaStartStopInteraction* ptr = new HlaStartStopInteractionImpl(this);
   return HlaStartStopInteractionPtr(ptr);
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
