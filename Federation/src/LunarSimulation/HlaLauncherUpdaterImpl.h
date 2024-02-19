/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALAUNCHERUPDATERIMPL_H
#define DEVELOPER_STUDIO_HLALAUNCHERUPDATERIMPL_H

#include <mutex>
#include <memory>

#include <LunarSimulation/HlaLauncherUpdater.h>
#include "AttributeValue.h"
#include "HlaLauncherImpl.h"

namespace LunarSimulation {

    class HlaLauncherUpdaterImpl : public HlaLauncherUpdater , public std::enable_shared_from_this<HlaLauncherUpdaterImpl> {

    private:
        mutable std::mutex _attributesLock;

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

        HlaLauncherImplPtr _instance;
        bool _updateSent;

    public:
        explicit HlaLauncherUpdaterImpl(HlaLauncherImplPtr instance) :
            _instance(instance),
            _updateSent(false)
        {}

        void setPosition(const std::vector</* 3 */ double >& position);
        void setMass(const double& mass);
        void setEnergy(const double& energy);
        void setName(const std::wstring& name);
        void setType(const std::wstring& type);
        void setStatus(const std::wstring& status);
        void setParentReferenceFrame(const std::wstring& parentReferenceFrame);
        void setState(const LunarSimulation::SpaceTimeCoordinateState& state);
        void setAcceleration(const std::vector</* 3 */ double >& acceleration);
        void setRotationalAcceleration(const std::vector</* 3 */ double >& rotationalAcceleration);
        void setCenterOfMass(const std::vector</* 3 */ double >& centerOfMass);
        void setBodyWrtStructural(const LunarSimulation::AttitudeQuaternion& bodyWrtStructural);

        void sendUpdate()
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendUpdate(HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendUpdate(HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendUpdate(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

    };
}
#endif
