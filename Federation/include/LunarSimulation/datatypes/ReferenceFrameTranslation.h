/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMETRANSLATION_H
#define DEVELOPER_STUDIO_DATATYPES_REFERENCEFRAMETRANSLATION_H

#include <iostream>
#include <LunarSimulation/HlaLibSettings.h>

#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/VelocityVector.h>
#include <vector>

namespace LunarSimulation {
   /**
   * Implementation of the <code>ReferenceFrameTranslation</code> data type from the FOM.
   * <br>Description from the FOM: This is the translational state of a subject reference frame with respect to a 'referent' frame. This data type does not specify the two reference frames.
   */
   class ReferenceFrameTranslation {

   public:
      /**
      * Description from the FOM: Position of the subject frame origin with respect to the referent origin with components expressed in the referent coordinate axes.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      */
      std::vector</* 3 */ double > position;
      /**
      * Description from the FOM: Velocity of the subject frame origin with respect to its referent origin with components expressed in the referent coordinate axes.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      */
      std::vector</* 3 */ double > velocity;

      LIBAPI ReferenceFrameTranslation()
         :
         position(0),
         velocity(0)
      {}

      /**
      * Constructor for ReferenceFrameTranslation
      *
      * @param position_ value to set as position.
      *        <br>Description from the FOM: Position of the subject frame origin with respect to the referent origin with components expressed in the referent coordinate axes.
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param velocity_ value to set as velocity.
      *        <br>Description from the FOM: Velocity of the subject frame origin with respect to its referent origin with components expressed in the referent coordinate axes.
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      */
      LIBAPI ReferenceFrameTranslation(
         std::vector</* 3 */ double > position_,
         std::vector</* 3 */ double > velocity_
         )
         :
         position(position_),
         velocity(velocity_)
      {}



      /**
      * Function to get position.
      * <br>Description from the FOM: Position of the subject frame origin with respect to the referent origin with components expressed in the referent coordinate axes.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return position
      */
      LIBAPI std::vector</* 3 */ double > & getPosition() {
         return position;
      }

      /**
      * Function to get velocity.
      * <br>Description from the FOM: Velocity of the subject frame origin with respect to its referent origin with components expressed in the referent coordinate axes.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return velocity
      */
      LIBAPI std::vector</* 3 */ double > & getVelocity() {
         return velocity;
      }

   };


   LIBAPI bool operator ==(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r);
   LIBAPI bool operator !=(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r);
   LIBAPI bool operator <(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r);
   LIBAPI bool operator >(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r);

   LIBAPI std::wostream & operator << (std::wostream &, LunarSimulation::ReferenceFrameTranslation const &);
   LIBAPI std::ostream & operator << (std::ostream &, LunarSimulation::ReferenceFrameTranslation const &);
}
#endif
