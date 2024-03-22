/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include <type_traits>

#include <LunarSimulation/datatypes/MTRMode.h>

namespace LunarSimulation {

    bool LunarSimulation::MTRMode::isValid(const LunarSimulation::MTRMode::MTRMode& data) {
        switch (data) {
            case MTR_GOTO_RUN:
                return true;
            case MTR_GOTO_FREEZE:
                return true;
            case MTR_GOTO_SHUTDOWN:
                return true;
            default:
                return false;
        }
    }

    std::wostream  & operator << (std::wostream& ws, const LunarSimulation::MTRMode::MTRMode& data) {
        auto dataT = static_cast<std::underlying_type<LunarSimulation::MTRMode::MTRMode>::type>(data);
        ws << L"<MTRMode:";
        if (data == MTRMode::MTR_GOTO_RUN) {
            ws << L"MTR_GOTO_RUN (" << dataT << L")>";
            return ws;
        }
        if (data == MTRMode::MTR_GOTO_FREEZE) {
            ws << L"MTR_GOTO_FREEZE (" << dataT << L")>";
            return ws;
        }
        if (data == MTRMode::MTR_GOTO_SHUTDOWN) {
            ws << L"MTR_GOTO_SHUTDOWN (" << dataT << L")>";
            return ws;
        }
        ws << L"Unknown enumerator (" << dataT << L")>";
        return ws;
    }

    std::ostream  & operator << (std::ostream& s, const LunarSimulation::MTRMode::MTRMode& data) {
        auto dataT = static_cast<std::underlying_type<LunarSimulation::MTRMode::MTRMode>::type>(data);
        s << "<MTRMode:";
        if (data == MTRMode::MTR_GOTO_RUN) {
            s << "MTR_GOTO_RUN (" << dataT << ")>";
            return s;
        }
        if (data == MTRMode::MTR_GOTO_FREEZE) {
            s << "MTR_GOTO_FREEZE (" << dataT << ")>";
            return s;
        }
        if (data == MTRMode::MTR_GOTO_SHUTDOWN) {
            s << "MTR_GOTO_SHUTDOWN (" << dataT << ")>";
            return s;
        }
        s << "Unknown enumerator (" << dataT << ")>";
        return s;
    }
}

