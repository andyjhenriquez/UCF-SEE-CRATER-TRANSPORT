/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_MTRMODE_H
#define DEVELOPER_STUDIO_DATATYPES_MTRMODE_H

#include <iostream>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
    namespace MTRMode {
        /**
        * Implementation of the <code>MTRMode</code> data type from the FOM.
        * <br>Description from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
        */
        enum MTRMode {
            /** <code>MTR_GOTO_RUN</code> (with ordinal 2) */
            MTR_GOTO_RUN = 2,
            /** <code>MTR_GOTO_FREEZE</code> (with ordinal 3) */
            MTR_GOTO_FREEZE = 3,
            /** <code>MTR_GOTO_SHUTDOWN</code> (with ordinal 4) */
            MTR_GOTO_SHUTDOWN = 4
        };

        /**
        * Returns true if the enum is valid, i.e. if it is defined in the FOM.
        *
        * It is possible to explicitly convert an integer value to an enumeration. However, if the integer value
        * does not exist among the enumeration values the resulting enum value is undefined. This function will
        * only return true for defined values.
        *
        * To cast an integer to MTRMode: static_cast<LunarSimulation::MTRMode::MTRMode>(i)
        */
        LIBAPI bool isValid(const MTRMode& data);
    }

    LIBAPI std::wostream & operator << (std::wostream &, LunarSimulation::MTRMode::MTRMode const &);
    LIBAPI std::ostream & operator << (std::ostream &, LunarSimulation::MTRMode::MTRMode const &);
}


#endif
