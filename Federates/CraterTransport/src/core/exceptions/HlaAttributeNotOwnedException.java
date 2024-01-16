package core.exceptions;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */


/**
 * Exception thrown if the attribute failed to be updated due to lacking ownership,
 * or when trying to release an unowned attribute.
 */
public final class HlaAttributeNotOwnedException extends HlaBaseException {

   public HlaAttributeNotOwnedException(String message) {
      super(message);
   }

   public HlaAttributeNotOwnedException(String message, Throwable cause) {
      super(message, cause);
   }
}
