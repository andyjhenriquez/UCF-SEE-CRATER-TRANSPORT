/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAINTERACTIONMANAGER_H
#define DEVELOPER_STUDIO_HLAINTERACTIONMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <set>

#include <iostream>

#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaInteractionListener.h>

namespace LunarSimulation {


  /**
   *  Interface for creating a HlaHLAinteractionRootInteraction
   */
   class HlaHLAinteractionRootInteraction : private LunarSimulation::noncopyable {
   public:

     /**
      * Send the HlaHLAinteractionRootInteraction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction()
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, 
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

     /**
      * Send the HlaHLAinteractionRootInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaHLAinteractionRootInteraction with a specified timestamp
      *
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaHLAinteractionRootInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      LIBAPI virtual ~HlaHLAinteractionRootInteraction() {}
   };

   /**
    * Interface for getting HLAinteractionRoot.Start_Stop parameters
    */
    class HlaStartStopParameters : private LunarSimulation::noncopyable {
    public:
    
      /**
       * Returns true if a valid value for haltSimulation is available.
       *
       * <br>Description from the FOM: Stop simulation if true
       *
       * @return true if haltSimulation is valid
       */
       LIBAPI virtual bool hasHaltSimulation() = 0;

      /**
       * Returns the value of the haltSimulation parameter.
       *
       * <br>Description from the FOM: Stop simulation if true
       * <br>Description of the data type from the FOM: 
       *
       * @return the haltSimulation
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual bool getHaltSimulation() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the haltSimulation parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Stop simulation if true
       * <br>Description of the data type from the FOM: 
       *
       * @param defaultValue default value
       *
       * @return the haltSimulation or <code>defaultValue</code> if not set
       */
       LIBAPI virtual bool getHaltSimulation(bool defaultValue) = 0;
    
      /**
       * Returns true if a valid value for exitSimulation is available.
       *
       * <br>Description from the FOM: Exit simulation if true
       *
       * @return true if exitSimulation is valid
       */
       LIBAPI virtual bool hasExitSimulation() = 0;

      /**
       * Returns the value of the exitSimulation parameter.
       *
       * <br>Description from the FOM: Exit simulation if true
       * <br>Description of the data type from the FOM: 
       *
       * @return the exitSimulation
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual bool getExitSimulation() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the exitSimulation parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Exit simulation if true
       * <br>Description of the data type from the FOM: 
       *
       * @param defaultValue default value
       *
       * @return the exitSimulation or <code>defaultValue</code> if not set
       */
       LIBAPI virtual bool getExitSimulation(bool defaultValue) = 0;

       /**
       * Get the HlaFederateId for the federate that sent this interaction
       *
       * @return The federate id for the federate that sent this interaction
       */
       LIBAPI virtual HlaFederateIdPtr getProducingFederate() const = 0;

       /**
       * Check if the parameters are within the interest defined for this interaction.
       *
       * @return true if the parameters are within interest
       */
       LIBAPI virtual bool isWithinInterest() const = 0;

       /**
       * Destructor
       */
       LIBAPI virtual ~HlaStartStopParameters() {}
    };

    LIBAPI std::wostream & operator << (std::wostream &, HlaStartStopParameters &);
    LIBAPI std::ostream & operator << (std::ostream &, HlaStartStopParameters &);

  /**
   *  Interface for creating a HlaStartStopInteraction
   */
   class HlaStartStopInteraction : private LunarSimulation::noncopyable {
   public:

     /**
      * Sets the value for haltSimulation.
      * <br>Description from the FOM: Stop simulation if true
      * <br>Description of the data type from the FOM: 
      *
      * @param haltSimulation value to set
      */
      LIBAPI virtual void setHaltSimulation(bool haltSimulation) = 0;

     /**
      * Sets the value for exitSimulation.
      * <br>Description from the FOM: Exit simulation if true
      * <br>Description of the data type from the FOM: 
      *
      * @param exitSimulation value to set
      */
      LIBAPI virtual void setExitSimulation(bool exitSimulation) = 0;

     /**
      * Send the HlaStartStopInteraction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction()
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, 
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

     /**
      * Send the HlaStartStopInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaStartStopInteraction with a specified timestamp
      *
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaStartStopInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      LIBAPI virtual ~HlaStartStopInteraction() {}
   };

   /**
    * Interface for getting HLAinteractionRoot.LoadScenario parameters
    */
    class HlaLoadScenarioParameters : private LunarSimulation::noncopyable {
    public:
    
