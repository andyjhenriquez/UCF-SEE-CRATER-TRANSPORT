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

import core.datatypes.MTRMode;
import core.exceptions.*;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;


/**
 * Manager used to manage all interactions.
 * <p>
 * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public interface HlaInteractionManager {

   /**
    * An enumeration of all interactions.
    *
    * <table>
    * <caption>All interactions</caption>
    * <tr><td><b>Enum constant</b></td><td><b>Java name</b></td><td><b>FOM name</b></td></tr>
    * <tr><td>HLAINTERACTION_ROOT</td><td>HLAinteractionRoot</td><td><code>HLAinteractionRoot</code></td></tr>
    * <tr><td>START_STOP</td><td>StartStop</td><td><code>HLAinteractionRoot.Start_Stop</code></td></tr>
    * <tr><td>MODE_TRANSITION_REQUEST</td><td>ModeTransitionRequest</td><td><code>HLAinteractionRoot.ModeTransitionRequest</code></td></tr>
    * </table>
    */
   enum Interaction {
      /** HLAinteractionRoot (FOM name <code>HLAinteractionRoot</code>) */
      HLAINTERACTION_ROOT("HLAinteractionRoot"),
      /** StartStop (FOM name <code>HLAinteractionRoot.Start_Stop</code>) */
      START_STOP("HLAinteractionRoot.Start_Stop"),
      /** ModeTransitionRequest (FOM name <code>HLAinteractionRoot.ModeTransitionRequest</code>) */
      MODE_TRANSITION_REQUEST("HLAinteractionRoot.ModeTransitionRequest");

      private static final Map<String, Interaction> NAMES;

      static {
         NAMES = new HashMap<String, Interaction>(values().length);
         for (Interaction val : values()) {
            NAMES.put(val._hlaName, val);
         }
      }

      private final String _hlaName;

      private Interaction(String hlaName) {
         _hlaName = hlaName;
      }

      /**
       * Get the HLA name of the interaction.
       *
       * @return the HLA name of the interaction.
       */
      public String getHlaName() {
         return _hlaName;
      }

     /**
      * Find the Interaction with the specified name.
      *
      * @param name name of the interaction to find
      *
      * @return the interaction with the specified <code>name</code>, or <code>null</code> if not found
      */
      public static Interaction find(String name) {
         return NAMES.get(name);
      }
   }

  /**
   *  Interface for creating a HlaHLAinteractionRootInteraction
   * <p>
   * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
   */
   public interface HlaHLAinteractionRootInteraction {

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
      public void sendInteraction() throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                                           HlaSaveInProgressException, HlaRestoreInProgressException;

     /**
      * Send the HlaHLAinteractionRootInteraction with a specified timestamp
      *
      * @param timeStamp timestamp to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaTimeStamp timeStamp) throws HlaNotConnectedException, HlaFomException, HlaInternalException,
                                                                       HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;

     /**
      * Send the HlaHLAinteractionRootInteraction with a specified logical time.
      *
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInvalidLogicalTimeException if the logical time is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException,
                                                                           HlaInternalException, HlaRtiException, HlaSaveInProgressException,
                                                                           HlaRestoreInProgressException;

     /**
      * Send the HlaHLAinteractionRootInteraction with a specified timestamp and logical time.
      *
      * @param timeStamp timestamp to send for this interaction
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInvalidLogicalTimeException if the logical time is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) throws HlaNotConnectedException,
                                                                HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
                                                                HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;
   }

  /**
   * Get a HlaHLAinteractionRootInteraction
   *
   * @return An interaction
   */
   HlaHLAinteractionRootInteraction getHlaHLAinteractionRootInteraction();

  /**
   *  Interface for creating a HlaStartStopInteraction
   * <p>
   * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
   */
   public interface HlaStartStopInteraction {

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
      public void sendInteraction() throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                                           HlaSaveInProgressException, HlaRestoreInProgressException;

     /**
      * Send the HlaStartStopInteraction with a specified timestamp
      *
      * @param timeStamp timestamp to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaTimeStamp timeStamp) throws HlaNotConnectedException, HlaFomException, HlaInternalException,
                                                                       HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;

     /**
      * Send the HlaStartStopInteraction with a specified logical time.
      *
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInvalidLogicalTimeException if the logical time is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException,
                                                                           HlaInternalException, HlaRtiException, HlaSaveInProgressException,
                                                                           HlaRestoreInProgressException;

     /**
      * Send the HlaStartStopInteraction with a specified timestamp and logical time.
      *
      * @param timeStamp timestamp to send for this interaction
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInvalidLogicalTimeException if the logical time is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) throws HlaNotConnectedException,
                                                                HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
                                                                HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;
   }

  /**
   * Get a HlaStartStopInteraction
   *
   * @return An interaction
   */
   HlaStartStopInteraction getHlaStartStopInteraction();

   /**
    * Interface for getting HLAinteractionRoot.ModeTransitionRequest parameters
    * <p>
    * This class is <code>Immutable</code> (and therefore <code>ThreadSafe</code>)
 * as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
    */
    public interface HlaModeTransitionRequestParameters {

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
       public boolean hasExecution_mode();

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
       public MTRMode getExecution_mode() throws HlaValueNotSetException;

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
       public MTRMode getExecution_mode(MTRMode defaultValue);

      /**
       * Get the HlaFederateId for the federate that sent this interaction.
       *
       * @return The federate id for the federate that sent this interaction
       */
       public HlaFederateId getProducingFederate();

      /**
       * Check if the parameters are within the interest defined for this interaction.
       *
       * @return true if the parameters are within interest
       */
       public boolean isWithinInterest();

      /**
       * Get a string representation of the interaction parameters.
       *
       * @return A string representation of the interaction parameters.
       */
       public String toString();
    }

  /**
   *  Interface for creating a HlaModeTransitionRequestInteraction
   * <p>
   * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
   */
   public interface HlaModeTransitionRequestInteraction {

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
      *
      * @return the updated interaction
      *
      */
      public HlaModeTransitionRequestInteraction setExecution_mode(MTRMode executionMode);

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
      public void sendInteraction() throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                                           HlaSaveInProgressException, HlaRestoreInProgressException;

     /**
      * Send the HlaModeTransitionRequestInteraction with a specified timestamp
      *
      * @param timeStamp timestamp to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaTimeStamp timeStamp) throws HlaNotConnectedException, HlaFomException, HlaInternalException,
                                                                       HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;

     /**
      * Send the HlaModeTransitionRequestInteraction with a specified logical time.
      *
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInvalidLogicalTimeException if the logical time is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException,
                                                                           HlaInternalException, HlaRtiException, HlaSaveInProgressException,
                                                                           HlaRestoreInProgressException;

     /**
      * Send the HlaModeTransitionRequestInteraction with a specified timestamp and logical time.
      *
      * @param timeStamp timestamp to send for this interaction
      * @param logicalTime logical time to send for this interaction
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaFomException if the FOM is invalid
      * @throws HlaInvalidLogicalTimeException if the logical time is invalid
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      public void sendInteraction(HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) throws HlaNotConnectedException,
                                                                HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
                                                                HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;
   }

  /**
   * Get a HlaModeTransitionRequestInteraction
   *
   * @return An interaction
   */
   HlaModeTransitionRequestInteraction getHlaModeTransitionRequestInteraction();

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
   void sendHLAinteractionRoot(
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot</code> interaction with a specified timestamp.
    *
    * @param timeStamp timestamp to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendHLAinteractionRoot(
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot</code> interaction with a specified logical time.
    *
    * @param logicalTime logical time to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendHLAinteractionRoot(
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
            HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot</code> interaction with a specified timestamp and logical time.
    *
    * @param timeStamp timestamp to send for this interaction
    * @param logicalTime logical time to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendHLAinteractionRoot(
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
            HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;
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
   void sendStartStop(
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified timestamp.
    *
    * @param timeStamp timestamp to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendStartStop(
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified logical time.
    *
    * @param logicalTime logical time to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendStartStop(
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
            HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot.Start_Stop</code> interaction with a specified timestamp and logical time.
    *
    * @param timeStamp timestamp to send for this interaction
    * @param logicalTime logical time to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendStartStop(
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
            HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;
   /**
    * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction.
    *
    * @param executionMode   represents the <code>execution_mode</code> from the FOM.
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
   void sendModeTransitionRequest(
      MTRMode executionMode
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction with a specified timestamp.
    *
    * @param executionMode   represents the <code>execution_mode</code> from the FOM.
    *        <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
    *        <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
    * @param timeStamp timestamp to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendModeTransitionRequest(
      MTRMode executionMode,
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction with a specified logical time.
    *
    * @param executionMode   represents the <code>execution_mode</code> from the FOM.
    *        <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
    *        <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
    * @param logicalTime logical time to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendModeTransitionRequest(
      MTRMode executionMode,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
            HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Sends the <code>HLAinteractionRoot.ModeTransitionRequest</code> interaction with a specified timestamp and logical time.
    *
    * @param executionMode   represents the <code>execution_mode</code> from the FOM.
    *        <br>Description from the FOM: The run mode requested.  There are only 3 valid Mode Transition Request (MTR) mode values: MTR_GOTO_RUN, MTR_GOTO_FREEZE, MTR_GOTO_SHUTDOWN.  Of these three valid mode requests, only 7 combinations of current execution mode and requested mode are valid: 
1. EXEC_MODE_UNINITIALIZED -> EXEC_MODE_SHUTDOWN 
2. EXEC_MODE_INITIALIZED -> EXEC_MODE_FREEZE 
3. EXEC_MODE_INITIALIZED -> EXEC_MODE_SHUTDOWN 
4. EXEC_MODE_RUNNING -> EXEC_MODE_FREEZE 
5. EXEC_MODE_RUNNING -> EXEC_MODE_SHUTDOWN 
6. EXEC_MODE_FREEZE -> EXEC_MODE_RUNNING 
7. EXEC_MODE_FREEZE -> EXEC_MODE_SHUTDOWN
    *        <br>Description of the data type from the FOM: Mode Transition Request (MTR) transition values.  This enumeration is used to request a specific mode transition.  However, not all mode transition requests are accepted for any given Run Mode.  See mode transition validation table in the Space Reference FOM documentation.
    * @param timeStamp timestamp to send for this interaction
    * @param logicalTime logical time to send for this interaction
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaFomException if the FOM is invalid
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
   void sendModeTransitionRequest(
      MTRMode executionMode,
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException,
            HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Add a interaction listener.
    *
    * @param listener listener to add
    */
   void addHlaInteractionListener(HlaInteractionListener listener);

   /**
    * Remove a interaction listener.
    *
    * @param listener listener to remove
    */
   void removeHlaInteractionListener(HlaInteractionListener listener);

   /**
    * Enables or disables an interaction.
    * The interaction is enabled by default. The state can only be changed when not connected.
    * When an interaction is disabled it will act as disconnected,
    * ie throws HlaNotConnectedException.
    *
    * @param enabled <code>true</code> to enable the interaction, otherwise <code>false</code>
    * @param interaction the interaction to change
    */
   void setEnabled(boolean enabled, Interaction interaction);

   /**
    * Enables or disables a set of interactions.
    * The interactions are enabled by default. The state can only be changed when not connected.
    * When an interaction is disabled it will act as disconnected,
    * ie throws HlaNotConnectedException.
    *
    * @param enabled <code>true</code> to enable the interactions, otherwise <code>false</code>
    * @param interactions the interactions to change
    */
   void setEnabled(boolean enabled, Set<Interaction> interactions);

   /**
    * Enables a set of interactions if they are available in the FOM at runtime.
    * The interactions are enabled by default. The state can only be changed when not connected.
    * When an interaction is disabled it will act as disconnected,
    * ie throws HlaNotConnectedException.
    *
    * @param interactions the interactions to change
    */
   void setEnabledIfAvailableInFom(Set<Interaction> interactions);

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
   boolean isEnabled(Interaction interaction);
}
