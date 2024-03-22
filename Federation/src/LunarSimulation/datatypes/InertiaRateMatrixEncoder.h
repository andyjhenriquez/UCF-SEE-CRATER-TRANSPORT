/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_INERTIARATEMATRIXENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_INERTIARATEMATRIXENCODER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <RtiDriver/Encoding/BasicDataElements.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/HLAfixedArray.h>
#include <vector>

namespace LunarSimulation {

    class InertiaRateMatrixEncoder :public EncodingHelpers::AbstractDataElement{

    public:
        InertiaRateMatrixEncoder();

        InertiaRateMatrixEncoder(const InertiaRateMatrixEncoder & rhs);

        explicit InertiaRateMatrixEncoder(const std::vector<double > & v)
            THROW_SPEC (EncodingHelpers::EncoderException);

        operator std::vector<double > () const;

        void set(const std::vector<double > & v)
            THROW_SPEC (EncodingHelpers::EncoderException);

        DataElement* clone () const;

    private:
        EncodingHelpers::HLAfixedArray _encoder;
        EncodingHelpers::HLAfloat64LE _var0Encoder;
        EncodingHelpers::HLAfloat64LE _var1Encoder;
        EncodingHelpers::HLAfloat64LE _var2Encoder;
        EncodingHelpers::HLAfloat64LE _var3Encoder;
        EncodingHelpers::HLAfloat64LE _var4Encoder;
        EncodingHelpers::HLAfloat64LE _var5Encoder;
        EncodingHelpers::HLAfloat64LE _var6Encoder;
        EncodingHelpers::HLAfloat64LE _var7Encoder;
        EncodingHelpers::HLAfloat64LE _var8Encoder;

        EncodingHelpers::DataElement & getEncoder() {
            return _encoder;
        }

        const EncodingHelpers::DataElement & getEncoder() const {
            return _encoder;
        }
    };
}

#endif
