/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAMOONUPDATERIMPL_H
#define DEVELOPER_STUDIO_HLAMOONUPDATERIMPL_H

#include <mutex>
#include <memory>

#include <LunarSimulation/HlaMoonUpdater.h>
#include "AttributeValue.h"
#include "HlaMoonImpl.h"

namespace LunarSimulation {

    class HlaMoonUpdaterImpl : public HlaMoonUpdater , public std::enable_shared_from_this<HlaMoonUpdaterImpl> {

    private:
        mutable std::mutex _attributesLock;

        AttributeValue<std::wstring > _name;
        AttributeValue<std::wstring > _parentName;
        AttributeValue<LunarSimulation::SpaceTimeCoordinateState > _state;

        HlaMoonImplPtr _instance;
        bool _updateSent;

    public:
        explicit HlaMoonUpdaterImpl(HlaMoonImplPtr instance) :
            _instance(instance),
            _updateSent(false)
        {}

        void sendName();
        void setParentName(const std::wstring& parentName);
        void setState(const LunarSimulation::SpaceTimeCoordinateState& state);

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
