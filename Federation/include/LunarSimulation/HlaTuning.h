/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLATUNING_H
#define DEVELOPER_STUDIO_HLATUNING_H

#include <algorithm>

#include <LunarSimulation/HlaSettings.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
    /**
    * Class used to support Tuning of the generated code.
    *
    * It is possible to override the tuning values with the same file used by HlaSettings;
    * a <code>FederateConfig.txt</code> file in the current directory,
    */
    class HlaTuning : private LunarSimulation::noncopyable {
    private:
        HlaSettingsPtr _settings;
    public:

        /** Create a HlaTuning object */
        LIBAPI HlaTuning(HlaSettingsPtr settings);

        /**
        * Perform an request of attribute value update when a new instance is discovered or comes within interest.
        * Instances are requested after a delay [REQUEST_MIN_DELAY_MS, REQUEST_MAX_DELAY_MS].
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>request</code>.
        *
        * @see #PROVIDE
        * @see #REQUEST_MIN_DELAY_MS
        * @see #REQUEST_MAX_DELAY_MS
        */
        const bool REQUEST;

        /**
        * Max delay for request of attribute value update for discovered instances, in milliseconds.
        * A random value between <i>min</i> and <i>max</i> is used.
        *
        * Valid range is <code>[0 <= <i>min</i> <= <i>max</i> <= 3 600 000]</code> (<code>[0 ms ... 1 hr]</code>).
        * The default value is <code>20</code> ms.
        * The <code>FederateConfig.txt</code> key is <code>requestMinDelayMs</code>.
        *
        * @see #REQUEST
        * @see #REQUEST_MIN_DELAY_MS
        */
        const unsigned int REQUEST_MIN_DELAY_MS;

        /**
        * Max delay for request of attribute value update for discovered instances, in milliseconds.
        * A random value between <i>min</i> and <i>max</i> is used.
        *
        * Valid range is <code>[0 <= <i>min</i> <= <i>max</i> <= 3 600 000]</code> (<code>[0 ms ... 1 hr]</code>).
        * The default value is <code>50</code> ms.
        * The <code>FederateConfig.txt</code> key is <code>requestMaxDelayMs</code>.
        *
        * @see #REQUEST
        * @see #REQUEST_MIN_DELAY_MS
        */
        const unsigned int REQUEST_MAX_DELAY_MS;

        /**
        * Perform an attribute update when a provide is requested.
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>provide</code>.
        *
        * @see #REQUEST
        */
        const bool PROVIDE;

       /**
        * Turn on the Convey Producing Federate option in the Switches table when using HLA Evolved
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>conveyProducingFederate</code>.
        */
        const bool CONVEY_PRODUCING_FEDERATE;  

        /**
        * Perform automatic achieve on all announced synchronization points.
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>autoAchieve</code>.
        */
        const bool AUTO_ACHIEVE;

        /**
        * Include a dump of the data in <code>HlaDecodeException</code>.
        *
        * The default value is <code>false</code>.
        * The <code>FederateConfig.txt</code> key is <code>includeDataInDecodeException</code>.
        */
        const bool INCLUDE_DATA_IN_DECODE_EXCEPTION;

        /**
        * Verify the length of all received data, throws a <code>HlaDecodeException</code> if the lengths do not match.
        *
        * The default value is <code>false</code>.
        * The <code>FederateConfig.txt</code> key is <code>verifyReceivedDataLength</code>.
        */
        const bool VERIFY_RECEIVED_DATA_LENGTH;

        /**
        * The resign action.
        * <p>
        * Valid values are:
        * <ul>
        *  <li> 0: UNCONDITIONALLY_DIVEST_ATTRIBUTES - divests all owned attributes </li>
        *  <li> 1: DELETE_OBJECTS - deletes all object instances that the federate owns </li>
        *  <li> 2: CANCEL_PENDING_OWNERSHIP_ACQUISITIONS - cancels all pending ownership acquisitions </li>
        *  <li> 3: DELETE_OBJECTS_THEN_DIVEST - combines 1 and 0 </li>
        *  <li> 4: CANCEL_THEN_DELETE_THEN_DIVEST - combines 2, 1, and 0 </li>
        *  <li> 5: NO_ACTION - no handling of owned attributes or pending acquisitions </li>
        * </ul>
        *
        * The default value is <code>4</code>, CANCEL_THEN_DELETE_THEN_DIVEST.
        * The <code>FederateConfig.txt</code> key is <code>resignAction</code>.
        */
        const int RESIGN_ACTION;

        /**
        * Create the federation with the selected time representation for logical time,
        * even if HLA Time Management is not enabled.
        *
        * The default value is <code>false</code>.
        * The <code>FederateConfig.txt</code> key is <code>createFederationWithTimeRepresentation</code>.
        */
        const bool CREATE_FEDERATION_WITH_TIME_REPRESENTATION;

        /**
        * Always send and receive updates and interactions with a <code>LogicalTime</code>,
        * even if HLA Time Management is not enabled.
        *
        * The default value is <code>false</code>.
        * The <code>FederateConfig.txt</code> key is <code>alwaysUseLogicalTime</code>.
        */
        const bool ALWAYS_USE_LOGICAL_TIME;

        /**
        * Do an initial time advance to <code>GALT</code> when only time constrained.
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>initialAdvanceWhenConstrained</code>.
        */
        const bool INITIAL_ADVANCE_WHEN_CONSTRAINED;

        /**
        * Do an initial time advance to a <code>LogicalTime</code> that is even divisible by the initial step size.
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>initialAdvanceToEvenStepSize</code>.
        */
        const bool INITIAL_ADVANCE_TO_EVEN_STEP_SIZE;

        /**
        * Always advance time to the expected frame times when using <code>advanceToNextEvent()</code>.
        * <p>
        * Example (step size is 5 and an event is received at logical time 12):
        * <ul>
        *    <li>Granted logical times when value set to <code>true</code>: 5, 10, 12, 15, 20</li>
        *    <li>Granted logical times when value set to <code>false</code>: 5, 10, 12, 17, 22</li>
        * </ul>
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>forceFrameTimesWhenEventBased</code>.
        */
        const bool FORCE_FRAME_TIMES_WHEN_EVENT_BASED;

        /**
        * Deliver receive order messages in both time advancing state and time granted state.
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>enableAsynchronousDelivery</code>.
        */
        const bool ENABLE_ASYNCHRONOUS_DELIVERY;

        /**
        * The capacity of the Notification Queue.
        *
        * Valid range is <code>[0 <= <i>value</i> <= 2^31 - 1]</code>.
        * Use 0 for unlimited capacity.
        * The default value is <code>200 000</code> entries.
        * The <code>FederateConfig.txt</code> key is <code>notificationQueueCapacity</code>.
        */
        const unsigned int NOTIFICATION_QUEUE_CAPACITY;

        /**
        * The time advance methods will wait for all notifications received in the advancing state to
        * be precessed before returning from the advance method.
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>advanceWaitsForNotifications</code>.
        */
        const bool ADVANCE_WAITS_FOR_NOTIFICATIONS;

        /**
        * If configured to use HLA Time Management, it will be enabled on connect.
        * If flag is false, <code>enableTimeManagement()</code> must be called to enable HLA Time Management.
        *
        * This flag has no effect if federate is not configured to use HLA Time Management.
        *
        * The default value is <code>true</code>.
        * The <code>FederateConfig.txt</code> key is <code>enableTimeManagementOnConnect</code>.
        */
        const bool ENABLE_TIME_MANAGEMENT_ON_CONNECT;

    private:
        //Get the value from Settings file
        bool getSetting(std::string key, bool defaultValue);

        //Get the value from the settings file
        int getSetting(std::string key, int defaultValue);

        unsigned int inRange(unsigned int min, unsigned int value, unsigned int max) {
            return std::max(min, std::min(value, max));
        }
    };
}

#endif
