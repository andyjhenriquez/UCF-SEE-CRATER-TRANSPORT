/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_OBJECT_INSTANCE_HANDLE
#define DS_DRIVER_OBJECT_INSTANCE_HANDLE

#include "Handle.h"
#include "ObjectClassHandle.h"

#include <memory>

namespace RtiDriver {
   class ObjectInstanceHandle : public Handle {
   public:
      virtual ObjectClassHandle* getObjectClassHandle() const = 0;
      virtual std::wstring getObjectInstanceName() const = 0;
      virtual ObjectInstanceHandle * clone() const = 0;
   };
}
#endif
