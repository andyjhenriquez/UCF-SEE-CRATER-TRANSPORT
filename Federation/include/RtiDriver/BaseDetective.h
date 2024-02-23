/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_BASE_DETECTIVE
#define DS_DRIVER_BASE_DETECTIVE

#include "Detective.h"

#include <memory>


namespace RtiDriver {

   class BaseDetective : public Detective {
   protected: 
      RtiDriver::RtiAmbassador* _rtiAmbassador;
      RtiDriver::FederateAmbassador* _federateAmbassador;

   public:
      virtual ~BaseDetective() {
         delete _rtiAmbassador;
      }

      //Called when the Detective is installed, takes ownership of pointer
      virtual void setRtiAmbassador(RtiDriver::RtiAmbassador* rtiAmbassador) {
         _rtiAmbassador = rtiAmbassador;
      }

      //Called just before joinFederationExecution, does not take ownership of pointer
      virtual void setFederateAmbassador(RtiDriver::FederateAmbassador* federateAmbassador) {
         _federateAmbassador = federateAmbassador;
      }

      /*
       * RTI ambassador calls
       */

      ////////////////////////////////////
      // Federation Management Services //
      ////////////////////////////////////

      virtual void disconnect()
         RTI_DRIVER_THROW_SPEC(
         FederateIsExecutionMember,
         RTIinternalError) {
            _rtiAmbassador->disconnect();
      }

      virtual void createFederationExecution(const std::wstring& federationExecutionName, const std::wstring& fdd, const std::vector<std::wstring>& additionalFomModules = std::vector<std::wstring>(0), const std::wstring& logicalTimeImpl = L"")
         RTI_DRIVER_THROW_SPEC(
         FederationExecutionAlreadyExists,
         CouldNotOpenFDD,
         ErrorReadingFDD,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->createFederationExecution(federationExecutionName, fdd, additionalFomModules, logicalTimeImpl);
      }

      virtual void destroyFederationExecution(const std::wstring& federationExecutionName)
         RTI_DRIVER_THROW_SPEC(
         FederatesCurrentlyJoined,
         FederationExecutionDoesNotExist,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->destroyFederationExecution(federationExecutionName);
      }

     /*
      * Note: Does NOT take memory ownership of federateReference!
      */
      virtual FederateHandle* joinFederationExecution(const std::wstring& federateName, const std::wstring& federateType, const std::wstring& federationExecutionName,
         FederateAmbassador* federateReference, const std::vector<std::wstring>& additionalFomModules,const std::wstring& logicalTimeImpl)
         RTI_DRIVER_THROW_SPEC(
         FederateAlreadyExecutionMember,
         FederationExecutionDoesNotExist,
         CouldNotOpenFDD,
         ErrorReadingFDD,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->joinFederationExecution(federateName, federateType, federationExecutionName, federateReference, additionalFomModules, logicalTimeImpl);
      }

      virtual void resignFederationExecution(ResignAction resignAction)
         RTI_DRIVER_THROW_SPEC(
         OwnershipAcquisitionPending,
         FederateOwnsAttributes,
         FederateNotExecutionMember,
         NotConnected,
         InvalidResignAction,
         RTIinternalError) {
            _rtiAmbassador->resignFederationExecution(resignAction);
      }

      //
      // Synchpoints
      //

      virtual void registerFederationSynchronizationPoint(const std::wstring& synchronizationPointLabel, const VariableLengthData& userSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->registerFederationSynchronizationPoint(synchronizationPointLabel, userSuppliedTag);
      }

      virtual void registerFederationSynchronizationPoint(const std::wstring& synchronizationPointLabel, const VariableLengthData& userSuppliedTag,
         const FederateHandleSet& synchronizationSet)
         RTI_DRIVER_THROW_SPEC(
         InvalidFederateHandle,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->registerFederationSynchronizationPoint(synchronizationPointLabel, userSuppliedTag, synchronizationSet);
      }

