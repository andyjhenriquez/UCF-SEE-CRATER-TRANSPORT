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

#include "HlaPhysicalInterfaceAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaPhysicalInterfaceAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaPhysicalInterfaceAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaPhysicalInterfaceAttributes::NAME] = L"name";
    nameMap[HlaPhysicalInterfaceAttributes::PARENT_NAME] = L"parent_name";
    nameMap[HlaPhysicalInterfaceAttributes::POSITION] = L"position";
    nameMap[HlaPhysicalInterfaceAttributes::ATTITUDE] = L"attitude";
    return nameMap;
}

static  std::map<std::wstring, HlaPhysicalInterfaceAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaPhysicalInterfaceAttributes::Attribute> attributeMap;
    attributeMap[L"name"] = HlaPhysicalInterfaceAttributes::NAME;
    attributeMap[L"parent_name"] = HlaPhysicalInterfaceAttributes::PARENT_NAME;
    attributeMap[L"position"] = HlaPhysicalInterfaceAttributes::POSITION;
    attributeMap[L"attitude"] = HlaPhysicalInterfaceAttributes::ATTITUDE;
    return attributeMap;
}

static std::map<HlaPhysicalInterfaceAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaPhysicalInterfaceAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaPhysicalInterfaceAttributesImpl::hasName() {
   return _name.hasValue();
}

std::wstring HlaPhysicalInterfaceAttributesImpl::getName()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

std::wstring HlaPhysicalInterfaceAttributesImpl::getName(std::wstring defaultValue) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalInterfaceAttributesImpl::getNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return _name.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

bool HlaPhysicalInterfaceAttributesImpl::hasParentName() {
   return _parentName.hasValue();
}

std::wstring HlaPhysicalInterfaceAttributesImpl::getParentName()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentName.hasValue()) {
      return *_parentName.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentName' not set");
}

std::wstring HlaPhysicalInterfaceAttributesImpl::getParentName(std::wstring defaultValue) {
   if (_parentName.hasValue()) {
      return *_parentName.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaPhysicalInterfaceAttributesImpl::getParentNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentName.hasValue()) {
      return _parentName.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentName' not set");
}

bool HlaPhysicalInterfaceAttributesImpl::hasPosition() {
   return _position.hasValue();
}

std::vector</* 3 */ double > HlaPhysicalInterfaceAttributesImpl::getPosition()
THROW_SPEC (HlaValueNotSetException) {
   if (_position.hasValue()) {
      return *_position.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'position' not set");
}

std::vector</* 3 */ double > HlaPhysicalInterfaceAttributesImpl::getPosition(std::vector</* 3 */ double > defaultValue) {
   if (_position.hasValue()) {
      return *_position.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > HlaPhysicalInterfaceAttributesImpl::getPositionTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_position.hasValue()) {
      return _position.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'position' not set");
}

bool HlaPhysicalInterfaceAttributesImpl::hasAttitude() {
   return _attitude.hasValue();
}

LunarSimulation::AttitudeQuaternion HlaPhysicalInterfaceAttributesImpl::getAttitude()
THROW_SPEC (HlaValueNotSetException) {
   if (_attitude.hasValue()) {
      return *_attitude.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'attitude' not set");
}

LunarSimulation::AttitudeQuaternion HlaPhysicalInterfaceAttributesImpl::getAttitude(LunarSimulation::AttitudeQuaternion defaultValue) {
   if (_attitude.hasValue()) {
      return *_attitude.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > HlaPhysicalInterfaceAttributesImpl::getAttitudeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_attitude.hasValue()) {
      return _attitude.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'attitude' not set");
}


std::wstring HlaPhysicalInterfaceAttributes::getName(Attribute attribute) {
    std::map<HlaPhysicalInterfaceAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaPhysicalInterfaceAttributes::find(HlaPhysicalInterfaceAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaPhysicalInterfaceAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

