/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAINTERACTIONLISTENER_H
#define DEVELOPER_STUDIO_HLAINTERACTIONLISTENER_H

#include <LunarSimulation/datatypes/MTRMode.h>

#include <LunarSimulation/HlaTimeStamp.h>
#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Listener for all global interactions.
   */

   class HlaInteractionListener {
   public:

      LIBAPI virtual ~HlaInteractionListener() {}

      /**
      * This method is invoked when an HLA <code>HLAinteractionRoot</code> interaction is received,
      * (or is sent locally).
      * @param local <code>true</code> if the interaction was sent locally <code>false</code> otherwise
      * @param timeStamp the time when the interaction was sent
      * @param logicalTime the logical time when the interaction was sent
      */
      LIBAPI virtual void hLAinteractionRoot(
          bool local,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) = 0;
      /**
      * This method is invoked when an HLA <code>HLAinteractionRoot.Start_Stop</code> interaction is received,
      * (or is sent locally).
      * @param local <code>true</code> if the interaction was sent locally <code>false</code> otherwise
      * @param timeStamp the time when the interaction was sent
      * @param logicalTime the logical time when the interaction was sent
      */
      LIBAPI virtual void startStop(
          bool local,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) = 0;
      /**
      * This method is invoked when an HLA <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction is received,
      * (or is sent locally).
      * @param local <code>true</code> if the interaction was sent locally <code>false</code> otherwise
      * @param parameters contains value for the parameters
      * @param timeStamp the time when the interaction was sent
      * @param logicalTime the logical time when the interaction was sent
      */
      LIBAPI virtual void modeTransitionRequest(
          bool local,
          HlaModeTransitionRequestParametersPtr parameters,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) = 0;

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaInteractionListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaInteractionListener::Adapter : public HlaInteractionListener {
   public:

      LIBAPI virtual void hLAinteractionRoot(
          bool local,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) {}
      LIBAPI virtual void startStop(
          bool local,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) {}
      LIBAPI virtual void modeTransitionRequest(
          bool local,
          HlaModeTransitionRequestParametersPtr parameters,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) {}
   };

}
#endif
