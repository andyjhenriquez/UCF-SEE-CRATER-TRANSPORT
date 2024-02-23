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

#include "InertiaMatrixEncoder.h"

#include "BaseEncoder.h"
#include <LunarSimulation/HlaException.h>
#include "../StringUtil.h"

using namespace LunarSimulation;
using namespace EncodingHelpers;

InertiaMatrixEncoder::InertiaMatrixEncoder() :
    _encoder(EncodingHelpers::HLAfloat64LE(), 9)
    , _var0Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var1Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var2Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var3Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var4Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var5Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var6Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var7Encoder(BaseEncoder::createMassMomentOfInertia())
    , _var8Encoder(BaseEncoder::createMassMomentOfInertia())
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
    _encoder.setElementPointer(3, &_var3Encoder);
    _encoder.setElementPointer(4, &_var4Encoder);
    _encoder.setElementPointer(5, &_var5Encoder);
    _encoder.setElementPointer(6, &_var6Encoder);
    _encoder.setElementPointer(7, &_var7Encoder);
    _encoder.setElementPointer(8, &_var8Encoder);
}

InertiaMatrixEncoder::InertiaMatrixEncoder(const InertiaMatrixEncoder & rhs) :
    _encoder(EncodingHelpers::HLAfloat64LE(), 9)
    , _var0Encoder(rhs._var0Encoder)
    , _var1Encoder(rhs._var1Encoder)
    , _var2Encoder(rhs._var2Encoder)
    , _var3Encoder(rhs._var3Encoder)
    , _var4Encoder(rhs._var4Encoder)
    , _var5Encoder(rhs._var5Encoder)
    , _var6Encoder(rhs._var6Encoder)
    , _var7Encoder(rhs._var7Encoder)
    , _var8Encoder(rhs._var8Encoder)
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
    _encoder.setElementPointer(3, &_var3Encoder);
    _encoder.setElementPointer(4, &_var4Encoder);
    _encoder.setElementPointer(5, &_var5Encoder);
    _encoder.setElementPointer(6, &_var6Encoder);
    _encoder.setElementPointer(7, &_var7Encoder);
    _encoder.setElementPointer(8, &_var8Encoder);
}

static size_t verifyLength(const std::vector<double >& v) THROW_SPEC (EncodingHelpers::EncoderException) {
    if (v.size() != 9) {
        throw EncodingHelpers::EncoderException(L"Wrong size of vector in InertiaMatrixEncoder! Expected size: 9. Size of current vector: " + StringUtil::sizeToWstring(v.size()));
    }
    return v.size();
}

InertiaMatrixEncoder::InertiaMatrixEncoder(const std::vector<double >& v) THROW_SPEC (EncodingHelpers::EncoderException) :
    _encoder(EncodingHelpers::HLAfloat64LE(), verifyLength(v))
    , _var0Encoder(BaseEncoder::createMassMomentOfInertia(v[0]))
    , _var1Encoder(BaseEncoder::createMassMomentOfInertia(v[1]))
    , _var2Encoder(BaseEncoder::createMassMomentOfInertia(v[2]))
    , _var3Encoder(BaseEncoder::createMassMomentOfInertia(v[3]))
    , _var4Encoder(BaseEncoder::createMassMomentOfInertia(v[4]))
    , _var5Encoder(BaseEncoder::createMassMomentOfInertia(v[5]))
    , _var6Encoder(BaseEncoder::createMassMomentOfInertia(v[6]))
    , _var7Encoder(BaseEncoder::createMassMomentOfInertia(v[7]))
    , _var8Encoder(BaseEncoder::createMassMomentOfInertia(v[8]))
{
    _encoder.setElementPointer(0, &_var0Encoder);
    _encoder.setElementPointer(1, &_var1Encoder);
    _encoder.setElementPointer(2, &_var2Encoder);
    _encoder.setElementPointer(3, &_var3Encoder);
    _encoder.setElementPointer(4, &_var4Encoder);
    _encoder.setElementPointer(5, &_var5Encoder);
    _encoder.setElementPointer(6, &_var6Encoder);
    _encoder.setElementPointer(7, &_var7Encoder);
    _encoder.setElementPointer(8, &_var8Encoder);
}

InertiaMatrixEncoder::operator std::vector<double > () const {
    std::vector<double > res;
    for (size_t i = 0; i < _encoder.size(); i++) {
        res.push_back(dynamic_cast<const EncodingHelpers::HLAfloat64LE&>(_encoder[i]));
    }
    return res;
}

void InertiaMatrixEncoder::set(const std::vector<double > & v) THROW_SPEC (EncodingHelpers::EncoderException) {
    verifyLength(v);
    _var0Encoder.set(v[0]);
    _var1Encoder.set(v[1]);
    _var2Encoder.set(v[2]);
    _var3Encoder.set(v[3]);
    _var4Encoder.set(v[4]);
    _var5Encoder.set(v[5]);
    _var6Encoder.set(v[6]);
    _var7Encoder.set(v[7]);
    _var8Encoder.set(v[8]);
}

EncodingHelpers::DataElement* InertiaMatrixEncoder::clone () const {
    return new InertiaMatrixEncoder(*this);
}

