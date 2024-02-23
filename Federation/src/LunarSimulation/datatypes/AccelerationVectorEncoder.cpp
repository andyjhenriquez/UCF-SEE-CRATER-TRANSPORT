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

#include "AccelerationVectorEncoder.h"

#include "BaseEncoder.h"
#include <LunarSimulation/HlaException.h>
#include "../StringUtil.h"

using namespace LunarSimulation;
using namespace EncodingHelpers;

AccelerationVectorEncoder::AccelerationVectorEncoder() :
    _encoder(EncodingHelpers::HLAfloat64LE(), 3)
    , _var0Encoder(BaseEncoder::createAcceleration())
    , _var1Encoder(BaseEncoder::createAcceleration())
    , _var2Encoder(BaseEncoder::createAcceleration())
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
}

AccelerationVectorEncoder::AccelerationVectorEncoder(const AccelerationVectorEncoder & rhs) :
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
        throw EncodingHelpers::EncoderException(L"Wrong size of vector in AccelerationVectorEncoder! Expected size: 3. Size of current vector: " + StringUtil::sizeToWstring(v.size()));
    }
    return v.size();
}

AccelerationVectorEncoder::AccelerationVectorEncoder(const std::vector<double >& v) THROW_SPEC (EncodingHelpers::EncoderException) :
    _encoder(EncodingHelpers::HLAfloat64LE(), verifyLength(v))
    , _var0Encoder(BaseEncoder::createAcceleration(v[0]))
    , _var1Encoder(BaseEncoder::createAcceleration(v[1]))
    , _var2Encoder(BaseEncoder::createAcceleration(v[2]))
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
}

AccelerationVectorEncoder::operator std::vector<double > () const {
    std::vector<double > res;
    for (size_t i = 0; i < _encoder.size(); i++) {
        res.push_back(dynamic_cast<const EncodingHelpers::HLAfloat64LE&>(_encoder[i]));
    }
    return res;
}

void AccelerationVectorEncoder::set(const std::vector<double > & v) THROW_SPEC (EncodingHelpers::EncoderException) {
    verifyLength(v);
    _var0Encoder.set(v[0]);
    _var1Encoder.set(v[1]);
    _var2Encoder.set(v[2]);
}

EncodingHelpers::DataElement* AccelerationVectorEncoder::clone () const {
    return new AccelerationVectorEncoder(*this);
}

