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

import core.datatypes.AttitudeQuaternion;
import se.pitch.encoders1516.HLAfloat64LE;

public final class AttitudeQuaternionEncoder extends AbstractFixedRecordEncoder<AttitudeQuaternion> {


   public AttitudeQuaternionEncoder() {
      super(AttitudeQuaternionEncoder.class);

      _encoder.add(BaseEncoder.createHLAfloat64LE());
      _encoder.add(new VectorEncoder());
   }

   public AttitudeQuaternionEncoder(AttitudeQuaternion value) {
      this();
      setValue(value);
   }

   protected void encodeValue(AttitudeQuaternion value) {
      ((HLAfloat64LE)_encoder.get(0)).setValue(value.getScalar());
      ((VectorEncoder)_encoder.get(1)).setValue(value.getVector());
   }

   protected AttitudeQuaternion decodeValue() {
      return AttitudeQuaternion.create(
         ((HLAfloat64LE)_encoder.get(0)).getValue(),
         ((VectorEncoder)_encoder.get(1)).getValue()
      );
   }
}
