/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPAYLOADMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAPAYLOADMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include <string>
#include "datatypes/AccelerationVectorEncoder.h"
#include "datatypes/AngularAccelerationVectorEncoder.h"
#include "datatypes/AttitudeQuaternionEncoder.h"
#include "datatypes/ForceVectorEncoder.h"
#include "datatypes/InertiaMatrixEncoder.h"
#include "datatypes/InertiaRateMatrixEncoder.h"
#include "datatypes/PositionVectorEncoder.h"
#include "datatypes/SpaceTimeCoordinateStateEncoder.h"
#include "datatypes/TorqueVectorEncoder.h"
#include "datatypes/VelocityVectorEncoder.h"

#include <LunarSimulation/HlaPayloadManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaPayloadInteractionManager;

    class HlaPayloadManagerImpl : public HlaPayloadManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaPayloadImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaPayloadImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaPayloadImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        Cache<std::wstring, HlaPayloadImplPtr> _getByNameCache; // guarded by _instancesLock
        ListenerSet<HlaPayloadManagerListenerPtr> _payloadManagerListeners;
        ListenerSet<HlaPayloadValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaPayloadListenerPtr> _defaultInstanceListeners;

    public:
        HlaPayloadManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaPayloadPtr> getAllHlaPayloads();
        std::vector<HlaPayloadPtr> getHlaPayloads();
        std::vector<HlaPayloadPtr> getLocalHlaPayloads();
        std::vector<HlaPayloadPtr> getRemoteHlaPayloads();
        HlaPayloadPtr getPayloadByName(std::wstring name);
        HlaPayloadPtr getPayloadByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaPayloadPtr getPayloadByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaPayloadPtr createLocalHlaPayload(
            std::wstring name
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPayloadPtr createLocalHlaPayload(const std::wstring& hlaInstanceName,
            std::wstring name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPayloadPtr deleteHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaPayloadManagerListener(HlaPayloadManagerListenerPtr managerListener);
        void removeHlaPayloadManagerListener(HlaPayloadManagerListenerPtr managerListener);

        void addHlaPayloadDefaultInstanceListener(HlaPayloadListenerPtr listener);
        void addHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListenerPtr valueListener);
        void removeHlaPayloadDefaultInstanceListener(HlaPayloadListenerPtr listener);
        void removeHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaPayloadImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaPayloadImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderDecoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderEncoder;
        LunarSimulation::VelocityVectorEncoder _velocityVectorEncoderDecoder;
        LunarSimulation::VelocityVectorEncoder _velocityVectorEncoderEncoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEDecoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEEncoder;
        LunarSimulation::ForceVectorEncoder _forceVectorEncoderDecoder;
        LunarSimulation::ForceVectorEncoder _forceVectorEncoderEncoder;
        LunarSimulation::TorqueVectorEncoder _torqueVectorEncoderDecoder;
        LunarSimulation::TorqueVectorEncoder _torqueVectorEncoderEncoder;
        LunarSimulation::InertiaMatrixEncoder _inertiaMatrixEncoderDecoder;
        LunarSimulation::InertiaMatrixEncoder _inertiaMatrixEncoderEncoder;
        LunarSimulation::InertiaRateMatrixEncoder _inertiaRateMatrixEncoderDecoder;
        LunarSimulation::InertiaRateMatrixEncoder _inertiaRateMatrixEncoderEncoder;
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
        HlaPayloadPtr createLocalInstance(const std::wstring& hlaInstanceName,
             const std::wstring& name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPayloadImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaPayloadImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaPayloadPtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaPayloadImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaPayloadImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

        HlaPayloadImplPtr findByName(std::wstring name); // guarded by _instancesLock
    };
}
#endif