      /**
       * Returns true if a valid value for moonFriction is available.
       *
       * <br>Description from the FOM: Friction coefficient for surface of the moon
       *
       * @return true if moonFriction is valid
       */
       LIBAPI virtual bool hasMoonFriction() = 0;

      /**
       * Returns the value of the moonFriction parameter.
       *
       * <br>Description from the FOM: Friction coefficient for surface of the moon
       * <br>Description of the data type from the FOM: Double-precision floating point number
       *
       * @return the moonFriction
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual double getMoonFriction() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the moonFriction parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Friction coefficient for surface of the moon
       * <br>Description of the data type from the FOM: Double-precision floating point number
       *
       * @param defaultValue default value
       *
       * @return the moonFriction or <code>defaultValue</code> if not set
       */
       LIBAPI virtual double getMoonFriction(double defaultValue) = 0;
    
      /**
       * Returns true if a valid value for roverInitialPosition is available.
       *
       * <br>Description from the FOM: Start postion for rover
       *
       * @return true if roverInitialPosition is valid
       */
       LIBAPI virtual bool hasRoverInitialPosition() = 0;

      /**
       * Returns the value of the roverInitialPosition parameter.
       *
       * <br>Description from the FOM: Start postion for rover
       * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @return the roverInitialPosition
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getRoverInitialPosition() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the roverInitialPosition parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Start postion for rover
       * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @param defaultValue default value
       *
       * @return the roverInitialPosition or <code>defaultValue</code> if not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getRoverInitialPosition(std::vector</* 3 */ double > defaultValue) = 0;
    
      /**
       * Returns true if a valid value for roverHealth is available.
       *
       * <br>Description from the FOM: Health of rover
       *
       * @return true if roverHealth is valid
       */
       LIBAPI virtual bool hasRoverHealth() = 0;

      /**
       * Returns the value of the roverHealth parameter.
       *
       * <br>Description from the FOM: Health of rover
       * <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
       *
       * @return the roverHealth
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual double getRoverHealth() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the roverHealth parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Health of rover
       * <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
       *
       * @param defaultValue default value
       *
       * @return the roverHealth or <code>defaultValue</code> if not set
       */
       LIBAPI virtual double getRoverHealth(double defaultValue) = 0;
    
      /**
       * Returns true if a valid value for roverMass is available.
       *
       * <br>Description from the FOM: Mass of rover
       *
       * @return true if roverMass is valid
       */
       LIBAPI virtual bool hasRoverMass() = 0;

      /**
       * Returns the value of the roverMass parameter.
       *
       * <br>Description from the FOM: Mass of rover
       * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
       *
       * @return the roverMass
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual double getRoverMass() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the roverMass parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Mass of rover
       * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
       *
       * @param defaultValue default value
       *
       * @return the roverMass or <code>defaultValue</code> if not set
       */
       LIBAPI virtual double getRoverMass(double defaultValue) = 0;
    
      /**
       * Returns true if a valid value for payloadMass is available.
       *
       * <br>Description from the FOM: Mass of payload
       *
       * @return true if payloadMass is valid
       */
       LIBAPI virtual bool hasPayloadMass() = 0;

      /**
       * Returns the value of the payloadMass parameter.
       *
       * <br>Description from the FOM: Mass of payload
       * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
       *
       * @return the payloadMass
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual double getPayloadMass() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the payloadMass parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Mass of payload
       * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
       *
       * @param defaultValue default value
       *
       * @return the payloadMass or <code>defaultValue</code> if not set
       */
       LIBAPI virtual double getPayloadMass(double defaultValue) = 0;
    
      /**
       * Returns true if a valid value for launchSpeedVector is available.
       *
       * <br>Description from the FOM: Initial speed of payload
       *
       * @return true if launchSpeedVector is valid
       */
       LIBAPI virtual bool hasLaunchSpeedVector() = 0;

      /**
       * Returns the value of the launchSpeedVector parameter.
       *
       * <br>Description from the FOM: Initial speed of payload
       * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @return the launchSpeedVector
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getLaunchSpeedVector() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the launchSpeedVector parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Initial speed of payload
       * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @param defaultValue default value
       *
       * @return the launchSpeedVector or <code>defaultValue</code> if not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getLaunchSpeedVector(std::vector</* 3 */ double > defaultValue) = 0;
    
      /**
       * Returns true if a valid value for roverStartPosition is available.
       *
       * <br>Description from the FOM: Rover Start Position
       *
       * @return true if roverStartPosition is valid
       */
       LIBAPI virtual bool hasRoverStartPosition() = 0;

