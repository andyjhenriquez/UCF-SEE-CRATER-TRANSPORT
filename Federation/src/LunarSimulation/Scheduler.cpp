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

#ifdef _WIN32
#pragma warning( disable : 4355)
#endif

#include "Scheduler.h"
#include "HlaWorldImpl.h"
#include "StringUtil.h"

using namespace LunarSimulation;

Scheduler::Scheduler(HlaWorldImpl*  hlaWorld) : _threadFinished(false),
_hlaWorld(hlaWorld),
_executorThread(std::shared_ptr<std::thread>(new std::thread(&Scheduler::run, this)))
{}

Scheduler::~Scheduler() {
    _threadFinished = true;
    _emptyQueueCondition.notify_one();
    _rescheduleCondition.notify_one();
    _executorThread->join();
}

bool Scheduler::PrioPtimes::operator ()(const Scheduler::Bf &p1, const Scheduler::Bf &p2) {
    return (p1.second > p2.second);
}

void Scheduler::run() {
    while (true) {
        try {
            if (_threadFinished && _prioQueue.empty()) {
                return;
            }

            {
                std::unique_lock<std::mutex> lock(_mutex);
                while (_prioQueue.empty()) {
                    _emptyQueueCondition.wait(lock);
                    if (_threadFinished) {
                        return;
                    }
                }
            }
            runExecutor();
        } catch (std::exception &e) {
            HlaExceptionPtr ex(new HlaInternalException(L"Exception in Scheduler::run: " + StringUtil::convert(e.what())));
            _hlaWorld->postException(ex);
        } catch (...) {
            HlaExceptionPtr ex(new HlaInternalException(L"Unknown exception in Scheduler::run"));
            _hlaWorld->postException(ex);
        }
    }
}

void Scheduler::runExecutor() {
    {
        std::unique_lock<std::mutex> lock(_mutex);
        if (!_rescheduleCondition.wait_until(lock, _timeOfNextTask)) {
            // Time of next task not reached, so rescheduled
            return;
        }
    }

    Bf top;
    {
        std::unique_lock<std::mutex> lock(_mutex);
        if (!_prioQueue.empty()) {
            top = _prioQueue.top();
            _prioQueue.pop();

            if (!_prioQueue.empty()) {
                _timeOfNextTask = _prioQueue.top().second;
            }
        }
    }
    if (top.first) {
        top.first();
    }
}

void Scheduler::addTask(std::function<void()> runner, unsigned long long delayInMillis) {
    std::unique_lock<std::mutex> lock(_mutex);
    TimeUtility::time_point currentTaskTime = TimeUtility::addMillisToCurrentTime(delayInMillis);
    if (_prioQueue.empty()) {
        _timeOfNextTask = currentTaskTime;
    }
    _prioQueue.push(Bf(runner, currentTaskTime));
    _emptyQueueCondition.notify_one();
    if (currentTaskTime < _timeOfNextTask) {
        _timeOfNextTask = currentTaskTime;
        _rescheduleCondition.notify_one();
    }
}
