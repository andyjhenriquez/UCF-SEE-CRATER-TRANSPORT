/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEMANAGER_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <string>
#include <vector>

#include <vector>

#include <LunarSimulation/HlaPhysicalInterfaceManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaPhysicalInterfaces.
   */
   class HlaPhysicalInterfaceManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaPhysicalInterfaceManager() {}

      /**
      * Gets a list of all HlaPhysicalInterfaces within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaPhysicalInterfaces
      */
      LIBAPI virtual std::vector<HlaPhysicalInterfacePtr> getHlaPhysicalInterfaces() = 0;

      /**
      * Gets a list of all HlaPhysicalInterfaces, both local and remote.
      * HlaPhysicalInterfaces not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaPhysicalInterfaces
      */
      LIBAPI virtual std::vector<HlaPhysicalInterfacePtr> getAllHlaPhysicalInterfaces() = 0;

      /**
      * Gets a list of local HlaPhysicalInterfaces within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaPhysicalInterfaces
      */
      LIBAPI virtual std::vector<HlaPhysicalInterfacePtr> getLocalHlaPhysicalInterfaces() = 0;

      /**
      * Gets a list of remote HlaPhysicalInterfaces within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaPhysicalInterfaces
      */
      LIBAPI virtual std::vector<HlaPhysicalInterfacePtr> getRemoteHlaPhysicalInterfaces() = 0;

      /**
      * Find a HlaPhysicalInterface with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaPhysicalInterface to find
      *
      * @return the specified HlaPhysicalInterface, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaPhysicalInterfacePtr getPhysicalInterfaceByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaPhysicalInterface with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaPhysicalInterface to find
      *
      * @return the specified HlaPhysicalInterface, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaPhysicalInterfacePtr getPhysicalInterfaceByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaPhysicalInterface, and sets all <i>Create</i> attributes.
      *
      * @return Returns a new local HlaPhysicalInterface.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalInterfacePtr createLocalHlaPhysicalInterface(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaPhysicalInterface with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      *
      * @return Returns a new local HlaPhysicalInterface.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalInterfacePtr createLocalHlaPhysicalInterface(
         const std::wstring& hlaInstanceName
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalInterface and removes it from the federation.
      *
      * @param physicalInterface The HlaPhysicalInterface to delete
      *
      * @return the HlaPhysicalInterface deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalInterface and removes it from the federation.
      *
      * @param physicalInterface The HlaPhysicalInterface to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaPhysicalInterface deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalInterface and removes it from the federation.
      *
      * @param physicalInterface The HlaPhysicalInterface to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaPhysicalInterface deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalInterface and removes it from the federation.
      *
      * @param physicalInterface The HlaPhysicalInterface to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaPhysicalInterface deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalInterfacePtr deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaPhysicalInterface manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaPhysicalInterfaceManagerListener(HlaPhysicalInterfaceManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaPhysicalInterface manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaPhysicalInterfaceManagerListener(HlaPhysicalInterfaceManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaPhysicalInterface (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaPhysicalInterface is updated.
      * The listener is also called when an interaction is sent to an instance of HlaPhysicalInterface.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaPhysicalInterfaceDefaultInstanceListener(HlaPhysicalInterfaceListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaPhysicalInterface.
      * Note: The listener will not be removed from already existing instances of HlaPhysicalInterface.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaPhysicalInterfaceDefaultInstanceListener(HlaPhysicalInterfaceListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaPhysicalInterface (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaPhysicalInterface is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaPhysicalInterfaceDefaultInstanceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaPhysicalInterface.
      * Note: The valueListener will not be removed from already existing instances of HlaPhysicalInterface.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaPhysicalInterfaceDefaultInstanceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaPhysicalInterface manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaPhysicalInterface manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaPhysicalInterface manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaPhysicalInterface manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaPhysicalInterface manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaPhysicalInterface manager is actually enabled when connected.
      * An HlaPhysicalInterface manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaPhysicalInterface manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
