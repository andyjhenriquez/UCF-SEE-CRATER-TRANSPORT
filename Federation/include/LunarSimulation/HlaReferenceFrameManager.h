/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAREFERENCEFRAMEMANAGER_H
#define DEVELOPER_STUDIO_HLAREFERENCEFRAMEMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>

#include <vector>

#include <LunarSimulation/HlaReferenceFrameManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaReferenceFrames.
   */
   class HlaReferenceFrameManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaReferenceFrameManager() {}

      /**
      * Gets a list of all HlaReferenceFrames within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaReferenceFrames
      */
      LIBAPI virtual std::vector<HlaReferenceFramePtr> getHlaReferenceFrames() = 0;

      /**
      * Gets a list of all HlaReferenceFrames, both local and remote.
      * HlaReferenceFrames not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaReferenceFrames
      */
      LIBAPI virtual std::vector<HlaReferenceFramePtr> getAllHlaReferenceFrames() = 0;

      /**
      * Gets a list of local HlaReferenceFrames within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaReferenceFrames
      */
      LIBAPI virtual std::vector<HlaReferenceFramePtr> getLocalHlaReferenceFrames() = 0;

      /**
      * Gets a list of remote HlaReferenceFrames within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaReferenceFrames
      */
      LIBAPI virtual std::vector<HlaReferenceFramePtr> getRemoteHlaReferenceFrames() = 0;

      /**
      * Find a HlaReferenceFrame with the given <code>name</code>.
      * If more than one HlaReferenceFrame with the given <code>name</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * name was selected as a <i>Lookup</i> attribute.
      *
      * @param name The name that looks up which HlaReferenceFrame to return.
      *
      * @return an HlaReferenceFrame, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaReferenceFramePtr getReferenceFrameByName(std::wstring name) = 0;

      /**
      * Find a HlaReferenceFrame with the given <code>parentName</code>.
      * If more than one HlaReferenceFrame with the given <code>parentName</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * parentName was selected as a <i>Lookup</i> attribute.
      *
      * @param parentName The parentName that looks up which HlaReferenceFrame to return.
      *
      * @return an HlaReferenceFrame, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaReferenceFramePtr getReferenceFrameByParent_name(std::wstring parentName) = 0;

      /**
      * Find a HlaReferenceFrame with the given <code>state</code>.
      * If more than one HlaReferenceFrame with the given <code>state</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * state was selected as a <i>Lookup</i> attribute.
      *
      * @param state The state that looks up which HlaReferenceFrame to return.
      *
      * @return an HlaReferenceFrame, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaReferenceFramePtr getReferenceFrameByState(SpaceTimeCoordinateState state) = 0;

      /**
      * Find a HlaReferenceFrame with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaReferenceFrame to find
      *
      * @return the specified HlaReferenceFrame, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaReferenceFramePtr getReferenceFrameByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaReferenceFrame with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaReferenceFrame to find
      *
      * @return the specified HlaReferenceFrame, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaReferenceFramePtr getReferenceFrameByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaReferenceFrame, and sets all <i>Create</i> attributes.
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaReferenceFrame.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaReferenceFramePtr createLocalHlaReferenceFrame(
         std::wstring name
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaReferenceFrame with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaReferenceFrame.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaReferenceFramePtr createLocalHlaReferenceFrame(
         const std::wstring& hlaInstanceName,
         std::wstring name
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaReferenceFrame and removes it from the federation.
      *
      * @param referenceFrame The HlaReferenceFrame to delete
      *
      * @return the HlaReferenceFrame deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaReferenceFrame and removes it from the federation.
      *
      * @param referenceFrame The HlaReferenceFrame to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaReferenceFrame deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaReferenceFrame and removes it from the federation.
      *
      * @param referenceFrame The HlaReferenceFrame to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaReferenceFrame deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaReferenceFrame and removes it from the federation.
      *
      * @param referenceFrame The HlaReferenceFrame to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaReferenceFrame deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaReferenceFramePtr deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaReferenceFrame manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaReferenceFrameManagerListener(HlaReferenceFrameManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaReferenceFrame manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaReferenceFrameManagerListener(HlaReferenceFrameManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaReferenceFrame (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaReferenceFrame is updated.
      * The listener is also called when an interaction is sent to an instance of HlaReferenceFrame.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaReferenceFrameDefaultInstanceListener(HlaReferenceFrameListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaReferenceFrame.
      * Note: The listener will not be removed from already existing instances of HlaReferenceFrame.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaReferenceFrameDefaultInstanceListener(HlaReferenceFrameListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaReferenceFrame (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaReferenceFrame is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaReferenceFrameDefaultInstanceValueListener(HlaReferenceFrameValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaReferenceFrame.
      * Note: The valueListener will not be removed from already existing instances of HlaReferenceFrame.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaReferenceFrameDefaultInstanceValueListener(HlaReferenceFrameValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaReferenceFrame manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaReferenceFrame manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaReferenceFrame manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaReferenceFrame manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaReferenceFrame manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaReferenceFrame manager is actually enabled when connected.
      * An HlaReferenceFrame manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaReferenceFrame manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
