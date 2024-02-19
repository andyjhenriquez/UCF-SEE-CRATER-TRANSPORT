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

#include "MTRModeEncoder.h"

#include "BaseEncoder.h"

using namespace LunarSimulation;

MTRModeEncoder::MTRModeEncoder() {
}

MTRModeEncoder::MTRModeEncoder(const MTRModeEncoder & rhs) :
    _encoder(rhs._encoder)
{
}

MTRModeEncoder::MTRModeEncoder(const MTRMode::MTRMode &d) {
    _encoder.set(d);
}

void MTRModeEncoder::set(const MTRMode::MTRMode & d) {
   _encoder.set(d);
}

EncodingHelpers::DataElement* MTRModeEncoder::clone () const {
   return new MTRModeEncoder(*this);
}
