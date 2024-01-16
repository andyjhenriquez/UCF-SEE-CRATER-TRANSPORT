package core.impl.utils;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

public final class MinMax<T> {
   public final T _min;
   public final T _max;

   private MinMax(T min, T max) {
      _min = min;
      _max = max;
   }

   public static <T> MinMax<T> create(T min, T max) {
      return new MinMax<T>(min, max);
   }
}
