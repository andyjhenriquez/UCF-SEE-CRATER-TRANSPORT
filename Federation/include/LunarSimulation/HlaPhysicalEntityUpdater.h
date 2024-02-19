/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALENTITYUPDATER_H
#define DEVELOPER_STUDIO_HLAPHYSICALENTITYUPDATER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/AccelerationVector.h>
#include <LunarSimulation/datatypes/AngularAccelerationVector.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaHLAobjectRootUpdater.h>

namespace LunarSimulation {

    /**
    * Updater used to update attribute values.
    */
    class HlaPhysicalEntityUpdater : public HlaHLAobjectRootUpdater {

    public:

    LIBAPI virtual ~HlaPhysicalEntityUpdater() {}

    /**
    * Set the name for this update.
    * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
    * <br>Description of the data type from the FOM: 
    *
    * @param name the new name
    */
    LIBAPI virtual void setName(const std::wstring& name) = 0;

    /**
    * Set the type for this update.
    * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
    * <br>Description of the data type from the FOM: 
    *
    * @param type the new type
    */
    LIBAPI virtual void setType(const std::wstring& type) = 0;

    /**
    * Set the status for this update.
    * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
    * <br>Description of the data type from the FOM: 
    *
    * @param status the new status
    */
    LIBAPI virtual void setStatus(const std::wstring& status) = 0;

    /**
    * Set the parentReferenceFrame for this update.
    * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
    * <br>Description of the data type from the FOM: 
    *
    * @param parentReferenceFrame the new parentReferenceFrame
    */
    LIBAPI virtual void setParentReferenceFrame(const std::wstring& parentReferenceFrame) = 0;

    /**
    * Set the state for this update.
    * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
    * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
    *
    * @param state the new state
    */
    LIBAPI virtual void setState(const LunarSimulation::SpaceTimeCoordinateState& state) = 0;

    /**
    * Set the acceleration for this update.
    * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param acceleration the new acceleration
    */
    LIBAPI virtual void setAcceleration(const std::vector</* 3 */ double >& acceleration) = 0;

    /**
    * Set the rotationalAcceleration for this update.
    * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
    *
    * @param rotationalAcceleration the new rotationalAcceleration
    */
    LIBAPI virtual void setRotationalAcceleration(const std::vector</* 3 */ double >& rotationalAcceleration) = 0;

    /**
    * Set the centerOfMass for this update.
    * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
    * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
    *
    * @param centerOfMass the new centerOfMass
    */
    LIBAPI virtual void setCenterOfMass(const std::vector</* 3 */ double >& centerOfMass) = 0;

    /**
    * Set the bodyWrtStructural for this update.
    * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
    * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
    *
    * @param bodyWrtStructural the new bodyWrtStructural
    */
    LIBAPI virtual void setBodyWrtStructural(const LunarSimulation::AttitudeQuaternion& bodyWrtStructural) = 0;

    /**
    * Send all the attributes.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate()
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

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
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate(HlaTimeStampPtr timestamp)
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

    /**
    * Send all the attributes with a specified timestamp.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate(HlaLogicalTimePtr logicalTime)
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

    /**
    * Send all the attributes with a specified timestamp.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param timestamp timestamp to send for this update
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;
    };
}
#endif
