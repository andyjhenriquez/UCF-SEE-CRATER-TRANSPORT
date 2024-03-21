/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include "HlaExecutionConfigurationManagerImpl.h"

#include <functional>

#include <LunarSimulation/HlaExecutionConfigurationManagerListener.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaExecutionConfigurationImpl.h"
#include "HlaWorldImpl.h"
#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"


using namespace LunarSimulation;
using namespace std;

static wchar_t HLA_OBJECT_CLASS_NAME[] = L"HLAobjectRoot.ExecutionConfiguration";

HlaExecutionConfigurationManagerImpl::HlaExecutionConfigurationManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld)
:
_objectManager(objectManager),
_hlaWorld(hlaWorld),
_enabled(true),
_optional(false)
{
    _objectManager->addManager(this, wstring(HLA_OBJECT_CLASS_NAME));
}


bool HlaExecutionConfigurationManagerImpl::isEnabled(const std::wstring& objectClassName) {
    return _enabled;
}

bool HlaExecutionConfigurationManagerImpl::isOptional(const std::wstring& objectClassName) {
    return _optional;
}

void HlaExecutionConfigurationManagerImpl::connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _objectClassHandle = ObjectClassHandlePtr(objectClassHandle.clone());
    RtiDriver::NameSet attributeNames = HlaExecutionConfigurationImpl::getAttributes();
    _objectManager->publish(*_objectClassHandle, attributeNames);
    _objectManager->subscribe(*_objectClassHandle, attributeNames);
}
void HlaExecutionConfigurationManagerImpl::clearAllInstances(bool doFireDeleted) {
    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    HlaExecutionConfigurationImplPtr instance;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        for (InstanceMap::const_iterator it = _localInstances.begin(); it != _localInstances.end(); it++) {
            instance = it->second;
            instance->setRemoved();
            if (doFireDeleted) {
                fireDeleted(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());
            }
        }
        _localInstances.clear();
        _hlaInstanceNameMap.clear();
        _encodedHlaInstanceHandleMap.clear();

        for (InstanceMap::const_iterator it = _remoteInstances.begin(); it != _remoteInstances.end(); it++) {
            instance = it->second;
            instance->setRemoved();
            if (doFireDeleted) {
                fireDeleted(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());
            }
        }
        _remoteInstances.clear();

    }
}

void HlaExecutionConfigurationManagerImpl::disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) {
    _objectClassHandle.reset();
    clearAllInstances(true);
}

void HlaExecutionConfigurationManagerImpl::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
    ObjectInstanceHandlePtr oihPtr(objectInstanceHandle.clone());
    HlaExecutionConfigurationImplPtr instance = createObjectInstance(oihPtr, false, federateId);

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
        _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()]= instance;
        _remoteInstances[oihPtr] = instance;
    }

    fireDiscovered(instance, timeStamp);

    std::set<HlaExecutionConfigurationListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaExecutionConfigurationListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaExecutionConfigurationListener(*it);
    }

    std::set<HlaExecutionConfigurationValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaExecutionConfigurationValueListener(*it);
    }
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    if (_hlaWorld->getTuning()->REQUEST) {
        struct MyRunner {
            static void run(HlaExecutionConfigurationImplPtr instance,
                            ObjectManager* objectManager,
                            HlaWorldImpl* hlaWorld,
                            ObjectInstanceHandlePtr objectInstanceHandle) {
                if (!instance->isRemoved()) {
                    RtiDriver::NameSet unsetAttributes = instance->getUnsetAttributeNames();
                    if (!unsetAttributes.empty()) {
                        try {
                            objectManager->requestAttributeValueUpdate(*objectInstanceHandle, unsetAttributes, hlaWorld->getCurrentTime());
                        } catch (HlaException&) {
                            //Ignoring this exception
                        }
                    }
                }
            }
        };

        std::function<void()> callback = std::bind(&MyRunner::run, instance, _objectManager, _hlaWorld, ObjectInstanceHandlePtr(objectInstanceHandle.clone()));
        _hlaWorld->invokeDelay(_hlaWorld->getTuning()->REQUEST_MIN_DELAY_MS, _hlaWorld->getTuning()->REQUEST_MAX_DELAY_MS, callback);
    }
}

