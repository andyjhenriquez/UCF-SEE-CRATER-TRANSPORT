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

#include "HlaDynamicalEntityImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaDynamicalEntityValueListener.h>
#include "StringUtil.h"
#include "HlaDynamicalEntityManagerImpl.h"
#include "HlaDynamicalEntityAttributesImpl.h"
#include "HlaDynamicalEntityUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;

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

RtiDriver::NameSet HlaDynamicalEntityImpl::getAttributes() {
    RtiDriver::NameSet res;
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


bool HlaDynamicalEntityImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaDynamicalEntityImpl::isWithinInterest() const {
    return !_removed;
}

HlaDynamicalEntityAttributesPtr HlaDynamicalEntityImpl::getHlaDynamicalEntityAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
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
    return HlaDynamicalEntityAttributesPtr(new HlaDynamicalEntityAttributesImpl(
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

HlaDynamicalEntityUpdaterPtr HlaDynamicalEntityImpl::getHlaDynamicalEntityUpdater() {
    HlaDynamicalEntityUpdater* ptr = new HlaDynamicalEntityUpdaterImpl(shared_from_this());
    return HlaDynamicalEntityUpdaterPtr(ptr);
}

std::wstring HlaDynamicalEntityImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaDynamicalEntityImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

void HlaDynamicalEntityImpl::setCreateAttributes(
        std::shared_ptr<std::wstring > name,
        HlaTimeStampPtr timeStamp) {
    HlaDynamicalEntityImpl::AttributeMap attributeUpdates;
    attributeUpdates[HlaDynamicalEntityAttributes::NAME] = name;
    try {
        HlaLogicalTimeImplPtr logicalTime = HlaLogicalTimeImpl::getInvalid();
        applyUpdate(attributeUpdates, timeStamp, logicalTime);
    } catch (HlaException &e) {
        HlaExceptionPtr ex(new HlaInternalException(L"Failed to set create attributes in HlaDynamicalEntityImpl" + e.what_w()));
        _hlaWorld->postException(ex);
    }
}

HlaFederateIdImplPtr HlaDynamicalEntityImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaDynamicalEntityUpdaterImpl
*/

void HlaDynamicalEntityImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaDynamicalEntityAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaDynamicalEntityAttributesImplPtr  HlaDynamicalEntityImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaDynamicalEntityAttributesImplPtr ret;

    HlaEnumSet<HlaDynamicalEntityAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        for (AttributeMap::const_iterator iter = attributeUpdate.begin(); iter != attributeUpdate.end(); ++iter) {
                switch (iter->first) {
                    case HlaDynamicalEntityAttributes::FORCE:
                        {
                            updateForce();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_forceAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _forceAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireforceUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::FORCE, _forceAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::FORCE);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::TORQUE:
                        {
                            updateTorque();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_torqueAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _torqueAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firetorqueUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::TORQUE, _torqueAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::TORQUE);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::MASS:
                        {
                            updateMass();
                            AttributeValue<double > oldValue(_massAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _massAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firemassUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::MASS, _massAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::MASS);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::MASS_RATE:
                        {
                            updateMassRate();
                            AttributeValue<double > oldValue(_massRateAttribute);

                            std::shared_ptr<double > valuePtr =  std::static_pointer_cast<double >(iter->second);
                            _massRateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firemass_rateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::MASS_RATE, _massRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::MASS_RATE);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::INERTIA:
                        {
                            updateInertia();
                            AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaAttribute);

                            std::shared_ptr<std::vector</* 9 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 9 */ double > >(iter->second);
                            _inertiaAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireinertiaUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::INERTIA, _inertiaAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::INERTIA);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::INERTIA_RATE:
                        {
                            updateInertiaRate();
                            AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaRateAttribute);

                            std::shared_ptr<std::vector</* 9 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 9 */ double > >(iter->second);
                            _inertiaRateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireinertia_rateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::INERTIA_RATE, _inertiaRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::INERTIA_RATE);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::NAME:
                        {
                            updateName();
                            AttributeValue<std::wstring > oldValue(_nameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _nameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firenameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::NAME);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::TYPE:
                        {
                            updateType();
                            AttributeValue<std::wstring > oldValue(_typeAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _typeAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firetypeUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::TYPE);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::STATUS:
                        {
                            updateStatus();
                            AttributeValue<std::wstring > oldValue(_statusAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _statusAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestatusUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::STATUS);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME:
                        {
                            updateParentReferenceFrame();
                            AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                            std::shared_ptr<std::wstring > valuePtr =  std::static_pointer_cast<std::wstring >(iter->second);
                            _parentReferenceFrameAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireparent_reference_frameUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::STATE:
                        {
                            updateState();
                            AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                            std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > valuePtr =  std::static_pointer_cast<LunarSimulation::SpaceTimeCoordinateState >(iter->second);
                            _stateAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firestateUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::STATE);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::ACCELERATION:
                        {
                            updateAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _accelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            fireaccelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::ACCELERATION);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION:
                        {
                            updateRotationalAcceleration();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _rotationalAccelerationAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firerotational_accelerationUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::CENTER_OF_MASS:
                        {
                            updateCenterOfMass();
                            AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                            std::shared_ptr<std::vector</* 3 */ double > > valuePtr =  std::static_pointer_cast<std::vector</* 3 */ double > >(iter->second);
                            _centerOfMassAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firecenter_of_massUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::CENTER_OF_MASS);
                        }
                        break;
                    case HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL:
                        {
                            updateBodyWrtStructural();
                            AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                            std::shared_ptr<LunarSimulation::AttitudeQuaternion > valuePtr =  std::static_pointer_cast<LunarSimulation::AttitudeQuaternion >(iter->second);
                            _bodyWrtStructuralAttribute.setValue(valuePtr, federateId, logicalTime, timeStamp);

                            firebody_wrt_structuralUpdated(valuePtr, oldValue, timeStamp, logicalTime);
                            fireProducingFederateUpdated(HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                            attributeUpdateSet.insert(HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL);
                        }
                        break;
                    default:
                        break;
                }
        }
        ret = std::dynamic_pointer_cast<HlaDynamicalEntityAttributesImpl>(getHlaDynamicalEntityAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaDynamicalEntityImpl::sendAttributes(const AttributeMap& attributeSet, HlaDynamicalEntityAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
            switch (iter->first) {

                case HlaDynamicalEntityAttributes::FORCE:
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
                case HlaDynamicalEntityAttributes::TORQUE:
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
                case HlaDynamicalEntityAttributes::MASS:
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
                case HlaDynamicalEntityAttributes::MASS_RATE:
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
                case HlaDynamicalEntityAttributes::INERTIA:
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
                case HlaDynamicalEntityAttributes::INERTIA_RATE:
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
                case HlaDynamicalEntityAttributes::NAME:
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
                case HlaDynamicalEntityAttributes::TYPE:
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
                case HlaDynamicalEntityAttributes::STATUS:
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
                case HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME:
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
                case HlaDynamicalEntityAttributes::STATE:
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
                case HlaDynamicalEntityAttributes::ACCELERATION:
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
                case HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION:
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
                case HlaDynamicalEntityAttributes::CENTER_OF_MASS:
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
                case HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL:
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

void HlaDynamicalEntityImpl::fireforceUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::forceUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firetorqueUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::torqueUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firemassUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::massUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firemass_rateUpdated(std::shared_ptr<double > value, const AttributeValue<double >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<double > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::massRateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::fireinertiaUpdated(std::shared_ptr<std::vector</* 9 */ double > > value, const AttributeValue<std::vector</* 9 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 9 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::inertiaUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::fireinertia_rateUpdated(std::shared_ptr<std::vector</* 9 */ double > > value, const AttributeValue<std::vector</* 9 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 9 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::inertiaRateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firenameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::nameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firetypeUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::typeUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firestatusUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::statusUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::fireparent_reference_frameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::wstring > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::parentReferenceFrameUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firestateUpdated(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > value, const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::stateUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::fireaccelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::accelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firerotational_accelerationUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::rotationalAccelerationUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firecenter_of_massUpdated(std::shared_ptr<std::vector</* 3 */ double > > value, const AttributeValue<std::vector</* 3 */ double > >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<std::vector</* 3 */ double > > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::centerOfMassUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::firebody_wrt_structuralUpdated(std::shared_ptr<LunarSimulation::AttitudeQuaternion > value, const AttributeValue<LunarSimulation::AttitudeQuaternion >& prevValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    bool valid = prevValue.hasValue();
    std::shared_ptr<LunarSimulation::AttitudeQuaternion > oldValue = valid ? prevValue.getValue() : value;
    std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::bodyWrtStructuralUpdated, *it, shared_from_this(), *value, valid, *oldValue, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}


void HlaDynamicalEntityImpl::fireAttributesUpdated(const HlaEnumSet<HlaDynamicalEntityAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaDynamicalEntityListenerPtr> listeners = _dynamicalEntityListeners.getListeners();
    for (std::set<HlaDynamicalEntityListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityImpl::fireProducingFederateUpdated(HlaDynamicalEntityAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (oldFederateId && newFederateId && *oldFederateId != *newFederateId) {
        std::set<HlaDynamicalEntityValueListenerPtr> listeners = _dynamicalEntityValueListeners.getListeners();
        for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
            std::function<void()> callback = std::bind(&HlaDynamicalEntityValueListener::producingFederateUpdated, *it, shared_from_this(), attribute, oldFederateId, newFederateId, timeStamp, logicalTime);
            _hlaWorld->postNotification(callback);
        }
    }
}

bool HlaDynamicalEntityImpl::hasForce() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    return _forceAttribute.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getForce() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    if (_forceAttribute.hasValue()) {
        return *_forceAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'force' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getForce(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    if (_forceAttribute.hasValue()) {
        return *_forceAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityImpl::getForceTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateForce();
    if (_forceAttribute.hasValue()) {
        return _forceAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'force' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateForce() {
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

bool HlaDynamicalEntityImpl::hasTorque() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    return _torqueAttribute.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getTorque() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    if (_torqueAttribute.hasValue()) {
        return *_torqueAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'torque' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getTorque(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    if (_torqueAttribute.hasValue()) {
        return *_torqueAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityImpl::getTorqueTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateTorque();
    if (_torqueAttribute.hasValue()) {
        return _torqueAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'torque' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateTorque() {
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

bool HlaDynamicalEntityImpl::hasMass() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    return _massAttribute.hasValue();
}

double HlaDynamicalEntityImpl::getMass() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return *_massAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'mass' not set for instance " + getHlaInstanceName());
}

double HlaDynamicalEntityImpl::getMass(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return *_massAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaDynamicalEntityImpl::getMassTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMass();
    if (_massAttribute.hasValue()) {
        return _massAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'mass' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateMass() {
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

bool HlaDynamicalEntityImpl::hasMassRate() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    return _massRateAttribute.hasValue();
}

double HlaDynamicalEntityImpl::getMassRate() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    if (_massRateAttribute.hasValue()) {
        return *_massRateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'massRate' not set for instance " + getHlaInstanceName());
}

double HlaDynamicalEntityImpl::getMassRate(double defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    if (_massRateAttribute.hasValue()) {
        return *_massRateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaDynamicalEntityImpl::getMassRateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateMassRate();
    if (_massRateAttribute.hasValue()) {
        return _massRateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'massRate' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateMassRate() {
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

bool HlaDynamicalEntityImpl::hasInertia() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    return _inertiaAttribute.hasValue();
}

std::vector</* 9 */ double > HlaDynamicalEntityImpl::getInertia() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    if (_inertiaAttribute.hasValue()) {
        return *_inertiaAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertia' not set for instance " + getHlaInstanceName());
}

std::vector</* 9 */ double > HlaDynamicalEntityImpl::getInertia(std::vector</* 9 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    if (_inertiaAttribute.hasValue()) {
        return *_inertiaAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaDynamicalEntityImpl::getInertiaTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertia();
    if (_inertiaAttribute.hasValue()) {
        return _inertiaAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertia' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateInertia() {
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

bool HlaDynamicalEntityImpl::hasInertiaRate() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    return _inertiaRateAttribute.hasValue();
}

std::vector</* 9 */ double > HlaDynamicalEntityImpl::getInertiaRate() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    if (_inertiaRateAttribute.hasValue()) {
        return *_inertiaRateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set for instance " + getHlaInstanceName());
}

std::vector</* 9 */ double > HlaDynamicalEntityImpl::getInertiaRate(std::vector</* 9 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    if (_inertiaRateAttribute.hasValue()) {
        return *_inertiaRateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaDynamicalEntityImpl::getInertiaRateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateInertiaRate();
    if (_inertiaRateAttribute.hasValue()) {
        return _inertiaRateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateInertiaRate() {
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

bool HlaDynamicalEntityImpl::hasName() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    return _nameAttribute.hasValue();
}

std::wstring HlaDynamicalEntityImpl::getName() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

std::wstring HlaDynamicalEntityImpl::getName(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return *_nameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityImpl::getNameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateName();
    if (_nameAttribute.hasValue()) {
        return _nameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'name' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateName() {
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

bool HlaDynamicalEntityImpl::hasType() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    return _typeAttribute.hasValue();
}

std::wstring HlaDynamicalEntityImpl::getType() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

std::wstring HlaDynamicalEntityImpl::getType(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return *_typeAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityImpl::getTypeTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateType();
    if (_typeAttribute.hasValue()) {
        return _typeAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'type' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateType() {
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

bool HlaDynamicalEntityImpl::hasStatus() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    return _statusAttribute.hasValue();
}

std::wstring HlaDynamicalEntityImpl::getStatus() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

std::wstring HlaDynamicalEntityImpl::getStatus(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return *_statusAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityImpl::getStatusTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateStatus();
    if (_statusAttribute.hasValue()) {
        return _statusAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'status' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateStatus() {
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

bool HlaDynamicalEntityImpl::hasParentReferenceFrame() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    return _parentReferenceFrameAttribute.hasValue();
}

std::wstring HlaDynamicalEntityImpl::getParentReferenceFrame() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

std::wstring HlaDynamicalEntityImpl::getParentReferenceFrame(std::wstring defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return *_parentReferenceFrameAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityImpl::getParentReferenceFrameTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateParentReferenceFrame();
    if (_parentReferenceFrameAttribute.hasValue()) {
        return _parentReferenceFrameAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateParentReferenceFrame() {
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

bool HlaDynamicalEntityImpl::hasState() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    return _stateAttribute.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaDynamicalEntityImpl::getState() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

LunarSimulation::SpaceTimeCoordinateState HlaDynamicalEntityImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return *_stateAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaDynamicalEntityImpl::getStateTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateState();
    if (_stateAttribute.hasValue()) {
        return _stateAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'state' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateState() {
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

bool HlaDynamicalEntityImpl::hasAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    return _accelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return *_accelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityImpl::getAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateAcceleration();
    if (_accelerationAttribute.hasValue()) {
        return _accelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'acceleration' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateAcceleration() {
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

bool HlaDynamicalEntityImpl::hasRotationalAcceleration() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    return _rotationalAccelerationAttribute.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getRotationalAcceleration() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return *_rotationalAccelerationAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityImpl::getRotationalAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateRotationalAcceleration();
    if (_rotationalAccelerationAttribute.hasValue()) {
        return _rotationalAccelerationAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateRotationalAcceleration() {
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

bool HlaDynamicalEntityImpl::hasCenterOfMass() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    return _centerOfMassAttribute.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getCenterOfMass() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

std::vector</* 3 */ double > HlaDynamicalEntityImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return *_centerOfMassAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityImpl::getCenterOfMassTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateCenterOfMass();
    if (_centerOfMassAttribute.hasValue()) {
        return _centerOfMassAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateCenterOfMass() {
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

bool HlaDynamicalEntityImpl::hasBodyWrtStructural() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    return _bodyWrtStructuralAttribute.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaDynamicalEntityImpl::getBodyWrtStructural() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

LunarSimulation::AttitudeQuaternion HlaDynamicalEntityImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return *_bodyWrtStructuralAttribute.getValue();
    }
    return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaDynamicalEntityImpl::getBodyWrtStructuralTimeStamped() THROW_SPEC (HlaValueNotSetException) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    updateBodyWrtStructural();
    if (_bodyWrtStructuralAttribute.hasValue()) {
        return _bodyWrtStructuralAttribute.getTimestampedValue();
    }
    throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set for instance " + getHlaInstanceName());
}

void HlaDynamicalEntityImpl::updateBodyWrtStructural() {
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



void HlaDynamicalEntityImpl::addHlaDynamicalEntityListener(HlaDynamicalEntityListenerPtr listener) {
    _dynamicalEntityListeners.add(listener);
}

void HlaDynamicalEntityImpl::removeHlaDynamicalEntityListener(HlaDynamicalEntityListenerPtr listener) {
    _dynamicalEntityListeners.remove(listener);
}

void HlaDynamicalEntityImpl::addHlaDynamicalEntityValueListener(HlaDynamicalEntityValueListenerPtr valueListener) {
    _dynamicalEntityValueListeners.add(valueListener);
}
                    
void HlaDynamicalEntityImpl::removeHlaDynamicalEntityValueListener(HlaDynamicalEntityValueListenerPtr valueListener) {
    _dynamicalEntityValueListeners.remove(valueListener);
}


void HlaDynamicalEntityImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaDynamicalEntityAttributes::Attribute> attributesUpdated(attributes.size());
    {
       std::lock_guard<std::recursive_mutex> lock(_attributesLock);
       for (RtiDriver::NameValueMap::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
          HlaDynamicalEntityAttributes::Attribute attribute;
          if (!HlaDynamicalEntityAttributes::find(attribute, iter->first)) {
             continue;
          }

          switch (attribute) {
             case HlaDynamicalEntityAttributes::FORCE: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::FORCE);

                if (_dynamicalEntityValueListeners.empty()) {
                    _forceAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateForce();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_forceAttribute);

                   _forceAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateForce();
                   if (_forceAttribute.hasValue()) {
                      fireforceUpdated(_forceAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::FORCE, _forceAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::TORQUE: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::TORQUE);

                if (_dynamicalEntityValueListeners.empty()) {
                    _torqueAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateTorque();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_torqueAttribute);

                   _torqueAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateTorque();
                   if (_torqueAttribute.hasValue()) {
                      firetorqueUpdated(_torqueAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::TORQUE, _torqueAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::MASS: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::MASS);

                if (_dynamicalEntityValueListeners.empty()) {
                    _massAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateMass();
                   AttributeValue<double > oldValue(_massAttribute);

                   _massAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateMass();
                   if (_massAttribute.hasValue()) {
                      firemassUpdated(_massAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::MASS, _massAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::MASS_RATE: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::MASS_RATE);

                if (_dynamicalEntityValueListeners.empty()) {
                    _massRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateMassRate();
                   AttributeValue<double > oldValue(_massRateAttribute);

                   _massRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateMassRate();
                   if (_massRateAttribute.hasValue()) {
                      firemass_rateUpdated(_massRateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::MASS_RATE, _massRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::INERTIA: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::INERTIA);

                if (_dynamicalEntityValueListeners.empty()) {
                    _inertiaAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateInertia();
                   AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaAttribute);

                   _inertiaAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateInertia();
                   if (_inertiaAttribute.hasValue()) {
                      fireinertiaUpdated(_inertiaAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::INERTIA, _inertiaAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::INERTIA_RATE: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::INERTIA_RATE);

                if (_dynamicalEntityValueListeners.empty()) {
                    _inertiaRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateInertiaRate();
                   AttributeValue<std::vector</* 9 */ double > > oldValue(_inertiaRateAttribute);

                   _inertiaRateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateInertiaRate();
                   if (_inertiaRateAttribute.hasValue()) {
                      fireinertia_rateUpdated(_inertiaRateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::INERTIA_RATE, _inertiaRateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::NAME: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::NAME);

                if (_dynamicalEntityValueListeners.empty()) {
                    _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateName();
                   AttributeValue<std::wstring > oldValue(_nameAttribute);

                   _nameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateName();
                   if (_nameAttribute.hasValue()) {
                      firenameUpdated(_nameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::NAME, _nameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::TYPE: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::TYPE);

                if (_dynamicalEntityValueListeners.empty()) {
                    _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateType();
                   AttributeValue<std::wstring > oldValue(_typeAttribute);

                   _typeAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateType();
                   if (_typeAttribute.hasValue()) {
                      firetypeUpdated(_typeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::TYPE, _typeAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::STATUS: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::STATUS);

                if (_dynamicalEntityValueListeners.empty()) {
                    _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateStatus();
                   AttributeValue<std::wstring > oldValue(_statusAttribute);

                   _statusAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateStatus();
                   if (_statusAttribute.hasValue()) {
                      firestatusUpdated(_statusAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::STATUS, _statusAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME);

                if (_dynamicalEntityValueListeners.empty()) {
                    _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateParentReferenceFrame();
                   AttributeValue<std::wstring > oldValue(_parentReferenceFrameAttribute);

                   _parentReferenceFrameAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateParentReferenceFrame();
                   if (_parentReferenceFrameAttribute.hasValue()) {
                      fireparent_reference_frameUpdated(_parentReferenceFrameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME, _parentReferenceFrameAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::STATE: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::STATE);

                if (_dynamicalEntityValueListeners.empty()) {
                    _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateState();
                   AttributeValue<LunarSimulation::SpaceTimeCoordinateState > oldValue(_stateAttribute);

                   _stateAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateState();
                   if (_stateAttribute.hasValue()) {
                      firestateUpdated(_stateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::STATE, _stateAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::ACCELERATION: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::ACCELERATION);

                if (_dynamicalEntityValueListeners.empty()) {
                    _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_accelerationAttribute);

                   _accelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateAcceleration();
                   if (_accelerationAttribute.hasValue()) {
                      fireaccelerationUpdated(_accelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::ACCELERATION, _accelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION);

                if (_dynamicalEntityValueListeners.empty()) {
                    _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateRotationalAcceleration();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_rotationalAccelerationAttribute);

                   _rotationalAccelerationAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateRotationalAcceleration();
                   if (_rotationalAccelerationAttribute.hasValue()) {
                      firerotational_accelerationUpdated(_rotationalAccelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION, _rotationalAccelerationAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::CENTER_OF_MASS: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::CENTER_OF_MASS);

                if (_dynamicalEntityValueListeners.empty()) {
                    _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateCenterOfMass();
                   AttributeValue<std::vector</* 3 */ double > > oldValue(_centerOfMassAttribute);

                   _centerOfMassAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateCenterOfMass();
                   if (_centerOfMassAttribute.hasValue()) {
                      firecenter_of_massUpdated(_centerOfMassAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::CENTER_OF_MASS, _centerOfMassAttribute.getFederateId(), federateId, timeStamp, logicalTime);
                }
                break;
             }
             case HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL: {
                attributesUpdated.insert(HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL);

                if (_dynamicalEntityValueListeners.empty()) {
                    _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);
                } else {
                   updateBodyWrtStructural();
                   AttributeValue<LunarSimulation::AttitudeQuaternion > oldValue(_bodyWrtStructuralAttribute);

                   _bodyWrtStructuralAttribute.setEncodedValue(iter->second, federateId, logicalTime, timeStamp);

                   updateBodyWrtStructural();
                   if (_bodyWrtStructuralAttribute.hasValue()) {
                      firebody_wrt_structuralUpdated(_bodyWrtStructuralAttribute.getValue(), oldValue, timeStamp, logicalTime);
                   }
                   fireProducingFederateUpdated(HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL, _bodyWrtStructuralAttribute.getFederateId(), federateId, timeStamp, logicalTime);
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

void HlaDynamicalEntityImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaDynamicalEntityAttributesImpl>(getHlaDynamicalEntityAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaDynamicalEntityImpl::AttributeMap HlaDynamicalEntityImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
        if (iter->compare(FORCE_ATTRIBUTE_NAME) == 0) {
            updateForce();
            if (_forceAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::FORCE] = _forceAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(TORQUE_ATTRIBUTE_NAME) == 0) {
            updateTorque();
            if (_torqueAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::TORQUE] = _torqueAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(MASS_ATTRIBUTE_NAME) == 0) {
            updateMass();
            if (_massAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::MASS] = _massAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(MASS_RATE_ATTRIBUTE_NAME) == 0) {
            updateMassRate();
            if (_massRateAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::MASS_RATE] = _massRateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(INERTIA_ATTRIBUTE_NAME) == 0) {
            updateInertia();
            if (_inertiaAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::INERTIA] = _inertiaAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(INERTIA_RATE_ATTRIBUTE_NAME) == 0) {
            updateInertiaRate();
            if (_inertiaRateAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::INERTIA_RATE] = _inertiaRateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(NAME_ATTRIBUTE_NAME) == 0) {
            updateName();
            if (_nameAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::NAME] = _nameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(TYPE_ATTRIBUTE_NAME) == 0) {
            updateType();
            if (_typeAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::TYPE] = _typeAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATUS_ATTRIBUTE_NAME) == 0) {
            updateStatus();
            if (_statusAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::STATUS] = _statusAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME) == 0) {
            updateParentReferenceFrame();
            if (_parentReferenceFrameAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrameAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(STATE_ATTRIBUTE_NAME) == 0) {
            updateState();
            if (_stateAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::STATE] = _stateAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateAcceleration();
            if (_accelerationAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::ACCELERATION] = _accelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME) == 0) {
            updateRotationalAcceleration();
            if (_rotationalAccelerationAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION] = _rotationalAccelerationAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(CENTER_OF_MASS_ATTRIBUTE_NAME) == 0) {
            updateCenterOfMass();
            if (_centerOfMassAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::CENTER_OF_MASS] = _centerOfMassAttribute.getValue();
            }
            continue;
        }
        if (iter->compare(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME) == 0) {
            updateBodyWrtStructural();
            if (_bodyWrtStructuralAttribute.hasValue()) {
                res[HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructuralAttribute.getValue();
            }
            continue;
        }
    }
    return res;
}

RtiDriver::NameSet HlaDynamicalEntityImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaDynamicalEntityAttributesPtr attributes = getHlaDynamicalEntityAttributes();
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



HlaFederateIdPtr HlaDynamicalEntityImpl::getLastProducingFederate(HlaDynamicalEntityAttributes::Attribute attribute) {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    switch (attribute) {
        case HlaDynamicalEntityAttributes::FORCE: {
            if (_forceAttribute.hasFederateId()) {
                return _forceAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::TORQUE: {
            if (_torqueAttribute.hasFederateId()) {
                return _torqueAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::MASS: {
            if (_massAttribute.hasFederateId()) {
                return _massAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::MASS_RATE: {
            if (_massRateAttribute.hasFederateId()) {
                return _massRateAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::INERTIA: {
            if (_inertiaAttribute.hasFederateId()) {
                return _inertiaAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::INERTIA_RATE: {
            if (_inertiaRateAttribute.hasFederateId()) {
                return _inertiaRateAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::NAME: {
            if (_nameAttribute.hasFederateId()) {
                return _nameAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::TYPE: {
            if (_typeAttribute.hasFederateId()) {
                return _typeAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::STATUS: {
            if (_statusAttribute.hasFederateId()) {
                return _statusAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME: {
            if (_parentReferenceFrameAttribute.hasFederateId()) {
                return _parentReferenceFrameAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::STATE: {
            if (_stateAttribute.hasFederateId()) {
                return _stateAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::ACCELERATION: {
            if (_accelerationAttribute.hasFederateId()) {
                return _accelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION: {
            if (_rotationalAccelerationAttribute.hasFederateId()) {
                return _rotationalAccelerationAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::CENTER_OF_MASS: {
            if (_centerOfMassAttribute.hasFederateId()) {
                return _centerOfMassAttribute.getFederateId();
            }
            break;
        }
        case HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL: {
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
