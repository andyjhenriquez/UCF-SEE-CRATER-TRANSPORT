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

#include "AngularAccelerationVectorEncoder.h"

#include "BaseEncoder.h"
#include <LunarSimulation/HlaException.h>
#include "../StringUtil.h"

using namespace LunarSimulation;
using namespace EncodingHelpers;

AngularAccelerationVectorEncoder::AngularAccelerationVectorEncoder() :
    _encoder(EncodingHelpers::HLAfloat64LE(), 3)
    , _var0Encoder(BaseEncoder::createAngularAcceleration())
    , _var1Encoder(BaseEncoder::createAngularAcceleration())
    , _var2Encoder(BaseEncoder::createAngularAcceleration())
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
}

AngularAccelerationVectorEncoder::AngularAccelerationVectorEncoder(const AngularAccelerationVectorEncoder & rhs) :
    _encoder(EncodingHelpers::HLAfloat64LE(), 3)
    , _var0Encoder(rhs._var0Encoder)
    , _var1Encoder(rhs._var1Encoder)
    , _var2Encoder(rhs._var2Encoder)
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
}

static size_t verifyLength(const std::vector<double >& v) THROW_SPEC (EncodingHelpers::EncoderException) {
    if (v.size() != 3) {
        throw EncodingHelpers::EncoderException(L"Wrong size of vector in AngularAccelerationVectorEncoder! Expected size: 3. Size of current vector: " + StringUtil::sizeToWstring(v.size()));
    }
    return v.size();
}

AngularAccelerationVectorEncoder::AngularAccelerationVectorEncoder(const std::vector<double >& v) THROW_SPEC (EncodingHelpers::EncoderException) :
    _encoder(EncodingHelpers::HLAfloat64LE(), verifyLength(v))
    , _var0Encoder(BaseEncoder::createAngularAcceleration(v[0]))
    , _var1Encoder(BaseEncoder::createAngularAcceleration(v[1]))
    , _var2Encoder(BaseEncoder::createAngularAcceleration(v[2]))
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
}

AngularAccelerationVectorEncoder::operator std::vector<double > () const {
    std::vector<double > res;
    for (size_t i = 0; i < _encoder.size(); i++) {
        res.push_back(dynamic_cast<const EncodingHelpers::HLAfloat64LE&>(_encoder[i]));
    }
    return res;
}

void AngularAccelerationVectorEncoder::set(const std::vector<double > & v) THROW_SPEC (EncodingHelpers::EncoderException) {
    verifyLength(v);
    _var0Encoder.set(v[0]);
    _var1Encoder.set(v[1]);
    _var2Encoder.set(v[2]);
}

EncodingHelpers::DataElement* AngularAccelerationVectorEncoder::clone () const {
    return new AngularAccelerationVectorEncoder(*this);
}