void HlaExecutionConfigurationManagerImpl::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    InstanceMap::const_iterator iter;
    HlaExecutionConfigurationImplPtr instance;
    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        ObjectInstanceHandlePtr oihp(objectInstanceHandle.clone());
        iter = _remoteInstances.find(oihp);

        if (iter == _remoteInstances.end()) {
            HlaExceptionPtr ex(new HlaInternalException(L"Got reflect for an unknown instance: " + (const std::wstring &)objectInstanceHandle));
            _hlaWorld->postException(ex);
            return;
        }
        instance = iter->second;
    }
    instance->reflectAttributeValues(attributes, federateId, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaExecutionConfigurationManagerImpl::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaExecutionConfigurationImplPtr instance;
    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        ObjectInstanceHandlePtr p = ObjectInstanceHandlePtr(objectInstanceHandle.clone());
        InstanceMap::iterator it = _remoteInstances.find(p);
        if (it == _remoteInstances.end()) {
            HlaExceptionPtr ex(new HlaInternalException(L"Got remove for an unknown instance: " + (const std::wstring &)objectInstanceHandle));
            _hlaWorld->postException(ex);
            return;
        }
        instance = it->second;

        _hlaInstanceNameMap.erase(instance->getHlaInstanceName());
        _encodedHlaInstanceHandleMap.erase(instance->getEncodedHlaObjectInstanceHandle());

        if (instance->isLocal()) {
            _localInstances.erase(it);
        } else {
            _remoteInstances.erase(it);
        }

    }

    instance->setRemoved();
    fireDeleted(instance, timeStamp, logicalTime);
}

void HlaExecutionConfigurationManagerImpl::fireDeleted(HlaExecutionConfigurationImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaExecutionConfigurationManagerListenerPtr> listeners = _executionConfigurationManagerListeners.getListeners();
    for (std::set<HlaExecutionConfigurationManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
           std::function<void()> callback = std::bind(&HlaExecutionConfigurationManagerListener::hlaExecutionConfigurationDeleted, *iter, instance, timeStamp, logicalTime);
           _hlaWorld->postNotification(callback);
    }
}
void HlaExecutionConfigurationManagerImpl::fireInitialized(HlaExecutionConfigurationImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaExecutionConfigurationManagerListenerPtr> listeners = _executionConfigurationManagerListeners.getListeners();
    for (std::set<HlaExecutionConfigurationManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationManagerListener::hlaExecutionConfigurationInitialized, *iter, instance, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

std::vector<HlaExecutionConfigurationPtr> HlaExecutionConfigurationManagerImpl::getHlaExecutionConfigurations() {
    return getAllHlaExecutionConfigurations();
}

std::vector<HlaExecutionConfigurationPtr> HlaExecutionConfigurationManagerImpl::getAllHlaExecutionConfigurations() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaExecutionConfigurationPtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator i = _localInstances.begin(); i != _localInstances.end(); ++i) {
        res.push_back(i->second);
    }
    res.reserve(res.size() + _remoteInstances.size());
    for (InstanceMap::const_iterator i = _remoteInstances.begin(); i != _remoteInstances.end(); ++i) {
        res.push_back(i->second);
    }
    return res;
}

std::vector<HlaExecutionConfigurationPtr> HlaExecutionConfigurationManagerImpl::getLocalHlaExecutionConfigurations() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaExecutionConfigurationPtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator iter = _localInstances.begin(); iter != _localInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

