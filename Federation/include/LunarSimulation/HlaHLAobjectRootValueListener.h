/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAHLAOBJECTROOTVALUELISTENER_H
#define DEVELOPER_STUDIO_HLAHLAOBJECTROOTVALUELISTENER_H

#include <memory>


#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaHLAobjectRootAttributes.h>    

namespace LunarSimulation {

   /**
   * Listener for updates of attributes, with the new updated values.  
   */
   class HlaHLAobjectRootValueListener {

   public:

      LIBAPI virtual ~HlaHLAobjectRootValueListener() {}

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaHLAobjectRootValueListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaHLAobjectRootValueListener::Adapter : public HlaHLAobjectRootValueListener {

   public:
   };

}
#endif
