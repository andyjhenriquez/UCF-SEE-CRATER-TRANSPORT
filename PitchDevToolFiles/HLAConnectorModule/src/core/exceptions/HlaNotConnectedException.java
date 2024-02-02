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
 * Exception thrown if not connected to the RTI and joined to the federation when performing an operation
 * that require that.
 */
public final class HlaNotConnectedException extends HlaBaseException {

   public HlaNotConnectedException(String message) {
      super(message);
   }

   public HlaNotConnectedException(String message, Throwable cause) {
      super(message, cause);
   }
}
