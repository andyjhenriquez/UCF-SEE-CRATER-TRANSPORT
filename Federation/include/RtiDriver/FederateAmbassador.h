/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_FEDERATE_AMBASSADOR
#define DS_DRIVER_FEDERATE_AMBASSADOR

#include <string>

#include "Types.h"
#include "ObjectClassHandle.h"
#include "ObjectInstanceHandle.h"
#include "InteractionClassHandle.h"
#include "FederateHandle.h"

namespace RtiDriver {

   class FederateAmbassador {
   public:
      virtual ~FederateAmbassador() {}

      ////////////////////////////////////
      // Federation Management Services //
      ////////////////////////////////////

      virtual void connectionLost(const std::wstring& faultDescription) = 0;

      //
      // Synchpoints
      //

      virtual void synchronizationPointRegistrationSucceeded(const std::wstring& synchPointName) = 0;

      virtual void synchronizationPointRegistrationFailed(const std::wstring& synchPointName, SynchronizationPointFailureReason failureReason) = 0;

      virtual void announceSynchronizationPoint(const std::wstring& synchPointName, const VariableLengthData& userSuppliedTag) = 0;

      virtual void federationSynchronized(const std::wstring& synchPointName) = 0;

      //
      // Save
      //

      virtual void initiateFederateSave(const std::wstring& label) = 0;

      virtual void initiateFederateSave(const std::wstring& label, const LogicalTime theTime) = 0;


      virtual void federationSaved() = 0;

      virtual void federationNotSaved(SaveFailureReason saveFailureReason) = 0;

      //
      // Restore
      //

      virtual void requestFederationRestoreSucceeded(const std::wstring& label) = 0;

      virtual void requestFederationRestoreFailed(const std::wstring& label) = 0;

      virtual void federationRestoreBegun() = 0;

      virtual void initiateFederateRestore(const std::wstring& label, const FederateHandle& federateHandle, const std::wstring& federateName) = 0;

      virtual void federationRestored() = 0;

      virtual void federationNotRestored(RestoreFailureReason restoreFailureReason) = 0;

      ////////////////////////////////
      // Object Management Services //
      ////////////////////////////////

      virtual void objectInstanceNameReservationSucceeded(const std::wstring& instanceName) = 0;

      virtual void objectInstanceNameReservationFailed(const std::wstring& instanceName)= 0;


      virtual void discoverObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName) = 0;

      virtual void discoverObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName,
         const FederateHandle& producingFederate) = 0;


      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag) = 0;

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag, const FederateHandle& producingFederate) = 0;

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) = 0;

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType, const FederateHandle& producingFederate) = 0;


      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag) = 0;

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag, const FederateHandle& producingFederate) = 0;

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) = 0;

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType, const FederateHandle& producingFederate) = 0;


      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag) = 0;

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag,
         const FederateHandle& producingFederate) = 0;

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) = 0;

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType,
         const FederateHandle& producingFederate) = 0;


      virtual void provideAttributeValueUpdate(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
         const VariableLengthData& userSuppliedTag) = 0;

      ///////////////////////////////////
      // Ownership Management Services //
      ///////////////////////////////////

      virtual void requestAttributeOwnershipRelease(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
          const VariableLengthData& userSuppliedTag) = 0;

      virtual void attributeOwnershipAcquisitionNotification(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
          const VariableLengthData& userSuppliedTag) = 0;

      virtual void requestAttributeOwnershipAssumption(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& offeredAttributes,
          const VariableLengthData& userSuppliedTag) = 0;

      virtual void attributeOwnershipUnavailable(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& theAttributes) = 0;

      virtual void informAttributeOwnership(const ObjectInstanceHandle& theObject, const std::wstring theAttribute, const FederateHandle& federateHandle) = 0;

      virtual void attributeIsNotOwned(const ObjectInstanceHandle& theObject, const std::wstring theAttribute) = 0;

      virtual void attributeIsOwnedByRTI(const ObjectInstanceHandle& theObject, const std::wstring theAttribute) = 0;

      virtual void confirmAttributeOwnershipAcquisitionCancellation(const ObjectInstanceHandle& theObject, const NameSet& attributeHandleSet) = 0;

      //////////////////////////////////
      // Data Distribution Management //
      //////////////////////////////////

      virtual void attributesInScope(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet) = 0;

      virtual void attributesOutOfScope(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet) = 0;

      //////////////////////////////
      // Time Management Services //
      //////////////////////////////

      virtual void timeRegulationEnabled(const LogicalTime theTime) = 0;

      virtual void timeConstrainedEnabled(const LogicalTime theTime) = 0;

      virtual void timeAdvanceGrant(const LogicalTime theTime) = 0;
   };
}
#endif
