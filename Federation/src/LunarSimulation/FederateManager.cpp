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

#include "FederateManager.h"

#include <RtiDriver/Exception.h>
#include <RtiDriver/InteractionClassHandle.h>
#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaSettings.h>
#include <LunarSimulation/HlaTuning.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include "HlaWorldImpl.h"
#include "StringUtil.h"
#include "HlaFederateIdImpl.h"
#include "HlaLogicalTimeImpl.h"

#include <cmath>

using namespace LunarSimulation;

FederateManager::FederateManager(HlaWorldImpl* hlaWorld) :
    _hlaWorld(hlaWorld),
    _ddmListener(NULL),
    _nameReservationSucceeded(false),
    _nameReservationCompleted(false),
    _restoreRequestSucceeded(false),
    _restoreRequestCompleted(false),
    _expectingGrantAfterRestore(false),
    _handleDisconnectDetected(false),
    _timeConstrained(false),
    _timeRegulating(false),
    _granted(true)
{}

FederateManager::~FederateManager()
{}

template <typename T> void FederateManager::disconnectRtiAndThrow(const T& exception) {
    try {
        _rtiAmbassador->disconnect();
    } catch (HlaException&) {
    }
    throw exception;
}

template <typename T> void FederateManager::disconnectAndThrow(bool destroyFederationOnDisconnect, const T& exception) {
    try {
        disconnect(destroyFederationOnDisconnect);
    } catch (HlaException&) {
    }
    throw exception;
}

static RtiDriver::NameRegionsMap mapWithSameValueForAllKeys(const RtiDriver::NameSet& keys, const RtiDriver::RegionSet& value) {
    RtiDriver::NameRegionsMap map;
    for (RtiDriver::NameSet::const_iterator iter = keys.begin(); iter != keys.end(); iter++) {
        map[*iter] = value;
    }
    return map;
}

static RtiDriver::RegionSet makeRegionSet(const RtiDriver::Region& value) {
    RtiDriver::RegionSet regions;
    regions.insert(const_cast<RtiDriver::Region*>(&value));
    return regions;
}

static RtiDriver::RegionSet makeRegionSet(const std::vector<RegionPtr>& value) {
    RtiDriver::RegionSet regions;
    for (std::vector<RegionPtr>::const_iterator iter = value.begin(); iter != value.end(); iter++) {
        regions.insert((*iter).get());
    }
    return regions;
}

void FederateManager::connectionLost(const std::wstring& faultDescription) {
    try {
       _hlaWorld->disconnect(faultDescription.size() == 0 ? L"<unknown>" : faultDescription);
    } catch (HlaException&) {
       //do nothing
    }
}

void FederateManager::setSaveRestManager(SaveRestManager* saveRestManager) {
   _saveRestManager = saveRestManager;
}


void FederateManager::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag) {
    try {
        _objectManager->removeObjectInstance(objectInstanceHandle, _timeStampFactory->create(userSuppliedTag), HlaLogicalTimeImpl::getInvalid());
    } catch (std::exception &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Unhandled exception in FederateAmbassador removeObjectInstance callback: " + StringUtil::convert(e.what())));
        _hlaWorld->postException(ex);
    }
}

void FederateManager::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag,
                                           const RtiDriver::FederateHandle& producingFederate) {
    //ignore producingFederate
    removeObjectInstance(objectInstanceHandle, userSuppliedTag);
}

void FederateManager::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType) {
    try {
        _objectManager->removeObjectInstance(objectInstanceHandle, _timeStampFactory->create(userSuppliedTag), HlaLogicalTimeImpl::createReceived(theTime.integer64, orderType == RtiDriver::TIMESTAMP));
    } catch (std::exception &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Unhandled exception in FederateAmbassador removeObjectInstance callback: " + StringUtil::convert(e.what())));
        _hlaWorld->postException(ex);
    }
}

void FederateManager::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType,
                                           const RtiDriver::FederateHandle& producingFederate) {
    //ignore producingFederate
    removeObjectInstance(objectInstanceHandle, userSuppliedTag,theTime, orderType);
}

void FederateManager::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                                  const RtiDriver::NameSet& attributeHandleSet,
                                                  const RtiDriver::VariableLengthData& userSuppliedTag)
{
    if (_hlaWorld->getTuning()->PROVIDE) {
        struct ValueUpdate {
            static void run(HlaWorldImpl* hlaWorld,
                            ObjectManager* objectManager,
                            ObjectInstanceHandlePtr objectInstanceHandle,
                            RtiDriver::NameSet attributeHandleSet,
                            HlaTimeStampPtr timeStamp) {
                try {
                    objectManager->provideAttributeValueUpdate(*objectInstanceHandle, attributeHandleSet, timeStamp);
                } catch (std::exception &e) {
                    HlaExceptionPtr ex(new HlaInternalException(L"Unhandled exception in FederateAmbassador provideAttributeValueUpdate callback: " + StringUtil::convert(e.what())));
                    hlaWorld->postException(ex);
                }
            }
        };
        HlaTimeStampPtr hlaTimeStampPtr = _timeStampFactory->create(userSuppliedTag);

        std::function<void()> callback = std::bind(&ValueUpdate::run, _hlaWorld,
            _objectManager, ObjectInstanceHandlePtr(objectInstanceHandle.clone()), attributeHandleSet, hlaTimeStampPtr);
        _hlaWorld->invokeLater(callback);
    }
}

void FederateManager::init(RtiInteractionManager* interactionManager, ObjectManager* objectManager, HlaTimeStampFactoryPtr timeStampFactory)
{
    _interactionManager = interactionManager;
    _objectManager = objectManager;
    _timeStampFactory = timeStampFactory;
}

HlaSettings::HlaVersion FederateManager::getHlaVersion() {
   switch (_rtiAmbassador->getHLAversion()) {
      case RtiDriver::HLA_13:           return HlaSettings::HLA_13;
      case RtiDriver::HLA_EVOLVED:      return HlaSettings::HLA_EVOLVED;
      case RtiDriver::HLA_4:            return HlaSettings::HLA_4;
      case RtiDriver::HLA_VERSION_NONE: return HlaSettings::HLA_VERSION_NONE;

      default:
      case RtiDriver::HLA_1516:         return HlaSettings::HLA_1516;
   }
}

RtiDriver::Profile FederateManager::getRtiDriverProfile(const std::wstring& str) {
    if (L"A" == str) {
        return RtiDriver::A;
    } else if (L"B" == str) {
        return RtiDriver::B;
    } else if (L"C" == str) {
        return RtiDriver::C;
    } else if (L"D" == str) {
        return RtiDriver::D;
    } else if (L"E" == str) {
        return RtiDriver::E;
    } else if (L"F" == str) {
        return RtiDriver::F;
    }

    return RtiDriver::UNSPECIFIED;
}

std::wstring FederateManager::getRtiDriverProfileStr(const RtiDriver::Profile& profile, const std::wstring& localSettingsDesignator,
                                                     const std::wstring& crcHost, const std::wstring& crcPort) {
    switch (profile) {
        case RtiDriver::A: return L"Profile A (HLA 1516-2000), CRC Host " + crcHost + L":" + crcPort;
        case RtiDriver::B: {
           if (localSettingsDesignator.empty() && !crcHost.empty()) {
              return L"Profile B (HLA 1516-2010 Evolved), CRC Host " + crcHost + L":" + crcPort;
           } else {
              return L"Profile B (HLA 1516-2010 Evolved), LSD '" + localSettingsDesignator + L"'";
           }
        }
        case RtiDriver::C: return L"Profile C (HLA 1.3), CRC Host " + crcHost + L":" + crcPort;
        case RtiDriver::D: return L"Profile D (HLA 1516 DLC)";
        case RtiDriver::E: {
           if (localSettingsDesignator.empty() && !crcHost.empty()) {
              return L"Profile E (DIS), " + crcHost + L":" + crcPort;
           } else {
              return L"Profile E (DIS), '" + localSettingsDesignator + L"'";
           }
        }
        case RtiDriver::F: {
           if (localSettingsDesignator.empty() && !crcHost.empty()) {
              return L"Profile F (HLA 1516-202X, version 4), CRC Host " + crcHost + L":" + crcPort;
           } else {
              return L"Profile F (HLA 1516-202X, version 4), LSD '" + localSettingsDesignator + L"'";
           }
        }

        default:
        case RtiDriver::UNSPECIFIED: return L"Profile ANY, LSD '" + localSettingsDesignator + L"', CRC Host " + crcHost + L":" + crcPort;
    }
}

