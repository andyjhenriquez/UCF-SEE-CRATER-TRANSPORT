/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLADYNAMICALENTITYMANAGER_H
#define DEVELOPER_STUDIO_HLADYNAMICALENTITYMANAGER_H

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
#include <string>
#include <vector>

#include <vector>

#include <LunarSimulation/HlaDynamicalEntityManagerListener.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
   * Manager used to manage HlaDynamicalEntitys.
   */
   class HlaDynamicalEntityManager : private LunarSimulation::noncopyable {

   public:

      LIBAPI virtual ~HlaDynamicalEntityManager() {}

      /**
      * Gets a list of all HlaDynamicalEntitys within interest, both local and remote.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of HlaDynamicalEntitys
      */
      LIBAPI virtual std::vector<HlaDynamicalEntityPtr> getHlaDynamicalEntitys() = 0;

      /**
      * Gets a list of all HlaDynamicalEntitys, both local and remote.
      * HlaDynamicalEntitys not within interest are also included.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of all HlaDynamicalEntitys
      */
      LIBAPI virtual std::vector<HlaDynamicalEntityPtr> getAllHlaDynamicalEntitys() = 0;

      /**
      * Gets a list of local HlaDynamicalEntitys within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of local HlaDynamicalEntitys
      */
      LIBAPI virtual std::vector<HlaDynamicalEntityPtr> getLocalHlaDynamicalEntitys() = 0;

      /**
      * Gets a list of remote HlaDynamicalEntitys within interest.
      * The list is a copy that is allowed to be altered.
      *
      * @return a list of remote HlaDynamicalEntitys
      */
      LIBAPI virtual std::vector<HlaDynamicalEntityPtr> getRemoteHlaDynamicalEntitys() = 0;

      /**
      * Find a HlaDynamicalEntity with the given <code>name</code>.
      * If more than one HlaDynamicalEntity with the given <code>name</code> is present, one of
      * them is returned, it is undefined which. If none is found, <code>null</code> is returned.
      * <p>
      * name was selected as a <i>Lookup</i> attribute.
      *
      * @param name The name that looks up which HlaDynamicalEntity to return.
      *
      * @return an HlaDynamicalEntity, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaDynamicalEntityPtr getDynamicalEntityByName(std::wstring name) = 0;

      /**
      * Find a HlaDynamicalEntity with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> of the HlaDynamicalEntity to find
      *
      * @return the specified HlaDynamicalEntity, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaDynamicalEntityPtr getDynamicalEntityByHlaInstanceName(const std::wstring& hlaInstanceName) = 0;

      /**
      * Find a HlaDynamicalEntity with the given <code>HLA instance name</code>.
      * If none is found, <code>null</code> is returned.
      *
      * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaDynamicalEntity to find
      *
      * @return the specified HlaDynamicalEntity, or <code>null</code> if not found.
      */
      LIBAPI virtual HlaDynamicalEntityPtr getDynamicalEntityByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) = 0;

      /**
      * Creates a new HlaDynamicalEntity, and sets all <i>Create</i> attributes.
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaDynamicalEntity.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaDynamicalEntityPtr createLocalHlaDynamicalEntity(
         std::wstring name
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Creates a new HlaDynamicalEntity with a specified <code>HLA instance name</code>, and sets all
      * <i>Create</i> attributes.
      *
      * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
      * @param name represents the <code>name</code> from the FOM.
      *        <br>Description from the FOM: A non-empty string that identifies the entity. Each entity instance in the federation must have a unique name.
      *        <br>Description of the data type from the FOM: 
      *
      * @return Returns a new local HlaDynamicalEntity.
      *
      * @throws HlaIllegalInstanceNameException if the name is illegal
      * @throws HlaInstanceNameInUseException if the name is already in use
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaDynamicalEntityPtr createLocalHlaDynamicalEntity(
         const std::wstring& hlaInstanceName,
         std::wstring name
      ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                    HlaNotConnectedException, HlaInternalException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaDynamicalEntity and removes it from the federation.
      *
      * @param dynamicalEntity The HlaDynamicalEntity to delete
      *
      * @return the HlaDynamicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity)
          THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                      HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaDynamicalEntity and removes it from the federation.
      *
      * @param dynamicalEntity The HlaDynamicalEntity to delete
      * @param timestamp timestamp when the instance was removed.
      *
      * @return the HlaDynamicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaDynamicalEntity and removes it from the federation.
      *
      * @param dynamicalEntity The HlaDynamicalEntity to delete
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaDynamicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Deletes a local HlaDynamicalEntity and removes it from the federation.
      *
      * @param dynamicalEntity The HlaDynamicalEntity to delete
      * @param timestamp timestamp when the instance was removed.
      * @param logicalTime The logical time for the delete
      *
      * @return the HlaDynamicalEntity deleted, null if it didn't exist.
      *
      * @throws HlaNotConnectedException if the federate is not connected
      * @throws HlaInternalException on internal errors
      * @throws HlaRtiException on exception from the RTI
      * @throws HlaInvalidLogicalTimeException on exception from the RTI
      * @throws HlaSaveInProgressException if a federation save is in progress
      * @throws HlaRestoreInProgressException if a federation restore is in progress
      */
      LIBAPI virtual HlaDynamicalEntityPtr deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
      THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException,
                  HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

      /**
      * Add a HlaDynamicalEntity manager listener.
      *
      * @param managerListener listener to add
      */
      LIBAPI virtual void addHlaDynamicalEntityManagerListener(HlaDynamicalEntityManagerListenerPtr managerListener) = 0;

      /**
      * Removed a HlaDynamicalEntity manager listener.
      *
      * @param managerListener listener to remove
      */
      LIBAPI virtual void removeHlaDynamicalEntityManagerListener(HlaDynamicalEntityManagerListenerPtr managerListener) = 0;

     /**
      * Add a listener that will automatically be added to all instances of HlaDynamicalEntity (Both local and remote).
      * The listener is notified when any attribute of an instance of HlaDynamicalEntity is updated.
      * The listener is also called when an interaction is sent to an instance of HlaDynamicalEntity.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param listener The listener to add.
      */
      LIBAPI virtual void addHlaDynamicalEntityDefaultInstanceListener(HlaDynamicalEntityListenerPtr listener) = 0;

     /**
      * Remove a listener from the set of listeners that are automatically added to new instances of HlaDynamicalEntity.
      * Note: The listener will not be removed from already existing instances of HlaDynamicalEntity.
      * This method is idempotent.
      *
      * @param listener The listener to remove.
      */
      LIBAPI virtual void removeHlaDynamicalEntityDefaultInstanceListener(HlaDynamicalEntityListenerPtr listener) = 0;

     /**
      * Add a valueListener that will automatically be added to all instances of HlaDynamicalEntity (Both local and remote).
      * The  Valuelistener is notified when any attribute of an instance of HlaDynamicalEntity is updated.
      * Note that the attribute values that are notified are not guaranteed to
      * be the latest available values for that attribute.
      * All listeners will automatically be removed when an instance is removed.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to add.
      */
      LIBAPI virtual void addHlaDynamicalEntityDefaultInstanceValueListener(HlaDynamicalEntityValueListenerPtr valueListener) = 0;

     /**
      * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaDynamicalEntity.
      * Note: The valueListener will not be removed from already existing instances of HlaDynamicalEntity.
      * This method is idempotent.
      *
      * @param valueListener The valueListener to remove.
      */
      LIBAPI virtual void removeHlaDynamicalEntityDefaultInstanceValueListener(HlaDynamicalEntityValueListenerPtr valueListener) = 0;

     /**
      * Enables or disables the HlaDynamicalEntity manager.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaDynamicalEntity manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      *
      * @param enabled <code>true</code> to enable the HlaDynamicalEntity manager, otherwise <code>false</code>
      */
      LIBAPI virtual void setEnabled(bool enabled) = 0;

     /**
      * Enables the HlaDynamicalEntity manager if it is available in the FOM at runtime.
      * The manager is enabled by default. The state can only be changed when not connected.
      * When the HlaDynamicalEntity manager is disabled it will act as disconnected,
      * ie throws HlaNotConnectedException.
      */
      LIBAPI virtual void setEnabledIfAvailableInFom() = 0;

     /**
      * Check if the HlaDynamicalEntity manager is actually enabled when connected.
      * An HlaDynamicalEntity manager may be disabled with the <code>setEnabled(false)</code> function, or it may be configured
      * as <i>if available in the FOM</i> by the <code>setEnabledIfAvailableInFom()</code> function and
      * then not available in the FOM at runtime.
      * <p>
      * This method should only be used when connected, it will always return <code>false</code>
      * when not connected.
      *
      * @return <code>true</code> if connected and the HlaDynamicalEntity manager is enabled.
      */
      LIBAPI virtual bool isEnabled() = 0;
   };
}
#endif
