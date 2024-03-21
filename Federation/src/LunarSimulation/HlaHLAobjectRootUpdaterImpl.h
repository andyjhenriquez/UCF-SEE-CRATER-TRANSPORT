/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAHLAOBJECTROOTUPDATERIMPL_H
#define DEVELOPER_STUDIO_HLAHLAOBJECTROOTUPDATERIMPL_H

#include <mutex>
#include <memory>

#include <LunarSimulation/HlaHLAobjectRootUpdater.h>
#include "AttributeValue.h"
#include "HlaHLAobjectRootImpl.h"

namespace LunarSimulation {

    class HlaHLAobjectRootUpdaterImpl : public HlaHLAobjectRootUpdater , public std::enable_shared_from_this<HlaHLAobjectRootUpdaterImpl> {

    private:
        mutable std::mutex _attributesLock;


        HlaHLAobjectRootImplPtr _instance;
        bool _updateSent;

    public:
        explicit HlaHLAobjectRootUpdaterImpl(HlaHLAobjectRootImplPtr instance) :
            _instance(instance),
            _updateSent(false)
        {}


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
