/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_BLOCKINGQUEUE_H
#define DEVELOPER_STUDIO_BLOCKINGQUEUE_H

#include <queue>

#include <mutex>

#include <LunarSimulation/HlaLibSettings.h>
#include "ConditionVariable.h"
#include "TimeUtility.h"

namespace LunarSimulation {

    template <class T> class BlockingQueue : private LunarSimulation::noncopyable {
    private:
        std::queue<T> _queue;
        int _capacity;  // 0 == no limit
        mutable std::mutex _mutex;
        ConditionVariable _pushCondition;
        ConditionVariable _popCondition;

    public:
        BlockingQueue() : _capacity(0) {
        }

        void limitCapacity(int capacity) {
           _capacity = capacity;
        }

        void push(T data) {
           std::unique_lock<std::mutex> lock(_mutex);
           if (_capacity > 0) {
              while (_queue.size() >= (size_t)_capacity) {
                 _popCondition.wait(lock);
              }
           }
           _queue.push(data);
           _pushCondition.notify_one();
        }

        bool empty() const {
           std::unique_lock<std::mutex> lock(_mutex);
           return _queue.empty();
        }

        void pop(T& popped_value) {
           std::unique_lock<std::mutex> lock(_mutex);
           while (_queue.empty()) {
              _pushCondition.wait(lock);
           }
           popped_value = _queue.front();
           _queue.pop();
           _popCondition.notify_one();
        }

        /*
         * The timer starts after the lock has been acquired, this ensures that the thread will be working
         * on the queue for exactly millis amount of milliseconds. The total amount of time spent will in most
         * cases be slightly larger than millis because it takes a certain time for the lock to be acquired.
         */
        bool pop(T& popped_value, unsigned long long millis) {
           std::unique_lock<std::mutex> lock(_mutex);

           TimeUtility::time_point sleepUntil = TimeUtility::addMillisToCurrentTime(millis);
           while (_queue.empty()) {
              if (_pushCondition.wait_until(lock, sleepUntil)) {
                 return false;
              }
           }

           popped_value = _queue.front();
           _queue.pop();
           _popCondition.notify_one();
           return true;
        }

        int size() {
           std::unique_lock<std::mutex> lock(_mutex);
           return static_cast<int>(_queue.size());
        }
    };
}
#endif
