/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_TIMEUTILITY_H
#define DEVELOPER_STUDIO_TIMEUTILITY_H

#include <chrono>

namespace LunarSimulation {

    class TimeUtility {
    public:
        typedef std::chrono::system_clock::duration duration;
        typedef std::chrono::system_clock::time_point time_point;

        static void sleep(unsigned long long millis);
        static time_point getCurrentTime();
        static time_point addMillisToCurrentTime(unsigned long long millis);
        static duration millisAsDuration(unsigned long long millis);

        /**
         * The difference, measured in milliseconds, between time and midnight, January 1, 1970 UTC.
         */
        static unsigned long long asMillis(const time_point& time);

        static unsigned long long getCurrentTimeMillis();
    };
}
#endif
