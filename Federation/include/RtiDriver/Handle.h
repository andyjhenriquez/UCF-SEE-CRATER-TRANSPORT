/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_HANDLE
#define DS_DRIVER_HANDLE

#include <string>
#include "Types.h"

namespace RtiDriver {

   /**
    * Representation of a HLA handle, the class is immutable.
    */
   class Handle {
   public:
      /**
       * Returns a pointer to the encoded representation of the handle.
       * Ownership of the memory is handled by the Handle object. The
       * pointer is valid as long as the underlying Handle object is.
       */
      virtual const VariableLengthData getEncodedHandle() const = 0;

      virtual bool operator<(const Handle& rhs) const = 0;

      /**
       * String representation of the handle, only to be used for
       * debugging purposes.
       */
      virtual std::wstring toString() const = 0;

      virtual ~Handle() {}
   };
}
#endif
