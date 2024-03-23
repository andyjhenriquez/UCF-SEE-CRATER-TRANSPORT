/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_SYNCPOINTMANAGER_H
#define DEVELOPER_STUDIO_SYNCPOINTMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <set>

#include <mutex>

#include <LunarSimulation/HlaTimeStamp.h>
#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>
#include "ListenerSet.h"

namespace LunarSimulation {
    class FederateManager;

    class SyncPointManager {
    public:
        class Listener {
        public:
            virtual ~Listener() {}
            virtual void announceSynchronizationPoint(std::wstring synchPointLabel, HlaTimeStampPtr hlaTimeStamp) = 0;
            virtual void federationSynchronized(std::wstring synchPointLabel) = 0;
        };

        explicit SyncPointManager(FederateManager* federate);
        void addSynchronizationPointHandler(Listener* listener);

        bool registerFederationSynchronizationPoint(std::wstring synchPointLabel,
                                                    std::set<std::vector<char> > encodedFederateHandles,
                                                    HlaTimeStampPtr timeStamp)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        bool synchronizationPointAchieved(std::wstring synchPointLabel)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void announceSynchronizationPoint(std::wstring synchPointLabel, HlaTimeStampPtr hlaTimeStamp);
        void federationSynchronized(std::wstring synchPointLabel);

        void connected();
        void disconnect();

    private:
        FederateManager* _federate;
        mutable std::mutex _registerInProgressLock;
        ListenerSet<Listener*> _listeners;
        bool _connected;
    };
}
#endif
