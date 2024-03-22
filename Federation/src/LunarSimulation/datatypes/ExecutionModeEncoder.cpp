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

#include "ExecutionModeEncoder.h"

#include "BaseEncoder.h"

using namespace LunarSimulation;

ExecutionModeEncoder::ExecutionModeEncoder() {
}

ExecutionModeEncoder::ExecutionModeEncoder(const ExecutionModeEncoder & rhs) :
    _encoder(rhs._encoder)
{
}

ExecutionModeEncoder::ExecutionModeEncoder(const ExecutionMode::ExecutionMode &d) {
    _encoder.set(d);
}

void ExecutionModeEncoder::set(const ExecutionMode::ExecutionMode & d) {
   _encoder.set(d);
}

EncodingHelpers::DataElement* ExecutionModeEncoder::clone () const {
   return new ExecutionModeEncoder(*this);
}
