/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAFEDERATEID_H
#define DEVELOPER_STUDIO_HLAFEDERATEID_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <vector>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>     

namespace LunarSimulation {

  /**
   * A HlaFederateId is a unique identifier for a federate
   */
   class HlaFederateId : private LunarSimulation::noncopyable {
      public:
      /**
      * True if this federate id has an encoded federate handle available
      *
      * @return true if an encoded federate handle is available
      */
      LIBAPI virtual bool hasEncodedHlaFederateHandle() = 0;

     /**
      * Get the encoded <code>HLA federate handle</code> for this federate id.
      *
      * @return encoded federate handle
      *
      * @throws HlaValueNotSetException if the encoded federate handle is unavailable
      */
      LIBAPI virtual std::vector<char> getEncodedHlaFederateHandle() THROW_SPEC (HlaValueNotSetException) = 0;

     /**
      * True if this federate id has a federate name available
      *
      * @return true if a federate name is available
      */
      LIBAPI virtual bool hasFederateName() = 0;

     /**
      * Get the name of the federate for this federate handle
      *
      * @return name of the federate
      *
      * @throws HlaValueNotSetException if the federate name is unavailable
      */
      LIBAPI virtual std::wstring getFederateName() THROW_SPEC (HlaValueNotSetException) = 0;

      LIBAPI virtual ~HlaFederateId() {}
   };
}
#endif