      virtual void synchronizationPointAchieved(const std::wstring& synchronizationPointLabel)
         RTI_DRIVER_THROW_SPEC(
         SynchronizationPointLabelNotAnnounced,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->synchronizationPointAchieved(synchronizationPointLabel);
      }

      //
      // Save
      //

      virtual void requestFederationSave(const std::wstring& label)
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
               _rtiAmbassador->requestFederationSave(label);
      }

      virtual void requestFederationSave(const std::wstring& label, const LogicalTime theTime)
         RTI_DRIVER_THROW_SPEC(
            LogicalTimeAlreadyPassed,
            InvalidLogicalTime,
            FederateUnableToUseTime,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
               _rtiAmbassador->requestFederationSave(label, theTime);
      }

      virtual void federateSaveBegun()
         RTI_DRIVER_THROW_SPEC(
         SaveNotInitiated,
         FederateNotExecutionMember,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->federateSaveBegun();
      }

      virtual void federateSaveComplete()
         RTI_DRIVER_THROW_SPEC(
         SaveNotInitiated,
         FederateHasNotBegunSave,
         FederateNotExecutionMember,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->federateSaveComplete();
      }

      virtual void federateSaveNotComplete()
         RTI_DRIVER_THROW_SPEC(
            SaveNotInitiated,
            FederateHasNotBegunSave,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
               _rtiAmbassador->federateSaveNotComplete();
      }

      //
      // Restore
      //

