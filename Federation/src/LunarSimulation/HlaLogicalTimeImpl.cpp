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
#include "HlaLogicalTimeImpl.h"

#include <sstream>
#include "StringUtil.h"

using namespace LunarSimulation;

const HlaLogicalTimeImplPtr HlaLogicalTimeImpl::_INVALID = HlaLogicalTimeImplPtr(new HlaLogicalTimeImpl());
const HlaLogicalTimeImplPtr HlaLogicalTimeImpl::_INITIAL = create(0);

HlaLogicalTimeImpl::HlaLogicalTimeImpl(long long value, OrderType receivedOrderType) :
    _valid(true), _value(value), _receivedOrderType(receivedOrderType) {
}

HlaLogicalTimeImpl::HlaLogicalTimeImpl() :
    _valid(false), _value(-1), _receivedOrderType(NONE) {
}

HlaLogicalTimeImplPtr HlaLogicalTimeImpl::createReceived(long long value, bool tso) {
    return HlaLogicalTimeImplPtr(new HlaLogicalTimeImpl(value, tso ? TIME_STAMP_ORDER : RECEIVE_ORDER));
}

HlaLogicalTimeImplPtr HlaLogicalTimeImpl::create(long long value) {
    return HlaLogicalTimeImplPtr(new HlaLogicalTimeImpl(value, NONE));
}

HlaLogicalTimeImplPtr HlaLogicalTimeImpl::getInvalid() {
    return _INVALID;
}

HlaLogicalTimeImplPtr HlaLogicalTimeImpl::getInitial() {
    return _INITIAL;
}

bool HlaLogicalTimeImpl::isValid() const {
    return _valid;
}

long long HlaLogicalTimeImpl::getValue() const {
    return _value;
}

HlaLogicalTime::OrderType HlaLogicalTimeImpl::getReceivedOrderType() const {
    return _receivedOrderType;
}

bool HlaLogicalTimeImpl::wasReceivedInTimeStampOrder() const {
    return _receivedOrderType == TIME_STAMP_ORDER;
}

HlaLogicalTimePtr HlaLogicalTimeImpl::add(long long addend) const {
    if (isValid()) {
       return create(_value + addend);
    } else {
       return getInvalid();
    }
}

std::wstring HlaLogicalTimeImpl::toString() const {
    if (!isValid()) {
       return L"HlaLogicalTime<INVALID>";
    }

    std::wstringstream ss;
    std::wstring orderTypeString = L">";
    if (_receivedOrderType == TIME_STAMP_ORDER) {
        orderTypeString = L", TSO>";
    } else if (_receivedOrderType == RECEIVE_ORDER) {
        orderTypeString = L", RO>";
    }

    ss << L"HlaLogicalTime<" << _value << orderTypeString;
    return ss.str();
}
