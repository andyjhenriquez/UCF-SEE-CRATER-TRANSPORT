/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include <type_traits>

#include <LunarSimulation/datatypes/ExecutionMode.h>

namespace LunarSimulation {

    bool LunarSimulation::ExecutionMode::isValid(const LunarSimulation::ExecutionMode::ExecutionMode& data) {
        switch (data) {
            case EXEC_MODE_UNINITIALIZED:
                return true;
            case EXEC_MODE_INITIALIZING:
                return true;
            case EXEC_MODE_RUNNING:
                return true;
            case EXEC_MODE_FREEZE:
                return true;
            case EXEC_MODE_SHUTDOWN:
                return true;
            default:
                return false;
        }
    }

    std::wostream  & operator << (std::wostream& ws, const LunarSimulation::ExecutionMode::ExecutionMode& data) {
        auto dataT = static_cast<std::underlying_type<LunarSimulation::ExecutionMode::ExecutionMode>::type>(data);
        ws << L"<ExecutionMode:";
        if (data == ExecutionMode::EXEC_MODE_UNINITIALIZED) {
            ws << L"EXEC_MODE_UNINITIALIZED (" << dataT << L")>";
            return ws;
        }
        if (data == ExecutionMode::EXEC_MODE_INITIALIZING) {
            ws << L"EXEC_MODE_INITIALIZING (" << dataT << L")>";
            return ws;
        }
        if (data == ExecutionMode::EXEC_MODE_RUNNING) {
            ws << L"EXEC_MODE_RUNNING (" << dataT << L")>";
            return ws;
        }
        if (data == ExecutionMode::EXEC_MODE_FREEZE) {
            ws << L"EXEC_MODE_FREEZE (" << dataT << L")>";
            return ws;
        }
        if (data == ExecutionMode::EXEC_MODE_SHUTDOWN) {
            ws << L"EXEC_MODE_SHUTDOWN (" << dataT << L")>";
            return ws;
        }
        ws << L"Unknown enumerator (" << dataT << L")>";
        return ws;
    }

    std::ostream  & operator << (std::ostream& s, const LunarSimulation::ExecutionMode::ExecutionMode& data) {
        auto dataT = static_cast<std::underlying_type<LunarSimulation::ExecutionMode::ExecutionMode>::type>(data);
        s << "<ExecutionMode:";
        if (data == ExecutionMode::EXEC_MODE_UNINITIALIZED) {
            s << "EXEC_MODE_UNINITIALIZED (" << dataT << ")>";
            return s;
        }
        if (data == ExecutionMode::EXEC_MODE_INITIALIZING) {
            s << "EXEC_MODE_INITIALIZING (" << dataT << ")>";
            return s;
        }
        if (data == ExecutionMode::EXEC_MODE_RUNNING) {
            s << "EXEC_MODE_RUNNING (" << dataT << ")>";
            return s;
        }
        if (data == ExecutionMode::EXEC_MODE_FREEZE) {
            s << "EXEC_MODE_FREEZE (" << dataT << ")>";
            return s;
        }
        if (data == ExecutionMode::EXEC_MODE_SHUTDOWN) {
            s << "EXEC_MODE_SHUTDOWN (" << dataT << ")>";
            return s;
        }
        s << "Unknown enumerator (" << dataT << ")>";
        return s;
    }
}

