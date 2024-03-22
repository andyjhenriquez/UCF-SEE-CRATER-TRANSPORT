/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALAUNCHERMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLALAUNCHERMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include <string>
#include "datatypes/AccelerationVectorEncoder.h"
#include "datatypes/AngularAccelerationVectorEncoder.h"
#include "datatypes/AttitudeQuaternionEncoder.h"
#include "datatypes/PositionVectorEncoder.h"
#include "datatypes/SpaceTimeCoordinateStateEncoder.h"

#include <LunarSimulation/HlaLauncherManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaLauncherInteractionManager;

    class HlaLauncherManagerImpl : public HlaLauncherManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaLauncherImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaLauncherImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaLauncherImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        Cache<std::wstring, HlaLauncherImplPtr> _getByNameCache; // guarded by _instancesLock
        ListenerSet<HlaLauncherManagerListenerPtr> _launcherManagerListeners;
        ListenerSet<HlaLauncherValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaLauncherListenerPtr> _defaultInstanceListeners;

    public:
        HlaLauncherManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaLauncherPtr> getAllHlaLaunchers();
        std::vector<HlaLauncherPtr> getHlaLaunchers();
        std::vector<HlaLauncherPtr> getLocalHlaLaunchers();
        std::vector<HlaLauncherPtr> getRemoteHlaLaunchers();
        HlaLauncherPtr getLauncherByName(std::wstring name);
        HlaLauncherPtr getLauncherByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaLauncherPtr getLauncherByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaLauncherPtr createLocalHlaLauncher(
            std::wstring name
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaLauncherPtr createLocalHlaLauncher(const std::wstring& hlaInstanceName,
            std::wstring name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaLauncherPtr deleteHlaLauncher(HlaLauncherPtr launcher, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaLauncherManagerListener(HlaLauncherManagerListenerPtr managerListener);
        void removeHlaLauncherManagerListener(HlaLauncherManagerListenerPtr managerListener);

        void addHlaLauncherDefaultInstanceListener(HlaLauncherListenerPtr listener);
        void addHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListenerPtr valueListener);
        void removeHlaLauncherDefaultInstanceListener(HlaLauncherListenerPtr listener);
        void removeHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaLauncherImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaLauncherImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderDecoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderEncoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEDecoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEEncoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringDecoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringEncoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderDecoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderEncoder;
        LunarSimulation::AccelerationVectorEncoder _accelerationVectorEncoderDecoder;
        LunarSimulation::AccelerationVectorEncoder _accelerationVectorEncoderEncoder;
        LunarSimulation::AngularAccelerationVectorEncoder _angularAccelerationVectorEncoderDecoder;
        LunarSimulation::AngularAccelerationVectorEncoder _angularAccelerationVectorEncoderEncoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderDecoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderEncoder;

    private:
        HlaLauncherPtr createLocalInstance(const std::wstring& hlaInstanceName,
             const std::wstring& name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaLauncherImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaLauncherImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaLauncherPtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaLauncherImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaLauncherImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

        HlaLauncherImplPtr findByName(std::wstring name); // guarded by _instancesLock
    };
}
#endif
