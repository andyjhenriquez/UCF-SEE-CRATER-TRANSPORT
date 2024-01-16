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
 * Manager used to manage HlaPayloads.
 * <p>
 * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public interface HlaPayloadManager {

   /**
    * Gets a list of all HlaPayloads within interest, both local and remote.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of HlaPayloads
    */
    List<HlaPayload> getHlaPayloads();

   /**
    * Gets a list of all HlaPayloads, both local and remote.
    * HlaPayloads not within interest are also included.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of all HlaPayloads
    */
    List<HlaPayload> getAllHlaPayloads();

   /**
    * Gets a list of local HlaPayloads within interest.
    * The list is a copy that is allowed to be altered.
    *
    * @return a list of local HlaPayloads
    */
    List<HlaPayload> getLocalHlaPayloads();

   /**
    * Find a HlaPayload with the given <code>HLA instance name</code>.
    * If none is found, <code>null</code> is returned.
    *
    * @param hlaInstanceName the <code>HLA instance name</code> of the HlaPayload to find
    *
    * @return the specified HlaPayload, or <code>null</code> if not found.
    */
   HlaPayload getPayloadByHlaInstanceName(String hlaInstanceName);

   /**
    * Find a HlaPayload with the given <code>HLA instance name</code>.
    * If none is found, <code>null</code> is returned.
    *
    * @param encodedHlaInstanceHandle the encoded <code>HLA instance handle</code> of the HlaPayload to find
    *
    * @return the specified HlaPayload, or <code>null</code> if not found.
    */
   HlaPayload getPayloadByHlaInstanceHandle(byte[] encodedHlaInstanceHandle);

   /**
    * Creates a new HlaPayload, and sets all <i>Create</i> attributes.
    *
    *
    * @return Returns a new local HlaPayload.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaPayload createLocalHlaPayload(
    ) throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;


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
    HlaPayload createLocalHlaPayload(
       String hlaInstanceName
    ) throws HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
             HlaNotConnectedException, HlaInternalException, HlaRtiException,
             HlaSaveInProgressException, HlaRestoreInProgressException;


   /**
    * Deletes a local HlaPayload and removes it from the federation.
    *
    * @param payload The HlaPayload to delete
    *
    * @return the HlaPayload deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaPayload deleteLocalHlaPayload(HlaPayload payload)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaPayload and removes it from the federation with a specified timestamp
    *
    * @param payload The HlaPayload to delete
    * @param timestamp timestamp when the instance was removed.
    *
    * @return the HlaPayload deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaPayload deleteLocalHlaPayload(HlaPayload payload, HlaTimeStamp timestamp)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaPayload and removes it from the federation at a specified logical time.
    *
    * @param payload The HlaPayload to delete
    * @param logicalTime The logical time when the instance was removed.
    *
    * @return the HlaPayload deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaPayload deleteLocalHlaPayload(HlaPayload payload, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Deletes a local HlaPayload and removes it from the federation with a specified timestamp at a specified logical time.
    *
    * @param payload The HlaPayload to delete
    * @param timestamp timestamp when the instance was removed.
    * @param logicalTime The logical time when the instance was removed.
    *
    * @return the HlaPayload deleted, null if it did not exist.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    HlaPayload deleteLocalHlaPayload(HlaPayload payload, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

    /**
     * Add an HlaPayload manager listener.
     *
     * @param managerListener listener to add
     */
    void addHlaPayloadManagerListener(HlaPayloadManagerListener managerListener);

    /**
     * Remove an HlaPayload manager listener.
     *
     * @param managerListener listener to remove
     */
    void removeHlaPayloadManagerListener(HlaPayloadManagerListener managerListener);

    /**
     * Add a listener that will automatically be added to all instances of HlaPayload (Both local and remote).
     * The listener is notified when any attribute of an instance of HlaPayload is updated.
     * The listener is also called when an interaction is sent to an instance of HlaPayload.
     * All listeners will automatically be removed when an instance is removed.
     * This method is idempotent.
     *
     * @param listener The listener to add.
     */
    void addHlaPayloadDefaultInstanceListener(HlaPayloadListener listener);

    /**
     * Remove a listener from the set of listeners that are automatically added to new instances of HlaPayload.
     * Note: The listener will not be removed from already existing instances of HlaPayload.
     * This method is idempotent.
     *
     * @param listener The listener to remove.
     */
    void removeHlaPayloadDefaultInstanceListener(HlaPayloadListener listener);

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
    void addHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListener valueListener);

    /**
     * Remove a valueListener from the set of listeners that are automatically added to new instances of HlaPayload.
     * Note: The valueListener will not be removed from already existing instances of HlaPayload.
     * This method is idempotent.
     *
     * @param valueListener The valueListener to remove.
     */
    void removeHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListener valueListener);

    /**
     * Enables or disables the HlaPayload manager.
     * The manager is enabled by default. The state can only be changed when not connected.
     * When the HlaPayload manager is disabled it will act as disconnected,
     * ie throws HlaNotConnectedException.
     *
     * @param enabled <code>true</code> to enable the HlaPayload manager, otherwise <code>false</code>
     */
    void setEnabled(boolean enabled);

    /**
     * Enables the HlaPayload manager if it is available in the FOM at runtime.
     * The manager is enabled by default. The state can only be changed when not connected.
     * When the HlaPayload manager is disabled it will act as disconnected,
     * ie throws HlaNotConnectedException.
     */
    void setEnabledIfAvailableInFom();

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
    boolean isEnabled();
}

