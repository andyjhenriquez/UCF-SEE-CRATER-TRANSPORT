/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAREFERENCEFRAMEATTRIBUTES_H
#define DEVELOPER_STUDIO_HLAREFERENCEFRAMEATTRIBUTES_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>
#include <vector>
#include <utility>
    
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaHLAobjectRootAttributes.h>
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

   /**
   * Interface used to represent all attributes for an object instance.
   */
   class HlaReferenceFrameAttributes : public HlaHLAobjectRootAttributes {
   public:


     /**
      * An enumeration of the attributes of an HlaReferenceFrame
      *
      *<table>
      * <caption>All attributes</caption>
      * <tr><td><b>Enum constant</b></td><td><b>C++ name</b></td><td><b>FOM name</b></td></tr>
      * <tr><td>NAME</td><td>name</td><td><code>name</code></td></tr>
      * <tr><td>PARENT_NAME</td><td>parentName</td><td><code>parent_name</code></td></tr>
      * <tr><td>STATE</td><td>state</td><td><code>state</code></td></tr>
      *</table>
      */
      enum Attribute {
        /**
        * name (FOM name: <code>name</code>).
        * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
        */
         NAME,

        /**
        * parentName (FOM name: <code>parent_name</code>).
        * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
        */
         PARENT_NAME,

        /**
        * state (FOM name: <code>state</code>).
        * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
        */
         STATE

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

      LIBAPI virtual ~HlaReferenceFrameAttributes() {}
    
      /**
      * Returns true if the <code>name</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      *
      * @return true if <code>name</code> is available.
      */
      LIBAPI virtual bool hasName() = 0;

      /**
      * Gets the value of the <code>name</code> attribute.
      *
      * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      * <br>Description of the data type from the FOM: 
      *
      * @return the <code>name</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::wstring getName()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>name</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>name</code> attribute.
      */
      LIBAPI virtual std::wstring getName(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>name</code> attribute.
      * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>name</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getNameTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>parentName</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
      *
      * @return true if <code>parentName</code> is available.
      */
      LIBAPI virtual bool hasParentName() = 0;

      /**
      * Gets the value of the <code>parentName</code> attribute.
      *
      * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
      * <br>Description of the data type from the FOM: 
      *
      * @return the <code>parentName</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::wstring getParentName()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>parentName</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>parentName</code> attribute.
      */
      LIBAPI virtual std::wstring getParentName(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>parentName</code> attribute.
      * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>parentName</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getParentNameTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>state</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
      *
      * @return true if <code>state</code> is available.
      */
      LIBAPI virtual bool hasState() = 0;

      /**
      * Gets the value of the <code>state</code> attribute.
      *
      * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @return the <code>state</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::SpaceTimeCoordinateState getState()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>state</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @param defaultValue default value
      *
      * @return the <code>state</code> attribute.
      */
      LIBAPI virtual LunarSimulation::SpaceTimeCoordinateState getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>state</code> attribute.
      * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @return the time stamped <code>state</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > getStateTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
   };
}
#endif
