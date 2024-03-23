/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include "SyncPointManager.h"

#include "FederateManager.h"

using namespace LunarSimulation;

SyncPointManager::SyncPointManager(FederateManager* federate) : _federate(federate), _connected(false) {
    _federate->setSynchronizationPointManager(this);
}

void SyncPointManager::addSynchronizationPointHandler(Listener* listener) {
    _listeners.add(listener);
}

bool SyncPointManager::registerFederationSynchronizationPoint(std::wstring synchPointLabel, std::set<std::vector<char> > encodedFederateHandles, HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (!_connected) {
        throw HlaNotConnectedException("Not connected");
    }
    std::unique_lock<std::mutex> lock(_registerInProgressLock);
    return _federate->registerFederationSynchronizationPoint(synchPointLabel, encodedFederateHandles, timeStamp);
}

bool SyncPointManager::synchronizationPointAchieved(std::wstring synchPointLabel)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (!_connected) {
        throw HlaNotConnectedException("Not connected");
    }
    return _federate->synchronizationPointAchieved(synchPointLabel);
}

//Callbacks
void SyncPointManager::announceSynchronizationPoint(std::wstring synchPointLabel, HlaTimeStampPtr hlaTimeStamp) {
    std::set<Listener*> listeners = _listeners.getListeners();
    for (std::set<Listener*>::iterator it = listeners.begin(); it != listeners.end(); it++) {
        SyncPointManager::Listener* l = *it;
        l->announceSynchronizationPoint(synchPointLabel, hlaTimeStamp);
    }
}

void SyncPointManager::federationSynchronized(std::wstring synchPointLabel) {
    std::set<Listener*> listeners = _listeners.getListeners();
    for (std::set<Listener*>::iterator it = listeners.begin(); it != listeners.end(); it++) {
        SyncPointManager::Listener* l = *it;
        l->federationSynchronized(synchPointLabel);
    }
}

void SyncPointManager::connected() {
    _connected = true;
}

void SyncPointManager::disconnect() {
    _connected = false;
}
