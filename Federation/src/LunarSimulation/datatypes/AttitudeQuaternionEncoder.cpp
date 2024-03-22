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

#include "AttitudeQuaternionEncoder.h"
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>


#include "BaseEncoder.h"

using namespace LunarSimulation;

AttitudeQuaternionEncoder::AttitudeQuaternionEncoder()
    :
   _scalarEncoder(BaseEncoder::createScalar()),
   _vectorEncoder(BaseEncoder::createVector())
{
   _encoder.appendElementPointer(&_scalarEncoder);
   _encoder.appendElementPointer(&_vectorEncoder);
}

AttitudeQuaternionEncoder::AttitudeQuaternionEncoder(const AttitudeQuaternionEncoder & rhs)
    :
   _scalarEncoder(rhs._scalarEncoder),
   _vectorEncoder(rhs._vectorEncoder)
{
   _encoder.appendElementPointer(&_scalarEncoder);
   _encoder.appendElementPointer(&_vectorEncoder);
}

AttitudeQuaternionEncoder::AttitudeQuaternionEncoder(const AttitudeQuaternion &d)
    :
   _scalarEncoder(BaseEncoder::createScalar(d.scalar)),
   _vectorEncoder(BaseEncoder::createVector(d.vector))
{
   _encoder.appendElementPointer(&_scalarEncoder);
   _encoder.appendElementPointer(&_vectorEncoder);
}

AttitudeQuaternionEncoder::operator AttitudeQuaternion() const {
   return AttitudeQuaternion(
      dynamic_cast<const EncodingHelpers::HLAfloat64LE&>(_encoder.get(0)),
      dynamic_cast<const LunarSimulation::VectorEncoder&>(_encoder.get(1))
   );
}

void AttitudeQuaternionEncoder::set(const AttitudeQuaternion & d) {
   _scalarEncoder.set(d.scalar);
   _vectorEncoder.set(d.vector);
}

EncodingHelpers::DataElement* AttitudeQuaternionEncoder::clone () const {
   return new AttitudeQuaternionEncoder(*this);
}
