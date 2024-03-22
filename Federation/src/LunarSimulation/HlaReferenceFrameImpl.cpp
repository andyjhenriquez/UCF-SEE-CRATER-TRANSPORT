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

#include "HlaReferenceFrameImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaReferenceFrameValueListener.h>
#include "StringUtil.h"
#include "HlaReferenceFrameManagerImpl.h"
#include "HlaReferenceFrameAttributesImpl.h"
#include "HlaReferenceFrameUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;

static const wchar_t NAME_ATTRIBUTE_NAME[] = L"name";
static const wchar_t PARENT_NAME_ATTRIBUTE_NAME[] = L"parent_name";
static const wchar_t STATE_ATTRIBUTE_NAME[] = L"state";

RtiDriver::NameSet HlaReferenceFrameImpl::getAttributes() {
    RtiDriver::NameSet res;
    res.insert(L"name");
    res.insert(L"parent_name");
    res.insert(L"state");
    return res;
}


bool HlaReferenceFrameImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaReferenceFrameImpl::isWithinInterest() const {
    return !_removed;
}

HlaReferenceFrameAttributesPtr HlaReferenceFrameImpl::getHlaReferenceFrameAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    updateParentName();
    updateState();
    return HlaReferenceFrameAttributesPtr(new HlaReferenceFrameAttributesImpl(
        _nameAttribute,
        _parentNameAttribute,
        _stateAttribute
));
}

HlaReferenceFrameUpdaterPtr HlaReferenceFrameImpl::getHlaReferenceFrameUpdater() {
    HlaReferenceFrameUpdater* ptr = new HlaReferenceFrameUpdaterImpl(shared_from_this());
    return HlaReferenceFrameUpdaterPtr(ptr);
}

std::wstring HlaReferenceFrameImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaReferenceFrameImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

void HlaReferenceFrameImpl::setCreateAttributes(
        std::shared_ptr<std::wstring > name,
        HlaTimeStampPtr timeStamp) {
    HlaReferenceFrameImpl::AttributeMap attributeUpdates;
    attributeUpdates[HlaReferenceFrameAttributes::NAME] = name;
    try {
        HlaLogicalTimeImplPtr logicalTime = HlaLogicalTimeImpl::getInvalid();
        applyUpdate(attributeUpdates, timeStamp, logicalTime);
    } catch (HlaException &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Failed to set create attributes in HlaReferenceFrameImpl" + e.what_w()));
        _hlaWorld->postException(ex);
    }
}

HlaFederateIdImplPtr HlaReferenceFrameImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaReferenceFrameUpdaterImpl
*/

void HlaReferenceFrameImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaReferenceFrameAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaReferenceFrameAttributesImplPtr  HlaReferenceFrameImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaReferenceFrameAttributesImplPtr ret;

    HlaEnumSet<HlaReferenceFrameAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        for (AttributeMap::const_iterator iter = attributeUpdate.begin(); iter != attributeUpdate.end(); ++iter) {
                switch (iter->first) {
                    case HlaReferenceFrameAttributes::NAME:
                        {
                            updateName();
                            AttributeValue<std::wstring > oldValue(_nameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _nameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaReferenceFrameAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaReferenceFrameAttributes::NAME);
                        }
                        break;
                    case HlaReferenceFrameAttributes::PARENT_NAME:
                        {
                            updateParentName();
                            AttributeValue<std::wstring > oldValue(_parentNameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _parentNameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireparent_nameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaReferenceFrameAttributes::PARENT_NAME, _parentNameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaReferenceFrameAttributes::PARENT_NAME);
                        }
                        break;
                    case HlaReferenceFrameAttributes::STATE:
                        {
                            updateState();
                            AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                            std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > valuePtr =  std::static_pointer_cast<LunarSimulation::SpaceTimeCoordinateState >(iter->second);
                            _stateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaReferenceFrameAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaReferenceFrameAttributes::STATE);
                        }
                        break;
                    default:
                        break;
                }
        }
        ret = std::dynamic_pointer_cast<HlaReferenceFrameAttributesImpl>(getHlaReferenceFrameAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaReferenceFrameImpl::sendAttributes(const AttributeMap& attributeSet, HlaReferenceFrameAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
            switch (iter->first) {

                case HlaReferenceFrameAttributes::NAME:
                    if (attributeValues->hasName()) {
                        try {
                            _objectClassManager->_hLAunicodeStringEncoder.set(*(std::wstring*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_hLAunicodeStringEncoder.getEncodedLength());
                            _objectClassManager->_hLAunicodeStringEncoder.encodeInto(res);
                            attributeValueMap[NAME_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode NAME_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaReferenceFrameAttributes::PARENT_NAME:
                    if (attributeValues->hasParentName()) {
                        try {
                            _objectClassManager->_hLAunicodeStringEncoder.set(*(std::wstring*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_hLAunicodeStringEncoder.getEncodedLength());
                            _objectClassManager->_hLAunicodeStringEncoder.encodeInto(res);
                            attributeValueMap[PARENT_NAME_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode PARENT_NAME_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaReferenceFrameAttributes::STATE:
                    if (attributeValues->hasState()) {
                        try {
                            _objectClassManager->_spaceTimeCoordinateStateEncoderEncoder.set(*(LunarSimulation::SpaceTimeCoordinateState*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_spaceTimeCoordinateStateEncoderEncoder.getEncodedLength());
                            _objectClassManager->_spaceTimeCoordinateStateEncoderEncoder.encodeInto(res);
                            attributeValueMap[STATE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode STATE_ATTRIBUTE_NAME: " + e.what()));
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

void HlaReferenceFrameImpl::firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaReferenceFrameValueListenerPtr> listeners = _referenceFrameValueListeners.getListeners();
    for (std::set<HlaReferenceFrameValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaReferenceFrameValueListener::nameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaReferenceFrameImpl::fireparent_nameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaReferenceFrameValueListenerPtr> listeners = _referenceFrameValueListeners.getListeners();
    for (std::set<HlaReferenceFrameValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaReferenceFrameValueListener::parentNameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaReferenceFrameImpl::firestateUpdated(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > value, const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaReferenceFrameValueListenerPtr> listeners = _referenceFrameValueListeners.getListeners();
    for (std::set<HlaReferenceFrameValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaReferenceFrameValueListener::stateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaReferenceFrameImpl::fireAttributesUpdated(const HlaEnumSet<HlaReferenceFrameAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaReferenceFrameListenerPtr> listeners = _referenceFrameListeners.getListeners();
    for (std::set<HlaReferenceFrameListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaReferenceFrameListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaReferenceFrameImpl::fireProducingFederateUpdated(HlaReferenceFrameAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (oldFederateId && newFederateId && *oldFederateId != *newFederateId) {
        std::set<HlaReferenceFrameValueListenerPtr> listeners = _referenceFrameValueListeners.getListeners();
        for (std::set<HlaReferenceFrameValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            std::function<void()> callback = std::bind(&HlaReferenceFrameValueListener::producingFederateUpdated, *it, shared_from_this(), attribute, oldFederateId, newFederateId, timeStamp, logicalTime);
            _hlaWorld->postNotification(callback);
        }
    }
}

bool HlaReferenceFrameImpl::hasName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    return _nameAttribute.hasValue();
}

std::wstring HlaReferenceFrameImpl::getName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

std::wstring HlaReferenceFrameImpl::getName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaReferenceFrameImpl::getNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return _nameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

void HlaReferenceFrameImpl::updateName() {
    if (_nameAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _nameAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAunicodeStringDecoder.decodeFrom(encodedValue, 0);
            _nameAttribute.setDecodedValue(std::shared_ptr<std::wstring >(new std::wstring(_objectClassManager->_hLAunicodeStringDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NAME_ATTRIBUTE_NAME: Failed to decode HLAunicodeString. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode NAME_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _nameAttribute.clearEncodedValue();
        }
    }
}

bool HlaReferenceFrameImpl::hasParentName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    return _parentNameAttribute.hasValue();
}

std::wstring HlaReferenceFrameImpl::getParentName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    if (_parentNameAttribute.hasValue()) {
        return *_parentNameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentName' not set for instance " + getHlaInstanceName());
}

std::wstring HlaReferenceFrameImpl::getParentName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    if (_parentNameAttribute.hasValue()) {
        return *_parentNameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaReferenceFrameImpl::getParentNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    if (_parentNameAttribute.hasValue()) {
        return _parentNameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentName' not set for instance " + getHlaInstanceName());
}

void HlaReferenceFrameImpl::updateParentName() {
    if (_parentNameAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _parentNameAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAunicodeStringDecoder.decodeFrom(encodedValue, 0);
            _parentNameAttribute.setDecodedValue(std::shared_ptr<std::wstring >(new std::wstring(_objectClassManager->_hLAunicodeStringDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode PARENT_NAME_ATTRIBUTE_NAME: Failed to decode HLAunicodeString. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode PARENT_NAME_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _parentNameAttribute.clearEncodedValue();
        }
    }
}

bool HlaReferenceFrameImpl::hasState() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    return _stateAttribute.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaReferenceFrameImpl::getState() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

LunarSimulation::SpaceTimeCoordinateState HlaReferenceFrameImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaReferenceFrameImpl::getStateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return _stateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

void HlaReferenceFrameImpl::updateState() {
    if (_stateAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _stateAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_spaceTimeCoordinateStateEncoderDecoder.decodeFrom(encodedValue, 0);
            _stateAttribute.setDecodedValue(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState >(new LunarSimulation::SpaceTimeCoordinateState(_objectClassManager->_spaceTimeCoordinateStateEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode STATE_ATTRIBUTE_NAME: Failed to decode SpaceTimeCoordinateState. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode STATE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _stateAttribute.clearEncodedValue();
        }
    }
}



void HlaReferenceFrameImpl::addHlaReferenceFrameListener(HlaReferenceFrameListenerPtr listener) {
    _referenceFrameListeners.add(listener);
}

void HlaReferenceFrameImpl::removeHlaReferenceFrameListener(HlaReferenceFrameListenerPtr listener) {
    _referenceFrameListeners.remove(listener);
}

void HlaReferenceFrameImpl::addHlaReferenceFrameValueListener(HlaReferenceFrameValueListenerPtr valueListener) {
    _referenceFrameValueListeners.add(valueListener);
}
                    
void HlaReferenceFrameImpl::removeHlaReferenceFrameValueListener(HlaReferenceFrameValueListenerPtr valueListener) {
    _referenceFrameValueListeners.remove(valueListener);
}


void HlaReferenceFrameImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaReferenceFrameAttributes::Attribute> attributesUpdated(attributes.size());
    {
       std::lock_guard<std::recursive_mutex> lock(_attributesLock);
       for (RtiDriver::NameValueMap::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
          HlaReferenceFrameAttributes::Attribute attribute;
          if (!HlaReferenceFrameAttributes::find(attribute, iter->first)) {
             continue;
          }

          switch (attribute) {
             case HlaReferenceFrameAttributes::NAME: {
                attributesUpdated.insert(HlaReferenceFrameAttributes::NAME);

                if (_referenceFrameValueListeners.empty()) {
                    _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateName();
                   AttributeValue<std::wstring > oldValue(_nameAttribute);

                   _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateName();
                   if (_nameAttribute.hasValue()) {
                      firenameUpdated(_nameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaReferenceFrameAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaReferenceFrameAttributes::PARENT_NAME: {
                attributesUpdated.insert(HlaReferenceFrameAttributes::PARENT_NAME);

                if (_referenceFrameValueListeners.empty()) {
                    _parentNameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateParentName();
                   AttributeValue<std::wstring > oldValue(_parentNameAttribute);

                   _parentNameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateParentName();
                   if (_parentNameAttribute.hasValue()) {
                      fireparent_nameUpdated(_parentNameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaReferenceFrameAttributes::PARENT_NAME, _parentNameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaReferenceFrameAttributes::STATE: {
                attributesUpdated.insert(HlaReferenceFrameAttributes::STATE);

                if (_referenceFrameValueListeners.empty()) {
                    _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateState();
                   AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                   _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateState();
                   if (_stateAttribute.hasValue()) {
                      firestateUpdated(_stateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaReferenceFrameAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
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

void HlaReferenceFrameImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaReferenceFrameAttributesImpl>(getHlaReferenceFrameAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaReferenceFrameImpl::AttributeMap HlaReferenceFrameImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
        if (iter->compare(NAME_ATTRIBUTE_NAME) == 0) {
            updateName();
            if (_nameAttribute.hasValue()) {
                res[HlaReferenceFrameAttributes::NAME] = _nameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(PARENT_NAME_ATTRIBUTE_NAME) == 0) {
            updateParentName();
            if (_parentNameAttribute.hasValue()) {
                res[HlaReferenceFrameAttributes::PARENT_NAME] = _parentNameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATE_ATTRIBUTE_NAME) == 0) {
            updateState();
            if (_stateAttribute.hasValue()) {
                res[HlaReferenceFrameAttributes::STATE] = _stateAttribute.getValue();
            }
            continue;
        }
    }
    return res;
}

RtiDriver::NameSet HlaReferenceFrameImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaReferenceFrameAttributesPtr attributes = getHlaReferenceFrameAttributes();
    if (!attributes->hasName()) {
        res.insert(NAME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasParentName()) {
        res.insert(PARENT_NAME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasState()) {
        res.insert(STATE_ATTRIBUTE_NAME);
    }
    return res;
}



HlaFederateIdPtr HlaReferenceFrameImpl::getLastProducingFederate(HlaReferenceFrameAttributes::Attribute attribute) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    switch (attribute) {
        case HlaReferenceFrameAttributes::NAME: {
            if (_nameAttribute.hasFederateId()) {
                return _nameAttribute.getFederateId();
            }
            break;
        }
        case HlaReferenceFrameAttributes::PARENT_NAME: {
            if (_parentNameAttribute.hasFederateId()) {
                return _parentNameAttribute.getFederateId();
            }
            break;
        }
        case HlaReferenceFrameAttributes::STATE: {
            if (_stateAttribute.hasFederateId()) {
                return _stateAttribute.getFederateId();
            }
            break;
        }
        default:
            break;
    }
    return HlaFederateIdPtr(new HlaFederateIdImpl());
}