      /**
       * Returns the value of the roverStartPosition parameter.
       *
       * <br>Description from the FOM: Rover Start Position
       * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @return the roverStartPosition
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getRoverStartPosition() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the roverStartPosition parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Rover Start Position
       * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @param defaultValue default value
       *
       * @return the roverStartPosition or <code>defaultValue</code> if not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getRoverStartPosition(std::vector</* 3 */ double > defaultValue) = 0;
    
      /**
       * Returns true if a valid value for simulationScenario is available.
       *
       * <br>Description from the FOM: Which scenario to load in
       *
       * @return true if simulationScenario is valid
       */
       LIBAPI virtual bool hasSimulationScenario() = 0;

      /**
       * Returns the value of the simulationScenario parameter.
       *
       * <br>Description from the FOM: Which scenario to load in
       * <br>Description of the data type from the FOM: 
       *
       * @return the simulationScenario
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual std::wstring getSimulationScenario() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the simulationScenario parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Which scenario to load in
       * <br>Description of the data type from the FOM: 
       *
       * @param defaultValue default value
       *
       * @return the simulationScenario or <code>defaultValue</code> if not set
       */
       LIBAPI virtual std::wstring getSimulationScenario(std::wstring defaultValue) = 0;
    
      /**
       * Returns true if a valid value for launcherPosition is available.
       *
       * <br>Description from the FOM: Position of Launcher
       *
       * @return true if launcherPosition is valid
       */
       LIBAPI virtual bool hasLauncherPosition() = 0;

