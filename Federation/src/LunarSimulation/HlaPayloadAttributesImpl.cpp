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

#include "HlaPayloadAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaPayloadAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaPayloadAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaPayloadAttributes::POSITION] = L"position";
    nameMap[HlaPayloadAttributes::VELOCITY] = L"velocity";
    nameMap[HlaPayloadAttributes::HEALTH] = L"health";
    nameMap[HlaPayloadAttributes::FORCE] = L"force";
    nameMap[HlaPayloadAttributes::TORQUE] = L"torque";
    nameMap[HlaPayloadAttributes::MASS] = L"mass";
    nameMap[HlaPayloadAttributes::MASS_RATE] = L"mass_rate";
    nameMap[HlaPayloadAttributes::INERTIA] = L"inertia";
    nameMap[HlaPayloadAttributes::INERTIA_RATE] = L"inertia_rate";
    nameMap[HlaPayloadAttributes::NAME] = L"name";
    nameMap[HlaPayloadAttributes::TYPE] = L"type";
    nameMap[HlaPayloadAttributes::STATUS] = L"status";
    nameMap[HlaPayloadAttributes::PARENT_REFERENCE_FRAME] = L"parent_reference_frame";
    nameMap[HlaPayloadAttributes::STATE] = L"state";
    nameMap[HlaPayloadAttributes::ACCELERATION] = L"acceleration";
    nameMap[HlaPayloadAttributes::ROTATIONAL_ACCELERATION] = L"rotational_acceleration";
    nameMap[HlaPayloadAttributes::CENTER_OF_MASS] = L"center_of_mass";
    nameMap[HlaPayloadAttributes::BODY_WRT_STRUCTURAL] = L"body_wrt_structural";
    return nameMap;
}

static  std::map<std::wstring, HlaPayloadAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaPayloadAttributes::Attribute> attributeMap;
    attributeMap[L"position"] = HlaPayloadAttributes::POSITION;
    attributeMap[L"velocity"] = HlaPayloadAttributes::VELOCITY;
    attributeMap[L"health"] = HlaPayloadAttributes::HEALTH;
    attributeMap[L"force"] = HlaPayloadAttributes::FORCE;
    attributeMap[L"torque"] = HlaPayloadAttributes::TORQUE;
    attributeMap[L"mass"] = HlaPayloadAttributes::MASS;
    attributeMap[L"mass_rate"] = HlaPayloadAttributes::MASS_RATE;
    attributeMap[L"inertia"] = HlaPayloadAttributes::INERTIA;
    attributeMap[L"inertia_rate"] = HlaPayloadAttributes::INERTIA_RATE;
    attributeMap[L"name"] = HlaPayloadAttributes::NAME;
    attributeMap[L"type"] = HlaPayloadAttributes::TYPE;
    attributeMap[L"status"] = HlaPayloadAttributes::STATUS;
    attributeMap[L"parent_reference_frame"] = HlaPayloadAttributes::PARENT_REFERENCE_FRAME;
    attributeMap[L"state"] = HlaPayloadAttributes::STATE;
    attributeMap[L"acceleration"] = HlaPayloadAttributes::ACCELERATION;
    attributeMap[L"rotational_acceleration"] = HlaPayloadAttributes::ROTATIONAL_ACCELERATION;
    attributeMap[L"center_of_mass"] = HlaPayloadAttributes::CENTER_OF_MASS;
    attributeMap[L"body_wrt_structural"] = HlaPayloadAttributes::BODY_WRT_STRUCTURAL;
    return attributeMap;
}

