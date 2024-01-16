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

import core.datatypes.ExecutionMode;

public final class ExecutionModeEncoder extends AbstractEnum16Encoder<ExecutionMode> {

   public ExecutionModeEncoder() {
      super(ExecutionModeEncoder.class, ExecutionMode.class, BaseEncoder.createHLAinteger16LE());
   }

   public ExecutionModeEncoder(ExecutionMode value) {
      this();
      setValue(value);
   }

   protected ExecutionMode find(long ordinal) {
      return ExecutionMode.find(ordinal);
   }
}
