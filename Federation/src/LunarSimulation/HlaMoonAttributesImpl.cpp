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

#include "HlaMoonAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaMoonAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaMoonAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaMoonAttributes::NAME] = L"name";
    nameMap[HlaMoonAttributes::PARENT_NAME] = L"parent_name";
    nameMap[HlaMoonAttributes::STATE] = L"state";
    return nameMap;
}

static  std::map<std::wstring, HlaMoonAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaMoonAttributes::Attribute> attributeMap;
    attributeMap[L"name"] = HlaMoonAttributes::NAME;
    attributeMap[L"parent_name"] = HlaMoonAttributes::PARENT_NAME;
    attributeMap[L"state"] = HlaMoonAttributes::STATE;
    return attributeMap;
}

static std::map<HlaMoonAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaMoonAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaMoonAttributesImpl::hasName() {
   return _name.hasValue();
}

std::wstring HlaMoonAttributesImpl::getName()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

std::wstring HlaMoonAttributesImpl::getName(std::wstring defaultValue) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaMoonAttributesImpl::getNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return _name.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

bool HlaMoonAttributesImpl::hasParentName() {
   return _parentName.hasValue();
}

std::wstring HlaMoonAttributesImpl::getParentName()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentName.hasValue()) {
      return *_parentName.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentName' not set");
}

std::wstring HlaMoonAttributesImpl::getParentName(std::wstring defaultValue) {
   if (_parentName.hasValue()) {
      return *_parentName.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaMoonAttributesImpl::getParentNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentName.hasValue()) {
      return _parentName.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentName' not set");
}

bool HlaMoonAttributesImpl::hasState() {
   return _state.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaMoonAttributesImpl::getState()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

LunarSimulation::SpaceTimeCoordinateState HlaMoonAttributesImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaMoonAttributesImpl::getStateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return _state.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}


std::wstring HlaMoonAttributes::getName(Attribute attribute) {
    std::map<HlaMoonAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaMoonAttributes::find(HlaMoonAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaMoonAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

