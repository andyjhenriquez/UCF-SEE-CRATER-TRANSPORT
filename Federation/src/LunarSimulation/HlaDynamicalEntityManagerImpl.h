/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLADYNAMICALENTITYMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLADYNAMICALENTITYMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include "datatypes/AccelerationVectorEncoder.h"
#include "datatypes/AngularAccelerationVectorEncoder.h"
#include "datatypes/AttitudeQuaternionEncoder.h"
#include "datatypes/ForceVectorEncoder.h"
#include "datatypes/InertiaMatrixEncoder.h"
#include "datatypes/InertiaRateMatrixEncoder.h"
#include "datatypes/PositionVectorEncoder.h"
#include "datatypes/SpaceTimeCoordinateStateEncoder.h"
#include "datatypes/TorqueVectorEncoder.h"

#include <LunarSimulation/HlaDynamicalEntityManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaDynamicalEntityInteractionManager;

    class HlaDynamicalEntityManagerImpl : public HlaDynamicalEntityManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaDynamicalEntityImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaDynamicalEntityImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaDynamicalEntityImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        ListenerSet<HlaDynamicalEntityManagerListenerPtr> _dynamicalEntityManagerListeners;
        ListenerSet<HlaDynamicalEntityValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaDynamicalEntityListenerPtr> _defaultInstanceListeners;

    public:
        HlaDynamicalEntityManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaDynamicalEntityPtr> getAllHlaDynamicalEntitys();
        std::vector<HlaDynamicalEntityPtr> getHlaDynamicalEntitys();
        std::vector<HlaDynamicalEntityPtr> getLocalHlaDynamicalEntitys();
        std::vector<HlaDynamicalEntityPtr> getRemoteHlaDynamicalEntitys();
        HlaDynamicalEntityPtr getDynamicalEntityByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaDynamicalEntityPtr getDynamicalEntityByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaDynamicalEntityPtr createLocalHlaDynamicalEntity(
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaDynamicalEntityPtr createLocalHlaDynamicalEntity(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaDynamicalEntityPtr deleteHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaDynamicalEntityManagerListener(HlaDynamicalEntityManagerListenerPtr managerListener);
        void removeHlaDynamicalEntityManagerListener(HlaDynamicalEntityManagerListenerPtr managerListener);

        void addHlaDynamicalEntityDefaultInstanceListener(HlaDynamicalEntityListenerPtr listener);
        void addHlaDynamicalEntityDefaultInstanceValueListener(HlaDynamicalEntityValueListenerPtr valueListener);
        void removeHlaDynamicalEntityDefaultInstanceListener(HlaDynamicalEntityListenerPtr listener);
        void removeHlaDynamicalEntityDefaultInstanceValueListener(HlaDynamicalEntityValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaDynamicalEntityImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaDynamicalEntityImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        LunarSimulation::ForceVectorEncoder _forceVectorEncoderDecoder;
        LunarSimulation::ForceVectorEncoder _forceVectorEncoderEncoder;
        LunarSimulation::TorqueVectorEncoder _torqueVectorEncoderDecoder;
        LunarSimulation::TorqueVectorEncoder _torqueVectorEncoderEncoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEDecoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEEncoder;
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
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderDecoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderEncoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderDecoder;
        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoderEncoder;

    private:
        HlaDynamicalEntityPtr createLocalInstance(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaDynamicalEntityImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaDynamicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaDynamicalEntityPtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaDynamicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaDynamicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

    };
}
#endif
