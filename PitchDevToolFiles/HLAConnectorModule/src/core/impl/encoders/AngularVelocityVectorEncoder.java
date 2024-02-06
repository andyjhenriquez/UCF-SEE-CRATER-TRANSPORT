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

import se.pitch.encoders1516.HLAfloat64LE;
import java.util.Iterator;

public final class AngularVelocityVectorEncoder extends AbstractFixedArrayEncoder<double[]> {


   public AngularVelocityVectorEncoder() {
      super(AngularVelocityVectorEncoder.class, 3);
   }

   public AngularVelocityVectorEncoder(double[] value) {
      this();
      setValue(value);
   }

   protected void encodeValue(double[] values) {
      Iterator iter = _encoder.iterator();
      for (int i = 0; i < values.length && iter.hasNext(); i++) {
         HLAfloat64LE element = (HLAfloat64LE)iter.next();
         element.setValue(values[i]);
      }
   }

   protected double[] decodeValue() {
      double[] value = new double[_encoder.size()];
      int i = 0;
      for (Iterator iter = _encoder.iterator(); iter.hasNext();) {
         HLAfloat64LE element = (HLAfloat64LE)iter.next();
         value[i++] = element.getValue();
      }
      return value;
   }

   protected HLAfloat64LE createElement() {
      return BaseEncoder.createHLAfloat64LE();
   }

   protected int getLength(double[] value) {
      return value.length;
   }
}
