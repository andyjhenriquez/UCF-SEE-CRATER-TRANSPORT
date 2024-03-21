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

#include "ReferenceFrameTranslationEncoder.h"
#include <LunarSimulation/datatypes/ReferenceFrameTranslation.h>


#include "BaseEncoder.h"

using namespace LunarSimulation;

ReferenceFrameTranslationEncoder::ReferenceFrameTranslationEncoder()
    :
   _positionEncoder(BaseEncoder::createPositionVector()),
   _velocityEncoder(BaseEncoder::createVelocityVector())
{
   _encoder.appendElementPointer(&_positionEncoder);
   _encoder.appendElementPointer(&_velocityEncoder);
}

ReferenceFrameTranslationEncoder::ReferenceFrameTranslationEncoder(const ReferenceFrameTranslationEncoder & rhs)
    :
   _positionEncoder(rhs._positionEncoder),
   _velocityEncoder(rhs._velocityEncoder)
{
   _encoder.appendElementPointer(&_positionEncoder);
   _encoder.appendElementPointer(&_velocityEncoder);
}

ReferenceFrameTranslationEncoder::ReferenceFrameTranslationEncoder(const ReferenceFrameTranslation &d)
    :
   _positionEncoder(BaseEncoder::createPositionVector(d.position)),
   _velocityEncoder(BaseEncoder::createVelocityVector(d.velocity))
{
   _encoder.appendElementPointer(&_positionEncoder);
   _encoder.appendElementPointer(&_velocityEncoder);
}

ReferenceFrameTranslationEncoder::operator ReferenceFrameTranslation() const {
   return ReferenceFrameTranslation(
      dynamic_cast<const LunarSimulation::PositionVectorEncoder&>(_encoder.get(0)),
      dynamic_cast<const LunarSimulation::VelocityVectorEncoder&>(_encoder.get(1))
   );
}

void ReferenceFrameTranslationEncoder::set(const ReferenceFrameTranslation & d) {
   _positionEncoder.set(d.position);
   _velocityEncoder.set(d.velocity);
}

EncodingHelpers::DataElement* ReferenceFrameTranslationEncoder::clone () const {
   return new ReferenceFrameTranslationEncoder(*this);
}
