/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_FEDERATE_HANDLE
#define DS_DRIVER_FEDERATE_HANDLE

#include "Handle.h"

namespace RtiDriver {
   class FederateHandle : public Handle {
   public:
      // Only valid for HLA Evolved
      virtual std::wstring getFederateName() const = 0;

      virtual FederateHandle* clone() const = 0;
   };
}
#endif