HlaLogicalTimePtr FederateManager::connect(HlaSettingsPtr settings)
THROW_SPEC (HlaConnectException, HlaInvalidLicenseException, HlaFomException, HlaRtiException,
            HlaInternalException, HlaNotConnectedException, HlaInvalidLogicalTimeException,
            HlaSaveInProgressException, HlaRestoreInProgressException, HlaNormalizerException) {

    bool useTimeManagement = settings->getTimeRegulating() || settings->getTimeConstrained();
    std::wstring host = settings->getCrcHost();
    int port = settings->getCrcPort();
    std::wstring profileStr = settings->getRtiDriverProfile();
    std::wstring localSettingsDesignator = settings->getLocalSettingsDesignator();
    RtiDriver::Profile profile = getRtiDriverProfile(profileStr);
    bool destroyFederationOnDisconnect = settings->getDestroyFederation();
    try {
        RtiDriver::RtiAmbassador* rtiAmbassador = RtiDriver::getRtiAmbassador(profile, localSettingsDesignator, host, port);

        // Limit the number of detectives if the settings are broken and
        // throw an exception if a NULL detective isn't received.
        bool gotNullDetective = false;
        for (int i = 1; i < 100; ++i) {
            std::unique_ptr<RtiDriver::Detective> detective = settings->getRtiDriverDetective(i);
            if (detective.get() == NULL) {
                gotNullDetective = true;
                break;
            }
            rtiAmbassador = RtiDriver::installDetective(detective.release(), rtiAmbassador);
        }

        if (!gotNullDetective) {
            throw HlaInternalException(L"Expected NULL to signal end of Detectives from HlaSettings::getRtiDriverDetective()");
        }

        _rtiAmbassador = std::unique_ptr<RtiDriver::RtiAmbassador>(rtiAmbassador);
    } catch (RtiDriver::InvalidLicense& e) {
        throw HlaInvalidLicenseException(L"Invalid RTI Driver License: " + e.what());
    } catch (RtiDriver::ConnectionFailed& e) {
        throw HlaConnectException(L"Unable to connect to CRC. " +
                                        getRtiDriverProfileStr(profile, localSettingsDesignator, host, StringUtil::intToWstring(port)) +
                                        L": " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaConnectException(L"Unable to connect to CRC. " +
                                        getRtiDriverProfileStr(profile, localSettingsDesignator, host, StringUtil::intToWstring(port)) +
                                        L": " + e.what());
    }

    if (_rtiAmbassador.get() == NULL) {
        throw HlaConnectException("Unable to get RTI ambassador from RtiDriver");
    }

    std::wstring timeRepresentation = useTimeManagement ||
                                      _hlaWorld->getTuning()->CREATE_FEDERATION_WITH_TIME_REPRESENTATION ||
                                      _hlaWorld->getTuning()->ALWAYS_USE_LOGICAL_TIME ?
                                      L"HLAinteger64Time" : L"";

    if (settings->getCreateFederation()) {
        try {
            _rtiAmbassador->createFederationExecution(settings->getFederationName(),
                                                      settings->getFomUrl(HlaSettings::CREATE, getHlaVersion()),
                                                      settings->getAdditionalFomUrls(HlaSettings::CREATE, getHlaVersion()),
                                                      timeRepresentation);
        } catch (RtiDriver::FederationExecutionAlreadyExists) {
            //Ignoring this exception
        } catch (RtiDriver::CouldNotOpenFDD& e) {
            disconnectRtiAndThrow(HlaFomException(L"Failed to create federation: " + e.what()));
        } catch (RtiDriver::ErrorReadingFDD& e) {
            disconnectRtiAndThrow(HlaFomException(L"Failed to create federation: " + e.what()));
        } catch (RtiDriver::RTIinternalError& e) {
            disconnectRtiAndThrow(HlaInternalException(L"Failed to create federation: " + e.what()));
        } catch (RtiDriver::NotConnected& e) {
            disconnectRtiAndThrow(HlaConnectException(L"Failed to create federation: " + e.what()));
        }
    }

    _federationName = settings->getFederationName();
    try {
        std::vector<std::wstring> fomModules = settings->getAdditionalFomUrls(HlaSettings::JOIN, getHlaVersion());
        std::wstring baseFom = settings->getFomUrl(HlaSettings::JOIN, getHlaVersion());
        if (!baseFom.empty()) {
            fomModules.push_back(baseFom);
        }

        _federateHandle = std::unique_ptr<RtiDriver::FederateHandle>(_rtiAmbassador->joinFederationExecution(settings->getFederateName(),
            settings->getFederateType(), _federationName, this, fomModules, timeRepresentation));
        _federateId = HlaFederateIdImplPtr(new HlaFederateIdImpl(*_federateHandle));
    } catch (RtiDriver::FederateAlreadyExecutionMember) {
        //Ignoring this exception
    } catch (RtiDriver::FederationExecutionDoesNotExist& e) {
        disconnectRtiAndThrow(HlaRtiException(L"Failed to join federation " + _federationName + L"; " + e.what()));
    } catch (RtiDriver::ErrorReadingFDD& e) {
        disconnectRtiAndThrow(HlaFomException(L"Failed to join federation " + _federationName + L"; " + e.what()));
    } catch (RtiDriver::CouldNotOpenFDD& e) {
        disconnectRtiAndThrow(HlaFomException(L"Failed to join federation " + _federationName + L"; " + e.what()));
    } catch (RtiDriver::SaveInProgress& e) {
        disconnectRtiAndThrow(HlaSaveInProgressException(L"Failed to join federation " + _federationName + L"; " + e.what()));
    } catch (RtiDriver::RestoreInProgress& e) {
        disconnectRtiAndThrow(HlaRestoreInProgressException(L"Failed to join federation " + _federationName + L"; " + e.what()));
    } catch (RtiDriver::NotConnected& e) {
        disconnectRtiAndThrow(HlaRtiException(L"Failed to join federation " + _federationName +L"; " + e.what()));
    } catch (RtiDriver::RTIinternalError& e) {
        disconnectRtiAndThrow(HlaInternalException(L"Failed to join federation " + _federationName + L"; " + e.what()));
    }

    bool useDdm = false;
    try {
        RtiDriver::HlaVersion hlaVersion = _rtiAmbassador->getHLAversion();
        if (_ddmListener != NULL) {
            useDdm = _ddmListener->connected(hlaVersion);
        }
    } catch (HlaFomException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaRtiException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaNormalizerException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaInternalException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaSaveInProgressException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaRestoreInProgressException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaNotConnectedException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    }

    if (useDdm) {
        try {
            _rtiAmbassador->setAttributeScopeAdvisorySwitch(true);
        } catch (RtiDriver::SaveInProgress& e) {
            disconnectRtiAndThrow(HlaSaveInProgressException(L"Failed to enable attribute scope advisory switch when joining federation " + _federationName + L"; " + e.what()));
        } catch (RtiDriver::RestoreInProgress& e) {
            disconnectRtiAndThrow(HlaRestoreInProgressException(L"Failed to enable attribute scope advisory switch when joining federation " + _federationName + L"; " + e.what()));
        } catch (RtiDriver::RTIinternalError& e) {
            disconnectRtiAndThrow(HlaInternalException(L"Failed to enable attribute scope advisory switch when joining federation " + _federationName + L"; " + e.what()));

        } catch (RtiDriver::FederateNotExecutionMember& e) {
            disconnectRtiAndThrow(HlaRtiException(L"Failed to enable attribute scope advisory switch when joining federation " + _federationName +L"; " + e.what()));
        } catch (RtiDriver::NotConnected& e) {
            disconnectRtiAndThrow(HlaRtiException(L"Failed to enable attribute scope advisory switch when joining federation " + _federationName +L"; " + e.what()));
        }
    }

    if (_rtiAmbassador->getHLAversion() == RtiDriver::HLA_EVOLVED && _hlaWorld->getTuning()->CONVEY_PRODUCING_FEDERATE) {
        try {
            std::unique_ptr<RtiDriver::InteractionClassHandle> handle = std::unique_ptr<RtiDriver::InteractionClassHandle>(_rtiAmbassador->getInteractionClassHandle(L"HLAmanager.HLAfederate.HLAadjust.HLAsetSwitches"));
            _rtiAmbassador->publishInteractionClass(*handle);

            std::vector<char> variableArray(4, 0);
            std::vector<char> fedHandle = _federateHandle->getEncodedHandle();
            variableArray[3] = static_cast<char>(fedHandle.size());
            variableArray.insert(variableArray.end(), fedHandle.begin(), fedHandle.end());

            std::vector<char> hlaSwitchTrue(4, 0);
            hlaSwitchTrue[3] = 1;

            RtiDriver::NameValueMap parameters;
            parameters.insert(std::pair<std::wstring, std::vector<char> >(L"HLAfederate", variableArray));
            parameters.insert(std::pair<std::wstring, std::vector<char> >(L"HLAconveyProducingFederate", hlaSwitchTrue));

            _rtiAmbassador->sendInteraction(*handle, parameters, _hlaWorld->getCurrentTime()->getUserSuppliedTag());
        } catch (RtiDriver::BaseException& e) {
            disconnectAndThrow(destroyFederationOnDisconnect, HlaInternalException(L"Failed to send Enable Convey Producing Federate interaction " + e.what()));
        }
    }

    try {
        _interactionManager->connected();
        _objectManager->connected();
        _saveRestManager->connected();
    } catch (HlaFomException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaRtiException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaInternalException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaSaveInProgressException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaRestoreInProgressException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    } catch (HlaNotConnectedException& e) {
        disconnectAndThrow(destroyFederationOnDisconnect, e);
    }

    _timeConstrained = false;
    _timeRegulating = false;
    _expectingGrantAfterRestore = false;

    HlaLogicalTimePtr logicalTime = HlaLogicalTimeImpl::getInvalid();

    if (useTimeManagement && _hlaWorld->getTuning()->ENABLE_TIME_MANAGEMENT_ON_CONNECT) {
        logicalTime = enableTimeManagement(settings->getTimeRegulating(), settings->getTimeConstrained(), destroyFederationOnDisconnect, true);
    }
    _handleDisconnectDetected = true;

    return logicalTime;
}

HlaLogicalTimePtr FederateManager::enableTimeManagement(bool regulating, bool constrained, bool destroyFederationOnDisconnect, bool onJoin)
    THROW_SPEC (HlaInternalException, HlaInvalidLogicalTimeException, HlaRtiException, HlaNotConnectedException) {
    std::wstring exceptionMessage = L"Failed to enable time management when joining federation " + _federationName + L" ";
    try {
        if (_hlaWorld->getTuning()->ENABLE_ASYNCHRONOUS_DELIVERY) {
            _rtiAmbassador->enableAsynchronousDelivery();
        }

        if (constrained) {
            std::unique_lock<std::mutex> lock(_timeConstrainedSemaphore);
            if (!_rtiAmbassador->enableTimeConstrained()) {
                disconnectAndThrow(destroyFederationOnDisconnect, HlaRtiException(L"Failed to enable time management when joining federation " + _federationName + L". Not supported!"));
            }

            while (!_timeConstrained) {
                _timeConstrainedEnabled.wait(lock);
            }
            if (!_timeValid) {
                disconnectAndThrow(destroyFederationOnDisconnect, HlaRtiException(L"Failed to enable time management when joining federation " + _federationName + L". Wrong time representation!"));
            }
        }

        if (regulating) {
            std::unique_lock<std::mutex> lock(_timeRegulationSemaphore);
            if (!_rtiAmbassador->enableTimeRegulation(_hlaWorld->getLookahead())) {
                disconnectAndThrow(destroyFederationOnDisconnect, HlaRtiException(L"Failed to enable time management when joining federation " + _federationName + L". Not supported!"));
            }

            while (!_timeRegulating) {
                _timeRegulationEnabled.wait(lock);
            }
            if (!_timeValid) {
                disconnectAndThrow(destroyFederationOnDisconnect, HlaRtiException(L"Failed to enable time management when joining federation " + _federationName + L". Wrong time representation!"));
            }
        } else if (_hlaWorld->getTuning()->INITIAL_ADVANCE_WHEN_CONSTRAINED) {
            // keep up with other regulating federates
            RtiDriver::LogicalTime galt(static_cast<long long>(0));
            bool validGalt = _rtiAmbassador->queryGALT(galt);
            if (validGalt && galt.integer64 != _currentTime) {
                long long newTime = galt.integer64 - _hlaWorld->getStepSize();
                if (newTime > 0) {
                    timeAdvanceRequest(HlaLogicalTimeImpl::create(newTime));
                }
            }
        }

        if (_hlaWorld->getTuning()->INITIAL_ADVANCE_TO_EVEN_STEP_SIZE) {
            // start at time dividable with the step size
            long long diff = _currentTime % _hlaWorld->getStepSize();
            if (diff != 0) {
                timeAdvanceRequest(HlaLogicalTimeImpl::create(_currentTime + diff));
            }
        }

        return HlaLogicalTimeImpl::create(_currentTime);
    } catch (RtiDriver::InTimeAdvancingState& e) {
        throwException(destroyFederationOnDisconnect, HlaInternalException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::RequestForTimeRegulationPending& e) {
        throwException(destroyFederationOnDisconnect, HlaInternalException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::TimeRegulationAlreadyEnabled& e) {
        throwException(destroyFederationOnDisconnect, HlaInternalException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::TimeConstrainedAlreadyEnabled& e) {
        throwException(destroyFederationOnDisconnect, HlaInternalException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::SaveInProgress& e) {
        throwException(destroyFederationOnDisconnect, HlaSaveInProgressException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::RestoreInProgress& e) {
        throwException(destroyFederationOnDisconnect, HlaRestoreInProgressException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::RTIinternalError& e) {
        throwException(destroyFederationOnDisconnect, HlaRtiException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        throwException(destroyFederationOnDisconnect, HlaNotConnectedException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::NotConnected& e) {
        throwException(destroyFederationOnDisconnect, HlaNotConnectedException(exceptionMessage + e.what()), onJoin);
    } catch (RtiDriver::InvalidLookahead& e) {
        throwException(destroyFederationOnDisconnect, HlaInvalidLogicalTimeException(exceptionMessage + e.what()), onJoin);
    }
    return HlaLogicalTimeImpl::getInvalid();
}

template <typename T> void FederateManager::throwException(bool destroyFederationOnDisconnect, const T& exception, bool onJoin)
{
    if (onJoin) {
        disconnectAndThrow(destroyFederationOnDisconnect, exception);
    } else {
        throw exception;
    }
}

RtiDriver::ResignAction FederateManager::getResignAction(int resignAction) {
   switch (resignAction) {
      case 0: return RtiDriver::UNCONDITIONALLY_DIVEST_ATTRIBUTES;
      case 1: return RtiDriver::DELETE_OBJECTS;
      case 2: return RtiDriver::CANCEL_PENDING_OWNERSHIP_ACQUISITIONS;
      case 3: return RtiDriver::DELETE_OBJECTS_THEN_DIVEST;
      case 4: return RtiDriver::CANCEL_THEN_DELETE_THEN_DIVEST;
      case 5: return RtiDriver::NO_ACTION;

      default: return RtiDriver::CANCEL_THEN_DELETE_THEN_DIVEST;
   }
}

void FederateManager::disconnect(bool destroyFederationOnDisconnect)
THROW_SPEC (HlaFederateOwnsAttributeException, HlaRtiException, HlaInternalException) {
    _handleDisconnectDetected = false;
    try {
        _rtiAmbassador->resignFederationExecution(getResignAction(_hlaWorld->getTuning()->RESIGN_ACTION));
    } catch (RtiDriver::FederateNotExecutionMember&) {
        //do nothing
    } catch (RtiDriver::NotConnected&) {
        //do nothing
    } catch (RtiDriver::FederateOwnsAttributes& e) {
        _handleDisconnectDetected = true;
        throw HlaFederateOwnsAttributeException(L"Failed to resign: " + e.what());
    } catch (RtiDriver::OwnershipAcquisitionPending &e) {
        _handleDisconnectDetected = true;
        throw HlaFederateOwnsAttributeException(L"Failed to resign: " + e.what());
    } catch (RtiDriver::RTIinternalError&) {
        //ignore and disconnect anyway
    }

    if (destroyFederationOnDisconnect) {
        try {
            _rtiAmbassador->destroyFederationExecution(_federationName);
        } catch (RtiDriver::FederationExecutionDoesNotExist) {
            //Ignoring this exception
        } catch (RtiDriver::NotConnected&) {
            //Ignoring this exception
        } catch (RtiDriver::FederatesCurrentlyJoined) {
            //Ignoring this exception
        } catch (RtiDriver::RTIinternalError&) {
            //ignore and disconnect anyway
        }
    }

    try {
        _rtiAmbassador->disconnect();
    } catch (RtiDriver::FederateIsExecutionMember&) {
        //ignore and disconnect anyway
    } catch (RtiDriver::RTIinternalError&) {
        //ignore and disconnect anyway
    }

    disconnected();
}

std::vector<char> FederateManager::getEncodedHlaFederateHandle() {
    return _federateHandle->getEncodedHandle();
}

HlaFederateIdImplPtr FederateManager::getFederateIdImpl() {
    return HlaFederateIdImplPtr(_federateId);
}

void FederateManager::disconnectDetected() {
    if (_handleDisconnectDetected) {
       _handleDisconnectDetected = false;
       try {
          _hlaWorld->disconnect(L"");
       } catch (HlaException&) {
          //do nothing
       }
    }
}

void FederateManager::disconnected() {
    _objectManager->disconnect();
    _interactionManager->disconnect();
    _saveRestManager->disconnect();

    if (_ddmListener != NULL) {
        _ddmListener->disconnected();
    }
}

void FederateManager::publishInteractionClass(const RtiDriver::InteractionClassHandle& interactionClassHandle)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        _rtiAmbassador->publishInteractionClass(interactionClassHandle);
    } catch(RtiDriver::InteractionClassNotDefined& e) {
        throw HlaInternalException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());

    } catch(RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());

    } catch(RtiDriver::NotConnected &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::RTIinternalError &e) {
        throw HlaRtiException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    }
}

void FederateManager::subscribeInteractionClass(const RtiDriver::InteractionClassHandle& interactionClassHandle)
THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        _rtiAmbassador->subscribeInteractionClass(interactionClassHandle);
    } catch(RtiDriver::InteractionClassNotDefined& e) {
        throw HlaInternalException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::FederateServiceInvocationsAreBeingReportedViaMOM& e) {
        throw HlaInternalException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());

    } catch(RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());

    } catch(RtiDriver::NotConnected &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::RTIinternalError &e) {
        throw HlaRtiException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    }
}

void FederateManager::subscribeInteractionClass(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RegionSetPtr& newRegions, const RegionSetPtr& oldRegions)
THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        if (newRegions) {
            _rtiAmbassador->subscribeInteractionClassWithRegions(interactionClassHandle, makeRegionSet(*newRegions));
        }
        if (oldRegions) {
            _rtiAmbassador->unsubscribeInteractionClassWithRegions(interactionClassHandle, makeRegionSet(*oldRegions));
        }
    } catch(RtiDriver::InteractionClassNotDefined& e) {
        throw HlaInternalException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::InvalidRegion& e) {
        throw HlaInternalException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::InvalidRegionContext& e) {
        throw HlaInternalException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::FederateServiceInvocationsAreBeingReportedViaMOM& e) {
        throw HlaInternalException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());

    } catch(RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());

    } catch(RtiDriver::NotConnected &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    } catch(RtiDriver::RTIinternalError &e) {
        throw HlaRtiException(L"Failed to publish interaction class (" + (const std::wstring &)interactionClassHandle + L") " + e.what());
    }
}

