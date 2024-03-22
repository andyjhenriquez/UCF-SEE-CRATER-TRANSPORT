/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLASAVERESTOREMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLASAVERESTOREMANAGERIMPL_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <mutex>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaSaveRestoreManager.h>

#include "SaveRestManager.h"

namespace LunarSimulation {
    class HlaWorldImpl;
    class ObjectManager;

    class HlaSaveRestoreManagerImpl : public HlaSaveRestoreManager, SaveRestManager::Listener {
    public:

        HlaSaveRestoreManagerImpl(SaveRestManager* saveRestManager, ObjectManager* objectManager, HlaWorldImpl* hlaWorld);

        ~HlaSaveRestoreManagerImpl() {}

        void requestFederationSave(const std::wstring &label)
        THROW_SPEC (HlaNotConnectedException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException);

        void requestFederationSave(const std::wstring &label, HlaLogicalTimePtr saveTime)
        THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInvalidLogicalTimeException,
                    HlaSaveInProgressException, HlaRestoreInProgressException);

        bool requestFederationRestore(const std::wstring &label)
        THROW_SPEC (HlaNotConnectedException, HlaRtiException,
                    HlaSaveInProgressException, HlaRestoreInProgressException);

        bool awaitGrantedStateAfterRestore(unsigned long long timeoutMillis);

        void setHlaSaveRestoreListener(HlaSaveRestoreListenerPtr listener);

        bool isSaveInProgress();

        bool isRestoreInProgress();

        //Save callbacks

        void initiateFederateSave(const std::wstring& label, HlaLogicalTimePtr logicalTime);

        void federationSaved();

        void federationNotSaved(HlaSaveRestoreListener::HlaSaveFailure failure);

        //Restore callbacks

        void federationRestoreBegun();

        void initiateFederateRestore(const std::wstring& label, HlaFederateIdPtr federateHandle, const std::wstring& federateName);

        bool federationRestored();

        bool federationNotRestored(HlaSaveRestoreListener::HlaRestoreFailure failure);

        void timeAdvanceGrantAfterRestore(HlaLogicalTimePtr logicalTime);

    private:
        SaveRestManager* const _saveRestManager;
        ObjectManager* const _objectManager;
        HlaWorldImpl* const _hlaWorld;
        mutable std::mutex _listenerLock;
        HlaSaveRestoreListenerPtr _saveRestoreListener;
        HlaSaveRestoreListenerPtr _defaultSaveRestoreListener;

        bool _saveInProgress;
        bool _restoreInProgress;
        HlaLogicalTimePtr _restoredTime;
        bool _wasGrantedWhenRestored;
        bool _localRestoreSuccessful;

        class DefaultSaveRestoreListener : public HlaSaveRestoreListener::Adapter {
        };

        HlaSaveRestoreListenerPtr getHlaSaveRestoreListener();
        void performFederateSave(HlaSaveRestoreListenerPtr listener, const std::wstring& label, HlaLogicalTimePtr logicalTime);
        void performSave(bool federateSaved, const std::wstring& label, HlaLogicalTimePtr logicalTime);
        void performFederateRestore(HlaSaveRestoreListenerPtr listener, const std::wstring& label, HlaFederateIdPtr federateHandle, const std::wstring& federateName);
        void performRestore(bool federateRestored, const std::wstring& label, HlaFederateIdPtr federateHandle, const std::wstring& federateName);

        void firePerformFederateSave(const std::wstring& label, HlaLogicalTimePtr saveTime);
        void fireFederationSaved();
        void fireFederationNotSaved(HlaSaveRestoreListener::HlaSaveFailure saveFailureReason);
        void firePerformFederateRestore(const std::wstring& label, HlaFederateIdPtr federateHandle, const std::wstring& federateName);
        void fireFederationRestored(HlaLogicalTimePtr restoredTime, bool wasAdvancing);
        void fireFederationNotRestored(HlaSaveRestoreListener::HlaRestoreFailure restoreFailureReason, bool localRestoreWasSuccessful, HlaLogicalTimePtr localRestoredTime, bool wasAdvancing);
    };
}
#endif
