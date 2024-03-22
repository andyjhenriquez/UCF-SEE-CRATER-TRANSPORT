/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONVALUELISTENER_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONVALUELISTENER_H

#include <memory>

#include <LunarSimulation/datatypes/ExecutionMode.h>
#include <string>

#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaExecutionConfigurationAttributes.h>    

namespace LunarSimulation {

   /**
   * Listener for updates of attributes, with the new updated values.  
   */
   class HlaExecutionConfigurationValueListener {

   public:

      LIBAPI virtual ~HlaExecutionConfigurationValueListener() {}
    
      /**
      * This method is called when the attribute <code>rootFrameName</code> is updated.
      * <br>Description from the FOM: Specifies the name of the root coordinate frame in the federation execution's reference frame tree.  This frame shall remain fixed throughout the federation execution.
      * <br>Description of the data type from the FOM: 
      *
      * @param executionConfiguration The object which is updated.
      * @param rootFrameName The new value of the attribute in this update
      * @param validOldRootFrameName True if oldRootFrameName contains a valid value
      * @param oldRootFrameName The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void rootFrameNameUpdated(HlaExecutionConfigurationPtr executionConfiguration, std::wstring rootFrameName, bool validOldRootFrameName, std::wstring oldRootFrameName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>scenarioTimeEpoch</code> is updated.
      * <br>Description from the FOM: Federation execution scenario time epoch.  This is the beginning epoch expressed in Terrestrial Time (TT), using as starting epoch that of the Truncated Julian Date (TJD)- 1968-05-24 00:00:00 UTC, that corresponds to HLA logical time 0.  All joining federates shall use this time to coordinate the offset between their local simulation scenario times, their local simulation execution times and the HLA logical time.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @param executionConfiguration The object which is updated.
      * @param scenarioTimeEpoch The new value of the attribute in this update
      * @param validOldScenarioTimeEpoch True if oldScenarioTimeEpoch contains a valid value
      * @param oldScenarioTimeEpoch The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void scenarioTimeEpochUpdated(HlaExecutionConfigurationPtr executionConfiguration, double scenarioTimeEpoch, bool validOldScenarioTimeEpoch, double oldScenarioTimeEpoch, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>currentExecutionMode</code> is updated.
      * <br>Description from the FOM: Defines the current running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @param executionConfiguration The object which is updated.
      * @param currentExecutionMode The new value of the attribute in this update
      * @param validOldCurrentExecutionMode True if oldCurrentExecutionMode contains a valid value
      * @param oldCurrentExecutionMode The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void currentExecutionModeUpdated(HlaExecutionConfigurationPtr executionConfiguration, ExecutionMode::ExecutionMode currentExecutionMode, bool validOldCurrentExecutionMode, ExecutionMode::ExecutionMode oldCurrentExecutionMode, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>nextExecutionMode</code> is updated.
      * <br>Description from the FOM: Defines the next running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.  This is used in conjunction with the cte_mode_time, sim_mode_time and associated sync point mechanisms to coordinate federation execution mode transitions.
      * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
      *
      * @param executionConfiguration The object which is updated.
      * @param nextExecutionMode The new value of the attribute in this update
      * @param validOldNextExecutionMode True if oldNextExecutionMode contains a valid value
      * @param oldNextExecutionMode The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void nextExecutionModeUpdated(HlaExecutionConfigurationPtr executionConfiguration, ExecutionMode::ExecutionMode nextExecutionMode, bool validOldNextExecutionMode, ExecutionMode::ExecutionMode oldNextExecutionMode, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>nextModeScenarioTime</code> is updated.
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a federation scenario time reference.  Note: this value is only meaningful for going into freeze; exiting freeze is coordinated through a sync point mechanism.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @param executionConfiguration The object which is updated.
      * @param nextModeScenarioTime The new value of the attribute in this update
      * @param validOldNextModeScenarioTime True if oldNextModeScenarioTime contains a valid value
      * @param oldNextModeScenarioTime The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void nextModeScenarioTimeUpdated(HlaExecutionConfigurationPtr executionConfiguration, double nextModeScenarioTime, bool validOldNextModeScenarioTime, double oldNextModeScenarioTime, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>nextModeCteTime</code> is updated.
      * <br>Description from the FOM: The time for the next federation execution mode change expressed as a Central Timing Equipment (CTE) time reference.  The standard for this reference shall be defined in the federation agreement when CTE is used.
      * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
      *
      * @param executionConfiguration The object which is updated.
      * @param nextModeCteTime The new value of the attribute in this update
      * @param validOldNextModeCteTime True if oldNextModeCteTime contains a valid value
      * @param oldNextModeCteTime The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void nextModeCteTimeUpdated(HlaExecutionConfigurationPtr executionConfiguration, double nextModeCteTime, bool validOldNextModeCteTime, double oldNextModeCteTime, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
    
      /**
      * This method is called when the attribute <code>leastCommonTimeStep</code> is updated.
      * <br>Description from the FOM: A 64 bit integer time that represents microseconds for the least common value of all the time step values in the federation execution (LCTS).  This value is set by the Master Federate and does not change during the federation execution. This is used in the computation to find the next HLA Logical Time Boundary (HLTB) available to all federates in the federation execution.  The basic equation is HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS, where GALT is the greatest available logical time.  This is used to synchronize the federates in a federation execution to be on a common logical time boundary.
      * <br>Description of the data type from the FOM: Standardized 64 bit integer time [unit: NA, resolution: 1, accuracy: NA]
      *
      * @param executionConfiguration The object which is updated.
      * @param leastCommonTimeStep The new value of the attribute in this update
      * @param validOldLeastCommonTimeStep True if oldLeastCommonTimeStep contains a valid value
      * @param oldLeastCommonTimeStep The old value
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void leastCommonTimeStepUpdated(HlaExecutionConfigurationPtr executionConfiguration, long long leastCommonTimeStep, bool validOldLeastCommonTimeStep, long long oldLeastCommonTimeStep, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;
      /**
      * This method is called when the producing federate of an attribute is changed.
      * Only available when using HLA Evolved.
      *
      * @param executionConfiguration The object which is updated.
      * @param attribute The attribute that now has a new producing federate
      * @param oldProducingFederate The federate handle of the old producing federate
      * @param newProducingFederate The federate handle of the new producing federate
      * @param timeStamp The time when the update was initiated.
      * @param logicalTime The logical time when the update was initiated.
      */
      LIBAPI virtual void producingFederateUpdated(HlaExecutionConfigurationPtr executionConfiguration, HlaExecutionConfigurationAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)=0;