      virtual void requestFederationRestore(const std::wstring& label)
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
               _rtiAmbassador->requestFederationRestore(label);
      }

      virtual void federateRestoreComplete()
         RTI_DRIVER_THROW_SPEC(
         RestoreNotRequested,
         FederateNotExecutionMember,
         SaveInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->federateRestoreComplete();
      }

      virtual void federateRestoreNotComplete()
         RTI_DRIVER_THROW_SPEC(
            RestoreNotRequested,
            SaveInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
               _rtiAmbassador->federateRestoreNotComplete();
      }


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
         RTIinternalError) {
            _rtiAmbassador->publishObjectClassAttributes(objectClassHandle, attributes);
      }

      virtual void subscribeObjectClassAttributes(const ObjectClassHandle& objectClassHandle, const NameSet& attributes)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         ObjectClassNotDefined,
         AttributeNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->subscribeObjectClassAttributes(objectClassHandle, attributes);
      }

    virtual void subscribeObjectClassAttributesWithRegions(const ObjectClassHandle& objectClassHandle, const NameRegionsMap& attributeRegions)
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
         RTIinternalError){
              _rtiAmbassador->subscribeObjectClassAttributesWithRegions(objectClassHandle, attributeRegions);
     }

    virtual void unsubscribeObjectClassAttributesWithRegions(const ObjectClassHandle& objectClassHandle, const NameRegionsMap& attributeRegions)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         ObjectClassNotDefined,
         AttributeNotDefined,
         InvalidRegion,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
              _rtiAmbassador->unsubscribeObjectClassAttributesWithRegions(objectClassHandle, attributeRegions);
     }

      virtual void publishInteractionClass(const InteractionClassHandle& interactionClassHandle)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->publishInteractionClass(interactionClassHandle);
      }

      virtual void subscribeInteractionClass(const InteractionClassHandle& interactionClassHandle)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         FederateServiceInvocationsAreBeingReportedViaMOM,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->subscribeInteractionClass(interactionClassHandle);
      }

    virtual void subscribeInteractionClassWithRegions(const InteractionClassHandle& interactionClassHandle, const RegionSet& regions)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         InvalidRegion,
         InvalidRegionContext,
         FederateServiceInvocationsAreBeingReportedViaMOM,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->subscribeInteractionClassWithRegions(interactionClassHandle, regions);
      }

    virtual void unsubscribeInteractionClassWithRegions(const InteractionClassHandle& interactionClassHandle, const RegionSet& regions)
         RTI_DRIVER_THROW_SPEC(
         InteractionClassNotDefined,
         InvalidRegion,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->unsubscribeInteractionClassWithRegions(interactionClassHandle, regions);
      }

      ////////////////////////////////
      // Object Management Services //
      ////////////////////////////////

      virtual bool reserveObjectInstanceName(const std::wstring& theObjectName)
         RTI_DRIVER_THROW_SPEC(
         IllegalName,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->reserveObjectInstanceName(theObjectName);
      }

      virtual bool releaseObjectInstanceName(const std::wstring& theObjectName)
         RTI_DRIVER_THROW_SPEC(
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->releaseObjectInstanceName(theObjectName);
      }

      virtual ObjectInstanceHandle* registerObjectInstance(const ObjectClassHandle& theClass)
         RTI_DRIVER_THROW_SPEC(
         ObjectInstanceNotKnown,
         ObjectClassNotDefined,
         ObjectClassNotPublished,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->registerObjectInstance(theClass);
      }

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
         RTIinternalError) {
            return _rtiAmbassador->registerObjectInstance(theClass, theObjectName);
      }

    virtual ObjectInstanceHandle* registerObjectInstanceWithRegions(const ObjectClassHandle& theClass,
                                                                          const NameRegionsMap& attributeRegions,
                                                                          const std::wstring& theObjectName)
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
         RTIinternalError) {
            return _rtiAmbassador->registerObjectInstanceWithRegions(theClass, attributeRegions, theObjectName);
      }

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
         RTIinternalError) {
            _rtiAmbassador->updateAttributeValues(theObject, theAttributes, userSuppliedTag);
      }

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
         RTIinternalError) {
            _rtiAmbassador->sendInteraction(theInteraction, theParameters, userSuppliedTag);
      }

    virtual void sendInteractionWithRegions(const InteractionClassHandle& theInteraction,
                                    const NameValueMap& theParameters,
                                    const VariableLengthData& userSuppliedTag,
                                    const RegionSet& regions,
                                    const LogicalTime logicalTime)
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
         RTIinternalError) {
            _rtiAmbassador->sendInteractionWithRegions(theInteraction, theParameters, userSuppliedTag, regions, logicalTime);
      }

      virtual void deleteObjectInstance(const ObjectInstanceHandle& objectHandle, const VariableLengthData& userSuppliedTag)
         RTI_DRIVER_THROW_SPEC(
         DeletePrivilegeNotHeld,
         ObjectInstanceNotKnown,
         FederateNotExecutionMember,
         SaveInProgress,
         RestoreInProgress,
         NotConnected,
         RTIinternalError) {
            _rtiAmbassador->deleteObjectInstance(objectHandle, userSuppliedTag);
      }

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
         RTIinternalError) {
            _rtiAmbassador->requestAttributeValueUpdate(theObject, theAttributes, userSuppliedTag);
      }

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
         RTIinternalError) {
            _rtiAmbassador->attributeOwnershipAcquisition(theObject, desiredAttributes, theUserSuppliedTag);
      }

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
         RTIinternalError) {
            _rtiAmbassador->attributeOwnershipDivestitureIfWanted(theObject, theAttributes, theDivestedAttributes);
      }

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
         RTIinternalError) {
            _rtiAmbassador->unconditionalAttributeOwnershipDivestiture(theObject, theAttributes);
      }

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
         RTIinternalError) {
            _rtiAmbassador->attributeOwnershipAcquisitionIfAvailable(theObject, desiredAttributes);
      }

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
         NotConnected) {
            _rtiAmbassador->queryAttributeOwnership(theObject, theAttribute);
      }

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
         RTIinternalError) {
             return _rtiAmbassador->attributeOwnershipReleaseDenied(theObject, theAttributes);
      }

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
          AttributeAcquisitionWasNotRequested) {
              return _rtiAmbassador->cancelAttributeOwnershipAcquisition(theObject, theAttributes);
      }

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
          NotConnected) {
              return _rtiAmbassador->isAttributeOwnedByFederate(theObject, theAttribute);
      }

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
            RTIinternalError) {
        return _rtiAmbassador->enableTimeRegulation(lookahead);
   }