bool FederateManager::registerObjectInstanceName(const std::wstring& instanceName)
THROW_SPEC (HlaIllegalInstanceNameException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    std::unique_lock<std::mutex> lock(_nameReservationSemaphore);
    try {
        _nameReservationCompleted = false;
        bool reserveNameSupported = _rtiAmbassador->reserveObjectInstanceName(instanceName);
        if (reserveNameSupported) {
            while (!_nameReservationCompleted) {
                // Wait for response from RTI
                _nameReservationCondition.wait(lock);
            }
        }

        return !reserveNameSupported || _nameReservationSucceeded;
    } catch (RtiDriver::IllegalName& e) {
        throw HlaIllegalInstanceNameException(L"Failed to register object instance name " + instanceName + L": " + e.what());
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to register object instance name " + instanceName + L": " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to register object instance name " + instanceName + L": " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to register object instance name " + instanceName + L": " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to register object instance name " + instanceName + L": " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to register object instance name " + instanceName + L": " + e.what());
    }
}

InteractionClassHandlePtr FederateManager::getInteractionClassHandle(const std::wstring& interactionClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaRtiException) {
    try {
        return InteractionClassHandlePtr(_rtiAmbassador->getInteractionClassHandle(interactionClassName));
    } catch(RtiDriver::NameNotFound& e) {
        throw HlaFomException(L"Failed to get interaction class handle (" + interactionClassName + L") " + e.what());
    } catch(RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to get interaction class handle (" + interactionClassName + L") " + e.what());
    } catch(RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to get interaction class handle (" + interactionClassName + L") " + e.what());
    } catch(RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to get interaction class handle (" + interactionClassName + L") " + e.what());
    }
}

