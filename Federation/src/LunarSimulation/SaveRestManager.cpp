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

#include "SaveRestManager.h"

using namespace std;
using namespace LunarSimulation;


SaveRestManager::SaveRestManager(FederateManager* federate) : _federate(federate), _connected(false) {
   _federate->setSaveRestManager(this);
}

void SaveRestManager::setSaveRestoreManager(Listener* saveRestoreManager) {
   _listener = saveRestoreManager;
}

void SaveRestManager::connected() {
   _connected = true;
}

void SaveRestManager::disconnect() {
   _connected = false;
}

void SaveRestManager::requestFederationSave(const std::wstring &label, HlaLogicalTimePtr logicalTime)
THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaInvalidLogicalTimeException,
           HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (!_connected) {
       throw HlaNotConnectedException("Not connected");
    }
    _federate->requestFederationSave(label, logicalTime);
}

void SaveRestManager::federateSaveBegun()
THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaRestoreInProgressException) {
    if (!_connected) {
       throw HlaNotConnectedException("Not connected");
    }
    _federate->federateSaveBegun();

}

void SaveRestManager::federateSaveComplete()
THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaRestoreInProgressException) {
    if (!_connected) {
       throw HlaNotConnectedException("Not connected");
    }
    _federate->federateSaveComplete();
}

void SaveRestManager::federateSaveNotComplete()
THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaRestoreInProgressException) {
    if (!_connected) {
       throw HlaNotConnectedException("Not connected");
    }
    _federate->federateSaveNotComplete();
}

bool SaveRestManager::requestFederationRestore(const std::wstring &label)
THROW_SPEC( HlaNotConnectedException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (!_connected) {
       throw HlaNotConnectedException("Not connected");
    }
    return _federate->requestFederationRestore(label);
}

void SaveRestManager::federateRestoreComplete()
THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException) {
    if (!_connected) {
       throw HlaNotConnectedException("Not connected");
    }
    _federate->federateRestoreComplete();
}

void SaveRestManager::federateRestoreNotComplete()
THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException) {
    if (!_connected) {
       throw HlaNotConnectedException("Not connected");
    }
    _federate->federateRestoreNotComplete();
}


// Save Callbacks

void SaveRestManager::initiateFederateSave(const std::wstring &name, HlaLogicalTimePtr logicalTime) {
    _listener->initiateFederateSave(name, logicalTime);
}

void SaveRestManager::federationSaved() {
    _listener->federationSaved();
}

void SaveRestManager::federationNotSaved(RtiDriver::SaveFailureReason reason) {
    _listener->federationNotSaved(convert(reason));
}

// Restore Callbacks

void SaveRestManager::federationRestoreBegun() {
    _listener->federationRestoreBegun();
}

void SaveRestManager::initiateFederateRestore(const std::wstring &name, HlaFederateIdPtr federateHandle, const std::wstring &federateName) {
    _listener->initiateFederateRestore(name, federateHandle, federateName);
}

bool SaveRestManager::federationRestored() {
    return _listener->federationRestored();
}

bool SaveRestManager::federationNotRestored(RtiDriver::RestoreFailureReason reason) {
    return _listener->federationNotRestored(convert(reason));
}

void SaveRestManager::timeAdvanceGrantAfterRestore(HlaLogicalTimePtr logicalTime) {
    _listener->timeAdvanceGrantAfterRestore(logicalTime);
}

HlaSaveRestoreListener::HlaSaveFailure SaveRestManager::convert(RtiDriver::SaveFailureReason reason) {
   switch (reason) {
      case RtiDriver::RTI_UNABLE_TO_SAVE:
         return HlaSaveRestoreListener::SAVE_FAILURE_RTI_UNABLE_TO_SAVE;
      case RtiDriver::FEDERATE_REPORTED_FAILURE_DURING_SAVE:
         return HlaSaveRestoreListener::SAVE_FAILURE_FEDERATE_REPORTED_FAILURE;
      case RtiDriver::FEDERATE_RESIGNED_DURING_SAVE:
         return HlaSaveRestoreListener::SAVE_FAILURE_FEDERATE_RESIGNED;
      case RtiDriver::RTI_DETECTED_FAILURE_DURING_SAVE:
         return HlaSaveRestoreListener::SAVE_FAILURE_RTI_DETECTED_FAILURE;
      case RtiDriver::SAVE_TIME_CANNOT_BE_HONORED:
         return HlaSaveRestoreListener::SAVE_FAILURE_SAVE_TIME_CANNOT_BE_HONORED;
      case RtiDriver::SAVE_ABORTED:
         return HlaSaveRestoreListener::SAVE_FAILURE_SAVE_ABORTED;

      default:
      case RtiDriver::UNKNOWN_SAVE_FAILURE:
         return HlaSaveRestoreListener::SAVE_FAILURE_UNKNOWN;
   }
}

HlaSaveRestoreListener::HlaRestoreFailure SaveRestManager::convert(RtiDriver::RestoreFailureReason reason) {
   switch (reason) {
      case RtiDriver::RTI_UNABLE_TO_RESTORE:
         return HlaSaveRestoreListener::RESTORE_FAILURE_RTI_UNABLE_TO_RESTORE;
      case RtiDriver::FEDERATE_REPORTED_FAILURE_DURING_RESTORE:
         return HlaSaveRestoreListener::RESTORE_FAILURE_FEDERATE_REPORTED_FAILURE;
      case RtiDriver::FEDERATE_RESIGNED_DURING_RESTORE:
         return HlaSaveRestoreListener::RESTORE_FAILURE_FEDERATE_RESIGNED;
      case RtiDriver::RTI_DETECTED_FAILURE_DURING_RESTORE:
         return HlaSaveRestoreListener::RESTORE_FAILURE_RTI_DETECTED_FAILURE;
      case RtiDriver::RESTORE_ABORTED:
         return HlaSaveRestoreListener::RESTORE_FAILURE_RESTORE_ABORTED;

      default:
      case RtiDriver::UNKNOWN_RESTORE_FAILURE:
         return HlaSaveRestoreListener::RESTORE_FAILURE_UNKNOWN;
   }
}
