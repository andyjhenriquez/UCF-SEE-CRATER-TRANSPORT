/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_NULL_FEDERATE_AMBASSADOR
#define DS_DRIVER_NULL_FEDERATE_AMBASSADOR

#include "FederateAmbassador.h"

namespace RtiDriver {

   class NullFederateAmbassador : public FederateAmbassador {
   public:
      NullFederateAmbassador () {}

      virtual ~NullFederateAmbassador() {}

      ////////////////////////////////////
      // Federation Management Services //
      ////////////////////////////////////

      virtual void connectionLost(const std::wstring& faultDescription) {}

      //
      // Synchpoints
      //

      virtual void synchronizationPointRegistrationSucceeded(const std::wstring& synchPointName) {}

      virtual void synchronizationPointRegistrationFailed(const std::wstring& synchPointName, SynchronizationPointFailureReason failureReason) {}

      virtual void announceSynchronizationPoint(const std::wstring& synchPointName, const VariableLengthData& userSuppliedTag) {}

      virtual void federationSynchronized(const std::wstring& synchPointName) {}

      //
      // Save
      //

      virtual void initiateFederateSave(const std::wstring& label) {}

      virtual void initiateFederateSave(const std::wstring& label, const LogicalTime theTime) {}


      virtual void federationSaved() {}

      virtual void federationNotSaved(SaveFailureReason saveFailureReason) {}

      //
      // Restore
      //

      virtual void requestFederationRestoreSucceeded(const std::wstring& label) {}

      virtual void requestFederationRestoreFailed(const std::wstring& label) {}

      virtual void federationRestoreBegun() {}

      virtual void initiateFederateRestore(const std::wstring& label, const FederateHandle& federateHandle, const std::wstring& federateName) {}

      virtual void federationRestored() {}

      virtual void federationNotRestored(RestoreFailureReason restoreFailureReason) {}

      ////////////////////////////////
      // Object Management Services //
      ////////////////////////////////

      virtual void objectInstanceNameReservationSucceeded(const std::wstring& instanceName) {}

      virtual void objectInstanceNameReservationFailed(const std::wstring& instanceName){}


      virtual void discoverObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName) {}

      virtual void discoverObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName,
         const FederateHandle& producingFederate) {}


      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag) {}

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
         const VariableLengthData& userSuppliedTag, const FederateHandle& producingFederate) {}

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
        const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) {}

      virtual void reflectAttributeValues(const ObjectInstanceHandle& objectInstanceHandle, const NameValueMap& attributeHandleValueMap,
        const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType, const FederateHandle& producingFederate) {}



      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag) {}

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
         const VariableLengthData& userSuppliedTag, const FederateHandle& producingFederate) {}

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
        const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) {}

      virtual void receiveInteraction(const InteractionClassHandle& interactionClassHandle, const NameValueMap& parameterHandleValueMap,
        const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType, const FederateHandle& producingFederate) {}


      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag) {}

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag,
         const FederateHandle& producingFederate) {}

     virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType) {}

      virtual void removeObjectInstance(const ObjectInstanceHandle& objectInstanceHandle, const VariableLengthData& userSuppliedTag, const LogicalTime theTime, const OrderType orderType,
        const FederateHandle& producingFederate) {}


      virtual void provideAttributeValueUpdate(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
         const VariableLengthData& userSuppliedTag) {}

      ///////////////////////////////////
      // Ownership Management Services //
      ///////////////////////////////////

      virtual void requestAttributeOwnershipRelease(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
          const VariableLengthData& userSuppliedTag) {}

      virtual void attributeOwnershipAcquisitionNotification(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet,
          const VariableLengthData& userSuppliedTag) {}

      virtual void requestAttributeOwnershipAssumption(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& offeredAttributes,
          const VariableLengthData& userSuppliedTag) {}

      virtual void attributeOwnershipUnavailable(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& theAttributes) {}

      virtual void informAttributeOwnership(const ObjectInstanceHandle& theObject, const std::wstring theAttribute, const FederateHandle& federateHandle) {}

      virtual void attributeIsNotOwned(const ObjectInstanceHandle& theObject, const std::wstring theAttribute) {}

      virtual void attributeIsOwnedByRTI(const ObjectInstanceHandle& theObject, const std::wstring theAttribute) {}

      virtual void confirmAttributeOwnershipAcquisitionCancellation(const ObjectInstanceHandle& theObject, const NameSet& attributeHandleSet) {}

      //////////////////////////////////
      // Data Distribution Management //
      //////////////////////////////////

      virtual void attributesInScope(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet) {}

      virtual void attributesOutOfScope(const ObjectInstanceHandle& objectInstanceHandle, const NameSet& attributeHandleSet) {}

      //////////////////////////////
      // Time Management Services //
      //////////////////////////////

      virtual void timeRegulationEnabled(const LogicalTime theTime) {}

      virtual void timeConstrainedEnabled(const LogicalTime theTime) {}

      virtual void timeAdvanceGrant(const LogicalTime theTime) {}
   };
}
#endif
