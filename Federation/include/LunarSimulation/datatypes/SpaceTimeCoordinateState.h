/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_SPACETIMECOORDINATESTATE_H
#define DEVELOPER_STUDIO_DATATYPES_SPACETIMECOORDINATESTATE_H

#include <iostream>
#include <LunarSimulation/HlaLibSettings.h>

#include <LunarSimulation/datatypes/ReferenceFrameRotation.h>
#include <LunarSimulation/datatypes/ReferenceFrameTranslation.h>

namespace LunarSimulation {
   /**
   * Implementation of the <code>SpaceTimeCoordinateState</code> data type from the FOM.
   * <br>Description from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
   */
   class SpaceTimeCoordinateState {

   public:
      /**
      * Description from the FOM: This is the reference frame's translational state with respect to its parent frame. If this frame has no parent, this attribute is meaningless.
      * <br>Description of the data type from the FOM: This is the translational state of a subject reference frame with respect to a 'referent' frame. This data type does not specify the two reference frames.
      */
      ReferenceFrameTranslation translationalState;
      /**
      * Description from the FOM: This is the reference frame's rotational state with respect to its parent frame. If this frame has no parent, this attribute is meaningless.
      * <br>Description of the data type from the FOM: This is the rotational state of a reference frame with respect to a 'referent' frame.
      */
      ReferenceFrameRotation rotationalState;
      /**
      * Description from the FOM: This specifies the simulated physical time (TT), which represents the time dimension associated with a reference frame state.  It is the fourth component along with the three spatial dimensions that define a reference frame coordinate state.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      */
      double time;

      LIBAPI SpaceTimeCoordinateState()
         :
         translationalState(ReferenceFrameTranslation()),
         rotationalState(ReferenceFrameRotation()),
         time(0)
      {}

      /**
      * Constructor for SpaceTimeCoordinateState
      *
      * @param translationalState_ value to set as translationalState.
      *        <br>Description from the FOM: This is the reference frame's translational state with respect to its parent frame. If this frame has no parent, this attribute is meaningless.
      *        <br>Description of the data type from the FOM: This is the translational state of a subject reference frame with respect to a 'referent' frame. This data type does not specify the two reference frames.
      * @param rotationalState_ value to set as rotationalState.
      *        <br>Description from the FOM: This is the reference frame's rotational state with respect to its parent frame. If this frame has no parent, this attribute is meaningless.
      *        <br>Description of the data type from the FOM: This is the rotational state of a reference frame with respect to a 'referent' frame.
      * @param time_ value to set as time.
      *        <br>Description from the FOM: This specifies the simulated physical time (TT), which represents the time dimension associated with a reference frame state.  It is the fourth component along with the three spatial dimensions that define a reference frame coordinate state.
      *        <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      */
      LIBAPI SpaceTimeCoordinateState(
         ReferenceFrameTranslation translationalState_,
         ReferenceFrameRotation rotationalState_,
         double time_
         )
         :
         translationalState(translationalState_),
         rotationalState(rotationalState_),
         time(time_)
      {}



      /**
      * Function to get translationalState.
      * <br>Description from the FOM: This is the reference frame's translational state with respect to its parent frame. If this frame has no parent, this attribute is meaningless.
      * <br>Description of the data type from the FOM: This is the translational state of a subject reference frame with respect to a 'referent' frame. This data type does not specify the two reference frames.
      *
      * @return translationalState
      */
      LIBAPI LunarSimulation::ReferenceFrameTranslation & getTranslationalState() {
         return translationalState;
      }

      /**
      * Function to get rotationalState.
      * <br>Description from the FOM: This is the reference frame's rotational state with respect to its parent frame. If this frame has no parent, this attribute is meaningless.
      * <br>Description of the data type from the FOM: This is the rotational state of a reference frame with respect to a 'referent' frame.
      *
      * @return rotationalState
      */
      LIBAPI LunarSimulation::ReferenceFrameRotation & getRotationalState() {
         return rotationalState;
      }

      /**
      * Function to get time.
      * <br>Description from the FOM: This specifies the simulated physical time (TT), which represents the time dimension associated with a reference frame state.  It is the fourth component along with the three spatial dimensions that define a reference frame coordinate state.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @return time
      */
      LIBAPI double & getTime() {
         return time;
      }

   };


   LIBAPI bool operator ==(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r);
   LIBAPI bool operator !=(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r);
   LIBAPI bool operator <(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r);
   LIBAPI bool operator >(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r);

   LIBAPI std::wostream & operator << (std::wostream &, LunarSimulation::SpaceTimeCoordinateState const &);
   LIBAPI std::ostream & operator << (std::ostream &, LunarSimulation::SpaceTimeCoordinateState const &);
}
#endif
