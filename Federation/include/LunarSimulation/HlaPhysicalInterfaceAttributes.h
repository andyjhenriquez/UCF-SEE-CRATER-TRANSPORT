/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEATTRIBUTES_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEATTRIBUTES_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>
#include <vector>
#include <utility>
    
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaHLAobjectRootAttributes.h>
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

   /**
   * Interface used to represent all attributes for an object instance.
   */
   class HlaPhysicalInterfaceAttributes : public HlaHLAobjectRootAttributes {
   public:


     /**
      * An enumeration of the attributes of an HlaPhysicalInterface
      *
      *<table>
      * <caption>All attributes</caption>
      * <tr><td><b>Enum constant</b></td><td><b>C++ name</b></td><td><b>FOM name</b></td></tr>
      * <tr><td>NAME</td><td>name</td><td><code>name</code></td></tr>
      * <tr><td>PARENT_NAME</td><td>parentName</td><td><code>parent_name</code></td></tr>
      * <tr><td>POSITION</td><td>position</td><td><code>position</code></td></tr>
      * <tr><td>ATTITUDE</td><td>attitude</td><td><code>attitude</code></td></tr>
      *</table>
      */
      enum Attribute {
        /**
        * name (FOM name: <code>name</code>).
        * <br>Description from the FOM: A non-empty string that identifies the interface. Each PhysicalInterface instance in the federation must have a unique name.
        */
         NAME,

        /**
        * parentName (FOM name: <code>parent_name</code>).
        * <br>Description from the FOM: The HLA Object Instance Name of the PhysicalEntity or PhysicalInterface to which this interface is attached.
        */
         PARENT_NAME,

        /**
        * position (FOM name: <code>position</code>).
        * <br>Description from the FOM: A 3-vector that specifies the position of the interface reference frame origin with respect to the parent structural reference frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
        */
         POSITION,

        /**
        * attitude (FOM name: <code>attitude</code>).
        * <br>Description from the FOM: An attitude quaternion of the interfaces reference frame ('subject frame') with respect to its parent structural reference frame ('referent frame').
        */
         ATTITUDE

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

      LIBAPI virtual ~HlaPhysicalInterfaceAttributes() {}
    
      /**
      * Returns true if the <code>name</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A non-empty string that identifies the interface. Each PhysicalInterface instance in the federation must have a unique name.
      *
      * @return true if <code>name</code> is available.
      */
      LIBAPI virtual bool hasName() = 0;

      /**
      * Gets the value of the <code>name</code> attribute.
      *
      * <br>Description from the FOM: A non-empty string that identifies the interface. Each PhysicalInterface instance in the federation must have a unique name.
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
      * <br>Description from the FOM: A non-empty string that identifies the interface. Each PhysicalInterface instance in the federation must have a unique name.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>name</code> attribute.
      */
      LIBAPI virtual std::wstring getName(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>name</code> attribute.
      * <br>Description from the FOM: A non-empty string that identifies the interface. Each PhysicalInterface instance in the federation must have a unique name.
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
      * <br>Description from the FOM: The HLA Object Instance Name of the PhysicalEntity or PhysicalInterface to which this interface is attached.
      *
      * @return true if <code>parentName</code> is available.
      */
      LIBAPI virtual bool hasParentName() = 0;

      /**
      * Gets the value of the <code>parentName</code> attribute.
      *
      * <br>Description from the FOM: The HLA Object Instance Name of the PhysicalEntity or PhysicalInterface to which this interface is attached.
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
      * <br>Description from the FOM: The HLA Object Instance Name of the PhysicalEntity or PhysicalInterface to which this interface is attached.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>parentName</code> attribute.
      */
      LIBAPI virtual std::wstring getParentName(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>parentName</code> attribute.
      * <br>Description from the FOM: The HLA Object Instance Name of the PhysicalEntity or PhysicalInterface to which this interface is attached.
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>parentName</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getParentNameTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>position</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A 3-vector that specifies the position of the interface reference frame origin with respect to the parent structural reference frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      *
      * @return true if <code>position</code> is available.
      */
      LIBAPI virtual bool hasPosition() = 0;

      /**
      * Gets the value of the <code>position</code> attribute.
      *
      * <br>Description from the FOM: A 3-vector that specifies the position of the interface reference frame origin with respect to the parent structural reference frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return the <code>position</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::vector</* 3 */ double > getPosition()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>position</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A 3-vector that specifies the position of the interface reference frame origin with respect to the parent structural reference frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param defaultValue default value
      *
      * @return the <code>position</code> attribute.
      */
      LIBAPI virtual std::vector</* 3 */ double > getPosition(std::vector</* 3 */ double > defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>position</code> attribute.
      * <br>Description from the FOM: A 3-vector that specifies the position of the interface reference frame origin with respect to the parent structural reference frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return the time stamped <code>position</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getPositionTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>attitude</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: An attitude quaternion of the interfaces reference frame ('subject frame') with respect to its parent structural reference frame ('referent frame').
      *
      * @return true if <code>attitude</code> is available.
      */
      LIBAPI virtual bool hasAttitude() = 0;

      /**
      * Gets the value of the <code>attitude</code> attribute.
      *
      * <br>Description from the FOM: An attitude quaternion of the interfaces reference frame ('subject frame') with respect to its parent structural reference frame ('referent frame').
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @return the <code>attitude</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::AttitudeQuaternion getAttitude()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>attitude</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: An attitude quaternion of the interfaces reference frame ('subject frame') with respect to its parent structural reference frame ('referent frame').
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @param defaultValue default value
      *
      * @return the <code>attitude</code> attribute.
      */
      LIBAPI virtual LunarSimulation::AttitudeQuaternion getAttitude(LunarSimulation::AttitudeQuaternion defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>attitude</code> attribute.
      * <br>Description from the FOM: An attitude quaternion of the interfaces reference frame ('subject frame') with respect to its parent structural reference frame ('referent frame').
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @return the time stamped <code>attitude</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > getAttitudeTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
   };
}
#endif
