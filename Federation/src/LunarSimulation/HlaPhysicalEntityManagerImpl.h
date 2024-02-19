/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALENTITYMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAPHYSICALENTITYMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include "datatypes/AccelerationVectorEncoder.h"
#include "datatypes/AngularAccelerationVectorEncoder.h"
#include "datatypes/AttitudeQuaternionEncoder.h"
#include "datatypes/PositionVectorEncoder.h"
#include "datatypes/SpaceTimeCoordinateStateEncoder.h"

#include <LunarSimulation/HlaPhysicalEntityManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaPhysicalEntityInteractionManager;

    class HlaPhysicalEntityManagerImpl : public HlaPhysicalEntityManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaPhysicalEntityImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaPhysicalEntityImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaPhysicalEntityImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        ListenerSet<HlaPhysicalEntityManagerListenerPtr> _physicalEntityManagerListeners;
        ListenerSet<HlaPhysicalEntityValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaPhysicalEntityListenerPtr> _defaultInstanceListeners;

    public:
        HlaPhysicalEntityManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaPhysicalEntityPtr> getAllHlaPhysicalEntitys();
        std::vector<HlaPhysicalEntityPtr> getHlaPhysicalEntitys();
        std::vector<HlaPhysicalEntityPtr> getLocalHlaPhysicalEntitys();
        std::vector<HlaPhysicalEntityPtr> getRemoteHlaPhysicalEntitys();
        HlaPhysicalEntityPtr getPhysicalEntityByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaPhysicalEntityPtr getPhysicalEntityByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaPhysicalEntityPtr createLocalHlaPhysicalEntity(
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPhysicalEntityPtr createLocalHlaPhysicalEntity(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaPhysicalEntityPtr deleteHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaPhysicalEntityManagerListener(HlaPhysicalEntityManagerListenerPtr managerListener);
        void removeHlaPhysicalEntityManagerListener(HlaPhysicalEntityManagerListenerPtr managerListener);

        void addHlaPhysicalEntityDefaultInstanceListener(HlaPhysicalEntityListenerPtr listener);
        void addHlaPhysicalEntityDefaultInstanceValueListener(HlaPhysicalEntityValueListenerPtr valueListener);
        void removeHlaPhysicalEntityDefaultInstanceListener(HlaPhysicalEntityListenerPtr listener);
        void removeHlaPhysicalEntityDefaultInstanceValueListener(HlaPhysicalEntityValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaPhysicalEntityImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaPhysicalEntityImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringDecoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringEncoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderDecoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderEncoder;
        LunarSimulation::AccelerationVectorEncoder _accelerationVectorEncoderDecoder;
        LunarSimulation::AccelerationVectorEncoder _accelerationVectorEncoderEncoder;
        LunarSimulation::AngularAccelerationVectorEncoder _angularAccelerationVectorEncoderDecoder;
        LunarSimulation::AngularAccelerationVectorEncoder _angularAccelerationVectorEncoderEncoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderDecoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderEncoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderDecoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderEncoder;

    private:
        HlaPhysicalEntityPtr createLocalInstance(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaPhysicalEntityImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaPhysicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaPhysicalEntityPtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaPhysicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaPhysicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

    };
}
#endif
