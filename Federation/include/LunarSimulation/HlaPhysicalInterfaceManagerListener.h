/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALINTERFACEMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLAPHYSICALINTERFACEMANAGERLISTENER_H

#include <LunarSimulation/HlaPhysicalInterface.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaPhysicalInterface instances.
    */
    class HlaPhysicalInterfaceManagerListener {

    public:

        LIBAPI virtual ~HlaPhysicalInterfaceManagerListener() {}

        /**
        * This method is called when a new HlaPhysicalInterface instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param physicalInterface the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalInterfaceDiscovered(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPhysicalInterface instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param physicalInterface the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalInterfaceInitialized(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaPhysicalInterfaceManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param physicalInterface the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalInterfaceInInterest(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPhysicalInterfaceManagerListener instance goes out of interest.
        *
        * @param physicalInterface the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalInterfaceOutOfInterest(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPhysicalInterface instance is deleted.
        *
        * @param physicalInterface the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaPhysicalInterfaceDeleted(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaPhysicalInterfaceManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaPhysicalInterfaceManagerListener::Adapter : public HlaPhysicalInterfaceManagerListener {

    public:
        LIBAPI virtual void hlaPhysicalInterfaceDiscovered(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPhysicalInterfaceInitialized(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaPhysicalInterfaceInInterest(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPhysicalInterfaceOutOfInterest(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPhysicalInterfaceDeleted(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
