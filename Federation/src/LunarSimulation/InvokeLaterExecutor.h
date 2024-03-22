/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_INVOKELATEREXECUTOR_H
#define DEVELOPER_STUDIO_INVOKELATEREXECUTOR_H

#include <functional>
#include <thread>
#include <memory>

#include <LunarSimulation/HlaLibSettings.h>
#include "NotificationQueue.h"

namespace LunarSimulation {
    class HlaWorldImpl;

    class InvokeLaterExecutor : private LunarSimulation::noncopyable {
    public:
        explicit InvokeLaterExecutor(HlaWorldImpl* hlaWorld);
        ~InvokeLaterExecutor();

        void executeForever();
        void execute(std::function<void()> runner);

    private:
        HlaWorldImpl*  _hlaWorld;
        NotificationQueue _executorQueue;
        std::shared_ptr<std::thread> _invokeLaterThread;
    };
}
#endif
