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

#include "HlaMoonManagerImpl.h"

#include <functional>

#include <LunarSimulation/HlaMoonManagerListener.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaMoonImpl.h"
#include "HlaWorldImpl.h"
#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"


using namespace LunarSimulation;
using namespace std;

static wchar_t HLA_OBJECT_CLASS_NAME[] = L"HLAobjectRoot.ReferenceFrame.Moon";

HlaMoonManagerImpl::HlaMoonManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld)
:
_objectManager(objectManager),
_hlaWorld(hlaWorld),
_enabled(true),
_optional(false)
{
    _objectManager->addManager(this, wstring(HLA_OBJECT_CLASS_NAME));
}


bool HlaMoonManagerImpl::isEnabled(const std::wstring& objectClassName) {
    return _enabled;
}

bool HlaMoonManagerImpl::isOptional(const std::wstring& objectClassName) {
    return _optional;
}

void HlaMoonManagerImpl::connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _objectClassHandle = ObjectClassHandlePtr(objectClassHandle.clone());
    RtiDriver::NameSet attributeNames = HlaMoonImpl::getAttributes();
    _objectManager->publish(*_objectClassHandle, attributeNames);
    _objectManager->subscribe(*_objectClassHandle, attributeNames);
}
void HlaMoonManagerImpl::clearAllInstances(bool doFireDeleted) {
    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    HlaMoonImplPtr instance;

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

void HlaMoonManagerImpl::disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) {
    _objectClassHandle.reset();
    clearAllInstances(true);
}