virtual bool enableTimeConstrained()  RTI_DRIVER_THROW_SPEC(
            InTimeAdvancingState,
            RequestForTimeConstrainedPending,
            TimeConstrainedAlreadyEnabled,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
        return _rtiAmbassador->enableTimeConstrained();
   }

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
            RTIinternalError) {
        _rtiAmbassador->timeAdvanceRequest(logicalTime);
   }

virtual void nextMessageRequestAvailable(const LogicalTime logicalTime)  RTI_DRIVER_THROW_SPEC(
            LogicalTimeAlreadyPassed,
            InvalidLogicalTime,
            InTimeAdvancingState,
            RequestForTimeRegulationPending,
            RequestForTimeConstrainedPending,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
        _rtiAmbassador->nextMessageRequestAvailable(logicalTime);
   }

virtual void modifyLookahead(const LogicalTime lookahead)  RTI_DRIVER_THROW_SPEC(
            InvalidLookahead,
            InTimeAdvancingState,
            TimeRegulationIsNotEnabled,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
        _rtiAmbassador->modifyLookahead(lookahead);
   }

virtual bool queryGALT(LogicalTime& logicalTime) RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
        return _rtiAmbassador->queryGALT(logicalTime);
   }

virtual bool enableAsynchronousDelivery() RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
        return _rtiAmbassador->enableAsynchronousDelivery();
   }

