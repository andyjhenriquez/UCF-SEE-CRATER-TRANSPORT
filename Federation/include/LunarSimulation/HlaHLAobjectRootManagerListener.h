/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAHLAOBJECTROOTMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLAHLAOBJECTROOTMANAGERLISTENER_H

#include <LunarSimulation/HlaHLAobjectRoot.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaHLAobjectRoot instances.
    */
    class HlaHLAobjectRootManagerListener {

    public:

        LIBAPI virtual ~HlaHLAobjectRootManagerListener() {}

        /**
        * This method is called when a new HlaHLAobjectRoot instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param hLAobjectRoot the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaHLAobjectRootDiscovered(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaHLAobjectRoot instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param hLAobjectRoot the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaHLAobjectRootInitialized(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaHLAobjectRootManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param hLAobjectRoot the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaHLAobjectRootInInterest(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaHLAobjectRootManagerListener instance goes out of interest.
        *
        * @param hLAobjectRoot the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaHLAobjectRootOutOfInterest(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaHLAobjectRoot instance is deleted.
        *
        * @param hLAobjectRoot the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaHLAobjectRootDeleted(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaHLAobjectRootManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaHLAobjectRootManagerListener::Adapter : public HlaHLAobjectRootManagerListener {

    public:
        LIBAPI virtual void hlaHLAobjectRootDiscovered(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaHLAobjectRootInitialized(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaHLAobjectRootInInterest(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaHLAobjectRootOutOfInterest(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaHLAobjectRootDeleted(HlaHLAobjectRootPtr hLAobjectRoot, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
