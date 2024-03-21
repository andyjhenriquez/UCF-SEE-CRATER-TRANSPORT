/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAHLAOBJECTROOTATTRIBUTES_H
#define DEVELOPER_STUDIO_HLAHLAOBJECTROOTATTRIBUTES_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>
#include <vector>
#include <utility>
    

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

   /**
   * Interface used to represent all attributes for an object instance.
   */
   class HlaHLAobjectRootAttributes : private LunarSimulation::noncopyable {
   public:


     /**
      * An enumeration of the attributes of an HlaHLAobjectRoot
      *
      *<table>
      * <caption>All attributes</caption>
      * <tr><td><b>Enum constant</b></td><td><b>C++ name</b></td><td><b>FOM name</b></td></tr>
      *</table>
      */
      enum Attribute {
      };

     /**
      * Gets the name of the attribute.
      *
      * @return The name of the attribute. An empty string will be returned if the attribute does not exist.
      */
      LIBAPI virtual std::wstring getName(Attribute attribute);

     /**
      * Finds the attribute specified in the parameter attributeName.
      * The found enumeration will be stored in the parameter attribute.
      *
      * @return true if the attribute was found, false otherwise.
      */
      LIBAPI virtual bool find(Attribute& attribute, std::wstring attributeName);

      LIBAPI virtual ~HlaHLAobjectRootAttributes() {}
   };
}
#endif
