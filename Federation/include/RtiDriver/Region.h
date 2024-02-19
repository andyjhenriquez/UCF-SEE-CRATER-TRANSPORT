/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_REGION
#define DS_DRIVER_REGION

#include <string>
#include "Types.h"

namespace RtiDriver {

   /**
    * Representation of a HLA Region.
    *
    * DDM is currently only supported by the HLA Evolved Profile, B!
    */
   class Region {
   public:
      virtual bool operator<(const Region& rhs) const = 0;

      /**
       * String representation of the handle, only to be used for
       * debugging purposes.
       */
      virtual std::wstring toString() const = 0;

      virtual ~Region() {}
   };
}
#endif
