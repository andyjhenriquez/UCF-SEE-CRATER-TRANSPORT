/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_RTI_AMBASSADOR
#define DS_DRIVER_RTI_AMBASSADOR

#if defined(_WIN32)
#pragma warning (disable : 4290)  // C++ exception specification in declaration 
#endif

#include "Exception.h"
#include "ObjectInstanceHandle.h"
#include "ObjectClassHandle.h"
#include "InteractionClassHandle.h"
#include "FederateHandle.h"
#include "FederateAmbassador.h"
#include "Region.h"
#include "Types.h"

#include <string>
#include <vector>
#include <memory>

namespace RtiDriver {

   /*
    * Caller responsible for all returned pointers.
    */
   class RtiAmbassador {

   public:

      virtual ~RtiAmbassador() {}

      ////////////////////////////////////
      // Federation Management Services //
      ////////////////////////////////////

      virtual void disconnect()
         RTI_DRIVER_THROW_SPEC(
         FederateIsExecutionMember,
         RTIinternalError) = 0;


      virtual void createFederationExecution(const std::wstring& federationExecutionName,
                                             const std::wstring& fdd,
                                             const std::vector<std::wstring>& additionalFomModules = std::vector<std::wstring>(0),
                                             const std::wstring& logicalTimeImpl = L"")
         RTI_DRIVER_THROW_SPEC(
         FederationExecutionAlreadyExists,
         CouldNotOpenFDD,
         ErrorReadingFDD,
         NotConnected,
         RTIinternalError) = 0;

      virtual void destroyFederationExecution(const std::wstring& federationExecutionName)
         RTI_DRIVER_THROW_SPEC(
         FederatesCurrentlyJoined,
         FederationExecutionDoesNotExist,
         NotConnected,
         RTIinternalError) = 0;

      /*
       * Note: Does NOT take memory ownership of federateReference!
       */
      virtual FederateHandle* joinFederationExecution(const std::wstring& federateName,
                                                      const std::wstring& federateType,
                                                      const std::wstring& federationExecutionName,
                                                      FederateAmbassador* federateReference,
                                                      const std::vector<std::wstring>& additionalFomModules = std::vector<std::wstring>(0),
                                                      const std::wstring& logicalTimeImpl = L"")
        RTI_DRIVER_THROW_SPEC(
        FederateAlreadyExecutionMember,
        FederationExecutionDoesNotExist,
        CouldNotOpenFDD,
        ErrorReadingFDD,
        SaveInProgress,
        RestoreInProgress,
        NotConnected,
        RTIinternalError) = 0;

      virtual void resignFederationExecution(ResignAction resignAction)
         RTI_DRIVER_THROW_SPEC(
         OwnershipAcquisitionPending,
         FederateOwnsAttributes,
         FederateNotExecutionMember,
         NotConnected,
         InvalidResignAction,
         RTIinternalError) = 0;

      //
      // Synchpoints
      //

