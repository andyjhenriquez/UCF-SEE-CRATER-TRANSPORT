/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMETRANSLATIONENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMETRANSLATIONENCODER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <RtiDriver/Encoding/BasicDataElements.h>
#include "PositionVectorEncoder.h"
#include "VelocityVectorEncoder.h"
#include <LunarSimulation/HlaLibSettings.h>
#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/HLAfixedRecord.h>

namespace LunarSimulation {

    class ReferenceFrameTranslation;

    class ReferenceFrameTranslationEncoder : public EncodingHelpers::AbstractDataElement {

    public:
        ReferenceFrameTranslationEncoder();

        ReferenceFrameTranslationEncoder(const ReferenceFrameTranslationEncoder & rhs);

        explicit ReferenceFrameTranslationEncoder(const ReferenceFrameTranslation & d);

        operator ReferenceFrameTranslation() const;

        void set(const ReferenceFrameTranslation & d);

        DataElement* clone() const;

    private:
        EncodingHelpers::HLAfixedRecord _encoder;

        LunarSimulation::PositionVectorEncoder _positionEncoder;
        LunarSimulation::VelocityVectorEncoder _velocityEncoder;

        EncodingHelpers::DataElement & getEncoder() {
            return _encoder;
        }

        const EncodingHelpers::DataElement & getEncoder() const {
            return _encoder;
        }
    };
}

#endif
