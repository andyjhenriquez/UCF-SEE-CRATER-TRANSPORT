/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAMOONMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAMOONMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include <string>
#include "datatypes/SpaceTimeCoordinateStateEncoder.h"

#include <LunarSimulation/HlaMoonManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaMoonInteractionManager;

    class HlaMoonManagerImpl : public HlaMoonManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaMoonImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaMoonImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaMoonImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        Cache<std::wstring, HlaMoonImplPtr> _getByNameCache; // guarded by _instancesLock
        Cache<std::wstring, HlaMoonImplPtr> _getByParentNameCache; // guarded by _instancesLock
        Cache<LunarSimulation::SpaceTimeCoordinateState, HlaMoonImplPtr> _getByStateCache; // guarded by _instancesLock
        ListenerSet<HlaMoonManagerListenerPtr> _moonManagerListeners;
        ListenerSet<HlaMoonValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaMoonListenerPtr> _defaultInstanceListeners;

    public:
        HlaMoonManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaMoonPtr> getAllHlaMoons();
        std::vector<HlaMoonPtr> getHlaMoons();
        std::vector<HlaMoonPtr> getLocalHlaMoons();
        std::vector<HlaMoonPtr> getRemoteHlaMoons();
        HlaMoonPtr getMoonByName(std::wstring name);
        HlaMoonPtr getMoonByParent_name(std::wstring parentName);
        HlaMoonPtr getMoonByState(SpaceTimeCoordinateState state);
        HlaMoonPtr getMoonByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaMoonPtr getMoonByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaMoonPtr createLocalHlaMoon(
            std::wstring name
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaMoonPtr createLocalHlaMoon(const std::wstring& hlaInstanceName,
            std::wstring name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaMoonPtr deleteHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaMoonManagerListener(HlaMoonManagerListenerPtr managerListener);
        void removeHlaMoonManagerListener(HlaMoonManagerListenerPtr managerListener);

        void addHlaMoonDefaultInstanceListener(HlaMoonListenerPtr listener);
        void addHlaMoonDefaultInstanceValueListener(HlaMoonValueListenerPtr valueListener);
        void removeHlaMoonDefaultInstanceListener(HlaMoonListenerPtr listener);
        void removeHlaMoonDefaultInstanceValueListener(HlaMoonValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaMoonImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaMoonImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringDecoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringEncoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderDecoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderEncoder;

    private:
        HlaMoonPtr createLocalInstance(const std::wstring& hlaInstanceName,
             const std::wstring& name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaMoonImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaMoonImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaMoonPtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaMoonImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaMoonImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

        HlaMoonImplPtr findByName(std::wstring name); // guarded by _instancesLock
        HlaMoonImplPtr findByParentName(std::wstring parentName); // guarded by _instancesLock
        HlaMoonImplPtr findByState(SpaceTimeCoordinateState state); // guarded by _instancesLock
    };
}
#endif
