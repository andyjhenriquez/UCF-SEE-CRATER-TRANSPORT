/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

/*
 * Generated 2024-03-21 15:32:44 (-0400) by guida using Pitch Developer Studio 6.2.0
 */
#include <LunarSimulation/HlaAllHeaders.h>

#ifdef _WIN32
#pragma warning( disable : 4355)
#endif

#include "HlaWorldImpl.h"

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <limits>

#include <mutex>
#include <cmath>

#include <LunarSimulation/HlaTuning.h>
#include "StringUtil.h"
#include "HlaFederateIdImpl.h"
#include "HlaLogicalTimeImpl.h"
#include "HlaInteractionManagerImpl.h"
#include "HlaSaveRestoreManagerImpl.h"

#include "HlaHLAobjectRootManagerImpl.h"
#include "HlaPhysicalEntityManagerImpl.h"
#include "HlaDynamicalEntityManagerImpl.h"
#include "HlaPayloadManagerImpl.h"
#include "HlaLauncherManagerImpl.h"
#include "HlaPhysicalInterfaceManagerImpl.h"
#include "HlaReferenceFrameManagerImpl.h"
#include "HlaMoonManagerImpl.h"
#include "HlaExecutionConfigurationManagerImpl.h"

using namespace std;
using namespace LunarSimulation;

const wchar_t DEFAULT_TIME_STAMP_FACTORY_NAME[] = L"system_clock";

HlaWorldImpl::~HlaWorldImpl() {
    disconnect();
}

HlaWorldPtr HlaWorld::Factory::create(bool manualEvokeMode, HlaSettingsPtr settings, HlaTimeStampFactoryPtr timeStampFactory) {
    return HlaWorldPtr(new HlaWorldImpl(settings, manualEvokeMode, timeStampFactory));
}

HlaWorldImpl::HlaWorldImpl(HlaSettingsPtr settings, bool manualEvokeMode, HlaTimeStampFactoryPtr timeStampFactory) :
    _federateManager(this),
    _objectManager(this, &_federateManager),
    _interactionManager(this, &_federateManager),
    _saveRestManager(&_federateManager),
    _globalInteractionManager(new HlaInteractionManagerImpl(&_interactionManager, this)),
    _saveRestoreManager(new HlaSaveRestoreManagerImpl(&_saveRestManager, &_objectManager, this)),
    _hLAobjectRootManager(new HlaHLAobjectRootManagerImpl(&_objectManager, this)),
    _physicalEntityManager(new HlaPhysicalEntityManagerImpl(&_objectManager, this)),
    _dynamicalEntityManager(new HlaDynamicalEntityManagerImpl(&_objectManager, this)),
    _payloadManager(new HlaPayloadManagerImpl(&_objectManager, this)),
    _launcherManager(new HlaLauncherManagerImpl(&_objectManager, this)),
    _physicalInterfaceManager(new HlaPhysicalInterfaceManagerImpl(&_objectManager, this)),
    _referenceFrameManager(new HlaReferenceFrameManagerImpl(&_objectManager, this)),
    _moonManager(new HlaMoonManagerImpl(&_objectManager, this)),
    _executionConfigurationManager(new HlaExecutionConfigurationManagerImpl(&_objectManager, this)),
    _granted(false),
    _invokeLaterExecutor(this),
    _scheduler(this),
    _defaultExceptionListener(new DefaultExceptionListener()),
    _currentLogicalTime(HlaLogicalTimeImpl::getInvalid()),
    _nextLogicalTime(HlaLogicalTimeImpl::getInvalid()),
    _defaultSendTime(HlaLogicalTimeImpl::getInvalid()),
    _advanceToNextEvent(false)
{
    HlaSettingsPtr candidateSettings = HlaSettingsPtr(new HlaSettings());
    if (!settings || candidateSettings->hasSettingsFile()) {
        _settings = candidateSettings;
    } else {
        _settings = settings;
    }

    _tuning = HlaTuningPtr(new HlaTuning(_settings));
    _notificationQueue.limitCapacity(_tuning->NOTIFICATION_QUEUE_CAPACITY);

    _manualEvokeMode = manualEvokeMode;

    _stepSize = _settings->getStepSize(HlaLogicalTimeImpl::getInitial());
    _lookahead = _settings->getLookahead(HlaLogicalTimeImpl::getInitial());

    if (candidateSettings->hasSettingsFile() || !timeStampFactory) {
        // Order of precedence
        // 1. File-based settings override everything, even if we passed in a timeStampFactory instance, else
        // 2. If we did not pass in a timeStampFactory then use current settings
        wstring factoryName = _settings->getTimeStampFactoryName();
        if (!factoryName.empty()) {
            timeStampFactory = HlaTimeStampFactory::getHlaTimeStampFactory(factoryName);
        }
    }

    _timeStampFactory = timeStampFactory.get() ? timeStampFactory : HlaTimeStampFactory::getHlaTimeStampFactory(DEFAULT_TIME_STAMP_FACTORY_NAME);

    _federateManager.init(&_interactionManager, &_objectManager, _timeStampFactory);
    _connected = false;
    _timeManagementEnabled = false;
}

