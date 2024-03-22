/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_MTRMODEENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_MTRMODEENCODER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/MTRMode.h>
#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/BasicDataElements.h>

namespace LunarSimulation {

    class MTRModeEncoder : public EncodingHelpers::AbstractDataElement {

    public:
        MTRModeEncoder();

        MTRModeEncoder(const MTRModeEncoder & rhs);

        explicit MTRModeEncoder(const MTRMode::MTRMode & d);

        operator MTRMode::MTRMode() const {
            return static_cast<MTRMode::MTRMode>(_encoder.get());
        }

        void set(const MTRMode::MTRMode & d);

        DataElement* clone () const;

    private:
        EncodingHelpers::HLAinteger16LE _encoder;

        EncodingHelpers::DataElement & getEncoder() {
            return _encoder;
        }

        const EncodingHelpers::DataElement & getEncoder() const {
            return _encoder;
        }
    };
}

#endif
