/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_ATTITUDEQUATERNIONENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_ATTITUDEQUATERNIONENCODER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <RtiDriver/Encoding/BasicDataElements.h>
#include "VectorEncoder.h"
#include <LunarSimulation/HlaLibSettings.h>
#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/HLAfixedRecord.h>

namespace LunarSimulation {

    class AttitudeQuaternion;

    class AttitudeQuaternionEncoder : public EncodingHelpers::AbstractDataElement {

    public:
        AttitudeQuaternionEncoder();

        AttitudeQuaternionEncoder(const AttitudeQuaternionEncoder & rhs);

        explicit AttitudeQuaternionEncoder(const AttitudeQuaternion & d);

        operator AttitudeQuaternion() const;

        void set(const AttitudeQuaternion & d);

        DataElement* clone() const;

    private:
        EncodingHelpers::HLAfixedRecord _encoder;

        EncodingHelpers::HLAfloat64LE _scalarEncoder;
        LunarSimulation::VectorEncoder _vectorEncoder;

        EncodingHelpers::DataElement & getEncoder() {
            return _encoder;
        }

        const EncodingHelpers::DataElement & getEncoder() const {
            return _encoder;
        }
    };
}

#endif