void HlaWorldImpl::DefaultExceptionListener::exceptionThrown(HlaExceptionPtr exception, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::cerr << "Default exception listener [" << StringUtil::convert(timeStamp->toString()) << "] : " << exception->what() << std::endl;
}

void HlaWorldImpl::startAutoEvokeThread() {
    while (true) {
        try {
            if (!_notificationQueue.evoke()) {
                break;
            }

            //if stop is posted the infinite-loop will break
            if (!_notificationQueue.waitForEnable()) {
                break;
            }
        } catch (std::exception &e) {
            HlaExceptionPtr ex(new HlaInternalException(L"Exception in HlaWorld::startAutoEvokeThread: " + StringUtil::convert(e.what())));
            postException(ex);
        } catch (...) {
            HlaExceptionPtr ex(new HlaInternalException(L"Unknown exception in HlaWorld::startAutoEvokeThread"));
            postException(ex);
        }
    }
}

HlaLogicalTimePtr HlaWorldImpl::connect() THROW_SPEC (HlaConnectException, HlaInvalidLicenseException, HlaFomException,
                                    HlaRtiException, HlaInternalException, HlaNotConnectedException, HlaNormalizerException,
                                    HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    std::lock_guard<std::recursive_mutex> lock(_connectedLock);
    if (!_connected) {
        _currentLogicalTime = _federateManager.connect(_settings);
        _nextLogicalTime = _currentLogicalTime->add(_stepSize);
        _defaultSendTime = inc(_currentLogicalTime, _lookahead, true);

        //Start in Granted state
        _granted = true;

        _connected = true;
        _timeManagementEnabled = _currentLogicalTime != HlaLogicalTimeImpl::getInvalid();
        if (!_manualEvokeMode) {
            _autoEvokeThread = std::shared_ptr<std::thread>(new std::thread(&HlaWorldImpl::startAutoEvokeThread, this));
        }
        fireConnected(getCurrentTime());
    }
    return _currentLogicalTime;
}

void HlaWorldImpl::disconnect() THROW_SPEC (HlaFederateOwnsAttributeException, HlaRtiException, HlaInternalException) {
    disconnect(L"");
}

void HlaWorldImpl::disconnect(const std::wstring& faultDescription) THROW_SPEC (HlaFederateOwnsAttributeException, HlaRtiException, HlaInternalException) {
    std::lock_guard<std::recursive_mutex> lock(_connectedLock);
    if (_connected) {
        _federateManager.disconnect(_settings->getDestroyFederation());
        _connected = false;
        _persistentHelper.clear();

        if (faultDescription.size() > 0) {
            HlaExceptionPtr ex(new HlaNotConnectedException(faultDescription));
            postException(ex);
        }

        fireDisconnected(getCurrentTime());
        _notificationQueue.postStop();
        if (!_manualEvokeMode) {
            _autoEvokeThread->join();
        }
    }
}

