/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef PITCH_LIBSETTINGS_H
#define PITCH_LIBSETTINGS_H

#if defined(_WIN32)
   #ifdef BUILDING_RTIDRIVER
      #define RTIDRIVERDLL_API __declspec(dllexport)
   #else
      #define RTIDRIVERDLL_API __declspec(dllimport)
   #endif
#else
   #define RTIDRIVERDLL_API
#endif

#endif
