/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_TYPES
#define DS_DRIVER_TYPES

#include <vector>
#include <map>
#include <string>
#include <set>

namespace RtiDriver {

   typedef std::vector<char> VariableLengthData;

   class FederateHandle;

   typedef std::map<std::wstring, VariableLengthData> NameValueMap;
   typedef std::set<std::wstring> NameSet;
   typedef std::set<FederateHandle*> FederateHandleSet;

   typedef struct Range_s {
      unsigned int   lowerBound;
      unsigned int   upperBound;

      Range_s(unsigned int lower, unsigned int upper) : lowerBound(lower), upperBound(upper) {}
      Range_s() : lowerBound(0), upperBound(0) {}
   } Range;

   class Region;

   typedef std::set<Region*> RegionSet;
   typedef std::map<std::wstring, RegionSet> NameRegionsMap;
   typedef std::map<std::wstring, Range> NameRangeMap;

   enum TimeRepresentation {
      NONE, INTEGER64, FLOAT64
   };

   typedef struct LogicalTime_s {
      union {
          long long   integer64;
          double      float64;
      };
      TimeRepresentation representation;

      LogicalTime_s(long long val) : integer64(val), representation(INTEGER64) {}
      LogicalTime_s(double val) : float64(val), representation(FLOAT64) {}
      LogicalTime_s() : integer64(-1), representation(NONE) {}
   } LogicalTime;

   enum OrderType {
      RECEIVE,
      TIMESTAMP
   };

   enum SynchronizationPointFailureReason {
      SYNCHRONIZATION_POINT_LABEL_NOT_UNIQUE,
      SYNCHRONIZATION_SET_MEMBER_NOT_JOINED,
      UNKNOWN
   };

   enum RestoreFailureReason {
      RTI_UNABLE_TO_RESTORE,
      FEDERATE_REPORTED_FAILURE_DURING_RESTORE,
      FEDERATE_RESIGNED_DURING_RESTORE,
      RTI_DETECTED_FAILURE_DURING_RESTORE,
      RESTORE_ABORTED,
      UNKNOWN_RESTORE_FAILURE
   };


   enum SaveFailureReason {
      RTI_UNABLE_TO_SAVE,
      FEDERATE_REPORTED_FAILURE_DURING_SAVE,
      FEDERATE_RESIGNED_DURING_SAVE,
      RTI_DETECTED_FAILURE_DURING_SAVE,
      SAVE_TIME_CANNOT_BE_HONORED,
      SAVE_ABORTED,
      UNKNOWN_SAVE_FAILURE
   };

   enum ResignAction {
      UNCONDITIONALLY_DIVEST_ATTRIBUTES,
      DELETE_OBJECTS,
      CANCEL_PENDING_OWNERSHIP_ACQUISITIONS,
      DELETE_OBJECTS_THEN_DIVEST,
      CANCEL_THEN_DELETE_THEN_DIVEST,
      NO_ACTION
   };

   enum HlaVersion {
      HLA_13,
      HLA_1516,
      HLA_EVOLVED,
      HLA_4,
      ANY,
      HLA_VERSION_NONE  // Used by DIS profile
   };
}
#endif
