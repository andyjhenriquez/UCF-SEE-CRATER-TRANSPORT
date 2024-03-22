/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAREFERENCEFRAMEMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAREFERENCEFRAMEMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include <string>
#include "datatypes/SpaceTimeCoordinateStateEncoder.h"

#include <LunarSimulation/HlaReferenceFrameManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaReferenceFrameInteractionManager;

    class HlaReferenceFrameManagerImpl : public HlaReferenceFrameManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaReferenceFrameImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaReferenceFrameImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaReferenceFrameImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        Cache<std::wstring, HlaReferenceFrameImplPtr> _getByNameCache; // guarded by _instancesLock
        Cache<std::wstring, HlaReferenceFrameImplPtr> _getByParentNameCache; // guarded by _instancesLock
        Cache<LunarSimulation::SpaceTimeCoordinateState, HlaReferenceFrameImplPtr> _getByStateCache; // guarded by _instancesLock
        ListenerSet<HlaReferenceFrameManagerListenerPtr> _referenceFrameManagerListeners;
        ListenerSet<HlaReferenceFrameValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaReferenceFrameListenerPtr> _defaultInstanceListeners;

    public:
        HlaReferenceFrameManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaReferenceFramePtr> getAllHlaReferenceFrames();
        std::vector<HlaReferenceFramePtr> getHlaReferenceFrames();
        std::vector<HlaReferenceFramePtr> getLocalHlaReferenceFrames();
        std::vector<HlaReferenceFramePtr> getRemoteHlaReferenceFrames();
        HlaReferenceFramePtr getReferenceFrameByName(std::wstring name);
        HlaReferenceFramePtr getReferenceFrameByParent_name(std::wstring parentName);
        HlaReferenceFramePtr getReferenceFrameByState(SpaceTimeCoordinateState state);
        HlaReferenceFramePtr getReferenceFrameByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaReferenceFramePtr getReferenceFrameByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaReferenceFramePtr createLocalHlaReferenceFrame(
            std::wstring name
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaReferenceFramePtr createLocalHlaReferenceFrame(const std::wstring& hlaInstanceName,
            std::wstring name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaReferenceFramePtr deleteHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaReferenceFrameManagerListener(HlaReferenceFrameManagerListenerPtr managerListener);
        void removeHlaReferenceFrameManagerListener(HlaReferenceFrameManagerListenerPtr managerListener);

        void addHlaReferenceFrameDefaultInstanceListener(HlaReferenceFrameListenerPtr listener);
        void addHlaReferenceFrameDefaultInstanceValueListener(HlaReferenceFrameValueListenerPtr valueListener);
        void removeHlaReferenceFrameDefaultInstanceListener(HlaReferenceFrameListenerPtr listener);
        void removeHlaReferenceFrameDefaultInstanceValueListener(HlaReferenceFrameValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaReferenceFrameImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaReferenceFrameImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringDecoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringEncoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderDecoder;
        LunarSimulation::SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderEncoder;

    private:
        HlaReferenceFramePtr createLocalInstance(const std::wstring& hlaInstanceName,
             const std::wstring& name
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaReferenceFrameImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaReferenceFrameImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaReferenceFramePtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaReferenceFrameImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaReferenceFrameImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

        HlaReferenceFrameImplPtr findByName(std::wstring name); // guarded by _instancesLock
        HlaReferenceFrameImplPtr findByParentName(std::wstring parentName); // guarded by _instancesLock
        HlaReferenceFrameImplPtr findByState(SpaceTimeCoordinateState state); // guarded by _instancesLock
    };
}
#endif
