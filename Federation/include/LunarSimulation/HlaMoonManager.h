/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAMOONMANAGER_H
#define DEVELOPER_STUDIO_HLAMOONMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>

#include <vector>

#include <LunarSimulation/HlaMoonManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaMoons.
   */
   class HlaMoonManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaMoonManager() {}

      /**
      * Gets a list of all HlaMoons within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaMoons
      */
      LIBAPI virtual std::vector<HlaMoonPtr> getHlaMoons() = 0;

      /**
      * Gets a list of all HlaMoons, both local and remote.
      * HlaMoons not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaMoons
      */
      LIBAPI virtual std::vector<HlaMoonPtr> getAllHlaMoons() = 0;

      /**
      * Gets a list of local HlaMoons within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaMoons
      */
      LIBAPI virtual std::vector<HlaMoonPtr> getLocalHlaMoons() = 0;

      /**
      * Gets a list of remote HlaMoons within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaMoons
      */
      LIBAPI virtual std::vector<HlaMoonPtr> getRemoteHlaMoons() = 0;

      /**
      * Find a HlaMoon with the given <code>name</code>.
      * If more than one HlaMoon with the given <code>name</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * name was selected as a <i>Lookup</i> attribute.
      *
      * @param name The name that looks up which HlaMoon to return.
      *
      * @return an HlaMoon, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaMoonPtr getMoonByName(std::wstring name) = 0;

      /**
      * Find a HlaMoon with the given <code>parentName</code>.
      * If more than one HlaMoon with the given <code>parentName</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * parentName was selected as a <i>Lookup</i> attribute.
      *
      * @param parentName The parentName that looks up which HlaMoon to return.
      *
      * @return an HlaMoon, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaMoonPtr getMoonByParent_name(std::wstring parentName) = 0;

      /**
      * Find a HlaMoon with the given <code>state</code>.
      * If more than one HlaMoon with the given <code>state</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * state was selected as a <i>Lookup</i> attribute.
      *
      * @param state The state that looks up which HlaMoon to return.
      *
      * @return an HlaMoon, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaMoonPtr getMoonByState(SpaceTimeCoordinateState state) = 0;

      /**
      * Find a HlaMoon with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaMoon to find
      *
      * @return the specified HlaMoon, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaMoonPtr getMoonByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaMoon with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaMoon to find
      *
      * @return the specified HlaMoon, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaMoonPtr getMoonByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaMoon, and sets all <i>Create</i> attributes.
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaMoon.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaMoonPtr createLocalHlaMoon(
         std::wstring name
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaMoon with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaMoon.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaMoonPtr createLocalHlaMoon(
         const std::wstring& hlaInstanceName,
         std::wstring name
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaMoon and removes it from the federation.
      *
      * @param moon The HlaMoon to delete
      *
      * @return the HlaMoon deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaMoon and removes it from the federation.
      *
      * @param moon The HlaMoon to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaMoon deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaMoon and removes it from the federation.
      *
      * @param moon The HlaMoon to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaMoon deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaMoon and removes it from the federation.
      *
      * @param moon The HlaMoon to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaMoon deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaMoonPtr deleteLocalHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaMoon manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaMoonManagerListener(HlaMoonManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaMoon manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaMoonManagerListener(HlaMoonManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaMoon (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaMoon is updated.
      * The listener is also called when an interaction is sent to an instance of HlaMoon.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaMoonDefaultInstanceListener(HlaMoonListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaMoon.
      * Note: The listener will not be removed from already existing instances of HlaMoon.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaMoonDefaultInstanceListener(HlaMoonListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaMoon (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaMoon is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaMoonDefaultInstanceValueListener(HlaMoonValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaMoon.
      * Note: The valueListener will not be removed from already existing instances of HlaMoon.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaMoonDefaultInstanceValueListener(HlaMoonValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaMoon manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaMoon manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaMoon manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaMoon manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaMoon manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaMoon manager is actually enabled when connected.
      * An HlaMoon manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaMoon manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