void HlaMoonManagerImpl::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
    ObjectInstanceHandlePtr oihPtr(objectInstanceHandle.clone());
    HlaMoonImplPtr instance = createObjectInstance(oihPtr, false, federateId);

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
        _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()]= instance;
        _remoteInstances[oihPtr] = instance;
    }

    fireDiscovered(instance, timeStamp);

    std::set<HlaMoonListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaMoonListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaMoonListener(*it);
    }

    std::set<HlaMoonValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaMoonValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaMoonValueListener(*it);
    }
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    if (_hlaWorld->getTuning()->REQUEST) {
        struct MyRunner {
            static void run(HlaMoonImplPtr instance,
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

void HlaMoonManagerImpl::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    InstanceMap::const_iterator iter;
    HlaMoonImplPtr instance;
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

void HlaMoonManagerImpl::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaMoonImplPtr instance;
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

void HlaMoonManagerImpl::fireDeleted(HlaMoonImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaMoonManagerListenerPtr> listeners = _moonManagerListeners.getListeners();
    for (std::set<HlaMoonManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
           std::function<void()> callback = std::bind(&HlaMoonManagerListener::hlaMoonDeleted, *iter, instance, timeStamp, logicalTime);
           _hlaWorld->postNotification(callback);
    }
}
void HlaMoonManagerImpl::fireInitialized(HlaMoonImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaMoonManagerListenerPtr> listeners = _moonManagerListeners.getListeners();
    for (std::set<HlaMoonManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
        std::function<void()> callback = std::bind(&HlaMoonManagerListener::hlaMoonInitialized, *iter, instance, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

std::vector<HlaMoonPtr> HlaMoonManagerImpl::getHlaMoons() {
    return getAllHlaMoons();
}

std::vector<HlaMoonPtr> HlaMoonManagerImpl::getAllHlaMoons() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaMoonPtr> res;
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

std::vector<HlaMoonPtr> HlaMoonManagerImpl::getLocalHlaMoons() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaMoonPtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator iter = _localInstances.begin(); iter != _localInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

std::vector<HlaMoonPtr> HlaMoonManagerImpl::getRemoteHlaMoons() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaMoonPtr> res;
    res.reserve(_remoteInstances.size());
    for (InstanceMap::const_iterator iter = _remoteInstances.begin(); iter != _remoteInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

HlaMoonPtr HlaMoonManagerImpl::getMoonByHlaInstanceName(const std::wstring& hlaInstanceName) {
    std::unique_lock<std::mutex> lock(_instancesLock);

    HlaInstanceNameMap::iterator i = _hlaInstanceNameMap.find(hlaInstanceName);
    if (i != _hlaInstanceNameMap.end()) {
        return i->second;
    }

    return HlaMoonPtr();
}

HlaMoonPtr HlaMoonManagerImpl::getMoonByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) {
    std::lock_guard<std::mutex> lock(_instancesLock);

    EncodedHlaInstanceHandleMap::iterator i = _encodedHlaInstanceHandleMap.find(encodedHlaInstanceHandle);
    if (i != _encodedHlaInstanceHandleMap.end()) {
        return i->second;
    }

    return HlaMoonPtr();
}

HlaMoonPtr HlaMoonManagerImpl::createLocalHlaMoon(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return createLocalInstance(L""
        );
    } catch (HlaInstanceNameInUseException) {
        //can not happen with empty hlaInstanceName
        return HlaMoonPtr();
    }
}

HlaMoonPtr HlaMoonManagerImpl::createLocalHlaMoon(const std::wstring& hlaInstanceName
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


HlaMoonPtr HlaMoonManagerImpl::createLocalInstance(
      const std::wstring& hlaInstanceName
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }
    HlaMoonImplPtr instance;
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

    std::set<HlaMoonListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaMoonListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaMoonListener(*it);
    }

    std::set<HlaMoonValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaMoonValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaMoonValueListener(*it);
    }

    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    return instance;
}

HlaMoonPtr HlaMoonManagerImpl::deleteLocalHlaMoon(HlaMoonPtr moon)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaMoon(moon, _hlaWorld->getCurrentTime(), _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaMoonPtr HlaMoonManagerImpl::deleteLocalHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaMoon(moon, timestamp, _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaMoonPtr HlaMoonManagerImpl::deleteLocalHlaMoon(HlaMoonPtr moon, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaMoon(moon, _hlaWorld->getCurrentTime(), logicalTime, true);
}

HlaMoonPtr HlaMoonManagerImpl::deleteLocalHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaMoon(moon, timestamp, logicalTime, true);
}



HlaMoonPtr HlaMoonManagerImpl::deleteHlaMoon(HlaMoonPtr moon, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime, bool checkLocal )
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (moon->isRemoved() || (checkLocal && !moon->isLocal())) {
        return HlaMoonPtr();
    }

    ObjectInstanceHandlePtr instanceHandle = ((HlaMoonImpl*)moon.get())->getObjectInstanceHandle();
    std::vector<char> encodedInstanceHandle =   ((HlaMoonImpl*)moon.get())->getEncodedHlaObjectInstanceHandle();
    std::wstring instanceName = ((HlaMoonImpl*)moon.get())->getHlaInstanceName();
    _objectManager->deleteObjectInstance(*instanceHandle, timestamp, logicalTime);

    HlaMoonImplPtr moonImpl;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        _hlaInstanceNameMap.erase(instanceName);
        _encodedHlaInstanceHandleMap.erase(encodedInstanceHandle);

        if (moon->isLocal()) {
            moonImpl = _localInstances[instanceHandle];
            _localInstances.erase(instanceHandle);
        } else {
            moonImpl = _remoteInstances[instanceHandle];
            _remoteInstances.erase(instanceHandle);
        }

    }

    moonImpl->setRemoved();
    fireDeleted(moonImpl, timestamp, logicalTime);
    return moon;
}

void HlaMoonManagerImpl::addHlaMoonManagerListener(HlaMoonManagerListenerPtr managerListener) {
    _moonManagerListeners.add(managerListener);
}

void HlaMoonManagerImpl::removeHlaMoonManagerListener(HlaMoonManagerListenerPtr managerListener) {
    _moonManagerListeners.remove(managerListener);
}

void HlaMoonManagerImpl::addHlaMoonDefaultInstanceListener(HlaMoonListenerPtr listener) {
   _defaultInstanceListeners.add(listener);
}

void HlaMoonManagerImpl::addHlaMoonDefaultInstanceValueListener(HlaMoonValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.add(valueListener);
}

void HlaMoonManagerImpl::removeHlaMoonDefaultInstanceListener(HlaMoonListenerPtr listener) {
   _defaultInstanceListeners.remove(listener);
}

void HlaMoonManagerImpl::removeHlaMoonDefaultInstanceValueListener(HlaMoonValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.remove(valueListener);
}

void HlaMoonManagerImpl::setEnabled(bool enabled) {
    _optional = false;
    _enabled = enabled;
}

void HlaMoonManagerImpl::setEnabledIfAvailableInFom() {
    _optional = true;
    _enabled = true;
}

bool HlaMoonManagerImpl::isEnabled() {
    return _objectClassHandle.get() != NULL;
}

HlaMoonImplPtr HlaMoonManagerImpl::createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId) {
    return HlaMoonImplPtr(new HlaMoonImpl(_hlaWorld, this, objectInstanceHandle, isLocal, federateId));
}

void HlaMoonManagerImpl::checkInitializedFired(HlaMoonImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (!instance->isInitializedFired() && instance->isInitialized()) {
        instance->setInitializedFired();
        fireInitialized(instance, timeStamp, logicalTime);
    }
}

void HlaMoonManagerImpl::fireDiscovered(HlaMoonPtr instance, HlaTimeStampPtr timeStamp) {
    std::set<HlaMoonManagerListenerPtr> listeners = _moonManagerListeners.getListeners();
    for (std::set<HlaMoonManagerListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaMoonManagerListener::hlaMoonDiscovered, *it, instance, timeStamp);
        _hlaWorld->postNotification(callback);
    }
}

void HlaMoonManagerImpl::updateAttributeValues(HlaMoonImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    _objectManager->updateAttributeValues(*objectInstanceHandle, attributes, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaMoonManagerImpl::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) {
    InstanceMap::const_iterator iter;
    HlaMoonImplPtr instance;
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

void HlaMoonManagerImpl::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaMoonManagerImpl::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaMoonManagerImpl::save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) {
    if (_localInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save local instances");
    }
    if (_remoteInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save remote instances");
    }
}

void HlaMoonManagerImpl::restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) {
    clearAllInstances(false);
}

