/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DS_DRIVER_MAIN
#define DS_DRIVER_MAIN

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BUILDING_RTIDRIVER
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// RTIDRIVERDLL_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#if defined(_WIN32)
   #ifdef BUILDING_RTIDRIVER
      #define RTIDRIVERDLL_API __declspec(dllexport)
   #else
      #define RTIDRIVERDLL_API __declspec(dllimport)
   #endif
#else
   #define RTIDRIVERDLL_API
#endif

#include "RtiAmbassador.h"
#include "Detective.h"

#include <memory>


namespace RtiDriver {

   enum Profile { A, B, C, D, E, F, UNSPECIFIED };

   RTIDRIVERDLL_API std::string getLicenseInfo();

   RTIDRIVERDLL_API void saveLicense(std::string license);

   /*
    * Returned pointer owned by caller.
    */
   RTIDRIVERDLL_API RtiDriver::RtiAmbassador* getRtiAmbassador(Profile profile = UNSPECIFIED,
                                                               std::wstring localSettingsDesignator = L"",
                                                               std::wstring host = L"",
                                                               int port = -1)
      RTI_DRIVER_THROW_SPEC(RtiDriver::RTIinternalError, RtiDriver::ConnectionFailed, RtiDriver::InvalidLicense);

   /*
    * Multiple Detectives can be installer like this:
    *
    * rtiAmbassador = RtiDriver::installDetective(firstDetective, RtiDriver::installDetective(secondDetective, rtiAmbassador));
    *
    * Takes ownership of detective and rtiAmbassador pointers, returned pointer owned by caller.
    */
   RTIDRIVERDLL_API RtiDriver::RtiAmbassador* installDetective(RtiDriver::Detective* detective, RtiDriver::RtiAmbassador* rtiAmbassador);
}

#endif
