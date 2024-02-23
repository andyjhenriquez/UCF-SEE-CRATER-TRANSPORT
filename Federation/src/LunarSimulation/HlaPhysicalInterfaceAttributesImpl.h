/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEATTRIBUTESIMPL_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEATTRIBUTESIMPL_H

#include <string>
#include <vector>

#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaPhysicalInterfaceAttributes.h>
#include "AttributeValue.h"
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

    class HlaPhysicalInterfaceAttributesImpl : public HlaPhysicalInterfaceAttributes {
    public:
        HlaPhysicalInterfaceAttributesImpl(
            const AttributeValue<std::wstring >& name,
            const AttributeValue<std::wstring >& parentName,
            const AttributeValue<std::vector</* 3 */ double > >& position,
            const AttributeValue<LunarSimulation::AttitudeQuaternion >& attitude
        )
        :
            _name(name),
            _parentName(parentName),
            _position(position),
            _attitude(attitude)
        {}

        bool hasName();
        std::wstring getName() THROW_SPEC (HlaValueNotSetException);
        std::wstring getName(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getNameTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasParentName();
        std::wstring getParentName() THROW_SPEC (HlaValueNotSetException);
        std::wstring getParentName(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getParentNameTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasPosition();
        std::vector</* 3 */ double > getPosition() THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getPosition(std::vector</* 3 */ double > defaultValue);
        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getPositionTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasAttitude();
        LunarSimulation::AttitudeQuaternion getAttitude() THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::AttitudeQuaternion getAttitude(LunarSimulation::AttitudeQuaternion defaultValue);
        LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > getAttitudeTimeStamped() THROW_SPEC (HlaValueNotSetException);
    
    private:
        AttributeValue<std::wstring > _name;
        AttributeValue<std::wstring > _parentName;
        AttributeValue<std::vector</* 3 */ double > > _position;
        AttributeValue<LunarSimulation::AttitudeQuaternion > _attitude;
    };
}
#endif
