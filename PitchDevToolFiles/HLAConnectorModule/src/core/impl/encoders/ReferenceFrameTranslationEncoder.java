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

import core.datatypes.ReferenceFrameTranslation;

public final class ReferenceFrameTranslationEncoder extends AbstractFixedRecordEncoder<ReferenceFrameTranslation> {


   public ReferenceFrameTranslationEncoder() {
      super(ReferenceFrameTranslationEncoder.class);

      _encoder.add(new PositionVectorEncoder());
      _encoder.add(new VelocityVectorEncoder());
   }

   public ReferenceFrameTranslationEncoder(ReferenceFrameTranslation value) {
      this();
      setValue(value);
   }

   protected void encodeValue(ReferenceFrameTranslation value) {
      ((PositionVectorEncoder)_encoder.get(0)).setValue(value.getPosition());
      ((VelocityVectorEncoder)_encoder.get(1)).setValue(value.getVelocity());
   }

   protected ReferenceFrameTranslation decodeValue() {
      return ReferenceFrameTranslation.create(
         ((PositionVectorEncoder)_encoder.get(0)).getValue(),
         ((VelocityVectorEncoder)_encoder.get(1)).getValue()
      );
   }
}
