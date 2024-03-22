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

#include "HlaExecutionConfigurationImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaExecutionConfigurationValueListener.h>
#include "StringUtil.h"
#include "HlaExecutionConfigurationManagerImpl.h"
#include "HlaExecutionConfigurationAttributesImpl.h"
#include "HlaExecutionConfigurationUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;

static const wchar_t ROOT_FRAME_NAME_ATTRIBUTE_NAME[] = L"root_frame_name";
static const wchar_t SCENARIO_TIME_EPOCH_ATTRIBUTE_NAME[] = L"scenario_time_epoch";
static const wchar_t CURRENT_EXECUTION_MODE_ATTRIBUTE_NAME[] = L"current_execution_mode";
static const wchar_t NEXT_EXECUTION_MODE_ATTRIBUTE_NAME[] = L"next_execution_mode";
static const wchar_t NEXT_MODE_SCENARIO_TIME_ATTRIBUTE_NAME[] = L"next_mode_scenario_time";
static const wchar_t NEXT_MODE_CTE_TIME_ATTRIBUTE_NAME[] = L"next_mode_cte_time";
static const wchar_t LEAST_COMMON_TIME_STEP_ATTRIBUTE_NAME[] = L"least_common_time_step";

RtiDriver::NameSet HlaExecutionConfigurationImpl::getAttributes() {
    RtiDriver::NameSet res;
    res.insert(L"root_frame_name");
    res.insert(L"scenario_time_epoch");
    res.insert(L"current_execution_mode");
    res.insert(L"next_execution_mode");
    res.insert(L"next_mode_scenario_time");
    res.insert(L"next_mode_cte_time");
    res.insert(L"least_common_time_step");
    return res;
}


bool HlaExecutionConfigurationImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaExecutionConfigurationImpl::isWithinInterest() const {
    return !_removed;
}

HlaExecutionConfigurationAttributesPtr HlaExecutionConfigurationImpl::getHlaExecutionConfigurationAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRootFrameName();
    updateScenarioTimeEpoch();
    updateCurrentExecutionMode();
    updateNextExecutionMode();
    updateNextModeScenarioTime();
    updateNextModeCteTime();
    updateLeastCommonTimeStep();
    return HlaExecutionConfigurationAttributesPtr(new HlaExecutionConfigurationAttributesImpl(
        _rootFrameNameAttribute,
        _scenarioTimeEpochAttribute,
        _currentExecutionModeAttribute,
        _nextExecutionModeAttribute,
        _nextModeScenarioTimeAttribute,
        _nextModeCteTimeAttribute,
        _leastCommonTimeStepAttribute
));
}

HlaExecutionConfigurationUpdaterPtr HlaExecutionConfigurationImpl::getHlaExecutionConfigurationUpdater() {
    HlaExecutionConfigurationUpdater* ptr = new HlaExecutionConfigurationUpdaterImpl(shared_from_this());
    return HlaExecutionConfigurationUpdaterPtr(ptr);
}

std::wstring HlaExecutionConfigurationImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaExecutionConfigurationImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

HlaFederateIdImplPtr HlaExecutionConfigurationImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaExecutionConfigurationUpdaterImpl
*/

void HlaExecutionConfigurationImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaExecutionConfigurationAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaExecutionConfigurationAttributesImplPtr  HlaExecutionConfigurationImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaExecutionConfigurationAttributesImplPtr ret;

    HlaEnumSet<HlaExecutionConfigurationAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        for (AttributeMap::const_iterator iter = attributeUpdate.begin(); iter != attributeUpdate.end(); ++iter) {
                switch (iter->first) {
                    case HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME:
                        {
                            updateRootFrameName();
                            AttributeValue<std::wstring > oldValue(_rootFrameNameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _rootFrameNameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireroot_frame_nameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME, _rootFrameNameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME);
                        }
                        break;
                    case HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH:
                        {
                            updateScenarioTimeEpoch();
                            AttributeValue<double > oldValue(_scenarioTimeEpochAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _scenarioTimeEpochAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firescenario_time_epochUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH, _scenarioTimeEpochAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH);
                        }
                        break;
                    case HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE:
                        {
                            updateCurrentExecutionMode();
                            AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > oldValue(_currentExecutionModeAttribute);

                            std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > valuePtr =  std::static_pointer_cast<LunarSimulation::ExecutionMode::ExecutionMode >(iter->second);
                            _currentExecutionModeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firecurrent_execution_modeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE, _currentExecutionModeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE);
                        }
                        break;
                    case HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE:
                        {
                            updateNextExecutionMode();
                            AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > oldValue(_nextExecutionModeAttribute);

                            std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > valuePtr =  std::static_pointer_cast<LunarSimulation::ExecutionMode::ExecutionMode >(iter->second);
                            _nextExecutionModeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenext_execution_modeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE, _nextExecutionModeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE);
                        }
                        break;
                    case HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME:
                        {
                            updateNextModeScenarioTime();
                            AttributeValue<double > oldValue(_nextModeScenarioTimeAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _nextModeScenarioTimeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenext_mode_scenario_timeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME, _nextModeScenarioTimeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME);
                        }
                        break;
                    case HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME:
                        {
                            updateNextModeCteTime();
                            AttributeValue<double > oldValue(_nextModeCteTimeAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _nextModeCteTimeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenext_mode_cte_timeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME, _nextModeCteTimeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME);
                        }
                        break;
                    case HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP:
                        {
                            updateLeastCommonTimeStep();
                            AttributeValue<long long > oldValue(_leastCommonTimeStepAttribute);

                            std::shared_ptr<long long > valuePtr =  std::static_pointer_cast<long long >(iter->second);
                            _leastCommonTimeStepAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireleast_common_time_stepUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP, _leastCommonTimeStepAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP);
                        }
                        break;
                    default:
                        break;
                }
        }
        ret = std::dynamic_pointer_cast<HlaExecutionConfigurationAttributesImpl>(getHlaExecutionConfigurationAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaExecutionConfigurationImpl::sendAttributes(const AttributeMap& attributeSet, HlaExecutionConfigurationAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
            switch (iter->first) {

                case HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME:
                    if (attributeValues->hasRootFrameName()) {
                        try {
                            _objectClassManager->_hLAunicodeStringEncoder.set(*(std::wstring*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_hLAunicodeStringEncoder.getEncodedLength());
                            _objectClassManager->_hLAunicodeStringEncoder.encodeInto(res);
                            attributeValueMap[ROOT_FRAME_NAME_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode ROOT_FRAME_NAME_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH:
                    if (attributeValues->hasScenarioTimeEpoch()) {
                        try {
                            _objectClassManager->_hLAfloat64LEEncoder.set(*(double*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAfloat64LEEncoder.encodeInto(res);
                            attributeValueMap[SCENARIO_TIME_EPOCH_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode SCENARIO_TIME_EPOCH_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE:
                    if (attributeValues->hasCurrentExecutionMode()) {
                        try {
                            _objectClassManager->_executionModeEncoderEncoder.set(*(LunarSimulation::ExecutionMode::ExecutionMode*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_executionModeEncoderEncoder.encodeInto(res);
                            attributeValueMap[CURRENT_EXECUTION_MODE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode CURRENT_EXECUTION_MODE_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE:
                    if (attributeValues->hasNextExecutionMode()) {
                        try {
                            _objectClassManager->_executionModeEncoderEncoder.set(*(LunarSimulation::ExecutionMode::ExecutionMode*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_executionModeEncoderEncoder.encodeInto(res);
                            attributeValueMap[NEXT_EXECUTION_MODE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode NEXT_EXECUTION_MODE_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME:
                    if (attributeValues->hasNextModeScenarioTime()) {
                        try {
                            _objectClassManager->_hLAfloat64LEEncoder.set(*(double*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAfloat64LEEncoder.encodeInto(res);
                            attributeValueMap[NEXT_MODE_SCENARIO_TIME_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode NEXT_MODE_SCENARIO_TIME_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME:
                    if (attributeValues->hasNextModeCteTime()) {
                        try {
                            _objectClassManager->_hLAfloat64LEEncoder.set(*(double*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAfloat64LEEncoder.encodeInto(res);
                            attributeValueMap[NEXT_MODE_CTE_TIME_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode NEXT_MODE_CTE_TIME_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP:
                    if (attributeValues->hasLeastCommonTimeStep()) {
                        try {
                            _objectClassManager->_hLAinteger64BEEncoder.set(*(long long*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAinteger64BEEncoder.encodeInto(res);
                            attributeValueMap[LEAST_COMMON_TIME_STEP_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode LEAST_COMMON_TIME_STEP_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (!attributeValueMap.empty()) {
       _objectClassManager->updateAttributeValues(shared_from_this(), _objectInstanceHandle, attributeValueMap, timeStamp, logicalTime);
    }
}

void HlaExecutionConfigurationImpl::fireroot_frame_nameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::rootFrameNameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationImpl::firescenario_time_epochUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::scenarioTimeEpochUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationImpl::firecurrent_execution_modeUpdated(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > value, const AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::currentExecutionModeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationImpl::firenext_execution_modeUpdated(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > value, const AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::nextExecutionModeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationImpl::firenext_mode_scenario_timeUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::nextModeScenarioTimeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationImpl::firenext_mode_cte_timeUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::nextModeCteTimeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationImpl::fireleast_common_time_stepUpdated(std::shared_ptr<long long > value, const AttributeValue<long long >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<long long > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::leastCommonTimeStepUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaExecutionConfigurationImpl::fireAttributesUpdated(const HlaEnumSet<HlaExecutionConfigurationAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaExecutionConfigurationListenerPtr> listeners = _executionConfigurationListeners.getListeners();
    for (std::set<HlaExecutionConfigurationListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationImpl::fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (oldFederateId && newFederateId && *oldFederateId != *newFederateId) {
        std::set<HlaExecutionConfigurationValueListenerPtr> listeners = _executionConfigurationValueListeners.getListeners();
        for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            std::function<void()> callback = std::bind(&HlaExecutionConfigurationValueListener::producingFederateUpdated, *it, shared_from_this(), attribute, oldFederateId, newFederateId, timeStamp, logicalTime);
            _hlaWorld->postNotification(callback);
        }
    }
}

bool HlaExecutionConfigurationImpl::hasRootFrameName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRootFrameName();
    return _rootFrameNameAttribute.hasValue();
}

std::wstring HlaExecutionConfigurationImpl::getRootFrameName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRootFrameName();
    if (_rootFrameNameAttribute.hasValue()) {
        return *_rootFrameNameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rootFrameName' not set for instance " + getHlaInstanceName());
}

std::wstring HlaExecutionConfigurationImpl::getRootFrameName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRootFrameName();
    if (_rootFrameNameAttribute.hasValue()) {
        return *_rootFrameNameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaExecutionConfigurationImpl::getRootFrameNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRootFrameName();
    if (_rootFrameNameAttribute.hasValue()) {
        return _rootFrameNameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rootFrameName' not set for instance " + getHlaInstanceName());
}

void HlaExecutionConfigurationImpl::updateRootFrameName() {
    if (_rootFrameNameAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _rootFrameNameAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAunicodeStringDecoder.decodeFrom(encodedValue, 0);
            _rootFrameNameAttribute.setDecodedValue(std::shared_ptr<std::wstring >(new std::wstring(_objectClassManager->_hLAunicodeStringDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ROOT_FRAME_NAME_ATTRIBUTE_NAME: Failed to decode HLAunicodeString. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ROOT_FRAME_NAME_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _rootFrameNameAttribute.clearEncodedValue();
        }
    }
}

bool HlaExecutionConfigurationImpl::hasScenarioTimeEpoch() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateScenarioTimeEpoch();
    return _scenarioTimeEpochAttribute.hasValue();
}

double HlaExecutionConfigurationImpl::getScenarioTimeEpoch() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateScenarioTimeEpoch();
    if (_scenarioTimeEpochAttribute.hasValue()) {
        return *_scenarioTimeEpochAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'scenarioTimeEpoch' not set for instance " + getHlaInstanceName());
}

double HlaExecutionConfigurationImpl::getScenarioTimeEpoch(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateScenarioTimeEpoch();
    if (_scenarioTimeEpochAttribute.hasValue()) {
        return *_scenarioTimeEpochAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaExecutionConfigurationImpl::getScenarioTimeEpochTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateScenarioTimeEpoch();
    if (_scenarioTimeEpochAttribute.hasValue()) {
        return _scenarioTimeEpochAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'scenarioTimeEpoch' not set for instance " + getHlaInstanceName());
}

void HlaExecutionConfigurationImpl::updateScenarioTimeEpoch() {
    if (_scenarioTimeEpochAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _scenarioTimeEpochAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAfloat64LEDecoder.decodeFrom(encodedValue, 0);
            _scenarioTimeEpochAttribute.setDecodedValue(std::shared_ptr<double >(new double(_objectClassManager->_hLAfloat64LEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode SCENARIO_TIME_EPOCH_ATTRIBUTE_NAME: Failed to decode Time. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode SCENARIO_TIME_EPOCH_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _scenarioTimeEpochAttribute.clearEncodedValue();
        }
    }
}

bool HlaExecutionConfigurationImpl::hasCurrentExecutionMode() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCurrentExecutionMode();
    return _currentExecutionModeAttribute.hasValue();
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationImpl::getCurrentExecutionMode() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCurrentExecutionMode();
    if (_currentExecutionModeAttribute.hasValue()) {
        return *_currentExecutionModeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'currentExecutionMode' not set for instance " + getHlaInstanceName());
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationImpl::getCurrentExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCurrentExecutionMode();
    if (_currentExecutionModeAttribute.hasValue()) {
        return *_currentExecutionModeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > HlaExecutionConfigurationImpl::getCurrentExecutionModeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCurrentExecutionMode();
    if (_currentExecutionModeAttribute.hasValue()) {
        return _currentExecutionModeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'currentExecutionMode' not set for instance " + getHlaInstanceName());
}

void HlaExecutionConfigurationImpl::updateCurrentExecutionMode() {
    if (_currentExecutionModeAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _currentExecutionModeAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_executionModeEncoderDecoder.decodeFrom(encodedValue, 0);
            _currentExecutionModeAttribute.setDecodedValue(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode >(new LunarSimulation::ExecutionMode::ExecutionMode(_objectClassManager->_executionModeEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode CURRENT_EXECUTION_MODE_ATTRIBUTE_NAME: Failed to decode ExecutionMode. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode CURRENT_EXECUTION_MODE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _currentExecutionModeAttribute.clearEncodedValue();
        }
    }
}

bool HlaExecutionConfigurationImpl::hasNextExecutionMode() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextExecutionMode();
    return _nextExecutionModeAttribute.hasValue();
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationImpl::getNextExecutionMode() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextExecutionMode();
    if (_nextExecutionModeAttribute.hasValue()) {
        return *_nextExecutionModeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'nextExecutionMode' not set for instance " + getHlaInstanceName());
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationImpl::getNextExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextExecutionMode();
    if (_nextExecutionModeAttribute.hasValue()) {
        return *_nextExecutionModeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > HlaExecutionConfigurationImpl::getNextExecutionModeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextExecutionMode();
    if (_nextExecutionModeAttribute.hasValue()) {
        return _nextExecutionModeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'nextExecutionMode' not set for instance " + getHlaInstanceName());
}

void HlaExecutionConfigurationImpl::updateNextExecutionMode() {
    if (_nextExecutionModeAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _nextExecutionModeAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_executionModeEncoderDecoder.decodeFrom(encodedValue, 0);
            _nextExecutionModeAttribute.setDecodedValue(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode >(new LunarSimulation::ExecutionMode::ExecutionMode(_objectClassManager->_executionModeEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NEXT_EXECUTION_MODE_ATTRIBUTE_NAME: Failed to decode ExecutionMode. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NEXT_EXECUTION_MODE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _nextExecutionModeAttribute.clearEncodedValue();
        }
    }
}

bool HlaExecutionConfigurationImpl::hasNextModeScenarioTime() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeScenarioTime();
    return _nextModeScenarioTimeAttribute.hasValue();
}

double HlaExecutionConfigurationImpl::getNextModeScenarioTime() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeScenarioTime();
    if (_nextModeScenarioTimeAttribute.hasValue()) {
        return *_nextModeScenarioTimeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'nextModeScenarioTime' not set for instance " + getHlaInstanceName());
}

double HlaExecutionConfigurationImpl::getNextModeScenarioTime(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeScenarioTime();
    if (_nextModeScenarioTimeAttribute.hasValue()) {
        return *_nextModeScenarioTimeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaExecutionConfigurationImpl::getNextModeScenarioTimeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeScenarioTime();
    if (_nextModeScenarioTimeAttribute.hasValue()) {
        return _nextModeScenarioTimeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'nextModeScenarioTime' not set for instance " + getHlaInstanceName());
}

void HlaExecutionConfigurationImpl::updateNextModeScenarioTime() {
    if (_nextModeScenarioTimeAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _nextModeScenarioTimeAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAfloat64LEDecoder.decodeFrom(encodedValue, 0);
            _nextModeScenarioTimeAttribute.setDecodedValue(std::shared_ptr<double >(new double(_objectClassManager->_hLAfloat64LEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NEXT_MODE_SCENARIO_TIME_ATTRIBUTE_NAME: Failed to decode Time. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NEXT_MODE_SCENARIO_TIME_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _nextModeScenarioTimeAttribute.clearEncodedValue();
        }
    }
}

bool HlaExecutionConfigurationImpl::hasNextModeCteTime() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeCteTime();
    return _nextModeCteTimeAttribute.hasValue();
}

double HlaExecutionConfigurationImpl::getNextModeCteTime() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeCteTime();
    if (_nextModeCteTimeAttribute.hasValue()) {
        return *_nextModeCteTimeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'nextModeCteTime' not set for instance " + getHlaInstanceName());
}

double HlaExecutionConfigurationImpl::getNextModeCteTime(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeCteTime();
    if (_nextModeCteTimeAttribute.hasValue()) {
        return *_nextModeCteTimeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaExecutionConfigurationImpl::getNextModeCteTimeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateNextModeCteTime();
    if (_nextModeCteTimeAttribute.hasValue()) {
        return _nextModeCteTimeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'nextModeCteTime' not set for instance " + getHlaInstanceName());
}

void HlaExecutionConfigurationImpl::updateNextModeCteTime() {
    if (_nextModeCteTimeAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _nextModeCteTimeAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAfloat64LEDecoder.decodeFrom(encodedValue, 0);
            _nextModeCteTimeAttribute.setDecodedValue(std::shared_ptr<double >(new double(_objectClassManager->_hLAfloat64LEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NEXT_MODE_CTE_TIME_ATTRIBUTE_NAME: Failed to decode Time. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NEXT_MODE_CTE_TIME_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _nextModeCteTimeAttribute.clearEncodedValue();
        }
    }
}

bool HlaExecutionConfigurationImpl::hasLeastCommonTimeStep() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateLeastCommonTimeStep();
    return _leastCommonTimeStepAttribute.hasValue();
}

long long HlaExecutionConfigurationImpl::getLeastCommonTimeStep() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateLeastCommonTimeStep();
    if (_leastCommonTimeStepAttribute.hasValue()) {
        return *_leastCommonTimeStepAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'leastCommonTimeStep' not set for instance " + getHlaInstanceName());
}

long long HlaExecutionConfigurationImpl::getLeastCommonTimeStep(long long defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateLeastCommonTimeStep();
    if (_leastCommonTimeStepAttribute.hasValue()) {
        return *_leastCommonTimeStepAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< long long > HlaExecutionConfigurationImpl::getLeastCommonTimeStepTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateLeastCommonTimeStep();
    if (_leastCommonTimeStepAttribute.hasValue()) {
        return _leastCommonTimeStepAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'leastCommonTimeStep' not set for instance " + getHlaInstanceName());
}

void HlaExecutionConfigurationImpl::updateLeastCommonTimeStep() {
    if (_leastCommonTimeStepAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _leastCommonTimeStepAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAinteger64BEDecoder.decodeFrom(encodedValue, 0);
            _leastCommonTimeStepAttribute.setDecodedValue(std::shared_ptr<long long >(new long long(_objectClassManager->_hLAinteger64BEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode LEAST_COMMON_TIME_STEP_ATTRIBUTE_NAME: Failed to decode HLAinteger64Time. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode LEAST_COMMON_TIME_STEP_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _leastCommonTimeStepAttribute.clearEncodedValue();
        }
    }
}



void HlaExecutionConfigurationImpl::addHlaExecutionConfigurationListener(HlaExecutionConfigurationListenerPtr listener) {
    _executionConfigurationListeners.add(listener);
}

void HlaExecutionConfigurationImpl::removeHlaExecutionConfigurationListener(HlaExecutionConfigurationListenerPtr listener) {
    _executionConfigurationListeners.remove(listener);
}

void HlaExecutionConfigurationImpl::addHlaExecutionConfigurationValueListener(HlaExecutionConfigurationValueListenerPtr valueListener) {
    _executionConfigurationValueListeners.add(valueListener);
}
                    
void HlaExecutionConfigurationImpl::removeHlaExecutionConfigurationValueListener(HlaExecutionConfigurationValueListenerPtr valueListener) {
    _executionConfigurationValueListeners.remove(valueListener);
}


void HlaExecutionConfigurationImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaExecutionConfigurationAttributes::Attribute> attributesUpdated(attributes.size());
    {
       std::lock_guard<std::recursive_mutex> lock(_attributesLock);
       for (RtiDriver::NameValueMap::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
          HlaExecutionConfigurationAttributes::Attribute attribute;
          if (!HlaExecutionConfigurationAttributes::find(attribute, iter->first)) {
             continue;
          }

          switch (attribute) {
             case HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME: {
                attributesUpdated.insert(HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME);

                if (_executionConfigurationValueListeners.empty()) {
                    _rootFrameNameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateRootFrameName();
                   AttributeValue<std::wstring > oldValue(_rootFrameNameAttribute);

                   _rootFrameNameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateRootFrameName();
                   if (_rootFrameNameAttribute.hasValue()) {
                      fireroot_frame_nameUpdated(_rootFrameNameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME, _rootFrameNameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH: {
                attributesUpdated.insert(HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH);

                if (_executionConfigurationValueListeners.empty()) {
                    _scenarioTimeEpochAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateScenarioTimeEpoch();
                   AttributeValue<double > oldValue(_scenarioTimeEpochAttribute);

                   _scenarioTimeEpochAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateScenarioTimeEpoch();
                   if (_scenarioTimeEpochAttribute.hasValue()) {
                      firescenario_time_epochUpdated(_scenarioTimeEpochAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH, _scenarioTimeEpochAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE: {
                attributesUpdated.insert(HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE);

                if (_executionConfigurationValueListeners.empty()) {
                    _currentExecutionModeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateCurrentExecutionMode();
                   AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > oldValue(_currentExecutionModeAttribute);

                   _currentExecutionModeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateCurrentExecutionMode();
                   if (_currentExecutionModeAttribute.hasValue()) {
                      firecurrent_execution_modeUpdated(_currentExecutionModeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE, _currentExecutionModeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE: {
                attributesUpdated.insert(HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE);

                if (_executionConfigurationValueListeners.empty()) {
                    _nextExecutionModeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateNextExecutionMode();
                   AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > oldValue(_nextExecutionModeAttribute);

                   _nextExecutionModeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateNextExecutionMode();
                   if (_nextExecutionModeAttribute.hasValue()) {
                      firenext_execution_modeUpdated(_nextExecutionModeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE, _nextExecutionModeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME: {
                attributesUpdated.insert(HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME);

                if (_executionConfigurationValueListeners.empty()) {
                    _nextModeScenarioTimeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateNextModeScenarioTime();
                   AttributeValue<double > oldValue(_nextModeScenarioTimeAttribute);

                   _nextModeScenarioTimeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateNextModeScenarioTime();
                   if (_nextModeScenarioTimeAttribute.hasValue()) {
                      firenext_mode_scenario_timeUpdated(_nextModeScenarioTimeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME, _nextModeScenarioTimeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME: {
                attributesUpdated.insert(HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME);

                if (_executionConfigurationValueListeners.empty()) {
                    _nextModeCteTimeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateNextModeCteTime();
                   AttributeValue<double > oldValue(_nextModeCteTimeAttribute);

                   _nextModeCteTimeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateNextModeCteTime();
                   if (_nextModeCteTimeAttribute.hasValue()) {
                      firenext_mode_cte_timeUpdated(_nextModeCteTimeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME, _nextModeCteTimeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP: {
                attributesUpdated.insert(HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP);

                if (_executionConfigurationValueListeners.empty()) {
                    _leastCommonTimeStepAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateLeastCommonTimeStep();
                   AttributeValue<long long > oldValue(_leastCommonTimeStepAttribute);

                   _leastCommonTimeStepAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateLeastCommonTimeStep();
                   if (_leastCommonTimeStepAttribute.hasValue()) {
                      fireleast_common_time_stepUpdated(_leastCommonTimeStepAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP, _leastCommonTimeStepAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             default:
                break;
          }
       }
    }

    attributesUpdated.freeze();
    fireAttributesUpdated(attributesUpdated, timeStamp, logicalTime);
}

void HlaExecutionConfigurationImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaExecutionConfigurationAttributesImpl>(getHlaExecutionConfigurationAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaExecutionConfigurationImpl::AttributeMap HlaExecutionConfigurationImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
        if (iter->compare(ROOT_FRAME_NAME_ATTRIBUTE_NAME) == 0) {
            updateRootFrameName();
            if (_rootFrameNameAttribute.hasValue()) {
                res[HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME] = _rootFrameNameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(SCENARIO_TIME_EPOCH_ATTRIBUTE_NAME) == 0) {
            updateScenarioTimeEpoch();
            if (_scenarioTimeEpochAttribute.hasValue()) {
                res[HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH] = _scenarioTimeEpochAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(CURRENT_EXECUTION_MODE_ATTRIBUTE_NAME) == 0) {
            updateCurrentExecutionMode();
            if (_currentExecutionModeAttribute.hasValue()) {
                res[HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE] = _currentExecutionModeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(NEXT_EXECUTION_MODE_ATTRIBUTE_NAME) == 0) {
            updateNextExecutionMode();
            if (_nextExecutionModeAttribute.hasValue()) {
                res[HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE] = _nextExecutionModeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(NEXT_MODE_SCENARIO_TIME_ATTRIBUTE_NAME) == 0) {
            updateNextModeScenarioTime();
            if (_nextModeScenarioTimeAttribute.hasValue()) {
                res[HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME] = _nextModeScenarioTimeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(NEXT_MODE_CTE_TIME_ATTRIBUTE_NAME) == 0) {
            updateNextModeCteTime();
            if (_nextModeCteTimeAttribute.hasValue()) {
                res[HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME] = _nextModeCteTimeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(LEAST_COMMON_TIME_STEP_ATTRIBUTE_NAME) == 0) {
            updateLeastCommonTimeStep();
            if (_leastCommonTimeStepAttribute.hasValue()) {
                res[HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP] = _leastCommonTimeStepAttribute.getValue();
            }
            continue;
        }
    }
    return res;
}

RtiDriver::NameSet HlaExecutionConfigurationImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaExecutionConfigurationAttributesPtr attributes = getHlaExecutionConfigurationAttributes();
    if (!attributes->hasRootFrameName()) {
        res.insert(ROOT_FRAME_NAME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasScenarioTimeEpoch()) {
        res.insert(SCENARIO_TIME_EPOCH_ATTRIBUTE_NAME);
    }
    if (!attributes->hasCurrentExecutionMode()) {
        res.insert(CURRENT_EXECUTION_MODE_ATTRIBUTE_NAME);
    }
    if (!attributes->hasNextExecutionMode()) {
        res.insert(NEXT_EXECUTION_MODE_ATTRIBUTE_NAME);
    }
    if (!attributes->hasNextModeScenarioTime()) {
        res.insert(NEXT_MODE_SCENARIO_TIME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasNextModeCteTime()) {
        res.insert(NEXT_MODE_CTE_TIME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasLeastCommonTimeStep()) {
        res.insert(LEAST_COMMON_TIME_STEP_ATTRIBUTE_NAME);
    }
    return res;
}



HlaFederateIdPtr HlaExecutionConfigurationImpl::getLastProducingFederate(HlaExecutionConfigurationAttributes::Attribute attribute) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    switch (attribute) {
        case HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME: {
            if (_rootFrameNameAttribute.hasFederateId()) {
                return _rootFrameNameAttribute.getFederateId();
            }
            break;
        }
        case HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH: {
            if (_scenarioTimeEpochAttribute.hasFederateId()) {
                return _scenarioTimeEpochAttribute.getFederateId();
            }
            break;
        }
        case HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE: {
            if (_currentExecutionModeAttribute.hasFederateId()) {
                return _currentExecutionModeAttribute.getFederateId();
            }
            break;
        }
        case HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE: {
            if (_nextExecutionModeAttribute.hasFederateId()) {
                return _nextExecutionModeAttribute.getFederateId();
            }
            break;
        }
        case HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME: {
            if (_nextModeScenarioTimeAttribute.hasFederateId()) {
                return _nextModeScenarioTimeAttribute.getFederateId();
            }
            break;
        }
        case HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME: {
            if (_nextModeCteTimeAttribute.hasFederateId()) {
                return _nextModeCteTimeAttribute.getFederateId();
            }
            break;
        }
        case HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP: {
            if (_leastCommonTimeStepAttribute.hasFederateId()) {
                return _leastCommonTimeStepAttribute.getFederateId();
            }
            break;
        }
        default:
            break;
    }
    return HlaFederateIdPtr(new HlaFederateIdImpl());
}
