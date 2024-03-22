/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALAUNCHERMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLALAUNCHERMANAGERLISTENER_H

#include <LunarSimulation/HlaLauncher.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaLauncher instances.
    */
    class HlaLauncherManagerListener {

    public:

        LIBAPI virtual ~HlaLauncherManagerListener() {}

        /**
        * This method is called when a new HlaLauncher instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param launcher the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaLauncherDiscovered(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaLauncher instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param launcher the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaLauncherInitialized(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaLauncherManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param launcher the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaLauncherInInterest(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaLauncherManagerListener instance goes out of interest.
        *
        * @param launcher the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaLauncherOutOfInterest(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaLauncher instance is deleted.
        *
        * @param launcher the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaLauncherDeleted(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaLauncherManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaLauncherManagerListener::Adapter : public HlaLauncherManagerListener {

    public:
        LIBAPI virtual void hlaLauncherDiscovered(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaLauncherInitialized(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaLauncherInInterest(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaLauncherOutOfInterest(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaLauncherDeleted(HlaLauncherPtr launcher, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
