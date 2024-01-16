package core.impl.encoders;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

import core.datatypes.ReferenceFrameRotation;

public final class ReferenceFrameRotationEncoder extends AbstractFixedRecordEncoder<ReferenceFrameRotation> {


   public ReferenceFrameRotationEncoder() {
      super(ReferenceFrameRotationEncoder.class);

      _encoder.add(new AttitudeQuaternionEncoder());
      _encoder.add(new AngularVelocityVectorEncoder());
   }

   public ReferenceFrameRotationEncoder(ReferenceFrameRotation value) {
      this();
      setValue(value);
   }

   protected void encodeValue(ReferenceFrameRotation value) {
      ((AttitudeQuaternionEncoder)_encoder.get(0)).setValue(value.getAttitudeQuaternion());
      ((AngularVelocityVectorEncoder)_encoder.get(1)).setValue(value.getAngularVelocity());
   }

   protected ReferenceFrameRotation decodeValue() {
      return ReferenceFrameRotation.create(
         ((AttitudeQuaternionEncoder)_encoder.get(0)).getValue(),
         ((AngularVelocityVectorEncoder)_encoder.get(1)).getValue()
      );
   }
}