bool HlaWorldImpl::enableTimeManagement()
THROW_SPEC (HlaRtiException, HlaInternalException, HlaInvalidLogicalTimeException, HlaInvalidLogicalTimeException)
{
    std::lock_guard<std::recursive_mutex> lock(_connectedLock);
    if (!_connected) {
        throw HlaNotConnectedException(L"Must be connected to federation to enable time management");
    }

    bool regulating = _settings->getTimeRegulating();
    bool constrained = _settings->getTimeConstrained();
    if (_timeManagementEnabled || (!regulating && !constrained)) {
        return false;
    }

    {
        std::lock_guard<std::mutex> lock(_timeStateGranted);
        if (!_granted) {
            throw HlaInTimeAdvancingStateException(L"Can only enable time management in Granted state");
        }
        _granted = false;
    }

    _currentLogicalTime = _federateManager.enableTimeManagement(regulating, constrained, _settings->getDestroyFederation(), false);
    if (_currentLogicalTime == HlaLogicalTimeImpl::getInvalid()) {
        return false;
    }

    _timeManagementEnabled = true;
    _nextLogicalTime = _currentLogicalTime->add(_stepSize);
    _defaultSendTime = inc(_currentLogicalTime, _lookahead, true);
    _granted = true;
    return true;
}

HlaLogicalTimePtr HlaWorldImpl::advance(bool advanceToNextEvent)
THROW_SPEC (HlaNotConnectedException, HlaRtiException, HlaInTimeAdvancingStateException, HlaInvalidLogicalTimeException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   if (_saveRestoreManager->isSaveInProgress()) {
      throw HlaSaveInProgressException(L"Can not advance during save");
   }
   if (_saveRestoreManager->isRestoreInProgress()) {
      throw HlaRestoreInProgressException(L"Can not advance during restore");
   }
   if (!_connected) {
      throw HlaNotConnectedException(L"Must be connected to federation to advance");
   }

   {
      std::lock_guard<std::mutex> lock(_timeStateGranted);
      if (!_granted) {
         throw HlaInTimeAdvancingStateException(L"Can only advance in Granted state");
      }
      _granted = false;
   }
   _advanceToNextEvent = advanceToNextEvent;

   if (_manualEvokeMode) {
      while (!_notificationQueue.hasEvokedGrantDone()) {
         evoke();
      }
   } else {
      _notificationQueue.waitForGrantDone();
   }

   _defaultSendTime = max(inc(_nextLogicalTime, _lookahead, !_advanceToNextEvent), _defaultSendTime);

   fireTimeAdvanceRequested(getCurrentTime(), _nextLogicalTime);

   // if this throws we are stuck in advancing state
   _currentLogicalTime = _advanceToNextEvent ? _federateManager.nextMessageRequestAvailable(_nextLogicalTime) :
                                               _federateManager.timeAdvanceRequest(_nextLogicalTime);

   if (_tuning->ADVANCE_WAITS_FOR_NOTIFICATIONS) {
      _notificationQueue.postGrantReceived();
   }

   returnToGrantedState();

   if (_tuning->ADVANCE_WAITS_FOR_NOTIFICATIONS) {
      if (_manualEvokeMode) {
         while (!_notificationQueue.hasEvokedGrantReceived()) {
            evoke();
         }
      } else {
         _notificationQueue.waitForGrantReceived();
      }
   }

   return _currentLogicalTime;
}

void HlaWorldImpl::returnToGrantedState()
THROW_SPEC (HlaInternalException, HlaRtiException, HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _stepSize = _settings->getStepSize(_nextLogicalTime);
   long long lookahead = _settings->getLookahead(_nextLogicalTime);

   if (lookahead != _lookahead) {
      _lookahead = lookahead;
      _federateManager.modifyLookahead(_lookahead);
   }

   if ((_currentLogicalTime->getValue() >= _nextLogicalTime->getValue()) || _tuning->FORCE_FRAME_TIMES_WHEN_EVENT_BASED) {
      _nextLogicalTime = _currentLogicalTime->add(_stepSize);
   }
   _defaultSendTime = max(inc(_currentLogicalTime, _lookahead, !_advanceToNextEvent), _defaultSendTime);

   std::vector<std::function<void()> > notifications;
   {
      std::lock_guard<std::mutex> lock(_timeStateGranted);
      _granted = true;
      _timeStateGrantedCondition.notify_all();
      notifications = _invokeWhenGranted;
      _invokeWhenGranted.clear();
   }

   fireTimeAdvanceGranted(getCurrentTime(), _currentLogicalTime);

   _notificationQueue.postNotifications(notifications);
   _notificationQueue.postGrantDone();
}

