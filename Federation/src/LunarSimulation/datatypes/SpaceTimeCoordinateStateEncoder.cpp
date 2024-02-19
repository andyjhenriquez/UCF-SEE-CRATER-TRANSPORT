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

#include "SpaceTimeCoordinateStateEncoder.h"
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>


#include "BaseEncoder.h"

using namespace LunarSimulation;

SpaceTimeCoordinateStateEncoder::SpaceTimeCoordinateStateEncoder()
    :
   _translationalStateEncoder(BaseEncoder::createReferenceFrameTranslation()),
   _rotationalStateEncoder(BaseEncoder::createReferenceFrameRotation()),
   _timeEncoder(BaseEncoder::createTime())
{
   _encoder.appendElementPointer(&_translationalStateEncoder);
   _encoder.appendElementPointer(&_rotationalStateEncoder);
   _encoder.appendElementPointer(&_timeEncoder);
}

SpaceTimeCoordinateStateEncoder::SpaceTimeCoordinateStateEncoder(const SpaceTimeCoordinateStateEncoder & rhs)
    :
   _translationalStateEncoder(rhs._translationalStateEncoder),
   _rotationalStateEncoder(rhs._rotationalStateEncoder),
   _timeEncoder(rhs._timeEncoder)
{
   _encoder.appendElementPointer(&_translationalStateEncoder);
   _encoder.appendElementPointer(&_rotationalStateEncoder);
   _encoder.appendElementPointer(&_timeEncoder);
}

SpaceTimeCoordinateStateEncoder::SpaceTimeCoordinateStateEncoder(const SpaceTimeCoordinateState &d)
    :
   _translationalStateEncoder(BaseEncoder::createReferenceFrameTranslation(d.translationalState)),
   _rotationalStateEncoder(BaseEncoder::createReferenceFrameRotation(d.rotationalState)),
   _timeEncoder(BaseEncoder::createTime(d.time))
{
   _encoder.appendElementPointer(&_translationalStateEncoder);
   _encoder.appendElementPointer(&_rotationalStateEncoder);
   _encoder.appendElementPointer(&_timeEncoder);
}

SpaceTimeCoordinateStateEncoder::operator SpaceTimeCoordinateState() const {
   return SpaceTimeCoordinateState(
      dynamic_cast<const LunarSimulation::ReferenceFrameTranslationEncoder&>(_encoder.get(0)),
      dynamic_cast<const LunarSimulation::ReferenceFrameRotationEncoder&>(_encoder.get(1)),
      dynamic_cast<const EncodingHelpers::HLAfloat64LE&>(_encoder.get(2))
   );
}

void SpaceTimeCoordinateStateEncoder::set(const SpaceTimeCoordinateState & d) {
   _translationalStateEncoder.set(d.translationalState);
   _rotationalStateEncoder.set(d.rotationalState);
   _timeEncoder.set(d.time);
}

EncodingHelpers::DataElement* SpaceTimeCoordinateStateEncoder::clone () const {
   return new SpaceTimeCoordinateStateEncoder(*this);
}
