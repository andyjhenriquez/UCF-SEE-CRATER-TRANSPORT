/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALAUNCHERMANAGER_H
#define DEVELOPER_STUDIO_HLALAUNCHERMANAGER_H

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

#include <vector>

#include <LunarSimulation/HlaLauncherManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaLaunchers.
   */
   class HlaLauncherManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaLauncherManager() {}

      /**
      * Gets a list of all HlaLaunchers within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaLaunchers
      */
      LIBAPI virtual std::vector<HlaLauncherPtr> getHlaLaunchers() = 0;

      /**
      * Gets a list of all HlaLaunchers, both local and remote.
      * HlaLaunchers not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaLaunchers
      */
      LIBAPI virtual std::vector<HlaLauncherPtr> getAllHlaLaunchers() = 0;

      /**
      * Gets a list of local HlaLaunchers within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaLaunchers
      */
      LIBAPI virtual std::vector<HlaLauncherPtr> getLocalHlaLaunchers() = 0;

      /**
      * Gets a list of remote HlaLaunchers within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaLaunchers
      */
      LIBAPI virtual std::vector<HlaLauncherPtr> getRemoteHlaLaunchers() = 0;

      /**
      * Find a HlaLauncher with the given <code>name</code>.
      * If more than one HlaLauncher with the given <code>name</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * name was selected as a <i>Lookup</i> attribute.
      *
      * @param name The name that looks up which HlaLauncher to return.
      *
      * @return an HlaLauncher, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaLauncherPtr getLauncherByName(std::wstring name) = 0;

      /**
      * Find a HlaLauncher with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaLauncher to find
      *
      * @return the specified HlaLauncher, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaLauncherPtr getLauncherByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaLauncher with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaLauncher to find
      *
      * @return the specified HlaLauncher, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaLauncherPtr getLauncherByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaLauncher, and sets all <i>Create</i> attributes.
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaLauncher.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaLauncherPtr createLocalHlaLauncher(
         std::wstring name
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaLauncher with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaLauncher.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaLauncherPtr createLocalHlaLauncher(
         const std::wstring& hlaInstanceName,
         std::wstring name
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaLauncher and removes it from the federation.
      *
      * @param launcher The HlaLauncher to delete
      *
      * @return the HlaLauncher deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaLauncher and removes it from the federation.
      *
      * @param launcher The HlaLauncher to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaLauncher deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaLauncher and removes it from the federation.
      *
      * @param launcher The HlaLauncher to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaLauncher deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaLauncher and removes it from the federation.
      *
      * @param launcher The HlaLauncher to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaLauncher deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaLauncherPtr deleteLocalHlaLauncher(HlaLauncherPtr launcher, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaLauncher manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaLauncherManagerListener(HlaLauncherManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaLauncher manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaLauncherManagerListener(HlaLauncherManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaLauncher (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaLauncher is updated.
      * The listener is also called when an interaction is sent to an instance of HlaLauncher.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaLauncherDefaultInstanceListener(HlaLauncherListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaLauncher.
      * Note: The listener will not be removed from already existing instances of HlaLauncher.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaLauncherDefaultInstanceListener(HlaLauncherListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaLauncher (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaLauncher is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaLauncher.
      * Note: The valueListener will not be removed from already existing instances of HlaLauncher.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaLauncher manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaLauncher manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaLauncher manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaLauncher manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaLauncher manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaLauncher manager is actually enabled when connected.
      * An HlaLauncher manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaLauncher manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
