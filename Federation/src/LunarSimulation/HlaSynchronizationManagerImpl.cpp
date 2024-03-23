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

#include "HlaSynchronizationManagerImpl.h"

using namespace std;
using namespace LunarSimulation;

HlaSynchronizationManagerImpl::HlaSynchronizationManagerImpl(SyncPointManager* syncPointManager, HlaWorldImpl* hlaWorldImpl)
:   _syncPointManager(syncPointManager),
    _hlaWorldImpl(hlaWorldImpl) {
    _syncPointManager->addSynchronizationPointHandler(this);
}

bool HlaSynchronizationManagerImpl::registerSynchronizationPoint(const std::wstring &synchronizationPointLabel)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    std::set<std::vector<char> > encodedFederateHandleSynchronizationSet;
    return registerSynchronizationPoint(synchronizationPointLabel, encodedFederateHandleSynchronizationSet);
}

bool HlaSynchronizationManagerImpl::registerSynchronizationPoint(const std::wstring &synchronizationPointLabel, std::set<std::vector<char> > encodedFederateHandleSynchronizationSet)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return _syncPointManager->registerFederationSynchronizationPoint(synchronizationPointLabel, encodedFederateHandleSynchronizationSet, _hlaWorldImpl->getCurrentTime());
}

bool HlaSynchronizationManagerImpl::isSynchronizationPointRegistered(const std::wstring& synchronizationPointLabel) const {
    return _syncPoints.isRegistered(synchronizationPointLabel);
}

std::set<std::wstring> HlaSynchronizationManagerImpl::getRegisteredSynchronizationPointLabels() const {
    return _syncPoints.getCurrentlyRegistered();
}

std::set<std::wstring> HlaSynchronizationManagerImpl::getPendingAchieveSynchronizationPointLabels() const {
    return _syncPoints.getPendingAchieve();
}

bool HlaSynchronizationManagerImpl::waitForSynchronizationPointRegistration(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms) {
    return !_syncPoints.waitForRegister(synchronizationPointLabel, timeout_ms);
}

bool HlaSynchronizationManagerImpl::achieveSynchronizationPoint(const std::wstring& synchronizationPointLabel)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    bool success = _syncPointManager->synchronizationPointAchieved(synchronizationPointLabel);
    if (success) {
        _syncPoints.labelAchieved(synchronizationPointLabel);
    }
    return success;
}

bool HlaSynchronizationManagerImpl::achieveSynchronizationPointAndWaitForSynchronized(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    bool ignore;
    return achieveSynchronizationPointAndWaitForSynchronized(synchronizationPointLabel, timeout_ms, ignore);
}

bool HlaSynchronizationManagerImpl::achieveSynchronizationPointAndWaitForSynchronized(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms, bool & didTimeout)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    bool success = achieveSynchronizationPoint(synchronizationPointLabel);
    if (success) {
        didTimeout = _syncPoints.waitForSynchronized(synchronizationPointLabel, timeout_ms);
    }
    return success;
}

void HlaSynchronizationManagerImpl::addHlaSynchronizationListener(HlaSynchronizationListenerPtr listener) {
    _listeners.add(listener);
}

void HlaSynchronizationManagerImpl::removeHlaSynchronizationListener(HlaSynchronizationListenerPtr listener) {
    _listeners.remove(listener);
}

/*
* SyncPointManager.Listener interface impl
*/

void HlaSynchronizationManagerImpl::announceSynchronizationPoint(std::wstring synchPointLabel, HlaTimeStampPtr hlaTimeStamp) {
    HlaSynchronizationManagerImpl::fireSynchronizationPointRegistered(synchPointLabel, hlaTimeStamp);
}

void HlaSynchronizationManagerImpl::federationSynchronized(std::wstring synchPointLabel) {
    fireSynchronizationPointSynchronized(synchPointLabel, _hlaWorldImpl->getCurrentTime());
}

