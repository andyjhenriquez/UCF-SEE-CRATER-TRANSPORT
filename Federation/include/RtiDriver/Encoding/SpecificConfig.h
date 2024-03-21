/***********************************************************************
   The IEEE hereby grants a general, royalty-free license to copy, distribute,
   display and make derivative works from this material, for all purposes,
   provided that any use of the material contains the following
   attribution: "Reprinted with permission from IEEE 1516.1(TM)-2009".
   Should you require additional information, contact the Manager, Standards
   Intellectual Property, IEEE Standards Association (stds-ipr@ieee.org).
***********************************************************************/
/***********************************************************************
   IEEE 1516.1 High Level Architecture Interface Specification C++ API
   File: RTI/SpecificConfig.h
***********************************************************************/

// Purpose: This file contains definitions that are used to isolate
// platform-specific elements of the API.  It is not implementation-specific.

#ifndef DS_DRIVER_RTI_SpecificConfig_h
#define DS_DRIVER_RTI_SpecificConfig_h

#if defined(_WIN32)
#if defined(_MSC_VER) //&& defined(RTI_DISABLE_WARNINGS)
// disable warning about truncating template instantiation symbol names
#pragma warning(disable: 4786)
// disable warning about exceptions not being part of a method's signature
#pragma warning(disable: 4290)
// disable warnings about a "dllexport" class using a regular class
#pragma warning(disable: 4251)
#endif
//
// On Windows, BUILDING_RTIDRIVER should be defined only when compiling
// the RTI DLL (i.e. by RTI developers).

#if defined(BUILDING_RTIDRIVER)
// define the proper qualifiers to import/export symbols from/to DLL
   #define RTIDRIVER_EXPORT __declspec(dllexport)
#else // !BUILDING_RTI
   #define RTIDRIVER_EXPORT __declspec(dllimport)
#endif // BUILDING_RTI

#else // !_WIN32
// no special qualfifers are necessary on non-WIN32 platforms
#define RTIDRIVER_EXPORT
#endif

#endif // DS_DRIVER_RTI_SpecificConfig_h
