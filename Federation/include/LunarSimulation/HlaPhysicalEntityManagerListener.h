/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPHYSICALENTITYMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLAPHYSICALENTITYMANAGERLISTENER_H

#include <LunarSimulation/HlaPhysicalEntity.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaPhysicalEntity instances.
    */
    class HlaPhysicalEntityManagerListener {

    public:

        LIBAPI virtual ~HlaPhysicalEntityManagerListener() {}

        /**
        * This method is called when a new HlaPhysicalEntity instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param physicalEntity the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalEntityDiscovered(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPhysicalEntity instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param physicalEntity the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalEntityInitialized(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaPhysicalEntityManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param physicalEntity the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalEntityInInterest(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPhysicalEntityManagerListener instance goes out of interest.
        *
        * @param physicalEntity the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaPhysicalEntityOutOfInterest(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaPhysicalEntity instance is deleted.
        *
        * @param physicalEntity the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaPhysicalEntityDeleted(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaPhysicalEntityManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaPhysicalEntityManagerListener::Adapter : public HlaPhysicalEntityManagerListener {

    public:
        LIBAPI virtual void hlaPhysicalEntityDiscovered(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPhysicalEntityInitialized(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaPhysicalEntityInInterest(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPhysicalEntityOutOfInterest(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaPhysicalEntityDeleted(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