void HlaSynchronizationManagerImpl::fireSynchronizationPointRegistered(const std::wstring& synchPointLabel, const HlaTimeStampPtr hlaTimeStamp) {
    _syncPoints.labelRegistered(synchPointLabel);
    std::set<HlaSynchronizationListenerPtr> listeners = _listeners.getListeners();
    for (std::set<HlaSynchronizationListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); it++) {
        std::function<void()> callback = std::bind(&HlaSynchronizationListener::synchronizationPointRegistered, *it, synchPointLabel, hlaTimeStamp);
        _hlaWorldImpl->postNotification(callback);
    }
}

void HlaSynchronizationManagerImpl::fireSynchronizationPointSynchronized(const std::wstring& synchPointLabel, const HlaTimeStampPtr hlaTimeStamp) {
    _syncPoints.labelSynchronized(synchPointLabel);
    std::set<HlaSynchronizationListenerPtr> listeners = _listeners.getListeners();
    std::set<HlaSynchronizationListenerPtr>::iterator it;
    for (it = listeners.begin(); it != listeners.end(); it++) {
        std::function<void()> callback = std::bind(&HlaSynchronizationListener::synchronizationPointSynchronized, *it, synchPointLabel, hlaTimeStamp);
        _hlaWorldImpl->postNotification(callback);
    }
}

bool HlaSynchronizationManagerImpl::SyncPoints::waitForEvent(bool isRegister, const std::wstring& label, unsigned long long timeout) {
    std::unique_lock<std::mutex> lock(_mutex);
    if (triggered(isRegister, label)) {
        return false;
    }
    TimeUtility::time_point sleepUntil = TimeUtility::addMillisToCurrentTime(timeout);
    while (!triggered(isRegister, label)) { //A while loop is used because of spurious wake ups.
        if (_condition.wait_until(lock, sleepUntil)) {
            return !triggered(isRegister, label);
        }
    }
    return false;
}

void HlaSynchronizationManagerImpl::SyncPoints::labelRegistered(const std::wstring& label) {
    std::unique_lock<std::mutex> lock(_mutex);
    _labels.insert(label);
    _labelsPendingAchieve.insert(label);
    _condition.notify_all();
}

void HlaSynchronizationManagerImpl::SyncPoints::labelAchieved(const std::wstring& label) {
    std::unique_lock<std::mutex> lock(_mutex);
    _labelsPendingAchieve.erase(label);
}

void HlaSynchronizationManagerImpl::SyncPoints::labelSynchronized(const std::wstring& label) {
    std::unique_lock<std::mutex> lock(_mutex);
    _labels.erase(label);
    _labelsPendingAchieve.erase(label);
    _condition.notify_all();
}

bool HlaSynchronizationManagerImpl::SyncPoints::isRegistered(const std::wstring& label) const {
    std::unique_lock<std::mutex> lock(_mutex);
    return (_labels.count(label) == 1);
}

bool HlaSynchronizationManagerImpl::SyncPoints::isRegisteredUnlocked(const std::wstring& label) const {
    return (_labels.count(label) == 1);
}

std::set<std::wstring> HlaSynchronizationManagerImpl::SyncPoints::getCurrentlyRegistered() const {
    std::unique_lock<std::mutex> lock(_mutex);
    return _labels;
}

std::set<std::wstring> HlaSynchronizationManagerImpl::SyncPoints::getPendingAchieve() const {
    std::unique_lock<std::mutex> lock(_mutex);
    return _labelsPendingAchieve;
}

bool HlaSynchronizationManagerImpl::SyncPoints::waitForRegister(const std::wstring& label, unsigned long long timeout) {
    return waitForEvent(true, label, timeout);
}

bool HlaSynchronizationManagerImpl::SyncPoints::waitForSynchronized(const std::wstring& label, unsigned long long timeout) {
    return waitForEvent(false, label, timeout);
}

bool HlaSynchronizationManagerImpl::SyncPoints::triggered(bool isRegister, const std::wstring& label) {
    return isRegister == isRegisteredUnlocked(label);
}