virtual bool disableAsynchronousDelivery() RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
            RTIinternalError) {
        return _rtiAmbassador->disableAsynchronousDelivery();
   }

    //////////////////////////////////
    // Data Distribution Management //
    //////////////////////////////////

    virtual Region* createRegion(const NameRangeMap& dimensions, const std::wstring& hla13RoutingSpace)
         RTI_DRIVER_THROW_SPEC(
            InvalidDimension,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->createRegion(dimensions, hla13RoutingSpace);
      }

    virtual void updateRegion(const Region& region, const NameRangeMap& updatedDimensions)
         RTI_DRIVER_THROW_SPEC(
            InvalidDimension,
            InvalidRegion,
            RegionDoesNotContainDimension,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
         RTIinternalError) {
            _rtiAmbassador->updateRegion(region, updatedDimensions);
      }

    virtual void commitRegions(const RegionSet& regions)
         RTI_DRIVER_THROW_SPEC(
            InvalidRegion,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
         RTIinternalError) {
            _rtiAmbassador->commitRegions(regions);
      }

    virtual void deleteRegion(const Region& region)
         RTI_DRIVER_THROW_SPEC(
            RegionInUse,
            InvalidRegion,
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
         RTIinternalError) {
            _rtiAmbassador->deleteRegion(region);
      }

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
         RTIinternalError) {
            _rtiAmbassador->associateRegionsForUpdates(objectInstance, attributeRegions);
      }

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
         RTIinternalError) {
            _rtiAmbassador->unassociateRegionsForUpdates(objectInstance, attributeRegions);
      }

    virtual bool setAttributeScopeAdvisorySwitch(bool enable)
         RTI_DRIVER_THROW_SPEC(
            SaveInProgress,
            RestoreInProgress,
            FederateNotExecutionMember,
            NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->setAttributeScopeAdvisorySwitch(enable);
      }

    virtual unsigned int normalizeFederateHandle(const FederateHandle& federateHandle)
         RTI_DRIVER_THROW_SPEC(
            InvalidFederateHandle,
            FederateNotExecutionMember,
            NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->normalizeFederateHandle(federateHandle);
      }

      /////////////////////////
      // RTI Support Services //
      //////////////////////////

      virtual ObjectClassHandle* getObjectClassHandle(const std::wstring& objectClassName)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->getObjectClassHandle(objectClassName);
      }

      virtual InteractionClassHandle* getInteractionClassHandle(const std::wstring& interactionClassName)
         RTI_DRIVER_THROW_SPEC(
         NameNotFound,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->getInteractionClassHandle(interactionClassName);
      }

      virtual FederateHandle* decodeFederateHandle(VariableLengthData const & encodedFederateHandle)
         RTI_DRIVER_THROW_SPEC(
         CouldNotDecode,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->decodeFederateHandle(encodedFederateHandle);
      }

      virtual ObjectInstanceHandle* decodeObjectInstanceHandle(VariableLengthData const & encodedObjectInstanceHandle)
         RTI_DRIVER_THROW_SPEC(
         CouldNotDecode,
         FederateNotExecutionMember,
         NotConnected,
         RTIinternalError) {
            return _rtiAmbassador->decodeObjectInstanceHandle(encodedObjectInstanceHandle);
      }

      virtual HlaVersion getHLAversion() {
         return _rtiAmbassador->getHLAversion();
      }


      /*
       * Federate ambassador calls
       */

      ////////////////////////////////////
      // Federation Management Services //
      ////////////////////////////////////

      virtual void connectionLost(const std::wstring& faultDescription) {
         _federateAmbassador->connectionLost(faultDescription);
      }

      //
      // Synchpoints
      //

      virtual void synchronizationPointRegistrationSucceeded(const std::wstring& synchPointName) {
         _federateAmbassador->synchronizationPointRegistrationSucceeded(synchPointName);
      }

      virtual void synchronizationPointRegistrationFailed(const std::wstring& synchPointName, SynchronizationPointFailureReason failureReason) {
         _federateAmbassador->synchronizationPointRegistrationFailed(synchPointName, failureReason);
      }

      virtual void announceSynchronizationPoint(const std::wstring& synchPointName, const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->announceSynchronizationPoint(synchPointName, userSuppliedTag);
      }

      virtual void federationSynchronized(const std::wstring& synchPointName) {
         _federateAmbassador->federationSynchronized(synchPointName);
      }

      //
      // Save
      //

      virtual void initiateFederateSave(const std::wstring& label) {
         _federateAmbassador->initiateFederateSave(label);
      }

      //
      // Restore
      //

      virtual void initiateFederateRestore(const std::wstring& label, const FederateHandle& federateHandle, const std::wstring& federateName) {
         _federateAmbassador->initiateFederateRestore(label, federateHandle, federateName);
      }

      ////////////////////////////////
      // Object Management Services //
      ////////////////////////////////

      virtual void objectInstanceNameReservationSucceeded(const std::wstring& instanceName) {
         _federateAmbassador->objectInstanceNameReservationSucceeded(instanceName);
      }

      virtual void objectInstanceNameReservationFailed(const std::wstring& instanceName) {
         _federateAmbassador->objectInstanceNameReservationFailed(instanceName);
      }

      virtual void discoverObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName) {
         _federateAmbassador->discoverObjectInstance(objectInstanceHandle, instanceName);
      }

      virtual void discoverObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName,
         const FederateHandle& producingFederate) {
         _federateAmbassador->discoverObjectInstance(objectInstanceHandle, instanceName, producingFederate);
      }

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag);
      }

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag, const FederateHandle& producingFederate) {
         _federateAmbassador->reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag, producingFederate);
      }

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
        const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) {
         _federateAmbassador->reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag, theTime, orderType);
      }

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
        const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType, const FederateHandle& producingFederate) {
         _federateAmbassador->reflectAttributeValues(objectInstanceHandle, attributeHandleValueMap, userSuppliedTag, theTime, orderType, producingFederate);
      }

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag);
      }

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag, const FederateHandle& producingFederate) {
         _federateAmbassador->receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag, producingFederate);
      }

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) {
         _federateAmbassador->receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag, theTime, orderType);
      }

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType, const FederateHandle& producingFederate) {
         _federateAmbassador->receiveInteraction(interactionClassHandle, parameterHandleValueMap, userSuppliedTag, theTime, orderType, producingFederate);
      }

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->removeObjectInstance(objectInstanceHandle, userSuppliedTag);
      }

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag,
         const FederateHandle& producingFederate) {
         _federateAmbassador->removeObjectInstance(objectInstanceHandle, userSuppliedTag, producingFederate);
      }

       virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) {
         _federateAmbassador->removeObjectInstance(objectInstanceHandle, userSuppliedTag, theTime, orderType);
      }

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType,
         const FederateHandle& producingFederate) {
         _federateAmbassador->removeObjectInstance(objectInstanceHandle, userSuppliedTag, theTime, orderType, producingFederate);
      }

      virtual void provideAttributeValueUpdate(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
         const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->provideAttributeValueUpdate(objectInstanceHandle, attributeHandleSet, userSuppliedTag);
      }

      ///////////////////////////////////
      // Ownership Management Services //
      ///////////////////////////////////

      virtual void requestAttributeOwnershipRelease(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
         const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->requestAttributeOwnershipRelease(objectInstanceHandle, attributeHandleSet, userSuppliedTag);
      }

      virtual void attributeOwnershipAcquisitionNotification(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
         const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->attributeOwnershipAcquisitionNotification(objectInstanceHandle, attributeHandleSet, userSuppliedTag);
       }

      virtual void requestAttributeOwnershipAssumption(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& offeredAttributes,
         const VariableLengthData& userSuppliedTag) {
         _federateAmbassador->requestAttributeOwnershipAssumption(objectInstanceHandle, offeredAttributes, userSuppliedTag);
      }

      virtual void attributeOwnershipUnavailable(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& theAttributes) {
         _federateAmbassador->attributeOwnershipUnavailable(objectInstanceHandle, theAttributes);
      }

      virtual void informAttributeOwnership(const ObjectInstanceHandle& theObject, const std::wstring theAttribute, const FederateHandle& federateHandle) {
         _federateAmbassador->informAttributeOwnership(theObject, theAttribute, federateHandle);
      }

      virtual void attributeIsNotOwned(const ObjectInstanceHandle& theObject, const std::wstring theAttribute) {
         _federateAmbassador->attributeIsNotOwned(theObject, theAttribute);
      }

      virtual void attributeIsOwnedByRTI(const ObjectInstanceHandle& theObject, const std::wstring theAttribute) {
         _federateAmbassador->attributeIsOwnedByRTI(theObject, theAttribute);
      }

      virtual void confirmAttributeOwnershipAcquisitionCancellation(const ObjectInstanceHandle& theObject, const NameSet& theAttributes) {
         _federateAmbassador->confirmAttributeOwnershipAcquisitionCancellation(theObject, theAttributes);
      }

      //////////////////////////////////
      // Data Distribution Management //
      //////////////////////////////////

      virtual void attributesInScope(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet) {
         _federateAmbassador->attributesInScope(objectInstanceHandle, attributeHandleSet);
      }

      virtual void attributesOutOfScope(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet) {
         _federateAmbassador->attributesOutOfScope(objectInstanceHandle, attributeHandleSet);
      }

      //////////////////////////////
      // Time Management Services //
      //////////////////////////////

      virtual void timeRegulationEnabled(const LogicalTime theTime) {
         _federateAmbassador->timeRegulationEnabled(theTime);
      }

      virtual void timeConstrainedEnabled(const LogicalTime theTime) {
         _federateAmbassador->timeConstrainedEnabled(theTime);
      }

      virtual void timeAdvanceGrant(const LogicalTime theTime) {
         _federateAmbassador->timeAdvanceGrant(theTime);
      }
   };
}

#endif
