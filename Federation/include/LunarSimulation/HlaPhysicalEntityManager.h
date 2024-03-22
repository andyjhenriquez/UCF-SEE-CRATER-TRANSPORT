/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALENTITYMANAGER_H
#define DEVELOPER_STUDIO_HLAPHYSICALENTITYMANAGER_H

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

#include <LunarSimulation/HlaPhysicalEntityManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaPhysicalEntitys.
   */
   class HlaPhysicalEntityManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaPhysicalEntityManager() {}

      /**
      * Gets a list of all HlaPhysicalEntitys within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaPhysicalEntitys
      */
      LIBAPI virtual std::vector<HlaPhysicalEntityPtr> getHlaPhysicalEntitys() = 0;

      /**
      * Gets a list of all HlaPhysicalEntitys, both local and remote.
      * HlaPhysicalEntitys not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaPhysicalEntitys
      */
      LIBAPI virtual std::vector<HlaPhysicalEntityPtr> getAllHlaPhysicalEntitys() = 0;

      /**
      * Gets a list of local HlaPhysicalEntitys within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaPhysicalEntitys
      */
      LIBAPI virtual std::vector<HlaPhysicalEntityPtr> getLocalHlaPhysicalEntitys() = 0;

      /**
      * Gets a list of remote HlaPhysicalEntitys within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaPhysicalEntitys
      */
      LIBAPI virtual std::vector<HlaPhysicalEntityPtr> getRemoteHlaPhysicalEntitys() = 0;

      /**
      * Find a HlaPhysicalEntity with the given <code>name</code>.
      * If more than one HlaPhysicalEntity with the given <code>name</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * name was selected as a <i>Lookup</i> attribute.
      *
      * @param name The name that looks up which HlaPhysicalEntity to return.
      *
      * @return an HlaPhysicalEntity, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaPhysicalEntityPtr getPhysicalEntityByName(std::wstring name) = 0;

      /**
      * Find a HlaPhysicalEntity with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaPhysicalEntity to find
      *
      * @return the specified HlaPhysicalEntity, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaPhysicalEntityPtr getPhysicalEntityByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaPhysicalEntity with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaPhysicalEntity to find
      *
      * @return the specified HlaPhysicalEntity, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaPhysicalEntityPtr getPhysicalEntityByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaPhysicalEntity, and sets all <i>Create</i> attributes.
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaPhysicalEntity.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalEntityPtr createLocalHlaPhysicalEntity(
         std::wstring name
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaPhysicalEntity with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaPhysicalEntity.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalEntityPtr createLocalHlaPhysicalEntity(
         const std::wstring& hlaInstanceName,
         std::wstring name
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalEntity and removes it from the federation.
      *
      * @param physicalEntity The HlaPhysicalEntity to delete
      *
      * @return the HlaPhysicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalEntity and removes it from the federation.
      *
      * @param physicalEntity The HlaPhysicalEntity to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaPhysicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalEntity and removes it from the federation.
      *
      * @param physicalEntity The HlaPhysicalEntity to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaPhysicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaPhysicalEntity and removes it from the federation.
      *
      * @param physicalEntity The HlaPhysicalEntity to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaPhysicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaPhysicalEntityPtr deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaPhysicalEntity manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaPhysicalEntityManagerListener(HlaPhysicalEntityManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaPhysicalEntity manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaPhysicalEntityManagerListener(HlaPhysicalEntityManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaPhysicalEntity (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaPhysicalEntity is updated.
      * The listener is also called when an interaction is sent to an instance of HlaPhysicalEntity.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaPhysicalEntityDefaultInstanceListener(HlaPhysicalEntityListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaPhysicalEntity.
      * Note: The listener will not be removed from already existing instances of HlaPhysicalEntity.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaPhysicalEntityDefaultInstanceListener(HlaPhysicalEntityListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaPhysicalEntity (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaPhysicalEntity is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaPhysicalEntityDefaultInstanceValueListener(HlaPhysicalEntityValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaPhysicalEntity.
      * Note: The valueListener will not be removed from already existing instances of HlaPhysicalEntity.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaPhysicalEntityDefaultInstanceValueListener(HlaPhysicalEntityValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaPhysicalEntity manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaPhysicalEntity manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaPhysicalEntity manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaPhysicalEntity manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaPhysicalEntity manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaPhysicalEntity manager is actually enabled when connected.
      * An HlaPhysicalEntity manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaPhysicalEntity manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
