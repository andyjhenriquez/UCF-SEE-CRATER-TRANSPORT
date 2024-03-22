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

#include "HlaSaveRestoreManagerImpl.h"


#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"
#include "HlaWorldImpl.h"

using namespace std;
using namespace LunarSimulation;


HlaSaveRestoreManagerImpl::HlaSaveRestoreManagerImpl(SaveRestManager* saveRestManager, ObjectManager* objectManager, HlaWorldImpl* hlaWorld)
    : _saveRestManager(saveRestManager), _objectManager(objectManager), _hlaWorld(hlaWorld),
      _defaultSaveRestoreListener(new DefaultSaveRestoreListener()),
      _saveInProgress(false), _restoreInProgress(false), _wasGrantedWhenRestored(false), _localRestoreSuccessful(false) {
    _saveRestManager->setSaveRestoreManager(this);
}

void HlaSaveRestoreManagerImpl::requestFederationSave(const wstring& label)
THROW_SPEC (HlaNotConnectedException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        _saveRestManager->requestFederationSave(label, HlaLogicalTimePtr());
    } catch (HlaInvalidLogicalTimeException&) {
        //can not happen with null logical time
    }
}

void HlaSaveRestoreManagerImpl::requestFederationSave(const wstring& label, HlaLogicalTimePtr saveTime)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInvalidLogicalTimeException,
            HlaSaveInProgressException, HlaRestoreInProgressException) {
    _saveRestManager->requestFederationSave(label, saveTime);
}

bool HlaSaveRestoreManagerImpl::requestFederationRestore(const wstring &label)
THROW_SPEC (HlaNotConnectedException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException) {
    return _saveRestManager->requestFederationRestore(label);
}

bool HlaSaveRestoreManagerImpl::awaitGrantedStateAfterRestore(unsigned long long timeoutMillis) {
    return _hlaWorld->awaitGranted(timeoutMillis);
}

void HlaSaveRestoreManagerImpl::setHlaSaveRestoreListener(HlaSaveRestoreListenerPtr listener) {
    std::lock_guard<std::mutex> mutex(_listenerLock);
    _saveRestoreListener = listener;
}

bool HlaSaveRestoreManagerImpl::isSaveInProgress() {
    return _saveInProgress;
}

bool HlaSaveRestoreManagerImpl::isRestoreInProgress() {
    return _restoreInProgress;
}

HlaSaveRestoreListenerPtr HlaSaveRestoreManagerImpl::getHlaSaveRestoreListener() {
    std::lock_guard<std::mutex> mutex(_listenerLock);
    if (_saveRestoreListener) {
        return _saveRestoreListener;
    } else {
        return _defaultSaveRestoreListener;
    }
}

/*
 * Save callbacks
 */

// invoked on user notification thread
void HlaSaveRestoreManagerImpl::performFederateSave(HlaSaveRestoreListenerPtr listener, const wstring& label, HlaLogicalTimePtr logicalTime) {
    bool success = listener->performFederateSave(label, logicalTime);
    std::function<void()> callback = std::bind(&HlaSaveRestoreManagerImpl::performSave, this, success, label, logicalTime);
   _hlaWorld->invokeLater(callback);
}

// invoked on invoke later thread
void HlaSaveRestoreManagerImpl::performSave(bool federateSaved, const wstring& label, HlaLogicalTimePtr logicalTime) {
    try {
        _saveRestManager->federateSaveBegun();

        if (!federateSaved) {
           _saveRestManager->federateSaveNotComplete();
           return;
        }

        try {
            _hlaWorld->save(label, logicalTime);
            _objectManager->save();

            _saveRestManager->federateSaveComplete();
        } catch (HlaSaveFederateException& e) {
            HlaExceptionPtr ex(new HlaSaveFederateException(L"Failed to save: " + e.what_w()));
            _hlaWorld->postException(ex);
            _saveRestManager->federateSaveNotComplete();
        }
    } catch (HlaRestoreInProgressException& e) {
        HlaExceptionPtr ex(new HlaRtiException(L"Failed to perform save: " + e.what_w()));
        _hlaWorld->postException(ex);
    } catch (HlaRtiException& e) {
        HlaExceptionPtr ex(new HlaRtiException(L"Failed to perform save: " + e.what_w()));
        _hlaWorld->postException(ex);
    } catch (HlaNotConnectedException& e) {
        HlaExceptionPtr ex(new HlaRtiException(L"Failed to perform save: " + e.what_w()));
        _hlaWorld->postException(ex);
    }
}

void HlaSaveRestoreManagerImpl::initiateFederateSave(const wstring& label, HlaLogicalTimePtr logicalTime) {
    _saveInProgress = true;
    firePerformFederateSave(label, logicalTime);
}

void HlaSaveRestoreManagerImpl::federationSaved() {
    _saveInProgress = false;
    fireFederationSaved();
}

void HlaSaveRestoreManagerImpl::federationNotSaved(HlaSaveRestoreListener::HlaSaveFailure reason) {
    _saveInProgress = false;
    fireFederationNotSaved(reason);
}

/*
 * Restore callbacks
 */

// invoked on user notification thread
void HlaSaveRestoreManagerImpl::performFederateRestore(HlaSaveRestoreListenerPtr listener, const wstring& label, HlaFederateIdPtr federateHandle, const wstring& federateName) {
    bool success = listener->performFederateRestore(label);
    std::function<void()> callback = std::bind(&HlaSaveRestoreManagerImpl::performRestore, this, success, label, federateHandle, federateName);
   _hlaWorld->invokeLater(callback);
}

