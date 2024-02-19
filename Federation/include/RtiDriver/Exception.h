/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DS_DRIVER_EXCEPTION
#define DS_DRIVER_EXCEPTION

#include <string>

/*
 * The usage of non-empty exception specifications are disabled by default.
 * They can be enabled by defining RTI_DRIVER_USE_THROW_SPEC.
 *
 * Note that Microsoft Visual C++ compilers ignore non-empty exception specifications,
 * https://docs.microsoft.com/en-us/cpp/cpp/nonstandard-behavior#function-exception-specifiers
 */

#if defined(RTI_DRIVER_USE_THROW_SPEC)
    #define RTI_DRIVER_THROW_SPEC       throw
#else
    #define RTI_DRIVER_THROW_SPEC(...)
#endif

namespace RtiDriver {
   // This class follows the interface of the C++ standard exception
   // class.  The key method, what, returns a string that
   // describes details of the exception that has occurred.

   class BaseException
   {
   public:
      explicit BaseException(std::wstring const & message) :
         _message(message)
      {}

      virtual ~BaseException ()
         RTI_DRIVER_THROW_SPEC()
      {}

      virtual std::wstring what() const
         RTI_DRIVER_THROW_SPEC()
      {
         return _message;
      }

   private:
      std::wstring _message;
   };

#define WIDEN_(x) L ## x
#define WIDEN(x)  WIDEN_(x)

#define RTI_EXCEPTION_SUPER(A, B)                                 \
   class A : public B {                                           \
   public:                                                        \
      explicit A(std::wstring message) :                          \
         B(std::wstring(WIDEN(#A)) + L": " + message)             \
      {}                                                          \
   };

#define RTI_EXCEPTION(A) RTI_EXCEPTION_SUPER(A, BaseException)

   //Exceptions used by both Evolved and 1516-2000:
   RTI_EXCEPTION(AttributeAlreadyBeingAcquired)
   RTI_EXCEPTION(AttributeNotDefined)
   RTI_EXCEPTION(AttributeNotOwned)
   RTI_EXCEPTION(AttributeNotPublished)
   RTI_EXCEPTION(CouldNotOpenFDD)
   RTI_EXCEPTION(DeletePrivilegeNotHeld)
   RTI_EXCEPTION(ErrorReadingFDD)
   RTI_EXCEPTION(FederateAlreadyExecutionMember)
   RTI_EXCEPTION(FederateNotExecutionMember)
   RTI_EXCEPTION(FederateOwnsAttributes)
   RTI_EXCEPTION(FederateServiceInvocationsAreBeingReportedViaMOM)
   RTI_EXCEPTION(FederationExecutionAlreadyExists)
   RTI_EXCEPTION(FederationExecutionDoesNotExist)
   RTI_EXCEPTION(InteractionClassNotDefined)
   RTI_EXCEPTION(InteractionClassNotPublished)
   RTI_EXCEPTION(InTimeAdvancingState)
   RTI_EXCEPTION(InvalidDimension)
   RTI_EXCEPTION(InvalidFederateHandle)
   RTI_EXCEPTION(InvalidLookahead)
   RTI_EXCEPTION(InvalidRegion)
   RTI_EXCEPTION(InvalidRegionContext)
   RTI_EXCEPTION(LogicalTimeAlreadyPassed)
   RTI_EXCEPTION(NotConnected)
   RTI_EXCEPTION(ObjectClassNotDefined)
   RTI_EXCEPTION(ObjectClassNotPublished)
   RTI_EXCEPTION(ObjectInstanceNameInUse)
   RTI_EXCEPTION(ObjectInstanceNameNotReserved)
   RTI_EXCEPTION(ObjectInstanceNotKnown)
   RTI_EXCEPTION(OwnershipAcquisitionPending)
   RTI_EXCEPTION(RegionInUse)
   RTI_EXCEPTION(RegionDoesNotContainDimension)
   RTI_EXCEPTION(RequestForTimeConstrainedPending)
   RTI_EXCEPTION(RequestForTimeRegulationPending)
   RTI_EXCEPTION(RestoreInProgress)
   RTI_EXCEPTION(RestoreNotRequested)
   RTI_EXCEPTION(RTIinternalError)
   RTI_EXCEPTION(SaveInProgress)
   RTI_EXCEPTION(TimeConstrainedAlreadyEnabled)
   RTI_EXCEPTION(TimeRegulationAlreadyEnabled)
   RTI_EXCEPTION(TimeRegulationIsNotEnabled)

   //Exceptions used by only Evolved:
   RTI_EXCEPTION(AlreadyConnected)
   RTI_EXCEPTION(CallNotAllowedFromWithinCallback)
   RTI_EXCEPTION(ConnectionFailed)
   RTI_EXCEPTION(CouldNotCreateLogicalTimeFactory)
   RTI_EXCEPTION(CouldNotDecode)
   RTI_EXCEPTION(FederateIsExecutionMember)
   RTI_EXCEPTION(FederateHasNotBegunSave)
   RTI_EXCEPTION(FederateUnableToUseTime)
   RTI_EXCEPTION(FederatesCurrentlyJoined)
   RTI_EXCEPTION(IllegalName)
   RTI_EXCEPTION(InvalidInteractionClassHandle)
   RTI_EXCEPTION(InvalidLocalSettingsDesignator)
   RTI_EXCEPTION(InvalidLogicalTime)
   RTI_EXCEPTION(InvalidResignAction)
   RTI_EXCEPTION(NameNotFound)
   RTI_EXCEPTION(SaveNotInitiated)
   RTI_EXCEPTION(SynchronizationPointLabelNotAnnounced)
   RTI_EXCEPTION(UnsupportedCallbackModel)
   RTI_EXCEPTION(AttributeAlreadyOwned)
   RTI_EXCEPTION(AttributeAcquisitionWasNotRequested)

   //Exceptions used by only 1516-2000:
   RTI_EXCEPTION(InteractionParameterNotDefined)
   RTI_EXCEPTION(InvalidObjectClassHandle)

   //Exceptions used by API
   RTI_EXCEPTION_SUPER(InvalidLicense, ConnectionFailed)

#undef RTI_EXCEPTION
#undef RTI_EXCEPTION_SUPER
}
#endif
