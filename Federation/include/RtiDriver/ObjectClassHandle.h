/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_OBJECT_CLASS_HANDLE
#define DS_DRIVER_OBJECT_CLASS_HANDLE

#include "Handle.h"

namespace RtiDriver {

   class ObjectClassHandle : public Handle {
   public:
      virtual ObjectClassHandle* clone() const = 0;

   };
}
#endif
