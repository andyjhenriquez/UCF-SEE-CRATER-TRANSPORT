/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLADYNAMICALENTITYMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLADYNAMICALENTITYMANAGERLISTENER_H

#include <LunarSimulation/HlaDynamicalEntity.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaDynamicalEntity instances.
    */
    class HlaDynamicalEntityManagerListener {

    public:

        LIBAPI virtual ~HlaDynamicalEntityManagerListener() {}

        /**
        * This method is called when a new HlaDynamicalEntity instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param dynamicalEntity the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaDynamicalEntityDiscovered(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaDynamicalEntity instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param dynamicalEntity the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaDynamicalEntityInitialized(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaDynamicalEntityManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param dynamicalEntity the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaDynamicalEntityInInterest(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaDynamicalEntityManagerListener instance goes out of interest.
        *
        * @param dynamicalEntity the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaDynamicalEntityOutOfInterest(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaDynamicalEntity instance is deleted.
        *
        * @param dynamicalEntity the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaDynamicalEntityDeleted(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaDynamicalEntityManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaDynamicalEntityManagerListener::Adapter : public HlaDynamicalEntityManagerListener {

    public:
        LIBAPI virtual void hlaDynamicalEntityDiscovered(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaDynamicalEntityInitialized(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaDynamicalEntityInInterest(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaDynamicalEntityOutOfInterest(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaDynamicalEntityDeleted(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
