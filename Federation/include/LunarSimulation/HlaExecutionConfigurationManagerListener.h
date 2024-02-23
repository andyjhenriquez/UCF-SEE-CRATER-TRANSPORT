/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONMANAGERLISTENER_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONMANAGERLISTENER_H

#include <LunarSimulation/HlaExecutionConfiguration.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

    /**
    * Listener for changes of HlaExecutionConfiguration instances.
    */
    class HlaExecutionConfigurationManagerListener {

    public:

        LIBAPI virtual ~HlaExecutionConfigurationManagerListener() {}

        /**
        * This method is called when a new HlaExecutionConfiguration instance is discovered.
        * A discovered instance is initially within interest.
        *
        * @param executionConfiguration the object which is discovered
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaExecutionConfigurationDiscovered(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaExecutionConfiguration instance is initialized.
        * An instance is initialized when it has been discovered and all attribute marked with
        * <i>initialized</i> has a value.
        *
        * @param executionConfiguration the object which is initialized
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time when the update was initiated
        */
        LIBAPI virtual void hlaExecutionConfigurationInitialized(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        /**
        * This method is called when a HlaExecutionConfigurationManagerListener instance comes within interest.
        * A discovered instance is initially within interest, so this will not
        * be called at the time of discovery.
        *
        * @param executionConfiguration the object which has come into interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaExecutionConfigurationInInterest(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaExecutionConfigurationManagerListener instance goes out of interest.
        *
        * @param executionConfiguration the object which has gone out of interest
        * @param timeStamp the time when the update was initiated
        */
        LIBAPI virtual void hlaExecutionConfigurationOutOfInterest(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp) = 0;

        /**
        * This method is called when a HlaExecutionConfiguration instance is deleted.
        *
        * @param executionConfiguration the object to be deleted
        * @param timeStamp the time when the update was initiated
        * @param logicalTime the logical time for the delete
        */
        LIBAPI virtual void hlaExecutionConfigurationDeleted(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) = 0;

        class Adapter;
        class InstanceListener;
        class InstanceValueListener;
        class InstanceOwnershipListener;
    };

    /**
    * An adapter class that implements the HlaExecutionConfigurationManagerListener interface with empty methods.
    * It might be used as a base class for a listener.
    */
    class HlaExecutionConfigurationManagerListener::Adapter : public HlaExecutionConfigurationManagerListener {

    public:
        LIBAPI virtual void hlaExecutionConfigurationDiscovered(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaExecutionConfigurationInitialized(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}
        LIBAPI virtual void hlaExecutionConfigurationInInterest(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaExecutionConfigurationOutOfInterest(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp) {}
        LIBAPI virtual void hlaExecutionConfigurationDeleted(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {}

    };
}
#endif
