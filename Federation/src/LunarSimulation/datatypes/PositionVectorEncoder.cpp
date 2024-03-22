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

#include "PositionVectorEncoder.h"

#include "BaseEncoder.h"
#include <LunarSimulation/HlaException.h>
#include "../StringUtil.h"

using namespace LunarSimulation;
using namespace EncodingHelpers;

PositionVectorEncoder::PositionVectorEncoder() :
    _encoder(EncodingHelpers::HLAfloat64LE(), 3)
    , _var0Encoder(BaseEncoder::createLength())
    , _var1Encoder(BaseEncoder::createLength())
    , _var2Encoder(BaseEncoder::createLength())
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
}

PositionVectorEncoder::PositionVectorEncoder(const PositionVectorEncoder & rhs) :
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
        throw EncodingHelpers::EncoderException(L"Wrong size of vector in PositionVectorEncoder! Expected size: 3. Size of current vector: " + StringUtil::sizeToWstring(v.size()));
    }
    return v.size();
}

PositionVectorEncoder::PositionVectorEncoder(const std::vector<double >& v) THROW_SPEC (EncodingHelpers::EncoderException) :
    _encoder(EncodingHelpers::HLAfloat64LE(), verifyLength(v))
    , _var0Encoder(BaseEncoder::createLength(v[0]))
    , _var1Encoder(BaseEncoder::createLength(v[1]))
    , _var2Encoder(BaseEncoder::createLength(v[2]))
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
}

PositionVectorEncoder::operator std::vector<double > () const {
    std::vector<double > res;
    for (size_t i = 0; i < _encoder.size(); i++) {
        res.push_back(dynamic_cast<const EncodingHelpers::HLAfloat64LE&>(_encoder[i]));
    }
    return res;
}

void PositionVectorEncoder::set(const std::vector<double > & v) THROW_SPEC (EncodingHelpers::EncoderException) {
    verifyLength(v);
    _var0Encoder.set(v[0]);
    _var1Encoder.set(v[1]);
    _var2Encoder.set(v[2]);
}

EncodingHelpers::DataElement* PositionVectorEncoder::clone () const {
    return new PositionVectorEncoder(*this);
}

