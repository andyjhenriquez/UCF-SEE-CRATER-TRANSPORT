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

#include "HlaDynamicalEntityAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaDynamicalEntityAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaDynamicalEntityAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaDynamicalEntityAttributes::FORCE] = L"force";
    nameMap[HlaDynamicalEntityAttributes::TORQUE] = L"torque";
    nameMap[HlaDynamicalEntityAttributes::MASS] = L"mass";
    nameMap[HlaDynamicalEntityAttributes::MASS_RATE] = L"mass_rate";
    nameMap[HlaDynamicalEntityAttributes::INERTIA] = L"inertia";
    nameMap[HlaDynamicalEntityAttributes::INERTIA_RATE] = L"inertia_rate";
    nameMap[HlaDynamicalEntityAttributes::NAME] = L"name";
    nameMap[HlaDynamicalEntityAttributes::TYPE] = L"type";
    nameMap[HlaDynamicalEntityAttributes::STATUS] = L"status";
    nameMap[HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME] = L"parent_reference_frame";
    nameMap[HlaDynamicalEntityAttributes::STATE] = L"state";
    nameMap[HlaDynamicalEntityAttributes::ACCELERATION] = L"acceleration";
    nameMap[HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION] = L"rotational_acceleration";
    nameMap[HlaDynamicalEntityAttributes::CENTER_OF_MASS] = L"center_of_mass";
    nameMap[HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL] = L"body_wrt_structural";
    return nameMap;
}

static  std::map<std::wstring, HlaDynamicalEntityAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaDynamicalEntityAttributes::Attribute> attributeMap;
    attributeMap[L"force"] = HlaDynamicalEntityAttributes::FORCE;
    attributeMap[L"torque"] = HlaDynamicalEntityAttributes::TORQUE;
    attributeMap[L"mass"] = HlaDynamicalEntityAttributes::MASS;
    attributeMap[L"mass_rate"] = HlaDynamicalEntityAttributes::MASS_RATE;
    attributeMap[L"inertia"] = HlaDynamicalEntityAttributes::INERTIA;
    attributeMap[L"inertia_rate"] = HlaDynamicalEntityAttributes::INERTIA_RATE;
    attributeMap[L"name"] = HlaDynamicalEntityAttributes::NAME;
    attributeMap[L"type"] = HlaDynamicalEntityAttributes::TYPE;
    attributeMap[L"status"] = HlaDynamicalEntityAttributes::STATUS;
    attributeMap[L"parent_reference_frame"] = HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME;
    attributeMap[L"state"] = HlaDynamicalEntityAttributes::STATE;
    attributeMap[L"acceleration"] = HlaDynamicalEntityAttributes::ACCELERATION;
    attributeMap[L"rotational_acceleration"] = HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION;
    attributeMap[L"center_of_mass"] = HlaDynamicalEntityAttributes::CENTER_OF_MASS;
    attributeMap[L"body_wrt_structural"] = HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL;
    return attributeMap;
}

