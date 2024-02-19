/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_INTERACTION_CLASS_HANDLE
#define DS_DRIVER_INTERACTION_CLASS_HANDLE

#include "Handle.h"

namespace RtiDriver {
   class InteractionClassHandle : public Handle {
   public:
      virtual InteractionClassHandle* clone() const = 0;
   };
}
#endif
