/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_FEDERATEMANAGER_H
#define DEVELOPER_STUDIO_FEDERATEMANAGER_H

#include <mutex>

#include <vector>

#include <RtiDriver/RtiDriver.h>
#include <RtiDriver/RtiAmbassador.h>
#include <RtiDriver/FederateAmbassador.h>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaSettings.h>
#include <LunarSimulation/HlaLibSettings.h>
#include "ConditionVariable.h"
#include "ImplPointers.h"


namespace LunarSimulation {
    class ObjectManager;
    class RtiInteractionManager;
    class HlaWorldImpl;
    class SaveRestManager;
    class SyncPointManager;

    class FederateManagerDdmListener {
    public:
        virtual ~FederateManagerDdmListener() {}
        virtual bool connected(const RtiDriver::HlaVersion& hlaVersion)
            THROW_SPEC (HlaNormalizerException, HlaRtiException,
                        HlaNotConnectedException, HlaInternalException,
                        HlaSaveInProgressException, HlaRestoreInProgressException) = 0;
        virtual void disconnected() = 0;
    };

    class FederateManager : public RtiDriver::FederateAmbassador , private LunarSimulation::noncopyable {
    private:
        ObjectManager* _objectManager;
        RtiInteractionManager* _interactionManager;
        SaveRestManager* _saveRestManager;
        SyncPointManager* _syncPointManager;
        HlaWorldImpl* _hlaWorld;
        HlaTimeStampFactoryPtr _timeStampFactory;
        FederateManagerDdmListener* _ddmListener;


        bool _synchPointRegisterSucceeded;
        mutable std::mutex _synchPointRegistrationSemaphore;
        ConditionVariable _synchPointRegistrationCondition;
        bool _synchPointRegistrationComplete;

        bool _nameReservationSucceeded;
        bool _nameReservationCompleted;
        mutable std::mutex _nameReservationSemaphore;
        ConditionVariable _nameReservationCondition;

        mutable std::mutex _restoreRequestSemaphore;
        ConditionVariable _restoreRequestCondition;
        bool _restoreRequestSucceeded;
        bool _restoreRequestCompleted;
        bool _expectingGrantAfterRestore;
        volatile bool _handleDisconnectDetected;

        std::unique_ptr<RtiDriver::FederateHandle> _federateHandle;
        HlaFederateIdImplPtr _federateId;
        std::unique_ptr<RtiDriver::RtiAmbassador> _rtiAmbassador;
        std::wstring _federationName;

        mutable std::mutex _timeConstrainedSemaphore;
        ConditionVariable _timeConstrainedEnabled;
        mutable std::mutex _timeRegulationSemaphore;
        ConditionVariable _timeRegulationEnabled;
        mutable std::mutex _timeAdvanceSemaphore;
        ConditionVariable _timeAdvanceGranted;
        long long _currentTime;
        bool _timeValid;
        bool _timeConstrained;
        bool _timeRegulating;
        bool _granted;

        HlaSettings::HlaVersion getHlaVersion();
        RtiDriver::Profile getRtiDriverProfile(const std::wstring& str);
        std::wstring getRtiDriverProfileStr(const RtiDriver::Profile& profile, const std::wstring& localSettingsDesignator,
                                            const std::wstring& crcHost, const std::wstring& crcPort);
        RtiDriver::ResignAction getResignAction(int resignAction);

        void disconnectDetected();

        bool sendWithLogicalTime(HlaLogicalTimePtr logicalTime);
        long long encodeSendLogicalTime(HlaLogicalTimePtr logicalTime);

        template <typename T> void disconnectRtiAndThrow(const T& exception);
        template <typename T> void disconnectAndThrow(bool destroyFederationOnDisconnect, const T& exception);
        template <typename T> void throwException(bool destroyFederationOnDisconnect, const T& exception, bool onJoin);
    public:
        explicit FederateManager(HlaWorldImpl* hlaWorld);
        void init(RtiInteractionManager* interactionManager, ObjectManager* objectManager, HlaTimeStampFactoryPtr timeStampFactory);
        
        ~FederateManager();

        void setSynchronizationPointManager(SyncPointManager* syncPointManager) {
            _syncPointManager = syncPointManager;
        }

        void setSaveRestManager(SaveRestManager* saveRestManager);
        void setDdmListener(FederateManagerDdmListener *listener) {
            _ddmListener = listener;
        }

        HlaLogicalTimePtr connect(HlaSettingsPtr settings)
            THROW_SPEC (HlaConnectException, HlaInvalidLicenseException, HlaRtiException, HlaFomException,
                        HlaInternalException, HlaNotConnectedException, HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException, HlaNormalizerException);