ObjectClassHandlePtr FederateManager::getObjectClassHandle(const std::wstring& objectClassName)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException) {
    try {
        return ObjectClassHandlePtr(_rtiAmbassador->getObjectClassHandle(objectClassName));
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to get object class handle " + objectClassName + L": " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to get object class handle " + objectClassName + L": " + e.what());

    } catch (RtiDriver::NameNotFound& e) {
        throw HlaFomException(L"Failed to get object class handle " + objectClassName + L": " + e.what());

    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to get object class handle " + objectClassName + L": " + e.what());
    }
}

void FederateManager::publishObjectClassAttributes(const RtiDriver::ObjectClassHandle& objectClassHandle, const RtiDriver::NameSet& attributeNames)
THROW_SPEC (HlaRtiException, HlaFomException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        _rtiAmbassador->publishObjectClassAttributes(objectClassHandle, attributeNames);
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::OwnershipAcquisitionPending& e) {
        throw HlaRtiException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::NameNotFound& e) {
        throw HlaFomException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::ObjectClassNotDefined& e) {
        throw HlaInternalException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::AttributeNotDefined& e) {
        throw HlaInternalException(L"Failed to publish object class: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to publish object class: " + e.what());
    }
}

void FederateManager::subscribeObjectClassAttributes(const RtiDriver::ObjectClassHandle& objectClassHandle, const RtiDriver::NameSet& attributeNames)
THROW_SPEC (HlaRtiException, HlaFomException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        _rtiAmbassador->subscribeObjectClassAttributes(objectClassHandle, attributeNames);
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::NameNotFound& e) {
        throw HlaFomException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::ObjectClassNotDefined& e) {
        throw HlaInternalException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::AttributeNotDefined& e) {
        throw HlaInternalException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to subscribe to object class: " + e.what());
    }
}

void FederateManager::subscribeObjectClassAttributes(const RtiDriver::ObjectClassHandle& objectClassHandle, const RtiDriver::NameSet& attributeNames, const RegionSetPtr& newRegions, const RegionSetPtr& oldRegions)
THROW_SPEC (HlaRtiException, HlaFomException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        if (newRegions) {
            RtiDriver::NameRegionsMap regions = mapWithSameValueForAllKeys(attributeNames, makeRegionSet(*newRegions));
            _rtiAmbassador->subscribeObjectClassAttributesWithRegions(objectClassHandle, regions);
        }
        if (oldRegions) {
            RtiDriver::NameRegionsMap regions = mapWithSameValueForAllKeys(attributeNames, makeRegionSet(*oldRegions));
            _rtiAmbassador->unsubscribeObjectClassAttributesWithRegions(objectClassHandle, regions);
        }
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::NameNotFound& e) {
        throw HlaFomException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::ObjectClassNotDefined& e) {
        throw HlaInternalException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::AttributeNotDefined& e) {
        throw HlaInternalException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::InvalidRegion& e) {
        throw HlaInternalException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::InvalidRegionContext& e) {
        throw HlaInternalException(L"Failed to subscribe to object class: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to subscribe to object class: " + e.what());
    }
}

ObjectInstanceHandlePtr FederateManager::createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& instanceName)
THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        if (instanceName.empty()) {
            return ObjectInstanceHandlePtr(_rtiAmbassador->registerObjectInstance(objectClassHandle));
        } else {
            return ObjectInstanceHandlePtr(_rtiAmbassador->registerObjectInstance(objectClassHandle, instanceName));
        }
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNameInUse&) {
        throw HlaInstanceNameInUseException(instanceName);
    } catch (RtiDriver::ObjectInstanceNameNotReserved&) {
        throw HlaInstanceNameInUseException(instanceName);
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectClassNotPublished& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectClassNotDefined& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNotKnown& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to register object instance: " + e.what());
    }
}

