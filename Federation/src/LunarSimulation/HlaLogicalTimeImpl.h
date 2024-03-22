/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALOGICALTIMEIMPL_H
#define DEVELOPER_STUDIO_HLALOGICALTIMEIMPL_H

#include <LunarSimulation/HlaLogicalTime.h>
#include "ImplPointers.h"


namespace LunarSimulation {
   class HlaLogicalTimeImpl : public HlaLogicalTime {
    private:
        const bool _valid;
        const long long _value;
        const OrderType _receivedOrderType;

        HlaLogicalTimeImpl(long long value, OrderType receivedOrderType);
        HlaLogicalTimeImpl();

        static const HlaLogicalTimeImplPtr _INVALID;
        static const HlaLogicalTimeImplPtr _INITIAL;

    public:

        static HlaLogicalTimeImplPtr createReceived(long long value, bool tso);

        static HlaLogicalTimeImplPtr create(long long value);

        static HlaLogicalTimeImplPtr getInvalid();

        static HlaLogicalTimeImplPtr getInitial();

        virtual bool isValid() const;

        virtual long long getValue() const;

        virtual OrderType getReceivedOrderType() const;

        virtual bool wasReceivedInTimeStampOrder() const;

        virtual HlaLogicalTimePtr add(long long addend) const;

        virtual std::wstring toString() const;
    };
}
#endif
