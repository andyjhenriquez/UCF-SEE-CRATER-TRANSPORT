/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONMANAGERIMPL_H

#include <map>

#include <mutex>

#include <RtiDriver/ObjectClassHandle.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include "datatypes/ExecutionModeEncoder.h"

#include <LunarSimulation/HlaExecutionConfigurationManager.h>
#include <LunarSimulation/HlaPointers.h>
#include "AbstractObjectClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"
#include "Cache.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;
    class HlaExecutionConfigurationInteractionManager;

    class HlaExecutionConfigurationManagerImpl : public HlaExecutionConfigurationManager , public AbstractObjectClassManager {
        ObjectManager* _objectManager;
        HlaWorldImpl* _hlaWorld;
        bool _enabled;
        bool _optional;

        ObjectClassHandlePtr _objectClassHandle;

        mutable std::mutex _instancesLock;
        mutable std::mutex _localCreationInProgressLock;

        typedef std::map<ObjectInstanceHandlePtr, HlaExecutionConfigurationImplPtr, DualMapPtrComparator<ObjectInstanceHandlePtr> > InstanceMap;
        typedef std::map<std::wstring, HlaExecutionConfigurationImplPtr> HlaInstanceNameMap;
        typedef std::map<std::vector<char>, HlaExecutionConfigurationImplPtr> EncodedHlaInstanceHandleMap;
        InstanceMap _localInstances;  // guarded by _instancesLock, and _localCreationInProgressLock during local create
        InstanceMap _remoteInstances; // guarded by _instancesLock
        HlaInstanceNameMap _hlaInstanceNameMap; // guarded by _instancesLock
        EncodedHlaInstanceHandleMap _encodedHlaInstanceHandleMap; // guarded by _instancesLock

        ListenerSet<HlaExecutionConfigurationManagerListenerPtr> _executionConfigurationManagerListeners;
        ListenerSet<HlaExecutionConfigurationValueListenerPtr> _defaultInstanceValueListeners;
        ListenerSet<HlaExecutionConfigurationListenerPtr> _defaultInstanceListeners;

    public:
        HlaExecutionConfigurationManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld);
        bool isEnabled(const std::wstring& objectClassName);
        bool isOptional(const std::wstring& objectClassName);
        void connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp,HlaLogicalTimePtr logicalTime);

        std::vector<HlaExecutionConfigurationPtr> getAllHlaExecutionConfigurations();
        std::vector<HlaExecutionConfigurationPtr> getHlaExecutionConfigurations();
        std::vector<HlaExecutionConfigurationPtr> getLocalHlaExecutionConfigurations();
        std::vector<HlaExecutionConfigurationPtr> getRemoteHlaExecutionConfigurations();
        HlaExecutionConfigurationPtr getExecutionConfigurationByHlaInstanceName(const std::wstring& hlaInstanceName);
        HlaExecutionConfigurationPtr getExecutionConfigurationByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle);

        HlaExecutionConfigurationPtr createLocalHlaExecutionConfiguration(
        ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaExecutionConfigurationPtr createLocalHlaExecutionConfiguration(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,  HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaExecutionConfigurationPtr deleteHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime,bool checkLocal)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaExecutionConfigurationManagerListener(HlaExecutionConfigurationManagerListenerPtr managerListener);
        void removeHlaExecutionConfigurationManagerListener(HlaExecutionConfigurationManagerListenerPtr managerListener);

        void addHlaExecutionConfigurationDefaultInstanceListener(HlaExecutionConfigurationListenerPtr listener);
        void addHlaExecutionConfigurationDefaultInstanceValueListener(HlaExecutionConfigurationValueListenerPtr valueListener);
        void removeHlaExecutionConfigurationDefaultInstanceListener(HlaExecutionConfigurationListenerPtr listener);
        void removeHlaExecutionConfigurationDefaultInstanceValueListener(HlaExecutionConfigurationValueListenerPtr valueListener);

        void setEnabled(bool enabled);
        void setEnabledIfAvailableInFom();
        bool isEnabled();

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp);

        void updateAttributeValues(HlaExecutionConfigurationImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp);

        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes);

        void save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException);

        void restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException);

        /*
         * Share encoders and decoders for HlaExecutionConfigurationImpl
         */
        mutable std::mutex _decodersLock;
        mutable std::mutex _encodersLock;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringDecoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringEncoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEDecoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEEncoder;
        LunarSimulation::ExecutionModeEncoder _executionModeEncoderDecoder;
        LunarSimulation::ExecutionModeEncoder _executionModeEncoderEncoder;
        EncodingHelpers::HLAinteger64BE _hLAinteger64BEDecoder;
        EncodingHelpers::HLAinteger64BE _hLAinteger64BEEncoder;

    private:
        HlaExecutionConfigurationPtr createLocalInstance(const std::wstring& hlaInstanceName
        ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                      HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaExecutionConfigurationImplPtr createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId);
        void checkInitializedFired(HlaExecutionConfigurationImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDiscovered(HlaExecutionConfigurationPtr instance, HlaTimeStampPtr timeStamp);
        void fireInitialized(HlaExecutionConfigurationImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireDeleted(HlaExecutionConfigurationImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void clearAllInstances(bool doFireDeleted);

    };
}
#endif
