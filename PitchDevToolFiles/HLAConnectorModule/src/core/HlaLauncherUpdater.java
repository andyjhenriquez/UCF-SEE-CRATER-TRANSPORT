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
import core.exceptions.*;


/**
 * Updater used to update attribute values.
 * <p>
 * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public interface HlaLauncherUpdater extends HlaPhysicalEntityUpdater {

   /**
    * Set the position for this update.
    * <br>Description from the FOM: 3-Vector that represents the position of the launcher
    * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param position the new position
    *
    * @return this updater
    */
    HlaLauncherUpdater setPosition(double[/* 3 */] position);

   /**
    * Set the mass for this update.
    * <br>Description from the FOM: Mass of launcher
    * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
    *
    * @param mass the new mass
    *
    * @return this updater
    */
    HlaLauncherUpdater setMass(double mass);

   /**
    * Set the energy for this update.
    * <br>Description from the FOM: Amount of energy left in launcher. Launching a payload would cost some amount of energy
    * <br>Description of the data type from the FOM: A measure of energy. [unit: Joule (J), resolution: NA, accuracy: NA]
    *
    * @param energy the new energy
    *
    * @return this updater
    */
    HlaLauncherUpdater setEnergy(double energy);

   /**
    * Set the name for this update.
    * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
    * <br>Description of the data type from the FOM: 
    *
    * @param name the new name
    *
    * @return this updater
    */
    HlaLauncherUpdater setName(String name);

   /**
    * Set the type for this update.
    * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
    * <br>Description of the data type from the FOM: 
    *
    * @param type the new type
    *
    * @return this updater
    */
    HlaLauncherUpdater setType(String type);

   /**
    * Set the status for this update.
    * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
    * <br>Description of the data type from the FOM: 
    *
    * @param status the new status
    *
    * @return this updater
    */
    HlaLauncherUpdater setStatus(String status);

   /**
    * Set the parentReferenceFrame for this update.
    * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
    * <br>Description of the data type from the FOM: 
    *
    * @param parentReferenceFrame the new parentReferenceFrame
    *
    * @return this updater
    */
    HlaLauncherUpdater setParentReferenceFrame(String parentReferenceFrame);

   /**
    * Set the state for this update.
    * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
    * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
    *
    * @param state the new state
    *
    * @return this updater
    */
    HlaLauncherUpdater setState(SpaceTimeCoordinateState state);

   /**
    * Set the acceleration for this update.
    * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param acceleration the new acceleration
    *
    * @return this updater
    */
    HlaLauncherUpdater setAcceleration(double[/* 3 */] acceleration);

   /**
    * Set the rotationalAcceleration for this update.
    * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
    *
    * @param rotationalAcceleration the new rotationalAcceleration
    *
    * @return this updater
    */
    HlaLauncherUpdater setRotationalAcceleration(double[/* 3 */] rotationalAcceleration);

   /**
    * Set the centerOfMass for this update.
    * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param centerOfMass the new centerOfMass
    *
    * @return this updater
    */
    HlaLauncherUpdater setCenterOfMass(double[/* 3 */] centerOfMass);

   /**
    * Set the bodyWrtStructural for this update.
    * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
    * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
    *
    * @param bodyWrtStructural the new bodyWrtStructural
    *
    * @return this updater
    */
    HlaLauncherUpdater setBodyWrtStructural(AttitudeQuaternion bodyWrtStructural);

   /**
    * Send all the attributes.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate()
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Send all the attributes with a specified timestamp.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param timestamp timestamp to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate(HlaTimeStamp timestamp)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Send all the attributes with a specified logical time.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate(HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException,
                HlaInvalidLogicalTimeException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Send all the attributes with a specified timestamp and logical time.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param timestamp timestamp to send for this update
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate(HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException,
                HlaInvalidLogicalTimeException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;
}