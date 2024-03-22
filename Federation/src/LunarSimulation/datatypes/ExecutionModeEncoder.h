/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_EXECUTIONMODEENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_EXECUTIONMODEENCODER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/ExecutionMode.h>
#include <RtiDriver/Encoding/AbstractDataElement.h>
#include <RtiDriver/Encoding/BasicDataElements.h>

namespace LunarSimulation {

    class ExecutionModeEncoder : public EncodingHelpers::AbstractDataElement {

    public:
        ExecutionModeEncoder();

        ExecutionModeEncoder(const ExecutionModeEncoder & rhs);

        explicit ExecutionModeEncoder(const ExecutionMode::ExecutionMode & d);

        operator ExecutionMode::ExecutionMode() const {
            return static_cast<ExecutionMode::ExecutionMode>(_encoder.get());
        }

        void set(const ExecutionMode::ExecutionMode & d);

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
