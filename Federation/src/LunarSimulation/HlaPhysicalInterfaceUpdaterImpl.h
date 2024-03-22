/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEUPDATERIMPL_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEUPDATERIMPL_H

#include <mutex>
#include <memory>

#include <LunarSimulation/HlaPhysicalInterfaceUpdater.h>
#include "AttributeValue.h"
#include "HlaPhysicalInterfaceImpl.h"

namespace LunarSimulation {

    class HlaPhysicalInterfaceUpdaterImpl : public HlaPhysicalInterfaceUpdater , public std::enable_shared_from_this<HlaPhysicalInterfaceUpdaterImpl> {

    private:
        mutable std::mutex _attributesLock;

        AttributeValue<std::wstring > _name;
        AttributeValue<std::wstring > _parentName;
        AttributeValue<std::vector</* 3 */ double > > _position;
        AttributeValue<LunarSimulation::AttitudeQuaternion > _attitude;

        HlaPhysicalInterfaceImplPtr _instance;
        bool _updateSent;

    public:
        explicit HlaPhysicalInterfaceUpdaterImpl(HlaPhysicalInterfaceImplPtr instance) :
            _instance(instance),
            _updateSent(false)
        {}

        void sendName();
        void setParentName(const std::wstring& parentName);
        void setPosition(const std::vector</* 3 */ double >& position);
        void setAttitude(const LunarSimulation::AttitudeQuaternion& attitude);

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
