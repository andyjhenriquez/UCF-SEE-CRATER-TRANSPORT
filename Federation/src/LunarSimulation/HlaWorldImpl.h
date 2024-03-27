/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAWORLDIMPL_H
#define DEVELOPER_STUDIO_HLAWORLDIMPL_H

#include <exception>

#include <functional>
#include <memory>
#include <mutex>
#include <thread>

#include <LunarSimulation/HlaWorld.h>
#include <LunarSimulation/HlaSettings.h>
#include <vector>
#include "ImplPointers.h"
#include "NotificationQueue.h"
#include "Scheduler.h"
#include "InvokeLaterExecutor.h"
#include "ListenerSet.h"
#include "SaveRestManager.h"
#include "SyncPointManager.h"
#include "FederateManager.h"
#include "ObjectManager.h"
#include "RtiInteractionManager.h"
#include "PersistentHelper.h"

namespace LunarSimulation {
    class HlaSynchronizationManagerImpl;
    class HlaInteractionManagerImpl;
    class HlaSaveRestoreManagerImpl;

    class HlaHLAobjectRootManagerImpl;
    class HlaPhysicalEntityManagerImpl;
    class HlaDynamicalEntityManagerImpl;
    class HlaPayloadManagerImpl;
    class HlaLauncherManagerImpl;
    class HlaPhysicalInterfaceManagerImpl;
    class HlaReferenceFrameManagerImpl;
    class HlaMoonManagerImpl;
    class HlaExecutionConfigurationManagerImpl;

    class HlaWorldImpl : public HlaWorld {
    private:
        HlaTimeStampFactoryPtr _timeStampFactory;
        FederateManager _federateManager;
        ObjectManager _objectManager;
        RtiInteractionManager _interactionManager;
        SaveRestManager _saveRestManager;
        NotificationQueue _notificationQueue;
        HlaSettingsPtr _settings;
        HlaTuningPtr _tuning;
        ListenerSet<HlaWorldListenerPtr> _worldListeners;
        std::shared_ptr<HlaInteractionManagerImpl> _globalInteractionManager;
        std::shared_ptr<HlaSaveRestoreManagerImpl> _saveRestoreManager;
        std::vector<std::function<void()> > _invokeWhenGranted;
        std::shared_ptr<HlaHLAobjectRootManagerImpl> _hLAobjectRootManager;
        std::shared_ptr<HlaPhysicalEntityManagerImpl> _physicalEntityManager;
        std::shared_ptr<HlaDynamicalEntityManagerImpl> _dynamicalEntityManager;
        std::shared_ptr<HlaPayloadManagerImpl> _payloadManager;
        std::shared_ptr<HlaLauncherManagerImpl> _launcherManager;
        std::shared_ptr<HlaPhysicalInterfaceManagerImpl> _physicalInterfaceManager;
        std::shared_ptr<HlaReferenceFrameManagerImpl> _referenceFrameManager;
        std::shared_ptr<HlaMoonManagerImpl> _moonManager;
        std::shared_ptr<HlaExecutionConfigurationManagerImpl> _executionConfigurationManager;
        SyncPointManager _syncPointManager;
        std::shared_ptr<HlaSynchronizationManagerImpl> _synchronizationManager;
        void addHlaWorldListener(HlaWorldListenerPtr listener);
        void removeHlaWorldListener(HlaWorldListenerPtr listener);
        void fireConnected(HlaTimeStampPtr timeStamp);
        void fireDisconnected(HlaTimeStampPtr timeStamp);
        void fireTimeAdvanceRequested(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr requestedTime);
        void fireTimeAdvanceGranted(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr grantedTime);

        mutable std::recursive_mutex _connectedLock;
        bool _connected;
        bool _timeManagementEnabled;
        mutable std::mutex _timeStateGranted;
        ConditionVariable _timeStateGrantedCondition;
        bool _granted;

        std::shared_ptr<std::thread> _autoEvokeThread;
        bool _manualEvokeMode;
        InvokeLaterExecutor _invokeLaterExecutor;
        Scheduler _scheduler;
        void startAutoEvokeThread();

        mutable std::mutex _exceptionListenerLock;
        HlaWorld::ExceptionListenerPtr _exceptionListener;
        HlaWorld::ExceptionListenerPtr _defaultExceptionListener;

        class DefaultExceptionListener : public HlaWorld::ExceptionListener {
        public: 
            void exceptionThrown(HlaExceptionPtr exception, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        };

        HlaLogicalTimePtr advance(bool advanceToNextEvent)
            THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInTimeAdvancingStateException,
                        HlaInvalidLogicalTimeException, HlaInternalException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaLogicalTimePtr inc(HlaLogicalTimePtr logicalTime, long long addend, bool mustIncrease);
        HlaLogicalTimePtr max(HlaLogicalTimePtr time1, HlaLogicalTimePtr time2);
        void returnToGrantedState()
            THROW_SPEC (HlaInternalException, HlaRtiException,
                        HlaNotConnectedException, HlaInvalidLogicalTimeException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);

