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

#include "HlaLauncherAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaLauncherAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaLauncherAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaLauncherAttributes::POSITION] = L"position";
    nameMap[HlaLauncherAttributes::MASS] = L"mass";
    nameMap[HlaLauncherAttributes::ENERGY] = L"energy";
    nameMap[HlaLauncherAttributes::NAME] = L"name";
    nameMap[HlaLauncherAttributes::TYPE] = L"type";
    nameMap[HlaLauncherAttributes::STATUS] = L"status";
    nameMap[HlaLauncherAttributes::PARENT_REFERENCE_FRAME] = L"parent_reference_frame";
    nameMap[HlaLauncherAttributes::STATE] = L"state";
    nameMap[HlaLauncherAttributes::ACCELERATION] = L"acceleration";
    nameMap[HlaLauncherAttributes::ROTATIONAL_ACCELERATION] = L"rotational_acceleration";
    nameMap[HlaLauncherAttributes::CENTER_OF_MASS] = L"center_of_mass";
    nameMap[HlaLauncherAttributes::BODY_WRT_STRUCTURAL] = L"body_wrt_structural";
    return nameMap;
}

static  std::map<std::wstring, HlaLauncherAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaLauncherAttributes::Attribute> attributeMap;
    attributeMap[L"position"] = HlaLauncherAttributes::POSITION;
    attributeMap[L"mass"] = HlaLauncherAttributes::MASS;
    attributeMap[L"energy"] = HlaLauncherAttributes::ENERGY;
    attributeMap[L"name"] = HlaLauncherAttributes::NAME;
    attributeMap[L"type"] = HlaLauncherAttributes::TYPE;
    attributeMap[L"status"] = HlaLauncherAttributes::STATUS;
    attributeMap[L"parent_reference_frame"] = HlaLauncherAttributes::PARENT_REFERENCE_FRAME;
    attributeMap[L"state"] = HlaLauncherAttributes::STATE;
    attributeMap[L"acceleration"] = HlaLauncherAttributes::ACCELERATION;
    attributeMap[L"rotational_acceleration"] = HlaLauncherAttributes::ROTATIONAL_ACCELERATION;
    attributeMap[L"center_of_mass"] = HlaLauncherAttributes::CENTER_OF_MASS;
    attributeMap[L"body_wrt_structural"] = HlaLauncherAttributes::BODY_WRT_STRUCTURAL;
    return attributeMap;
}

static std::map<HlaLauncherAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaLauncherAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaLauncherAttributesImpl::hasPosition() {
   return _position.hasValue();
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getPosition()
THROW_SPEC (HlaValueNotSetException) {
   if (_position.hasValue()) {
      return *_position.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'position' not set");
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getPosition(std::vector</* 3 */ double > defaultValue) {
   if (_position.hasValue()) {
      return *_position.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherAttributesImpl::getPositionTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_position.hasValue()) {
      return _position.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'position' not set");
}

bool HlaLauncherAttributesImpl::hasMass() {
   return _mass.hasValue();
}

double HlaLauncherAttributesImpl::getMass()
THROW_SPEC (HlaValueNotSetException) {
   if (_mass.hasValue()) {
      return *_mass.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'mass' not set");
}

double HlaLauncherAttributesImpl::getMass(double defaultValue) {
   if (_mass.hasValue()) {
      return *_mass.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaLauncherAttributesImpl::getMassTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_mass.hasValue()) {
      return _mass.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'mass' not set");
}

bool HlaLauncherAttributesImpl::hasEnergy() {
   return _energy.hasValue();
}

double HlaLauncherAttributesImpl::getEnergy()
THROW_SPEC (HlaValueNotSetException) {
   if (_energy.hasValue()) {
      return *_energy.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'energy' not set");
}

double HlaLauncherAttributesImpl::getEnergy(double defaultValue) {
   if (_energy.hasValue()) {
      return *_energy.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaLauncherAttributesImpl::getEnergyTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_energy.hasValue()) {
      return _energy.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'energy' not set");
}

bool HlaLauncherAttributesImpl::hasName() {
   return _name.hasValue();
}

std::wstring HlaLauncherAttributesImpl::getName()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

std::wstring HlaLauncherAttributesImpl::getName(std::wstring defaultValue) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherAttributesImpl::getNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return _name.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

bool HlaLauncherAttributesImpl::hasType() {
   return _type.hasValue();
}

std::wstring HlaLauncherAttributesImpl::getType()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

std::wstring HlaLauncherAttributesImpl::getType(std::wstring defaultValue) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherAttributesImpl::getTypeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return _type.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

bool HlaLauncherAttributesImpl::hasStatus() {
   return _status.hasValue();
}

std::wstring HlaLauncherAttributesImpl::getStatus()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

std::wstring HlaLauncherAttributesImpl::getStatus(std::wstring defaultValue) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherAttributesImpl::getStatusTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return _status.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

bool HlaLauncherAttributesImpl::hasParentReferenceFrame() {
   return _parentReferenceFrame.hasValue();
}

std::wstring HlaLauncherAttributesImpl::getParentReferenceFrame()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

std::wstring HlaLauncherAttributesImpl::getParentReferenceFrame(std::wstring defaultValue) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaLauncherAttributesImpl::getParentReferenceFrameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return _parentReferenceFrame.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

bool HlaLauncherAttributesImpl::hasState() {
   return _state.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaLauncherAttributesImpl::getState()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

LunarSimulation::SpaceTimeCoordinateState HlaLauncherAttributesImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaLauncherAttributesImpl::getStateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return _state.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

bool HlaLauncherAttributesImpl::hasAcceleration() {
   return _acceleration.hasValue();
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherAttributesImpl::getAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return _acceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

bool HlaLauncherAttributesImpl::hasRotationalAcceleration() {
   return _rotationalAcceleration.hasValue();
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getRotationalAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherAttributesImpl::getRotationalAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return _rotationalAcceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

bool HlaLauncherAttributesImpl::hasCenterOfMass() {
   return _centerOfMass.hasValue();
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getCenterOfMass()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

std::vector</* 3 */ double > HlaLauncherAttributesImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaLauncherAttributesImpl::getCenterOfMassTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return _centerOfMass.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

bool HlaLauncherAttributesImpl::hasBodyWrtStructural() {
   return _bodyWrtStructural.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaLauncherAttributesImpl::getBodyWrtStructural()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}

LunarSimulation::AttitudeQuaternion HlaLauncherAttributesImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaLauncherAttributesImpl::getBodyWrtStructuralTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return _bodyWrtStructural.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}


std::wstring HlaLauncherAttributes::getName(Attribute attribute) {
    std::map<HlaLauncherAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaLauncherAttributes::find(HlaLauncherAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaLauncherAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

