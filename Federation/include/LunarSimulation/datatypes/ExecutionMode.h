/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_EXECUTIONMODE_H
#define DEVELOPER_STUDIO_DATATYPES_EXECUTIONMODE_H

#include <iostream>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
    namespace ExecutionMode {
        /**
        * Implementation of the <code>ExecutionMode</code> data type from the FOM.
        * <br>Description from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
        */
        enum ExecutionMode {
            /** <code>EXEC_MODE_UNINITIALIZED</code> (with ordinal 0) */
            EXEC_MODE_UNINITIALIZED = 0,
            /** <code>EXEC_MODE_INITIALIZING</code> (with ordinal 1) */
            EXEC_MODE_INITIALIZING = 1,
            /** <code>EXEC_MODE_RUNNING</code> (with ordinal 2) */
            EXEC_MODE_RUNNING = 2,
            /** <code>EXEC_MODE_FREEZE</code> (with ordinal 3) */
            EXEC_MODE_FREEZE = 3,
            /** <code>EXEC_MODE_SHUTDOWN</code> (with ordinal 4) */
            EXEC_MODE_SHUTDOWN = 4
        };

        /**
        * Returns true if the enum is valid, i.e. if it is defined in the FOM.
        *
        * It is possible to explicitly convert an integer value to an enumeration. However, if the integer value
        * does not exist among the enumeration values the resulting enum value is undefined. This function will
        * only return true for defined values.
        *
        * To cast an integer to ExecutionMode: static_cast<LunarSimulation::ExecutionMode::ExecutionMode>(i)
        */
        LIBAPI bool isValid(const ExecutionMode& data);
    }

    LIBAPI std::wostream & operator << (std::wostream &, LunarSimulation::ExecutionMode::ExecutionMode const &);
    LIBAPI std::ostream & operator << (std::ostream &, LunarSimulation::ExecutionMode::ExecutionMode const &);
}


#endif
