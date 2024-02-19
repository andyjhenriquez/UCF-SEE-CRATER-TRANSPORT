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

#include "HlaPhysicalInterfaceImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPhysicalInterfaceValueListener.h>
#include "StringUtil.h"
#include "HlaPhysicalInterfaceManagerImpl.h"
#include "HlaPhysicalInterfaceAttributesImpl.h"
#include "HlaPhysicalInterfaceUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;

static const wchar_t NAME_ATTRIBUTE_NAME[] = L"name";
static const wchar_t PARENT_NAME_ATTRIBUTE_NAME[] = L"parent_name";
static const wchar_t POSITION_ATTRIBUTE_NAME[] = L"position";
static const wchar_t ATTITUDE_ATTRIBUTE_NAME[] = L"attitude";

RtiDriver::NameSet HlaPhysicalInterfaceImpl::getAttributes() {
    RtiDriver::NameSet res;
    res.insert(L"name");
    res.insert(L"parent_name");
    res.insert(L"position");
    res.insert(L"attitude");
    return res;
}


bool HlaPhysicalInterfaceImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaPhysicalInterfaceImpl::isWithinInterest() const {
    return !_removed;
}

HlaPhysicalInterfaceAttributesPtr HlaPhysicalInterfaceImpl::getHlaPhysicalInterfaceAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    updateParentName();
    updatePosition();
    updateAttitude();
    return HlaPhysicalInterfaceAttributesPtr(new HlaPhysicalInterfaceAttributesImpl(
        _nameAttribute,
        _parentNameAttribute,
        _positionAttribute,
        _attitudeAttribute
));
}

HlaPhysicalInterfaceUpdaterPtr HlaPhysicalInterfaceImpl::getHlaPhysicalInterfaceUpdater() {
    HlaPhysicalInterfaceUpdater* ptr = new HlaPhysicalInterfaceUpdaterImpl(shared_from_this());
    return HlaPhysicalInterfaceUpdaterPtr(ptr);
}

std::wstring HlaPhysicalInterfaceImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaPhysicalInterfaceImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

HlaFederateIdImplPtr HlaPhysicalInterfaceImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaPhysicalInterfaceUpdaterImpl
*/

void HlaPhysicalInterfaceImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaPhysicalInterfaceAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaPhysicalInterfaceAttributesImplPtr  HlaPhysicalInterfaceImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaPhysicalInterfaceAttributesImplPtr ret;

    HlaEnumSet<HlaPhysicalInterfaceAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        for (AttributeMap::const_iterator iter = attributeUpdate.begin(); iter != attributeUpdate.end(); ++iter) {
                switch (iter->first) {
                    case HlaPhysicalInterfaceAttributes::NAME:
                        {
                            updateName();
                            AttributeValue<std::wstring > oldValue(_nameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _nameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalInterfaceAttributes::NAME);
                        }
                        break;
                    case HlaPhysicalInterfaceAttributes::PARENT_NAME:
                        {
                            updateParentName();
                            AttributeValue<std::wstring > oldValue(_parentNameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _parentNameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireparent_nameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::PARENT_NAME, _parentNameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalInterfaceAttributes::PARENT_NAME);
                        }
                        break;
                    case HlaPhysicalInterfaceAttributes::POSITION:
                        {
                            updatePosition();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_positionAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _positionAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firepositionUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::POSITION, _positionAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalInterfaceAttributes::POSITION);
                        }
                        break;
                    case HlaPhysicalInterfaceAttributes::ATTITUDE:
                        {
                            updateAttitude();
                            AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_attitudeAttribute);

                            std::shared_ptr<LunarSimulation::AttitudeQuaternion > valuePtr =  std::static_pointer_cast<LunarSimulation::AttitudeQuaternion >(iter->second);
                            _attitudeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireattitudeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::ATTITUDE, _attitudeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalInterfaceAttributes::ATTITUDE);
                        }
                        break;
                    default:
                        break;
                }
        }
        ret = std::dynamic_pointer_cast<HlaPhysicalInterfaceAttributesImpl>(getHlaPhysicalInterfaceAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaPhysicalInterfaceImpl::sendAttributes(const AttributeMap& attributeSet, HlaPhysicalInterfaceAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
            switch (iter->first) {

                case HlaPhysicalInterfaceAttributes::NAME:
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
                case HlaPhysicalInterfaceAttributes::PARENT_NAME:
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
                case HlaPhysicalInterfaceAttributes::POSITION:
                    if (attributeValues->hasPosition()) {
                        try {
                            _objectClassManager->_positionVectorEncoderEncoder.set(*(std::vector</* 3 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_positionVectorEncoderEncoder.getEncodedLength());
                            _objectClassManager->_positionVectorEncoderEncoder.encodeInto(res);
                            attributeValueMap[POSITION_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode POSITION_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPhysicalInterfaceAttributes::ATTITUDE:
                    if (attributeValues->hasAttitude()) {
                        try {
                            _objectClassManager->_attitudeQuaternionEncoderEncoder.set(*(LunarSimulation::AttitudeQuaternion*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_attitudeQuaternionEncoderEncoder.getEncodedLength());
                            _objectClassManager->_attitudeQuaternionEncoderEncoder.encodeInto(res);
                            attributeValueMap[ATTITUDE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode ATTITUDE_ATTRIBUTE_NAME: " + e.what()));
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

void HlaPhysicalInterfaceImpl::firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalInterfaceValueListenerPtr> listeners = _physicalInterfaceValueListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalInterfaceValueListener::nameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalInterfaceImpl::fireparent_nameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalInterfaceValueListenerPtr> listeners = _physicalInterfaceValueListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalInterfaceValueListener::parentNameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalInterfaceImpl::firepositionUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalInterfaceValueListenerPtr> listeners = _physicalInterfaceValueListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalInterfaceValueListener::positionUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalInterfaceImpl::fireattitudeUpdated(std::shared_ptr<LunarSimulation::AttitudeQuaternion > value, const AttributeValue<LunarSimulation::AttitudeQuaternion >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::AttitudeQuaternion > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalInterfaceValueListenerPtr> listeners = _physicalInterfaceValueListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalInterfaceValueListener::attitudeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaPhysicalInterfaceImpl::fireAttributesUpdated(const HlaEnumSet<HlaPhysicalInterfaceAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPhysicalInterfaceListenerPtr> listeners = _physicalInterfaceListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalInterfaceListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalInterfaceImpl::fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (oldFederateId && newFederateId && *oldFederateId != *newFederateId) {
        std::set<HlaPhysicalInterfaceValueListenerPtr> listeners = _physicalInterfaceValueListeners.getListeners();
        for (std::set<HlaPhysicalInterfaceValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            std::function<void()> callback = std::bind(&HlaPhysicalInterfaceValueListener::producingFederateUpdated, *it, shared_from_this(), attribute, oldFederateId, newFederateId, timeStamp, logicalTime);
            _hlaWorld->postNotification(callback);
        }
    }
}

bool HlaPhysicalInterfaceImpl::hasName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    return _nameAttribute.hasValue();
}

std::wstring HlaPhysicalInterfaceImpl::getName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPhysicalInterfaceImpl::getName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalInterfaceImpl::getNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return _nameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalInterfaceImpl::updateName() {
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

bool HlaPhysicalInterfaceImpl::hasParentName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    return _parentNameAttribute.hasValue();
}

std::wstring HlaPhysicalInterfaceImpl::getParentName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    if (_parentNameAttribute.hasValue()) {
        return *_parentNameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentName' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPhysicalInterfaceImpl::getParentName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    if (_parentNameAttribute.hasValue()) {
        return *_parentNameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalInterfaceImpl::getParentNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentName();
    if (_parentNameAttribute.hasValue()) {
        return _parentNameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentName' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalInterfaceImpl::updateParentName() {
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

bool HlaPhysicalInterfaceImpl::hasPosition() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    return _positionAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalInterfaceImpl::getPosition() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return *_positionAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'position' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPhysicalInterfaceImpl::getPosition(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return *_positionAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalInterfaceImpl::getPositionTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return _positionAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'position' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalInterfaceImpl::updatePosition() {
    if (_positionAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _positionAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_positionVectorEncoderDecoder.decodeFrom(encodedValue, 0);
            _positionAttribute.setDecodedValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(_objectClassManager->_positionVectorEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode POSITION_ATTRIBUTE_NAME: Failed to decode PositionVector. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode POSITION_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _positionAttribute.clearEncodedValue();
        }
    }
}

bool HlaPhysicalInterfaceImpl::hasAttitude() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAttitude();
    return _attitudeAttribute.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaPhysicalInterfaceImpl::getAttitude() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAttitude();
    if (_attitudeAttribute.hasValue()) {
        return *_attitudeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'attitude' not set for instance " + getHlaInstanceName());
}

LunarSimulation::AttitudeQuaternion HlaPhysicalInterfaceImpl::getAttitude(LunarSimulation::AttitudeQuaternion defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAttitude();
    if (_attitudeAttribute.hasValue()) {
        return *_attitudeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaPhysicalInterfaceImpl::getAttitudeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAttitude();
    if (_attitudeAttribute.hasValue()) {
        return _attitudeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'attitude' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalInterfaceImpl::updateAttitude() {
    if (_attitudeAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _attitudeAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_attitudeQuaternionEncoderDecoder.decodeFrom(encodedValue, 0);
            _attitudeAttribute.setDecodedValue(std::shared_ptr<LunarSimulation::AttitudeQuaternion >(new LunarSimulation::AttitudeQuaternion(_objectClassManager->_attitudeQuaternionEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ATTITUDE_ATTRIBUTE_NAME: Failed to decode AttitudeQuaternion. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ATTITUDE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _attitudeAttribute.clearEncodedValue();
        }
    }
}



void HlaPhysicalInterfaceImpl::addHlaPhysicalInterfaceListener(HlaPhysicalInterfaceListenerPtr listener) {
    _physicalInterfaceListeners.add(listener);
}

void HlaPhysicalInterfaceImpl::removeHlaPhysicalInterfaceListener(HlaPhysicalInterfaceListenerPtr listener) {
    _physicalInterfaceListeners.remove(listener);
}

void HlaPhysicalInterfaceImpl::addHlaPhysicalInterfaceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener) {
    _physicalInterfaceValueListeners.add(valueListener);
}
                    
void HlaPhysicalInterfaceImpl::removeHlaPhysicalInterfaceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener) {
    _physicalInterfaceValueListeners.remove(valueListener);
}


void HlaPhysicalInterfaceImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaPhysicalInterfaceAttributes::Attribute> attributesUpdated(attributes.size());
    {
       std::lock_guard<std::recursive_mutex> lock(_attributesLock);
       for (RtiDriver::NameValueMap::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
          HlaPhysicalInterfaceAttributes::Attribute attribute;
          if (!HlaPhysicalInterfaceAttributes::find(attribute, iter->first)) {
             continue;
          }

          switch (attribute) {
             case HlaPhysicalInterfaceAttributes::NAME: {
                attributesUpdated.insert(HlaPhysicalInterfaceAttributes::NAME);

                if (_physicalInterfaceValueListeners.empty()) {
                    _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateName();
                   AttributeValue<std::wstring > oldValue(_nameAttribute);

                   _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateName();
                   if (_nameAttribute.hasValue()) {
                      firenameUpdated(_nameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalInterfaceAttributes::PARENT_NAME: {
                attributesUpdated.insert(HlaPhysicalInterfaceAttributes::PARENT_NAME);

                if (_physicalInterfaceValueListeners.empty()) {
                    _parentNameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateParentName();
                   AttributeValue<std::wstring > oldValue(_parentNameAttribute);

                   _parentNameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateParentName();
                   if (_parentNameAttribute.hasValue()) {
                      fireparent_nameUpdated(_parentNameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::PARENT_NAME, _parentNameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalInterfaceAttributes::POSITION: {
                attributesUpdated.insert(HlaPhysicalInterfaceAttributes::POSITION);

                if (_physicalInterfaceValueListeners.empty()) {
                    _positionAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updatePosition();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_positionAttribute);

                   _positionAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updatePosition();
                   if (_positionAttribute.hasValue()) {
                      firepositionUpdated(_positionAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::POSITION, _positionAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalInterfaceAttributes::ATTITUDE: {
                attributesUpdated.insert(HlaPhysicalInterfaceAttributes::ATTITUDE);

                if (_physicalInterfaceValueListeners.empty()) {
                    _attitudeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateAttitude();
                   AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_attitudeAttribute);

                   _attitudeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateAttitude();
                   if (_attitudeAttribute.hasValue()) {
                      fireattitudeUpdated(_attitudeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalInterfaceAttributes::ATTITUDE, _attitudeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
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

void HlaPhysicalInterfaceImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaPhysicalInterfaceAttributesImpl>(getHlaPhysicalInterfaceAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaPhysicalInterfaceImpl::AttributeMap HlaPhysicalInterfaceImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
        if (iter->compare(NAME_ATTRIBUTE_NAME) == 0) {
            updateName();
            if (_nameAttribute.hasValue()) {
                res[HlaPhysicalInterfaceAttributes::NAME] = _nameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(PARENT_NAME_ATTRIBUTE_NAME) == 0) {
            updateParentName();
            if (_parentNameAttribute.hasValue()) {
                res[HlaPhysicalInterfaceAttributes::PARENT_NAME] = _parentNameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(POSITION_ATTRIBUTE_NAME) == 0) {
            updatePosition();
            if (_positionAttribute.hasValue()) {
                res[HlaPhysicalInterfaceAttributes::POSITION] = _positionAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ATTITUDE_ATTRIBUTE_NAME) == 0) {
            updateAttitude();
            if (_attitudeAttribute.hasValue()) {
                res[HlaPhysicalInterfaceAttributes::ATTITUDE] = _attitudeAttribute.getValue();
            }
            continue;
        }
    }
    return res;
}

RtiDriver::NameSet HlaPhysicalInterfaceImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaPhysicalInterfaceAttributesPtr attributes = getHlaPhysicalInterfaceAttributes();
    if (!attributes->hasName()) {
        res.insert(NAME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasParentName()) {
        res.insert(PARENT_NAME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasPosition()) {
        res.insert(POSITION_ATTRIBUTE_NAME);
    }
    if (!attributes->hasAttitude()) {
        res.insert(ATTITUDE_ATTRIBUTE_NAME);
    }
    return res;
}



HlaFederateIdPtr HlaPhysicalInterfaceImpl::getLastProducingFederate(HlaPhysicalInterfaceAttributes::Attribute attribute) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    switch (attribute) {
        case HlaPhysicalInterfaceAttributes::NAME: {
            if (_nameAttribute.hasFederateId()) {
                return _nameAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalInterfaceAttributes::PARENT_NAME: {
            if (_parentNameAttribute.hasFederateId()) {
                return _parentNameAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalInterfaceAttributes::POSITION: {
            if (_positionAttribute.hasFederateId()) {
                return _positionAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalInterfaceAttributes::ATTITUDE: {
            if (_attitudeAttribute.hasFederateId()) {
                return _attitudeAttribute.getFederateId();
            }
            break;
        }
        default:
            break;
    }
    return HlaFederateIdPtr(new HlaFederateIdImpl());
}
