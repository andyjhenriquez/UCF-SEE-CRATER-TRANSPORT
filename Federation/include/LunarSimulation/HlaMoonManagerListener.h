/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAMOONMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLAMOONMANAGERLISTENER_H

#include <LunarSimulation/HlaMoon.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaMoon instances.
    */
    class HlaMoonManagerListener {

    public:

        LIBAPI virtual ~HlaMoonManagerListener() {}

        /**
        * This method is called when a new HlaMoon instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param moon the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaMoonDiscovered(HlaMoonPtr moon, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaMoon instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param moon the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaMoonInitialized(HlaMoonPtr moon, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaMoonManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param moon the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaMoonInInterest(HlaMoonPtr moon, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaMoonManagerListener instance goes out of interest.
        *
        * @param moon the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaMoonOutOfInterest(HlaMoonPtr moon, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaMoon instance is deleted.
        *
        * @param moon the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaMoonDeleted(HlaMoonPtr moon, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaMoonManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaMoonManagerListener::Adapter : public HlaMoonManagerListener {

    public:
        LIBAPI virtual void hlaMoonDiscovered(HlaMoonPtr moon, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaMoonInitialized(HlaMoonPtr moon, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaMoonInInterest(HlaMoonPtr moon, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaMoonOutOfInterest(HlaMoonPtr moon, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaMoonDeleted(HlaMoonPtr moon, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