      /**
       * Returns the value of the launcherPosition parameter.
       *
       * <br>Description from the FOM: Position of Launcher
       * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @return the launcherPosition
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getLauncherPosition() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the launcherPosition parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Position of Launcher
       * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @param defaultValue default value
       *
       * @return the launcherPosition or <code>defaultValue</code> if not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getLauncherPosition(std::vector</* 3 */ double > defaultValue) = 0;
    
      /**
       * Returns true if a valid value for launchForce is available.
       *
       * <br>Description from the FOM: Launch force for payload exit
       *
       * @return true if launchForce is valid
       */
       LIBAPI virtual bool hasLaunchForce() = 0;

      /**
       * Returns the value of the launchForce parameter.
       *
       * <br>Description from the FOM: Launch force for payload exit
       * <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @return the launchForce
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getLaunchForce() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the launchForce parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: Launch force for payload exit
       * <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
       *
       * @param defaultValue default value
       *
       * @return the launchForce or <code>defaultValue</code> if not set
       */
       LIBAPI virtual std::vector</* 3 */ double > getLaunchForce(std::vector</* 3 */ double > defaultValue) = 0;

       /**
       * Get the HlaFederateId for the federate that sent this interaction
       *
       * @return The federate id for the federate that sent this interaction
       */
       LIBAPI virtual HlaFederateIdPtr getProducingFederate() const = 0;

       /**
       * Check if the parameters are within the interest defined for this interaction.
       *
       * @return true if the parameters are within interest
       */
       LIBAPI virtual bool isWithinInterest() const = 0;

       /**
       * Destructor
       */
       LIBAPI virtual ~HlaLoadScenarioParameters() {}
    };

    LIBAPI std::wostream & operator << (std::wostream &, HlaLoadScenarioParameters &);
    LIBAPI std::ostream & operator << (std::ostream &, HlaLoadScenarioParameters &);

  /**
   *  Interface for creating a HlaLoadScenarioInteraction
   */
   class HlaLoadScenarioInteraction : private LunarSimulation::noncopyable {
   public:

     /**
      * Sets the value for moonFriction.
      * <br>Description from the FOM: Friction coefficient for surface of the moon
      * <br>Description of the data type from the FOM: Double-precision floating point number
      *
      * @param moonFriction value to set
      */
      LIBAPI virtual void setMoonFriction(double moonFriction) = 0;

     /**
      * Sets the value for roverInitialPosition.
      * <br>Description from the FOM: Start postion for rover
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param roverInitialPosition value to set
      */
      LIBAPI virtual void setRoverInitialPosition(std::vector</* 3 */ double > roverInitialPosition) = 0;

     /**
      * Sets the value for roverHealth.
      * <br>Description from the FOM: Health of rover
      * <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
      *
      * @param roverHealth value to set
      */
      LIBAPI virtual void setRoverHealth(double roverHealth) = 0;

     /**
      * Sets the value for roverMass.
      * <br>Description from the FOM: Mass of rover
      * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      *
      * @param roverMass value to set
      */
      LIBAPI virtual void setRoverMass(double roverMass) = 0;

     /**
      * Sets the value for payloadMass.
      * <br>Description from the FOM: Mass of payload
      * <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      *
      * @param payloadMass value to set
      */
      LIBAPI virtual void setPayloadMass(double payloadMass) = 0;

     /**
      * Sets the value for launchSpeedVector.
      * <br>Description from the FOM: Initial speed of payload
      * <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param launchSpeedVector value to set
      */
      LIBAPI virtual void setLaunchSpeedVector(std::vector</* 3 */ double > launchSpeedVector) = 0;

     /**
      * Sets the value for roverStartPosition.
      * <br>Description from the FOM: Rover Start Position
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param roverStartPosition value to set
      */
      LIBAPI virtual void setRoverStartPosition(std::vector</* 3 */ double > roverStartPosition) = 0;

     /**
      * Sets the value for simulationScenario.
      * <br>Description from the FOM: Which scenario to load in
      * <br>Description of the data type from the FOM: 
      *
      * @param simulationScenario value to set
      */
      LIBAPI virtual void setSimulationScenario(std::wstring simulationScenario) = 0;

     /**
      * Sets the value for launcherPosition.
      * <br>Description from the FOM: Position of Launcher
      * <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param launcherPosition value to set
      */
      LIBAPI virtual void setLauncherPosition(std::vector</* 3 */ double > launcherPosition) = 0;

     /**
      * Sets the value for launchForce.
      * <br>Description from the FOM: Launch force for payload exit
      * <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @param launchForce value to set
      */
      LIBAPI virtual void setLaunchForce(std::vector</* 3 */ double > launchForce) = 0;

     /**
      * Send the HlaLoadScenarioInteraction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction()
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, 
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

     /**
      * Send the HlaLoadScenarioInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaLoadScenarioInteraction with a specified timestamp
      *
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaLoadScenarioInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      LIBAPI virtual ~HlaLoadScenarioInteraction() {}
   };

   /**
    * Interface for getting HLAinteractionRoot.ModeTransitionRequest parameters
    */
    class HlaModeTransitionRequestParameters : private LunarSimulation::noncopyable {
    public:
    
      /**
       * Returns true if a valid value for executionMode is available.
       *
       * <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
       *
       * @return true if executionMode is valid
       */
       LIBAPI virtual bool hasExecutionMode() = 0;

      /**
       * Returns the value of the executionMode parameter.
       *
       * <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
       * <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
       *
       * @return the executionMode
       *
       * @throws HlaValueNotSetException if value was not set
       */
       LIBAPI virtual MTRMode::MTRMode getExecutionMode() THROW_SPEC (HlaValueNotSetException) = 0;

      /**
       * Returns the value of the executionMode parameter, or <code>defaultValue</code> if value was not set.
       *
       * <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
       * <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
       *
       * @param defaultValue default value
       *
       * @return the executionMode or <code>defaultValue</code> if not set
       */
       LIBAPI virtual MTRMode::MTRMode getExecutionMode(MTRMode::MTRMode defaultValue) = 0;

       /**
       * Get the HlaFederateId for the federate that sent this interaction
       *
       * @return The federate id for the federate that sent this interaction
       */
       LIBAPI virtual HlaFederateIdPtr getProducingFederate() const = 0;

       /**
       * Check if the parameters are within the interest defined for this interaction.
       *
       * @return true if the parameters are within interest
       */
       LIBAPI virtual bool isWithinInterest() const = 0;

       /**
       * Destructor
       */
       LIBAPI virtual ~HlaModeTransitionRequestParameters() {}
    };

    LIBAPI std::wostream & operator << (std::wostream &, HlaModeTransitionRequestParameters &);
    LIBAPI std::ostream & operator << (std::ostream &, HlaModeTransitionRequestParameters &);

  /**
   *  Interface for creating a HlaModeTransitionRequestInteraction
   */
   class HlaModeTransitionRequestInteraction : private LunarSimulation::noncopyable {
   public:

     /**
      * Sets the value for executionMode.
      * <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
      * <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
      *
      * @param executionMode value to set
      */
      LIBAPI virtual void setExecutionMode(MTRMode::MTRMode executionMode) = 0;

     /**
      * Send the HlaModeTransitionRequestInteraction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction()
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, 
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

     /**
      * Send the HlaModeTransitionRequestInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaModeTransitionRequestInteraction with a specified timestamp
      *
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Send the HlaModeTransitionRequestInteraction with a specified timestamp
      *
      * @param timestamp timestamp to send for this interaction
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendInteraction(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                  HlaRtiException,HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      LIBAPI virtual ~HlaModeTransitionRequestInteraction() {}
   };

   /**
   * Manager used to manage all interactions.
   */
   class HlaInteractionManager : private LunarSimulation::noncopyable {

   public:

      /**
      * An enumeration of all interactions
      *
      *<table>
      * <caption>All interactions</caption>
      * <tr><td><b>Enum constant</b></td><td><b>C++ name</b></td><td><b>FOM name</b></td></tr>
      * <tr><td>HLAINTERACTION_ROOT</td><td>HLAinteractionRoot</td><td><code>HLAinteractionRoot</code></td></tr>
      * <tr><td>START_STOP</td><td>StartStop</td><td><code>HLAinteractionRoot.Start_Stop</code></td></tr>
      * <tr><td>LOAD_SCENARIO</td><td>LoadScenario</td><td><code>HLAinteractionRoot.LoadScenario</code></td></tr>
      * <tr><td>MODE_TRANSITION_REQUEST</td><td>ModeTransitionRequest</td><td><code>HLAinteractionRoot.ModeTransitionRequest</code></td></tr>
      *</table>
      */
      enum Interaction {
         /** HLAinteractionRoot (FOM name: <code>HLAinteractionRoot</code>) */
         HLAINTERACTION_ROOT,
         /** StartStop (FOM name: <code>HLAinteractionRoot.Start_Stop</code>) */
         START_STOP,
         /** LoadScenario (FOM name: <code>HLAinteractionRoot.LoadScenario</code>) */
         LOAD_SCENARIO,
         /** ModeTransitionRequest (FOM name: <code>HLAinteractionRoot.ModeTransitionRequest</code>) */
         MODE_TRANSITION_REQUEST
      };

      /**
      * Gets the HLA name of the interaction.
      *
      * @param interaction the interaction enum
      *
      * @return The name of the interaction. An empty string will be returned if the interaction does not exist.
      */
      LIBAPI virtual std::wstring getHlaName(Interaction interaction) = 0;

      /**
      * Finds the interaction specified in the parameter interactionName.
      * The found enumeration will be stored in the parameter interaction.
      *
      * @param interaction the interaction enum (out parameter)
      * @param interactionHlaName HLA name of the interaction to find 
      *
      * @return true if the interaction was found, false otherwise.
      */
      LIBAPI virtual bool find(Interaction& interaction, std::wstring interactionHlaName) = 0;

      LIBAPI virtual ~HlaInteractionManager() {}

      /**
      * Sends the <code>HLAinteractionRoot</code> interaction.
      *
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendHLAinteractionRoot(
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot</code> interaction with a specified timestamp.
      *
      * @param timeStamp timestamp to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendHLAinteractionRoot(
          HlaTimeStampPtr timeStamp
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot</code> interaction with a specified logicaltime.
      *
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendHLAinteractionRoot(
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot</code> interaction with a specified timestamp and logicaltime.
      *
      * @param timeStamp timestamp to send with the interaction
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendHLAinteractionRoot(
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;


      /**
      * Get a HlaHLAinteractionRootInteraction
      *
      * @return An interaction
      */
      LIBAPI virtual HlaHLAinteractionRootInteractionPtr getHlaHLAinteractionRootInteraction() = 0;

      /**
      * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction.
      *
      * @param haltSimulation represents the <code>HaltSimulation</code> from the FOM.
      *        <br>Description from the FOM: Stop simulation if true
      *        <br>Description of the data type from the FOM: 
      * @param exitSimulation represents the <code>Exit_Simulation</code> from the FOM.
      *        <br>Description from the FOM: Exit simulation if true
      *        <br>Description of the data type from the FOM: 
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendStartStop(
          bool haltSimulation,
          bool exitSimulation
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified timestamp.
      *
      * @param haltSimulation represents the <code>HaltSimulation</code> from the FOM.
      *        <br>Description from the FOM: Stop simulation if true
      *        <br>Description of the data type from the FOM: 
      * @param exitSimulation represents the <code>Exit_Simulation</code> from the FOM.
      *        <br>Description from the FOM: Exit simulation if true
      *        <br>Description of the data type from the FOM: 
      * @param timeStamp timestamp to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendStartStop(
          bool haltSimulation,
          bool exitSimulation,
          HlaTimeStampPtr timeStamp
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified logicaltime.
      *
      * @param haltSimulation represents the <code>HaltSimulation</code> from the FOM.
      *        <br>Description from the FOM: Stop simulation if true
      *        <br>Description of the data type from the FOM: 
      * @param exitSimulation represents the <code>Exit_Simulation</code> from the FOM.
      *        <br>Description from the FOM: Exit simulation if true
      *        <br>Description of the data type from the FOM: 
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendStartStop(
          bool haltSimulation,
          bool exitSimulation,
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified timestamp and logicaltime.
      *
      * @param haltSimulation represents the <code>HaltSimulation</code> from the FOM.
      *        <br>Description from the FOM: Stop simulation if true
      *        <br>Description of the data type from the FOM: 
      * @param exitSimulation represents the <code>Exit_Simulation</code> from the FOM.
      *        <br>Description from the FOM: Exit simulation if true
      *        <br>Description of the data type from the FOM: 
      * @param timeStamp timestamp to send with the interaction
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendStartStop(
          bool haltSimulation,
          bool exitSimulation,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;


      /**
      * Get a HlaStartStopInteraction
      *
      * @return An interaction
      */
      LIBAPI virtual HlaStartStopInteractionPtr getHlaStartStopInteraction() = 0;

      /**
      * Sends the <code>HLAinteractionRoot.LoadScenario</code> interaction.
      *
      * @param moonFriction represents the <code>MoonFriction</code> from the FOM.
      *        <br>Description from the FOM: Friction coefficient for surface of the moon
      *        <br>Description of the data type from the FOM: Double-precision floating point number
      * @param roverInitialPosition represents the <code>RoverInitialPosition</code> from the FOM.
      *        <br>Description from the FOM: Start postion for rover
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverHealth represents the <code>RoverHealth</code> from the FOM.
      *        <br>Description from the FOM: Health of rover
      *        <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
      * @param roverMass represents the <code>RoverMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of rover
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param payloadMass represents the <code>PayloadMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of payload
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param launchSpeedVector represents the <code>LaunchSpeedVector</code> from the FOM.
      *        <br>Description from the FOM: Initial speed of payload
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverStartPosition represents the <code>RoverStartPosition</code> from the FOM.
      *        <br>Description from the FOM: Rover Start Position
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param simulationScenario represents the <code>SimulationScenario</code> from the FOM.
      *        <br>Description from the FOM: Which scenario to load in
      *        <br>Description of the data type from the FOM: 
      * @param launcherPosition represents the <code>LauncherPosition</code> from the FOM.
      *        <br>Description from the FOM: Position of Launcher
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param launchForce represents the <code>LaunchForce</code> from the FOM.
      *        <br>Description from the FOM: Launch force for payload exit
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendLoadScenario(
          double moonFriction,
          std::vector</* 3 */ double > roverInitialPosition,
          double roverHealth,
          double roverMass,
          double payloadMass,
          std::vector</* 3 */ double > launchSpeedVector,
          std::vector</* 3 */ double > roverStartPosition,
          std::wstring simulationScenario,
          std::vector</* 3 */ double > launcherPosition,
          std::vector</* 3 */ double > launchForce
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.LoadScenario</code> interaction with a specified timestamp.
      *
      * @param moonFriction represents the <code>MoonFriction</code> from the FOM.
      *        <br>Description from the FOM: Friction coefficient for surface of the moon
      *        <br>Description of the data type from the FOM: Double-precision floating point number
      * @param roverInitialPosition represents the <code>RoverInitialPosition</code> from the FOM.
      *        <br>Description from the FOM: Start postion for rover
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverHealth represents the <code>RoverHealth</code> from the FOM.
      *        <br>Description from the FOM: Health of rover
      *        <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
      * @param roverMass represents the <code>RoverMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of rover
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param payloadMass represents the <code>PayloadMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of payload
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param launchSpeedVector represents the <code>LaunchSpeedVector</code> from the FOM.
      *        <br>Description from the FOM: Initial speed of payload
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverStartPosition represents the <code>RoverStartPosition</code> from the FOM.
      *        <br>Description from the FOM: Rover Start Position
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param simulationScenario represents the <code>SimulationScenario</code> from the FOM.
      *        <br>Description from the FOM: Which scenario to load in
      *        <br>Description of the data type from the FOM: 
      * @param launcherPosition represents the <code>LauncherPosition</code> from the FOM.
      *        <br>Description from the FOM: Position of Launcher
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param launchForce represents the <code>LaunchForce</code> from the FOM.
      *        <br>Description from the FOM: Launch force for payload exit
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param timeStamp timestamp to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendLoadScenario(
          double moonFriction,
          std::vector</* 3 */ double > roverInitialPosition,
          double roverHealth,
          double roverMass,
          double payloadMass,
          std::vector</* 3 */ double > launchSpeedVector,
          std::vector</* 3 */ double > roverStartPosition,
          std::wstring simulationScenario,
          std::vector</* 3 */ double > launcherPosition,
          std::vector</* 3 */ double > launchForce,
          HlaTimeStampPtr timeStamp
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.LoadScenario</code> interaction with a specified logicaltime.
      *
      * @param moonFriction represents the <code>MoonFriction</code> from the FOM.
      *        <br>Description from the FOM: Friction coefficient for surface of the moon
      *        <br>Description of the data type from the FOM: Double-precision floating point number
      * @param roverInitialPosition represents the <code>RoverInitialPosition</code> from the FOM.
      *        <br>Description from the FOM: Start postion for rover
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverHealth represents the <code>RoverHealth</code> from the FOM.
      *        <br>Description from the FOM: Health of rover
      *        <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
      * @param roverMass represents the <code>RoverMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of rover
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param payloadMass represents the <code>PayloadMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of payload
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param launchSpeedVector represents the <code>LaunchSpeedVector</code> from the FOM.
      *        <br>Description from the FOM: Initial speed of payload
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverStartPosition represents the <code>RoverStartPosition</code> from the FOM.
      *        <br>Description from the FOM: Rover Start Position
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param simulationScenario represents the <code>SimulationScenario</code> from the FOM.
      *        <br>Description from the FOM: Which scenario to load in
      *        <br>Description of the data type from the FOM: 
      * @param launcherPosition represents the <code>LauncherPosition</code> from the FOM.
      *        <br>Description from the FOM: Position of Launcher
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param launchForce represents the <code>LaunchForce</code> from the FOM.
      *        <br>Description from the FOM: Launch force for payload exit
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendLoadScenario(
          double moonFriction,
          std::vector</* 3 */ double > roverInitialPosition,
          double roverHealth,
          double roverMass,
          double payloadMass,
          std::vector</* 3 */ double > launchSpeedVector,
          std::vector</* 3 */ double > roverStartPosition,
          std::wstring simulationScenario,
          std::vector</* 3 */ double > launcherPosition,
          std::vector</* 3 */ double > launchForce,
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.LoadScenario</code> interaction with a specified timestamp and logicaltime.
      *
      * @param moonFriction represents the <code>MoonFriction</code> from the FOM.
      *        <br>Description from the FOM: Friction coefficient for surface of the moon
      *        <br>Description of the data type from the FOM: Double-precision floating point number
      * @param roverInitialPosition represents the <code>RoverInitialPosition</code> from the FOM.
      *        <br>Description from the FOM: Start postion for rover
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverHealth represents the <code>RoverHealth</code> from the FOM.
      *        <br>Description from the FOM: Health of rover
      *        <br>Description of the data type from the FOM: Scalar representing health [unit: NA]
      * @param roverMass represents the <code>RoverMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of rover
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param payloadMass represents the <code>PayloadMass</code> from the FOM.
      *        <br>Description from the FOM: Mass of payload
      *        <br>Description of the data type from the FOM: A measurement of mass. [unit: kilogram (kg), resolution: NA, accuracy: NA]
      * @param launchSpeedVector represents the <code>LaunchSpeedVector</code> from the FOM.
      *        <br>Description from the FOM: Initial speed of payload
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the time derivative of the vector position of some point with respect to another as seen by an observer fixed in some reference frame. This data type does not specify which points are involved, nor does it specify the observer frame of reference, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param roverStartPosition represents the <code>RoverStartPosition</code> from the FOM.
      *        <br>Description from the FOM: Rover Start Position
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param simulationScenario represents the <code>SimulationScenario</code> from the FOM.
      *        <br>Description from the FOM: Which scenario to load in
      *        <br>Description of the data type from the FOM: 
      * @param launcherPosition represents the <code>LauncherPosition</code> from the FOM.
      *        <br>Description from the FOM: Position of Launcher
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the translational position of one point with respect to another. This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param launchForce represents the <code>LaunchForce</code> from the FOM.
      *        <br>Description from the FOM: Launch force for payload exit
      *        <br>Description of the data type from the FOM: A 3-vector that specifies the vector force.  This data type does not specify which points are involved, nor does it specify the coordinate axes onto which the three components of the vector are projected.
      * @param timeStamp timestamp to send with the interaction
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendLoadScenario(
          double moonFriction,
          std::vector</* 3 */ double > roverInitialPosition,
          double roverHealth,
          double roverMass,
          double payloadMass,
          std::vector</* 3 */ double > launchSpeedVector,
          std::vector</* 3 */ double > roverStartPosition,
          std::wstring simulationScenario,
          std::vector</* 3 */ double > launcherPosition,
          std::vector</* 3 */ double > launchForce,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;


      /**
      * Get a HlaLoadScenarioInteraction
      *
      * @return An interaction
      */
      LIBAPI virtual HlaLoadScenarioInteractionPtr getHlaLoadScenarioInteraction() = 0;

      /**
      * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction.
      *
      * @param executionMode represents the <code>execution_mode</code> from the FOM.
      *        <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
      *        <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendModeTransitionRequest(
          MTRMode::MTRMode executionMode
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction with a specified timestamp.
      *
      * @param executionMode represents the <code>execution_mode</code> from the FOM.
      *        <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
      *        <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
      * @param timeStamp timestamp to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendModeTransitionRequest(
          MTRMode::MTRMode executionMode,
          HlaTimeStampPtr timeStamp
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction with a specified logicaltime.
      *
      * @param executionMode represents the <code>execution_mode</code> from the FOM.
      *        <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
      *        <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendModeTransitionRequest(
          MTRMode::MTRMode executionMode,
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction with a specified timestamp and logicaltime.
      *
      * @param executionMode represents the <code>execution_mode</code> from the FOM.
      *        <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
      *        <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
      * @param timeStamp timestamp to send with the interaction
      * @param logicalTime logical time to send with the interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendModeTransitionRequest(
          MTRMode::MTRMode executionMode,
          HlaTimeStampPtr timeStamp,
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;


      /**
      * Get a HlaModeTransitionRequestInteraction
      *
      * @return An interaction
      */
      LIBAPI virtual HlaModeTransitionRequestInteractionPtr getHlaModeTransitionRequestInteraction() = 0;
    
      /**
      * Add an interaction listener.
      *
      * @param listener listener to add
      */
      LIBAPI virtual void addHlaInteractionListener(HlaInteractionListenerPtr listener) = 0;

      /**
      * Remove an interaction listener.
      *
      * @param listener listener to remove
      */
      LIBAPI virtual void removeHlaInteractionListener(HlaInteractionListenerPtr listener) = 0;

      /**
       * Enables or disables an interaction.
       * The interaction is enabled by default. The state can only be changed when not connected.
       * When an interaction is disabled it will act as disconnected,
       * ie throws HlaNotConnectedException.
       *
       * @param enabled <code>true</code> to enable the interaction, otherwise <code>false</code>
       * @param interaction the interaction to change
       */
      LIBAPI virtual void setEnabled(bool enabled, Interaction interaction) = 0;

      /**
       * Enables or disables a set of interactions.
       * The interactions are enabled by default. The state can only be changed when not connected.
       * When an interaction is disabled it will act as disconnected,
       * ie throws HlaNotConnectedException.
       *
       * @param enabled <code>true</code> to enable the interactions, otherwise <code>false</code>
       * @param interactions the interactions to change
       */
      LIBAPI virtual void setEnabled(bool enabled, std::set<Interaction> interactions) = 0;

      /**
       * Enables a set of interactions if they are available in the FOM at runtime.
       * The interactions are enabled by default. The state can only be changed when not connected.
       * When an interaction is disabled it will act as disconnected,
       * ie throws HlaNotConnectedException.
       *
       * @param interactions the interactions to change
       */
       LIBAPI virtual void setEnabledIfAvailableInFom(std::set<Interaction> interactions) = 0;

      /**
       * Check if an interaction is actually enabled when connected.
       * An interaction may be disabled with the <code>setEnabled(false, ...)</code> function, or it may be configured
       * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom(...)</code> function and
       * then not available in the FOM at runtime.
       * <p>
       * This method should only be used when connected, it will always return <code>false</code>
       * when not connected.
       *
       * @param interaction the interaction to check
       *
       * @return <code>true</code> if connected and the interaction is enabled.
       */
      LIBAPI virtual bool isEnabled(Interaction interaction) = 0;
   };
}
#endif
