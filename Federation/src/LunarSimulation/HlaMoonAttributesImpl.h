/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAMOONATTRIBUTESIMPL_H
#define DEVELOPER_STUDIO_HLAMOONATTRIBUTESIMPL_H

#include <string>
#include <vector>

#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>

#include <LunarSimulation/HlaMoonAttributes.h>
#include "AttributeValue.h"
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

    class HlaMoonAttributesImpl : public HlaMoonAttributes {
    public:
        HlaMoonAttributesImpl(
            const AttributeValue<std::wstring >& name,
            const AttributeValue<std::wstring >& parentName,
            const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& state
        )
        :
            _name(name),
            _parentName(parentName),
            _state(state)
        {}

        bool hasName();
        std::wstring getName() THROW_SPEC (HlaValueNotSetException);
        std::wstring getName(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getNameTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasParentName();
        std::wstring getParentName() THROW_SPEC (HlaValueNotSetException);
        std::wstring getParentName(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getParentNameTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasState();
        LunarSimulation::SpaceTimeCoordinateState getState() THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::SpaceTimeCoordinateState getState(LunarSimulation::SpaceTimeCoordinateState defaultValue);
        LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > getStateTimeStamped() THROW_SPEC (HlaValueNotSetException);
    
    private:
        AttributeValue<std::wstring > _name;
        AttributeValue<std::wstring > _parentName;
        AttributeValue<LunarSimulation::SpaceTimeCoordinateState > _state;
    };
}
#endif
