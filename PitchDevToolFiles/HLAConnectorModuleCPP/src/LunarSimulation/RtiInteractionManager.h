/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_RTIINTERACTIONMANAGER_H
#define DEVELOPER_STUDIO_RTIINTERACTIONMANAGER_H

#include <string>
#include <map>
#include <vector>

#include <mutex>

#include <RtiDriver/InteractionClassHandle.h>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>
#include "AbstractInteractionClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"

namespace LunarSimulation {
    class FederateManager;
    class HlaWorldImpl;

    class RtiInteractionManager {
    private:
        HlaWorldImpl* _hlaWorld;
        FederateManager* _federateManager;

        typedef std::map<InteractionClassHandlePtr, AbstractInteractionClassManager*, DualMapPtrComparator<InteractionClassHandlePtr> > InteractionClassManagers;
        InteractionClassManagers _interactionClassManagers;
        mutable std::mutex _interactionClassManagersLock;

        typedef std::vector<std::pair<std::wstring,AbstractInteractionClassManager*> > WannabeManagerList;
        WannabeManagerList _wannabeManagers;

        InteractionClassManagers copyInteractionClassManagers();

    public:
        RtiInteractionManager(HlaWorldImpl* hlaWorld, FederateManager* fed);
        ~RtiInteractionManager(void);
        void disconnect();

        void addManager(AbstractInteractionClassManager* icm, std::wstring interactionClassName);
        void publish(const RtiDriver::InteractionClassHandle& ich)
            THROW_SPEC (HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void subscribe(const RtiDriver::InteractionClassHandle& ich)
            THROW_SPEC (HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void subscribe(const RtiDriver::InteractionClassHandle& ich, const RegionSetPtr& newRegions, const RegionSetPtr& oldRegions)
            THROW_SPEC (HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void connected() 
            THROW_SPEC (HlaFomException, HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendInteraction(const RtiDriver::InteractionClassHandle& ich, const RtiDriver::NameValueMap& parameters, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException, HlaInternalException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void sendInteraction(const RtiDriver::InteractionClassHandle& ich, const RtiDriver::NameValueMap& parameters, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime, const RtiDriver::Region& region)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException, HlaInternalException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void receiveInteraction(const RtiDriver::InteractionClassHandle& ich, const RtiDriver::NameValueMap& parameters, const HlaFederateIdImplPtr producingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
    };
}
#endif