std::vector<HlaExecutionConfigurationPtr> HlaExecutionConfigurationManagerImpl::getRemoteHlaExecutionConfigurations() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaExecutionConfigurationPtr> res;
    res.reserve(_remoteInstances.size());
    for (InstanceMap::const_iterator iter = _remoteInstances.begin(); iter != _remoteInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::getExecutionConfigurationByHlaInstanceName(const std::wstring& hlaInstanceName) {
    std::unique_lock<std::mutex> lock(_instancesLock);

    HlaInstanceNameMap::iterator i = _hlaInstanceNameMap.find(hlaInstanceName);
    if (i != _hlaInstanceNameMap.end()) {
        return i->second;
    }

    return HlaExecutionConfigurationPtr();
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::getExecutionConfigurationByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) {
    std::lock_guard<std::mutex> lock(_instancesLock);

    EncodedHlaInstanceHandleMap::iterator i = _encodedHlaInstanceHandleMap.find(encodedHlaInstanceHandle);
    if (i != _encodedHlaInstanceHandleMap.end()) {
        return i->second;
    }

    return HlaExecutionConfigurationPtr();
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::createLocalHlaExecutionConfiguration(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return createLocalInstance(L""
        );
    } catch (HlaInstanceNameInUseException) {
        //can not happen with empty hlaInstanceName
        return HlaExecutionConfigurationPtr();
    }
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::createLocalHlaExecutionConfiguration(const std::wstring& hlaInstanceName
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }

    //Silently ignore if we could not register object instance name, we might have registered it before
    _objectManager->registerObjectInstanceName(hlaInstanceName);

    return createLocalInstance(hlaInstanceName
    );
}


HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::createLocalInstance(
      const std::wstring& hlaInstanceName
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }
    HlaExecutionConfigurationImplPtr instance;
    {
        std::lock_guard<std::mutex> creationLock(_localCreationInProgressLock);
        ObjectInstanceHandlePtr objectInstanceHandle = _objectManager->createObjectInstance(*_objectClassHandle, hlaInstanceName);
        instance = createObjectInstance(objectInstanceHandle, true, _hlaWorld->getFederateIdImpl());
        {
            std::lock_guard<std::mutex> instanceLock(_instancesLock);
            _localInstances[objectInstanceHandle] = instance;
            _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
            _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()] = instance;
        }
    }

    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    fireDiscovered(instance, timeStamp);

    std::set<HlaExecutionConfigurationListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaExecutionConfigurationListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaExecutionConfigurationListener(*it);
    }

    std::set<HlaExecutionConfigurationValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaExecutionConfigurationValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaExecutionConfigurationValueListener(*it);
    }

    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    return instance;
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaExecutionConfiguration(executionConfiguration, _hlaWorld->getCurrentTime(), _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaExecutionConfiguration(executionConfiguration, timestamp, _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaExecutionConfiguration(executionConfiguration, _hlaWorld->getCurrentTime(), logicalTime, true);
}

HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::deleteLocalHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaExecutionConfiguration(executionConfiguration, timestamp, logicalTime, true);
}



HlaExecutionConfigurationPtr HlaExecutionConfigurationManagerImpl::deleteHlaExecutionConfiguration(HlaExecutionConfigurationPtr executionConfiguration, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime, bool checkLocal )
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (executionConfiguration->isRemoved() || (checkLocal && !executionConfiguration->isLocal())) {
        return HlaExecutionConfigurationPtr();
    }

    ObjectInstanceHandlePtr instanceHandle = ((HlaExecutionConfigurationImpl*)executionConfiguration.get())->getObjectInstanceHandle();
    std::vector<char> encodedInstanceHandle =   ((HlaExecutionConfigurationImpl*)executionConfiguration.get())->getEncodedHlaObjectInstanceHandle();
    std::wstring instanceName = ((HlaExecutionConfigurationImpl*)executionConfiguration.get())->getHlaInstanceName();
    _objectManager->deleteObjectInstance(*instanceHandle, timestamp, logicalTime);

    HlaExecutionConfigurationImplPtr executionConfigurationImpl;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        _hlaInstanceNameMap.erase(instanceName);
        _encodedHlaInstanceHandleMap.erase(encodedInstanceHandle);

        if (executionConfiguration->isLocal()) {
            executionConfigurationImpl = _localInstances[instanceHandle];
            _localInstances.erase(instanceHandle);
        } else {
            executionConfigurationImpl = _remoteInstances[instanceHandle];
            _remoteInstances.erase(instanceHandle);
        }

    }

    executionConfigurationImpl->setRemoved();
    fireDeleted(executionConfigurationImpl, timestamp, logicalTime);
    return executionConfiguration;
}