      virtual void registerFederationSynchronizationPoint(const std::wstring& synchronizationPointLabel, const VariableLengthData& userSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void registerFederationSynchronizationPoint(const std::wstring& synchronizationPointLabel, const VariableLengthData& userSuppliedTag,
         const FederateHandleSet& synchronizationSet)
         RTI_DRIVER_THROW_SPEC(
         InvalidFederateHandle,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void synchronizationPointAchieved(const std::wstring& synchronizationPointLabel)
         RTI_DRIVER_THROW_SPEC(
         SynchronizationPointLabelNotAnnounced,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      //
      // Save
      //

      virtual void requestFederationSave(const std::wstring& label)
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void requestFederationSave(const std::wstring& label, const LogicalTime theTime)
         RTI_DRIVER_THROW_SPEC(
            LogicalTimeAlreadyPassed,
            InvalidLogicalTime,
            FederateUnableToUseTime,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void federateSaveBegun()
         RTI_DRIVER_THROW_SPEC(
         SaveNotInitiated,
         FederateNotExecutionMember,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void federateSaveComplete()
         RTI_DRIVER_THROW_SPEC(
         SaveNotInitiated,
         FederateHasNotBegunSave,
         FederateNotExecutionMember,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void federateSaveNotComplete()
         RTI_DRIVER_THROW_SPEC(
            SaveNotInitiated,
            SaveNotInitiated,
            FederateHasNotBegunSave,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      //
      // Restore
      //

      virtual void requestFederationRestore(const std::wstring& label)
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void federateRestoreComplete()
         RTI_DRIVER_THROW_SPEC(
         RestoreNotRequested,
         FederateNotExecutionMember,
         SaveInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void federateRestoreNotComplete()
         RTI_DRIVER_THROW_SPEC(
            RestoreNotRequested,
            SaveInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      /////////////////////////////////////
      // Declaration Management Services //
      /////////////////////////////////////

      virtual void publishObjectClassAttributes(const ObjectClassHandle& objectClassHandle, const NameSet& attributes)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         ObjectClassNotDefined,
         AttributeNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         OwnershipAcquisitionPending,
         NotConnected,
         RTIinternalError) = 0;

      virtual void publishInteractionClass(const InteractionClassHandle& interactionClassHandle)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void subscribeObjectClassAttributes(const ObjectClassHandle& objectClassHandle, const NameSet& attributes)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         ObjectClassNotDefined,
         AttributeNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void subscribeObjectClassAttributesWithRegions(const ObjectClassHandle& objectClassHandle,
                                                             const NameRegionsMap& attributeRegions)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         ObjectClassNotDefined,
         AttributeNotDefined,
         InvalidRegion,
         InvalidRegionContext,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void unsubscribeObjectClassAttributesWithRegions(const ObjectClassHandle& objectClassHandle,
                                                               const NameRegionsMap& attributeRegions)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         ObjectClassNotDefined,
         AttributeNotDefined,
         InvalidRegion,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void subscribeInteractionClass(const InteractionClassHandle& interactionClassHandle)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         FederateServiceInvocationsAreBeingReportedViaMOM,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void subscribeInteractionClassWithRegions(const InteractionClassHandle& interactionClassHandle,
                                                        const RegionSet& regions)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         InvalidRegion,
         InvalidRegionContext,
         FederateServiceInvocationsAreBeingReportedViaMOM,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void unsubscribeInteractionClassWithRegions(const InteractionClassHandle& interactionClassHandle,
                                                          const RegionSet& regions)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         InvalidRegion,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;


      ////////////////////////////////
      // Object Management Services //
      ////////////////////////////////

      /**
       * Reserve object instance name.
       *
       * @param theObjectName name to reserve
       *
       * @return <code>True</code> if the HLA implementation supports name reservation
       *         (ie a Reservation Succeeded or Failure callback should be expected),
       *         <code>false</code> othervise.
       *
       * @see FederateAmbassador#objectInstanceNameReservationSucceeded(String)
       * @see FederateAmbassador#objectInstanceNameReservationFailed(String)
       */
      virtual bool reserveObjectInstanceName(const std::wstring& theObjectName)
         RTI_DRIVER_THROW_SPEC(
         IllegalName,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      /**
       * Releases a name previously reserved by this federate. This may be called after an the
       * name has been used to register an object instance.
       *
       * @param theObjectName the name to unreserve.
       *
       * @return <code>true</code> if the HLA implementation supports name reservation release and the name was release,
       *         <code>false</code> otherwise.
       *
       * @see RTIambassador#reserveObjectInstanceName(String)
       */
      virtual bool releaseObjectInstanceName(const std::wstring& theObjectName)
         RTI_DRIVER_THROW_SPEC(
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual ObjectInstanceHandle* registerObjectInstance(const ObjectClassHandle& theClass)
         RTI_DRIVER_THROW_SPEC(
         ObjectInstanceNotKnown,
         ObjectClassNotDefined,
         ObjectClassNotPublished,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual ObjectInstanceHandle* registerObjectInstance(const ObjectClassHandle& theClass, const std::wstring& theObjectName)
         RTI_DRIVER_THROW_SPEC(
         ObjectClassNotDefined,
         ObjectClassNotPublished,
         ObjectInstanceNameNotReserved,
         ObjectInstanceNameInUse,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual ObjectInstanceHandle* registerObjectInstanceWithRegions(const ObjectClassHandle& theClass,
                                                                      const NameRegionsMap& attributeRegions,
                                                                      const std::wstring& theObjectName = L"")
         RTI_DRIVER_THROW_SPEC(
         ObjectClassNotDefined,
         ObjectClassNotPublished,
         ObjectInstanceNameNotReserved,
         ObjectInstanceNameInUse,
         AttributeNotDefined,
         AttributeNotPublished,
         InvalidRegion,
         InvalidRegionContext,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void updateAttributeValues(const ObjectInstanceHandle& theObject,
         const NameValueMap& theAttributes,
         const VariableLengthData& userSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         ObjectInstanceNotKnown,
         AttributeNotDefined,
         AttributeNotOwned,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NameNotFound,
         NotConnected,
         RTIinternalError) = 0;

      virtual void updateAttributeValues(const ObjectInstanceHandle& theObject,
         const NameValueMap& theAttributes,
         const VariableLengthData& userSuppliedTag,
         const LogicalTime logicalTime)
         RTI_DRIVER_THROW_SPEC(
         InvalidLogicalTime,
         ObjectInstanceNotKnown,
         AttributeNotDefined,
         AttributeNotOwned,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NameNotFound,
         NotConnected,
         RTIinternalError) = 0;

      virtual void sendInteraction(const InteractionClassHandle& theInteraction,
         const NameValueMap& theParameters,
         const VariableLengthData& userSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotPublished,
         InteractionClassNotDefined,
         InteractionParameterNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NameNotFound,
         NotConnected,
         RTIinternalError) = 0;

      virtual void sendInteraction(const InteractionClassHandle& theInteraction,
         const NameValueMap& theParameters,
         const VariableLengthData& userSuppliedTag,
         const LogicalTime logicalTime)
         RTI_DRIVER_THROW_SPEC(
         InvalidLogicalTime,
         InteractionClassNotPublished,
         InteractionClassNotDefined,
         InteractionParameterNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NameNotFound,
         NotConnected,
         RTIinternalError) = 0;

      virtual void sendInteractionWithRegions(const InteractionClassHandle& theInteraction,
                                              const NameValueMap& theParameters,
                                              const VariableLengthData& userSuppliedTag,
                                              const RegionSet& regions,
                                              const LogicalTime logicalTime = LogicalTime())
         RTI_DRIVER_THROW_SPEC(
         InvalidLogicalTime,
         InteractionClassNotPublished,
         InteractionClassNotDefined,
         InteractionParameterNotDefined,
         InvalidRegion,
         InvalidRegionContext,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NameNotFound,
         NotConnected,
         RTIinternalError) = 0;

      virtual void deleteObjectInstance(const ObjectInstanceHandle& objectHandle, const VariableLengthData& userSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         DeletePrivilegeNotHeld,
         ObjectInstanceNotKnown,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void deleteObjectInstance(const ObjectInstanceHandle& objectHandle, const VariableLengthData& userSuppliedTag,
                                        const LogicalTime logicalTime)
         RTI_DRIVER_THROW_SPEC(
         InvalidLogicalTime,
         DeletePrivilegeNotHeld,
         ObjectInstanceNotKnown,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) = 0;

      virtual void requestAttributeValueUpdate(const ObjectInstanceHandle& theObject,
         const NameSet& theAttributes,
         const VariableLengthData& userSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         ObjectInstanceNotKnown,
         AttributeNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NameNotFound,
         NotConnected,
         RTIinternalError) = 0;

      ///////////////////////////////////
      // Ownership Management Services //
      ///////////////////////////////////

      virtual void attributeOwnershipAcquisition(
         const ObjectInstanceHandle& theObject,
         const NameSet& desiredAttributes,
         const VariableLengthData& theUserSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         AttributeNotPublished,
         ObjectClassNotPublished,
         FederateOwnsAttributes,
         AttributeNotDefined,
         ObjectInstanceNotKnown,
         SaveInProgress,
         RestoreInProgress,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual void attributeOwnershipDivestitureIfWanted(
         const ObjectInstanceHandle& theObject,
         const NameSet& theAttributes,
         NameSet& theDivestedAttributes) // filled by RTI
         RTI_DRIVER_THROW_SPEC(
         AttributeNotOwned,
         AttributeNotDefined,
         ObjectInstanceNotKnown,
         SaveInProgress,
         RestoreInProgress,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual void unconditionalAttributeOwnershipDivestiture(
         const ObjectInstanceHandle& theObject,
         const NameSet& theAttributes)
         RTI_DRIVER_THROW_SPEC(
         AttributeNotOwned,
         AttributeNotDefined,
         ObjectInstanceNotKnown,
         SaveInProgress,
         RestoreInProgress,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual void attributeOwnershipAcquisitionIfAvailable(
         const ObjectInstanceHandle& theObject,
         const NameSet& desiredAttributes)
         RTI_DRIVER_THROW_SPEC(
         AttributeAlreadyBeingAcquired,
         AttributeNotPublished,
         ObjectClassNotPublished,
         FederateOwnsAttributes,
         AttributeNotDefined,
         ObjectInstanceNotKnown,
         SaveInProgress,
         RestoreInProgress,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual void queryAttributeOwnership(
         const ObjectInstanceHandle& theObject,
         const std::wstring& theAttribute)
         RTI_DRIVER_THROW_SPEC(
         AttributeNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         RTIinternalError,
         ObjectInstanceNotKnown,
         NotConnected) = 0;

      virtual bool attributeOwnershipReleaseDenied(
         const ObjectInstanceHandle& theObject,
         const NameSet& theAttributes)
         RTI_DRIVER_THROW_SPEC(
         AttributeNotOwned,
         AttributeNotDefined,
         ObjectInstanceNotKnown,
         SaveInProgress,
         RestoreInProgress,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

    virtual bool cancelAttributeOwnershipAcquisition(
         const ObjectInstanceHandle& theObject,
         const NameSet& theAttributes)
         RTI_DRIVER_THROW_SPEC(
         AttributeNotDefined,
         ObjectInstanceNotKnown,
         SaveInProgress,
         RestoreInProgress,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError,
         AttributeAlreadyOwned,
         AttributeAcquisitionWasNotRequested) = 0;

    virtual bool isAttributeOwnedByFederate(
        const ObjectInstanceHandle& theObject,
        const std::wstring& theAttribute)
        RTI_DRIVER_THROW_SPEC(
        AttributeNotDefined,
        FederateNotExecutionMember,
        SaveInProgress,
        RestoreInProgress,
        RTIinternalError,
        ObjectInstanceNotKnown,
        NotConnected) = 0;

      /////////////////////
      // Time Management //
      /////////////////////

     virtual bool enableTimeRegulation(const LogicalTime lookahead) RTI_DRIVER_THROW_SPEC(
            InvalidLookahead,
            InTimeAdvancingState,
            RequestForTimeRegulationPending,
            TimeRegulationAlreadyEnabled,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

     virtual bool enableTimeConstrained() RTI_DRIVER_THROW_SPEC(
            InTimeAdvancingState,
            RequestForTimeConstrainedPending,
            TimeConstrainedAlreadyEnabled,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

     virtual void timeAdvanceRequest(const LogicalTime logicalTime) RTI_DRIVER_THROW_SPEC(
            LogicalTimeAlreadyPassed,
            InvalidLogicalTime,
            InTimeAdvancingState,
            RequestForTimeRegulationPending,
            RequestForTimeConstrainedPending,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

     virtual void nextMessageRequestAvailable(const LogicalTime logicalTime) RTI_DRIVER_THROW_SPEC(
            LogicalTimeAlreadyPassed,
            InvalidLogicalTime,
            InTimeAdvancingState,
            RequestForTimeRegulationPending,
            RequestForTimeConstrainedPending,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

     virtual void modifyLookahead(const LogicalTime lookahead) RTI_DRIVER_THROW_SPEC(
            InvalidLookahead,
            InTimeAdvancingState,
            TimeRegulationIsNotEnabled,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual bool queryGALT(LogicalTime& theTime) // filled by RTI
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual bool enableAsynchronousDelivery()
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual bool disableAsynchronousDelivery()
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      //////////////////////////////////
      // Data Distribution Management //
      //////////////////////////////////

      /*
       * DDM is currently only supported by the HLA Evolved Profile, B!
       */

      virtual Region* createRegion(const NameRangeMap& dimensions, const std::wstring& hla13RoutingSpace = L"")
         RTI_DRIVER_THROW_SPEC(
            InvalidDimension,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void updateRegion(const Region& region, const NameRangeMap& updatedDimensions)
         RTI_DRIVER_THROW_SPEC(
            InvalidDimension,
            InvalidRegion,
            RegionDoesNotContainDimension,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void commitRegions(const RegionSet& regions)
         RTI_DRIVER_THROW_SPEC(
            InvalidRegion,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void deleteRegion(const Region& region)
         RTI_DRIVER_THROW_SPEC(
            RegionInUse,
            InvalidRegion,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void associateRegionsForUpdates(const ObjectInstanceHandle& objectInstance,
                                              const NameRegionsMap& attributeRegions)
         RTI_DRIVER_THROW_SPEC(
            ObjectInstanceNotKnown,
            AttributeNotDefined,
            InvalidRegion,
            InvalidRegionContext,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual void unassociateRegionsForUpdates(const ObjectInstanceHandle& objectInstance,
                                                const NameRegionsMap& attributeRegions)
         RTI_DRIVER_THROW_SPEC(
            ObjectInstanceNotKnown,
            AttributeNotDefined,
            InvalidRegion,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual bool setAttributeScopeAdvisorySwitch(bool enable)
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      virtual unsigned int normalizeFederateHandle(const FederateHandle& federateHandle)
         RTI_DRIVER_THROW_SPEC(
            InvalidFederateHandle,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) = 0;

      /////////////////////////
      // RTI Support Services //
      //////////////////////////

      virtual ObjectClassHandle* getObjectClassHandle(const std::wstring& objectClassName)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual InteractionClassHandle* getInteractionClassHandle(const std::wstring& interactionClassName)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual FederateHandle* decodeFederateHandle(VariableLengthData const & encodedFederateHandle)
         RTI_DRIVER_THROW_SPEC(
         CouldNotDecode,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual ObjectInstanceHandle* decodeObjectInstanceHandle(VariableLengthData const & encodedObjectInstanceHandle)
         RTI_DRIVER_THROW_SPEC(
         CouldNotDecode,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) = 0;

      virtual HlaVersion getHLAversion() = 0;
   };
}
#endif