void HlaWorldImpl::invokeWhenGranted(std::function<void()> task) {
   std::lock_guard<std::mutex> lock(_timeStateGranted);
   if (_granted) {
      task();
   } else {
      _invokeWhenGranted.push_back(task);
   }
}

HlaLogicalTimePtr HlaWorldImpl::inc(HlaLogicalTimePtr logicalTime, long long addend, bool mustIncrease) {
   if (mustIncrease && addend == 0) {
      addend = 1;
   }
   return logicalTime->add(addend);
}

HlaLogicalTimePtr HlaWorldImpl::max(HlaLogicalTimePtr time1, HlaLogicalTimePtr time2) {
   if (time1->getValue() > time2->getValue()) {
      return time1;
   } else {
      return time2;
   }
}

HlaLogicalTimePtr HlaWorldImpl::advanceToNextFrame()
THROW_SPEC (HlaNotConnectedException,HlaRtiException,HlaInTimeAdvancingStateException,HlaInvalidLogicalTimeException,HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return advance(false);
}

HlaLogicalTimePtr HlaWorldImpl::advanceToNextEvent()
THROW_SPEC (HlaNotConnectedException,HlaRtiException,HlaInTimeAdvancingStateException,HlaInvalidLogicalTimeException,HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return advance(true);
}

HlaLogicalTimePtr HlaWorldImpl::advanceToLogicalTime(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException,HlaRtiException,HlaInTimeAdvancingStateException,HlaInvalidLogicalTimeException,HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (!logicalTime->isValid()) {
        throw HlaInvalidLogicalTimeException(L"Logical time not valid: " + logicalTime->toString());
    }
    if (logicalTime->getValue() < _currentLogicalTime->getValue()) {
        throw HlaInvalidLogicalTimeException(L"Requested logical time is less the current logical time: " +
                                               logicalTime->toString() + L" < " + _currentLogicalTime->toString());
    }
    _nextLogicalTime = logicalTime;
    return advance(false);
}

HlaLogicalTimePtr HlaWorldImpl::getCurrentLogicalTime() {
    return _currentLogicalTime;
}

HlaLogicalTimePtr HlaWorldImpl::getNextLogicalTime() {
    return _nextLogicalTime;
}

HlaLogicalTimePtr HlaWorldImpl::getDefaultSendTime() {
    return _defaultSendTime;
}

HlaLogicalTimePtr HlaWorldImpl::createLogicalTime(long long value) {
   return HlaLogicalTimeImpl::create(value);
}

HlaLogicalTimePtr HlaWorldImpl::createInvalidLogicalTime() {
   return HlaLogicalTimeImpl::getInvalid();
}

long long HlaWorldImpl::getStepSize() {
   return _stepSize;
}

long long HlaWorldImpl::getLookahead() {
   return _lookahead;
}

HlaTimeStampPtr HlaWorldImpl::getCurrentTime() {
    return _timeStampFactory->create();
}

HlaTimeStampFactoryPtr HlaWorldImpl::getTimeStampFactory() {
    return _timeStampFactory;
}

std::vector<char> HlaWorldImpl::getEncodedHlaFederateHandle() {
    if (!_connected) {
        return std::vector<char>();
    }
    return _federateManager.getEncodedHlaFederateHandle();
}

int HlaWorldImpl::peek() {
    return _notificationQueue.peek();
}

void HlaWorldImpl::evoke() {
    if (!_manualEvokeMode) return;
    _notificationQueue.evoke();

}
void HlaWorldImpl::evokeAll() {
    if (!_manualEvokeMode) return;
    while (peek() != 0) {
        _notificationQueue.evoke();
    }
}

