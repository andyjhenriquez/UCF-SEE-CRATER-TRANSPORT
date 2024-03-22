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

#include "TimeUtility.h"

#include <string>

#include <thread>

using namespace LunarSimulation;

static const TimeUtility::time_point epok = std::chrono::time_point_cast<TimeUtility::duration>(std::chrono::system_clock::from_time_t(0));

TimeUtility::time_point TimeUtility::getCurrentTime() {
    return std::chrono::time_point_cast<TimeUtility::duration>(std::chrono::system_clock::now());
}

unsigned long long TimeUtility::asMillis(const TimeUtility::time_point& time) {
    std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(time - epok);
    return diff.count();
}

void TimeUtility::sleep(unsigned long long millis) {
    std::this_thread::sleep_for(millisAsDuration(millis));
}

TimeUtility::time_point TimeUtility::addMillisToCurrentTime(unsigned long long millis) {
    return getCurrentTime() + millisAsDuration(millis);
}

TimeUtility::duration TimeUtility::millisAsDuration(unsigned long long millis) {
    return std::chrono::duration_cast<TimeUtility::duration>(std::chrono::milliseconds(millis));
}

unsigned long long TimeUtility::getCurrentTimeMillis() {
    return asMillis(getCurrentTime());
}
