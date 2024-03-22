/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONATTRIBUTES_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONATTRIBUTES_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>
#include <vector>
#include <utility>
    
#include <LunarSimulation/datatypes/ExecutionMode.h>
#include <string>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaHLAobjectRootAttributes.h>
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

   /**
   * Interface used to represent all attributes for an object instance.
   */
   class HlaExecutionConfigurationAttributes : public HlaHLAobjectRootAttributes {
   public:


     /**
      * An enumeration of the attributes of an HlaExecutionConfiguration
      *
      *<table>
      * <caption>All attributes</caption>
      * <tr><td><b>Enum constant</b></td><td><b>C++ name</b></td><td><b>FOM name</b></td></tr>
      * <tr><td>ROOT_FRAME_NAME</td><td>rootFrameName</td><td><code>root_frame_name</code></td></tr>
      * <tr><td>SCENARIO_TIME_EPOCH</td><td>scenarioTimeEpoch</td><td><code>scenario_time_epoch</code></td></tr>
      * <tr><td>CURRENT_EXECUTION_MODE</td><td>currentExecutionMode</td><td><code>current_execution_mode</code></td></tr>
      * <tr><td>NEXT_EXECUTION_MODE</td><td>nextExecutionMode</td><td><code>next_execution_mode</code></td></tr>
      * <tr><td>NEXT_MODE_SCENARIO_TIME</td><td>nextModeScenarioTime</td><td><code>next_mode_scenario_time</code></td></tr>
      * <tr><td>NEXT_MODE_CTE_TIME</td><td>nextModeCteTime</td><td><code>next_mode_cte_time</code></td></tr>
      * <tr><td>LEAST_COMMON_TIME_STEP</td><td>leastCommonTimeStep</td><td><code>least_common_time_step</code></td></tr>
      *</table>
      */
      enum Attribute {
        /**
        * rootFrameName (FOM name: <code>root_frame_name</code>).
        * <br>Description from the FOM: Specifies the name of the root coordinate frame in the federation execution's reference frame tree.  This frame shall remain fixed throughout the federation execution.
        */
         ROOT_FRAME_NAME,

        /**
        * scenarioTimeEpoch (FOM name: <code>scenario_time_epoch</code>).
        * <br>Description from the FOM: Federation execution scenario time epoch.  This is the beginning epoch expressed in Terrestrial Time (TT), using as starting epoch that of the Truncated Julian Date (TJD)- 1968-05-24 00:00:00 UTC, that corresponds to HLA logical time 0.  All joining federates shall use this time to coordinate the offset between their local simulation scenario times, their local simulation execution times and the HLA logical time.
        */
         SCENARIO_TIME_EPOCH,

        /**
        * currentExecutionMode (FOM name: <code>current_execution_mode</code>).
        * <br>Description from the FOM: Defines the current running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.
        */
         CURRENT_EXECUTION_MODE,

        /**
        * nextExecutionMode (FOM name: <code>next_execution_mode</code>).
        * <br>Description from the FOM: Defines the next running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.  This is used in conjunction with the cte_mode_time, sim_mode_time and associated sync point mechanisms to coordinate federation execution mode transitions.
        */
         NEXT_EXECUTION_MODE,

        /**
        * nextModeScenarioTime (FOM name: <code>next_mode_scenario_time</code>).
        * <br>Description from the FOM: The time for the next federation execution mode change expressed as a federation scenario time reference.  Note: this value is only meaningful for going into freeze; exiting freeze is coordinated through a sync point mechanism.
        */
         NEXT_MODE_SCENARIO_TIME,

        /**
        * nextModeCteTime (FOM name: <code>next_mode_cte_time</code>).
        * <br>Description from the FOM: The time for the next federation execution mode change expressed as a Central Timing Equipment (CTE) time reference.  The standard for this reference shall be defined in the federation agreement when CTE is used.
        */
         NEXT_MODE_CTE_TIME,

        /**
        * leastCommonTimeStep (FOM name: <code>least_common_time_step</code>).
        * <br>Description from the FOM: A 64 bit integer time that represents microseconds for the least common value of all the time step values in the federation execution (LCTS).  This value is set by the Master Federate and does not change during the federation execution. This is used in the computation to find the next HLA Logical Time Boundary (HLTB) available to all federates in the federation execution.  The basic equation is HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS, where GALT is the greatest available logical time.  This is used to synchronize the federates in a federation execution to be on a common logical time boundary.
        */
         LEAST_COMMON_TIME_STEP

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

      LIBAPI virtual ~HlaExecutionConfigurationAttributes() {}
    
      /**
      * Returns true if the <code>rootFrameName</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: Specifies the name of the root coordinate frame in the federation execution's reference frame tree.  This frame shall remain fixed throughout the federation execution.
      *
      * @return true if <code>rootFrameName</code> is available.
      */
      LIBAPI virtual bool hasRootFrameName() = 0;

      /**
      * Gets the value of the <code>rootFrameName</code> attribute.
      *
      * <br>Description from the FOM: Specifies the name of the root coordinate frame in the federation execution's reference frame tree.  This frame shall remain fixed throughout the federation execution.
      * <br>Description of the data type from the FOM: 
      *
      * @return the <code>rootFrameName</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual std::wstring getRootFrameName()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>rootFrameName</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: Specifies the name of the root coordinate frame in the federation execution's reference frame tree.  This frame shall remain fixed throughout the federation execution.
      * <br>Description of the data type from the FOM: 
      *
      * @param defaultValue default value
      *
      * @return the <code>rootFrameName</code> attribute.
      */
      LIBAPI virtual std::wstring getRootFrameName(std::wstring defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>rootFrameName</code> attribute.
      * <br>Description from the FOM: Specifies the name of the root coordinate frame in the federation execution's reference frame tree.  This frame shall remain fixed throughout the federation execution.
      * <br>Description of the data type from the FOM: 
      *
      * @return the time stamped <code>rootFrameName</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< std::wstring > getRootFrameNameTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>scenarioTimeEpoch</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: Federation execution scenario time epoch.  This is the beginning epoch expressed in Terrestrial Time (TT), using as starting epoch that of the Truncated Julian Date (TJD)- 1968-05-24 00:00:00 UTC, that corresponds to HLA logical time 0.  All joining federates shall use this time to coordinate the offset between their local simulation scenario times, their local simulation execution times and the HLA logical time.
      *
      * @return true if <code>scenarioTimeEpoch</code> is available.
      */
      LIBAPI virtual bool hasScenarioTimeEpoch() = 0;

      /**
      * Gets the value of the <code>scenarioTimeEpoch</code> attribute.
      *
      * <br>Description from the FOM: Federation execution scenario time epoch.  This is the beginning epoch expressed in Terrestrial Time (TT), using as starting epoch that of the Truncated Julian Date (TJD)- 1968-05-24 00:00:00 UTC, that corresponds to HLA logical time 0.  All joining federates shall use this time to coordinate the offset between their local simulation scenario times, their local simulation execution times and the HLA logical time.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @return the <code>scenarioTimeEpoch</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual double getScenarioTimeEpoch()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>scenarioTimeEpoch</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: Federation execution scenario time epoch.  This is the beginning epoch expressed in Terrestrial Time (TT), using as starting epoch that of the Truncated Julian Date (TJD)- 1968-05-24 00:00:00 UTC, that corresponds to HLA logical time 0.  All joining federates shall use this time to coordinate the offset between their local simulation scenario times, their local simulation execution times and the HLA logical time.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @param defaultValue default value
      *
      * @return the <code>scenarioTimeEpoch</code> attribute.
      */
      LIBAPI virtual double getScenarioTimeEpoch(double defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>scenarioTimeEpoch</code> attribute.
      * <br>Description from the FOM: Federation execution scenario time epoch.  This is the beginning epoch expressed in Terrestrial Time (TT), using as starting epoch that of the Truncated Julian Date (TJD)- 1968-05-24 00:00:00 UTC, that corresponds to HLA logical time 0.  All joining federates shall use this time to coordinate the offset between their local simulation scenario times, their local simulation execution times and the HLA logical time.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @return the time stamped <code>scenarioTimeEpoch</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< double > getScenarioTimeEpochTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>currentExecutionMode</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: Defines the current running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.
      *
      * @return true if <code>currentExecutionMode</code> is available.
      */
      LIBAPI virtual bool hasCurrentExecutionMode() = 0;

      /**
      * Gets the value of the <code>currentExecutionMode</code> attribute.
      *
      * <br>Description from the FOM: Defines the current running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @return the <code>currentExecutionMode</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::ExecutionMode::ExecutionMode getCurrentExecutionMode()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>currentExecutionMode</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: Defines the current running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @param defaultValue default value
      *
      * @return the <code>currentExecutionMode</code> attribute.
      */
      LIBAPI virtual LunarSimulation::ExecutionMode::ExecutionMode getCurrentExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>currentExecutionMode</code> attribute.
      * <br>Description from the FOM: Defines the current running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @return the time stamped <code>currentExecutionMode</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > getCurrentExecutionModeTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>nextExecutionMode</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: Defines the next running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.  This is used in conjunction with the cte_mode_time, sim_mode_time and associated sync point mechanisms to coordinate federation execution mode transitions.
      *
      * @return true if <code>nextExecutionMode</code> is available.
      */
      LIBAPI virtual bool hasNextExecutionMode() = 0;

      /**
      * Gets the value of the <code>nextExecutionMode</code> attribute.
      *
      * <br>Description from the FOM: Defines the next running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.  This is used in conjunction with the cte_mode_time, sim_mode_time and associated sync point mechanisms to coordinate federation execution mode transitions.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @return the <code>nextExecutionMode</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::ExecutionMode::ExecutionMode getNextExecutionMode()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>nextExecutionMode</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: Defines the next running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.  This is used in conjunction with the cte_mode_time, sim_mode_time and associated sync point mechanisms to coordinate federation execution mode transitions.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @param defaultValue default value
      *
      * @return the <code>nextExecutionMode</code> attribute.
      */
      LIBAPI virtual LunarSimulation::ExecutionMode::ExecutionMode getNextExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>nextExecutionMode</code> attribute.
      * <br>Description from the FOM: Defines the next running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.  This is used in conjunction with the cte_mode_time, sim_mode_time and associated sync point mechanisms to coordinate federation execution mode transitions.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @return the time stamped <code>nextExecutionMode</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > getNextExecutionModeTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>nextModeScenarioTime</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a federation scenario time reference.  Note: this value is only meaningful for going into freeze; exiting freeze is coordinated through a sync point mechanism.
      *
      * @return true if <code>nextModeScenarioTime</code> is available.
      */
      LIBAPI virtual bool hasNextModeScenarioTime() = 0;

      /**
      * Gets the value of the <code>nextModeScenarioTime</code> attribute.
      *
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a federation scenario time reference.  Note: this value is only meaningful for going into freeze; exiting freeze is coordinated through a sync point mechanism.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @return the <code>nextModeScenarioTime</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual double getNextModeScenarioTime()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>nextModeScenarioTime</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a federation scenario time reference.  Note: this value is only meaningful for going into freeze; exiting freeze is coordinated through a sync point mechanism.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @param defaultValue default value
      *
      * @return the <code>nextModeScenarioTime</code> attribute.
      */
      LIBAPI virtual double getNextModeScenarioTime(double defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>nextModeScenarioTime</code> attribute.
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a federation scenario time reference.  Note: this value is only meaningful for going into freeze; exiting freeze is coordinated through a sync point mechanism.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @return the time stamped <code>nextModeScenarioTime</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< double > getNextModeScenarioTimeTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>nextModeCteTime</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a Central Timing Equipment (CTE) time reference.  The standard for this reference shall be defined in the federation agreement when CTE is used.
      *
      * @return true if <code>nextModeCteTime</code> is available.
      */
      LIBAPI virtual bool hasNextModeCteTime() = 0;

      /**
      * Gets the value of the <code>nextModeCteTime</code> attribute.
      *
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a Central Timing Equipment (CTE) time reference.  The standard for this reference shall be defined in the federation agreement when CTE is used.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @return the <code>nextModeCteTime</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual double getNextModeCteTime()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>nextModeCteTime</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a Central Timing Equipment (CTE) time reference.  The standard for this reference shall be defined in the federation agreement when CTE is used.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @param defaultValue default value
      *
      * @return the <code>nextModeCteTime</code> attribute.
      */
      LIBAPI virtual double getNextModeCteTime(double defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>nextModeCteTime</code> attribute.
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a Central Timing Equipment (CTE) time reference.  The standard for this reference shall be defined in the federation agreement when CTE is used.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @return the time stamped <code>nextModeCteTime</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< double > getNextModeCteTimeTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
    
      /**
      * Returns true if the <code>leastCommonTimeStep</code> attribute has received a value yet.
      *
      * <br>Description from the FOM: A 64 bit integer time that represents microseconds for the least common value of all the time step values in the federation execution (LCTS).  This value is set by the Master Federate and does not change during the federation execution. This is used in the computation to find the next HLA Logical Time Boundary (HLTB) available to all federates in the federation execution.  The basic equation is HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS, where GALT is the greatest available logical time.  This is used to synchronize the federates in a federation execution to be on a common logical time boundary.
      *
      * @return true if <code>leastCommonTimeStep</code> is available.
      */
      LIBAPI virtual bool hasLeastCommonTimeStep() = 0;

      /**
      * Gets the value of the <code>leastCommonTimeStep</code> attribute.
      *
      * <br>Description from the FOM: A 64 bit integer time that represents microseconds for the least common value of all the time step values in the federation execution (LCTS).  This value is set by the Master Federate and does not change during the federation execution. This is used in the computation to find the next HLA Logical Time Boundary (HLTB) available to all federates in the federation execution.  The basic equation is HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS, where GALT is the greatest available logical time.  This is used to synchronize the federates in a federation execution to be on a common logical time boundary.
      * <br>Description of the data type from the FOM: Standardized 64 bit integer time [unit: NA, resolution: 1, accuracy: NA]
      *
      * @return the <code>leastCommonTimeStep</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual long long getLeastCommonTimeStep()
         THROW_SPEC (HlaValueNotSetException) = 0;

      /**
      * Gets the value of the <code>leastCommonTimeStep</code> attribute, or <code>defaultValue</code> if value was not set.
      *
      * <br>Description from the FOM: A 64 bit integer time that represents microseconds for the least common value of all the time step values in the federation execution (LCTS).  This value is set by the Master Federate and does not change during the federation execution. This is used in the computation to find the next HLA Logical Time Boundary (HLTB) available to all federates in the federation execution.  The basic equation is HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS, where GALT is the greatest available logical time.  This is used to synchronize the federates in a federation execution to be on a common logical time boundary.
      * <br>Description of the data type from the FOM: Standardized 64 bit integer time [unit: NA, resolution: 1, accuracy: NA]
      *
      * @param defaultValue default value
      *
      * @return the <code>leastCommonTimeStep</code> attribute.
      */
      LIBAPI virtual long long getLeastCommonTimeStep(long long defaultValue) = 0;

      /**
      * Gets the time stamped value of the <code>leastCommonTimeStep</code> attribute.
      * <br>Description from the FOM: A 64 bit integer time that represents microseconds for the least common value of all the time step values in the federation execution (LCTS).  This value is set by the Master Federate and does not change during the federation execution. This is used in the computation to find the next HLA Logical Time Boundary (HLTB) available to all federates in the federation execution.  The basic equation is HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS, where GALT is the greatest available logical time.  This is used to synchronize the federates in a federation execution to be on a common logical time boundary.
      * <br>Description of the data type from the FOM: Standardized 64 bit integer time [unit: NA, resolution: 1, accuracy: NA]
      *
      * @return the time stamped <code>leastCommonTimeStep</code> attribute.
      *
      * @throws HlaValueNotSetException unchecked exception that is thrown if no value is available.
      */
      LIBAPI virtual LunarSimulation::HlaTimeStamped< long long > getLeastCommonTimeStepTimeStamped()
         THROW_SPEC (HlaValueNotSetException) = 0;
   };
}
#endif
