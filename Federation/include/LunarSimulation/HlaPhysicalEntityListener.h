/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALENTITYLISTENER_H
#define DEVELOPER_STUDIO_HLAPHYSICALENTITYLISTENER_H

#include <set>


#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPhysicalEntityAttributes.h>
#include <LunarSimulation/HlaEnumSet.h>

namespace LunarSimulation {
   /**
   * Listener for updates of attributes.  
   */
   class HlaPhysicalEntityListener {
   public:

      LIBAPI virtual ~HlaPhysicalEntityListener() {}

      /**
      * This method is called when a HLA <code>reflectAttributeValueUpdate</code> is received for an remote object,
      * or a set of attributes is updated on a local object.
      *
      * @param physicalEntity The physicalEntity which this update corresponds to.
      * @param attributes The set of attributes that are updated.
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time the update was initiated.
      */
      LIBAPI virtual void attributesUpdated(HlaPhysicalEntityPtr physicalEntity, const HlaEnumSet<HlaPhysicalEntityAttributes::Attribute> &attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaPhysicalEntityListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaPhysicalEntityListener::Adapter : public HlaPhysicalEntityListener {
   public:

      LIBAPI virtual void attributesUpdated(HlaPhysicalEntityPtr physicalEntity, const HlaEnumSet<HlaPhysicalEntityAttributes::Attribute> &attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
   };

}
#endif
