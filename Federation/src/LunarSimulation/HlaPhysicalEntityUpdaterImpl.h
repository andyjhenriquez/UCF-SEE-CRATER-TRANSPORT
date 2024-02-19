/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALENTITYUPDATERIMPL_H
#define DEVELOPER_STUDIO_HLAPHYSICALENTITYUPDATERIMPL_H

#include <mutex>
#include <memory>

#include <LunarSimulation/HlaPhysicalEntityUpdater.h>
#include "AttributeValue.h"
#include "HlaPhysicalEntityImpl.h"

namespace LunarSimulation {

    class HlaPhysicalEntityUpdaterImpl : public HlaPhysicalEntityUpdater , public std::enable_shared_from_this<HlaPhysicalEntityUpdaterImpl> {

    private:
        mutable std::mutex _attributesLock;

        AttributeValue<std::wstring > _name;
        AttributeValue<std::wstring > _type;
        AttributeValue<std::wstring > _status;
        AttributeValue<std::wstring > _parentReferenceFrame;
        AttributeValue<LunarSimulation::SpaceTimeCoordinateState > _state;
        AttributeValue<std::vector</* 3 */ double > > _acceleration;
        AttributeValue<std::vector</* 3 */ double > > _rotationalAcceleration;
        AttributeValue<std::vector</* 3 */ double > > _centerOfMass;
        AttributeValue<LunarSimulation::AttitudeQuaternion > _bodyWrtStructural;

        HlaPhysicalEntityImplPtr _instance;
        bool _updateSent;

    public:
        explicit HlaPhysicalEntityUpdaterImpl(HlaPhysicalEntityImplPtr instance) :
            _instance(instance),
            _updateSent(false)
        {}

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