void HlaWorldImpl::evokeAll(unsigned long long millis) {
    if (!_manualEvokeMode) {
        TimeUtility::sleep(millis);
        return;
    }

    TimeUtility::time_point startTime = TimeUtility::getCurrentTime();
    TimeUtility::time_point stopTime = startTime + TimeUtility::millisAsDuration(millis);
    TimeUtility::time_point currentTime = startTime;

    while (currentTime <= stopTime) {
        unsigned long long millisToEvoke = TimeUtility::asMillis(startTime) + millis - TimeUtility::asMillis(currentTime);
        _notificationQueue.evoke(millisToEvoke);
        currentTime = TimeUtility::getCurrentTime();
    }
}

void HlaWorldImpl::invokeLater(std::function<void()> runner) {
    _invokeLaterExecutor.execute(runner);
}

void HlaWorldImpl::postException(HlaExceptionPtr e) {
    HlaTimeStampPtr currentTime = getCurrentTime();
    std::function<void()> callback = std::bind(&ExceptionListener::exceptionThrown, getExceptionListener(), e, currentTime, _currentLogicalTime);
    postNotification(callback);
}

void HlaWorldImpl::postNotification(std::function<void()> notification) {
    _notificationQueue.postNotification(notification);
}

void HlaWorldImpl::disableNotifications() {
    if (_manualEvokeMode) return;
    _notificationQueue.disableNotifications();
}

void HlaWorldImpl::enableNotifications() {
    if (_manualEvokeMode) return;
    _notificationQueue.enableNotifications();
}

void HlaWorldImpl::invokeDelay(unsigned int minDelayMillis, unsigned int maxDelayMillis, std::function<void()> task) {
    float r = static_cast<float>(rand() % 10000);
    float random = r / 10000;
    unsigned int delay = minDelayMillis + static_cast<unsigned int>(floor(random * (maxDelayMillis - minDelayMillis)));
    _scheduler.addTask(task, delay);
}

HlaHLAobjectRootManagerPtr HlaWorldImpl::getHlaHLAobjectRootManager() {
    return _hLAobjectRootManager;
}

HlaPhysicalEntityManagerPtr HlaWorldImpl::getHlaPhysicalEntityManager() {
    return _physicalEntityManager;
}

HlaDynamicalEntityManagerPtr HlaWorldImpl::getHlaDynamicalEntityManager() {
    return _dynamicalEntityManager;
}

HlaPayloadManagerPtr HlaWorldImpl::getHlaPayloadManager() {
    return _payloadManager;
}

HlaLauncherManagerPtr HlaWorldImpl::getHlaLauncherManager() {
    return _launcherManager;
}

HlaPhysicalInterfaceManagerPtr HlaWorldImpl::getHlaPhysicalInterfaceManager() {
    return _physicalInterfaceManager;
}

HlaReferenceFrameManagerPtr HlaWorldImpl::getHlaReferenceFrameManager() {
    return _referenceFrameManager;
}

HlaMoonManagerPtr HlaWorldImpl::getHlaMoonManager() {
    return _moonManager;
}

HlaExecutionConfigurationManagerPtr HlaWorldImpl::getHlaExecutionConfigurationManager() {
    return _executionConfigurationManager;
}

HlaInteractionManagerPtr HlaWorldImpl::getHlaInteractionManager() {
    return _globalInteractionManager;
}

HlaSaveRestoreManagerPtr HlaWorldImpl::getHlaSaveRestoreManager() {
    return _saveRestoreManager;
}

void HlaWorldImpl::setExceptionListener(ExceptionListenerPtr exceptionListener) {
    std::lock_guard<std::mutex> lock(_exceptionListenerLock);
    _exceptionListener = exceptionListener;
}

HlaWorld::ExceptionListenerPtr HlaWorldImpl::getExceptionListener() {
    std::lock_guard<std::mutex> mutex(_exceptionListenerLock);
    if (_exceptionListener) {
        return _exceptionListener;
    } else {
        return _defaultExceptionListener;
    }
}

void HlaWorldImpl::addHlaWorldListener(HlaWorldListenerPtr listener) {
    _worldListeners.add(listener);
}

void HlaWorldImpl::removeHlaWorldListener(HlaWorldListenerPtr listener) {
    _worldListeners.remove(listener);
}

