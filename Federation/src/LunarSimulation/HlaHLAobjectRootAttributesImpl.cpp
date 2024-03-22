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

#include "HlaHLAobjectRootAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaHLAobjectRootAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaHLAobjectRootAttributes::Attribute, std::wstring> nameMap;
    return nameMap;
}

static  std::map<std::wstring, HlaHLAobjectRootAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaHLAobjectRootAttributes::Attribute> attributeMap;
    return attributeMap;
}

static std::map<HlaHLAobjectRootAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaHLAobjectRootAttributes::Attribute> _attributeMap = insertAttributes();


std::wstring HlaHLAobjectRootAttributes::getName(Attribute attribute) {
    std::map<HlaHLAobjectRootAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaHLAobjectRootAttributes::find(HlaHLAobjectRootAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaHLAobjectRootAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

