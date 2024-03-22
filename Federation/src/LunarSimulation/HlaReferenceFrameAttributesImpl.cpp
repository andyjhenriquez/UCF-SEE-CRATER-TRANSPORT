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

#include "HlaReferenceFrameAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaReferenceFrameAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaReferenceFrameAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaReferenceFrameAttributes::NAME] = L"name";
    nameMap[HlaReferenceFrameAttributes::PARENT_NAME] = L"parent_name";
    nameMap[HlaReferenceFrameAttributes::STATE] = L"state";
    return nameMap;
}

static  std::map<std::wstring, HlaReferenceFrameAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaReferenceFrameAttributes::Attribute> attributeMap;
    attributeMap[L"name"] = HlaReferenceFrameAttributes::NAME;
    attributeMap[L"parent_name"] = HlaReferenceFrameAttributes::PARENT_NAME;
    attributeMap[L"state"] = HlaReferenceFrameAttributes::STATE;
    return attributeMap;
}

static std::map<HlaReferenceFrameAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaReferenceFrameAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaReferenceFrameAttributesImpl::hasName() {
   return _name.hasValue();
}

std::wstring HlaReferenceFrameAttributesImpl::getName()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

std::wstring HlaReferenceFrameAttributesImpl::getName(std::wstring defaultValue) {
   if (_name.hasValue()) {
      return *_name.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaReferenceFrameAttributesImpl::getNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_name.hasValue()) {
      return _name.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'name' not set");
}

bool HlaReferenceFrameAttributesImpl::hasParentName() {
   return _parentName.hasValue();
}

std::wstring HlaReferenceFrameAttributesImpl::getParentName()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentName.hasValue()) {
      return *_parentName.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentName' not set");
}

std::wstring HlaReferenceFrameAttributesImpl::getParentName(std::wstring defaultValue) {
   if (_parentName.hasValue()) {
      return *_parentName.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaReferenceFrameAttributesImpl::getParentNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_parentName.hasValue()) {
      return _parentName.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'parentName' not set");
}

bool HlaReferenceFrameAttributesImpl::hasState() {
   return _state.hasValue();
}

LunarSimulation::SpaceTimeCoordinateState HlaReferenceFrameAttributesImpl::getState()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}

LunarSimulation::SpaceTimeCoordinateState HlaReferenceFrameAttributesImpl::getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) {
   if (_state.hasValue()) {
      return *_state.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > HlaReferenceFrameAttributesImpl::getStateTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_state.hasValue()) {
      return _state.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'state' not set");
}


std::wstring HlaReferenceFrameAttributes::getName(Attribute attribute) {
    std::map<HlaReferenceFrameAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaReferenceFrameAttributes::find(HlaReferenceFrameAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaReferenceFrameAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

