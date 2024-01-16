package core;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

import core.datatypes.AttitudeQuaternion;
import core.datatypes.SpaceTimeCoordinateState;

/**
 * Listener for updates of attributes, with the new updated values.  
 */
public interface HlaPayloadValueListener {

   /**
    * This method is called when the attribute <code>position</code> is updated.
    * <br>Description from the FOM: 3-Vector that specifies the position of the launcher
    * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param payload   The object which is updated.
    * @param position    The new value of the attribute in this update
    * @param validOldPosition True if oldPosition contains a valid value
    * @param oldPosition   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void positionUpdated(HlaPayload payload, double[/* 3 */] position, boolean validOldPosition, double[/* 3 */] oldPosition, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>velocity</code> is updated.
    * <br>Description from the FOM: payload velocity
    * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param payload   The object which is updated.
    * @param velocity    The new value of the attribute in this update
    * @param validOldVelocity True if oldVelocity contains a valid value
    * @param oldVelocity   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void velocityUpdated(HlaPayload payload, double[/* 3 */] velocity, boolean validOldVelocity, double[/* 3 */] oldVelocity, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>health</code> is updated.
    * <br>Description from the FOM: Scalar representing health
    * <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
    *
    * @param payload   The object which is updated.
    * @param health    The new value of the attribute in this update
    * @param validOldHealth True if oldHealth contains a valid value
    * @param oldHealth   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void healthUpdated(HlaPayload payload, double health, boolean validOldHealth, double oldHealth, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>force</code> is updated.
    * <br>Description from the FOM: A 3-vector that specifies the total external force on the entity. Force is expressed and applied in the entity’s structural reference frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param payload   The object which is updated.
    * @param force    The new value of the attribute in this update
    * @param validOldForce True if oldForce contains a valid value
    * @param oldForce   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void forceUpdated(HlaPayload payload, double[/* 3 */] force, boolean validOldForce, double[/* 3 */] oldForce, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>torque</code> is updated.
    * <br>Description from the FOM: A 3-vector that specifies the total external torque on the entity. It is expressed in the entity’s structural reference frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the vector torque.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param payload   The object which is updated.
    * @param torque    The new value of the attribute in this update
    * @param validOldTorque True if oldTorque contains a valid value
    * @param oldTorque   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void torqueUpdated(HlaPayload payload, double[/* 3 */] torque, boolean validOldTorque, double[/* 3 */] oldTorque, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>mass</code> is updated.
    * <br>Description from the FOM: The mass of the DynamicalEntity.
    * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
    *
    * @param payload   The object which is updated.
    * @param mass    The new value of the attribute in this update
    * @param validOldMass True if oldMass contains a valid value
    * @param oldMass   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void massUpdated(HlaPayload payload, double mass, boolean validOldMass, double oldMass, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>massRate</code> is updated.
    * <br>Description from the FOM: The time rate of change of the DynamicalEntity's mass.
    * <br>Description of the data type from the FOM: A measurement of the rate of change of mass. [unit: kilogram per second (kg/s), resolution: NA, accuracy: NA]
    *
    * @param payload   The object which is updated.
    * @param massRate    The new value of the attribute in this update
    * @param validOldMassRate True if oldMassRate contains a valid value
    * @param oldMassRate   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void massRateUpdated(HlaPayload payload, double massRate, boolean validOldMassRate, double oldMassRate, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>inertia</code> is updated.
    * <br>Description from the FOM: A 3x3 matrix that specifies the centroid moments and coefficients of inertia with respect to the coordinate axes of the DynamicalEntity's body frame
    * <br>Description of the data type from the FOM: A 3x3 matrix that specifies the mass inertia matrix of a body about some coordinate axes. The nine elements of the matrix are stored row-wise, namely: Ixx, Ixy, Ixz, Iyx, Iyy, Iyz, Izx, Izy, Izz. The off-diagonal components Iij (i!=j) are the so-called 'negative integrals'. This means that the elements in this inertia matrix satisfy the equation H=Iw. Where H is the angular momentum vector, I is the inertia matrix and w is the angular velocity vector. This data type does not specify the coordinate axes about which the moments are calculated.
    *
    * @param payload   The object which is updated.
    * @param inertia    The new value of the attribute in this update
    * @param validOldInertia True if oldInertia contains a valid value
    * @param oldInertia   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void inertiaUpdated(HlaPayload payload, double[/* 9 */] inertia, boolean validOldInertia, double[/* 9 */] oldInertia, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>inertiaRate</code> is updated.
    * <br>Description from the FOM: A 3x3 matrix that specifies the time rate of change of the parameters in the InertiaMatrix.  The elements in this matrix correspond directly to the elements in the InteriaMatrix.
    * <br>Description of the data type from the FOM: A 3x3 matrix that specifies the time rate of change of the parameters in the InertiaMatrix.  The elements in this matrix correspond directly to the elements in the InteriaMatrix.
    *
    * @param payload   The object which is updated.
    * @param inertiaRate    The new value of the attribute in this update
    * @param validOldInertiaRate True if oldInertiaRate contains a valid value
    * @param oldInertiaRate   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void inertiaRateUpdated(HlaPayload payload, double[/* 9 */] inertiaRate, boolean validOldInertiaRate, double[/* 9 */] oldInertiaRate, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>name</code> is updated.
    * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
    * <br>Description of the data type from the FOM: 
    *
    * @param payload   The object which is updated.
    * @param name    The new value of the attribute in this update
    * @param validOldName True if oldName contains a valid value
    * @param oldName   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void nameUpdated(HlaPayload payload, String name, boolean validOldName, String oldName, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>type</code> is updated.
    * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
    * <br>Description of the data type from the FOM: 
    *
    * @param payload   The object which is updated.
    * @param type    The new value of the attribute in this update
    * @param validOldType True if oldType contains a valid value
    * @param oldType   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void typeUpdated(HlaPayload payload, String type, boolean validOldType, String oldType, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>status</code> is updated.
    * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
    * <br>Description of the data type from the FOM: 
    *
    * @param payload   The object which is updated.
    * @param status    The new value of the attribute in this update
    * @param validOldStatus True if oldStatus contains a valid value
    * @param oldStatus   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void statusUpdated(HlaPayload payload, String status, boolean validOldStatus, String oldStatus, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>parentReferenceFrame</code> is updated.
    * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
    * <br>Description of the data type from the FOM: 
    *
    * @param payload   The object which is updated.
    * @param parentReferenceFrame    The new value of the attribute in this update
    * @param validOldParentReferenceFrame True if oldParentReferenceFrame contains a valid value
    * @param oldParentReferenceFrame   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void parentReferenceFrameUpdated(HlaPayload payload, String parentReferenceFrame, boolean validOldParentReferenceFrame, String oldParentReferenceFrame, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>state</code> is updated.
    * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
    * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
    *
    * @param payload   The object which is updated.
    * @param state    The new value of the attribute in this update
    * @param validOldState True if oldState contains a valid value
    * @param oldState   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void stateUpdated(HlaPayload payload, SpaceTimeCoordinateState state, boolean validOldState, SpaceTimeCoordinateState oldState, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>acceleration</code> is updated.
    * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param payload   The object which is updated.
    * @param acceleration    The new value of the attribute in this update
    * @param validOldAcceleration True if oldAcceleration contains a valid value
    * @param oldAcceleration   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void accelerationUpdated(HlaPayload payload, double[/* 3 */] acceleration, boolean validOldAcceleration, double[/* 3 */] oldAcceleration, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>rotationalAcceleration</code> is updated.
    * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
    *
    * @param payload   The object which is updated.
    * @param rotationalAcceleration    The new value of the attribute in this update
    * @param validOldRotationalAcceleration True if oldRotationalAcceleration contains a valid value
    * @param oldRotationalAcceleration   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void rotationalAccelerationUpdated(HlaPayload payload, double[/* 3 */] rotationalAcceleration, boolean validOldRotationalAcceleration, double[/* 3 */] oldRotationalAcceleration, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>centerOfMass</code> is updated.
    * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param payload   The object which is updated.
    * @param centerOfMass    The new value of the attribute in this update
    * @param validOldCenterOfMass True if oldCenterOfMass contains a valid value
    * @param oldCenterOfMass   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void centerOfMassUpdated(HlaPayload payload, double[/* 3 */] centerOfMass, boolean validOldCenterOfMass, double[/* 3 */] oldCenterOfMass, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the attribute <code>bodyWrtStructural</code> is updated.
    * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
    * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
    *
    * @param payload   The object which is updated.
    * @param bodyWrtStructural    The new value of the attribute in this update
    * @param validOldBodyWrtStructural True if oldBodyWrtStructural contains a valid value
    * @param oldBodyWrtStructural   The old value of the attribute
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void bodyWrtStructuralUpdated(HlaPayload payload, AttitudeQuaternion bodyWrtStructural, boolean validOldBodyWrtStructural, AttitudeQuaternion oldBodyWrtStructural, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * This method is called when the producing federate of an attribute is changed.
    * Only available when using HLA Evolved.
    *
    * @param payload The object which is updated.
    * @param attribute The attribute that now has a new producing federate
    * @param oldProducingFederate The federate handle of the old producing federate
    * @param newProducingFederate The federate handle of the new producing federate
    * @param timeStamp  The time when the update was initiated.
    * @param logicalTime The logical time when the update was initiated.
    */
    void producingFederateUpdated(HlaPayload payload, HlaPayloadAttributes.Attribute attribute, HlaFederateId oldProducingFederate, HlaFederateId newProducingFederate, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime);

   /**
    * An abstract adapter class that implements the HlaPayloadValueListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    public abstract static class Adapter implements HlaPayloadValueListener {
        public void positionUpdated(HlaPayload payload, double[/* 3 */] position, boolean validOldPosition, double[/* 3 */] oldPosition, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void velocityUpdated(HlaPayload payload, double[/* 3 */] velocity, boolean validOldVelocity, double[/* 3 */] oldVelocity, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void healthUpdated(HlaPayload payload, double health, boolean validOldHealth, double oldHealth, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void forceUpdated(HlaPayload payload, double[/* 3 */] force, boolean validOldForce, double[/* 3 */] oldForce, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void torqueUpdated(HlaPayload payload, double[/* 3 */] torque, boolean validOldTorque, double[/* 3 */] oldTorque, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void massUpdated(HlaPayload payload, double mass, boolean validOldMass, double oldMass, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void massRateUpdated(HlaPayload payload, double massRate, boolean validOldMassRate, double oldMassRate, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void inertiaUpdated(HlaPayload payload, double[/* 9 */] inertia, boolean validOldInertia, double[/* 9 */] oldInertia, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void inertiaRateUpdated(HlaPayload payload, double[/* 9 */] inertiaRate, boolean validOldInertiaRate, double[/* 9 */] oldInertiaRate, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void nameUpdated(HlaPayload payload, String name, boolean validOldName, String oldName, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void typeUpdated(HlaPayload payload, String type, boolean validOldType, String oldType, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void statusUpdated(HlaPayload payload, String status, boolean validOldStatus, String oldStatus, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void parentReferenceFrameUpdated(HlaPayload payload, String parentReferenceFrame, boolean validOldParentReferenceFrame, String oldParentReferenceFrame, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void stateUpdated(HlaPayload payload, SpaceTimeCoordinateState state, boolean validOldState, SpaceTimeCoordinateState oldState, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void accelerationUpdated(HlaPayload payload, double[/* 3 */] acceleration, boolean validOldAcceleration, double[/* 3 */] oldAcceleration, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void rotationalAccelerationUpdated(HlaPayload payload, double[/* 3 */] rotationalAcceleration, boolean validOldRotationalAcceleration, double[/* 3 */] oldRotationalAcceleration, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void centerOfMassUpdated(HlaPayload payload, double[/* 3 */] centerOfMass, boolean validOldCenterOfMass, double[/* 3 */] oldCenterOfMass, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void bodyWrtStructuralUpdated(HlaPayload payload, AttitudeQuaternion bodyWrtStructural, boolean validOldBodyWrtStructural, AttitudeQuaternion oldBodyWrtStructural, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
        public void producingFederateUpdated(HlaPayload instance, HlaPayloadAttributes.Attribute attribute, HlaFederateId oldProducingFederate, HlaFederateId newProducingFederate, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {}
    }
}
