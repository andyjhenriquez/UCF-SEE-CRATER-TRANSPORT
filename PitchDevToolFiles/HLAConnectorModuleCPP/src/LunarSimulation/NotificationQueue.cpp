/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include "NotificationQueue.h"

using namespace LunarSimulation;

NotificationQueue::NotificationQueue() :
    _notificationEnabled(true),
    _grantReceived(false),
    _grantDone(true), //start with grant done
    _stopped(false)
{}

NotificationQueue::~NotificationQueue() {}

void NotificationQueue::limitCapacity(int capacity) {
    _queue.limitCapacity(capacity);
}

void NotificationQueue::postStop() {
    post(Notification(Notification::STOP));
    std::unique_lock<std::mutex> lock(_mutex);
    if (!_notificationEnabled) {
        _stopped = true;
        _enabledNotifier.notify_all();
    }
}

void NotificationQueue::postGrantReceived() {
     post(Notification(Notification::GRANT_RECEIVED));
}

void NotificationQueue::postGrantDone() {
     post(Notification(Notification::GRANT_DONE));
}

void NotificationQueue::disableNotifications() {
    std::unique_lock<std::mutex> lock(_mutex);
    if (_notificationEnabled) {
        _notificationEnabled = false;
        post(Notification(Notification::PAUSE));
    }
}

void NotificationQueue::enableNotifications() {
    std::unique_lock<std::mutex> lock(_mutex);
    if (!_notificationEnabled) {
        _notificationEnabled = true;
        post(Notification(Notification::PAUSE));
        _enabledNotifier.notify_all();
    }
}

bool NotificationQueue::isNotificationsEnabled() {
    return _notificationEnabled;
}

bool NotificationQueue::waitForEnable() {
    std::unique_lock<std::mutex> lock(_mutex);
    if (!_notificationEnabled) {
        _enabledNotifier.wait(lock);
        if (_stopped) return false;
    }
    return true;
}

void NotificationQueue::waitForGrantReceived() {
    std::unique_lock<std::mutex> lock(_mutex);
    if (!_grantReceived) {
        _grantReceivedNotifier.wait(lock);
    }
    _grantReceived = false;
}

bool NotificationQueue::hasEvokedGrantReceived() {
    std::unique_lock<std::mutex> lock(_mutex);
    return _grantReceived;
}

void NotificationQueue::waitForGrantDone() {
    std::unique_lock<std::mutex> lock(_mutex);
    if (!_grantDone) {
        _grantDoneNotifier.wait(lock);
    }
    _grantDone = false;
}

bool NotificationQueue::hasEvokedGrantDone() {
    std::unique_lock<std::mutex> lock(_mutex);
    return _grantDone;
}

bool NotificationQueue::evoke() {
    if (!_notificationEnabled) return true;
    Notification r;
    _queue.pop(r);
    return evoke(r);
}

bool NotificationQueue::evoke(unsigned long long millis) {
    if (!_notificationEnabled) return true;
    Notification r;
    if (_queue.pop(r, millis)) {
        return evoke(r);
    } else {
        return false;
    }
}

bool NotificationQueue::evoke(const Notification& runner) {
   switch (runner.type)
   {
   case Notification::STOP: {
      return false;
   }
   case Notification::GRANT_RECEIVED: {
      std::unique_lock<std::mutex> lock(_mutex);
      if (!_grantReceived) {
         _grantReceived = true;
         _grantReceivedNotifier.notify_all();
      }
      break;
   }
   case Notification::GRANT_DONE: {
      std::unique_lock<std::mutex> lock(_mutex);
      if (!_grantDone) {
         _grantDone = true;
         _grantDoneNotifier.notify_all();
      }
      break;
   }
   case Notification::PAUSE: {
      // Do nothing
      break;
   }
   default:
      {
      runner.function();
      }
   }
    return true;
}

void NotificationQueue::evokeAllNoBlock(unsigned long long millis) {
    TimeUtility::time_point stopTime = TimeUtility::addMillisToCurrentTime(millis);
    std::unique_lock<std::mutex> lock(_mutex);
    TimeUtility::time_point currentTime = TimeUtility::getCurrentTime();

    while (!_queue.empty() && (currentTime < stopTime)) {
        Notification r;
        _queue.pop(r);
        evoke(r);
        currentTime = TimeUtility::getCurrentTime();
    }
}

int NotificationQueue::peek() {
    return _queue.size();
}

void NotificationQueue::postNotification(std::function<void()> function) {
    _queue.push(Notification(function));
}

void NotificationQueue::post(Notification notification) {
    _queue.push(notification);
}

void NotificationQueue::postNotifications(std::vector<std::function<void()> > notifications) {
    for (std::vector<std::function<void()> >::iterator i = notifications.begin(); i != notifications.end(); ++i) {
        postNotification(*i);
    }
}
