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

#include "HlaPhysicalEntityAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaPhysicalEntityAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaPhysicalEntityAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaPhysicalEntityAttributes::NAME] = L"name";
    nameMap[HlaPhysicalEntityAttributes::TYPE] = L"type";
    nameMap[HlaPhysicalEntityAttributes::STATUS] = L"status";
    nameMap[HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME] = L"parent_reference_frame";
    nameMap[HlaPhysicalEntityAttributes::STATE] = L"state";
    nameMap[HlaPhysicalEntityAttributes::ACCELERATION] = L"acceleration";
    nameMap[HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION] = L"rotational_acceleration";
    nameMap[HlaPhysicalEntityAttributes::CENTER_OF_MASS] = L"center_of_mass";
    nameMap[HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL] = L"body_wrt_structural";
    return nameMap;
}

static  std::map<std::wstring, HlaPhysicalEntityAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaPhysicalEntityAttributes::Attribute> attributeMap;
    attributeMap[L"name"] = HlaPhysicalEntityAttributes::NAME;
    attributeMap[L"type"] = HlaPhysicalEntityAttributes::TYPE;
    attributeMap[L"status"] = HlaPhysicalEntityAttributes::STATUS;
    attributeMap[L"parent_reference_frame"] = HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME;
    attributeMap[L"state"] = HlaPhysicalEntityAttributes::STATE;
    attributeMap[L"acceleration"] = HlaPhysicalEntityAttributes::ACCELERATION;
    attributeMap[L"rotational_acceleration"] = HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION;
    attributeMap[L"center_of_mass"] = HlaPhysicalEntityAttributes::CENTER_OF_MASS;
    attributeMap[L"body_wrt_structural"] = HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL;
    return attributeMap;
}

static std::map<HlaPhysicalEntityAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaPhysicalEntityAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaPhysicalEntityAttributesImpl::hasName() {
   return _name.hasValue();
}

std::wstring HlaPhysicalEntityAttributesImpl::getName()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

std::wstring HlaPhysicalEntityAttributesImpl::getName(std::wstring defaultValue) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityAttributesImpl::getNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return _name.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasType() {
   return _type.hasValue();
}

std::wstring HlaPhysicalEntityAttributesImpl::getType()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

std::wstring HlaPhysicalEntityAttributesImpl::getType(std::wstring defaultValue) {
   if (_type.hasValue()) {
      return *_type.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityAttributesImpl::getTypeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_type.hasValue()) {
      return _type.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'type' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasStatus() {
   return _status.hasValue();
}

std::wstring HlaPhysicalEntityAttributesImpl::getStatus()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

std::wstring HlaPhysicalEntityAttributesImpl::getStatus(std::wstring defaultValue) {
   if (_status.hasValue()) {
      return *_status.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityAttributesImpl::getStatusTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_status.hasValue()) {
      return _status.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'status' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasParentReferenceFrame() {
   return _parentReferenceFrame.hasValue();
}

std::wstring HlaPhysicalEntityAttributesImpl::getParentReferenceFrame()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

std::wstring HlaPhysicalEntityAttributesImpl::getParentReferenceFrame(std::wstring defaultValue) {
   if (_parentReferenceFrame.hasValue()) {
      return *_parentReferenceFrame.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalEntityAttributesImpl::getParentReferenceFrameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentReferenceFrame.hasValue()) {
      return _parentReferenceFrame.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentReferenceFrame' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasState() {
   return _state.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaPhysicalEntityAttributesImpl::getState()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

LunarSimulation::SpaceTimeCoordinateState HlaPhysicalEntityAttributesImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaPhysicalEntityAttributesImpl::getStateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return _state.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasAcceleration() {
   return _acceleration.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalEntityAttributesImpl::getAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

std::vector</* 3 */ double > HlaPhysicalEntityAttributesImpl::getAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_acceleration.hasValue()) {
      return *_acceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalEntityAttributesImpl::getAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_acceleration.hasValue()) {
      return _acceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'acceleration' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasRotationalAcceleration() {
   return _rotationalAcceleration.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalEntityAttributesImpl::getRotationalAcceleration()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

std::vector</* 3 */ double > HlaPhysicalEntityAttributesImpl::getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) {
   if (_rotationalAcceleration.hasValue()) {
      return *_rotationalAcceleration.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalEntityAttributesImpl::getRotationalAccelerationTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_rotationalAcceleration.hasValue()) {
      return _rotationalAcceleration.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rotationalAcceleration' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasCenterOfMass() {
   return _centerOfMass.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalEntityAttributesImpl::getCenterOfMass()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

std::vector</* 3 */ double > HlaPhysicalEntityAttributesImpl::getCenterOfMass(std::vector</* 3 */ double > defaultValue) {
   if (_centerOfMass.hasValue()) {
      return *_centerOfMass.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalEntityAttributesImpl::getCenterOfMassTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_centerOfMass.hasValue()) {
      return _centerOfMass.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'centerOfMass' not set");
}

bool HlaPhysicalEntityAttributesImpl::hasBodyWrtStructural() {
   return _bodyWrtStructural.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaPhysicalEntityAttributesImpl::getBodyWrtStructural()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}

LunarSimulation::AttitudeQuaternion HlaPhysicalEntityAttributesImpl::getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) {
   if (_bodyWrtStructural.hasValue()) {
      return *_bodyWrtStructural.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaPhysicalEntityAttributesImpl::getBodyWrtStructuralTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_bodyWrtStructural.hasValue()) {
      return _bodyWrtStructural.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'bodyWrtStructural' not set");
}


std::wstring HlaPhysicalEntityAttributes::getName(Attribute attribute) {
    std::map<HlaPhysicalEntityAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaPhysicalEntityAttributes::find(HlaPhysicalEntityAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaPhysicalEntityAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

