/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_NOTIFICATIONQUEUE_H
#define DEVELOPER_STUDIO_NOTIFICATIONQUEUE_H

#include "BlockingQueue.h"

#include <vector>

#include <mutex>
#include <functional>

#include <LunarSimulation/HlaLibSettings.h>
#include "ConditionVariable.h"

namespace LunarSimulation {

    class NotificationQueue : private LunarSimulation::noncopyable {
    public:
        NotificationQueue();
        ~NotificationQueue();
        void limitCapacity(int capacity);
        void postStop();
        void postGrantReceived();
        void postGrantDone();
        void disableNotifications();
        void enableNotifications();
        bool isNotificationsEnabled();

        /**
        * Waits for notifications to be enabled (if they are disabled).
        *
        * @return false if Stop is posted else true.
        */
        bool waitForEnable();

        /**
        * Waits for the GrantReceived sentinel.
        */
        void waitForGrantReceived();

        /**
        * Check if the GrantReceived sentinel has been evoked.
        */
        bool hasEvokedGrantReceived();

        /**
        * Waits for the GrantDone sentinel.
        */
        void waitForGrantDone();

        /**
        * Check if the GrantDone sentinel has been evoked.
        */
        bool hasEvokedGrantDone();

        /**
        * Evokes a notification on the queue if there are any. If not, block.
        *
        * @return false if Stop is posted else true.
        */
        bool evoke();

        /**
        * Evokes a notification on the queue if there are any. If not, block, but at most <code>millis</code> milli seconds.
        * Since it takes a certain amount of time to acquire the lock on the queue this operation always takes at least
        * <code>millis</code> milliseconds depending on the amount of threads working with the queue at the "same" time.
        *
        * @param millis Maximum time to block.
        *
        * @return false if Stop is posted else true.
        */
        bool evoke(unsigned long long millis);


        /**
        * Evokes for at most <code>millis</code> milliseconds.
        * If all pending notifications are processed before <code>millis</code> milliseconds have elapsed,
        * the function returns. 
        *
        * Note that this method could return even when there are pending notifications left.
        *
        * @param millis The maximum time, in ms, to process notifications.
        */
        void evokeAllNoBlock(unsigned long long millis);

        int peek();
        void postNotification(std::function<void()> notification);
        void postNotifications(std::vector<std::function<void()> > notifications);

    private:
        class Notification
        {
        public:
           enum Type { STOP, PAUSE, GRANT_RECEIVED, GRANT_DONE, FUNCTION };
           Type type;
           std::function<void()> function;

           explicit Notification()
              : type(FUNCTION)
           {
           }

           explicit Notification(Type type)
              : type(type)
           {
           }

           explicit Notification(const std::function<void()>& function)
              : type(FUNCTION), function(function)
           {
           }
        };

        mutable std::mutex _mutex;
        ConditionVariable _enabledNotifier;
        ConditionVariable _grantReceivedNotifier;
        ConditionVariable _grantDoneNotifier;
        volatile bool _notificationEnabled;
        volatile bool _grantReceived;
        volatile bool _grantDone;
        volatile bool _stopped;
        BlockingQueue<Notification> _queue;
        bool evoke(const Notification& runner);
        void post(Notification notification);
    };
}
#endif
