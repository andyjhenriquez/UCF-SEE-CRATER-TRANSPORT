package core;

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


/**
 * Listener for all global interactions.
 */
public interface HlaInteractionListener {

   /**
    * This method is invoked when an HLA <code>HLAinteractionRoot</code> interaction is received,
    * (or is sent locally).
    *
    * @param local <code>true</code> if the interaction was sent locally <code>false</code> otherwise
    * @param timeStamp the time when the interaction was sent
    * @param logicalTime the logical time when the interaction was sent
    */
   void hLAinteractionRoot(
      boolean local,
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   );

   /**
    * This method is invoked when an HLA <code>HLAinteractionRoot.Start_Stop</code> interaction is received,
    * (or is sent locally).
    *
    * @param local <code>true</code> if the interaction was sent locally <code>false</code> otherwise
    * @param timeStamp the time when the interaction was sent
    * @param logicalTime the logical time when the interaction was sent
    */
   void startStop(
      boolean local,
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   );

   /**
    * This method is invoked when an HLA <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction is received,
    * (or is sent locally).
    *
    * @param local <code>true</code> if the interaction was sent locally <code>false</code> otherwise
    * @param parameters contains value for the parameters
    * @param timeStamp the time when the interaction was sent
    * @param logicalTime the logical time when the interaction was sent
    */
   void modeTransitionRequest(
      boolean local,
      HlaInteractionManager.HlaModeTransitionRequestParameters parameters,
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   );


   /**
    * An abstract adapter class that implements the HlaInteractionListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
   public abstract static class Adapter implements HlaInteractionListener {
      public void hLAinteractionRoot(
         boolean local,
         HlaTimeStamp timeStamp,
         HlaLogicalTime logicalTime
       ) {}

      public void startStop(
         boolean local,
         HlaTimeStamp timeStamp,
         HlaLogicalTime logicalTime
       ) {}

      public void modeTransitionRequest(
         boolean local,
         HlaInteractionManager.HlaModeTransitionRequestParameters parameters,
         HlaTimeStamp timeStamp,
         HlaLogicalTime logicalTime
       ) {}

   }
}
