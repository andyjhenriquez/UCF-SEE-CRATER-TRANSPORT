/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALAUNCHERATTRIBUTESIMPL_H
#define DEVELOPER_STUDIO_HLALAUNCHERATTRIBUTESIMPL_H

#include <string>
#include <vector>

#include <LunarSimulation/datatypes/AccelerationVector.h>
#include <LunarSimulation/datatypes/AngularAccelerationVector.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaLauncherAttributes.h>
#include "AttributeValue.h"
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

    class HlaLauncherAttributesImpl : public HlaLauncherAttributes {
    public:
        HlaLauncherAttributesImpl(
            const AttributeValue<std::vector</* 3 */ double > >& position,
            const AttributeValue<double >& mass,
            const AttributeValue<double >& energy,
            const AttributeValue<std::wstring >& name,
            const AttributeValue<std::wstring >& type,
            const AttributeValue<std::wstring >& status,
            const AttributeValue<std::wstring >& parentReferenceFrame,
            const AttributeValue<LunarSimulation::SpaceTimeCoordinateState >& state,
            const AttributeValue<std::vector</* 3 */ double > >& acceleration,
            const AttributeValue<std::vector</* 3 */ double > >& rotationalAcceleration,
            const AttributeValue<std::vector</* 3 */ double > >& centerOfMass,
            const AttributeValue<LunarSimulation::AttitudeQuaternion >& bodyWrtStructural
        )
        :
            _position(position),
            _mass(mass),
            _energy(energy),
            _name(name),
            _type(type),
            _status(status),
            _parentReferenceFrame(parentReferenceFrame),
            _state(state),
            _acceleration(acceleration),
            _rotationalAcceleration(rotationalAcceleration),
            _centerOfMass(centerOfMass),
            _bodyWrtStructural(bodyWrtStructural)
        {}

        bool hasPosition();
        std::vector</* 3 */ double > getPosition() THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getPosition(std::vector</* 3 */ double > defaultValue);
        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getPositionTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasMass();
        double getMass() THROW_SPEC (HlaValueNotSetException);
        double getMass(double defaultValue);
        LunarSimulation::HlaTimeStamped< double > getMassTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasEnergy();
        double getEnergy() THROW_SPEC (HlaValueNotSetException);
        double getEnergy(double defaultValue);
        LunarSimulation::HlaTimeStamped< double > getEnergyTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasName();
        std::wstring getName() THROW_SPEC (HlaValueNotSetException);
        std::wstring getName(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getNameTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasType();
        std::wstring getType() THROW_SPEC (HlaValueNotSetException);
        std::wstring getType(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getTypeTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasStatus();
        std::wstring getStatus() THROW_SPEC (HlaValueNotSetException);
        std::wstring getStatus(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getStatusTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasParentReferenceFrame();
        std::wstring getParentReferenceFrame() THROW_SPEC (HlaValueNotSetException);
        std::wstring getParentReferenceFrame(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getParentReferenceFrameTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasState();
        LunarSimulation::SpaceTimeCoordinateState getState() THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::SpaceTimeCoordinateState getState(LunarSimulation::SpaceTimeCoordinateState defaultValue);
        LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > getStateTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasAcceleration();
        std::vector</* 3 */ double > getAcceleration() THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getAcceleration(std::vector</* 3 */ double > defaultValue);
        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasRotationalAcceleration();
        std::vector</* 3 */ double > getRotationalAcceleration() THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getRotationalAcceleration(std::vector</* 3 */ double > defaultValue);
        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getRotationalAccelerationTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasCenterOfMass();
        std::vector</* 3 */ double > getCenterOfMass() THROW_SPEC (HlaValueNotSetException);
        std::vector</* 3 */ double > getCenterOfMass(std::vector</* 3 */ double > defaultValue);
        LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getCenterOfMassTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasBodyWrtStructural();
        LunarSimulation::AttitudeQuaternion getBodyWrtStructural() THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::AttitudeQuaternion getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue);
        LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > getBodyWrtStructuralTimeStamped() THROW_SPEC (HlaValueNotSetException);
    
    private:
        AttributeValue<std::vector</* 3 */ double > > _position;
        AttributeValue<double > _mass;
        AttributeValue<double > _energy;
        AttributeValue<std::wstring > _name;
        AttributeValue<std::wstring > _type;
        AttributeValue<std::wstring > _status;
        AttributeValue<std::wstring > _parentReferenceFrame;
        AttributeValue<LunarSimulation::SpaceTimeCoordinateState > _state;
        AttributeValue<std::vector</* 3 */ double > > _acceleration;
        AttributeValue<std::vector</* 3 */ double > > _rotationalAcceleration;
        AttributeValue<std::vector</* 3 */ double > > _centerOfMass;
        AttributeValue<LunarSimulation::AttitudeQuaternion > _bodyWrtStructural;
    };
}
#endif
