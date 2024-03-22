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
#include "HlaFederateIdImpl.h"

using namespace LunarSimulation;
using namespace std;

HlaFederateIdImpl::HlaFederateIdImpl(const RtiDriver::FederateHandle& federateHandle) {
    _federateHandle = std::unique_ptr<RtiDriver::FederateHandle>(federateHandle.clone());
    _hasHandle = true;
}

HlaFederateIdImpl::HlaFederateIdImpl() {    
    _hasHandle = false;
}

template <typename  T> bool equalByLessThen(const T& a, const T& b) {
    return !(a < b) && !(b < a);
}

bool HlaFederateIdImpl::operator==(const HlaFederateIdImpl& other) const {
    return _hasHandle && other._hasHandle ? equalByLessThen(*_federateHandle, *other._federateHandle) : _hasHandle == other._hasHandle;
}

bool HlaFederateIdImpl::operator!=(const HlaFederateIdImpl& other) const {
    return !(*this == other);
}

bool HlaFederateIdImpl::hasHandle() {
    return _hasHandle;
}

bool HlaFederateIdImpl::hasEncodedHlaFederateHandle() {
    return _hasHandle && _federateHandle->getEncodedHandle().size() != 0;
}

vector<char> HlaFederateIdImpl::getEncodedHlaFederateHandle() THROW_SPEC (HlaValueNotSetException) {
    if (hasEncodedHlaFederateHandle()) {
        return _federateHandle->getEncodedHandle();
    }
    throw HlaValueNotSetException("Encoded HlaFederateHandle is not available");
}

bool HlaFederateIdImpl::hasFederateName() {
    return _hasHandle && !_federateHandle->getFederateName().empty();
}

wstring HlaFederateIdImpl::getFederateName() THROW_SPEC (HlaValueNotSetException) {
    if (hasFederateName()) {
        return _federateHandle->getFederateName();
    }
    throw HlaValueNotSetException("Federate name is not available");
}