        void disconnect(bool destroyFederationOnDisconnect)
            THROW_SPEC (HlaFederateOwnsAttributeException, HlaRtiException, HlaInternalException);
        std::vector<char> getEncodedHlaFederateHandle();
        HlaFederateIdImplPtr getFederateIdImpl();
        void disconnected();

        HlaLogicalTimePtr enableTimeManagement(bool regulating, bool constrained, bool destroyFederationOnDisconnect, bool onJoin)
        THROW_SPEC (HlaInternalException, HlaInvalidLogicalTimeException,
                    HlaRtiException, HlaNotConnectedException);

        HlaLogicalTimePtr timeAdvanceRequest(HlaLogicalTimePtr logicalTime)
        THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,
                    HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException,
                    HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaLogicalTimePtr nextMessageRequestAvailable(HlaLogicalTimePtr logicalTime)
        THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,
                    HlaInvalidLogicalTimeException, HlaInTimeAdvancingStateException,
                    HlaSaveInProgressException, HlaRestoreInProgressException);

        void modifyLookahead(long long lookahead)
        THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,
                    HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);


         // Callback from RTI

        void timeRegulationEnabled(const RtiDriver::LogicalTime theTime);
        void timeConstrainedEnabled(const RtiDriver::LogicalTime theTime);
        void timeAdvanceGrant(const RtiDriver::LogicalTime theTime);
        
        void objectInstanceNameReservationSucceeded(const std::wstring& instanceName);
        void objectInstanceNameReservationFailed(const std::wstring& instanceName);

        void connectionLost(const std::wstring& faultDescription);

        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName);
        void discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName,
            const RtiDriver::FederateHandle& producingFederate);

        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributeHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag);
        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributeHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::FederateHandle& producingFederate);
        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributeHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType);
        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributeHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType, const RtiDriver::FederateHandle& producingFederate);
        void reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributeHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const HlaLogicalTimeImplPtr logicalTime, const HlaFederateIdImplPtr federateId);

        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag,
            const RtiDriver::FederateHandle& producingFederate);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType);
        void removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType,
            const RtiDriver::FederateHandle& producingFederate);
        
        void receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameterHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag);
        void receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameterHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::FederateHandle& producingFederate);
        void receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameterHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType);
        void receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameterHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const RtiDriver::LogicalTime theTime, const RtiDriver::OrderType orderType, const RtiDriver::FederateHandle& producingFederate);
        void receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameterHandleValueMap,
            const RtiDriver::VariableLengthData& userSuppliedTag, const HlaLogicalTimeImplPtr logicalTime, const HlaFederateIdImplPtr producingFederate);

        void provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
            const RtiDriver::NameSet& attributeHandleSet,
            const RtiDriver::VariableLengthData& userSuppliedTag);

        void requestAttributeOwnershipRelease(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& attributeHandleSet,
            const RtiDriver::VariableLengthData& userSuppliedTag);

        void attributeOwnershipAcquisitionNotification(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& attributeHandleSet,
             const RtiDriver::VariableLengthData& userSuppliedTag);

        void requestAttributeOwnershipAssumption(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& offeredAttributes,
         const RtiDriver::VariableLengthData& userSuppliedTag);

        void attributeOwnershipUnavailable(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& theAttributes);
        void confirmAttributeOwnershipAcquisitionCancellation(const RtiDriver::ObjectInstanceHandle& theObject, const RtiDriver::NameSet& attributeHandleSet);

        void informAttributeOwnership(const RtiDriver::ObjectInstanceHandle& theObject, const std::wstring theAttribute,  const RtiDriver::FederateHandle& federateHandle);
        void attributeIsNotOwned(const RtiDriver::ObjectInstanceHandle& theObject, const std::wstring theAttribute);
        void attributeIsOwnedByRTI(const RtiDriver::ObjectInstanceHandle& theObject, const std::wstring theAttribute);

        /*
         * Object RTI calls
         */

        ObjectClassHandlePtr getObjectClassHandle(const std::wstring& objectClassName)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException);

        void publishObjectClassAttributes(const RtiDriver::ObjectClassHandle& objectClassHandle, const RtiDriver::NameSet& attributeNames)
            THROW_SPEC (HlaRtiException, HlaFomException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void subscribeObjectClassAttributes(const RtiDriver::ObjectClassHandle& objectClassHandle, const RtiDriver::NameSet& attributeNames)
            THROW_SPEC (HlaRtiException, HlaFomException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void subscribeObjectClassAttributes(const RtiDriver::ObjectClassHandle& objectClassHandle, const RtiDriver::NameSet& attributeNames, const RegionSetPtr& newRegion, const RegionSetPtr& oldRegion)
            THROW_SPEC (HlaRtiException, HlaFomException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        bool registerObjectInstanceName(const std::wstring& instanceName)
            THROW_SPEC (HlaIllegalInstanceNameException, HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        ObjectInstanceHandlePtr createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& instanceName)
            THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);

        ObjectInstanceHandlePtr createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& instanceName, const RtiDriver::NameSet& attributeNames, const RtiDriver::Region& initialRegion)
            THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes,
            HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaAttributeNotOwnedException,
                        HlaObjectInstanceIsRemovedException,HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);

        void updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes,
            HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime,
            const RtiDriver::NameSet& attributeNames, const RtiDriver::Region& newRegion, const RtiDriver::Region& oldRegion)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaAttributeNotOwnedException,
                        HlaObjectInstanceIsRemovedException,HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);

        void deleteObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void requestAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, 
            const RtiDriver::NameSet& attributes,
            HlaTimeStampPtr hlaTimeStamp)
            THROW_SPEC (HlaRtiException, HlaInternalException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        /*
         * Interaction RTI calls
         */

        InteractionClassHandlePtr getInteractionClassHandle(const std::wstring& interactionClassName)
            THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaRtiException);

        void publishInteractionClass(const RtiDriver::InteractionClassHandle& interactionClassHandle)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void subscribeInteractionClass(const RtiDriver::InteractionClassHandle& interactionClassHandle)
            THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void subscribeInteractionClass(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RegionSetPtr& newRegion, const RegionSetPtr& oldRegion)
            THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle,
            const RtiDriver::NameValueMap& parameters,
            HlaTimeStampPtr timeStamp,
            HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException,
                        HlaInternalException, HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle,
            const RtiDriver::NameValueMap& parameters,
            HlaTimeStampPtr timeStamp,
            HlaLogicalTimePtr logicalTime,
            const RtiDriver::Region& region)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaFomException,
                        HlaInternalException, HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);

        /*
         * Synchronization points
         */

        bool registerFederationSynchronizationPoint(const std::wstring& synchPointLabel, const std::set<std::vector<char> >& encodedFederateHandles,
            HlaTimeStampPtr timeStamp)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        bool synchronizationPointAchieved(const std::wstring& synchPointLabel)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void synchronizationPointRegistrationSucceeded(const std::wstring& synchPointName);
        void synchronizationPointRegistrationFailed(const std::wstring& synchPointName, RtiDriver::SynchronizationPointFailureReason failureReason);
        void announceSynchronizationPoint(const std::wstring& synchPointName, const RtiDriver::VariableLengthData& userSuppliedTag);
        void federationSynchronized(const std::wstring& synchPointName);

        /*
         * Save
         */

        void requestFederationSave(const std::wstring &label, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void federateSaveBegun() THROW_SPEC (HlaRtiException, HlaNotConnectedException,  HlaRestoreInProgressException);
        void federateSaveComplete() THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaRestoreInProgressException);
        void federateSaveNotComplete() THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaRestoreInProgressException);

        //Callbacks
        void initiateFederateSave(const std::wstring& label);
        void initiateFederateSave(const std::wstring& label, const RtiDriver::LogicalTime theTime);
        void federationSaved();
        void federationNotSaved(RtiDriver::SaveFailureReason saveFailureReason);

        /*
         * Restore
         */

        bool requestFederationRestore(const std::wstring &label) THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void federateRestoreComplete() THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException);
        void federateRestoreNotComplete() THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException);

        //Callbacks
        void requestFederationRestoreSucceeded(const std::wstring& label);
        void requestFederationRestoreFailed(const std::wstring& label);
        void federationRestoreBegun();
        void initiateFederateRestore(const std::wstring& label, const RtiDriver::FederateHandle& federateHandle, const std::wstring& federateName);
        void federationRestored();
        void federationNotRestored(RtiDriver::RestoreFailureReason restoreFailureReason);

        /*
         * DDM
         */

        // area is a map from Dimension names to Ranges, all within the same hla13routingSpace
        RegionPtr createRegion(const RtiDriver::NameRangeMap& area, const std::wstring& hla13routingSpace) THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void deleteRegion(const RtiDriver::Region& region) THROW_SPEC (HlaRtiException, HlaNotConnectedException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException);

         //Callbacks
        void attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& attributeNames);
        void attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& attributeNames);

   };
}
#endif