static std::map<HlaDynamicalEntityAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaDynamicalEntityAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaDynamicalEntityAttributesImpl::hasForce() {
   return _force.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getForce()
THROW_SPEC (HlaValueNotSetException) {
   if (_force.hasValue()) {
      return *_force.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'force' not set");
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getForce(std::vector</* 3 */ double > defaultValue) {
   if (_force.hasValue()) {
      return *_force.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityAttributesImpl::getForceTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_force.hasValue()) {
      return _force.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'force' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasTorque() {
   return _torque.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getTorque()
THROW_SPEC (HlaValueNotSetException) {
   if (_torque.hasValue()) {
      return *_torque.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'torque' not set");
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getTorque(std::vector</* 3 */ double > defaultValue) {
   if (_torque.hasValue()) {
      return *_torque.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityAttributesImpl::getTorqueTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_torque.hasValue()) {
      return _torque.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'torque' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasMass() {
   return _mass.hasValue();
}

double HlaDynamicalEntityAttributesImpl::getMass()
THROW_SPEC (HlaValueNotSetException) {
   if (_mass.hasValue()) {
      return *_mass.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'mass' not set");
}

double HlaDynamicalEntityAttributesImpl::getMass(double defaultValue) {
   if (_mass.hasValue()) {
      return *_mass.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaDynamicalEntityAttributesImpl::getMassTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_mass.hasValue()) {
      return _mass.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'mass' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasMassRate() {
   return _massRate.hasValue();
}

double HlaDynamicalEntityAttributesImpl::getMassRate()
THROW_SPEC (HlaValueNotSetException) {
   if (_massRate.hasValue()) {
      return *_massRate.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'massRate' not set");
}

double HlaDynamicalEntityAttributesImpl::getMassRate(double defaultValue) {
   if (_massRate.hasValue()) {
      return *_massRate.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaDynamicalEntityAttributesImpl::getMassRateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_massRate.hasValue()) {
      return _massRate.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'massRate' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasInertia() {
   return _inertia.hasValue();
}

std::vector</* 9 */ double > HlaDynamicalEntityAttributesImpl::getInertia()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertia.hasValue()) {
      return *_inertia.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertia' not set");
}

std::vector</* 9 */ double > HlaDynamicalEntityAttributesImpl::getInertia(std::vector</* 9 */ double > defaultValue) {
   if (_inertia.hasValue()) {
      return *_inertia.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaDynamicalEntityAttributesImpl::getInertiaTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertia.hasValue()) {
      return _inertia.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertia' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasInertiaRate() {
   return _inertiaRate.hasValue();
}

std::vector</* 9 */ double > HlaDynamicalEntityAttributesImpl::getInertiaRate()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertiaRate.hasValue()) {
      return *_inertiaRate.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set");
}

std::vector</* 9 */ double > HlaDynamicalEntityAttributesImpl::getInertiaRate(std::vector</* 9 */ double > defaultValue) {
   if (_inertiaRate.hasValue()) {
      return *_inertiaRate.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaDynamicalEntityAttributesImpl::getInertiaRateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertiaRate.hasValue()) {
      return _inertiaRate.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasName() {
   return _name.hasValue();
}

std::wstring HlaDynamicalEntityAttributesImpl::getName()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

std::wstring HlaDynamicalEntityAttributesImpl::getName(std::wstring defaultValue) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityAttributesImpl::getNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return _name.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasType() {
   return _type.hasValue();
}

std::wstring HlaDynamicalEntityAttributesImpl::getType()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

std::wstring HlaDynamicalEntityAttributesImpl::getType(std::wstring defaultValue) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityAttributesImpl::getTypeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return _type.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasStatus() {
   return _status.hasValue();
}

std::wstring HlaDynamicalEntityAttributesImpl::getStatus()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

std::wstring HlaDynamicalEntityAttributesImpl::getStatus(std::wstring defaultValue) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityAttributesImpl::getStatusTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return _status.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasParentReferenceFrame() {
   return _parentReferenceFrame.hasValue();
}

std::wstring HlaDynamicalEntityAttributesImpl::getParentReferenceFrame()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

std::wstring HlaDynamicalEntityAttributesImpl::getParentReferenceFrame(std::wstring defaultValue) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaDynamicalEntityAttributesImpl::getParentReferenceFrameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return _parentReferenceFrame.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasState() {
   return _state.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaDynamicalEntityAttributesImpl::getState()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

LunarSimulation::SpaceTimeCoordinateState HlaDynamicalEntityAttributesImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaDynamicalEntityAttributesImpl::getStateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return _state.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasAcceleration() {
   return _acceleration.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityAttributesImpl::getAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return _acceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasRotationalAcceleration() {
   return _rotationalAcceleration.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getRotationalAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityAttributesImpl::getRotationalAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return _rotationalAcceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasCenterOfMass() {
   return _centerOfMass.hasValue();
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getCenterOfMass()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

std::vector</* 3 */ double > HlaDynamicalEntityAttributesImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaDynamicalEntityAttributesImpl::getCenterOfMassTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return _centerOfMass.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

bool HlaDynamicalEntityAttributesImpl::hasBodyWrtStructural() {
   return _bodyWrtStructural.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaDynamicalEntityAttributesImpl::getBodyWrtStructural()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}

LunarSimulation::AttitudeQuaternion HlaDynamicalEntityAttributesImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaDynamicalEntityAttributesImpl::getBodyWrtStructuralTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return _bodyWrtStructural.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}


std::wstring HlaDynamicalEntityAttributes::getName(Attribute attribute) {
    std::map<HlaDynamicalEntityAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaDynamicalEntityAttributes::find(HlaDynamicalEntityAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaDynamicalEntityAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

