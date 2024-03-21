/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_DETECTIVE
#define DS_DRIVER_DETECTIVE

#include "RtiAmbassador.h"
#include "FederateAmbassador.h"

#include <memory>


namespace RtiDriver {

   class Detective : public RtiDriver::RtiAmbassador , public RtiDriver::FederateAmbassador {
   public:
      virtual ~Detective() {}

      //Called when the Detective is installed, takes ownership of pointer
      virtual void setRtiAmbassador(RtiDriver::RtiAmbassador* rtiAmbassador) = 0;

      //Called just before joinFederationExecution, does not take ownership of pointer
      virtual void setFederateAmbassador(RtiDriver::FederateAmbassador* federateAmbassador) = 0;
   };
}

#endif
