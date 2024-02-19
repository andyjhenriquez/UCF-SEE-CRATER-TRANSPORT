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

#include "HlaPayloadImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPayloadValueListener.h>
#include "StringUtil.h"
#include "HlaPayloadManagerImpl.h"
#include "HlaPayloadAttributesImpl.h"
#include "HlaPayloadUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;

static const wchar_t POSITION_ATTRIBUTE_NAME[] = L"position";
static const wchar_t VELOCITY_ATTRIBUTE_NAME[] = L"velocity";
static const wchar_t HEALTH_ATTRIBUTE_NAME[] = L"health";
static const wchar_t FORCE_ATTRIBUTE_NAME[] = L"force";
static const wchar_t TORQUE_ATTRIBUTE_NAME[] = L"torque";
static const wchar_t MASS_ATTRIBUTE_NAME[] = L"mass";
static const wchar_t MASS_RATE_ATTRIBUTE_NAME[] = L"mass_rate";
static const wchar_t INERTIA_ATTRIBUTE_NAME[] = L"inertia";
static const wchar_t INERTIA_RATE_ATTRIBUTE_NAME[] = L"inertia_rate";
static const wchar_t NAME_ATTRIBUTE_NAME[] = L"name";
static const wchar_t TYPE_ATTRIBUTE_NAME[] = L"type";
static const wchar_t STATUS_ATTRIBUTE_NAME[] = L"status";
static const wchar_t PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME[] = L"parent_reference_frame";
static const wchar_t STATE_ATTRIBUTE_NAME[] = L"state";
static const wchar_t ACCELERATION_ATTRIBUTE_NAME[] = L"acceleration";
static const wchar_t ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME[] = L"rotational_acceleration";
static const wchar_t CENTER_OF_MASS_ATTRIBUTE_NAME[] = L"center_of_mass";
static const wchar_t BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME[] = L"body_wrt_structural";

