package core;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

import core.exceptions.*;
import java.util.List;


/**
 * Manager used to manage HlaLaunchers.
 * <p>
 * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public interface HlaLauncherManager {

   /**
    * Gets a list of all HlaLaunchers within interest, both local and remote.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of HlaLaunchers
    */
    List<HlaLauncher> getHlaLaunchers();

   /**
    * Gets a list of all HlaLaunchers, both local and remote.
    * HlaLaunchers not within interest are also included.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of all HlaLaunchers
    */
    List<HlaLauncher> getAllHlaLaunchers();

   /**
    * Gets a list of local HlaLaunchers within interest.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of local HlaLaunchers
    */
    List<HlaLauncher> getLocalHlaLaunchers();

   /**
    * Gets a list of remote HlaLaunchers within interest.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of remote HlaLaunchers
    */
    List<HlaLauncher> getRemoteHlaLaunchers();

   /**
    * Find a HlaLauncher with the given <code>HLA instance name</code>.
    * If none is found, <code>null</code> is returned.
    *
    * @param hlaInstanceName the <code>HLA instance name</code> of the HlaLauncher to find
    *
    * @return the specified HlaLauncher, or <code>null</code> if not found.
    */
   HlaLauncher getLauncherByHlaInstanceName(String hlaInstanceName);

   /**
    * Find a HlaLauncher with the given <code>HLA instance name</code>.
    * If none is found, <code>null</code> is returned.
    *
    * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaLauncher to find
    *
    * @return the specified HlaLauncher, or <code>null</code> if not found.
    */
   HlaLauncher getLauncherByHlaInstanceHandle(byte[] encodedHlaInstanceHandle);

   /**
    * Creates a new HlaLauncher, and sets all <i>Create</i> attributes.
    *
    *
    * @return Returns a new local HlaLauncher.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaLauncher createLocalHlaLauncher(
    ) throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;


   /**
    * Creates a new HlaLauncher with a specified <code>HLA instance name</code>, and sets all
    * <i>Create</i> attributes.
    *
    * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
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
    HlaLauncher createLocalHlaLauncher(
       String hlaInstanceName
    ) throws HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
             HlaNotConnectedException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;


   /**
    * Deletes a local HlaLauncher and removes it from the federation.
    *
    * @param launcher The HlaLauncher to delete
    *
    * @return the HlaLauncher deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaLauncher deleteLocalHlaLauncher(HlaLauncher launcher)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaLauncher and removes it from the federation with a specified timestamp
    *
    * @param launcher The HlaLauncher to delete
    * @param timestamp timestamp when the instance was removed.
    *
    * @return the HlaLauncher deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaLauncher deleteLocalHlaLauncher(HlaLauncher launcher, HlaTimeStamp timestamp)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaLauncher and removes it from the federation at a specified logical time.
    *
    * @param launcher The HlaLauncher to delete
    * @param logicalTime The logical time when the instance was removed.
    *
    * @return the HlaLauncher deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaLauncher deleteLocalHlaLauncher(HlaLauncher launcher, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaLauncher and removes it from the federation with a specified timestamp at a specified logical time.
    *
    * @param launcher The HlaLauncher to delete
    * @param timestamp timestamp when the instance was removed.
    * @param logicalTime The logical time when the instance was removed.
    *
    * @return the HlaLauncher deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaLauncher deleteLocalHlaLauncher(HlaLauncher launcher, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

    /**
     * Add an HlaLauncher manager listener.
     *
     * @param managerListener listener to add
     */
    void addHlaLauncherManagerListener(HlaLauncherManagerListener managerListener);

    /**
     * Remove an HlaLauncher manager listener.
     *
     * @param managerListener listener to remove
     */
    void removeHlaLauncherManagerListener(HlaLauncherManagerListener managerListener);

    /**
     * Add a listener that will automatically be added to all instances of HlaLauncher (Both local and remote).
     * The listener is notified when any attribute of an instance of HlaLauncher is updated.
     * The listener is also called when an interaction is sent to an instance of HlaLauncher.
     * All listeners will automatically be removed when an instance is removed.
     * This method is idempotent.
     *
     * @param listener The listener to add.
     */
    void addHlaLauncherDefaultInstanceListener(HlaLauncherListener listener);

    /**
     * Remove a listener from the set of listeners that are automatically added to new instances of HlaLauncher.
     * Note: The listener will not be removed from already existing instances of HlaLauncher.
     * This method is idempotent.
     *
     * @param listener The listener to remove.
     */
    void removeHlaLauncherDefaultInstanceListener(HlaLauncherListener listener);

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
    void addHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListener valueListener);

    /**
     * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaLauncher.
     * Note: The valueListener will not be removed from already existing instances of HlaLauncher.
     * This method is idempotent.
     *
     * @param valueListener The valueListener to remove.
     */
    void removeHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListener valueListener);

    /**
     * Enables or disables the HlaLauncher manager.
     * The manager is enabled by default. The state can only be changed when not connected.
     * When the HlaLauncher manager is disabled it will act as disconnected,
     * ie throws HlaNotConnectedException.
     *
     * @param enabled <code>true</code> to enable the HlaLauncher manager, otherwise <code>false</code>
     */
    void setEnabled(boolean enabled);

    /**
     * Enables the HlaLauncher manager if it is available in the FOM at runtime.
     * The manager is enabled by default. The state can only be changed when not connected.
     * When the HlaLauncher manager is disabled it will act as disconnected,
     * ie throws HlaNotConnectedException.
     */
    void setEnabledIfAvailableInFom();

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
    boolean isEnabled();
}