      class Adapter;
   };

   /**
   * An adapter class that implements the HlaExecutionConfigurationValueListener interface with empty methods.
   * It might be used as a base class for a listener.
   */
   class HlaExecutionConfigurationValueListener::Adapter : public HlaExecutionConfigurationValueListener {

   public:

      LIBAPI virtual void rootFrameNameUpdated(HlaExecutionConfigurationPtr executionConfiguration, std::wstring rootFrameName, bool validOldRootFrameName, std::wstring oldRootFrameName, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void scenarioTimeEpochUpdated(HlaExecutionConfigurationPtr executionConfiguration, double scenarioTimeEpoch, bool validOldScenarioTimeEpoch, double oldScenarioTimeEpoch, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void currentExecutionModeUpdated(HlaExecutionConfigurationPtr executionConfiguration, ExecutionMode::ExecutionMode currentExecutionMode, bool validOldCurrentExecutionMode, ExecutionMode::ExecutionMode oldCurrentExecutionMode, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void nextExecutionModeUpdated(HlaExecutionConfigurationPtr executionConfiguration, ExecutionMode::ExecutionMode nextExecutionMode, bool validOldNextExecutionMode, ExecutionMode::ExecutionMode oldNextExecutionMode, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void nextModeScenarioTimeUpdated(HlaExecutionConfigurationPtr executionConfiguration, double nextModeScenarioTime, bool validOldNextModeScenarioTime, double oldNextModeScenarioTime, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void nextModeCteTimeUpdated(HlaExecutionConfigurationPtr executionConfiguration, double nextModeCteTime, bool validOldNextModeCteTime, double oldNextModeCteTime, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

      LIBAPI virtual void leastCommonTimeStepUpdated(HlaExecutionConfigurationPtr executionConfiguration, long long leastCommonTimeStep, bool validOldLeastCommonTimeStep, long long oldLeastCommonTimeStep, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
      LIBAPI virtual void producingFederateUpdated(HlaExecutionConfigurationPtr executionConfiguration, HlaExecutionConfigurationAttributes::Attribute attribute, HlaFederateIdPtr oldProducingFederate, HlaFederateIdPtr newProducingFederate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
   };

}
#endif
