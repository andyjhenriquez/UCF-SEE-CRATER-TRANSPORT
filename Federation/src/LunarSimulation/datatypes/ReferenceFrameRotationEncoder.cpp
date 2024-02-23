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

#include "ReferenceFrameRotationEncoder.h"
#include <LunarSimulation/datatypes/ReferenceFrameRotation.h>


#include "BaseEncoder.h"

using namespace LunarSimulation;

ReferenceFrameRotationEncoder::ReferenceFrameRotationEncoder()
    :
   _attitudeQuaternionEncoder(BaseEncoder::createAttitudeQuaternion()),
   _angularVelocityEncoder(BaseEncoder::createAngularVelocityVector())
{
   _encoder.appendElementPointer(&_attitudeQuaternionEncoder);
   _encoder.appendElementPointer(&_angularVelocityEncoder);
}

ReferenceFrameRotationEncoder::ReferenceFrameRotationEncoder(const ReferenceFrameRotationEncoder & rhs)
    :
   _attitudeQuaternionEncoder(rhs._attitudeQuaternionEncoder),
   _angularVelocityEncoder(rhs._angularVelocityEncoder)
{
   _encoder.appendElementPointer(&_attitudeQuaternionEncoder);
   _encoder.appendElementPointer(&_angularVelocityEncoder);
}

ReferenceFrameRotationEncoder::ReferenceFrameRotationEncoder(const ReferenceFrameRotation &d)
    :
   _attitudeQuaternionEncoder(BaseEncoder::createAttitudeQuaternion(d.attitudeQuaternion)),
   _angularVelocityEncoder(BaseEncoder::createAngularVelocityVector(d.angularVelocity))
{
   _encoder.appendElementPointer(&_attitudeQuaternionEncoder);
   _encoder.appendElementPointer(&_angularVelocityEncoder);
}

ReferenceFrameRotationEncoder::operator ReferenceFrameRotation() const {
   return ReferenceFrameRotation(
      dynamic_cast<const LunarSimulation::AttitudeQuaternionEncoder&>(_encoder.get(0)),
      dynamic_cast<const LunarSimulation::AngularVelocityVectorEncoder&>(_encoder.get(1))
   );
}

void ReferenceFrameRotationEncoder::set(const ReferenceFrameRotation & d) {
   _attitudeQuaternionEncoder.set(d.attitudeQuaternion);
   _angularVelocityEncoder.set(d.angularVelocity);
}

EncodingHelpers::DataElement* ReferenceFrameRotationEncoder::clone () const {
   return new ReferenceFrameRotationEncoder(*this);
}
