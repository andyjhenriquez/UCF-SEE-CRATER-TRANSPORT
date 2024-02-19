/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMEROTATION_H
#define DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMEROTATION_H

#include <iostream>
#include <LunarSimulation/HlaLibSettings.h>

#include <LunarSimulation/datatypes/AngularVelocityVector.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <vector>

namespace LunarSimulation {
   /**
   * Implementation of the <code>ReferenceFrameRotation</code> data type from the FOM.
   * <br>Description from the FOM: This is the rotational state of a reference frame with respect to a 'referent' frame.
   */
   class ReferenceFrameRotation {

   public:
      /**
      * Description from the FOM: Attitude quaternion that specifies the orientation of the subject frame with respect to the referent.
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      */
      AttitudeQuaternion attitudeQuaternion;
      /**
      * Description from the FOM: Angular velocity of the subject frame with respect to the referent with components resolved onto the subject coordinate axes.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the orientation of one reference frame with respect to another. This data type does not specify the reference frames, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      */
      std::vector</* 3 */ double > angularVelocity;

      LIBAPI ReferenceFrameRotation()
         :
         attitudeQuaternion(AttitudeQuaternion()),
         angularVelocity(0)
      {}

      /**
      * Constructor for ReferenceFrameRotation
      *
      * @param attitudeQuaternion_ value to set as attitudeQuaternion.
      *        <br>Description from the FOM: Attitude quaternion that specifies the orientation of the subject frame with respect to the referent.
      *        <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      * @param angularVelocity_ value to set as angularVelocity.
      *        <br>Description from the FOM: Angular velocity of the subject frame with respect to the referent with components resolved onto the subject coordinate axes.
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the orientation of one reference frame with respect to another. This data type does not specify the reference frames, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      */
      LIBAPI ReferenceFrameRotation(
         AttitudeQuaternion attitudeQuaternion_,
         std::vector</* 3 */ double > angularVelocity_
         )
         :
         attitudeQuaternion(attitudeQuaternion_),
         angularVelocity(angularVelocity_)
      {}



      /**
      * Function to get attitudeQuaternion.
      * <br>Description from the FOM: Attitude quaternion that specifies the orientation of the subject frame with respect to the referent.
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @return attitudeQuaternion
      */
      LIBAPI LunarSimulation::AttitudeQuaternion & getAttitudeQuaternion() {
         return attitudeQuaternion;
      }

      /**
      * Function to get angularVelocity.
      * <br>Description from the FOM: Angular velocity of the subject frame with respect to the referent with components resolved onto the subject coordinate axes.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the orientation of one reference frame with respect to another. This data type does not specify the reference frames, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return angularVelocity
      */
      LIBAPI std::vector</* 3 */ double > & getAngularVelocity() {
         return angularVelocity;
      }

   };


   LIBAPI bool operator ==(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r);
   LIBAPI bool operator !=(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r);
   LIBAPI bool operator <(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r);
   LIBAPI bool operator >(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r);

   LIBAPI std::wostream & operator << (std::wostream &, LunarSimulation::ReferenceFrameRotation const &);
   LIBAPI std::ostream & operator << (std::ostream &, LunarSimulation::ReferenceFrameRotation const &);
}
#endif