static std::map<HlaPayloadAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaPayloadAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaPayloadAttributesImpl::hasPosition() {
   return _position.hasValue();
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getPosition()
THROW_SPEC (HlaValueNotSetException) {
   if (_position.hasValue()) {
      return *_position.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'position' not set");
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getPosition(std::vector</* 3 */ double > defaultValue) {
   if (_position.hasValue()) {
      return *_position.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadAttributesImpl::getPositionTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_position.hasValue()) {
      return _position.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'position' not set");
}

bool HlaPayloadAttributesImpl::hasVelocity() {
   return _velocity.hasValue();
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getVelocity()
THROW_SPEC (HlaValueNotSetException) {
   if (_velocity.hasValue()) {
      return *_velocity.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'velocity' not set");
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getVelocity(std::vector</* 3 */ double > defaultValue) {
   if (_velocity.hasValue()) {
      return *_velocity.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadAttributesImpl::getVelocityTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_velocity.hasValue()) {
      return _velocity.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'velocity' not set");
}

bool HlaPayloadAttributesImpl::hasHealth() {
   return _health.hasValue();
}

double HlaPayloadAttributesImpl::getHealth()
THROW_SPEC (HlaValueNotSetException) {
   if (_health.hasValue()) {
      return *_health.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'health' not set");
}

double HlaPayloadAttributesImpl::getHealth(double defaultValue) {
   if (_health.hasValue()) {
      return *_health.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaPayloadAttributesImpl::getHealthTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_health.hasValue()) {
      return _health.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'health' not set");
}

bool HlaPayloadAttributesImpl::hasForce() {
   return _force.hasValue();
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getForce()
THROW_SPEC (HlaValueNotSetException) {
   if (_force.hasValue()) {
      return *_force.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'force' not set");
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getForce(std::vector</* 3 */ double > defaultValue) {
   if (_force.hasValue()) {
      return *_force.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadAttributesImpl::getForceTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_force.hasValue()) {
      return _force.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'force' not set");
}

bool HlaPayloadAttributesImpl::hasTorque() {
   return _torque.hasValue();
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getTorque()
THROW_SPEC (HlaValueNotSetException) {
   if (_torque.hasValue()) {
      return *_torque.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'torque' not set");
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getTorque(std::vector</* 3 */ double > defaultValue) {
   if (_torque.hasValue()) {
      return *_torque.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadAttributesImpl::getTorqueTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_torque.hasValue()) {
      return _torque.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'torque' not set");
}

bool HlaPayloadAttributesImpl::hasMass() {
   return _mass.hasValue();
}

double HlaPayloadAttributesImpl::getMass()
THROW_SPEC (HlaValueNotSetException) {
   if (_mass.hasValue()) {
      return *_mass.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'mass' not set");
}

double HlaPayloadAttributesImpl::getMass(double defaultValue) {
   if (_mass.hasValue()) {
      return *_mass.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaPayloadAttributesImpl::getMassTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_mass.hasValue()) {
      return _mass.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'mass' not set");
}

bool HlaPayloadAttributesImpl::hasMassRate() {
   return _massRate.hasValue();
}

double HlaPayloadAttributesImpl::getMassRate()
THROW_SPEC (HlaValueNotSetException) {
   if (_massRate.hasValue()) {
      return *_massRate.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'massRate' not set");
}

double HlaPayloadAttributesImpl::getMassRate(double defaultValue) {
   if (_massRate.hasValue()) {
      return *_massRate.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaPayloadAttributesImpl::getMassRateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_massRate.hasValue()) {
      return _massRate.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'massRate' not set");
}

bool HlaPayloadAttributesImpl::hasInertia() {
   return _inertia.hasValue();
}

std::vector</* 9 */ double > HlaPayloadAttributesImpl::getInertia()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertia.hasValue()) {
      return *_inertia.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertia' not set");
}

std::vector</* 9 */ double > HlaPayloadAttributesImpl::getInertia(std::vector</* 9 */ double > defaultValue) {
   if (_inertia.hasValue()) {
      return *_inertia.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaPayloadAttributesImpl::getInertiaTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertia.hasValue()) {
      return _inertia.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertia' not set");
}

bool HlaPayloadAttributesImpl::hasInertiaRate() {
   return _inertiaRate.hasValue();
}

std::vector</* 9 */ double > HlaPayloadAttributesImpl::getInertiaRate()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertiaRate.hasValue()) {
      return *_inertiaRate.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set");
}

std::vector</* 9 */ double > HlaPayloadAttributesImpl::getInertiaRate(std::vector</* 9 */ double > defaultValue) {
   if (_inertiaRate.hasValue()) {
      return *_inertiaRate.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 9 */ double > > HlaPayloadAttributesImpl::getInertiaRateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_inertiaRate.hasValue()) {
      return _inertiaRate.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'inertiaRate' not set");
}

bool HlaPayloadAttributesImpl::hasName() {
   return _name.hasValue();
}

std::wstring HlaPayloadAttributesImpl::getName()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

std::wstring HlaPayloadAttributesImpl::getName(std::wstring defaultValue) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadAttributesImpl::getNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return _name.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

bool HlaPayloadAttributesImpl::hasType() {
   return _type.hasValue();
}

std::wstring HlaPayloadAttributesImpl::getType()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

std::wstring HlaPayloadAttributesImpl::getType(std::wstring defaultValue) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadAttributesImpl::getTypeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return _type.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

bool HlaPayloadAttributesImpl::hasStatus() {
   return _status.hasValue();
}

std::wstring HlaPayloadAttributesImpl::getStatus()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

std::wstring HlaPayloadAttributesImpl::getStatus(std::wstring defaultValue) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadAttributesImpl::getStatusTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return _status.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

bool HlaPayloadAttributesImpl::hasParentReferenceFrame() {
   return _parentReferenceFrame.hasValue();
}

std::wstring HlaPayloadAttributesImpl::getParentReferenceFrame()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

std::wstring HlaPayloadAttributesImpl::getParentReferenceFrame(std::wstring defaultValue) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPayloadAttributesImpl::getParentReferenceFrameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return _parentReferenceFrame.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

bool HlaPayloadAttributesImpl::hasState() {
   return _state.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaPayloadAttributesImpl::getState()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

LunarSimulation::SpaceTimeCoordinateState HlaPayloadAttributesImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaPayloadAttributesImpl::getStateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return _state.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

bool HlaPayloadAttributesImpl::hasAcceleration() {
   return _acceleration.hasValue();
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadAttributesImpl::getAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return _acceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

bool HlaPayloadAttributesImpl::hasRotationalAcceleration() {
   return _rotationalAcceleration.hasValue();
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getRotationalAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadAttributesImpl::getRotationalAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return _rotationalAcceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

bool HlaPayloadAttributesImpl::hasCenterOfMass() {
   return _centerOfMass.hasValue();
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getCenterOfMass()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

std::vector</* 3 */ double > HlaPayloadAttributesImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPayloadAttributesImpl::getCenterOfMassTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return _centerOfMass.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

bool HlaPayloadAttributesImpl::hasBodyWrtStructural() {
   return _bodyWrtStructural.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaPayloadAttributesImpl::getBodyWrtStructural()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}

LunarSimulation::AttitudeQuaternion HlaPayloadAttributesImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaPayloadAttributesImpl::getBodyWrtStructuralTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return _bodyWrtStructural.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}


std::wstring HlaPayloadAttributes::getName(Attribute attribute) {
    std::map<HlaPayloadAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaPayloadAttributes::find(HlaPayloadAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaPayloadAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