ObjectInstanceHandlePtr FederateManager::createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& instanceName, const RtiDriver::NameSet& attributeNames, const RtiDriver::Region& initialRegion)
THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        RtiDriver::NameRegionsMap regions = mapWithSameValueForAllKeys(attributeNames, makeRegionSet(initialRegion));
        return ObjectInstanceHandlePtr(_rtiAmbassador->registerObjectInstanceWithRegions(objectClassHandle, regions, instanceName));
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNameInUse&) {
        throw HlaInstanceNameInUseException(instanceName);
    } catch (RtiDriver::ObjectInstanceNameNotReserved&) {
        throw HlaInstanceNameInUseException(instanceName);
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectClassNotPublished& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectClassNotDefined& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNotKnown& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::AttributeNotDefined& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::AttributeNotPublished& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::InvalidRegion& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::InvalidRegionContext& e) {
        throw HlaInternalException(L"Failed to register object instance: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to register object instance: " + e.what());
    }
}

void FederateManager::sendInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameters, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException, HlaInternalException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        if (sendWithLogicalTime(logicalTime)) {
            _rtiAmbassador->sendInteraction(interactionClassHandle, parameters, timeStamp->getUserSuppliedTag(), encodeSendLogicalTime(logicalTime));
        } else {
            _rtiAmbassador->sendInteraction(interactionClassHandle, parameters, timeStamp->getUserSuppliedTag());
        }
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::NameNotFound& e) {
        throw HlaFomException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InteractionParameterNotDefined& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InteractionClassNotPublished& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InteractionClassNotDefined& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InvalidLogicalTime& e) {
        throw HlaInvalidLogicalTimeException(L"Failed to send interaction: " + e.what());
    }
}

void FederateManager::sendInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameters, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime, const RtiDriver::Region& region)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException, HlaInternalException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        if (sendWithLogicalTime(logicalTime)) {
            _rtiAmbassador->sendInteractionWithRegions(interactionClassHandle, parameters, timeStamp->getUserSuppliedTag(), makeRegionSet(region), encodeSendLogicalTime(logicalTime));
        } else {
            _rtiAmbassador->sendInteractionWithRegions(interactionClassHandle, parameters, timeStamp->getUserSuppliedTag(), makeRegionSet(region));
        }
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::NameNotFound& e) {
        throw HlaFomException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InteractionParameterNotDefined& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InteractionClassNotPublished& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InteractionClassNotDefined& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InvalidRegion& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InvalidRegionContext& e) {
        throw HlaInternalException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to send interaction: " + e.what());
    } catch (RtiDriver::InvalidLogicalTime& e) {
        throw HlaInvalidLogicalTimeException(L"Failed to send interaction: " + e.what());
    }
}

void FederateManager::requestAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                                  const RtiDriver::NameSet& attributes,
                                                  HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        _rtiAmbassador->requestAttributeValueUpdate(objectInstanceHandle, attributes, timeStamp->getUserSuppliedTag());
    } catch(RtiDriver::AttributeNotDefined& e) {
        throw HlaRtiException(L"Failed to request attribute value update for object instance: " + e.what());
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to request attribute value update for object instance: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to request attribute value update for object instance: " + e.what());
    } catch(RtiDriver::NameNotFound& e) {
        throw HlaRtiException(L"Failed to request attribute value update for object instance: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to request attribute value update for object instance: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to request attribute value update for object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNotKnown& e) {
        throw HlaInternalException(L"Failed to request attribute value update for object instance: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to request attribute value update for object instance: " + e.what());
    }
}


// Callbacks

void FederateManager::objectInstanceNameReservationSucceeded(const std::wstring&) {
    std::unique_lock<std::mutex> lock(_nameReservationSemaphore);
    _nameReservationCompleted = true;
    _nameReservationSucceeded = true;
    _nameReservationCondition.notify_all();
}

void FederateManager::objectInstanceNameReservationFailed(const std::wstring&) {
    std::unique_lock<std::mutex> lock(_nameReservationSemaphore);
    _nameReservationCompleted = true;
    _nameReservationSucceeded = false;
    _nameReservationCondition.notify_all();
}

void FederateManager::receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle,
                                         const RtiDriver::NameValueMap& parameterHandleValueMap,
                                         const RtiDriver::VariableLengthData& userSuppliedTag)
{
    HlaLogicalTimeImplPtr logicalTime = HlaLogicalTimeImpl::getInvalid();
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl());
    receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag, logicalTime, federateId);
}

void FederateManager::receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle,
                                         const RtiDriver::NameValueMap& parameterHandleValueMap,
                                         const RtiDriver::VariableLengthData& userSuppliedTag,
                                         const RtiDriver::FederateHandle& producingFederate)
{
    HlaLogicalTimeImplPtr logicalTime = HlaLogicalTimeImpl::getInvalid();
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl(producingFederate));
    receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag, logicalTime, federateId);
}

void FederateManager::receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle,
                                         const RtiDriver::NameValueMap& parameterHandleValueMap,
                                         const RtiDriver::VariableLengthData& userSuppliedTag,
                                         const RtiDriver::LogicalTime theTime,
                                         const RtiDriver::OrderType orderType)
{
    HlaLogicalTimeImplPtr logicalTime = HlaLogicalTimeImpl::createReceived(theTime.integer64, orderType == RtiDriver::TIMESTAMP);
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl());
    receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag, logicalTime, federateId);
}

void FederateManager::receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle,
                                         const RtiDriver::NameValueMap& parameterHandleValueMap,
                                         const RtiDriver::VariableLengthData& userSuppliedTag,
                                         const RtiDriver::LogicalTime theTime,
                                         const RtiDriver::OrderType orderType,
                                         const RtiDriver::FederateHandle& producingFederate)
{
    HlaLogicalTimeImplPtr logicalTime = HlaLogicalTimeImpl::createReceived(theTime.integer64, orderType == RtiDriver::TIMESTAMP);
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl(producingFederate));
    receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag, logicalTime, federateId);
}

void FederateManager::receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle,
                                         const RtiDriver::NameValueMap& parameterHandleValueMap,
                                         const RtiDriver::VariableLengthData& userSuppliedTag,
                                         const HlaLogicalTimeImplPtr logicalTime,
                                         const HlaFederateIdImplPtr producingFederate)
{
    try {
        RtiDriver::NameValueMap parameters(parameterHandleValueMap);
        _interactionManager->receiveInteraction(interactionClassHandle, parameters, producingFederate, _timeStampFactory->create(userSuppliedTag), logicalTime);
    } catch (std::exception &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Unhandled exception in FederateAmbassador receiveInteraction callback: " + StringUtil::convert(e.what())));
        _hlaWorld->postException(ex);
    }
}

void FederateManager::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                             const RtiDriver::NameValueMap& attributeHandleValueMap,
                                             const RtiDriver::VariableLengthData& userSuppliedTag)
{
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl());
    HlaLogicalTimeImplPtr time = HlaLogicalTimeImpl::getInvalid();
    reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag, time, federateId);
}

void FederateManager::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                             const RtiDriver::NameValueMap& attributeHandleValueMap,
                                             const RtiDriver::VariableLengthData& userSuppliedTag,
                                             const RtiDriver::FederateHandle& producingFederate)
{
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl(producingFederate));
    HlaLogicalTimeImplPtr time = HlaLogicalTimeImpl::getInvalid();
    reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag, time, federateId);
}

void FederateManager::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                             const RtiDriver::NameValueMap& attributeHandleValueMap,
                                             const RtiDriver::VariableLengthData& userSuppliedTag,
                                             const RtiDriver::LogicalTime theTime,
                                             const RtiDriver::OrderType orderType)
{
    HlaLogicalTimeImplPtr time = HlaLogicalTimeImpl::createReceived(theTime.integer64, orderType == RtiDriver::TIMESTAMP);
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl());
    reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag, time, federateId);
}

void FederateManager::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                             const RtiDriver::NameValueMap& attributeHandleValueMap,
                                             const RtiDriver::VariableLengthData& userSuppliedTag,
                                             const RtiDriver::LogicalTime theTime,
                                             const RtiDriver::OrderType orderType,
                                             const RtiDriver::FederateHandle& producingFederate)
{
    HlaLogicalTimeImplPtr time = HlaLogicalTimeImpl::createReceived(theTime.integer64, orderType == RtiDriver::TIMESTAMP);
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl(producingFederate));
    reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag, time, federateId);
}

void FederateManager::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                             const RtiDriver::NameValueMap& attributeHandleValueMap,
                                             const RtiDriver::VariableLengthData& userSuppliedTag,
                                             const HlaLogicalTimeImplPtr logicalTime,
                                             const HlaFederateIdImplPtr federateId)
{
    try {
        RtiDriver::NameValueMap attributes(attributeHandleValueMap);
        _objectManager->reflectAttributeValues(objectInstanceHandle, attributes, federateId, _timeStampFactory->create(userSuppliedTag), logicalTime);
    } catch (std::exception &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Unhandled exception in FederateAmbassador reflectAttributeValues callback: " + StringUtil::convert(e.what())));
        _hlaWorld->postException(ex);
    }
}

