/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPAYLOADMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLAPAYLOADMANAGERLISTENER_H

#include <LunarSimulation/HlaPayload.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaPayload instances.
    */
    class HlaPayloadManagerListener {

    public:

        LIBAPI virtual ~HlaPayloadManagerListener() {}

        /**
        * This method is called when a new HlaPayload instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param payload the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPayloadDiscovered(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPayload instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param payload the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaPayloadInitialized(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaPayloadManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param payload the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPayloadInInterest(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPayloadManagerListener instance goes out of interest.
        *
        * @param payload the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPayloadOutOfInterest(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPayload instance is deleted.
        *
        * @param payload the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaPayloadDeleted(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaPayloadManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaPayloadManagerListener::Adapter : public HlaPayloadManagerListener {

    public:
        LIBAPI virtual void hlaPayloadDiscovered(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPayloadInitialized(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaPayloadInInterest(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPayloadOutOfInterest(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPayloadDeleted(HlaPayloadPtr payload, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
