/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAREFERENCEFRAMEMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLAREFERENCEFRAMEMANAGERLISTENER_H

#include <LunarSimulation/HlaReferenceFrame.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaReferenceFrame instances.
    */
    class HlaReferenceFrameManagerListener {

    public:

        LIBAPI virtual ~HlaReferenceFrameManagerListener() {}

        /**
        * This method is called when a new HlaReferenceFrame instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param referenceFrame the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaReferenceFrameDiscovered(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaReferenceFrame instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param referenceFrame the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaReferenceFrameInitialized(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaReferenceFrameManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param referenceFrame the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaReferenceFrameInInterest(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaReferenceFrameManagerListener instance goes out of interest.
        *
        * @param referenceFrame the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaReferenceFrameOutOfInterest(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaReferenceFrame instance is deleted.
        *
        * @param referenceFrame the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaReferenceFrameDeleted(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaReferenceFrameManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaReferenceFrameManagerListener::Adapter : public HlaReferenceFrameManagerListener {

    public:
        LIBAPI virtual void hlaReferenceFrameDiscovered(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaReferenceFrameInitialized(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaReferenceFrameInInterest(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaReferenceFrameOutOfInterest(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaReferenceFrameDeleted(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
