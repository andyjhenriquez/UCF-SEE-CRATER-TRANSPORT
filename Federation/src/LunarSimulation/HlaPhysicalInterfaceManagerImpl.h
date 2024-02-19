/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include "datatypes/AttitudeQuaternionEncoder.h"
#include "datatypes/PositionVectorEncoder.h"

#include <LunarSimulation/HlaPhysicalInterfaceManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaPhysicalInterfaceInteractionManager;

    class HlaPhysicalInterfaceManagerImpl : public HlaPhysicalInterfaceManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaPhysicalInterfaceImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaPhysicalInterfaceImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaPhysicalInterfaceImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        ListenerSet<HlaPhysicalInterfaceManagerListenerPtr> _physicalInterfaceManagerListeners;
        ListenerSet<HlaPhysicalInterfaceValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaPhysicalInterfaceListenerPtr> _defaultInstanceListeners;

    public:
        HlaPhysicalInterfaceManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaPhysicalInterfacePtr> getAllHlaPhysicalInterfaces();
        std::vector<HlaPhysicalInterfacePtr> getHlaPhysicalInterfaces();
        std::vector<HlaPhysicalInterfacePtr> getLocalHlaPhysicalInterfaces();
        std::vector<HlaPhysicalInterfacePtr> getRemoteHlaPhysicalInterfaces();
        HlaPhysicalInterfacePtr getPhysicalInterfaceByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaPhysicalInterfacePtr getPhysicalInterfaceByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaPhysicalInterfacePtr createLocalHlaPhysicalInterface(
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPhysicalInterfacePtr createLocalHlaPhysicalInterface(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPhysicalInterfacePtr deleteHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaPhysicalInterfaceManagerListener(HlaPhysicalInterfaceManagerListenerPtr managerListener);
        void removeHlaPhysicalInterfaceManagerListener(HlaPhysicalInterfaceManagerListenerPtr managerListener);

        void addHlaPhysicalInterfaceDefaultInstanceListener(HlaPhysicalInterfaceListenerPtr listener);
        void addHlaPhysicalInterfaceDefaultInstanceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener);
        void removeHlaPhysicalInterfaceDefaultInstanceListener(HlaPhysicalInterfaceListenerPtr listener);
        void removeHlaPhysicalInterfaceDefaultInstanceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaPhysicalInterfaceImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaPhysicalInterfaceImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringDecoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringEncoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderDecoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderEncoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderDecoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderEncoder;

    private:
        HlaPhysicalInterfacePtr createLocalInstance(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalInterfaceImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaPhysicalInterfaceImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaPhysicalInterfacePtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaPhysicalInterfaceImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaPhysicalInterfaceImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

    };
}
#endif
