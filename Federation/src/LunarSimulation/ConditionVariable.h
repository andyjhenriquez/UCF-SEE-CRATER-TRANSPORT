/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_CONDITIONVARIABLE_H
#define DEVELOPER_STUDIO_CONDITIONVARIABLE_H

#include <mutex>
#include <condition_variable>
#include <chrono>

#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
    class ConditionVariable : private LunarSimulation::noncopyable {
    private:
        std::condition_variable _condition;

    public:
        ConditionVariable() : _condition() {
        }

        void notify_one() {
            _condition.notify_one();
        }

        void notify_all() {
            _condition.notify_all();
        }

        void wait(std::unique_lock<std::mutex>& lock) {
            _condition.wait(lock);
        }

        // returns true on timeout
        template<class Clock, class Duration>
        bool wait_until(std::unique_lock<std::mutex>& lock, const std::chrono::time_point<Clock, Duration> & absoluteTime) {
            return _condition.wait_until(lock, absoluteTime) == std::cv_status::timeout;
        }

        // returns true on timeout
        bool wait_for(std::unique_lock<std::mutex>& lock, const std::chrono::system_clock::duration & duration) {
            return _condition.wait_for(lock, duration) == std::cv_status::timeout;
        }
    };
}
#endif
