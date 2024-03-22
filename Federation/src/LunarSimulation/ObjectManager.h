/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_OBJECTMANAGER_H
#define DEVELOPER_STUDIO_OBJECTMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>
#include <set>
#include <vector>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/ObjectInstanceHandle.h>
#include <RtiDriver/Region.h>

#include <LunarSimulation/HlaException.h>
#include "ImplPointers.h"
#include "AbstractObjectClassManager.h"
#include "DualMap.h"

namespace LunarSimulation {
    class FederateManager;
    class HlaWorldImpl;

    class ObjectManager {

        typedef std::vector<std::pair<std::wstring, AbstractObjectClassManager*> > WannabeManagerList;
        WannabeManagerList _wannabeManagers;

        typedef std::map<ObjectClassHandlePtr, AbstractObjectClassManager*, DualMapPtrComparator<ObjectClassHandlePtr> > ObjectClassManagers;
        ObjectClassManagers _objectClassManagers;
        mutable std::mutex _objectClassManagersLock;

        FederateManager* _federateManager;
        HlaWorldImpl* _hlaWorld;
        mutable std::mutex _registerNameInProgressLock;

        AbstractObjectClassManager* getObjectClassManager(const ObjectClassHandlePtr& objectClassHandle);
        ObjectClassManagers copyObjectClassManagers();

    public:
        ObjectManager(HlaWorldImpl* hlaWorld, FederateManager* federateManager);

        void addManager(AbstractObjectClassManager* manager, const std::wstring& className);

        void subscribe(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::set<std::wstring>& attributeNames)
            THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void subscribe(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::set<std::wstring>& attributeNames, const RegionSetPtr& newRegion, const RegionSetPtr& oldRegion)
            THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void publish(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::set<std::wstring>& attributeNames)
            THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        bool registerObjectInstanceName(const std::wstring& instanceName)
            THROW_SPEC (HlaNotConnectedException, HlaIllegalInstanceNameException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        ObjectInstanceHandlePtr createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& instanceName)
            THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        ObjectInstanceHandlePtr createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& instanceName, const std::set<std::wstring>& attributeNames, const RtiDriver::Region& region)
            THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes,
                                   HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException,
                        HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);

        void updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes,
                                   HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime, const std::set<std::wstring>& attributeNames, const RtiDriver::Region& newRegion, const RtiDriver::Region& oldRegion)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException,
                        HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);

        void deleteObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);


        void requestAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& hlaAttributeNames,
            HlaTimeStampPtr currentTime)
            THROW_SPEC (HlaInternalException, HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void save() THROW_SPEC(HlaSaveFederateException);

        void restore() THROW_SPEC(HlaRestoreFederateException);

        //Callbacks
        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
            const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
            const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);

        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
            HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
            const std::set<std::wstring>& attributes, HlaTimeStampPtr hlaTimeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void connected() THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnect();
    };
}
#endif
