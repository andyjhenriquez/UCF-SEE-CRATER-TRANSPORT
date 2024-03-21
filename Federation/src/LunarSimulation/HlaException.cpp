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

#include <LunarSimulation/HlaException.h>

#include "StringUtil.h"

using namespace LunarSimulation;

const char* HlaException::what() const NON_THROWING_SPEC {
   return _what.c_str();
}

std::wstring HlaException::what_w() const NON_THROWING_SPEC {
   return StringUtil::convert(_what);
}

HlaDecodeException::HlaDecodeException(const char* message, const bool includeData, const std::vector<char> &in) :
   HlaException(std::string("HlaDecodeException") + ": " + std::string(message) + (includeData ? ", data: " + StringUtil::toHexString(in) : ""))
{}

HlaDecodeException::HlaDecodeException(std::wstring message, const bool includeData, const std::vector<char> &in) :
   HlaException(std::string("HlaDecodeException") + ": " + StringUtil::convert(message) + (includeData ? ", data: " + StringUtil::toHexString(in) : ""))
{}


#define DEVSTUDIO_EXCEPTION_IMPL(A)                                               \
   A::A(const char* message) :                                                     \
      HlaException(std::string(#A) + ": " + std::string(message))            \
   {}                                                                              \
                                                                                   \
   A::A(std::wstring message) :                                                    \
      HlaException(std::string(#A) + ": " + StringUtil::convert(message))    \
   {}                                                                              \

DEVSTUDIO_EXCEPTION_IMPL(HlaAttributeNotOwnedException)
DEVSTUDIO_EXCEPTION_IMPL(HlaConnectException)
DEVSTUDIO_EXCEPTION_IMPL(HlaEncodeException)
DEVSTUDIO_EXCEPTION_IMPL(HlaFomException)
DEVSTUDIO_EXCEPTION_IMPL(HlaIllegalInstanceNameException)
DEVSTUDIO_EXCEPTION_IMPL(HlaInstanceNameInUseException)
DEVSTUDIO_EXCEPTION_IMPL(HlaInternalException)
DEVSTUDIO_EXCEPTION_IMPL(HlaNotConnectedException)
DEVSTUDIO_EXCEPTION_IMPL(HlaRtiException)
DEVSTUDIO_EXCEPTION_IMPL(HlaUpdaterReusedException)
DEVSTUDIO_EXCEPTION_IMPL(HlaValueNotSetException)
DEVSTUDIO_EXCEPTION_IMPL(HlaObjectInstanceIsRemovedException)
DEVSTUDIO_EXCEPTION_IMPL(HlaFederateOwnsAttributeException)
DEVSTUDIO_EXCEPTION_IMPL(HlaInTimeAdvancingStateException)
DEVSTUDIO_EXCEPTION_IMPL(HlaInvalidLicenseException)
DEVSTUDIO_EXCEPTION_IMPL(HlaInvalidLogicalTimeException)
DEVSTUDIO_EXCEPTION_IMPL(HlaSaveInProgressException)
DEVSTUDIO_EXCEPTION_IMPL(HlaRestoreInProgressException)
DEVSTUDIO_EXCEPTION_IMPL(HlaSaveFederateException)
DEVSTUDIO_EXCEPTION_IMPL(HlaRestoreFederateException)
DEVSTUDIO_EXCEPTION_IMPL(HlaInvalidInterestException)
DEVSTUDIO_EXCEPTION_IMPL(HlaNormalizerException)
DEVSTUDIO_EXCEPTION_IMPL(HlaAttributeAlreadyOwnedException)
DEVSTUDIO_EXCEPTION_IMPL(HlaFederateNotAcquiringAttributeException)
DEVSTUDIO_EXCEPTION_IMPL(HlaIncompatibleHlaVersionException)