void HlaWorldImpl::fireConnected(HlaTimeStampPtr timeStamp) {
    std::set<HlaWorldListenerPtr> listeners = _worldListeners.getListeners();
    for (std::set<HlaWorldListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaWorldListener::connected, *it, timeStamp);
        postNotification(callback);
    }
}

void HlaWorldImpl::fireDisconnected(HlaTimeStampPtr timeStamp) {
    std::set<HlaWorldListenerPtr> listeners = _worldListeners.getListeners();
    for (std::set<HlaWorldListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaWorldListener::disconnected, *it, timeStamp);
        postNotification(callback);
    }
}

void HlaWorldImpl::fireTimeAdvanceRequested(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr requestedTime) {
    std::set<HlaWorldListenerPtr> listeners = _worldListeners.getListeners();
    for (std::set<HlaWorldListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaWorldListener::timeAdvanceRequested, *it, timeStamp, requestedTime);
        postNotification(callback);
    }
}

void HlaWorldImpl::fireTimeAdvanceGranted(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr grantedTime) {
    std::set<HlaWorldListenerPtr> listeners = _worldListeners.getListeners();
    for (std::set<HlaWorldListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaWorldListener::timeAdvanceGranted, *it, timeStamp, grantedTime);
        postNotification(callback);
    }
}

HlaFederateIdImplPtr HlaWorldImpl::getFederateIdImpl() {
    if (!_connected) {
        return HlaFederateIdImplPtr(new HlaFederateIdImpl());
    }
    return _federateManager.getFederateIdImpl();
}

HlaFederateIdPtr HlaWorldImpl::getFederateId() {
    return std::dynamic_pointer_cast<HlaFederateId>(getFederateIdImpl());
}

void HlaWorldImpl::save(std::wstring label, HlaLogicalTimePtr saveTime) THROW_SPEC(HlaSaveFederateException) {
    SaveState state = {
        saveTime,
        _currentLogicalTime,
        _nextLogicalTime,
        _defaultSendTime,
        _stepSize,
        _lookahead,
        _advanceToNextEvent
    };
    if (!_persistentHelper.saveState(label, state)) {
        throw HlaSaveFederateException(L"Failed to save the internal state");
    }
}

std::pair<HlaLogicalTimePtr, bool> HlaWorldImpl::restore(std::wstring label, HlaFederateIdPtr federateHandle, std::wstring federateName) THROW_SPEC(HlaRestoreFederateException) {
    SaveState state;
    if (!_persistentHelper.loadState(label, state)) {
        throw HlaRestoreFederateException(L"Unable to restore federate, unknown restore label " + label);
    }

    HlaLogicalTimePtr saveTime = state._saveTime;

    bool wasGranted;
    {
        std::lock_guard<std::mutex> lock(_timeStateGranted);
        wasGranted = _granted;
        if (_granted && saveTime->wasReceivedInTimeStampOrder()) {
           _granted = false;
        }
        _invokeWhenGranted.clear();
    }

    _currentLogicalTime = state._currentLogicalTime;
    _nextLogicalTime = state._nextLogicalTime;
    _defaultSendTime = state._defaultSendTime;
    _stepSize = state._stepSize;
    _lookahead = state._lookahead;
    _advanceToNextEvent = state._advanceToNextEvent;

    //federateHandle and federateName will only change if we resign from the federation and restore in a new federation

    return std::pair<HlaLogicalTimePtr, bool>(saveTime, wasGranted);
}

void HlaWorldImpl::timeAdvanceGrantAfterRestore(HlaLogicalTimePtr logicalTime) {
    _currentLogicalTime = logicalTime;

    try {
       returnToGrantedState();
    } catch (HlaException& e) {
       HlaExceptionPtr ex(new HlaInternalException(L"Failed to return to granted time state after restore: " + e.what_w()));
       postException(ex);
    }
}

bool HlaWorldImpl::awaitGranted(unsigned long long timeoutMillis) {
    std::unique_lock<std::mutex> lock(_timeStateGranted);

    TimeUtility::time_point sleepUntil = TimeUtility::addMillisToCurrentTime(timeoutMillis);
    while (!_granted) {
        if (_timeStateGrantedCondition.wait_until(lock, sleepUntil)) {
            return _granted;
        }
     }
     return _granted;
}
