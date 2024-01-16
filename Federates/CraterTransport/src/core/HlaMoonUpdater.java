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

import core.datatypes.SpaceTimeCoordinateState;
import core.exceptions.*;


/**
 * Updater used to update attribute values.
 * <p>
 * This class is <code>ThreadSafe</code> as defined by <i>Java Concurrency in Practice</i>,
 * see <a href="http://jcip.net/annotations/doc/net/jcip/annotations/package-summary.html">jcip.net</a>.
 */
public interface HlaMoonUpdater extends HlaReferenceFrameUpdater {

   /**
    * Set the name for this update.
    * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
    * <br>Description of the data type from the FOM: 
    *
    * @param name the new name
    *
    * @return this updater
    */
    HlaMoonUpdater setName(String name);

   /**
    * Set the parentName for this update.
    * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
    * <br>Description of the data type from the FOM: 
    *
    * @param parentName the new parentName
    *
    * @return this updater
    */
    HlaMoonUpdater setParentName(String parentName);

   /**
    * Set the state for this update.
    * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
    * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
    *
    * @param state the new state
    *
    * @return this updater
    */
    HlaMoonUpdater setState(SpaceTimeCoordinateState state);

   /**
    * Send all the attributes.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate()
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Send all the attributes with a specified timestamp.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param timestamp timestamp to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate(HlaTimeStamp timestamp)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Send all the attributes with a specified logical time.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate(HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException,
                HlaInvalidLogicalTimeException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;

   /**
    * Send all the attributes with a specified timestamp and logical time.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param timestamp timestamp to send for this update
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaInvalidLogicalTimeException if the logical time is invalid
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance has been removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    void sendUpdate(HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException,
                HlaInvalidLogicalTimeException, HlaUpdaterReusedException,
                HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException;
}