RtiDriver::NameSet HlaPayloadImpl::getAttributes() {
    RtiDriver::NameSet res;
    res.insert(L"position");
    res.insert(L"velocity");
    res.insert(L"health");
    res.insert(L"force");
    res.insert(L"torque");
    res.insert(L"mass");
    res.insert(L"mass_rate");
    res.insert(L"inertia");
    res.insert(L"inertia_rate");
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


bool HlaPayloadImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaPayloadImpl::isWithinInterest() const {
    return !_removed;
}

HlaPayloadAttributesPtr HlaPayloadImpl::getHlaPayloadAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    updateVelocity();
    updateHealth();
    updateForce();
    updateTorque();
    updateMass();
    updateMassRate();
    updateInertia();
    updateInertiaRate();
    updateName();
    updateType();
    updateStatus();
    updateParentReferenceFrame();
    updateState();
    updateAcceleration();
    updateRotationalAcceleration();
    updateCenterOfMass();
    updateBodyWrtStructural();
    return HlaPayloadAttributesPtr(new HlaPayloadAttributesImpl(
        _positionAttribute,
        _velocityAttribute,
        _healthAttribute,
        _forceAttribute,
        _torqueAttribute,
        _massAttribute,
        _massRateAttribute,
        _inertiaAttribute,
        _inertiaRateAttribute,
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

HlaPayloadUpdaterPtr HlaPayloadImpl::getHlaPayloadUpdater() {
    HlaPayloadUpdater* ptr = new HlaPayloadUpdaterImpl(shared_from_this());
    return HlaPayloadUpdaterPtr(ptr);
}

std::wstring HlaPayloadImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaPayloadImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

HlaFederateIdImplPtr HlaPayloadImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaPayloadUpdaterImpl
*/

void HlaPayloadImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaPayloadAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaPayloadAttributesImplPtr  HlaPayloadImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaPayloadAttributesImplPtr ret;

    HlaEnumSet<HlaPayloadAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        for (AttributeMap::const_iterator iter = attributeUpdate.begin(); iter != attributeUpdate.end(); ++iter) {
                switch (iter->first) {
                    case HlaPayloadAttributes::POSITION:
                        {
                            updatePosition();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_positionAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _positionAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firepositionUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::POSITION, _positionAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::POSITION);
                        }
                        break;
                    case HlaPayloadAttributes::VELOCITY:
                        {
                            updateVelocity();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_velocityAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _velocityAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firevelocityUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::VELOCITY, _velocityAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::VELOCITY);
                        }
                        break;
                    case HlaPayloadAttributes::HEALTH:
                        {
                            updateHealth();
                            AttributeValue<double > oldValue(_healthAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _healthAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firehealthUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::HEALTH, _healthAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::HEALTH);
                        }
                        break;
                    case HlaPayloadAttributes::FORCE:
                        {
                            updateForce();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_forceAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _forceAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireforceUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::FORCE, _forceAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::FORCE);
                        }
                        break;
                    case HlaPayloadAttributes::TORQUE:
                        {
                            updateTorque();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_torqueAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _torqueAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firetorqueUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::TORQUE, _torqueAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::TORQUE);
                        }
                        break;
                    case HlaPayloadAttributes::MASS:
                        {
                            updateMass();
                            AttributeValue<double > oldValue(_massAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _massAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firemassUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::MASS, _massAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::MASS);
                        }
                        break;
                    case HlaPayloadAttributes::MASS_RATE:
                        {
                            updateMassRate();
                            AttributeValue<double > oldValue(_massRateAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _massRateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firemass_rateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::MASS_RATE, _massRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::MASS_RATE);
                        }
                        break;
                    case HlaPayloadAttributes::INERTIA:
                        {
                            updateInertia();
                            AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaAttribute);

                            std::shared_ptr<std::vector</* 9 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 9 */ double > >(iter->second);
                            _inertiaAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireinertiaUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::INERTIA, _inertiaAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::INERTIA);
                        }
                        break;
                    case HlaPayloadAttributes::INERTIA_RATE:
                        {
                            updateInertiaRate();
                            AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaRateAttribute);

                            std::shared_ptr<std::vector</* 9 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 9 */ double > >(iter->second);
                            _inertiaRateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireinertia_rateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::INERTIA_RATE, _inertiaRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::INERTIA_RATE);
                        }
                        break;
                    case HlaPayloadAttributes::NAME:
                        {
                            updateName();
                            AttributeValue<std::wstring > oldValue(_nameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _nameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::NAME);
                        }
                        break;
                    case HlaPayloadAttributes::TYPE:
                        {
                            updateType();
                            AttributeValue<std::wstring > oldValue(_typeAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _typeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firetypeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::TYPE);
                        }
                        break;
                    case HlaPayloadAttributes::STATUS:
                        {
                            updateStatus();
                            AttributeValue<std::wstring > oldValue(_statusAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _statusAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestatusUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::STATUS);
                        }
                        break;
                    case HlaPayloadAttributes::PARENT_REFERENCE_FRAME:
                        {
                            updateParentReferenceFrame();
                            AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _parentReferenceFrameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireparent_reference_frameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::PARENT_REFERENCE_FRAME);
                        }
                        break;
                    case HlaPayloadAttributes::STATE:
                        {
                            updateState();
                            AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                            std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > valuePtr =  std::static_pointer_cast<LunarSimulation::SpaceTimeCoordinateState >(iter->second);
                            _stateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::STATE);
                        }
                        break;
                    case HlaPayloadAttributes::ACCELERATION:
                        {
                            updateAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _accelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireaccelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::ACCELERATION);
                        }
                        break;
                    case HlaPayloadAttributes::ROTATIONAL_ACCELERATION:
                        {
                            updateRotationalAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _rotationalAccelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firerotational_accelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::ROTATIONAL_ACCELERATION);
                        }
                        break;
                    case HlaPayloadAttributes::CENTER_OF_MASS:
                        {
                            updateCenterOfMass();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _centerOfMassAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firecenter_of_massUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::CENTER_OF_MASS);
                        }
                        break;
                    case HlaPayloadAttributes::BODY_WRT_STRUCTURAL:
                        {
                            updateBodyWrtStructural();
                            AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                            std::shared_ptr<LunarSimulation::AttitudeQuaternion > valuePtr =  std::static_pointer_cast<LunarSimulation::AttitudeQuaternion >(iter->second);
                            _bodyWrtStructuralAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firebody_wrt_structuralUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaPayloadAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaPayloadAttributes::BODY_WRT_STRUCTURAL);
                        }
                        break;
                    default:
                        break;
                }
        }
        ret = std::dynamic_pointer_cast<HlaPayloadAttributesImpl>(getHlaPayloadAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaPayloadImpl::sendAttributes(const AttributeMap& attributeSet, HlaPayloadAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
            switch (iter->first) {

                case HlaPayloadAttributes::POSITION:
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
                case HlaPayloadAttributes::VELOCITY:
                    if (attributeValues->hasVelocity()) {
                        try {
                            _objectClassManager->_velocityVectorEncoderEncoder.set(*(std::vector</* 3 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_velocityVectorEncoderEncoder.getEncodedLength());
                            _objectClassManager->_velocityVectorEncoderEncoder.encodeInto(res);
                            attributeValueMap[VELOCITY_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode VELOCITY_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPayloadAttributes::HEALTH:
                    if (attributeValues->hasHealth()) {
                        try {
                            _objectClassManager->_hLAfloat64LEEncoder.set(*(double*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAfloat64LEEncoder.encodeInto(res);
                            attributeValueMap[HEALTH_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode HEALTH_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPayloadAttributes::FORCE:
                    if (attributeValues->hasForce()) {
                        try {
                            _objectClassManager->_forceVectorEncoderEncoder.set(*(std::vector</* 3 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_forceVectorEncoderEncoder.getEncodedLength());
                            _objectClassManager->_forceVectorEncoderEncoder.encodeInto(res);
                            attributeValueMap[FORCE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode FORCE_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPayloadAttributes::TORQUE:
                    if (attributeValues->hasTorque()) {
                        try {
                            _objectClassManager->_torqueVectorEncoderEncoder.set(*(std::vector</* 3 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_torqueVectorEncoderEncoder.getEncodedLength());
                            _objectClassManager->_torqueVectorEncoderEncoder.encodeInto(res);
                            attributeValueMap[TORQUE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode TORQUE_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPayloadAttributes::MASS:
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
                case HlaPayloadAttributes::MASS_RATE:
                    if (attributeValues->hasMassRate()) {
                        try {
                            _objectClassManager->_hLAfloat64LEEncoder.set(*(double*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            _objectClassManager->_hLAfloat64LEEncoder.encodeInto(res);
                            attributeValueMap[MASS_RATE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode MASS_RATE_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPayloadAttributes::INERTIA:
                    if (attributeValues->hasInertia()) {
                        try {
                            _objectClassManager->_inertiaMatrixEncoderEncoder.set(*(std::vector</* 9 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_inertiaMatrixEncoderEncoder.getEncodedLength());
                            _objectClassManager->_inertiaMatrixEncoderEncoder.encodeInto(res);
                            attributeValueMap[INERTIA_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode INERTIA_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPayloadAttributes::INERTIA_RATE:
                    if (attributeValues->hasInertiaRate()) {
                        try {
                            _objectClassManager->_inertiaRateMatrixEncoderEncoder.set(*(std::vector</* 9 */ double >*)iter->second.get());
                            RtiDriver::VariableLengthData res;
                            res.reserve(_objectClassManager->_inertiaRateMatrixEncoderEncoder.getEncodedLength());
                            _objectClassManager->_inertiaRateMatrixEncoderEncoder.encodeInto(res);
                            attributeValueMap[INERTIA_RATE_ATTRIBUTE_NAME] = res;
                        } catch (EncodingHelpers::EncoderException & e) {
                            HlaExceptionPtr ex(new HlaEncodeException(L"Failed to encode INERTIA_RATE_ATTRIBUTE_NAME: " + e.what()));
                            _hlaWorld->postException(ex);
                        }
                    }
                    break;
                case HlaPayloadAttributes::NAME:
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
                case HlaPayloadAttributes::TYPE:
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
                case HlaPayloadAttributes::STATUS:
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
                case HlaPayloadAttributes::PARENT_REFERENCE_FRAME:
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
                case HlaPayloadAttributes::STATE:
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
                case HlaPayloadAttributes::ACCELERATION:
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
                case HlaPayloadAttributes::ROTATIONAL_ACCELERATION:
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
                case HlaPayloadAttributes::CENTER_OF_MASS:
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
                case HlaPayloadAttributes::BODY_WRT_STRUCTURAL:
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

void HlaPayloadImpl::firepositionUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::positionUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firevelocityUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::velocityUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firehealthUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::healthUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::fireforceUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::forceUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firetorqueUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::torqueUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firemassUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::massUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firemass_rateUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::massRateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::fireinertiaUpdated(std::shared_ptr<std::vector</* 9 */ double > > value, const AttributeValue<std::vector</* 9 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 9 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::inertiaUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::fireinertia_rateUpdated(std::shared_ptr<std::vector</* 9 */ double > > value, const AttributeValue<std::vector</* 9 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 9 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::inertiaRateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::nameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firetypeUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::typeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firestatusUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::statusUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::fireparent_reference_frameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::parentReferenceFrameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firestateUpdated(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > value, const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::stateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::fireaccelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::accelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firerotational_accelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::rotationalAccelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firecenter_of_massUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::centerOfMassUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::firebody_wrt_structuralUpdated(std::shared_ptr<LunarSimulation::AttitudeQuaternion > value, const AttributeValue<LunarSimulation::AttitudeQuaternion >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::AttitudeQuaternion > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadValueListener::bodyWrtStructuralUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaPayloadImpl::fireAttributesUpdated(const HlaEnumSet<HlaPayloadAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPayloadListenerPtr> listeners = _payloadListeners.getListeners();
    for (std::set<HlaPayloadListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadImpl::fireProducingFederateUpdated(HlaPayloadAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (oldFederateId && newFederateId && *oldFederateId != *newFederateId) {
        std::set<HlaPayloadValueListenerPtr> listeners = _payloadValueListeners.getListeners();
        for (std::set<HlaPayloadValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            std::function<void()> callback = std::bind(&HlaPayloadValueListener::producingFederateUpdated, *it, shared_from_this(), attribute, oldFederateId, newFederateId, timeStamp, logicalTime);
            _hlaWorld->postNotification(callback);
        }
    }
}

bool HlaPayloadImpl::hasPosition() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    return _positionAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPayloadImpl::getPosition() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return *_positionAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'position' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPayloadImpl::getPosition(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return *_positionAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadImpl::getPositionTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updatePosition();
    if (_positionAttribute.hasValue()) {
        return _positionAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'position' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updatePosition() {
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

bool HlaPayloadImpl::hasVelocity() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateVelocity();
    return _velocityAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPayloadImpl::getVelocity() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateVelocity();
    if (_velocityAttribute.hasValue()) {
        return *_velocityAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'velocity' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPayloadImpl::getVelocity(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateVelocity();
    if (_velocityAttribute.hasValue()) {
        return *_velocityAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadImpl::getVelocityTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateVelocity();
    if (_velocityAttribute.hasValue()) {
        return _velocityAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'velocity' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateVelocity() {
    if (_velocityAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _velocityAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_velocityVectorEncoderDecoder.decodeFrom(encodedValue, 0);
            _velocityAttribute.setDecodedValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(_objectClassManager->_velocityVectorEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode VELOCITY_ATTRIBUTE_NAME: Failed to decode VelocityVector. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode VELOCITY_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _velocityAttribute.clearEncodedValue();
        }
    }
}

bool HlaPayloadImpl::hasHealth() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateHealth();
    return _healthAttribute.hasValue();
}

double HlaPayloadImpl::getHealth() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateHealth();
    if (_healthAttribute.hasValue()) {
        return *_healthAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'health' not set for instance " + getHlaInstanceName());
}

double HlaPayloadImpl::getHealth(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateHealth();
    if (_healthAttribute.hasValue()) {
        return *_healthAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaPayloadImpl::getHealthTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateHealth();
    if (_healthAttribute.hasValue()) {
        return _healthAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'health' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateHealth() {
    if (_healthAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _healthAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAfloat64LEDecoder.decodeFrom(encodedValue, 0);
            _healthAttribute.setDecodedValue(std::shared_ptr<double >(new double(_objectClassManager->_hLAfloat64LEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode HEALTH_ATTRIBUTE_NAME: Failed to decode Health. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode HEALTH_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _healthAttribute.clearEncodedValue();
        }
    }
}

bool HlaPayloadImpl::hasForce() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    return _forceAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPayloadImpl::getForce() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    if (_forceAttribute.hasValue()) {
        return *_forceAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'force' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPayloadImpl::getForce(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    if (_forceAttribute.hasValue()) {
        return *_forceAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadImpl::getForceTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    if (_forceAttribute.hasValue()) {
        return _forceAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'force' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateForce() {
    if (_forceAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _forceAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_forceVectorEncoderDecoder.decodeFrom(encodedValue, 0);
            _forceAttribute.setDecodedValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(_objectClassManager->_forceVectorEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode FORCE_ATTRIBUTE_NAME: Failed to decode ForceVector. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode FORCE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _forceAttribute.clearEncodedValue();
        }
    }
}

bool HlaPayloadImpl::hasTorque() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    return _torqueAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPayloadImpl::getTorque() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    if (_torqueAttribute.hasValue()) {
        return *_torqueAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'torque' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPayloadImpl::getTorque(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    if (_torqueAttribute.hasValue()) {
        return *_torqueAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadImpl::getTorqueTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    if (_torqueAttribute.hasValue()) {
        return _torqueAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'torque' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateTorque() {
    if (_torqueAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _torqueAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_torqueVectorEncoderDecoder.decodeFrom(encodedValue, 0);
            _torqueAttribute.setDecodedValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(_objectClassManager->_torqueVectorEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode TORQUE_ATTRIBUTE_NAME: Failed to decode TorqueVector. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode TORQUE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _torqueAttribute.clearEncodedValue();
        }
    }
}

bool HlaPayloadImpl::hasMass() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    return _massAttribute.hasValue();
}

double HlaPayloadImpl::getMass() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return *_massAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'mass' not set for instance " + getHlaInstanceName());
}

double HlaPayloadImpl::getMass(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return *_massAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaPayloadImpl::getMassTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return _massAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'mass' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateMass() {
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

bool HlaPayloadImpl::hasMassRate() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    return _massRateAttribute.hasValue();
}

double HlaPayloadImpl::getMassRate() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    if (_massRateAttribute.hasValue()) {
        return *_massRateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'massRate' not set for instance " + getHlaInstanceName());
}

double HlaPayloadImpl::getMassRate(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    if (_massRateAttribute.hasValue()) {
        return *_massRateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaPayloadImpl::getMassRateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    if (_massRateAttribute.hasValue()) {
        return _massRateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'massRate' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateMassRate() {
    if (_massRateAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _massRateAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_hLAfloat64LEDecoder.decodeFrom(encodedValue, 0);
            _massRateAttribute.setDecodedValue(std::shared_ptr<double >(new double(_objectClassManager->_hLAfloat64LEDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode MASS_RATE_ATTRIBUTE_NAME: Failed to decode MassRate. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode MASS_RATE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _massRateAttribute.clearEncodedValue();
        }
    }
}

bool HlaPayloadImpl::hasInertia() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    return _inertiaAttribute.hasValue();
}

std::vector</* 9 */ double > HlaPayloadImpl::getInertia() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    if (_inertiaAttribute.hasValue()) {
        return *_inertiaAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertia' not set for instance " + getHlaInstanceName());
}

std::vector</* 9 */ double > HlaPayloadImpl::getInertia(std::vector</* 9 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    if (_inertiaAttribute.hasValue()) {
        return *_inertiaAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaPayloadImpl::getInertiaTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    if (_inertiaAttribute.hasValue()) {
        return _inertiaAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertia' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateInertia() {
    if (_inertiaAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _inertiaAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_inertiaMatrixEncoderDecoder.decodeFrom(encodedValue, 0);
            _inertiaAttribute.setDecodedValue(std::shared_ptr<std::vector</* 9 */ double > >(new std::vector</* 9 */ double >(_objectClassManager->_inertiaMatrixEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode INERTIA_ATTRIBUTE_NAME: Failed to decode InertiaMatrix. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode INERTIA_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _inertiaAttribute.clearEncodedValue();
        }
    }
}

bool HlaPayloadImpl::hasInertiaRate() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    return _inertiaRateAttribute.hasValue();
}

std::vector</* 9 */ double > HlaPayloadImpl::getInertiaRate() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    if (_inertiaRateAttribute.hasValue()) {
        return *_inertiaRateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set for instance " + getHlaInstanceName());
}

std::vector</* 9 */ double > HlaPayloadImpl::getInertiaRate(std::vector</* 9 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    if (_inertiaRateAttribute.hasValue()) {
        return *_inertiaRateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaPayloadImpl::getInertiaRateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    if (_inertiaRateAttribute.hasValue()) {
        return _inertiaRateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateInertiaRate() {
    if (_inertiaRateAttribute.hasEncodedValue()) {
        const RtiDriver::VariableLengthData& encodedValue = _inertiaRateAttribute.getEncodedValue();
        try {
            std::unique_lock<std::mutex> lock(_objectClassManager->_decodersLock);
            size_t encodedSize = _objectClassManager->_inertiaRateMatrixEncoderDecoder.decodeFrom(encodedValue, 0);
            _inertiaRateAttribute.setDecodedValue(std::shared_ptr<std::vector</* 9 */ double > >(new std::vector</* 9 */ double >(_objectClassManager->_inertiaRateMatrixEncoderDecoder)));

            if (_hlaWorld->getTuning()->VERIFY_RECEIVED_DATA_LENGTH && encodedSize != encodedValue.size()) {
                HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode INERTIA_RATE_ATTRIBUTE_NAME: Failed to decode InertiaRateMatrix. Invalid data length " +
                                                                      StringUtil::sizeToWstring(encodedValue.size()) + L", expected " + StringUtil::sizeToWstring(encodedSize) + L".",
                                                                      _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
                _hlaWorld->postException(ex);
            }
        } catch (EncodingHelpers::EncoderException & e) {
            HlaExceptionPtr ex(new HlaDecodeException(L"Failed to decode INERTIA_RATE_ATTRIBUTE_NAME: " + e.what(), _hlaWorld->getTuning()->INCLUDE_DATA_IN_DECODE_EXCEPTION, encodedValue));
            _hlaWorld->postException(ex);
            _inertiaRateAttribute.clearEncodedValue();
        }
    }
}

