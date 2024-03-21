/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAWORLDLISTENER_H
#define DEVELOPER_STUDIO_HLAWORLDLISTENER_H

#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPointers.h>

namespace LunarSimulation {
    /**
    * A HlaWorldListener is notified of connects and disconnects.
    */
    class HlaWorldListener {
    public:

        LIBAPI virtual ~HlaWorldListener() {}

         /**
         * This method is called when the federate is connected.
         *
         * @param timeStamp The time when the world was connected.
         */
        LIBAPI virtual void connected(HlaTimeStampPtr timeStamp) = 0;

        /**
         * This method is called when the federate is disconnected.
         *
         * @param timeStamp The time when the world was disconnected.
         */
        LIBAPI virtual void disconnected(HlaTimeStampPtr timeStamp) = 0;


        /**
         * This method is called when the federate requests to advance the logical time.
         *
         * @param timeStamp The time when the request was initiated.
         * @param requestedTime The requested logical time.
         */
        LIBAPI virtual void timeAdvanceRequested(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr requestedTime) = 0;

        /**
         * This method is called when the federates request to advance the logical time is granted.
         *
         * @param timeStamp The time when the request was granted.
         * @param grantedTime The granted logical time.
         */
        LIBAPI virtual void timeAdvanceGranted(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr grantedTime) = 0;

        class Adapter;
    };


    /**
    * An adapter class that implements the HlaWorldListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaWorldListener::Adapter : public HlaWorldListener {
    public:

        LIBAPI virtual void connected(HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void disconnected(HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void timeAdvanceRequested(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr requestedTime) {}
        LIBAPI virtual void timeAdvanceGranted(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr grantedTime) {}

    };

}
#endif
