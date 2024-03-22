/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAFEDERATEIDIMPL_H
#define DEVELOPER_STUDIO_HLAFEDERATEIDIMPL_H

#include <LunarSimulation/HlaFederateId.h>
#include <memory>
#include <RtiDriver/FederateHandle.h>    

namespace LunarSimulation {
   class HlaFederateIdImpl : public HlaFederateId {
      std::unique_ptr<RtiDriver::FederateHandle> _federateHandle;
      bool _hasHandle;

   public:
      explicit HlaFederateIdImpl(const RtiDriver::FederateHandle& federateHandle);
      HlaFederateIdImpl();
      bool operator==(const HlaFederateIdImpl& other) const;
      bool operator!=(const HlaFederateIdImpl& other) const;

      bool hasHandle();

      bool hasEncodedHlaFederateHandle();

      std::vector<char> getEncodedHlaFederateHandle() THROW_SPEC (HlaValueNotSetException);

      bool hasFederateName();

      std::wstring getFederateName() THROW_SPEC (HlaValueNotSetException);
   };
}
#endif
