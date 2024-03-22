/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAHLAOBJECTROOTMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAHLAOBJECTROOTMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>

#include <LunarSimulation/HlaHLAobjectRootManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaHLAobjectRootInteractionManager;

    class HlaHLAobjectRootManagerImpl : public HlaHLAobjectRootManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaHLAobjectRootImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaHLAobjectRootImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaHLAobjectRootImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        ListenerSet<HlaHLAobjectRootManagerListenerPtr> _hLAobjectRootManagerListeners;
        ListenerSet<HlaHLAobjectRootValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaHLAobjectRootListenerPtr> _defaultInstanceListeners;

    public:
        HlaHLAobjectRootManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaHLAobjectRootPtr> getAllHlaHLAobjectRoots();
        std::vector<HlaHLAobjectRootPtr> getHlaHLAobjectRoots();
        std::vector<HlaHLAobjectRootPtr> getLocalHlaHLAobjectRoots();
        std::vector<HlaHLAobjectRootPtr> getRemoteHlaHLAobjectRoots();
        HlaHLAobjectRootPtr getHLAobjectRootByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaHLAobjectRootPtr getHLAobjectRootByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaHLAobjectRootPtr createLocalHlaHLAobjectRoot(
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaHLAobjectRootPtr createLocalHlaHLAobjectRoot(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaHLAobjectRootPtr deleteHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaHLAobjectRootManagerListener(HlaHLAobjectRootManagerListenerPtr managerListener);
        void removeHlaHLAobjectRootManagerListener(HlaHLAobjectRootManagerListenerPtr managerListener);

        void addHlaHLAobjectRootDefaultInstanceListener(HlaHLAobjectRootListenerPtr listener);
        void addHlaHLAobjectRootDefaultInstanceValueListener(HlaHLAobjectRootValueListenerPtr valueListener);
        void removeHlaHLAobjectRootDefaultInstanceListener(HlaHLAobjectRootListenerPtr listener);
        void removeHlaHLAobjectRootDefaultInstanceValueListener(HlaHLAobjectRootValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaHLAobjectRootImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaHLAobjectRootImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;

    private:
        HlaHLAobjectRootPtr createLocalInstance(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaHLAobjectRootImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaHLAobjectRootImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaHLAobjectRootPtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaHLAobjectRootImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaHLAobjectRootImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

    };
}
#endif
