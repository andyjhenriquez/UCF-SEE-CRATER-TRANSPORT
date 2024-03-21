/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_SCHEDULER_H
#define DEVELOPER_STUDIO_SCHEDULER_H

#include <queue>
#include <set>

#include <memory>
#include <functional>
#include <mutex>
#include <thread>

#include <LunarSimulation/HlaLibSettings.h>
#include "ConditionVariable.h"
#include "TimeUtility.h"

namespace LunarSimulation {
    class HlaWorldImpl;

    class Scheduler : private LunarSimulation::noncopyable {
        typedef std::pair<std::function<void()>, TimeUtility::time_point> Bf;

        class PrioPtimes {
        public:
            bool operator() (const Bf& p1, const Bf& p2);
        };

    public:

        /**
        * The Scheduler always waits until the queue is empty before destroying the
        * executing thread if the Scheduler is removed.
        */
        explicit Scheduler(HlaWorldImpl* hlaWorld);
        ~Scheduler();
        void addTask(std::function<void()> runner, unsigned long long delayInMillis);
    private:
        void runExecutor();
        void run();

        std::priority_queue<Bf, std::vector<Bf>, PrioPtimes> _prioQueue;
        mutable std::mutex _mutex;
        TimeUtility::time_point _timeOfNextTask;
        volatile bool _threadFinished;
        HlaWorldImpl*  _hlaWorld;
        ConditionVariable _emptyQueueCondition;
        ConditionVariable _rescheduleCondition;
        std::shared_ptr<std::thread> _executorThread;
    };
}
#endif