void FederateManager::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName) {
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl());
    try {
        _objectManager->discoverObjectInstance(objectInstanceHandle, instanceName, federateId, _timeStampFactory->create());
    } catch (std::exception &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Unhandled exception in FederateAmbassador discoverObjectInstance callback: " + StringUtil::convert(e.what())));
        _hlaWorld->postException(ex);
    }
}

void FederateManager::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const RtiDriver::FederateHandle& producingFederate) {
    HlaFederateIdImplPtr federateId(new HlaFederateIdImpl(producingFederate));
    try {
        _objectManager->discoverObjectInstance(objectInstanceHandle, instanceName, federateId, _timeStampFactory->create());
    } catch (std::exception &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Unhandled exception in FederateAmbassador discoverObjectInstance callback: " + StringUtil::convert(e.what())));
        _hlaWorld->postException(ex);
    }
}

void FederateManager::updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                            const RtiDriver::NameValueMap& attributes,
                                            HlaTimeStampPtr timeStamp,
                                            HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
         if (sendWithLogicalTime(logicalTime)) {
            _rtiAmbassador->updateAttributeValues(objectInstanceHandle, attributes, timeStamp->getUserSuppliedTag(), encodeSendLogicalTime(logicalTime));
         } else {
            _rtiAmbassador->updateAttributeValues(objectInstanceHandle, attributes, timeStamp->getUserSuppliedTag());
         }
    } catch(RtiDriver::AttributeNotDefined& e) {
        throw HlaRtiException(L"Failed to update object instance: " + e.what());
    } catch(RtiDriver::AttributeNotOwned& e) {
        throw HlaAttributeNotOwnedException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to update object instance: " + e.what());
    } catch(RtiDriver::NameNotFound& e) {
        throw HlaRtiException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNotKnown& e) {
        throw HlaObjectInstanceIsRemovedException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::InvalidLogicalTime& e) {
        throw HlaInvalidLogicalTimeException(L"Failed to update object instance: " + e.what());
    }
}

void FederateManager::updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                            const RtiDriver::NameValueMap& attributes,
                                            HlaTimeStampPtr timeStamp,
                                            HlaLogicalTimePtr logicalTime,
                                            const RtiDriver::NameSet& attributeNames,
                                            const RtiDriver::Region& newRegion,
                                            const RtiDriver::Region& oldRegion)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
         _rtiAmbassador->associateRegionsForUpdates(objectInstanceHandle, mapWithSameValueForAllKeys(attributeNames, makeRegionSet(newRegion)));
         _rtiAmbassador->unassociateRegionsForUpdates(objectInstanceHandle, mapWithSameValueForAllKeys(attributeNames, makeRegionSet(oldRegion)));

         if (sendWithLogicalTime(logicalTime)) {
            _rtiAmbassador->updateAttributeValues(objectInstanceHandle, attributes, timeStamp->getUserSuppliedTag(), encodeSendLogicalTime(logicalTime));
         } else {
            _rtiAmbassador->updateAttributeValues(objectInstanceHandle, attributes, timeStamp->getUserSuppliedTag());
         }
    } catch(RtiDriver::AttributeNotDefined& e) {
        throw HlaRtiException(L"Failed to update object instance: " + e.what());
    } catch(RtiDriver::AttributeNotOwned& e) {
        throw HlaAttributeNotOwnedException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to update object instance: " + e.what());
    } catch(RtiDriver::NameNotFound& e) {
        throw HlaRtiException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNotKnown& e) {
        throw HlaObjectInstanceIsRemovedException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::InvalidRegion& e) {
        throw HlaInternalException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::InvalidRegionContext& e) {
        throw HlaInternalException(L"Failed to update object instance: " + e.what());
    } catch (RtiDriver::InvalidLogicalTime& e) {
        throw HlaInvalidLogicalTimeException(L"Failed to update object instance: " + e.what());
    }
}

void FederateManager::deleteObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                           HlaTimeStampPtr timeStamp,
                                           HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        if (sendWithLogicalTime(logicalTime)) {
            _rtiAmbassador->deleteObjectInstance(objectInstanceHandle, timeStamp->getUserSuppliedTag(), encodeSendLogicalTime(logicalTime));
        } else {
            _rtiAmbassador->deleteObjectInstance(objectInstanceHandle, timeStamp->getUserSuppliedTag());
        }

        std::wstring instanceName = objectInstanceHandle.getObjectInstanceName();
        if (instanceName.length() < 3 || instanceName.substr(0, 3) != L"HLA") {
           _rtiAmbassador->releaseObjectInstanceName(instanceName);
        }
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to delete object instance: " + e.what());
    } catch (RtiDriver::NotConnected &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to delete object instance: " + e.what());

    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to delete object instance: " + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to delete object instance: " + e.what());

    } catch (RtiDriver::DeletePrivilegeNotHeld& e) {
        throw HlaInternalException(L"Failed to delete object instance: " + e.what());
    } catch (RtiDriver::ObjectInstanceNotKnown& e) {
        throw HlaInternalException(L"Failed to delete object instance: " + e.what());

    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to delete object instance: " + e.what());
    } catch (RtiDriver::InvalidLogicalTime& e) {
        throw HlaInvalidLogicalTimeException(L"Failed to delete object instance: " + e.what());
    }
}


void FederateManager::synchronizationPointRegistrationSucceeded(const std::wstring& synchPointName) {
     //ignore
}

void FederateManager::synchronizationPointRegistrationFailed(const std::wstring& synchPointName, RtiDriver::SynchronizationPointFailureReason failureReason) {
     //ignore
}

void FederateManager::announceSynchronizationPoint(const std::wstring& synchPointName, const RtiDriver::VariableLengthData& userSuppliedTag) {
    if (_hlaWorld->getTuning()->AUTO_ACHIEVE) {
        struct FederateAutoAchieve {
            static void run(RtiDriver::RtiAmbassador* rtiAmbassador, HlaWorldImpl*  hlaWorld, std::wstring syncPointLabel) {
                try {
                    rtiAmbassador->synchronizationPointAchieved(syncPointLabel);
                } catch (RtiDriver::BaseException& e) {
                    HlaExceptionPtr ex(new HlaRtiException(L"Failed to achieve synchronization point: " + e.what()));
                    hlaWorld->postException(ex);
                }
            }
        };
        std::function<void()> callback = std::bind(&FederateAutoAchieve::run, _rtiAmbassador.get(), _hlaWorld, synchPointName);
        _hlaWorld->invokeLater(callback);
    }
}

void FederateManager::federationSynchronized(const std::wstring& synchPointName) {
    //Ignore
}

void FederateManager::timeRegulationEnabled(const RtiDriver::LogicalTime theTime) {
    std::unique_lock<std::mutex> lock(_timeRegulationSemaphore);
    _timeRegulating = true;
    _timeValid = theTime.representation == RtiDriver::INTEGER64;
    _currentTime = theTime.integer64;
    _timeRegulationEnabled.notify_all();
}

void FederateManager::timeConstrainedEnabled(const RtiDriver::LogicalTime theTime) {
    std::unique_lock<std::mutex> lock(_timeConstrainedSemaphore);
    _timeConstrained = true;
    _timeValid = theTime.representation == RtiDriver::INTEGER64;
    _currentTime = theTime.integer64;
    _timeConstrainedEnabled.notify_all();
}

void FederateManager::timeAdvanceGrant(const RtiDriver::LogicalTime theTime) {
    if (_expectingGrantAfterRestore) {
        _expectingGrantAfterRestore = false;
        try {
            HlaLogicalTimeImplPtr time = HlaLogicalTimeImpl::createReceived(theTime.integer64, true);
            _saveRestManager->timeAdvanceGrantAfterRestore(time);
        }  catch (HlaException &e) {
            _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
        }
        return;
    }

    std::unique_lock<std::mutex> lock(_timeAdvanceSemaphore);
    _currentTime = theTime.integer64;
    _granted = true;
    _timeAdvanceGranted.notify_all();
}