void HlaExecutionConfigurationManagerImpl::addHlaExecutionConfigurationManagerListener(HlaExecutionConfigurationManagerListenerPtr managerListener) {
    _executionConfigurationManagerListeners.add(managerListener);
}

void HlaExecutionConfigurationManagerImpl::removeHlaExecutionConfigurationManagerListener(HlaExecutionConfigurationManagerListenerPtr managerListener) {
    _executionConfigurationManagerListeners.remove(managerListener);
}

void HlaExecutionConfigurationManagerImpl::addHlaExecutionConfigurationDefaultInstanceListener(HlaExecutionConfigurationListenerPtr listener) {
   _defaultInstanceListeners.add(listener);
}

void HlaExecutionConfigurationManagerImpl::addHlaExecutionConfigurationDefaultInstanceValueListener(HlaExecutionConfigurationValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.add(valueListener);
}

void HlaExecutionConfigurationManagerImpl::removeHlaExecutionConfigurationDefaultInstanceListener(HlaExecutionConfigurationListenerPtr listener) {
   _defaultInstanceListeners.remove(listener);
}

void HlaExecutionConfigurationManagerImpl::removeHlaExecutionConfigurationDefaultInstanceValueListener(HlaExecutionConfigurationValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.remove(valueListener);
}

void HlaExecutionConfigurationManagerImpl::setEnabled(bool enabled) {
    _optional = false;
    _enabled = enabled;
}

void HlaExecutionConfigurationManagerImpl::setEnabledIfAvailableInFom() {
    _optional = true;
    _enabled = true;
}

bool HlaExecutionConfigurationManagerImpl::isEnabled() {
    return _objectClassHandle.get() != NULL;
}

HlaExecutionConfigurationImplPtr HlaExecutionConfigurationManagerImpl::createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId) {
    return HlaExecutionConfigurationImplPtr(new HlaExecutionConfigurationImpl(_hlaWorld, this, objectInstanceHandle, isLocal, federateId));
}

void HlaExecutionConfigurationManagerImpl::checkInitializedFired(HlaExecutionConfigurationImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (!instance->isInitializedFired() && instance->isInitialized()) {
        instance->setInitializedFired();
        fireInitialized(instance, timeStamp, logicalTime);
    }
}

void HlaExecutionConfigurationManagerImpl::fireDiscovered(HlaExecutionConfigurationPtr instance, HlaTimeStampPtr timeStamp) {
    std::set<HlaExecutionConfigurationManagerListenerPtr> listeners = _executionConfigurationManagerListeners.getListeners();
    for (std::set<HlaExecutionConfigurationManagerListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaExecutionConfigurationManagerListener::hlaExecutionConfigurationDiscovered, *it, instance, timeStamp);
        _hlaWorld->postNotification(callback);
    }
}

void HlaExecutionConfigurationManagerImpl::updateAttributeValues(HlaExecutionConfigurationImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    _objectManager->updateAttributeValues(*objectInstanceHandle, attributes, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaExecutionConfigurationManagerImpl::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) {
    InstanceMap::const_iterator iter;
    HlaExecutionConfigurationImplPtr instance;
    {
        std::lock_guard<std::mutex> creationLock(_localCreationInProgressLock);
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        ObjectInstanceHandlePtr oihp(objectInstanceHandle.clone());
        iter = _localInstances.find(oihp);
        if (iter == _localInstances.end()) {
            // instance missing since provideAttributeValueUpdate is called on a separate thread
            return;
        }
        instance = iter->second;
    }
    instance->provideAttributeValueUpdate(attributes, timeStamp);
}

void HlaExecutionConfigurationManagerImpl::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaExecutionConfigurationManagerImpl::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaExecutionConfigurationManagerImpl::save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) {
    if (_localInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save local instances");
    }
    if (_remoteInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save remote instances");
    }
}

void HlaExecutionConfigurationManagerImpl::restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) {
    clearAllInstances(false);
}

