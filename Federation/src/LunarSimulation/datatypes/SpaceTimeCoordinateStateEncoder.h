/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_SPACETIMECOORDINATESTATEENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_SPACETIMECOORDINATESTATEENCODER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <RtiDriver/Encoding/BasicDataElements.h>
#include "ReferenceFrameRotationEncoder.h"
#include "ReferenceFrameTranslationEncoder.h"
#include <LunarSimulation/HlaLibSettings.h>
#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/HLAfixedRecord.h>

namespace LunarSimulation {

    class SpaceTimeCoordinateState;

    class SpaceTimeCoordinateStateEncoder : public EncodingHelpers::AbstractDataElement {

    public:
        SpaceTimeCoordinateStateEncoder();

        SpaceTimeCoordinateStateEncoder(const SpaceTimeCoordinateStateEncoder & rhs);

        explicit SpaceTimeCoordinateStateEncoder(const SpaceTimeCoordinateState & d);

        operator SpaceTimeCoordinateState() const;

        void set(const SpaceTimeCoordinateState & d);

        DataElement* clone() const;

    private:
        EncodingHelpers::HLAfixedRecord _encoder;

        LunarSimulation::ReferenceFrameTranslationEncoder _translationalStateEncoder;
        LunarSimulation::ReferenceFrameRotationEncoder _rotationalStateEncoder;
        EncodingHelpers::HLAfloat64LE _timeEncoder;

        EncodingHelpers::DataElement & getEncoder() {
            return _encoder;
        }

        const EncodingHelpers::DataElement & getEncoder() const {
            return _encoder;
        }
    };
}

#endif
