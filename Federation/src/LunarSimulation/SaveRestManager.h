/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_SAVERESTMANAGER_H
#define DEVELOPER_STUDIO_SAVERESTMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include <string>

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaSaveRestoreListener.h>
#include <LunarSimulation/HlaLogicalTime.h>
#include <LunarSimulation/HlaFederateId.h>

#include "ImplPointers.h"
#include "FederateManager.h"


namespace LunarSimulation {

    class SaveRestManager {

    public:

        class Listener;

        explicit SaveRestManager(FederateManager* federate);

        void setSaveRestoreManager(Listener* saveRestoreManager);

        void connected();

        void disconnect();

        void requestFederationSave(const std::wstring &label, HlaLogicalTimePtr logicalTime)
        THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void federateSaveBegun()
        THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaRestoreInProgressException);

        void federateSaveComplete()
        THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaRestoreInProgressException);

        void federateSaveNotComplete()
        THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaRestoreInProgressException);

        bool requestFederationRestore(const std::wstring &label)
        THROW_SPEC( HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void federateRestoreComplete()
        THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException);

        void federateRestoreNotComplete()
        THROW_SPEC(HlaNotConnectedException, HlaRtiException, HlaSaveInProgressException);



        // Save Callbacks

        void initiateFederateSave(const std::wstring &name, HlaLogicalTimePtr logicalTime);

        void federationSaved();

        void federationNotSaved(RtiDriver::SaveFailureReason reason);

        // Restore Callbacks

        void federationRestoreBegun();

        void initiateFederateRestore(const std::wstring &name, HlaFederateIdPtr federateHandle, const std::wstring &federateName);

        bool federationRestored();

        bool federationNotRestored(RtiDriver::RestoreFailureReason reason);

        void timeAdvanceGrantAfterRestore(HlaLogicalTimePtr logicalTime);

        static HlaSaveRestoreListener::HlaSaveFailure convert(RtiDriver::SaveFailureReason reason);
        static HlaSaveRestoreListener::HlaRestoreFailure convert(RtiDriver::RestoreFailureReason reason);

    private:

        FederateManager* const _federate;
        Listener* _listener;
        bool _connected;

    };

    class SaveRestManager::Listener {
    public:

        virtual ~Listener() {}

        virtual void initiateFederateSave(const std::wstring& label, HlaLogicalTimePtr logicalTime) = 0;

        virtual void federationSaved() = 0;

        virtual void federationNotSaved(HlaSaveRestoreListener::HlaSaveFailure failure) = 0;

        virtual void federationRestoreBegun() = 0;

        virtual void initiateFederateRestore(const std::wstring& label, HlaFederateIdPtr federateHandle, const std::wstring& federateName) = 0;

        virtual bool federationRestored() = 0;

        virtual bool federationNotRestored(HlaSaveRestoreListener::HlaRestoreFailure failure) = 0;

        virtual void timeAdvanceGrantAfterRestore(HlaLogicalTimePtr logicalTime) = 0;
    };
}
#endif
