/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLASYNCHRONIZATIONMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLASYNCHRONIZATIONMANAGERIMPL_H

#include <mutex>

#include <LunarSimulation/HlaSynchronizationManager.h>
#include <LunarSimulation/HlaSynchronizationListener.h>
#include <LunarSimulation/HlaException.h>
#include "HlaWorldImpl.h"
#include "ConditionVariable.h"
#include "SyncPointManager.h"
#include "TimeUtility.h"
#include "ListenerSet.h"

namespace LunarSimulation {

    class HlaSynchronizationManagerImpl : public HlaSynchronizationManager, public SyncPointManager::Listener {
    public:
        HlaSynchronizationManagerImpl(SyncPointManager* syncPointManager, HlaWorldImpl* hlaWorldImpl);

        bool registerSynchronizationPoint(const std::wstring& synchronizationPointLabel)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        bool registerSynchronizationPoint(const std::wstring& synchronizationPointLabel,
                                          std::set<std::vector<char> > encodedFederateHandleSynchronizationSet)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        bool isSynchronizationPointRegistered(const std::wstring& synchronizationPointLabel) const;
        std::set<std::wstring> getRegisteredSynchronizationPointLabels() const;
        std::set<std::wstring> getPendingAchieveSynchronizationPointLabels() const;

        bool waitForSynchronizationPointRegistration(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms);

        bool achieveSynchronizationPoint(const std::wstring& synchronizationPointLabel)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        bool achieveSynchronizationPointAndWaitForSynchronized(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        bool achieveSynchronizationPointAndWaitForSynchronized(const std::wstring& synchronizationPointLabel, unsigned long long timeout_ms, bool & didTimeout)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaSynchronizationListener(HlaSynchronizationListenerPtr listener);
        void removeHlaSynchronizationListener(HlaSynchronizationListenerPtr listener);

        /*
        * SyncPointManager.Listener interface impl
        */

        void announceSynchronizationPoint(std::wstring synchPointLabel, HlaTimeStampPtr hlaTimeStamp);
        void federationSynchronized(std::wstring synchPointLabel);

        void fireSynchronizationPointRegistered(const std::wstring& synchPointLabel, const HlaTimeStampPtr hlaTimeStamp);
        void fireSynchronizationPointSynchronized(const std::wstring& synchPointLabel, const HlaTimeStampPtr hlaTimeStamp);

    private:
        SyncPointManager* _syncPointManager;
        HlaWorldImpl* _hlaWorldImpl;

        class SyncPoints {
        public:
            void labelRegistered(const std::wstring& label);
            void labelAchieved(const std::wstring& label);
            void labelSynchronized(const std::wstring& label);
            bool isRegistered(const std::wstring& label) const;
            std::set<std::wstring> getCurrentlyRegistered() const;
            std::set<std::wstring> getPendingAchieve() const;
            bool waitForRegister(const std::wstring& label, unsigned long long timeout);
            bool waitForSynchronized(const std::wstring& label, unsigned long long timeout);

        private:
            std::set<std::wstring> _labels;
            std::set<std::wstring> _labelsPendingAchieve;
            mutable std::mutex _mutex;
            ConditionVariable _condition;

            bool isRegisteredUnlocked(const std::wstring& label) const;
            bool triggered(bool isRegister, const std::wstring& label);
            bool waitForEvent(bool isRegister, const std::wstring& label, unsigned long long timeout);
        };

        SyncPoints _syncPoints;
        ListenerSet<HlaSynchronizationListenerPtr> _listeners;
    };
}
#endif