HlaLogicalTimePtr FederateManager::timeAdvanceRequest(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,
            HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException,
            HlaSaveInProgressException, HlaRestoreInProgressException) {
   try {
      if (!sendWithLogicalTime(logicalTime)) {
         return logicalTime;
      }

      std::unique_lock<std::mutex> lock(_timeAdvanceSemaphore);
      _rtiAmbassador->timeAdvanceRequest(logicalTime->getValue());
      _granted = false;

      while (!_granted) {
         _timeAdvanceGranted.wait(lock);
      }

      return HlaLogicalTimeImpl::create(_currentTime);
   } catch (RtiDriver::FederateNotExecutionMember& e) {
      disconnectDetected();
      throw HlaNotConnectedException(L"Failed to request time advance: " + e.what() );
   } catch (RtiDriver::NotConnected& e) {
      disconnectDetected();
      throw HlaNotConnectedException(L"Failed to request time advance " + e.what() );
   } catch (RtiDriver::RestoreInProgress& e) {
      throw HlaRestoreInProgressException(L"Failed to request time advance "+ e.what() );
   } catch (RtiDriver::SaveInProgress& e) {
      throw HlaSaveInProgressException(L"Failed to request time advance "+ e.what() );
   } catch (RtiDriver::RTIinternalError& e) {
      throw HlaRtiException(L"Failed to request time advance " + e.what() );
   } catch (RtiDriver::InTimeAdvancingState& e) {
      throw HlaInTimeAdvancingStateException(L"Failed to request time advance "+ e.what() );
   } catch (RtiDriver::InvalidLogicalTime& e) {
      throw HlaInvalidLogicalTimeException(L"Failed to request time advance "+ e.what() );
   } catch (RtiDriver::LogicalTimeAlreadyPassed& e) {
      throw HlaInvalidLogicalTimeException(L"Failed to request time advance "+ e.what() );
   } catch (RtiDriver::RequestForTimeRegulationPending& e) {
      throw HlaInternalException(L"Failed to request time advance "+ e.what() );
   } catch (RtiDriver::RequestForTimeConstrainedPending& e) {
      throw HlaInternalException(L"Failed to request time advance "+ e.what() );
   }
}


HlaLogicalTimePtr FederateManager::nextMessageRequestAvailable(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,
            HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException,
            HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
       if (!sendWithLogicalTime(logicalTime)) {
          return logicalTime;
       }

       std::unique_lock<std::mutex> lock(_timeAdvanceSemaphore);
       _rtiAmbassador->nextMessageRequestAvailable(logicalTime->getValue());
       _granted = false;

       while (!_granted) {
          _timeAdvanceGranted.wait(lock);
       }

       return HlaLogicalTimeImpl::create(_currentTime);
    } catch (RtiDriver::FederateNotExecutionMember& e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to request time advance: " + e.what() );
    } catch (RtiDriver::NotConnected& e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to request time advance " + e.what() );
    } catch (RtiDriver::RestoreInProgress& e) {
       throw HlaRestoreInProgressException(L"Failed to request time advance "+ e.what() );
    } catch (RtiDriver::SaveInProgress& e) {
       throw HlaRtiException(L"Failed to request time advance "+ e.what() );
    } catch (RtiDriver::RTIinternalError& e) {
       throw HlaRtiException(L"Failed to request time advance " + e.what() );
    } catch (RtiDriver::InTimeAdvancingState& e) {
       throw HlaInTimeAdvancingStateException(L"Failed to request time advance "+ e.what() );
    } catch (RtiDriver::InvalidLogicalTime& e) {
       throw HlaInvalidLogicalTimeException(L"Failed to request time advance "+ e.what() );
    } catch (RtiDriver::LogicalTimeAlreadyPassed& e) {
       throw HlaInvalidLogicalTimeException(L"Failed to request time advance "+ e.what() );
    } catch (RtiDriver::RequestForTimeRegulationPending& e) {
       throw HlaInternalException(L"Failed to request time advance "+ e.what() );
    } catch (RtiDriver::RequestForTimeConstrainedPending& e) {
       throw HlaInternalException(L"Failed to request time advance "+ e.what() );
    }
}

void FederateManager::modifyLookahead(long long lookahead)
THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,
            HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        if (_timeRegulating || _timeConstrained) {
            _rtiAmbassador->modifyLookahead(lookahead);
        }
    } catch (RtiDriver::InvalidLookahead& e) {
        throw HlaInvalidLogicalTimeException(L"Invalid lookahead value" + e.what());
    } catch (RtiDriver::InTimeAdvancingState& e) {
        throw HlaInternalException(L"Cannot modify lookahead while in advancing state" + e.what());
    } catch (RtiDriver::SaveInProgress& e) {
        throw HlaSaveInProgressException(L"Failed to modify lookahead" + e.what());
    } catch (RtiDriver::RestoreInProgress& e) {
        throw HlaRestoreInProgressException(L"Failed to modify lookahead" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to modify lookahead" + e.what());
    } catch (RtiDriver::NotConnected& e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to modify lookahead" + e.what());
    } catch (RtiDriver::RTIinternalError& e) {
        throw HlaRtiException(L"Failed to modify lookahead" + e.what());
    }
}

bool FederateManager::sendWithLogicalTime(HlaLogicalTimePtr logicalTime) {
   if (!_timeRegulating && !_timeConstrained && !_hlaWorld->getTuning()->ALWAYS_USE_LOGICAL_TIME) {
      return false;
   }
   return logicalTime->isValid();
}

long long FederateManager::encodeSendLogicalTime(HlaLogicalTimePtr logicalTime) {
   return logicalTime->getValue();
}

void FederateManager::requestAttributeOwnershipRelease(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                                       const RtiDriver::NameSet& attributeHandleSet,
                                                       const RtiDriver::VariableLengthData& userSuppliedTag)
{}

void FederateManager::attributeOwnershipAcquisitionNotification(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                                                const RtiDriver::NameSet& attributeHandleSet,
                                                                const RtiDriver::VariableLengthData& userSuppliedTag)
{}

void FederateManager::requestAttributeOwnershipAssumption(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& offeredAttributes, const RtiDriver::VariableLengthData& userSuppliedTag)
{}

void FederateManager::attributeOwnershipUnavailable(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& theAttributes)
{}

void FederateManager::confirmAttributeOwnershipAcquisitionCancellation(const RtiDriver::ObjectInstanceHandle& theObject, const RtiDriver::NameSet& attributeHandleSet)
{}

void FederateManager::informAttributeOwnership(const RtiDriver::ObjectInstanceHandle& theObject, const std::wstring theAttribute,  const RtiDriver::FederateHandle& federateHandle)
{}

void FederateManager::attributeIsNotOwned(const RtiDriver::ObjectInstanceHandle& theObject, const std::wstring theAttribute)
{}

void FederateManager::attributeIsOwnedByRTI(const RtiDriver::ObjectInstanceHandle& theObject, const std::wstring theAttribute)
{}


/*
 * Save calls
 */

void FederateManager::requestFederationSave(const std::wstring &label, HlaLogicalTimePtr logicalTime)
THROW_SPEC( HlaRtiException, HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
      if (logicalTime) {
         _rtiAmbassador->requestFederationSave(label, encodeSendLogicalTime(logicalTime));
      } else {
         _rtiAmbassador->requestFederationSave(label);
      }
    } catch (RtiDriver::SaveInProgress &e) {
       throw HlaSaveInProgressException(L"Failed to request federation save:" + e.what());
    } catch (RtiDriver::RestoreInProgress &e) {
       throw HlaRestoreInProgressException(L"Failed to request federation save:" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to request federation save:" + e.what());
    } catch (RtiDriver::NotConnected &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to request federation save:" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
       throw HlaRtiException(L"Failed to request federation save:" + e.what());
    } catch (RtiDriver::FederateUnableToUseTime &e) {
       throw HlaInvalidLogicalTimeException(L"Failed to request federation save:" + e.what());
    } catch (RtiDriver::LogicalTimeAlreadyPassed &e) {
       throw HlaInvalidLogicalTimeException(L"Failed to request federation save:" + e.what());
    } catch (RtiDriver::InvalidLogicalTime &e) {
       throw HlaInvalidLogicalTimeException(L"Failed to request federation save:" + e.what());
    }
}

