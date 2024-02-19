/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONUPDATER_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONUPDATER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/ExecutionMode.h>
#include <string>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaHLAobjectRootUpdater.h>

namespace LunarSimulation {

    /**
    * Updater used to update attribute values.
    */
    class HlaExecutionConfigurationUpdater : public HlaHLAobjectRootUpdater {

    public:

    LIBAPI virtual ~HlaExecutionConfigurationUpdater() {}

    /**
    * Set the rootFrameName for this update.
    * <br>Description from the FOM: Specifies the name of the root coordinate frame in the federation execution's reference frame tree.  This frame shall remain fixed throughout the federation execution.
    * <br>Description of the data type from the FOM: 
    *
    * @param rootFrameName the new rootFrameName
    */
    LIBAPI virtual void setRootFrameName(const std::wstring& rootFrameName) = 0;

    /**
    * Set the scenarioTimeEpoch for this update.
    * <br>Description from the FOM: Federation execution scenario time epoch.  This is the beginning epoch expressed in Terrestrial Time (TT), using as starting epoch that of the Truncated Julian Date (TJD)- 1968-05-24 00:00:00 UTC, that corresponds to HLA logical time 0.  All joining federates shall use this time to coordinate the offset between their local simulation scenario times, their local simulation execution times and the HLA logical time.
    * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
    *
    * @param scenarioTimeEpoch the new scenarioTimeEpoch
    */
    LIBAPI virtual void setScenarioTimeEpoch(const double& scenarioTimeEpoch) = 0;

    /**
    * Set the currentExecutionMode for this update.
    * <br>Description from the FOM: Defines the current running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.
    * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
    *
    * @param currentExecutionMode the new currentExecutionMode
    */
    LIBAPI virtual void setCurrentExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& currentExecutionMode) = 0;

    /**
    * Set the nextExecutionMode for this update.
    * <br>Description from the FOM: Defines the next running state of the federation execution in terms of a finite set of states expressed in the ExecutionMode enumeration.  This is used in conjunction with the cte_mode_time, sim_mode_time and associated sync point mechanisms to coordinate federation execution mode transitions.
    * <br>Description of the data type from the FOM: Defines the mode for the running federation execution.  This enumeration type is used for coordinating transitions between federation execution run states.
    *
    * @param nextExecutionMode the new nextExecutionMode
    */
    LIBAPI virtual void setNextExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& nextExecutionMode) = 0;

    /**
    * Set the nextModeScenarioTime for this update.
    * <br>Description from the FOM: The time for the next federation execution mode change expressed as a federation scenario time reference.  Note: this value is only meaningful for going into freeze; exiting freeze is coordinated through a sync point mechanism.
    * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
    *
    * @param nextModeScenarioTime the new nextModeScenarioTime
    */
    LIBAPI virtual void setNextModeScenarioTime(const double& nextModeScenarioTime) = 0;

    /**
    * Set the nextModeCteTime for this update.
    * <br>Description from the FOM: The time for the next federation execution mode change expressed as a Central Timing Equipment (CTE) time reference.  The standard for this reference shall be defined in the federation agreement when CTE is used.
    * <br>Description of the data type from the FOM: A measurement of time. [unit: second (s), resolution: NA, accuracy: NA]
    *
    * @param nextModeCteTime the new nextModeCteTime
    */
    LIBAPI virtual void setNextModeCteTime(const double& nextModeCteTime) = 0;

    /**
    * Set the leastCommonTimeStep for this update.
    * <br>Description from the FOM: A 64 bit integer time that represents microseconds for the least common value of all the time step values in the federation execution (LCTS).  This value is set by the Master Federate and does not change during the federation execution. This is used in the computation to find the next HLA Logical Time Boundary (HLTB) available to all federates in the federation execution.  The basic equation is HLTB = ( floor(GALT/LCTS) + 1 ) * LCTS, where GALT is the greatest available logical time.  This is used to synchronize the federates in a federation execution to be on a common logical time boundary.
    * <br>Description of the data type from the FOM: Standardized 64 bit integer time [unit: NA, resolution: 1, accuracy: NA]
    *
    * @param leastCommonTimeStep the new leastCommonTimeStep
    */
    LIBAPI virtual void setLeastCommonTimeStep(const long long& leastCommonTimeStep) = 0;

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
