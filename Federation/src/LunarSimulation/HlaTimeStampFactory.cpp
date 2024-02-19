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

#include <LunarSimulation/HlaTimeStampFactory.h>

#include <ctime>
#include <stdexcept>

#include "TimeUtility.h"
#include "StringUtil.h"

using namespace LunarSimulation;

HlaTimeStampPtr HlaTimeStampFactory::create(const RtiDriver::VariableLengthData& userSuppliedTag) {
   return create();
}

HlaTimeStampPtr HlaTimeStampFactory::create(const HlaTimeStampPtr reference, double offset) {
   return reference;
}

HlaTimeStampFactoryPtr HlaTimeStampFactory::getHlaTimeStampFactory(const std::wstring& name) {
   if (name == L"none") {
      return HlaTimeStampFactoryPtr(new EmptyTimeStampFactory());
   } 
   if (name == L"system_clock") {
      return HlaTimeStampFactoryPtr(new SystemClockTimeStampFactory());
   }
   if (name == L"rpr_relative") {
      return HlaTimeStampFactoryPtr(new RprRelativeFactory());
   }
   if (name == L"rpr_absolute") {
      return HlaTimeStampFactoryPtr(new RprAbsoluteFactory());
   }
   return HlaTimeStampFactoryPtr();
}


static const int MILLIS_PER_HOUR = 1000 * 60 * 60;
static const int MILLIS_TO_MICROS = 1000;
static const int MICROS_PER_SEC = 1000 * 1000;
static const double RPR_TIMESCALE = 3600.0 / 0x7FFFFFFF; // 3600 / (2^31 - 1) = 1.676 microseconds


static RtiDriver::VariableLengthData encodeHexString(unsigned int value) {
    static const char* DIGITS = "0123456789ABCDEF";

    RtiDriver::VariableLengthData encodedVal = RtiDriver::VariableLengthData(8);
    for (size_t i = 0, shift = (8 - 1) * 4; i < 8; i++, shift -= 4) {
        encodedVal[i] = DIGITS[(value >> shift) & 0x0F];
    }

    return encodedVal;
}


static const RtiDriver::VariableLengthData encodeRprTimestamp(double sec, bool absolute) {
    unsigned int timeSteps = static_cast<unsigned int>(sec / RPR_TIMESCALE);

    // The 31 most significant bits are used
    unsigned int rprTime = timeSteps << 1;

    if (absolute) {
        // Add 1 in the least significant bit to indicate absolute time
        rprTime++;
    }

    return encodeHexString(rprTime);
}

static int characterDigit(char c) {
    int val = (int)c;
    if ('0' <= val && val <= '9') {
        return val - '0';
    }
    if ('A' <= val && val <= 'F') {
        return (10 + val) - 'A';
    }
    if ('a' <= val && val <= 'f') {
        return (10 + val) - 'a';
    }
    throw std::invalid_argument("Unable to decodeHexString, invaldic character: " + std::string(1, c));
}

static unsigned long long decodeHexString(const RtiDriver::VariableLengthData& data) {
    unsigned long long value = 0;
    for (size_t i = 0, shift = (data.size() - 1) * 4; i < data.size(); i++, shift -= 4) {
        value += ((unsigned long long)characterDigit(data[i])) << shift;
    }
    return value;
}

static const std::pair<bool, std::pair<double, bool> > decodeRprTimestamp(RtiDriver::VariableLengthData data) {
    try {
        if (data.size() > 8) {
            data.resize(8);
        }
        unsigned long long rprTicks = decodeHexString(data);

        // Lowest bit indicates absolute time
        bool absolute = (rprTicks & 0x01) == 0x01;
        unsigned int timeSteps = static_cast<unsigned int>(rprTicks >> 1);

        double secs = timeSteps * RPR_TIMESCALE;
        return std::pair<bool, std::pair<double, bool> >(true, std::pair<double, bool>(secs, absolute));
    } catch (...) {
        return std::pair<bool, std::pair<double, bool> >(false, std::pair<double, bool>(0, false));
    }
}

