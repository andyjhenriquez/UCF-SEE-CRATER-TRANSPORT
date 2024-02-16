/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONMANAGER_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/ExecutionMode.h>
#include <string>

#include <vector>

#include <LunarSimulation/HlaExecutionConfigurationManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaExecutionConfigurations.
   */
   class HlaExecutionConfigurationManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaExecutionConfigurationManager() {}

      /**
      * Gets a list of all HlaExecutionConfigurations within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaExecutionConfigurations
      */
      LIBAPI virtual std::vector<HlaExecutionConfigurationPtr> getHlaExecutionConfigurations() = 0;

      /**
      * Gets a list of all HlaExecutionConfigurations, both local and remote.
      * HlaExecutionConfigurations not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaExecutionConfigurations
      */
      LIBAPI virtual std::vector<HlaExecutionConfigurationPtr> getAllHlaExecutionConfigurations() = 0;

      /**
      * Gets a list of local HlaExecutionConfigurations within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaExecutionConfigurations
      */
      LIBAPI virtual std::vector<HlaExecutionConfigurationPtr> getLocalHlaExecutionConfigurations() = 0;

      /**
      * Gets a list of remote HlaExecutionConfigurations within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaExecutionConfigurations
      */
      LIBAPI virtual std::vector<HlaExecutionConfigurationPtr> getRemoteHlaExecutionConfigurations() = 0;

      /**
      * Find a HlaExecutionConfiguration with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaExecutionConfiguration to find
      *
      * @return the specified HlaExecutionConfiguration, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaExecutionConfigurationPtr getExecutionConfigurationByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaExecutionConfiguration with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaExecutionConfiguration to find
      *
      * @return the specified HlaExecutionConfiguration, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaExecutionConfigurationPtr getExecutionConfigurationByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaExecutionConfiguration, and sets all <i>Create</i> attributes.
      *
      * @return Returns a new local HlaExecutionConfiguration.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaExecutionConfigurationPtr createLocalHlaExecutionConfiguration(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaExecutionConfiguration with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      *
      * @return Returns a new local HlaExecutionConfiguration.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaExecutionConfigurationPtr createLocalHlaExecutionConfiguration(
         const std::wstring& hlaInstanceName
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaExecutionConfiguration and removes it from the federation.
      *
      * @param executionConfiguration The HlaExecutionConfiguration to delete
      *
      * @return the HlaExecutionConfiguration deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaExecutionConfiguration and removes it from the federation.
      *
      * @param executionConfiguration The HlaExecutionConfiguration to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaExecutionConfiguration deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaExecutionConfiguration and removes it from the federation.
      *
      * @param executionConfiguration The HlaExecutionConfiguration to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaExecutionConfiguration deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaExecutionConfiguration and removes it from the federation.
      *
      * @param executionConfiguration The HlaExecutionConfiguration to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaExecutionConfiguration deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaExecutionConfigurationPtr deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaExecutionConfiguration manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaExecutionConfigurationManagerListener(HlaExecutionConfigurationManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaExecutionConfiguration manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaExecutionConfigurationManagerListener(HlaExecutionConfigurationManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaExecutionConfiguration (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaExecutionConfiguration is updated.
      * The listener is also called when an interaction is sent to an instance of HlaExecutionConfiguration.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaExecutionConfigurationDefaultInstanceListener(HlaExecutionConfigurationListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaExecutionConfiguration.
      * Note: The listener will not be removed from already existing instances of HlaExecutionConfiguration.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaExecutionConfigurationDefaultInstanceListener(HlaExecutionConfigurationListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaExecutionConfiguration (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaExecutionConfiguration is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaExecutionConfigurationDefaultInstanceValueListener(HlaExecutionConfigurationValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaExecutionConfiguration.
      * Note: The valueListener will not be removed from already existing instances of HlaExecutionConfiguration.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaExecutionConfigurationDefaultInstanceValueListener(HlaExecutionConfigurationValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaExecutionConfiguration manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaExecutionConfiguration manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaExecutionConfiguration manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaExecutionConfiguration manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaExecutionConfiguration manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaExecutionConfiguration manager is actually enabled when connected.
      * An HlaExecutionConfiguration manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaExecutionConfiguration manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
