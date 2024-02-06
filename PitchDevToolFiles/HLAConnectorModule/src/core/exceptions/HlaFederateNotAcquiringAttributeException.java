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
 * Exception thrown if the federate tries to cancel acquire ownership of an attribute it
 * is not currently trying to acquire ownership of
 */
public final class HlaFederateNotAcquiringAttributeException extends HlaBaseException {

   public HlaFederateNotAcquiringAttributeException(String message) {
      super(message);
   }

   public HlaFederateNotAcquiringAttributeException(String message, Throwable cause) {
      super(message, cause);
   }
}