static std::wstring& append(std::wstring& sb, unsigned long long value, unsigned int zeros) {
    std::wstring valueStr = StringUtil::ulonglongToWstring(value);
    size_t length = valueStr.length();
    while (length < zeros) {
        sb.append(L"0");
        zeros--;
    }
    return sb.append(valueStr);
}

static const int MICRO_PER_MILLI = 1000;
static const int MILLI_PER_SEC = 1000;
static const int SEC_PER_MIN = 60;
static const int MIN_PER_HOUR = 60;

static const std::wstring microToString(unsigned long long micros) {
    unsigned long long millis = micros / MICRO_PER_MILLI;
    unsigned long long sec = millis / MILLI_PER_SEC;
    unsigned long long min = sec / SEC_PER_MIN;
    unsigned long long hour = min / MIN_PER_HOUR;

    std::wstring sb;
    if (hour != 0) {
        sb.append(StringUtil::ulonglongToWstring(hour)).append(L":");
        append(sb, min % MIN_PER_HOUR, 2).append(L":");
    } else {
        sb.append(StringUtil::ulonglongToWstring(min % MIN_PER_HOUR)).append(L":");
    }
    append(sb, sec % SEC_PER_MIN, 2).append(L".");
    append(sb, millis % MILLI_PER_SEC, 3).append(L",");
    append(sb, micros % MICRO_PER_MILLI, 3);

    return sb;
}

RprTimeStamp::RprTimeStamp() :
    _valid(true),
    _absolute(true),
    _micros((TimeUtility::getCurrentTimeMillis() % MILLIS_PER_HOUR) * MILLIS_TO_MICROS) {
}

RprTimeStamp::RprTimeStamp(unsigned long long startupTimeMilli) :
    _valid(true),
    _absolute(false),
    _micros(((TimeUtility::getCurrentTimeMillis() - startupTimeMilli) % MILLIS_PER_HOUR) * MILLIS_TO_MICROS)  {
}

RprTimeStamp::RprTimeStamp(unsigned long long micros, bool absolute) :
    _valid(true),
    _absolute(absolute),
    _micros(micros)  {
}

RprTimeStamp::RprTimeStamp(const RtiDriver::VariableLengthData& userSuppliedTag) :
    _arrivalTime(new RprTimeStamp()) {
    if (!userSuppliedTag.empty()) {
        std::pair<bool, std::pair<double, bool> > res = decodeRprTimestamp(userSuppliedTag);
        _valid = res.first;
        _micros = (unsigned long long)(res.second.first * MICROS_PER_SEC);
        _absolute = res.second.second;
    } else {
        _valid = false;
        _micros = 0;
        _absolute = true;
    }
}

RtiDriver::VariableLengthData RprTimeStamp::getUserSuppliedTag() const {
    return _valid ? encodeRprTimestamp(static_cast<double>(_micros) / MICROS_PER_SEC, _absolute) : RtiDriver::VariableLengthData();
}

double RprTimeStamp::secondsSince(HlaTimeStampPtr timestamp) const {
    return 1.0E-6 * static_cast<double>(_micros - timestamp->getValue());
}

std::wstring RprTimeStamp::toString() const {
    return (_absolute ? L"": L"~ ") + microToString(_micros);
}

RprRelativeFactory::RprRelativeFactory() :
    _startupTime(TimeUtility::getCurrentTimeMillis()) {
}

SystemClockTimeStamp::SystemClockTimeStamp() :
      _value(TimeUtility::getCurrentTimeMillis()) {
}

std::wstring SystemClockTimeStamp::toString() const {
   time_t sec = static_cast<time_t>(_value / MILLI_PER_SEC);
   char str[80];
   strftime(str, 80, "%Y-%m-%d %H:%M:%S", gmtime(&sec));

   std::wstring sb = StringUtil::convert(std::string(str));
   sb.append(L".");
   append(sb, _value % MILLI_PER_SEC, 3);
   return sb;
}

double SystemClockTimeStamp::secondsSince(HlaTimeStampPtr timestamp) const {
   return 0.001 * static_cast<double>(_value - timestamp->getValue());
}

HlaTimeStampPtr SystemClockTimeStampFactory::create() {
   return HlaTimeStampPtr(new SystemClockTimeStamp());
}
