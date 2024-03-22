/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALAUNCHERVALUELISTENER_H
#define DEVELOPER_STUDIO_HLALAUNCHERVALUELISTENER_H

#include <memory>

#include <LunarSimulation/datatypes/AccelerationVector.h>
#include <LunarSimulation/datatypes/AngularAccelerationVector.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaLauncherAttributes.h>    

namespace LunarSimulation {

   /**
   * Listener for updates of attributes, with the new updated values.  
   */
   class HlaLauncherValueListener {

   public:

      LIBAPI virtual ~HlaLauncherValueListener() {}
    
      /**
      * This method is called when the attribute <code>position</code> is updated.
      * <br>Description from the FOM: 3-Vector that represents the position of the launcher
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param launcher The object which is updated.
      * @param position The new value of the attribute in this update
      * @param validOldPosition True if oldPosition contains a valid value
      * @param oldPosition The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void positionUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > position, bool validOldPosition, std::vector</* 3 */ double > oldPosition, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>mass</code> is updated.
      * <br>Description from the FOM: Mass of launcher
      * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      *
      * @param launcher The object which is updated.
      * @param mass The new value of the attribute in this update
      * @param validOldMass True if oldMass contains a valid value
      * @param oldMass The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void massUpdated(HlaLauncherPtr launcher, double mass, bool validOldMass, double oldMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>energy</code> is updated.
      * <br>Description from the FOM: Amount of energy left in launcher. Launching a payload would cost some amount of energy
      * <br>Description of the data type from the FOM: A measure of energy. [unit: Joule (J), resolution: NA, accuracy: NA]
      *
      * @param launcher The object which is updated.
      * @param energy The new value of the attribute in this update
      * @param validOldEnergy True if oldEnergy contains a valid value
      * @param oldEnergy The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void energyUpdated(HlaLauncherPtr launcher, double energy, bool validOldEnergy, double oldEnergy, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>name</code> is updated.
      * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      * <br>Description of the data type from the FOM: 
      *
      * @param launcher The object which is updated.
      * @param name The new value of the attribute in this update
      * @param validOldName True if oldName contains a valid value
      * @param oldName The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void nameUpdated(HlaLauncherPtr launcher, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>type</code> is updated.
      * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
      * <br>Description of the data type from the FOM: 
      *
      * @param launcher The object which is updated.
      * @param type The new value of the attribute in this update
      * @param validOldType True if oldType contains a valid value
      * @param oldType The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void typeUpdated(HlaLauncherPtr launcher, std::wstring type, bool validOldType, std::wstring oldType, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>status</code> is updated.
      * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
      * <br>Description of the data type from the FOM: 
      *
      * @param launcher The object which is updated.
      * @param status The new value of the attribute in this update
      * @param validOldStatus True if oldStatus contains a valid value
      * @param oldStatus The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void statusUpdated(HlaLauncherPtr launcher, std::wstring status, bool validOldStatus, std::wstring oldStatus, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>parentReferenceFrame</code> is updated.
      * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
      * <br>Description of the data type from the FOM: 
      *
      * @param launcher The object which is updated.
      * @param parentReferenceFrame The new value of the attribute in this update
      * @param validOldParentReferenceFrame True if oldParentReferenceFrame contains a valid value
      * @param oldParentReferenceFrame The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void parentReferenceFrameUpdated(HlaLauncherPtr launcher, std::wstring parentReferenceFrame, bool validOldParentReferenceFrame, std::wstring oldParentReferenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>state</code> is updated.
      * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @param launcher The object which is updated.
      * @param state The new value of the attribute in this update
      * @param validOldState True if oldState contains a valid value
      * @param oldState The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void stateUpdated(HlaLauncherPtr launcher, SpaceTimeCoordinateState state, bool validOldState, SpaceTimeCoordinateState oldState, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>acceleration</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param launcher The object which is updated.
      * @param acceleration The new value of the attribute in this update
      * @param validOldAcceleration True if oldAcceleration contains a valid value
      * @param oldAcceleration The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void accelerationUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > acceleration, bool validOldAcceleration, std::vector</* 3 */ double > oldAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>rotationalAcceleration</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
      *
      * @param launcher The object which is updated.
      * @param rotationalAcceleration The new value of the attribute in this update
      * @param validOldRotationalAcceleration True if oldRotationalAcceleration contains a valid value
      * @param oldRotationalAcceleration The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void rotationalAccelerationUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > rotationalAcceleration, bool validOldRotationalAcceleration, std::vector</* 3 */ double > oldRotationalAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>centerOfMass</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param launcher The object which is updated.
      * @param centerOfMass The new value of the attribute in this update
      * @param validOldCenterOfMass True if oldCenterOfMass contains a valid value
      * @param oldCenterOfMass The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void centerOfMassUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > centerOfMass, bool validOldCenterOfMass, std::vector</* 3 */ double > oldCenterOfMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>bodyWrtStructural</code> is updated.
      * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @param launcher The object which is updated.
      * @param bodyWrtStructural The new value of the attribute in this update
      * @param validOldBodyWrtStructural True if oldBodyWrtStructural contains a valid value
      * @param oldBodyWrtStructural The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void bodyWrtStructuralUpdated(HlaLauncherPtr launcher, AttitudeQuaternion bodyWrtStructural, bool validOldBodyWrtStructural, AttitudeQuaternion oldBodyWrtStructural, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
      /**
      * This method is called when the producing federate of an attribute is changed.
      * Only available when using HLA Evolved.
      *
      * @param launcher The object which is updated.
      * @param attribute The attribute that now has a new producing federate
      * @param oldProducingFederate The federate handle of the old producing federate
      * @param newProducingFederate The federate handle of the new producing federate
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void producingFederateUpdated(HlaLauncherPtr launcher, HlaLauncherAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaLauncherValueListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaLauncherValueListener::Adapter : public HlaLauncherValueListener {

   public:

      LIBAPI virtual void positionUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > position, bool validOldPosition, std::vector</* 3 */ double > oldPosition, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void massUpdated(HlaLauncherPtr launcher, double mass, bool validOldMass, double oldMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void energyUpdated(HlaLauncherPtr launcher, double energy, bool validOldEnergy, double oldEnergy, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void nameUpdated(HlaLauncherPtr launcher, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void typeUpdated(HlaLauncherPtr launcher, std::wstring type, bool validOldType, std::wstring oldType, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void statusUpdated(HlaLauncherPtr launcher, std::wstring status, bool validOldStatus, std::wstring oldStatus, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void parentReferenceFrameUpdated(HlaLauncherPtr launcher, std::wstring parentReferenceFrame, bool validOldParentReferenceFrame, std::wstring oldParentReferenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void stateUpdated(HlaLauncherPtr launcher, SpaceTimeCoordinateState state, bool validOldState, SpaceTimeCoordinateState oldState, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void accelerationUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > acceleration, bool validOldAcceleration, std::vector</* 3 */ double > oldAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void rotationalAccelerationUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > rotationalAcceleration, bool validOldRotationalAcceleration, std::vector</* 3 */ double > oldRotationalAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void centerOfMassUpdated(HlaLauncherPtr launcher, std::vector</* 3 */ double > centerOfMass, bool validOldCenterOfMass, std::vector</* 3 */ double > oldCenterOfMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void bodyWrtStructuralUpdated(HlaLauncherPtr launcher, AttitudeQuaternion bodyWrtStructural, bool validOldBodyWrtStructural, AttitudeQuaternion oldBodyWrtStructural, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
      LIBAPI virtual void producingFederateUpdated(HlaLauncherPtr launcher, HlaLauncherAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
   };

}
#endif
