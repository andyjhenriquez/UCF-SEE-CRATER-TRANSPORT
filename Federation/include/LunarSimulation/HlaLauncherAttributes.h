/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALAUNCHERATTRIBUTES_H
#define DEVELOPER_STUDIO_HLALAUNCHERATTRIBUTES_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>
#include <vector>
#include <utility>
    
#include <LunarSimulation/datatypes/AccelerationVector.h>
#include <LunarSimulation/datatypes/AngularAccelerationVector.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>
#include <vector>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPhysicalEntityAttributes.h>
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

   /**
   * Interface used to represent all attributes for an object instance.
   */
   class HlaLauncherAttributes : public HlaPhysicalEntityAttributes {
   public:


     /**
      * An enumeration of the attributes of an HlaLauncher
      *
      *<table>
      * <caption>All attributes</caption>
      * <tr><td><b>Enum constant</b></td><td><b>C++ name</b></td><td><b>FOM name</b></td></tr>
      * <tr><td>POSITION</td><td>position</td><td><code>position</code></td></tr>
      * <tr><td>MASS</td><td>mass</td><td><code>mass</code></td></tr>
      * <tr><td>ENERGY</td><td>energy</td><td><code>energy</code></td></tr>
      * <tr><td>NAME</td><td>name</td><td><code>name</code></td></tr>
      * <tr><td>TYPE</td><td>type</td><td><code>type</code></td></tr>
      * <tr><td>STATUS</td><td>status</td><td><code>status</code></td></tr>
      * <tr><td>PARENT_REFERENCE_FRAME</td><td>parentReferenceFrame</td><td><code>parent_reference_frame</code></td></tr>
      * <tr><td>STATE</td><td>state</td><td><code>state</code></td></tr>
      * <tr><td>ACCELERATION</td><td>acceleration</td><td><code>acceleration</code></td></tr>
      * <tr><td>ROTATIONAL_ACCELERATION</td><td>rotationalAcceleration</td><td><code>rotational_acceleration</code></td></tr>
      * <tr><td>CENTER_OF_MASS</td><td>centerOfMass</td><td><code>center_of_mass</code></td></tr>
      * <tr><td>BODY_WRT_STRUCTURAL</td><td>bodyWrtStructural</td><td><code>body_wrt_structural</code></td></tr>
      *</table>
      */
      enum Attribute {
        /**
        * position (FOM name: <code>position</code>).
        * <br>Description from the FOM: 3-Vector that represents the position of the launcher
        */
         POSITION,

        /**
        * mass (FOM name: <code>mass</code>).
        * <br>Description from the FOM: Mass of launcher
        */
         MASS,

        /**
        * energy (FOM name: <code>energy</code>).
        * <br>Description from the FOM: Amount of energy left in launcher. Launching a payload would cost some amount of energy
        */
         ENERGY,

        /**
        * name (FOM name: <code>name</code>).
        * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
        */
         NAME,

        /**
        * type (FOM name: <code>type</code>).
        * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
        */
         TYPE,

        /**
        * status (FOM name: <code>status</code>).
        * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
        */
         STATUS,

        /**
        * parentReferenceFrame (FOM name: <code>parent_reference_frame</code>).
        * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
        */
         PARENT_REFERENCE_FRAME,

        /**
        * state (FOM name: <code>state</code>).
        * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
        */
         STATE,

        /**
        * acceleration (FOM name: <code>acceleration</code>).
        * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
        */
         ACCELERATION,

        /**
        * rotationalAcceleration (FOM name: <code>rotational_acceleration</code>).
        * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
        */
         ROTATIONAL_ACCELERATION,

        /**
        * centerOfMass (FOM name: <code>center_of_mass</code>).
        * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
        */
         CENTER_OF_MASS,

        /**
        * bodyWrtStructural (FOM name: <code>body_wrt_structural</code>).
        * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
        */
         BODY_WRT_STRUCTURAL

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

      LIBAPI virtual ~HlaLauncherAttributes() {}
    
      /**
      * Returns true if the <code>position</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: 3-Vector that represents the position of the launcher
      *
      * @return true if <code>position</code> is available.
      */
      LIBAPI virtual bool hasPosition() = 0;

      /**
      * Gets the value of the <code>position</code> attribute.
      *
      * <br>Description from the FOM: 3-Vector that represents the position of the launcher
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
      * <br>Description from the FOM: 3-Vector that represents the position of the launcher
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param defaultValue default value
      *
      * @return the <code>position</code> attribute.
      */
      LIBAPI virtual std::vector</* 3 */ double > getPosition(std::vector</* 3 */ double > defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>position</code> attribute.
      * <br>Description from the FOM: 3-Vector that represents the position of the launcher
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return the time stamped <code>position</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getPositionTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>mass</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: Mass of launcher
      *
      * @return true if <code>mass</code> is available.
      */
      LIBAPI virtual bool hasMass() = 0;

      /**
      * Gets the value of the <code>mass</code> attribute.
      *
      * <br>Description from the FOM: Mass of launcher
      * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      *
      * @return the <code>mass</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual double getMass()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>mass</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: Mass of launcher
      * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      *
      * @param defaultValue default value
      *
      * @return the <code>mass</code> attribute.
      */
      LIBAPI virtual double getMass(double defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>mass</code> attribute.
      * <br>Description from the FOM: Mass of launcher
      * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      *
      * @return the time stamped <code>mass</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< double > getMassTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>energy</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: Amount of energy left in launcher. Launching a payload would cost some amount of energy
      *
      * @return true if <code>energy</code> is available.
      */
      LIBAPI virtual bool hasEnergy() = 0;

      /**
      * Gets the value of the <code>energy</code> attribute.
      *
      * <br>Description from the FOM: Amount of energy left in launcher. Launching a payload would cost some amount of energy
      * <br>Description of the data type from the FOM: A measure of energy. [unit: Joule (J), resolution: NA, accuracy: NA]
      *
      * @return the <code>energy</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual double getEnergy()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>energy</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: Amount of energy left in launcher. Launching a payload would cost some amount of energy
      * <br>Description of the data type from the FOM: A measure of energy. [unit: Joule (J), resolution: NA, accuracy: NA]
      *
      * @param defaultValue default value
      *
      * @return the <code>energy</code> attribute.
      */
      LIBAPI virtual double getEnergy(double defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>energy</code> attribute.
      * <br>Description from the FOM: Amount of energy left in launcher. Launching a payload would cost some amount of energy
      * <br>Description of the data type from the FOM: A measure of energy. [unit: Joule (J), resolution: NA, accuracy: NA]
      *
      * @return the time stamped <code>energy</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< double > getEnergyTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>name</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      *
      * @return true if <code>name</code> is available.
      */
      LIBAPI virtual bool hasName() = 0;

      /**
      * Gets the value of the <code>name</code> attribute.
      *
      * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
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
      * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>name</code> attribute.
      */
      LIBAPI virtual std::wstring getName(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>name</code> attribute.
      * <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>name</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getNameTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>type</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
      *
      * @return true if <code>type</code> is available.
      */
      LIBAPI virtual bool hasType() = 0;

      /**
      * Gets the value of the <code>type</code> attribute.
      *
      * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
      * <br>Description of the data type from the FOM: 
      *
      * @return the <code>type</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::wstring getType()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>type</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>type</code> attribute.
      */
      LIBAPI virtual std::wstring getType(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>type</code> attribute.
      * <br>Description from the FOM: A non-empty string that identifies the entity type. It is not a mandatory field but it can be used to differentiate from a fuel tank and a space vehicle for example.
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>type</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getTypeTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>status</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
      *
      * @return true if <code>status</code> is available.
      */
      LIBAPI virtual bool hasStatus() = 0;

      /**
      * Gets the value of the <code>status</code> attribute.
      *
      * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
      * <br>Description of the data type from the FOM: 
      *
      * @return the <code>status</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::wstring getStatus()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>status</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>status</code> attribute.
      */
      LIBAPI virtual std::wstring getStatus(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>status</code> attribute.
      * <br>Description from the FOM: An informative string that documents the current status of the entity (whatever that might be).
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>status</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getStatusTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>parentReferenceFrame</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
      *
      * @return true if <code>parentReferenceFrame</code> is available.
      */
      LIBAPI virtual bool hasParentReferenceFrame() = 0;

      /**
      * Gets the value of the <code>parentReferenceFrame</code> attribute.
      *
      * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
      * <br>Description of the data type from the FOM: 
      *
      * @return the <code>parentReferenceFrame</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::wstring getParentReferenceFrame()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>parentReferenceFrame</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>parentReferenceFrame</code> attribute.
      */
      LIBAPI virtual std::wstring getParentReferenceFrame(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>parentReferenceFrame</code> attribute.
      * <br>Description from the FOM: The non-empty string that identifies the reference frame with respect to which the kinematic state attributes of this entity are calculated. This string must exactly match the name of some ReferenceFrame instance in the federation.
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>parentReferenceFrame</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getParentReferenceFrameTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>state</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
      *
      * @return true if <code>state</code> is available.
      */
      LIBAPI virtual bool hasState() = 0;

      /**
      * Gets the value of the <code>state</code> attribute.
      *
      * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
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
      * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @param defaultValue default value
      *
      * @return the <code>state</code> attribute.
      */
      LIBAPI virtual LunarSimulation::SpaceTimeCoordinateState getState(LunarSimulation::SpaceTimeCoordinateState defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>state</code> attribute.
      * <br>Description from the FOM: A four dimensional representation of the entity's translational and rotational state with respect to its parent reference frame.
      * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
      *
      * @return the time stamped <code>state</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< LunarSimulation::SpaceTimeCoordinateState > getStateTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>acceleration</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      *
      * @return true if <code>acceleration</code> is available.
      */
      LIBAPI virtual bool hasAcceleration() = 0;

      /**
      * Gets the value of the <code>acceleration</code> attribute.
      *
      * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return the <code>acceleration</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::vector</* 3 */ double > getAcceleration()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>acceleration</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param defaultValue default value
      *
      * @return the <code>acceleration</code> attribute.
      */
      LIBAPI virtual std::vector</* 3 */ double > getAcceleration(std::vector</* 3 */ double > defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>acceleration</code> attribute.
      * <br>Description from the FOM: A 3-vector that specifies the acceleration of the entity body frame origin (i.e., the entity's center of mass) with respect to the parent reference frame. This is the time derivative of the velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the parent frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of a vector velocity of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of  reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return the time stamped <code>acceleration</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getAccelerationTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>rotationalAcceleration</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
      *
      * @return true if <code>rotationalAcceleration</code> is available.
      */
      LIBAPI virtual bool hasRotationalAcceleration() = 0;

      /**
      * Gets the value of the <code>rotationalAcceleration</code> attribute.
      *
      * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
      *
      * @return the <code>rotationalAcceleration</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::vector</* 3 */ double > getRotationalAcceleration()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>rotationalAcceleration</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
      *
      * @param defaultValue default value
      *
      * @return the <code>rotationalAcceleration</code> attribute.
      */
      LIBAPI virtual std::vector</* 3 */ double > getRotationalAcceleration(std::vector</* 3 */ double > defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>rotationalAcceleration</code> attribute.
      * <br>Description from the FOM: A 3-vector that specifies the angular acceleration of the entity body frame with respect to the parent reference frame. This is the time derivative of the angular velocity vector as seen by an observer fixed in the parent frame. The components of this vector are resolved onto the coordinate axes of the entity body frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of an angular velocity vector as seen by an observer fixed in some reference frame. This data type does not specify which angular velocity, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are 
projected.
      *
      * @return the time stamped <code>rotationalAcceleration</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getRotationalAccelerationTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>centerOfMass</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
      *
      * @return true if <code>centerOfMass</code> is available.
      */
      LIBAPI virtual bool hasCenterOfMass() = 0;

      /**
      * Gets the value of the <code>centerOfMass</code> attribute.
      *
      * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return the <code>centerOfMass</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::vector</* 3 */ double > getCenterOfMass()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>centerOfMass</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param defaultValue default value
      *
      * @return the <code>centerOfMass</code> attribute.
      */
      LIBAPI virtual std::vector</* 3 */ double > getCenterOfMass(std::vector</* 3 */ double > defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>centerOfMass</code> attribute.
      * <br>Description from the FOM: A 3-vector that specifies the position of the entity center of mass (the body frame origin) with respect to the origin of the entity's structural frame. The components of this vector are resolved onto the coordinate axes of the structural frame.
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @return the time stamped <code>centerOfMass</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::vector</* 3 */ double > > getCenterOfMassTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>bodyWrtStructural</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
      *
      * @return true if <code>bodyWrtStructural</code> is available.
      */
      LIBAPI virtual bool hasBodyWrtStructural() = 0;

      /**
      * Gets the value of the <code>bodyWrtStructural</code> attribute.
      *
      * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @return the <code>bodyWrtStructural</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::AttitudeQuaternion getBodyWrtStructural()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>bodyWrtStructural</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @param defaultValue default value
      *
      * @return the <code>bodyWrtStructural</code> attribute.
      */
      LIBAPI virtual LunarSimulation::AttitudeQuaternion getBodyWrtStructural(LunarSimulation::AttitudeQuaternion defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>bodyWrtStructural</code> attribute.
      * <br>Description from the FOM: An attitude quaternion that specifies the orientation of an entity's body frame with respect to the entity's structural frame.  This attitude quaternion should never change.  If not specified, an identity quaternion is assumed.
      * <br>Description of the data type from the FOM: This is a quaternion quantifying the orientation of a 'subject' reference frame with respect to some other 'referent' frame. Quaternions consist of one scalar component and a 3-element vector component and can be denoted Q = (s, V), where s is a scalar and V is a vector (x, y, z). Confusion often arises regarding the meaning of the quaternion. (There are several similar but incompatible conventions.) This data type defines a so-called 'left unit transformation quaternion'. It may be used to transform the elements of a vector V_R = (xR, yR, zR) resolved in the referent frame's coordinate axes into the corresponding elements of a vector V_S = (xS, yS, zS) resolved in the subject frame's coordinate axes (i.e. determine the components of the same vector in another coordinate system). The quaternion transformation formula is (0, V_A) = Q . (0, V_B) . Q*, where '.' denotes quaternion multiplication and * denotes quaternion conjugation. The formula for multiplication of the quaternion Q1 = (s1, V1) where V1 is the vector (x1, y1, z1) by the quaternion Q2 = (s2, V2) where V2 is the vector (x2, y2, z2) is Q3 = Q1 . Q2 = (s3, V3) where s3 = s1 s2 - (x1 x2 + y1 y2 + z1 z2) and V3 = (x3, y3, z3) with x3 = s1 x2 + s2 x1 + (y1 z2 - z1 y2), y3 = s1 y2 + s2 y1 + (z1 x2 - x1 z2) and z3 = s1 z2 + s2 z1 + (x1 y2 - y1 x2). The formula for conjugation of the quaternion Q = (s, V), where V is the vector (x, y, z) is Q* = (s, -V) = (s, (-x, -y, -z)).
      *
      * @return the time stamped <code>bodyWrtStructural</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< LunarSimulation::AttitudeQuaternion > getBodyWrtStructuralTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
   };
}
#endif
