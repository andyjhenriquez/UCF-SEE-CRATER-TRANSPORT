/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include "RtiInteractionManager.h"


#include "HlaWorldImpl.h"
#include "FederateManager.h"
#include "HlaLogicalTimeImpl.h"

using namespace LunarSimulation;
using namespace std;

RtiInteractionManager::RtiInteractionManager(HlaWorldImpl* hlaWorld, FederateManager* fed)
:_hlaWorld(hlaWorld), _federateManager(fed) {}

RtiInteractionManager::~RtiInteractionManager(void) {}

RtiInteractionManager::InteractionClassManagers RtiInteractionManager::copyInteractionClassManagers() {
    std::lock_guard<std::mutex> lock(_interactionClassManagersLock);
    return _interactionClassManagers; // Return a copy
}

void RtiInteractionManager::disconnect() {
    // Copy the InteractionClassManagers map so that we can thread safely iterate over it without letting the lock escape out into the interaction class manager's disconnected call
    InteractionClassManagers interactionClassManagersCopy = copyInteractionClassManagers();
    for (InteractionClassManagers::iterator iter = interactionClassManagersCopy.begin(); iter != interactionClassManagersCopy.end(); iter++) {
        AbstractInteractionClassManager* interactionClassManager = iter->second;
        InteractionClassHandlePtr interactionClassHandle = iter->first;
        interactionClassManager->disconnected(interactionClassHandle);
    }
}

void RtiInteractionManager::addManager(AbstractInteractionClassManager* icm, wstring interactionClassName) {
    _wannabeManagers.push_back(std::pair<wstring, AbstractInteractionClassManager*>(interactionClassName,icm));
}

void RtiInteractionManager::publish(const RtiDriver::InteractionClassHandle& ich)
THROW_SPEC (HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _federateManager->publishInteractionClass(ich);
}

void RtiInteractionManager::subscribe(const RtiDriver::InteractionClassHandle& ich)
THROW_SPEC (HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _federateManager->subscribeInteractionClass(ich);
}

void RtiInteractionManager::subscribe(const RtiDriver::InteractionClassHandle& ich, const RegionSetPtr& newRegions, const RegionSetPtr& oldRegions)
THROW_SPEC (HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _federateManager->subscribeInteractionClass(ich, newRegions, oldRegions);
}

void RtiInteractionManager::connected()
THROW_SPEC (HlaFomException, HlaInternalException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException)  {
    for (WannabeManagerList::iterator iter = _wannabeManagers.begin(); iter != _wannabeManagers.end(); ++iter) {
        AbstractInteractionClassManager * interactionClassManager = iter->second;
        wstring interactionClassName = iter->first;
        if (interactionClassManager->isEnabled(interactionClassName)) {
            try {
                InteractionClassHandlePtr handle = _federateManager->getInteractionClassHandle(interactionClassName);
                {
                    std::lock_guard<std::mutex> lock(_interactionClassManagersLock);
                    _interactionClassManagers[handle] = interactionClassManager;
                }
                interactionClassManager->connected(*handle, interactionClassName);
            } catch (HlaFomException&) {
                if (!interactionClassManager->isOptional(interactionClassName)) {
                    throw;
                }
            }
        }
    }
}

void RtiInteractionManager::sendInteraction(const RtiDriver::InteractionClassHandle& ich, const RtiDriver::NameValueMap& parameters, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException, HlaInternalException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _federateManager->sendInteraction(ich, parameters, timeStamp, logicalTime);
}

void RtiInteractionManager::sendInteraction(const RtiDriver::InteractionClassHandle& ich, const RtiDriver::NameValueMap& parameters, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime, const RtiDriver::Region& region)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException, HlaInternalException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _federateManager->sendInteraction(ich, parameters, timeStamp, logicalTime, region);
}

void RtiInteractionManager::receiveInteraction(const RtiDriver::InteractionClassHandle& ich, const RtiDriver::NameValueMap& parameters, const HlaFederateIdImplPtr producingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    AbstractInteractionClassManager* classManager;
    {
        std::lock_guard<std::mutex> lock(_interactionClassManagersLock);
        classManager = _interactionClassManagers[InteractionClassHandlePtr(ich.clone())];
    }
    if (classManager != NULL) {
        classManager->receiveInteraction(ich, parameters, producingFederate, timeStamp, logicalTime);
    } else {
        HlaExceptionPtr ex(new HlaInternalException(L"Failed to find interaction class manger: " + (const std::wstring &)ich));
        _hlaWorld->postException(ex);
    }
}
