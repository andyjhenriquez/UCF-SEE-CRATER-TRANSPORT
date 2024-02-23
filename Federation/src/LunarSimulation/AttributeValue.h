/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_ATTRIBUTEVALUE_H
#define DEVELOPER_STUDIO_ATTRIBUTEVALUE_H

#include <memory>

#include "ImplPointers.h"
#include "HlaFederateIdImpl.h"
#include <RtiDriver/Types.h>
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

    template <class T> class AttributeValue {
    private:
        bool _hasValue;
        std::shared_ptr<T> _value;
        bool _hasEncodedValue;
        RtiDriver::VariableLengthData _encodedValue; //overrides _value if _hasEncodedValue, used for lazy decoding
        HlaTimeStampPtr _timestamp;
        bool _hasFederateId;
        HlaFederateIdImplPtr _federateId;
        HlaLogicalTimePtr _logicalTime;

    public:

        AttributeValue() :
            _hasValue(false),
            _hasEncodedValue(false),
            _hasFederateId(false)
        {
        }

        void setValue(std::shared_ptr<T> value, HlaTimeStampPtr timestamp = HlaTimeStampPtr()) {
            _hasValue = true;
            _value = value;
            _timestamp = timestamp;
        }

        void setValue(std::shared_ptr<T> value, HlaFederateIdImplPtr federateId, HlaLogicalTimePtr logicalTime, HlaTimeStampPtr timestamp = HlaTimeStampPtr()) {
            _hasValue = true;
            _value = value;
            _hasEncodedValue = false;
            _encodedValue.clear();
            _timestamp = timestamp;
            _logicalTime = logicalTime;
            if (federateId->hasHandle()) {
                _hasFederateId = true;
                _federateId = federateId;
            }
        }

        void setEncodedValue(const RtiDriver::VariableLengthData &encodedValue, HlaFederateIdImplPtr federateId, HlaLogicalTimePtr logicalTime, HlaTimeStampPtr timestamp = HlaTimeStampPtr()) {
            _hasEncodedValue = true;
            _encodedValue = encodedValue;
            _timestamp = timestamp;
            _logicalTime = logicalTime;
            if (federateId->hasHandle()) {
                _hasFederateId = true;
                _federateId = federateId;
            }
        }

        void clearEncodedValue() {
           _hasEncodedValue = false;
           _encodedValue.clear();
        }

        void setDecodedValue(std::shared_ptr<T> value) {
            _hasValue = true;
            _value = value;
            _hasEncodedValue = false;
            _encodedValue.clear();
        }

        bool hasValue() const {
            return _hasValue;
        }

        std::shared_ptr<T> getValue() const {
            return _value;
        }

        bool hasEncodedValue() const {
            return _hasEncodedValue;
        }

        RtiDriver::VariableLengthData const& getEncodedValue() const {
            return _encodedValue;
        }

        LunarSimulation::HlaTimeStamped<T> getTimestampedValue() const {
            return LunarSimulation::HlaTimeStamped<T>(*_value, _timestamp, _logicalTime);
        }

        bool hasFederateId() const {
            return _hasFederateId;
        }

        HlaFederateIdImplPtr getFederateId() const {
            return _federateId;
        }
    };
}

#endif