bool HlaPayloadImpl::hasName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    return _nameAttribute.hasValue();
}

std::wstring HlaPayloadImpl::getName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPayloadImpl::getName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadImpl::getNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return _nameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateName() {
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

bool HlaPayloadImpl::hasType() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    return _typeAttribute.hasValue();
}

std::wstring HlaPayloadImpl::getType() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPayloadImpl::getType(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadImpl::getTypeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return _typeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateType() {
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

bool HlaPayloadImpl::hasStatus() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    return _statusAttribute.hasValue();
}

std::wstring HlaPayloadImpl::getStatus() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPayloadImpl::getStatus(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadImpl::getStatusTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return _statusAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateStatus() {
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

bool HlaPayloadImpl::hasParentReferenceFrame() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    return _parentReferenceFrameAttribute.hasValue();
}

std::wstring HlaPayloadImpl::getParentReferenceFrame() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

std::wstring HlaPayloadImpl::getParentReferenceFrame(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadImpl::getParentReferenceFrameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return _parentReferenceFrameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateParentReferenceFrame() {
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

bool HlaPayloadImpl::hasState() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    return _stateAttribute.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaPayloadImpl::getState() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

LunarSimulation::SpaceTimeCoordinateState HlaPayloadImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaPayloadImpl::getStateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return _stateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateState() {
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

bool HlaPayloadImpl::hasAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    return _accelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPayloadImpl::getAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPayloadImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadImpl::getAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return _accelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateAcceleration() {
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

bool HlaPayloadImpl::hasRotationalAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    return _rotationalAccelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPayloadImpl::getRotationalAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPayloadImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadImpl::getRotationalAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return _rotationalAccelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateRotationalAcceleration() {
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

bool HlaPayloadImpl::hasCenterOfMass() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    return _centerOfMassAttribute.hasValue();
}

std::vector</* 3 */ double > HlaPayloadImpl::getCenterOfMass() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaPayloadImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadImpl::getCenterOfMassTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return _centerOfMassAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateCenterOfMass() {
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

bool HlaPayloadImpl::hasBodyWrtStructural() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    return _bodyWrtStructuralAttribute.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaPayloadImpl::getBodyWrtStructural() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

LunarSimulation::AttitudeQuaternion HlaPayloadImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaPayloadImpl::getBodyWrtStructuralTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return _bodyWrtStructuralAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

void HlaPayloadImpl::updateBodyWrtStructural() {
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



void HlaPayloadImpl::addHlaPayloadListener(HlaPayloadListenerPtr listener) {
    _payloadListeners.add(listener);
}

void HlaPayloadImpl::removeHlaPayloadListener(HlaPayloadListenerPtr listener) {
    _payloadListeners.remove(listener);
}

void HlaPayloadImpl::addHlaPayloadValueListener(HlaPayloadValueListenerPtr valueListener) {
    _payloadValueListeners.add(valueListener);
}
                    
void HlaPayloadImpl::removeHlaPayloadValueListener(HlaPayloadValueListenerPtr valueListener) {
    _payloadValueListeners.remove(valueListener);
}


void HlaPayloadImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaPayloadAttributes::Attribute> attributesUpdated(attributes.size());
    {
       std::lock_guard<std::recursive_mutex> lock(_attributesLock);
       for (RtiDriver::NameValueMap::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
          HlaPayloadAttributes::Attribute attribute;
          if (!HlaPayloadAttributes::find(attribute, iter->first)) {
             continue;
          }

          switch (attribute) {
             case HlaPayloadAttributes::POSITION: {
                attributesUpdated.insert(HlaPayloadAttributes::POSITION);

                if (_payloadValueListeners.empty()) {
                    _positionAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updatePosition();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_positionAttribute);

                   _positionAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updatePosition();
                   if (_positionAttribute.hasValue()) {
                      firepositionUpdated(_positionAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::POSITION, _positionAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::VELOCITY: {
                attributesUpdated.insert(HlaPayloadAttributes::VELOCITY);

                if (_payloadValueListeners.empty()) {
                    _velocityAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateVelocity();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_velocityAttribute);

                   _velocityAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateVelocity();
                   if (_velocityAttribute.hasValue()) {
                      firevelocityUpdated(_velocityAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::VELOCITY, _velocityAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::HEALTH: {
                attributesUpdated.insert(HlaPayloadAttributes::HEALTH);

                if (_payloadValueListeners.empty()) {
                    _healthAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateHealth();
                   AttributeValue<double > oldValue(_healthAttribute);

                   _healthAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateHealth();
                   if (_healthAttribute.hasValue()) {
                      firehealthUpdated(_healthAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::HEALTH, _healthAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::FORCE: {
                attributesUpdated.insert(HlaPayloadAttributes::FORCE);

                if (_payloadValueListeners.empty()) {
                    _forceAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateForce();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_forceAttribute);

                   _forceAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateForce();
                   if (_forceAttribute.hasValue()) {
                      fireforceUpdated(_forceAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::FORCE, _forceAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::TORQUE: {
                attributesUpdated.insert(HlaPayloadAttributes::TORQUE);

                if (_payloadValueListeners.empty()) {
                    _torqueAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateTorque();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_torqueAttribute);

                   _torqueAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateTorque();
                   if (_torqueAttribute.hasValue()) {
                      firetorqueUpdated(_torqueAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::TORQUE, _torqueAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::MASS: {
                attributesUpdated.insert(HlaPayloadAttributes::MASS);

                if (_payloadValueListeners.empty()) {
                    _massAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateMass();
                   AttributeValue<double > oldValue(_massAttribute);

                   _massAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateMass();
                   if (_massAttribute.hasValue()) {
                      firemassUpdated(_massAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::MASS, _massAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::MASS_RATE: {
                attributesUpdated.insert(HlaPayloadAttributes::MASS_RATE);

                if (_payloadValueListeners.empty()) {
                    _massRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateMassRate();
                   AttributeValue<double > oldValue(_massRateAttribute);

                   _massRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateMassRate();
                   if (_massRateAttribute.hasValue()) {
                      firemass_rateUpdated(_massRateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::MASS_RATE, _massRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::INERTIA: {
                attributesUpdated.insert(HlaPayloadAttributes::INERTIA);

                if (_payloadValueListeners.empty()) {
                    _inertiaAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateInertia();
                   AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaAttribute);

                   _inertiaAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateInertia();
                   if (_inertiaAttribute.hasValue()) {
                      fireinertiaUpdated(_inertiaAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::INERTIA, _inertiaAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::INERTIA_RATE: {
                attributesUpdated.insert(HlaPayloadAttributes::INERTIA_RATE);

                if (_payloadValueListeners.empty()) {
                    _inertiaRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateInertiaRate();
                   AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaRateAttribute);

                   _inertiaRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateInertiaRate();
                   if (_inertiaRateAttribute.hasValue()) {
                      fireinertia_rateUpdated(_inertiaRateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::INERTIA_RATE, _inertiaRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::NAME: {
                attributesUpdated.insert(HlaPayloadAttributes::NAME);

                if (_payloadValueListeners.empty()) {
                    _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateName();
                   AttributeValue<std::wstring > oldValue(_nameAttribute);

                   _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateName();
                   if (_nameAttribute.hasValue()) {
                      firenameUpdated(_nameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::TYPE: {
                attributesUpdated.insert(HlaPayloadAttributes::TYPE);

                if (_payloadValueListeners.empty()) {
                    _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateType();
                   AttributeValue<std::wstring > oldValue(_typeAttribute);

                   _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateType();
                   if (_typeAttribute.hasValue()) {
                      firetypeUpdated(_typeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::STATUS: {
                attributesUpdated.insert(HlaPayloadAttributes::STATUS);

                if (_payloadValueListeners.empty()) {
                    _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateStatus();
                   AttributeValue<std::wstring > oldValue(_statusAttribute);

                   _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateStatus();
                   if (_statusAttribute.hasValue()) {
                      firestatusUpdated(_statusAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::PARENT_REFERENCE_FRAME: {
                attributesUpdated.insert(HlaPayloadAttributes::PARENT_REFERENCE_FRAME);

                if (_payloadValueListeners.empty()) {
                    _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateParentReferenceFrame();
                   AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                   _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateParentReferenceFrame();
                   if (_parentReferenceFrameAttribute.hasValue()) {
                      fireparent_reference_frameUpdated(_parentReferenceFrameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::STATE: {
                attributesUpdated.insert(HlaPayloadAttributes::STATE);

                if (_payloadValueListeners.empty()) {
                    _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateState();
                   AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                   _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateState();
                   if (_stateAttribute.hasValue()) {
                      firestateUpdated(_stateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::ACCELERATION: {
                attributesUpdated.insert(HlaPayloadAttributes::ACCELERATION);

                if (_payloadValueListeners.empty()) {
                    _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                   _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateAcceleration();
                   if (_accelerationAttribute.hasValue()) {
                      fireaccelerationUpdated(_accelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::ROTATIONAL_ACCELERATION: {
                attributesUpdated.insert(HlaPayloadAttributes::ROTATIONAL_ACCELERATION);

                if (_payloadValueListeners.empty()) {
                    _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateRotationalAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                   _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateRotationalAcceleration();
                   if (_rotationalAccelerationAttribute.hasValue()) {
                      firerotational_accelerationUpdated(_rotationalAccelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::CENTER_OF_MASS: {
                attributesUpdated.insert(HlaPayloadAttributes::CENTER_OF_MASS);

                if (_payloadValueListeners.empty()) {
                    _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateCenterOfMass();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                   _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateCenterOfMass();
                   if (_centerOfMassAttribute.hasValue()) {
                      firecenter_of_massUpdated(_centerOfMassAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaPayloadAttributes::BODY_WRT_STRUCTURAL: {
                attributesUpdated.insert(HlaPayloadAttributes::BODY_WRT_STRUCTURAL);

                if (_payloadValueListeners.empty()) {
                    _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateBodyWrtStructural();
                   AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                   _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateBodyWrtStructural();
                   if (_bodyWrtStructuralAttribute.hasValue()) {
                      firebody_wrt_structuralUpdated(_bodyWrtStructuralAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaPayloadAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
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

void HlaPayloadImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaPayloadAttributesImpl>(getHlaPayloadAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaPayloadImpl::AttributeMap HlaPayloadImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
        if (iter->compare(POSITION_ATTRIBUTE_NAME) == 0) {
            updatePosition();
            if (_positionAttribute.hasValue()) {
                res[HlaPayloadAttributes::POSITION] = _positionAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(VELOCITY_ATTRIBUTE_NAME) == 0) {
            updateVelocity();
            if (_velocityAttribute.hasValue()) {
                res[HlaPayloadAttributes::VELOCITY] = _velocityAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(HEALTH_ATTRIBUTE_NAME) == 0) {
            updateHealth();
            if (_healthAttribute.hasValue()) {
                res[HlaPayloadAttributes::HEALTH] = _healthAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(FORCE_ATTRIBUTE_NAME) == 0) {
            updateForce();
            if (_forceAttribute.hasValue()) {
                res[HlaPayloadAttributes::FORCE] = _forceAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(TORQUE_ATTRIBUTE_NAME) == 0) {
            updateTorque();
            if (_torqueAttribute.hasValue()) {
                res[HlaPayloadAttributes::TORQUE] = _torqueAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(MASS_ATTRIBUTE_NAME) == 0) {
            updateMass();
            if (_massAttribute.hasValue()) {
                res[HlaPayloadAttributes::MASS] = _massAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(MASS_RATE_ATTRIBUTE_NAME) == 0) {
            updateMassRate();
            if (_massRateAttribute.hasValue()) {
                res[HlaPayloadAttributes::MASS_RATE] = _massRateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(INERTIA_ATTRIBUTE_NAME) == 0) {
            updateInertia();
            if (_inertiaAttribute.hasValue()) {
                res[HlaPayloadAttributes::INERTIA] = _inertiaAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(INERTIA_RATE_ATTRIBUTE_NAME) == 0) {
            updateInertiaRate();
            if (_inertiaRateAttribute.hasValue()) {
                res[HlaPayloadAttributes::INERTIA_RATE] = _inertiaRateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(NAME_ATTRIBUTE_NAME) == 0) {
            updateName();
            if (_nameAttribute.hasValue()) {
                res[HlaPayloadAttributes::NAME] = _nameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(TYPE_ATTRIBUTE_NAME) == 0) {
            updateType();
            if (_typeAttribute.hasValue()) {
                res[HlaPayloadAttributes::TYPE] = _typeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATUS_ATTRIBUTE_NAME) == 0) {
            updateStatus();
            if (_statusAttribute.hasValue()) {
                res[HlaPayloadAttributes::STATUS] = _statusAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME) == 0) {
            updateParentReferenceFrame();
            if (_parentReferenceFrameAttribute.hasValue()) {
                res[HlaPayloadAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATE_ATTRIBUTE_NAME) == 0) {
            updateState();
            if (_stateAttribute.hasValue()) {
                res[HlaPayloadAttributes::STATE] = _stateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateAcceleration();
            if (_accelerationAttribute.hasValue()) {
                res[HlaPayloadAttributes::ACCELERATION] = _accelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateRotationalAcceleration();
            if (_rotationalAccelerationAttribute.hasValue()) {
                res[HlaPayloadAttributes::ROTATIONAL_ACCELERATION] = _rotationalAccelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(CENTER_OF_MASS_ATTRIBUTE_NAME) == 0) {
            updateCenterOfMass();
            if (_centerOfMassAttribute.hasValue()) {
                res[HlaPayloadAttributes::CENTER_OF_MASS] = _centerOfMassAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME) == 0) {
            updateBodyWrtStructural();
            if (_bodyWrtStructuralAttribute.hasValue()) {
                res[HlaPayloadAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructuralAttribute.getValue();
            }
            continue;
        }
    }
    return res;
}

RtiDriver::NameSet HlaPayloadImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaPayloadAttributesPtr attributes = getHlaPayloadAttributes();
    if (!attributes->hasPosition()) {
        res.insert(POSITION_ATTRIBUTE_NAME);
    }
    if (!attributes->hasVelocity()) {
        res.insert(VELOCITY_ATTRIBUTE_NAME);
    }
    if (!attributes->hasHealth()) {
        res.insert(HEALTH_ATTRIBUTE_NAME);
    }
    if (!attributes->hasForce()) {
        res.insert(FORCE_ATTRIBUTE_NAME);
    }
    if (!attributes->hasTorque()) {
        res.insert(TORQUE_ATTRIBUTE_NAME);
    }
    if (!attributes->hasMass()) {
        res.insert(MASS_ATTRIBUTE_NAME);
    }
    if (!attributes->hasMassRate()) {
        res.insert(MASS_RATE_ATTRIBUTE_NAME);
    }
    if (!attributes->hasInertia()) {
        res.insert(INERTIA_ATTRIBUTE_NAME);
    }
    if (!attributes->hasInertiaRate()) {
        res.insert(INERTIA_RATE_ATTRIBUTE_NAME);
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



HlaFederateIdPtr HlaPayloadImpl::getLastProducingFederate(HlaPayloadAttributes::Attribute attribute) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    switch (attribute) {
        case HlaPayloadAttributes::POSITION: {
            if (_positionAttribute.hasFederateId()) {
                return _positionAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::VELOCITY: {
            if (_velocityAttribute.hasFederateId()) {
                return _velocityAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::HEALTH: {
            if (_healthAttribute.hasFederateId()) {
                return _healthAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::FORCE: {
            if (_forceAttribute.hasFederateId()) {
                return _forceAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::TORQUE: {
            if (_torqueAttribute.hasFederateId()) {
                return _torqueAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::MASS: {
            if (_massAttribute.hasFederateId()) {
                return _massAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::MASS_RATE: {
            if (_massRateAttribute.hasFederateId()) {
                return _massRateAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::INERTIA: {
            if (_inertiaAttribute.hasFederateId()) {
                return _inertiaAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::INERTIA_RATE: {
            if (_inertiaRateAttribute.hasFederateId()) {
                return _inertiaRateAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::NAME: {
            if (_nameAttribute.hasFederateId()) {
                return _nameAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::TYPE: {
            if (_typeAttribute.hasFederateId()) {
                return _typeAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::STATUS: {
            if (_statusAttribute.hasFederateId()) {
                return _statusAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::PARENT_REFERENCE_FRAME: {
            if (_parentReferenceFrameAttribute.hasFederateId()) {
                return _parentReferenceFrameAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::STATE: {
            if (_stateAttribute.hasFederateId()) {
                return _stateAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::ACCELERATION: {
            if (_accelerationAttribute.hasFederateId()) {
                return _accelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::ROTATIONAL_ACCELERATION: {
            if (_rotationalAccelerationAttribute.hasFederateId()) {
                return _rotationalAccelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::CENTER_OF_MASS: {
            if (_centerOfMassAttribute.hasFederateId()) {
                return _centerOfMassAttribute.getFederateId();
            }
            break;
        }
        case HlaPayloadAttributes::BODY_WRT_STRUCTURAL: {
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
