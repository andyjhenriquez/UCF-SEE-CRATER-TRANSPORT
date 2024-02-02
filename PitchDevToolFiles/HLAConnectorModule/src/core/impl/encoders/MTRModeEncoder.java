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

import core.datatypes.MTRMode;

public final class MTRModeEncoder extends AbstractEnum16Encoder<MTRMode> {

   public MTRModeEncoder() {
      super(MTRModeEncoder.class, MTRMode.class, BaseEncoder.createHLAinteger16LE());
   }

   public MTRModeEncoder(MTRMode value) {
      this();
      setValue(value);
   }

   protected MTRMode find(long ordinal) {
      return MTRMode.find(ordinal);
   }
}
