/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPAYLOADVALUELISTENER_H
#define DEVELOPER_STUDIO_HLAPAYLOADVALUELISTENER_H

#include <memory>

#include <LunarSimulation/datatypes/AccelerationVector.h>
#include <LunarSimulation/datatypes/AngularAccelerationVector.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/ForceVector.h>
#include <LunarSimulation/datatypes/InertiaMatrix.h>
#include <LunarSimulation/datatypes/InertiaRateMatrix.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <LunarSimulation/datatypes/TorqueVector.h>
#include <LunarSimulation/datatypes/VelocityVector.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPayloadAttributes.h>    

namespace LunarSimulation {

   /**
   * Listener for updates of attributes, with the new updated values.  
   */
   class HlaPayloadValueListener {

   public:

      LIBAPI virtual ~HlaPayloadValueListener() {}
    
      /**
      * This method is called when the attribute <code>position</code> is updated.
      * <br>Description from the FOM: 3-Vector that specifies the position of the launcher
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param payload The object which is updated.
      * @param position The new value of the attribute in this update
      * @param validOldPosition True if oldPosition contains a valid value
      * @param oldPosition The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void positionUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > position, bool validOldPosition, std::vector</* 3 */ double > oldPosition, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>velocity</code> is updated.
      * <br>Description from the FOM: payload velocity
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param payload The object which is updated.
      * @param velocity The new value of the attribute in this update
      * @param validOldVelocity True if oldVelocity contains a valid value
      * @param oldVelocity The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void velocityUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > velocity, bool validOldVelocity, std::vector</* 3 */ double > oldVelocity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>health</code> is updated.
      * <br>Description from the FOM: Scalar representing health
      * <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
      *
      * @param payload The object which is updated.
      * @param health The new value of the attribute in this update
      * @param validOldHealth True if oldHealth contains a valid value
      * @param oldHealth The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void healthUpdated(HlaPayloadPtr payload, double health, bool validOldHealth, double oldHealth, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>force</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the total external force on the entity. Force is expressed and applied in the entity’s structural reference frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param payload The object which is updated.
      * @param force The new value of the attribute in this update
      * @param validOldForce True if oldForce contains a valid value
      * @param oldForce The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void forceUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > force, bool validOldForce, std::vector</* 3 */ double > oldForce, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>torque</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the total external torque on the entity. It is expressed in the entity’s structural reference frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the vector torque.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param payload The object which is updated.
      * @param torque The new value of the attribute in this update
      * @param validOldTorque True if oldTorque contains a valid value
      * @param oldTorque The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void torqueUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > torque, bool validOldTorque, std::vector</* 3 */ double > oldTorque, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>mass</code> is updated.
      * <br>Description from the FOM: The mass of the DynamicalEntity.
      * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      *
      * @param payload The object which is updated.
      * @param mass The new value of the attribute in this update
      * @param validOldMass True if oldMass contains a valid value
      * @param oldMass The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void massUpdated(HlaPayloadPtr payload, double mass, bool validOldMass, double oldMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>massRate</code> is updated.
      * <br>Description from the FOM: The time rate of change of the DynamicalEntity's mass.
      * <br>Description of the data type from the FOM: A measurement of the rate of change of mass. [unit: kilogram per second (kg/s), resolution: NA, accuracy: NA]
      *
      * @param payload The object which is updated.
      * @param massRate The new value of the attribute in this update
      * @param validOldMassRate True if oldMassRate contains a valid value
      * @param oldMassRate The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void massRateUpdated(HlaPayloadPtr payload, double massRate, bool validOldMassRate, double oldMassRate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>inertia</code> is updated.
      * <br>Description from the FOM: A 3x3 matrix that specifies the centroid moments and coefficients of inertia with respect to the coordinate axes of the DynamicalEntity's body frame
      * <br>Description of the data type from the FOM: A 3x3 matrix that specifies the mass inertia matrix of a body about some coordinate axes. The nine elements of the matrix are stored row-wise, namely: Ixx, Ixy, Ixz, Iyx, Iyy, Iyz, Izx, Izy, Izz. The off-diagonal components Iij (i!=j) are the so-called 'negative integrals'. This means that the elements in this inertia matrix satisfy the equation H=Iw. Where H is the angular momentum vector, I is the inertia matrix and w is the angular velocity vector. This data type does not specify the coordinate axes about which the moments are calculated.
      *
      * @param payload The object which is updated.
      * @param inertia The new value of the attribute in this update
      * @param validOldInertia True if oldInertia contains a valid value
      * @param oldInertia The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void inertiaUpdated(HlaPayloadPtr payload, std::vector</* 9 */ double > inertia, bool validOldInertia, std::vector</* 9 */ double > oldInertia, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>inertiaRate</code> is updated.
      * <br>Description from the FOM: A 3x3 matrix that specifies the time rate of change of the parameters in the InertiaMatrix.  The elements in this matrix correspond directly to the elements in the InteriaMatrix.
      * <br>Description of the data type from the FOM: A 3x3 matrix that specifies the time rate of change of the parameters in the InertiaMatrix.  The elements in this matrix correspond directly to the elements in the InteriaMatrix.
      *
      * @param payload The object which is updated.
      * @param inertiaRate The new value of the attribute in this update
      * @param validOldInertiaRate True if oldInertiaRate contains a valid value
      * @param oldInertiaRate The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void inertiaRateUpdated(HlaPayloadPtr payload, std::vector</* 9 */ double > inertiaRate, bool validOldInertiaRate, std::vector</* 9 */ double > oldInertiaRate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>name</code> is updated.
      * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      * <br>Description of the data type from the FOM: 
      *
      * @param payload The object which is updated.
      * @param name The new value of the attribute in this update
      * @param validOldName True if oldName contains a valid value
      * @param oldName The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void nameUpdated(HlaPayloadPtr payload, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>type</code> is updated.
      * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
      * <br>Description of the data type from the FOM: 
      *
      * @param payload The object which is updated.
      * @param type The new value of the attribute in this update
      * @param validOldType True if oldType contains a valid value
      * @param oldType The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void typeUpdated(HlaPayloadPtr payload, std::wstring type, bool validOldType, std::wstring oldType, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>status</code> is updated.
      * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
      * <br>Description of the data type from the FOM: 
      *
      * @param payload The object which is updated.
      * @param status The new value of the attribute in this update
      * @param validOldStatus True if oldStatus contains a valid value
      * @param oldStatus The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void statusUpdated(HlaPayloadPtr payload, std::wstring status, bool validOldStatus, std::wstring oldStatus, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>parentReferenceFrame</code> is updated.
      * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
      * <br>Description of the data type from the FOM: 
      *
      * @param payload The object which is updated.
      * @param parentReferenceFrame The new value of the attribute in this update
      * @param validOldParentReferenceFrame True if oldParentReferenceFrame contains a valid value
      * @param oldParentReferenceFrame The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void parentReferenceFrameUpdated(HlaPayloadPtr payload, std::wstring parentReferenceFrame, bool validOldParentReferenceFrame, std::wstring oldParentReferenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>state</code> is updated.
      * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @param payload The object which is updated.
      * @param state The new value of the attribute in this update
      * @param validOldState True if oldState contains a valid value
      * @param oldState The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void stateUpdated(HlaPayloadPtr payload, SpaceTimeCoordinateState state, bool validOldState, SpaceTimeCoordinateState oldState, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>acceleration</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param payload The object which is updated.
      * @param acceleration The new value of the attribute in this update
      * @param validOldAcceleration True if oldAcceleration contains a valid value
      * @param oldAcceleration The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void accelerationUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > acceleration, bool validOldAcceleration, std::vector</* 3 */ double > oldAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>rotationalAcceleration</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
      *
      * @param payload The object which is updated.
      * @param rotationalAcceleration The new value of the attribute in this update
      * @param validOldRotationalAcceleration True if oldRotationalAcceleration contains a valid value
      * @param oldRotationalAcceleration The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void rotationalAccelerationUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > rotationalAcceleration, bool validOldRotationalAcceleration, std::vector</* 3 */ double > oldRotationalAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>centerOfMass</code> is updated.
      * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param payload The object which is updated.
      * @param centerOfMass The new value of the attribute in this update
      * @param validOldCenterOfMass True if oldCenterOfMass contains a valid value
      * @param oldCenterOfMass The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void centerOfMassUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > centerOfMass, bool validOldCenterOfMass, std::vector</* 3 */ double > oldCenterOfMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>bodyWrtStructural</code> is updated.
      * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @param payload The object which is updated.
      * @param bodyWrtStructural The new value of the attribute in this update
      * @param validOldBodyWrtStructural True if oldBodyWrtStructural contains a valid value
      * @param oldBodyWrtStructural The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void bodyWrtStructuralUpdated(HlaPayloadPtr payload, AttitudeQuaternion bodyWrtStructural, bool validOldBodyWrtStructural, AttitudeQuaternion oldBodyWrtStructural, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
      /**
      * This method is called when the producing federate of an attribute is changed.
      * Only available when using HLA Evolved.
      *
      * @param payload The object which is updated.
      * @param attribute The attribute that now has a new producing federate
      * @param oldProducingFederate The federate handle of the old producing federate
      * @param newProducingFederate The federate handle of the new producing federate
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void producingFederateUpdated(HlaPayloadPtr payload, HlaPayloadAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaPayloadValueListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaPayloadValueListener::Adapter : public HlaPayloadValueListener {

   public:

      LIBAPI virtual void positionUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > position, bool validOldPosition, std::vector</* 3 */ double > oldPosition, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void velocityUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > velocity, bool validOldVelocity, std::vector</* 3 */ double > oldVelocity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void healthUpdated(HlaPayloadPtr payload, double health, bool validOldHealth, double oldHealth, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void forceUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > force, bool validOldForce, std::vector</* 3 */ double > oldForce, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void torqueUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > torque, bool validOldTorque, std::vector</* 3 */ double > oldTorque, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void massUpdated(HlaPayloadPtr payload, double mass, bool validOldMass, double oldMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void massRateUpdated(HlaPayloadPtr payload, double massRate, bool validOldMassRate, double oldMassRate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void inertiaUpdated(HlaPayloadPtr payload, std::vector</* 9 */ double > inertia, bool validOldInertia, std::vector</* 9 */ double > oldInertia, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void inertiaRateUpdated(HlaPayloadPtr payload, std::vector</* 9 */ double > inertiaRate, bool validOldInertiaRate, std::vector</* 9 */ double > oldInertiaRate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void nameUpdated(HlaPayloadPtr payload, std::wstring name, bool validOldName, std::wstring oldName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void typeUpdated(HlaPayloadPtr payload, std::wstring type, bool validOldType, std::wstring oldType, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void statusUpdated(HlaPayloadPtr payload, std::wstring status, bool validOldStatus, std::wstring oldStatus, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void parentReferenceFrameUpdated(HlaPayloadPtr payload, std::wstring parentReferenceFrame, bool validOldParentReferenceFrame, std::wstring oldParentReferenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void stateUpdated(HlaPayloadPtr payload, SpaceTimeCoordinateState state, bool validOldState, SpaceTimeCoordinateState oldState, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void accelerationUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > acceleration, bool validOldAcceleration, std::vector</* 3 */ double > oldAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void rotationalAccelerationUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > rotationalAcceleration, bool validOldRotationalAcceleration, std::vector</* 3 */ double > oldRotationalAcceleration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void centerOfMassUpdated(HlaPayloadPtr payload, std::vector</* 3 */ double > centerOfMass, bool validOldCenterOfMass, std::vector</* 3 */ double > oldCenterOfMass, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void bodyWrtStructuralUpdated(HlaPayloadPtr payload, AttitudeQuaternion bodyWrtStructural, bool validOldBodyWrtStructural, AttitudeQuaternion oldBodyWrtStructural, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
      LIBAPI virtual void producingFederateUpdated(HlaPayloadPtr payload, HlaPayloadAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
   };

}
#endif
