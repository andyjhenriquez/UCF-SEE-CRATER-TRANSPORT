/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLADYNAMICALENTITYUPDATERIMPL_H
#define DEVELOPER_STUDIO_HLADYNAMICALENTITYUPDATERIMPL_H

#include <mutex>
#include <memory>

#include <LunarSimulation/HlaDynamicalEntityUpdater.h>
#include "AttributeValue.h"
#include "HlaDynamicalEntityImpl.h"

namespace LunarSimulation {

    class HlaDynamicalEntityUpdaterImpl : public HlaDynamicalEntityUpdater , public std::enable_shared_from_this<HlaDynamicalEntityUpdaterImpl> {

    private:
        mutable std::mutex _attributesLock;

        AttributeValue<std::vector</* 3 */ double > > _force;
        AttributeValue<std::vector</* 3 */ double > > _torque;
        AttributeValue<double > _mass;
        AttributeValue<double > _massRate;
        AttributeValue<std::vector</* 9 */ double > > _inertia;
        AttributeValue<std::vector</* 9 */ double > > _inertiaRate;
        AttributeValue<std::wstring > _name;
        AttributeValue<std::wstring > _type;
        AttributeValue<std::wstring > _status;
        AttributeValue<std::wstring > _parentReferenceFrame;
        AttributeValue<LunarSimulation::SpaceTimeCoordinateState > _state;
        AttributeValue<std::vector</* 3 */ double > > _acceleration;
        AttributeValue<std::vector</* 3 */ double > > _rotationalAcceleration;
        AttributeValue<std::vector</* 3 */ double > > _centerOfMass;
        AttributeValue<LunarSimulation::AttitudeQuaternion > _bodyWrtStructural;

        HlaDynamicalEntityImplPtr _instance;
        bool _updateSent;

    public:
        explicit HlaDynamicalEntityUpdaterImpl(HlaDynamicalEntityImplPtr instance) :
            _instance(instance),
            _updateSent(false)
        {}

        void setForce(const std::vector</* 3 */ double >& force);
        void setTorque(const std::vector</* 3 */ double >& torque);
        void setMass(const double& mass);
        void setMassRate(const double& massRate);
        void setInertia(const std::vector</* 9 */ double >& inertia);
        void setInertiaRate(const std::vector</* 9 */ double >& inertiaRate);
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