// invoked on invoke later thread
void HlaSaveRestoreManagerImpl::performRestore(bool federateRestored, const wstring& label, HlaFederateIdPtr federateHandle, const wstring& federateName) {
    try {
        if (!federateRestored) {
            _saveRestManager->federateRestoreNotComplete();
            return;
        }

        try {
            pair<HlaLogicalTimePtr, bool> restoreInfo = _hlaWorld->restore(label, federateHandle, federateName);
            _restoredTime = restoreInfo.first;
            _wasGrantedWhenRestored = restoreInfo.second;
            _objectManager->restore();

            _localRestoreSuccessful = true;
            _saveRestManager->federateRestoreComplete();
        } catch (HlaRestoreFederateException& e) {
            HlaExceptionPtr ex(new HlaRestoreFederateException(L"Failed to restore: " + e.what_w()));
            _hlaWorld->postException(ex);
            _saveRestManager->federateRestoreNotComplete();
        }
    } catch (HlaSaveInProgressException& e) {
        HlaExceptionPtr ex(new HlaRtiException(L"Failed to perform restore: " + e.what_w()));
        _hlaWorld->postException(ex);
    } catch (HlaRtiException& e) {
        HlaExceptionPtr ex(new HlaRtiException(L"Failed to perform restore: " + e.what_w()));
        _hlaWorld->postException(ex);
    } catch (HlaNotConnectedException& e) {
        HlaExceptionPtr ex(new HlaRtiException(L"Failed to perform restore: " + e.what_w()));
        _hlaWorld->postException(ex);
    }
}

void HlaSaveRestoreManagerImpl::federationRestoreBegun() {
    _restoreInProgress = true;
    _localRestoreSuccessful = false;
    // wait for initiateFederateRestore
}

void HlaSaveRestoreManagerImpl::initiateFederateRestore(const wstring& label, HlaFederateIdPtr federateHandle, const wstring& federateName) {
    firePerformFederateRestore(label, federateHandle, federateName);
}

bool HlaSaveRestoreManagerImpl::federationRestored() {
    _restoreInProgress = false;
    fireFederationRestored(_restoredTime, !_wasGrantedWhenRestored);
    return _wasGrantedWhenRestored && _restoredTime->wasReceivedInTimeStampOrder();
}

bool HlaSaveRestoreManagerImpl::federationNotRestored(HlaSaveRestoreListener::HlaRestoreFailure reason) {
    _restoreInProgress = false;
    HlaLogicalTimePtr localRestoredTime = _localRestoreSuccessful ? _restoredTime : std::dynamic_pointer_cast<HlaLogicalTime>(HlaLogicalTimeImpl::getInvalid());
    fireFederationNotRestored(reason, _localRestoreSuccessful, localRestoredTime, !_wasGrantedWhenRestored);
    return _wasGrantedWhenRestored && _localRestoreSuccessful && _restoredTime->wasReceivedInTimeStampOrder();
}

void HlaSaveRestoreManagerImpl::timeAdvanceGrantAfterRestore(HlaLogicalTimePtr logicalTime) {
    _hlaWorld->timeAdvanceGrantAfterRestore(logicalTime);
}

/*
 * Fire
 */

void HlaSaveRestoreManagerImpl::firePerformFederateSave(const std::wstring& label, HlaLogicalTimePtr saveTime) {
    std::function<void()> callback = std::bind(&HlaSaveRestoreManagerImpl::performFederateSave, this, getHlaSaveRestoreListener(), label, saveTime);
    _hlaWorld->postNotification(callback);
}

void HlaSaveRestoreManagerImpl::fireFederationSaved() {
    std::function<void()> callback = std::bind(&HlaSaveRestoreListener::federationSaved, getHlaSaveRestoreListener());
    _hlaWorld->postNotification(callback);
}

void HlaSaveRestoreManagerImpl::fireFederationNotSaved(HlaSaveRestoreListener::HlaSaveFailure saveFailureReason) {
    std::function<void()> callback = std::bind(&HlaSaveRestoreListener::federationNotSaved, getHlaSaveRestoreListener(), saveFailureReason);
    _hlaWorld->postNotification(callback);
}

void HlaSaveRestoreManagerImpl::firePerformFederateRestore(const std::wstring& label, HlaFederateIdPtr federateHandle, const wstring& federateName) {
    std::function<void()> callback = std::bind(&HlaSaveRestoreManagerImpl::performFederateRestore, this, getHlaSaveRestoreListener(), label, federateHandle, federateName);
    _hlaWorld->postNotification(callback);
}

void HlaSaveRestoreManagerImpl::fireFederationRestored(HlaLogicalTimePtr restoredTime, bool wasAdvancing) {
    std::function<void()> callback = std::bind(&HlaSaveRestoreListener::federationRestored, getHlaSaveRestoreListener(), restoredTime, wasAdvancing);
    _hlaWorld->postNotification(callback);
}

void HlaSaveRestoreManagerImpl::fireFederationNotRestored(HlaSaveRestoreListener::HlaRestoreFailure restoreFailureReason, bool localRestoreWasSuccessful, HlaLogicalTimePtr localRestoredTime, bool wasAdvancing) {
    std::function<void()> callback = std::bind(&HlaSaveRestoreListener::federationNotRestored, getHlaSaveRestoreListener(), restoreFailureReason, localRestoreWasSuccessful, localRestoredTime, wasAdvancing);
    _hlaWorld->postNotification(callback);
}
