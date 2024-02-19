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

#include "HlaLauncherImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLauncherValueListener.h>
#include "StringUtil.h"
#include "HlaLauncherManagerImpl.h"
#include "HlaLauncherAttributesImpl.h"
#include "HlaLauncherUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;

static const wchar_t POSITION_ATTRIBUTE_NAME[] = L"position";
static const wchar_t MASS_ATTRIBUTE_NAME[] = L"mass";
static const wchar_t ENERGY_ATTRIBUTE_NAME[] = L"energy";
static const wchar_t NAME_ATTRIBUTE_NAME[] = L"name";
static const wchar_t TYPE_ATTRIBUTE_NAME[] = L"type";
static const wchar_t STATUS_ATTRIBUTE_NAME[] = L"status";
static const wchar_t PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME[] = L"parent_reference_frame";
static const wchar_t STATE_ATTRIBUTE_NAME[] = L"state";
static const wchar_t ACCELERATION_ATTRIBUTE_NAME[] = L"acceleration";
static const wchar_t ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME[] = L"rotational_acceleration";
static const wchar_t CENTER_OF_MASS_ATTRIBUTE_NAME[] = L"center_of_mass";
static const wchar_t BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME[] = L"body_wrt_structural";

RtiDriver::NameSet HlaLauncherImpl::getAttributes() {
    RtiDriver::NameSet res;
    res.insert(L"position");
    res.insert(L"mass");
    res.insert(L"energy");
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


bool HlaLauncherImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaLauncherImpl::isWithinInterest() const {
    return !_removed;
}

HlaLauncherAttributesPtr HlaLauncherImpl::getHlaLauncherAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    updateMass();
    updateEnergy();
    updateName();
    updateType();
    updateStatus();
    updateParentReferenceFrame();
    updateState();
    updateAcceleration();
    updateRotationalAcceleration();
    updateCenterOfMass();
    updateBodyWrtStructural();
    return HlaLauncherAttributesPtr(new HlaLauncherAttributesImpl(
        _positionAttribute,
        _massAttribute,
        _energyAttribute,
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

HlaLauncherUpdaterPtr HlaLauncherImpl::getHlaLauncherUpdater() {
    HlaLauncherUpdater* ptr = new HlaLauncherUpdaterImpl(shared_from_this());
    return HlaLauncherUpdaterPtr(ptr);
}

std::wstring HlaLauncherImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaLauncherImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

HlaFederateIdImplPtr HlaLauncherImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaLauncherUpdaterImpl
*/

void HlaLauncherImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaLauncherAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaLauncherAttributesImplPtr  HlaLauncherImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaLauncherAttributesImplPtr ret;

    HlaEnumSet<HlaLauncherAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        for (AttributeMap::const_iterator iter = attributeUpdate.begin(); iter != attributeUpdate.end(); ++iter) {
                switch (iter->first) {
                    case HlaLauncherAttributes::POSITION:
                        {
                            updatePosition();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_positionAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _positionAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firepositionUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::POSITION, _positionAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::POSITION);
                        }
                        break;
                    case HlaLauncherAttributes::MASS:
                        {
                            updateMass();
                            AttributeValue<double > oldValue(_massAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _massAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firemassUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::MASS, _massAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::MASS);
                        }
                        break;
                    case HlaLauncherAttributes::ENERGY:
                        {
                            updateEnergy();
                            AttributeValue<double > oldValue(_energyAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _energyAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireenergyUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::ENERGY, _energyAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::ENERGY);
                        }
                        break;
                    case HlaLauncherAttributes::NAME:
                        {
                            updateName();
                            AttributeValue<std::wstring > oldValue(_nameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _nameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::NAME);
                        }
                        break;
                    case HlaLauncherAttributes::TYPE:
                        {
                            updateType();
                            AttributeValue<std::wstring > oldValue(_typeAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _typeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firetypeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::TYPE);
                        }
                        break;
                    case HlaLauncherAttributes::STATUS:
                        {
                            updateStatus();
                            AttributeValue<std::wstring > oldValue(_statusAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _statusAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestatusUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::STATUS);
                        }
                        break;
                    case HlaLauncherAttributes::PARENT_REFERENCE_FRAME:
                        {
                            updateParentReferenceFrame();
                            AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _parentReferenceFrameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireparent_reference_frameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::PARENT_REFERENCE_FRAME);
                        }
                        break;
                    case HlaLauncherAttributes::STATE:
                        {
                            updateState();
                            AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                            std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > valuePtr =  std::static_pointer_cast<LunarSimulation::SpaceTimeCoordinateState >(iter->second);
                            _stateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::STATE);
                        }
                        break;
                    case HlaLauncherAttributes::ACCELERATION:
                        {
                            updateAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _accelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireaccelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::ACCELERATION);
                        }
                        break;
                    case HlaLauncherAttributes::ROTATIONAL_ACCELERATION:
                        {
                            updateRotationalAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _rotationalAccelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firerotational_accelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::ROTATIONAL_ACCELERATION);
                        }
                        break;
                    case HlaLauncherAttributes::CENTER_OF_MASS:
                        {
                            updateCenterOfMass();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _centerOfMassAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firecenter_of_massUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::CENTER_OF_MASS);
                        }
                        break;
                    case HlaLauncherAttributes::BODY_WRT_STRUCTURAL:
                        {
                            updateBodyWrtStructural();
                            AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                            std::shared_ptr<LunarSimulation::AttitudeQuaternion > valuePtr =  std::static_pointer_cast<LunarSimulation::AttitudeQuaternion >(iter->second);
                            _bodyWrtStructuralAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firebody_wrt_structuralUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaLauncherAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaLauncherAttributes::BODY_WRT_STRUCTURAL);
                        }
                        break;
                    default:
                        break;
                }
        }
        ret = std::dynamic_pointer_cast<HlaLauncherAttributesImpl>(getHlaLauncherAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaLauncherImpl::sendAttributes(const AttributeMap& attributeSet, HlaLauncherAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
            switch (iter->first) {

                case HlaLauncherAttributes::POSITION:
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
                case HlaLauncherAttributes::MASS:
                    if (attributeValues->hasMass()) {
                        try {
                            _objectClassManager->_hLAfloat64LEEncoder.set(*(double*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAfloat64LEEncoder.encodeInto(res);
                            attributeValueMap[MASS_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode MASS_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaLauncherAttributes::ENERGY:
                    if (attributeValues->hasEnergy()) {
                        try {
                            _objectClassManager->_hLAfloat64LEEncoder.set(*(double*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAfloat64LEEncoder.encodeInto(res);
                            attributeValueMap[ENERGY_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode ENERGY_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaLauncherAttributes::NAME:
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
                case HlaLauncherAttributes::TYPE:
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
                case HlaLauncherAttributes::STATUS:
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
                case HlaLauncherAttributes::PARENT_REFERENCE_FRAME:
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
                case HlaLauncherAttributes::STATE:
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
                case HlaLauncherAttributes::ACCELERATION:
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
                case HlaLauncherAttributes::ROTATIONAL_ACCELERATION:
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
                case HlaLauncherAttributes::CENTER_OF_MASS:
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
                case HlaLauncherAttributes::BODY_WRT_STRUCTURAL:
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

void HlaLauncherImpl::firepositionUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::positionUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firemassUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::massUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::fireenergyUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::energyUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::nameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firetypeUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::typeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firestatusUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::statusUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::fireparent_reference_frameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::parentReferenceFrameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firestateUpdated(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > value, const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::stateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::fireaccelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::accelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firerotational_accelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::rotationalAccelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firecenter_of_massUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::centerOfMassUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::firebody_wrt_structuralUpdated(std::shared_ptr<LunarSimulation::AttitudeQuaternion > value, const AttributeValue<LunarSimulation::AttitudeQuaternion >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::AttitudeQuaternion > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
    for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherValueListener::bodyWrtStructuralUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaLauncherImpl::fireAttributesUpdated(const HlaEnumSet<HlaLauncherAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaLauncherListenerPtr> listeners = _launcherListeners.getListeners();
    for (std::set<HlaLauncherListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaLauncherListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaLauncherImpl::fireProducingFederateUpdated(HlaLauncherAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (oldFederateId && newFederateId && *oldFederateId != *newFederateId) {
        std::set<HlaLauncherValueListenerPtr> listeners = _launcherValueListeners.getListeners();
        for (std::set<HlaLauncherValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            std::function<void()> callback = std::bind(&HlaLauncherValueListener::producingFederateUpdated, *it, shared_from_this(), attribute, oldFederateId, newFederateId, timeStamp, logicalTime);
            _hlaWorld->postNotification(callback);
        }
    }
}

bool HlaLauncherImpl::hasPosition() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    return _positionAttribute.hasValue();
}

std::vector</* 3 */ double > HlaLauncherImpl::getPosition() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return *_positionAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'position' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaLauncherImpl::getPosition(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return *_positionAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherImpl::getPositionTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return _positionAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'position' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updatePosition() {
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

bool HlaLauncherImpl::hasMass() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    return _massAttribute.hasValue();
}

double HlaLauncherImpl::getMass() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return *_massAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'mass' not set for instance " + getHlaInstanceName());
}

double HlaLauncherImpl::getMass(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return *_massAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaLauncherImpl::getMassTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return _massAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'mass' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateMass() {
    if (_massAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _massAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAfloat64LEDecoder.decodeFrom(encodedValue, 0);
            _massAttribute.setDecodedValue(std::shared_ptr<double >(new double(_objectClassManager->_hLAfloat64LEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode MASS_ATTRIBUTE_NAME: Failed to decode Mass. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode MASS_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _massAttribute.clearEncodedValue();
        }
    }
}

bool HlaLauncherImpl::hasEnergy() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateEnergy();
    return _energyAttribute.hasValue();
}

double HlaLauncherImpl::getEnergy() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateEnergy();
    if (_energyAttribute.hasValue()) {
        return *_energyAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'energy' not set for instance " + getHlaInstanceName());
}

double HlaLauncherImpl::getEnergy(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateEnergy();
    if (_energyAttribute.hasValue()) {
        return *_energyAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaLauncherImpl::getEnergyTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateEnergy();
    if (_energyAttribute.hasValue()) {
        return _energyAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'energy' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateEnergy() {
    if (_energyAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _energyAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAfloat64LEDecoder.decodeFrom(encodedValue, 0);
            _energyAttribute.setDecodedValue(std::shared_ptr<double >(new double(_objectClassManager->_hLAfloat64LEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ENERGY_ATTRIBUTE_NAME: Failed to decode Energy. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode ENERGY_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _energyAttribute.clearEncodedValue();
        }
    }
}

bool HlaLauncherImpl::hasName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    return _nameAttribute.hasValue();
}

std::wstring HlaLauncherImpl::getName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

std::wstring HlaLauncherImpl::getName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherImpl::getNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return _nameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateName() {
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

bool HlaLauncherImpl::hasType() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    return _typeAttribute.hasValue();
}

std::wstring HlaLauncherImpl::getType() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

std::wstring HlaLauncherImpl::getType(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherImpl::getTypeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return _typeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateType() {
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

bool HlaLauncherImpl::hasStatus() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    return _statusAttribute.hasValue();
}

std::wstring HlaLauncherImpl::getStatus() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

std::wstring HlaLauncherImpl::getStatus(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherImpl::getStatusTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return _statusAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateStatus() {
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

bool HlaLauncherImpl::hasParentReferenceFrame() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    return _parentReferenceFrameAttribute.hasValue();
}

std::wstring HlaLauncherImpl::getParentReferenceFrame() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

std::wstring HlaLauncherImpl::getParentReferenceFrame(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherImpl::getParentReferenceFrameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return _parentReferenceFrameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateParentReferenceFrame() {
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

bool HlaLauncherImpl::hasState() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    return _stateAttribute.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaLauncherImpl::getState() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

LunarSimulation::SpaceTimeCoordinateState HlaLauncherImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaLauncherImpl::getStateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return _stateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateState() {
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

bool HlaLauncherImpl::hasAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    return _accelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaLauncherImpl::getAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaLauncherImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherImpl::getAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return _accelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateAcceleration() {
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

bool HlaLauncherImpl::hasRotationalAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    return _rotationalAccelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaLauncherImpl::getRotationalAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaLauncherImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherImpl::getRotationalAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return _rotationalAccelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateRotationalAcceleration() {
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

bool HlaLauncherImpl::hasCenterOfMass() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    return _centerOfMassAttribute.hasValue();
}

std::vector</* 3 */ double > HlaLauncherImpl::getCenterOfMass() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaLauncherImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherImpl::getCenterOfMassTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return _centerOfMassAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateCenterOfMass() {
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

bool HlaLauncherImpl::hasBodyWrtStructural() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    return _bodyWrtStructuralAttribute.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaLauncherImpl::getBodyWrtStructural() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

LunarSimulation::AttitudeQuaternion HlaLauncherImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaLauncherImpl::getBodyWrtStructuralTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return _bodyWrtStructuralAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

void HlaLauncherImpl::updateBodyWrtStructural() {
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



void HlaLauncherImpl::addHlaLauncherListener(HlaLauncherListenerPtr listener) {
    _launcherListeners.add(listener);
}

void HlaLauncherImpl::removeHlaLauncherListener(HlaLauncherListenerPtr listener) {
    _launcherListeners.remove(listener);
}

void HlaLauncherImpl::addHlaLauncherValueListener(HlaLauncherValueListenerPtr valueListener) {
    _launcherValueListeners.add(valueListener);
}
                    
void HlaLauncherImpl::removeHlaLauncherValueListener(HlaLauncherValueListenerPtr valueListener) {
    _launcherValueListeners.remove(valueListener);
}


void HlaLauncherImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaLauncherAttributes::Attribute> attributesUpdated(attributes.size());
    {
       std::lock_guard<std::recursive_mutex> lock(_attributesLock);
       for (RtiDriver::NameValueMap::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
          HlaLauncherAttributes::Attribute attribute;
          if (!HlaLauncherAttributes::find(attribute, iter->first)) {
             continue;
          }

          switch (attribute) {
             case HlaLauncherAttributes::POSITION: {
                attributesUpdated.insert(HlaLauncherAttributes::POSITION);

                if (_launcherValueListeners.empty()) {
                    _positionAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updatePosition();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_positionAttribute);

                   _positionAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updatePosition();
                   if (_positionAttribute.hasValue()) {
                      firepositionUpdated(_positionAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::POSITION, _positionAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::MASS: {
                attributesUpdated.insert(HlaLauncherAttributes::MASS);

                if (_launcherValueListeners.empty()) {
                    _massAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateMass();
                   AttributeValue<double > oldValue(_massAttribute);

                   _massAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateMass();
                   if (_massAttribute.hasValue()) {
                      firemassUpdated(_massAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::MASS, _massAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::ENERGY: {
                attributesUpdated.insert(HlaLauncherAttributes::ENERGY);

                if (_launcherValueListeners.empty()) {
                    _energyAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateEnergy();
                   AttributeValue<double > oldValue(_energyAttribute);

                   _energyAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateEnergy();
                   if (_energyAttribute.hasValue()) {
                      fireenergyUpdated(_energyAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::ENERGY, _energyAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::NAME: {
                attributesUpdated.insert(HlaLauncherAttributes::NAME);

                if (_launcherValueListeners.empty()) {
                    _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateName();
                   AttributeValue<std::wstring > oldValue(_nameAttribute);

                   _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateName();
                   if (_nameAttribute.hasValue()) {
                      firenameUpdated(_nameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::TYPE: {
                attributesUpdated.insert(HlaLauncherAttributes::TYPE);

                if (_launcherValueListeners.empty()) {
                    _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateType();
                   AttributeValue<std::wstring > oldValue(_typeAttribute);

                   _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateType();
                   if (_typeAttribute.hasValue()) {
                      firetypeUpdated(_typeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::STATUS: {
                attributesUpdated.insert(HlaLauncherAttributes::STATUS);

                if (_launcherValueListeners.empty()) {
                    _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateStatus();
                   AttributeValue<std::wstring > oldValue(_statusAttribute);

                   _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateStatus();
                   if (_statusAttribute.hasValue()) {
                      firestatusUpdated(_statusAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::PARENT_REFERENCE_FRAME: {
                attributesUpdated.insert(HlaLauncherAttributes::PARENT_REFERENCE_FRAME);

                if (_launcherValueListeners.empty()) {
                    _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateParentReferenceFrame();
                   AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                   _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateParentReferenceFrame();
                   if (_parentReferenceFrameAttribute.hasValue()) {
                      fireparent_reference_frameUpdated(_parentReferenceFrameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::STATE: {
                attributesUpdated.insert(HlaLauncherAttributes::STATE);

                if (_launcherValueListeners.empty()) {
                    _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateState();
                   AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                   _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateState();
                   if (_stateAttribute.hasValue()) {
                      firestateUpdated(_stateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::ACCELERATION: {
                attributesUpdated.insert(HlaLauncherAttributes::ACCELERATION);

                if (_launcherValueListeners.empty()) {
                    _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                   _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateAcceleration();
                   if (_accelerationAttribute.hasValue()) {
                      fireaccelerationUpdated(_accelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::ROTATIONAL_ACCELERATION: {
                attributesUpdated.insert(HlaLauncherAttributes::ROTATIONAL_ACCELERATION);

                if (_launcherValueListeners.empty()) {
                    _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateRotationalAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                   _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateRotationalAcceleration();
                   if (_rotationalAccelerationAttribute.hasValue()) {
                      firerotational_accelerationUpdated(_rotationalAccelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::CENTER_OF_MASS: {
                attributesUpdated.insert(HlaLauncherAttributes::CENTER_OF_MASS);

                if (_launcherValueListeners.empty()) {
                    _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateCenterOfMass();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                   _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateCenterOfMass();
                   if (_centerOfMassAttribute.hasValue()) {
                      firecenter_of_massUpdated(_centerOfMassAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaLauncherAttributes::BODY_WRT_STRUCTURAL: {
                attributesUpdated.insert(HlaLauncherAttributes::BODY_WRT_STRUCTURAL);

                if (_launcherValueListeners.empty()) {
                    _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateBodyWrtStructural();
                   AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                   _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateBodyWrtStructural();
                   if (_bodyWrtStructuralAttribute.hasValue()) {
                      firebody_wrt_structuralUpdated(_bodyWrtStructuralAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaLauncherAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
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

void HlaLauncherImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaLauncherAttributesImpl>(getHlaLauncherAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaLauncherImpl::AttributeMap HlaLauncherImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
        if (iter->compare(POSITION_ATTRIBUTE_NAME) == 0) {
            updatePosition();
            if (_positionAttribute.hasValue()) {
                res[HlaLauncherAttributes::POSITION] = _positionAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(MASS_ATTRIBUTE_NAME) == 0) {
            updateMass();
            if (_massAttribute.hasValue()) {
                res[HlaLauncherAttributes::MASS] = _massAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ENERGY_ATTRIBUTE_NAME) == 0) {
            updateEnergy();
            if (_energyAttribute.hasValue()) {
                res[HlaLauncherAttributes::ENERGY] = _energyAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(NAME_ATTRIBUTE_NAME) == 0) {
            updateName();
            if (_nameAttribute.hasValue()) {
                res[HlaLauncherAttributes::NAME] = _nameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(TYPE_ATTRIBUTE_NAME) == 0) {
            updateType();
            if (_typeAttribute.hasValue()) {
                res[HlaLauncherAttributes::TYPE] = _typeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATUS_ATTRIBUTE_NAME) == 0) {
            updateStatus();
            if (_statusAttribute.hasValue()) {
                res[HlaLauncherAttributes::STATUS] = _statusAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME) == 0) {
            updateParentReferenceFrame();
            if (_parentReferenceFrameAttribute.hasValue()) {
                res[HlaLauncherAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATE_ATTRIBUTE_NAME) == 0) {
            updateState();
            if (_stateAttribute.hasValue()) {
                res[HlaLauncherAttributes::STATE] = _stateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateAcceleration();
            if (_accelerationAttribute.hasValue()) {
                res[HlaLauncherAttributes::ACCELERATION] = _accelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateRotationalAcceleration();
            if (_rotationalAccelerationAttribute.hasValue()) {
                res[HlaLauncherAttributes::ROTATIONAL_ACCELERATION] = _rotationalAccelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(CENTER_OF_MASS_ATTRIBUTE_NAME) == 0) {
            updateCenterOfMass();
            if (_centerOfMassAttribute.hasValue()) {
                res[HlaLauncherAttributes::CENTER_OF_MASS] = _centerOfMassAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME) == 0) {
            updateBodyWrtStructural();
            if (_bodyWrtStructuralAttribute.hasValue()) {
                res[HlaLauncherAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructuralAttribute.getValue();
            }
            continue;
        }
    }
    return res;
}

RtiDriver::NameSet HlaLauncherImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaLauncherAttributesPtr attributes = getHlaLauncherAttributes();
    if (!attributes->hasPosition()) {
        res.insert(POSITION_ATTRIBUTE_NAME);
    }
    if (!attributes->hasMass()) {
        res.insert(MASS_ATTRIBUTE_NAME);
    }
    if (!attributes->hasEnergy()) {
        res.insert(ENERGY_ATTRIBUTE_NAME);
    }
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



HlaFederateIdPtr HlaLauncherImpl::getLastProducingFederate(HlaLauncherAttributes::Attribute attribute) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    switch (attribute) {
        case HlaLauncherAttributes::POSITION: {
            if (_positionAttribute.hasFederateId()) {
                return _positionAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::MASS: {
            if (_massAttribute.hasFederateId()) {
                return _massAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::ENERGY: {
            if (_energyAttribute.hasFederateId()) {
                return _energyAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::NAME: {
            if (_nameAttribute.hasFederateId()) {
                return _nameAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::TYPE: {
            if (_typeAttribute.hasFederateId()) {
                return _typeAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::STATUS: {
            if (_statusAttribute.hasFederateId()) {
                return _statusAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::PARENT_REFERENCE_FRAME: {
            if (_parentReferenceFrameAttribute.hasFederateId()) {
                return _parentReferenceFrameAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::STATE: {
            if (_stateAttribute.hasFederateId()) {
                return _stateAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::ACCELERATION: {
            if (_accelerationAttribute.hasFederateId()) {
                return _accelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::ROTATIONAL_ACCELERATION: {
            if (_rotationalAccelerationAttribute.hasFederateId()) {
                return _rotationalAccelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::CENTER_OF_MASS: {
            if (_centerOfMassAttribute.hasFederateId()) {
                return _centerOfMassAttribute.getFederateId();
            }
            break;
        }
        case HlaLauncherAttributes::BODY_WRT_STRUCTURAL: {
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
