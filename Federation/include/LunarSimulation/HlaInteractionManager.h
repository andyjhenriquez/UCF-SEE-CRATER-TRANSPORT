/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
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
   *  Interface for creating a HlaStartStopInteraction
   */
   class HlaStartStopInteraction : private LunarSimulation::noncopyable {
   public:

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
      * <tr><td>MODE_TRANSITION_REQUEST</td><td>ModeTransitionRequest</td><td><code>HLAinteractionRoot.ModeTransitionRequest</code></td></tr>
      *</table>
      */
      enum Interaction {
         /** HLAinteractionRoot (FOM name: <code>HLAinteractionRoot</code>) */
         HLAINTERACTION_ROOT,
         /** StartStop (FOM name: <code>HLAinteractionRoot.Start_Stop</code>) */
         START_STOP,
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
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual void sendStartStop(
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified timestamp.
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
      LIBAPI virtual void sendStartStop(
          HlaTimeStampPtr timeStamp
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified logicaltime.
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
      LIBAPI virtual void sendStartStop(
          HlaLogicalTimePtr logicalTime
      ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException,
                    HlaRtiException,HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified timestamp and logicaltime.
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
      LIBAPI virtual void sendStartStop(
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
