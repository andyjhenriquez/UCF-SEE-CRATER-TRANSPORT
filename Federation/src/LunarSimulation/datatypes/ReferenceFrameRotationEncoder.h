/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMEROTATIONENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMEROTATIONENCODER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <RtiDriver/Encoding/BasicDataElements.h>
#include "AngularVelocityVectorEncoder.h"
#include "AttitudeQuaternionEncoder.h"
#include <LunarSimulation/HlaLibSettings.h>
#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/HLAfixedRecord.h>

namespace LunarSimulation {

    class ReferenceFrameRotation;

    class ReferenceFrameRotationEncoder : public EncodingHelpers::AbstractDataElement {

    public:
        ReferenceFrameRotationEncoder();

        ReferenceFrameRotationEncoder(const ReferenceFrameRotationEncoder & rhs);

        explicit ReferenceFrameRotationEncoder(const ReferenceFrameRotation & d);

        operator ReferenceFrameRotation() const;

        void set(const ReferenceFrameRotation & d);

        DataElement* clone() const;

    private:
        EncodingHelpers::HLAfixedRecord _encoder;

        LunarSimulation::AttitudeQuaternionEncoder _attitudeQuaternionEncoder;
        LunarSimulation::AngularVelocityVectorEncoder _angularVelocityEncoder;

        EncodingHelpers::DataElement & getEncoder() {
            return _encoder;
        }

        const EncodingHelpers::DataElement & getEncoder() const {
            return _encoder;
        }
    };
}

#endif
