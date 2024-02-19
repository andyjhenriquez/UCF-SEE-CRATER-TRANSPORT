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

#include "HlaPhysicalEntityImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPhysicalEntityValueListener.h>
#include "StringUtil.h"
#include "HlaPhysicalEntityManagerImpl.h"
#include "HlaPhysicalEntityAttributesImpl.h"
#include "HlaPhysicalEntityUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;

static const wchar_t NAME_ATTRIBUTE_NAME[] = L"name";
static const wchar_t TYPE_ATTRIBUTE_NAME[] = L"type";
static const wchar_t STATUS_ATTRIBUTE_NAME[] = L"status";
static const wchar_t PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME[] = L"parent_reference_frame";
static const wchar_t STATE_ATTRIBUTE_NAME[] = L"state";
static const wchar_t ACCELERATION_ATTRIBUTE_NAME[] = L"acceleration";
static const wchar_t ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME[] = L"rotational_acceleration";
static const wchar_t CENTER_OF_MASS_ATTRIBUTE_NAME[] = L"center_of_mass";
static const wchar_t BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME[] = L"body_wrt_structural";

RtiDriver::NameSet HlaPhysicalEntityImpl::getAttributes() {
    RtiDriver::NameSet res;
    res.insert(L"name");
    res.insert(L"type");
    res.insert(L"status");
    res.insert(L"parent_reference_frame");
    res.insert(L"state");
    res.insert(L"acceleration");
    res.insert(L"rotational_acceleration");
    res.insert(L"center_of_mass");
    res.insert(L"body_wrt_structural");
    return res;
}


bool HlaPhysicalEntityImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaPhysicalEntityImpl::isWithinInterest() const {
    return !_removed;
}

HlaPhysicalEntityAttributesPtr HlaPhysicalEntityImpl::getHlaPhysicalEntityAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    updateType();
    updateStatus();
    updateParentReferenceFrame();
    updateState();
    updateAcceleration();
    updateRotationalAcceleration();
    updateCenterOfMass();
    updateBodyWrtStructural();
    return HlaPhysicalEntityAttributesPtr(new HlaPhysicalEntityAttributesImpl(
        _nameAttribute,
        _typeAttribute,
        _statusAttribute,
        _parentReferenceFrameAttribute,
        _stateAttribute,
        _accelerationAttribute,
        _rotationalAccelerationAttribute,
        _centerOfMassAttribute,
        _bodyWrtStructuralAttribute
));
}

HlaPhysicalEntityUpdaterPtr HlaPhysicalEntityImpl::getHlaPhysicalEntityUpdater() {
    HlaPhysicalEntityUpdater* ptr = new HlaPhysicalEntityUpdaterImpl(shared_from_this());
    return HlaPhysicalEntityUpdaterPtr(ptr);
}

std::wstring HlaPhysicalEntityImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaPhysicalEntityImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

HlaFederateIdImplPtr HlaPhysicalEntityImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaPhysicalEntityUpdaterImpl
*/

void HlaPhysicalEntityImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaPhysicalEntityAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaPhysicalEntityAttributesImplPtr  HlaPhysicalEntityImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaPhysicalEntityAttributesImplPtr ret;

    HlaEnumSet<HlaPhysicalEntityAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        for (AttributeMap::const_iterator iter = attributeUpdate.begin(); iter != attributeUpdate.end(); ++iter) {
                switch (iter->first) {
                    case HlaPhysicalEntityAttributes::NAME:
                        {
                            updateName();
                            AttributeValue<std::wstring > oldValue(_nameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _nameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::NAME);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::TYPE:
                        {
                            updateType();
                            AttributeValue<std::wstring > oldValue(_typeAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _typeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firetypeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::TYPE);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::STATUS:
                        {
                            updateStatus();
                            AttributeValue<std::wstring > oldValue(_statusAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _statusAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestatusUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::STATUS);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME:
                        {
                            updateParentReferenceFrame();
                            AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _parentReferenceFrameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireparent_reference_frameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::STATE:
                        {
                            updateState();
                            AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                            std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > valuePtr =  std::static_pointer_cast<LunarSimulation::SpaceTimeCoordinateState >(iter->second);
                            _stateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::STATE);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::ACCELERATION:
                        {
                            updateAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _accelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireaccelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::ACCELERATION);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION:
                        {
                            updateRotationalAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _rotationalAccelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firerotational_accelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::CENTER_OF_MASS:
                        {
                            updateCenterOfMass();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _centerOfMassAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firecenter_of_massUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::CENTER_OF_MASS);
                        }
                        break;
                    case HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL:
                        {
                            updateBodyWrtStructural();
                            AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                            std::shared_ptr<LunarSimulation::AttitudeQuaternion > valuePtr =  std::static_pointer_cast<LunarSimulation::AttitudeQuaternion >(iter->second);
                            _bodyWrtStructuralAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firebody_wrt_structuralUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL);
                        }
                        break;
                    default:
                        break;
                }
        }
        ret = std::dynamic_pointer_cast<HlaPhysicalEntityAttributesImpl>(getHlaPhysicalEntityAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaPhysicalEntityImpl::sendAttributes(const AttributeMap& attributeSet, HlaPhysicalEntityAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
            switch (iter->first) {

                case HlaPhysicalEntityAttributes::NAME:
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
                case HlaPhysicalEntityAttributes::TYPE:
                    if (attributeValues->hasType()) {
                        try {
                            _objectClassManager->_hLAunicodeStringEncoder.set(*(std::wstring*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_hLAunicodeStringEncoder.getEncodedLength());
                            _objectClassManager->_hLAunicodeStringEncoder.encodeInto(res);
                            attributeValueMap[TYPE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode TYPE_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPhysicalEntityAttributes::STATUS:
                    if (attributeValues->hasStatus()) {
                        try {
                            _objectClassManager->_hLAunicodeStringEncoder.set(*(std::wstring*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_hLAunicodeStringEncoder.getEncodedLength());
                            _objectClassManager->_hLAunicodeStringEncoder.encodeInto(res);
                            attributeValueMap[STATUS_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode STATUS_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME:
                    if (attributeValues->hasParentReferenceFrame()) {
                        try {
                            _objectClassManager->_hLAunicodeStringEncoder.set(*(std::wstring*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_hLAunicodeStringEncoder.getEncodedLength());
                            _objectClassManager->_hLAunicodeStringEncoder.encodeInto(res);
                            attributeValueMap[PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPhysicalEntityAttributes::STATE:
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
                case HlaPhysicalEntityAttributes::ACCELERATION:
                    if (attributeValues->hasAcceleration()) {
                        try {
                            _objectClassManager->_accelerationVectorEncoderEncoder.set(*(std::vector</* 3 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_accelerationVectorEncoderEncoder.getEncodedLength());
                            _objectClassManager->_accelerationVectorEncoderEncoder.encodeInto(res);
                            attributeValueMap[ACCELERATION_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode ACCELERATION_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION:
                    if (attributeValues->hasRotationalAcceleration()) {
                        try {
                            _objectClassManager->_angularAccelerationVectorEncoderEncoder.set(*(std::vector</* 3 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_angularAccelerationVectorEncoderEncoder.getEncodedLength());
                            _objectClassManager->_angularAccelerationVectorEncoderEncoder.encodeInto(res);
                            attributeValueMap[ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPhysicalEntityAttributes::CENTER_OF_MASS:
                    if (attributeValues->hasCenterOfMass()) {
                        try {
                            _objectClassManager->_positionVectorEncoderEncoder.set(*(std::vector</* 3 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_positionVectorEncoderEncoder.getEncodedLength());
                            _objectClassManager->_positionVectorEncoderEncoder.encodeInto(res);
                            attributeValueMap[CENTER_OF_MASS_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode CENTER_OF_MASS_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL:
                    if (attributeValues->hasBodyWrtStructural()) {
                        try {
                            _objectClassManager->_attitudeQuaternionEncoderEncoder.set(*(LunarSimulation::AttitudeQuaternion*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_attitudeQuaternionEncoderEncoder.getEncodedLength());
                            _objectClassManager->_attitudeQuaternionEncoderEncoder.encodeInto(res);
                            attributeValueMap[BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME: " + e.what()));
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

void HlaPhysicalEntityImpl::firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::nameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::firetypeUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::typeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::firestatusUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::statusUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::fireparent_reference_frameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::parentReferenceFrameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::firestateUpdated(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > value, const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::stateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::fireaccelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::accelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::firerotational_accelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::rotationalAccelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::firecenter_of_massUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::centerOfMassUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::firebody_wrt_structuralUpdated(std::shared_ptr<LunarSimulation::AttitudeQuaternion > value, const AttributeValue<LunarSimulation::AttitudeQuaternion >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::AttitudeQuaternion > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::bodyWrtStructuralUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaPhysicalEntityImpl::fireAttributesUpdated(const HlaEnumSet<HlaPhysicalEntityAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPhysicalEntityListenerPtr> listeners = _physicalEntityListeners.getListeners();
    for (std::set<HlaPhysicalEntityListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityImpl::fireProducingFederateUpdated(HlaPhysicalEntityAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (oldFederateId && newFederateId && *oldFederateId != *newFederateId) {
        std::set<HlaPhysicalEntityValueListenerPtr> listeners = _physicalEntityValueListeners.getListeners();
        for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            std::function<void()> callback = std::bind(&HlaPhysicalEntityValueListener::producingFederateUpdated, *it, shared_from_this(), attribute, oldFederateId, newFederateId, timeStamp, logicalTime);
            _hlaWorld->postNotification(callback);
        }
    }
}

bool HlaPhysicalEntityImpl::hasName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    return _nameAttribute.hasValue();
}

std::wstring HlaPhysicalEntityImpl::getName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPhysicalEntityImpl::getName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityImpl::getNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return _nameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateName() {
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

bool HlaPhysicalEntityImpl::hasType() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    return _typeAttribute.hasValue();
}

std::wstring HlaPhysicalEntityImpl::getType() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPhysicalEntityImpl::getType(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityImpl::getTypeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return _typeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateType() {
    if (_typeAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _typeAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAunicodeStringDecoder.decodeFrom(encodedValue, 0);
            _typeAttribute.setDecodedValue(std::shared_ptr<std::wstring >(new std::wstring(_objectClassManager->_hLAunicodeStringDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode TYPE_ATTRIBUTE_NAME: Failed to decode HLAunicodeString. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode TYPE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _typeAttribute.clearEncodedValue();
        }
    }
}

bool HlaPhysicalEntityImpl::hasStatus() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    return _statusAttribute.hasValue();
}

std::wstring HlaPhysicalEntityImpl::getStatus() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPhysicalEntityImpl::getStatus(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityImpl::getStatusTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return _statusAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateStatus() {
    if (_statusAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _statusAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAunicodeStringDecoder.decodeFrom(encodedValue, 0);
            _statusAttribute.setDecodedValue(std::shared_ptr<std::wstring >(new std::wstring(_objectClassManager->_hLAunicodeStringDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode STATUS_ATTRIBUTE_NAME: Failed to decode HLAunicodeString. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode STATUS_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _statusAttribute.clearEncodedValue();
        }
    }
}

bool HlaPhysicalEntityImpl::hasParentReferenceFrame() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    return _parentReferenceFrameAttribute.hasValue();
}

std::wstring HlaPhysicalEntityImpl::getParentReferenceFrame() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPhysicalEntityImpl::getParentReferenceFrame(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityImpl::getParentReferenceFrameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return _parentReferenceFrameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateParentReferenceFrame() {
    if (_parentReferenceFrameAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _parentReferenceFrameAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAunicodeStringDecoder.decodeFrom(encodedValue, 0);
            _parentReferenceFrameAttribute.setDecodedValue(std::shared_ptr<std::wstring >(new std::wstring(_objectClassManager->_hLAunicodeStringDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME: Failed to decode HLAunicodeString. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _parentReferenceFrameAttribute.clearEncodedValue();
        }
    }
}

bool HlaPhysicalEntityImpl::hasState() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    return _stateAttribute.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaPhysicalEntityImpl::getState() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

LunarSimulation::SpaceTimeCoordinateState HlaPhysicalEntityImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaPhysicalEntityImpl::getStateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return _stateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateState() {
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

bool HlaPhysicalEntityImpl::hasAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    return _accelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalEntityImpl::getAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPhysicalEntityImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalEntityImpl::getAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return _accelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateAcceleration() {
    if (_accelerationAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _accelerationAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_accelerationVectorEncoderDecoder.decodeFrom(encodedValue, 0);
            _accelerationAttribute.setDecodedValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(_objectClassManager->_accelerationVectorEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ACCELERATION_ATTRIBUTE_NAME: Failed to decode AccelerationVector. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ACCELERATION_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _accelerationAttribute.clearEncodedValue();
        }
    }
}

bool HlaPhysicalEntityImpl::hasRotationalAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    return _rotationalAccelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalEntityImpl::getRotationalAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPhysicalEntityImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalEntityImpl::getRotationalAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return _rotationalAccelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateRotationalAcceleration() {
    if (_rotationalAccelerationAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _rotationalAccelerationAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_angularAccelerationVectorEncoderDecoder.decodeFrom(encodedValue, 0);
            _rotationalAccelerationAttribute.setDecodedValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(_objectClassManager->_angularAccelerationVectorEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME: Failed to decode AngularAccelerationVector. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _rotationalAccelerationAttribute.clearEncodedValue();
        }
    }
}

bool HlaPhysicalEntityImpl::hasCenterOfMass() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    return _centerOfMassAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalEntityImpl::getCenterOfMass() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPhysicalEntityImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalEntityImpl::getCenterOfMassTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return _centerOfMassAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateCenterOfMass() {
    if (_centerOfMassAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _centerOfMassAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_positionVectorEncoderDecoder.decodeFrom(encodedValue, 0);
            _centerOfMassAttribute.setDecodedValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(_objectClassManager->_positionVectorEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode CENTER_OF_MASS_ATTRIBUTE_NAME: Failed to decode PositionVector. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode CENTER_OF_MASS_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _centerOfMassAttribute.clearEncodedValue();
        }
    }
}

bool HlaPhysicalEntityImpl::hasBodyWrtStructural() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    return _bodyWrtStructuralAttribute.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaPhysicalEntityImpl::getBodyWrtStructural() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

LunarSimulation::AttitudeQuaternion HlaPhysicalEntityImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaPhysicalEntityImpl::getBodyWrtStructuralTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return _bodyWrtStructuralAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

void HlaPhysicalEntityImpl::updateBodyWrtStructural() {
    if (_bodyWrtStructuralAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _bodyWrtStructuralAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_attitudeQuaternionEncoderDecoder.decodeFrom(encodedValue, 0);
            _bodyWrtStructuralAttribute.setDecodedValue(std::shared_ptr<LunarSimulation::AttitudeQuaternion >(new LunarSimulation::AttitudeQuaternion(_objectClassManager->_attitudeQuaternionEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME: Failed to decode AttitudeQuaternion. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _bodyWrtStructuralAttribute.clearEncodedValue();
        }
    }
}



void HlaPhysicalEntityImpl::addHlaPhysicalEntityListener(HlaPhysicalEntityListenerPtr listener) {
    _physicalEntityListeners.add(listener);
}

void HlaPhysicalEntityImpl::removeHlaPhysicalEntityListener(HlaPhysicalEntityListenerPtr listener) {
    _physicalEntityListeners.remove(listener);
}

void HlaPhysicalEntityImpl::addHlaPhysicalEntityValueListener(HlaPhysicalEntityValueListenerPtr valueListener) {
    _physicalEntityValueListeners.add(valueListener);
}
                    
void HlaPhysicalEntityImpl::removeHlaPhysicalEntityValueListener(HlaPhysicalEntityValueListenerPtr valueListener) {
    _physicalEntityValueListeners.remove(valueListener);
}


void HlaPhysicalEntityImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaPhysicalEntityAttributes::Attribute> attributesUpdated(attributes.size());
    {
       std::lock_guard<std::recursive_mutex> lock(_attributesLock);
       for (RtiDriver::NameValueMap::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
          HlaPhysicalEntityAttributes::Attribute attribute;
          if (!HlaPhysicalEntityAttributes::find(attribute, iter->first)) {
             continue;
          }

          switch (attribute) {
             case HlaPhysicalEntityAttributes::NAME: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::NAME);

                if (_physicalEntityValueListeners.empty()) {
                    _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateName();
                   AttributeValue<std::wstring > oldValue(_nameAttribute);

                   _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateName();
                   if (_nameAttribute.hasValue()) {
                      firenameUpdated(_nameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::TYPE: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::TYPE);

                if (_physicalEntityValueListeners.empty()) {
                    _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateType();
                   AttributeValue<std::wstring > oldValue(_typeAttribute);

                   _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateType();
                   if (_typeAttribute.hasValue()) {
                      firetypeUpdated(_typeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::STATUS: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::STATUS);

                if (_physicalEntityValueListeners.empty()) {
                    _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateStatus();
                   AttributeValue<std::wstring > oldValue(_statusAttribute);

                   _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateStatus();
                   if (_statusAttribute.hasValue()) {
                      firestatusUpdated(_statusAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME);

                if (_physicalEntityValueListeners.empty()) {
                    _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateParentReferenceFrame();
                   AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                   _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateParentReferenceFrame();
                   if (_parentReferenceFrameAttribute.hasValue()) {
                      fireparent_reference_frameUpdated(_parentReferenceFrameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::STATE: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::STATE);

                if (_physicalEntityValueListeners.empty()) {
                    _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateState();
                   AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                   _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateState();
                   if (_stateAttribute.hasValue()) {
                      firestateUpdated(_stateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::ACCELERATION: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::ACCELERATION);

                if (_physicalEntityValueListeners.empty()) {
                    _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                   _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateAcceleration();
                   if (_accelerationAttribute.hasValue()) {
                      fireaccelerationUpdated(_accelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION);

                if (_physicalEntityValueListeners.empty()) {
                    _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateRotationalAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                   _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateRotationalAcceleration();
                   if (_rotationalAccelerationAttribute.hasValue()) {
                      firerotational_accelerationUpdated(_rotationalAccelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::CENTER_OF_MASS: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::CENTER_OF_MASS);

                if (_physicalEntityValueListeners.empty()) {
                    _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateCenterOfMass();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                   _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateCenterOfMass();
                   if (_centerOfMassAttribute.hasValue()) {
                      firecenter_of_massUpdated(_centerOfMassAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL: {
                attributesUpdated.insert(HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL);

                if (_physicalEntityValueListeners.empty()) {
                    _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateBodyWrtStructural();
                   AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                   _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateBodyWrtStructural();
                   if (_bodyWrtStructuralAttribute.hasValue()) {
                      firebody_wrt_structuralUpdated(_bodyWrtStructuralAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
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

void HlaPhysicalEntityImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaPhysicalEntityAttributesImpl>(getHlaPhysicalEntityAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaPhysicalEntityImpl::AttributeMap HlaPhysicalEntityImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
        if (iter->compare(NAME_ATTRIBUTE_NAME) == 0) {
            updateName();
            if (_nameAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::NAME] = _nameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(TYPE_ATTRIBUTE_NAME) == 0) {
            updateType();
            if (_typeAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::TYPE] = _typeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATUS_ATTRIBUTE_NAME) == 0) {
            updateStatus();
            if (_statusAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::STATUS] = _statusAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME) == 0) {
            updateParentReferenceFrame();
            if (_parentReferenceFrameAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATE_ATTRIBUTE_NAME) == 0) {
            updateState();
            if (_stateAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::STATE] = _stateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateAcceleration();
            if (_accelerationAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::ACCELERATION] = _accelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateRotationalAcceleration();
            if (_rotationalAccelerationAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION] = _rotationalAccelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(CENTER_OF_MASS_ATTRIBUTE_NAME) == 0) {
            updateCenterOfMass();
            if (_centerOfMassAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::CENTER_OF_MASS] = _centerOfMassAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME) == 0) {
            updateBodyWrtStructural();
            if (_bodyWrtStructuralAttribute.hasValue()) {
                res[HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructuralAttribute.getValue();
            }
            continue;
        }
    }
    return res;
}

RtiDriver::NameSet HlaPhysicalEntityImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaPhysicalEntityAttributesPtr attributes = getHlaPhysicalEntityAttributes();
    if (!attributes->hasName()) {
        res.insert(NAME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasType()) {
        res.insert(TYPE_ATTRIBUTE_NAME);
    }
    if (!attributes->hasStatus()) {
        res.insert(STATUS_ATTRIBUTE_NAME);
    }
    if (!attributes->hasParentReferenceFrame()) {
        res.insert(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME);
    }
    if (!attributes->hasState()) {
        res.insert(STATE_ATTRIBUTE_NAME);
    }
    if (!attributes->hasAcceleration()) {
        res.insert(ACCELERATION_ATTRIBUTE_NAME);
    }
    if (!attributes->hasRotationalAcceleration()) {
        res.insert(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME);
    }
    if (!attributes->hasCenterOfMass()) {
        res.insert(CENTER_OF_MASS_ATTRIBUTE_NAME);
    }
    if (!attributes->hasBodyWrtStructural()) {
        res.insert(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME);
    }
    return res;
}



HlaFederateIdPtr HlaPhysicalEntityImpl::getLastProducingFederate(HlaPhysicalEntityAttributes::Attribute attribute) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    switch (attribute) {
        case HlaPhysicalEntityAttributes::NAME: {
            if (_nameAttribute.hasFederateId()) {
                return _nameAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::TYPE: {
            if (_typeAttribute.hasFederateId()) {
                return _typeAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::STATUS: {
            if (_statusAttribute.hasFederateId()) {
                return _statusAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME: {
            if (_parentReferenceFrameAttribute.hasFederateId()) {
                return _parentReferenceFrameAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::STATE: {
            if (_stateAttribute.hasFederateId()) {
                return _stateAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::ACCELERATION: {
            if (_accelerationAttribute.hasFederateId()) {
                return _accelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION: {
            if (_rotationalAccelerationAttribute.hasFederateId()) {
                return _rotationalAccelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::CENTER_OF_MASS: {
            if (_centerOfMassAttribute.hasFederateId()) {
                return _centerOfMassAttribute.getFederateId();
            }
            break;
        }
        case HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL: {
            if (_bodyWrtStructuralAttribute.hasFederateId()) {
                return _bodyWrtStructuralAttribute.getFederateId();
            }
            break;
        }
        default:
            break;
    }
    return HlaFederateIdPtr(new HlaFederateIdImpl());
}
