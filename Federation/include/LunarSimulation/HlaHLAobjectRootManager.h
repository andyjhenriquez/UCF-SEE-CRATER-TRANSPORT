/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAHLAOBJECTROOTMANAGER_H
#define DEVELOPER_STUDIO_HLAHLAOBJECTROOTMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif


#include <vector>

#include <LunarSimulation/HlaHLAobjectRootManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaHLAobjectRoots.
   */
   class HlaHLAobjectRootManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaHLAobjectRootManager() {}

      /**
      * Gets a list of all HlaHLAobjectRoots within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaHLAobjectRoots
      */
      LIBAPI virtual std::vector<HlaHLAobjectRootPtr> getHlaHLAobjectRoots() = 0;

      /**
      * Gets a list of all HlaHLAobjectRoots, both local and remote.
      * HlaHLAobjectRoots not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaHLAobjectRoots
      */
      LIBAPI virtual std::vector<HlaHLAobjectRootPtr> getAllHlaHLAobjectRoots() = 0;

      /**
      * Gets a list of local HlaHLAobjectRoots within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaHLAobjectRoots
      */
      LIBAPI virtual std::vector<HlaHLAobjectRootPtr> getLocalHlaHLAobjectRoots() = 0;

      /**
      * Gets a list of remote HlaHLAobjectRoots within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaHLAobjectRoots
      */
      LIBAPI virtual std::vector<HlaHLAobjectRootPtr> getRemoteHlaHLAobjectRoots() = 0;

      /**
      * Find a HlaHLAobjectRoot with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaHLAobjectRoot to find
      *
      * @return the specified HlaHLAobjectRoot, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaHLAobjectRootPtr getHLAobjectRootByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaHLAobjectRoot with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaHLAobjectRoot to find
      *
      * @return the specified HlaHLAobjectRoot, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaHLAobjectRootPtr getHLAobjectRootByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaHLAobjectRoot, and sets all <i>Create</i> attributes.
      *
      * @return Returns a new local HlaHLAobjectRoot.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaHLAobjectRootPtr createLocalHlaHLAobjectRoot(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaHLAobjectRoot with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      *
      * @return Returns a new local HlaHLAobjectRoot.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaHLAobjectRootPtr createLocalHlaHLAobjectRoot(
         const std::wstring& hlaInstanceName
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaHLAobjectRoot and removes it from the federation.
      *
      * @param hLAobjectRoot The HlaHLAobjectRoot to delete
      *
      * @return the HlaHLAobjectRoot deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaHLAobjectRoot and removes it from the federation.
      *
      * @param hLAobjectRoot The HlaHLAobjectRoot to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaHLAobjectRoot deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaHLAobjectRoot and removes it from the federation.
      *
      * @param hLAobjectRoot The HlaHLAobjectRoot to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaHLAobjectRoot deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaHLAobjectRoot and removes it from the federation.
      *
      * @param hLAobjectRoot The HlaHLAobjectRoot to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaHLAobjectRoot deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaHLAobjectRootPtr deleteLocalHlaHLAobjectRoot(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaHLAobjectRoot manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaHLAobjectRootManagerListener(HlaHLAobjectRootManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaHLAobjectRoot manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaHLAobjectRootManagerListener(HlaHLAobjectRootManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaHLAobjectRoot (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaHLAobjectRoot is updated.
      * The listener is also called when an interaction is sent to an instance of HlaHLAobjectRoot.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaHLAobjectRootDefaultInstanceListener(HlaHLAobjectRootListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaHLAobjectRoot.
      * Note: The listener will not be removed from already existing instances of HlaHLAobjectRoot.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaHLAobjectRootDefaultInstanceListener(HlaHLAobjectRootListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaHLAobjectRoot (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaHLAobjectRoot is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaHLAobjectRootDefaultInstanceValueListener(HlaHLAobjectRootValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaHLAobjectRoot.
      * Note: The valueListener will not be removed from already existing instances of HlaHLAobjectRoot.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaHLAobjectRootDefaultInstanceValueListener(HlaHLAobjectRootValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaHLAobjectRoot manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaHLAobjectRoot manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaHLAobjectRoot manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaHLAobjectRoot manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaHLAobjectRoot manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaHLAobjectRoot manager is actually enabled when connected.
      * An HlaHLAobjectRoot manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaHLAobjectRoot manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
