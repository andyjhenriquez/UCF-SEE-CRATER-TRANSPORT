/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAREFERENCEFRAMEUPDATER_H
#define DEVELOPER_STUDIO_HLAREFERENCEFRAMEUPDATER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>
#include <string>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaHLAobjectRootUpdater.h>

namespace LunarSimulation {

    /**
    * Updater used to update attribute values.
    */
    class HlaReferenceFrameUpdater : public HlaHLAobjectRootUpdater {

    public:

    LIBAPI virtual ~HlaReferenceFrameUpdater() {}

    /**
    * Set the name for this update.
    * <br>Description from the FOM: A unique name for this reference frame instance. Reference frame names are essential in forming 'links' between parent/child reference frames.
    * <br>Description of the data type from the FOM: 
    *
    * @param name the new name
    */
    LIBAPI virtual void setName(const std::wstring& name) = 0;

    /**
    * Set the parentName for this update.
    * <br>Description from the FOM: The name of this frame's parent reference frame. If this frame has no parent (i.e., is a 'root' reference frame), then this string must be empty, otherwise the non-empty string must correspond to the name attribute of some other ReferenceFrame object instance in the simulation.
    * <br>Description of the data type from the FOM: 
    *
    * @param parentName the new parentName
    */
    LIBAPI virtual void setParentName(const std::wstring& parentName) = 0;

    /**
    * Set the state for this update.
    * <br>Description from the FOM: A four dimensional representation of the reference frame with respect to its parent reference frame.  If the parent fame is an empty string, then only the time dimension has meaning.
    * <br>Description of the data type from the FOM: A multi-dimensional representation of an observational coordinate frame and associated state.  There are three spatial dimensions, three attitude dimensions and one time dimension.  The spatial and attitude components define a right-handed orthogonal set of coordinate axes that constitute a reference frame.  The time dimension specifies the 'position' of the coordinate with respect to the physical time scale (TT).
    *
    * @param state the new state
    */
    LIBAPI virtual void setState(const LunarSimulation::SpaceTimeCoordinateState& state) = 0;

    /**
    * Send all the attributes.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate()
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

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
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate(HlaTimeStampPtr timestamp)
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

    /**
    * Send all the attributes with a specified timestamp.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate(HlaLogicalTimePtr logicalTime)
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;

    /**
    * Send all the attributes with a specified timestamp.
    * Note that the <code>Updater</code> can not be reused after <code>sendUpdate</code> has been called.
    *
    * @param timestamp timestamp to send for this update
    * @param logicalTime logical time to send for this update
    *
    * @throws HlaNotConnectedException if the federate is not connected
    * @throws HlaInternalException on internal errors
    * @throws HlaRtiException on exception from the RTI
    * @throws HlaAttributeNotOwnedException if a changed attribute is not owned
    * @throws HlaUpdaterReusedException if the Updater is reused
    * @throws HlaObjectInstanceIsRemovedException if the object instance is removed
    * @throws HlaInvalidLogicalTimeException if the logical time is not valid.
    * @throws HlaSaveInProgressException if a federation save is in progress
    * @throws HlaRestoreInProgressException if a federation restore is in progress
    */
    LIBAPI virtual void sendUpdate(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
        THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) = 0;
    };
}
#endif