void FederateManager::federateSaveBegun()
THROW_SPEC(HlaRtiException, HlaNotConnectedException,  HlaRestoreInProgressException) {
    try {
       _rtiAmbassador->federateSaveBegun();
    } catch (RtiDriver::SaveNotInitiated &e) {
       throw HlaRtiException(L"Failed to tell RTI save begun:" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI save begun:" + e.what());
    } catch (RtiDriver::RestoreInProgress &e) {
       throw HlaRestoreInProgressException(L"Failed to tell RTI save begun:" + e.what());
    } catch (RtiDriver::NotConnected &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI save begun:" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
       throw HlaRtiException(L"Failed to tell RTI save begun" + e.what());
    }

}

void FederateManager::federateSaveComplete()
THROW_SPEC( HlaRtiException, HlaNotConnectedException, HlaRestoreInProgressException) {
    try {
       _rtiAmbassador->federateSaveComplete();
    } catch (RtiDriver::FederateHasNotBegunSave &e) {
       throw HlaRtiException(L"Failed to tell RTI save complete" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI save complete" + e.what());
    } catch (RtiDriver::RestoreInProgress &e) {
       throw HlaRestoreInProgressException(L"Failed to tell RTI save complete" + e.what());
    } catch (RtiDriver::NotConnected &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI save complete" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
       throw HlaRtiException(L"Failed to tell RTI save complete" + e.what());
    }
}

void FederateManager::federateSaveNotComplete()
THROW_SPEC( HlaRtiException, HlaNotConnectedException, HlaRestoreInProgressException) {
    try {
       _rtiAmbassador->federateSaveNotComplete();
    } catch (RtiDriver::FederateHasNotBegunSave &e) {
       throw HlaRtiException(L"Failed to tell RTI save not complete" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI save not complete" + e.what());
    } catch (RtiDriver::RestoreInProgress &e) {
       throw HlaRestoreInProgressException(L"Failed to tell RTI save not complete" + e.what());
    } catch (RtiDriver::NotConnected &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI save not complete" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
       throw HlaRtiException(L"Failed to tell RTI save not complete" + e.what());
    }
}

/*
 * Save callbacks
 */

void FederateManager::initiateFederateSave(const std::wstring& label) {
    try {
       HlaLogicalTimeImplPtr time = HlaLogicalTimeImpl::getInvalid();
       _saveRestManager->initiateFederateSave(label, time);
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::initiateFederateSave(const std::wstring& label, const RtiDriver::LogicalTime theTime) {
    try {
       HlaLogicalTimeImplPtr time = HlaLogicalTimeImpl::createReceived(theTime.integer64, true);
       _saveRestManager->initiateFederateSave(label, time);
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::federationSaved() {
    try {
       _saveRestManager->federationSaved();
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::federationNotSaved(RtiDriver::SaveFailureReason saveFailureReason) {
    try {
       _saveRestManager->federationNotSaved(saveFailureReason);
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

/*
 * Restore calls
 */

bool FederateManager::requestFederationRestore(const std::wstring &label)
THROW_SPEC( HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
         std::unique_lock<std::mutex> lock(_restoreRequestSemaphore);
         _restoreRequestCompleted = false;
         _rtiAmbassador->requestFederationRestore(label);
         // Wait for response from RTI
         while (!_restoreRequestCompleted) {
             _restoreRequestCondition.wait(lock);
         }
         return _restoreRequestSucceeded;
    } catch (RtiDriver::SaveInProgress &e) {
       throw HlaSaveInProgressException(L"Failed to request federation restore" + e.what());
    } catch (RtiDriver::RestoreInProgress &e) {
       throw HlaRestoreInProgressException(L"Failed to request federation restore" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to request federation restore" + e.what());
    } catch (RtiDriver::NotConnected &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to request federation restore" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
       throw HlaRtiException(L"Failed to request federation restore" + e.what());
    }
}

void FederateManager::federateRestoreComplete()
THROW_SPEC( HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException) {
    try {
       _rtiAmbassador->federateRestoreComplete();
    } catch (RtiDriver::RestoreNotRequested &e) {
       throw HlaRtiException(L"Failed to tell RTI federate restore complete" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI federate restore complete" + e.what());
    } catch (RtiDriver::SaveInProgress &e) {
       throw HlaSaveInProgressException(L"Failed to tell RTI federate restore complete" + e.what());
    } catch (RtiDriver::NotConnected &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI federate restore complete" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
       throw HlaRtiException(L"Failed to tell RTI federate restore complete" + e.what());
    }
}

void FederateManager::federateRestoreNotComplete()
THROW_SPEC( HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException) {
    try {
       _rtiAmbassador->federateRestoreNotComplete();
    } catch (RtiDriver::RestoreNotRequested &e) {
       throw HlaRtiException(L"Failed to tell RTI federate restore not complete" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI federate restore not complete" + e.what());
    } catch (RtiDriver::SaveInProgress &e) {
       throw HlaSaveInProgressException(L"Failed to tell RTI federate restore not complete" + e.what());
    } catch (RtiDriver::NotConnected &e) {
       disconnectDetected();
       throw HlaNotConnectedException(L"Failed to tell RTI federate restore not complete" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
       throw HlaRtiException(L"Failed to tell RTI federate restore not complete" + e.what());
    }
}

/*
 * Restore callbacks
 */

void FederateManager::requestFederationRestoreSucceeded(const std::wstring& label) {
    try {
        std::unique_lock<std::mutex> lock(_restoreRequestSemaphore);
        _restoreRequestCompleted = true;
        _restoreRequestSucceeded = true;
        _restoreRequestCondition.notify_all();
    } catch (HlaException &e) {
        _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::requestFederationRestoreFailed(const std::wstring& label) {
    try {
        std::unique_lock<std::mutex> lock(_restoreRequestSemaphore);
        _restoreRequestCompleted = true;
        _restoreRequestSucceeded = false;
        _restoreRequestCondition.notify_all();
    } catch (HlaException &e) {
        _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::federationRestoreBegun() {
    try {
       _saveRestManager->federationRestoreBegun();
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::initiateFederateRestore(const std::wstring& label, const RtiDriver::FederateHandle& federateHandle, const std::wstring& federateName) {
    try {
       HlaFederateIdImplPtr federateId(new HlaFederateIdImpl(federateHandle));
       _saveRestManager->initiateFederateRestore(label, federateId, federateName);
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::federationRestored() {
    try {
       _expectingGrantAfterRestore = _saveRestManager->federationRestored();
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::federationNotRestored(RtiDriver::RestoreFailureReason restoreFailureReason) {
    try {
       _expectingGrantAfterRestore = _saveRestManager->federationNotRestored(restoreFailureReason);
    } catch (HlaException &e) {
       _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

/*
 * DDM calls
 */

RegionPtr FederateManager::createRegion(const RtiDriver::NameRangeMap& area, const std::wstring& hla13routingSpace)
THROW_SPEC(HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        RegionPtr region = RegionPtr(_rtiAmbassador->createRegion(area, hla13routingSpace));

        _rtiAmbassador->commitRegions(makeRegionSet(*region));

        return region;
    } catch (RtiDriver::InvalidDimension &e) {
        throw HlaInternalException(L"Failed to create region" + e.what());
    } catch (RtiDriver::InvalidRegion &e) {
        throw HlaInternalException(L"Failed to create region" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to create region" + e.what());
    } catch (RtiDriver::RestoreInProgress &e) {
        throw HlaRestoreInProgressException(L"Failed to create region" + e.what());
    } catch (RtiDriver::SaveInProgress &e) {
        throw HlaSaveInProgressException(L"Failed to create region" + e.what());
    } catch (RtiDriver::NotConnected &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to create region" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
        throw HlaRtiException(L"Failed to create region" + e.what());
    }
}

void FederateManager::deleteRegion(const RtiDriver::Region& region)
THROW_SPEC(HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
         _rtiAmbassador->deleteRegion(region);
    } catch (RtiDriver::InvalidDimension &e) {
        throw HlaInternalException(L"Failed to create region" + e.what());
    } catch (RtiDriver::InvalidRegion &e) {
        throw HlaInternalException(L"Failed to create region" + e.what());
    } catch (RtiDriver::FederateNotExecutionMember &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to create region" + e.what());
    } catch (RtiDriver::RestoreInProgress &e) {
        throw HlaRestoreInProgressException(L"Failed to create region" + e.what());
    } catch (RtiDriver::SaveInProgress &e) {
        throw HlaSaveInProgressException(L"Failed to create region" + e.what());
    } catch (RtiDriver::NotConnected &e) {
        disconnectDetected();
        throw HlaNotConnectedException(L"Failed to create region" + e.what());
    } catch (RtiDriver::RTIinternalError &e) {
        throw HlaRtiException(L"Failed to create region" + e.what());
    }
}

/*
 * DDM callbacks
 */

void FederateManager::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& attributeNames) {
    try {
        _objectManager->attributesInScope(objectInstanceHandle, attributeNames);
    } catch (HlaException &e) {
        _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}

void FederateManager::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& attributeNames) {
    try {
        _objectManager->attributesOutOfScope(objectInstanceHandle, attributeNames);
    } catch (HlaException &e) {
        _hlaWorld->postException(HlaExceptionPtr(new HlaInternalException(L"Unhandled exception in FederateAmbassador callback: " + e.what_w())));
    }
}
