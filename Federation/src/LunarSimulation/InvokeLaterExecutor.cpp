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

#include "InvokeLaterExecutor.h"

#include "HlaWorldImpl.h"
#include "StringUtil.h"

using namespace LunarSimulation;

InvokeLaterExecutor::InvokeLaterExecutor(HlaWorldImpl* hlaWorld) :
    _hlaWorld(hlaWorld),
    _invokeLaterThread(std::shared_ptr<std::thread>(new std::thread(&InvokeLaterExecutor::executeForever, this))) {
}

InvokeLaterExecutor::~InvokeLaterExecutor() {
    _executorQueue.postStop();
    _invokeLaterThread->join();
}

void InvokeLaterExecutor::executeForever() {
    while (true) {
        try {
            if (!_executorQueue.evoke()) {
                break;
            }
        } catch (std::exception &e) {
            HlaExceptionPtr ex(new HlaInternalException(L"Exception in InvokeLaterExecutor::executeForever: " + StringUtil::convert(e.what())));
            _hlaWorld->postException(ex);
        } catch (...) {
            HlaExceptionPtr ex(new HlaInternalException(L"Unknown exception in InvokeLaterExecutor::executeForever"));
            _hlaWorld->postException(ex);
        }
    }
}

void InvokeLaterExecutor::execute(std::function<void()> runner) {
    _executorQueue.postNotification(runner);
}
