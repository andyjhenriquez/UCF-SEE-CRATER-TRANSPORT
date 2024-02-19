/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPAYLOADMANAGER_H
#define DEVELOPER_STUDIO_HLAPAYLOADMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/AccelerationVector.h>
#include <LunarSimulation/datatypes/AngularAccelerationVector.h>
#include <LunarSimulation/datatypes/AttitudeQuaternion.h>
#include <LunarSimulation/datatypes/ForceVector.h>
#include <LunarSimulation/datatypes/InertiaMatrix.h>
#include <LunarSimulation/datatypes/InertiaRateMatrix.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <LunarSimulation/datatypes/TorqueVector.h>
#include <LunarSimulation/datatypes/VelocityVector.h>
#include <string>
#include <vector>

#include <vector>

#include <LunarSimulation/HlaPayloadManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaPayloads.
   */
   class HlaPayloadManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaPayloadManager() {}

      /**
      * Gets a list of all HlaPayloads within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaPayloads
      */
      LIBAPI virtual std::vector<HlaPayloadPtr> getHlaPayloads() = 0;

      /**
      * Gets a list of all HlaPayloads, both local and remote.
      * HlaPayloads not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaPayloads
      */
      LIBAPI virtual std::vector<HlaPayloadPtr> getAllHlaPayloads() = 0;

      /**
      * Gets a list of local HlaPayloads within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaPayloads
      */
      LIBAPI virtual std::vector<HlaPayloadPtr> getLocalHlaPayloads() = 0;

      /**
      * Gets a list of remote HlaPayloads within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaPayloads
      */
      LIBAPI virtual std::vector<HlaPayloadPtr> getRemoteHlaPayloads() = 0;

      /**
      * Find a HlaPayload with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaPayload to find
      *
      * @return the specified HlaPayload, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaPayloadPtr getPayloadByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaPayload with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaPayload to find
      *
      * @return the specified HlaPayload, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaPayloadPtr getPayloadByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaPayload, and sets all <i>Create</i> attributes.
      *
      * @return Returns a new local HlaPayload.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPayloadPtr createLocalHlaPayload(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaPayload with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      *
      * @return Returns a new local HlaPayload.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPayloadPtr createLocalHlaPayload(
         const std::wstring& hlaInstanceName
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPayload and removes it from the federation.
      *
      * @param payload The HlaPayload to delete
      *
      * @return the HlaPayload deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPayload and removes it from the federation.
      *
      * @param payload The HlaPayload to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaPayload deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPayload and removes it from the federation.
      *
      * @param payload The HlaPayload to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaPayload deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPayload and removes it from the federation.
      *
      * @param payload The HlaPayload to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaPayload deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPayloadPtr deleteLocalHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaPayload manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaPayloadManagerListener(HlaPayloadManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaPayload manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaPayloadManagerListener(HlaPayloadManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaPayload (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaPayload is updated.
      * The listener is also called when an interaction is sent to an instance of HlaPayload.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaPayloadDefaultInstanceListener(HlaPayloadListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaPayload.
      * Note: The listener will not be removed from already existing instances of HlaPayload.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaPayloadDefaultInstanceListener(HlaPayloadListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaPayload (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaPayload is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaPayload.
      * Note: The valueListener will not be removed from already existing instances of HlaPayload.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaPayload manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaPayload manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaPayload manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaPayload manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaPayload manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaPayload manager is actually enabled when connected.
      * An HlaPayload manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaPayload manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