        HlaLogicalTimePtr _currentLogicalTime;
        HlaLogicalTimePtr _nextLogicalTime;
        HlaLogicalTimePtr _defaultSendTime;
        long long _stepSize;
        long long _lookahead;
        bool _advanceToNextEvent;

        struct SaveState {
            HlaLogicalTimePtr _saveTime;
            HlaLogicalTimePtr _currentLogicalTime;
            HlaLogicalTimePtr _nextLogicalTime;
            HlaLogicalTimePtr _defaultSendTime;
            long long _stepSize;
            long long _lookahead;
            bool _advanceToNextEvent;
        };

        PersistentHelper<SaveState> _persistentHelper;

    public:
        HlaWorldImpl(HlaSettingsPtr settings, bool manualEvokeMode, HlaTimeStampFactoryPtr);

        ~HlaWorldImpl();

        HlaLogicalTimePtr connect() THROW_SPEC (HlaConnectException, HlaInvalidLicenseException,
            HlaFomException, HlaRtiException, HlaNormalizerException,
            HlaInternalException, HlaNotConnectedException, HlaInvalidLogicalTimeException,
            HlaSaveInProgressException, HlaRestoreInProgressException);

        void disconnect() THROW_SPEC (HlaFederateOwnsAttributeException, HlaRtiException, HlaInternalException);
        void disconnect(const std::wstring& faultDescription) THROW_SPEC (HlaFederateOwnsAttributeException, HlaRtiException, HlaInternalException);
        bool enableTimeManagement()
            THROW_SPEC (HlaRtiException, HlaInternalException, HlaInvalidLogicalTimeException,
                        HlaInvalidLogicalTimeException);
        HlaLogicalTimePtr advanceToNextFrame()
            THROW_SPEC (HlaNotConnectedException,HlaRtiException,HlaInTimeAdvancingStateException,
                        HlaInvalidLogicalTimeException,HlaInternalException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaLogicalTimePtr advanceToNextEvent()
            THROW_SPEC (HlaNotConnectedException,HlaRtiException,HlaInTimeAdvancingStateException,
                        HlaInvalidLogicalTimeException,HlaInternalException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);
        HlaLogicalTimePtr advanceToLogicalTime(HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException,HlaRtiException,HlaInTimeAdvancingStateException,
                        HlaInvalidLogicalTimeException,HlaInternalException,
                        HlaSaveInProgressException, HlaRestoreInProgressException);
        void invokeWhenGranted(std::function<void()> task);
        HlaLogicalTimePtr getCurrentLogicalTime();
        HlaLogicalTimePtr getNextLogicalTime();
        HlaLogicalTimePtr getDefaultSendTime();
        HlaLogicalTimePtr createLogicalTime(long long value);
        HlaLogicalTimePtr createInvalidLogicalTime();
        long long getStepSize();
        long long getLookahead();

        HlaTimeStampPtr getCurrentTime();
        HlaTimeStampFactoryPtr getTimeStampFactory();

        std::vector<char> getEncodedHlaFederateHandle();

        int peek();
        void evoke();
        void evokeAll();
        void evokeAll(unsigned long long millis);

        void postException(HlaExceptionPtr e);
        void postNotification(std::function<void()> notification);

        void disableNotifications();
        void enableNotifications();

        void invokeLater(std::function<void()> runner);
        void invokeDelay(unsigned int minDelayMillis, unsigned int maxDelayMillis, std::function<void()> runner);

        HlaHLAobjectRootManagerPtr getHlaHLAobjectRootManager();
        HlaPhysicalEntityManagerPtr getHlaPhysicalEntityManager();
        HlaDynamicalEntityManagerPtr getHlaDynamicalEntityManager();
        HlaPayloadManagerPtr getHlaPayloadManager();
        HlaLauncherManagerPtr getHlaLauncherManager();
        HlaPhysicalInterfaceManagerPtr getHlaPhysicalInterfaceManager();
        HlaReferenceFrameManagerPtr getHlaReferenceFrameManager();
        HlaMoonManagerPtr getHlaMoonManager();
        HlaExecutionConfigurationManagerPtr getHlaExecutionConfigurationManager();
        HlaInteractionManagerPtr getHlaInteractionManager();
        HlaSaveRestoreManagerPtr getHlaSaveRestoreManager();
        HlaSynchronizationManagerPtr getHlaSynchronizationManager();

        void setExceptionListener(ExceptionListenerPtr exceptionListener);
        ExceptionListenerPtr getExceptionListener();

        HlaSettingsPtr getSettings() {
            return _settings;
        }

        HlaTuningPtr getTuning() {
            return _tuning;
        }

        HlaFederateIdImplPtr getFederateIdImpl();
        HlaFederateIdPtr getFederateId();

        void save(std::wstring label, HlaLogicalTimePtr saveTime) THROW_SPEC(HlaSaveFederateException);
        std::pair<HlaLogicalTimePtr, bool> restore(std::wstring label, HlaFederateIdPtr federateHandle, std::wstring federateName) THROW_SPEC(HlaRestoreFederateException);
        void timeAdvanceGrantAfterRestore(HlaLogicalTimePtr logicalTime);
        bool awaitGranted(unsigned long long timeoutMillis);
    };
}
#endif
