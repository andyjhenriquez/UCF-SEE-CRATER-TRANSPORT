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
 * Manager used to manage HlaMoons.
 * <p>
 * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public interface HlaMoonManager {

   /**
    * Gets a list of all HlaMoons within interest, both local and remote.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of HlaMoons
    */
    List<HlaMoon> getHlaMoons();

   /**
    * Gets a list of all HlaMoons, both local and remote.
    * HlaMoons not within interest are also included.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of all HlaMoons
    */
    List<HlaMoon> getAllHlaMoons();

   /**
    * Gets a list of local HlaMoons within interest.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of local HlaMoons
    */
    List<HlaMoon> getLocalHlaMoons();

   /**
    * Gets a list of remote HlaMoons within interest.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of remote HlaMoons
    */
    List<HlaMoon> getRemoteHlaMoons();

   /**
    * Find a HlaMoon with the given <code>HLA instance name</code>.
    * If none is found, <code>null</code> is returned.
    *
    * @param hlaInstanceName the <code>HLA instance name</code> of the HlaMoon to find
    *
    * @return the specified HlaMoon, or <code>null</code> if not found.
    */
   HlaMoon getMoonByHlaInstanceName(String hlaInstanceName);

   /**
    * Find a HlaMoon with the given <code>HLA instance name</code>.
    * If none is found, <code>null</code> is returned.
    *
    * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaMoon to find
    *
    * @return the specified HlaMoon, or <code>null</code> if not found.
    */
   HlaMoon getMoonByHlaInstanceHandle(byte[] encodedHlaInstanceHandle);

   /**
    * Creates a new HlaMoon, and sets all <i>Create</i> attributes.
    *
    *
    * @return Returns a new local HlaMoon.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaMoon createLocalHlaMoon(
    ) throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;


   /**
    * Creates a new HlaMoon with a specified <code>HLA instance name</code>, and sets all
    * <i>Create</i> attributes.
    *
    * @param hlaInstanceName the <code>HLA instance name</code> to register for this instance
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
    HlaMoon createLocalHlaMoon(
       String hlaInstanceName
    ) throws HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
             HlaNotConnectedException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;


   /**
    * Deletes a local HlaMoon and removes it from the federation.
    *
    * @param moon The HlaMoon to delete
    *
    * @return the HlaMoon deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaMoon deleteLocalHlaMoon(HlaMoon moon)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaMoon and removes it from the federation with a specified timestamp
    *
    * @param moon The HlaMoon to delete
    * @param timestamp timestamp when the instance was removed.
    *
    * @return the HlaMoon deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaMoon deleteLocalHlaMoon(HlaMoon moon, HlaTimeStamp timestamp)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaMoon and removes it from the federation at a specified logical time.
    *
    * @param moon The HlaMoon to delete
    * @param logicalTime The logical time when the instance was removed.
    *
    * @return the HlaMoon deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaMoon deleteLocalHlaMoon(HlaMoon moon, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaMoon and removes it from the federation with a specified timestamp at a specified logical time.
    *
    * @param moon The HlaMoon to delete
    * @param timestamp timestamp when the instance was removed.
    * @param logicalTime The logical time when the instance was removed.
    *
    * @return the HlaMoon deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaMoon deleteLocalHlaMoon(HlaMoon moon, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

    /**
     * Add an HlaMoon manager listener.
     *
     * @param managerListener listener to add
     */
    void addHlaMoonManagerListener(HlaMoonManagerListener managerListener);

    /**
     * Remove an HlaMoon manager listener.
     *
     * @param managerListener listener to remove
     */
    void removeHlaMoonManagerListener(HlaMoonManagerListener managerListener);

    /**
     * Add a listener that will automatically be added to all instances of HlaMoon (Both local and remote).
     * The listener is notified when any attribute of an instance of HlaMoon is updated.
     * The listener is also called when an interaction is sent to an instance of HlaMoon.
     * All listeners will automatically be removed when an instance is removed.
     * This method is idempotent.
     *
     * @param listener The listener to add.
     */
    void addHlaMoonDefaultInstanceListener(HlaMoonListener listener);

    /**
     * Remove a listener from the set of listeners that are automatically added to new instances of HlaMoon.
     * Note: The listener will not be removed from already existing instances of HlaMoon.
     * This method is idempotent.
     *
     * @param listener The listener to remove.
     */
    void removeHlaMoonDefaultInstanceListener(HlaMoonListener listener);

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
    void addHlaMoonDefaultInstanceValueListener(HlaMoonValueListener valueListener);

    /**
     * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaMoon.
     * Note: The valueListener will not be removed from already existing instances of HlaMoon.
     * This method is idempotent.
     *
     * @param valueListener The valueListener to remove.
     */
    void removeHlaMoonDefaultInstanceValueListener(HlaMoonValueListener valueListener);

    /**
     * Enables or disables the HlaMoon manager.
     * The manager is enabled by default. The state can only be changed when not connected.
     * When the HlaMoon manager is disabled it will act as disconnected,
     * ie throws HlaNotConnectedException.
     *
     * @param enabled <code>true</code> to enable the HlaMoon manager, otherwise <code>false</code>
     */
    void setEnabled(boolean enabled);

    /**
     * Enables the HlaMoon manager if it is available in the FOM at runtime.
     * The manager is enabled by default. The state can only be changed when not connected.
     * When the HlaMoon manager is disabled it will act as disconnected,
     * ie throws HlaNotConnectedException.
     */
    void setEnabledIfAvailableInFom();

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
    boolean isEnabled();
}

