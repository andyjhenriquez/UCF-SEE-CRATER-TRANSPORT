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

#include "HlaPhysicalInterfaceManagerImpl.h"

#include <functional>

#include <LunarSimulation/HlaPhysicalInterfaceManagerListener.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaPhysicalInterfaceImpl.h"
#include "HlaWorldImpl.h"
#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"

#include <string>

using namespace LunarSimulation;
using namespace std;

static wchar_t HLA_OBJECT_CLASS_NAME[] = L"HLAobjectRoot.PhysicalInterface";

HlaPhysicalInterfaceManagerImpl::HlaPhysicalInterfaceManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld)
:
_objectManager(objectManager),
_hlaWorld(hlaWorld),
_enabled(true),
_optional(false)
{
    _objectManager->addManager(this, wstring(HLA_OBJECT_CLASS_NAME));
    _getByNameCache.set_function(std::bind(&HlaPhysicalInterfaceManagerImpl::findByName, this, std::placeholders::_1));
}


bool HlaPhysicalInterfaceManagerImpl::isEnabled(const std::wstring& objectClassName) {
    return _enabled;
}

bool HlaPhysicalInterfaceManagerImpl::isOptional(const std::wstring& objectClassName) {
    return _optional;
}

void HlaPhysicalInterfaceManagerImpl::connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _objectClassHandle = ObjectClassHandlePtr(objectClassHandle.clone());
    RtiDriver::NameSet attributeNames = HlaPhysicalInterfaceImpl::getAttributes();
    _objectManager->publish(*_objectClassHandle, attributeNames);
    _objectManager->subscribe(*_objectClassHandle, attributeNames);
}
void HlaPhysicalInterfaceManagerImpl::clearAllInstances(bool doFireDeleted) {
    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    HlaPhysicalInterfaceImplPtr instance;

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

        _getByNameCache.clear();
    }
}

void HlaPhysicalInterfaceManagerImpl::disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) {
    _objectClassHandle.reset();
    clearAllInstances(true);
}

void HlaPhysicalInterfaceManagerImpl::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
    ObjectInstanceHandlePtr oihPtr(objectInstanceHandle.clone());
    HlaPhysicalInterfaceImplPtr instance = createObjectInstance(oihPtr, false, federateId);

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
        _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()]= instance;
        _remoteInstances[oihPtr] = instance;
    }

    fireDiscovered(instance, timeStamp);

    std::set<HlaPhysicalInterfaceListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaPhysicalInterfaceListener(*it);
    }

    std::set<HlaPhysicalInterfaceValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaPhysicalInterfaceValueListener(*it);
    }
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    if (_hlaWorld->getTuning()->REQUEST) {
        struct MyRunner {
            static void run(HlaPhysicalInterfaceImplPtr instance,
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

void HlaPhysicalInterfaceManagerImpl::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    InstanceMap::const_iterator iter;
    HlaPhysicalInterfaceImplPtr instance;
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

void HlaPhysicalInterfaceManagerImpl::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaPhysicalInterfaceImplPtr instance;
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

        if (instance->hasName()) {
            _getByNameCache.remove(instance->getName());
        }
    }

    instance->setRemoved();
    fireDeleted(instance, timeStamp, logicalTime);
}

void HlaPhysicalInterfaceManagerImpl::fireDeleted(HlaPhysicalInterfaceImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPhysicalInterfaceManagerListenerPtr> listeners = _physicalInterfaceManagerListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
           std::function<void()> callback = std::bind(&HlaPhysicalInterfaceManagerListener::hlaPhysicalInterfaceDeleted, *iter, instance, timeStamp, logicalTime);
           _hlaWorld->postNotification(callback);
    }
}
void HlaPhysicalInterfaceManagerImpl::fireInitialized(HlaPhysicalInterfaceImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPhysicalInterfaceManagerListenerPtr> listeners = _physicalInterfaceManagerListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
        std::function<void()> callback = std::bind(&HlaPhysicalInterfaceManagerListener::hlaPhysicalInterfaceInitialized, *iter, instance, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

std::vector<HlaPhysicalInterfacePtr> HlaPhysicalInterfaceManagerImpl::getHlaPhysicalInterfaces() {
    return getAllHlaPhysicalInterfaces();
}

std::vector<HlaPhysicalInterfacePtr> HlaPhysicalInterfaceManagerImpl::getAllHlaPhysicalInterfaces() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPhysicalInterfacePtr> res;
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

std::vector<HlaPhysicalInterfacePtr> HlaPhysicalInterfaceManagerImpl::getLocalHlaPhysicalInterfaces() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPhysicalInterfacePtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator iter = _localInstances.begin(); iter != _localInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

std::vector<HlaPhysicalInterfacePtr> HlaPhysicalInterfaceManagerImpl::getRemoteHlaPhysicalInterfaces() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPhysicalInterfacePtr> res;
    res.reserve(_remoteInstances.size());
    for (InstanceMap::const_iterator iter = _remoteInstances.begin(); iter != _remoteInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

HlaPhysicalInterfaceImplPtr HlaPhysicalInterfaceManagerImpl::findByName(std::wstring name) {
    for (InstanceMap::iterator i = _localInstances.begin(); i != _localInstances.end(); ++i) {
        if (i->second->hasName() && name == i->second->getName()) {
            return i->second;
        }
    }
    for (InstanceMap::iterator i = _remoteInstances.begin(); i != _remoteInstances.end(); ++i) {
        if (i->second->hasName() && name == i->second->getName()) {
            return i->second;
        }
    }
    return HlaPhysicalInterfaceImplPtr();
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::getPhysicalInterfaceByName(std::wstring name) {
    {
        std::lock_guard<std::mutex> lock(_instancesLock);
        // implicit call to findByName if not found in cache
        HlaPhysicalInterfaceImplPtr cachedInstance = _getByNameCache(name, _localInstances.size() + _remoteInstances.size());

        if (cachedInstance && (cachedInstance->isRemoved() || cachedInstance->getName() != name)) {
            _getByNameCache.remove(name);
            // retry after releasing lock
        } else {
            return cachedInstance;
        }
    }

    return getPhysicalInterfaceByName(name);
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::getPhysicalInterfaceByHlaInstanceName(const std::wstring& hlaInstanceName) {
    std::unique_lock<std::mutex> lock(_instancesLock);

    HlaInstanceNameMap::iterator i = _hlaInstanceNameMap.find(hlaInstanceName);
    if (i != _hlaInstanceNameMap.end()) {
        return i->second;
    }

    return HlaPhysicalInterfacePtr();
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::getPhysicalInterfaceByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) {
    std::lock_guard<std::mutex> lock(_instancesLock);

    EncodedHlaInstanceHandleMap::iterator i = _encodedHlaInstanceHandleMap.find(encodedHlaInstanceHandle);
    if (i != _encodedHlaInstanceHandleMap.end()) {
        return i->second;
    }

    return HlaPhysicalInterfacePtr();
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::createLocalHlaPhysicalInterface(
      std::wstring name
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return createLocalInstance(L"",
                                   name
        );
    } catch (HlaInstanceNameInUseException) {
        //can not happen with empty hlaInstanceName
        return HlaPhysicalInterfacePtr();
    }
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::createLocalHlaPhysicalInterface(const std::wstring& hlaInstanceName,
      std::wstring name
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }

    //Silently ignore if we could not register object instance name, we might have registered it before
    _objectManager->registerObjectInstanceName(hlaInstanceName);

    return createLocalInstance(hlaInstanceName,
         name
    );
}


HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::createLocalInstance(
      const std::wstring& hlaInstanceName,
      const std::wstring& name
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }
    HlaPhysicalInterfaceImplPtr instance;
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

    std::set<HlaPhysicalInterfaceListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaPhysicalInterfaceListener(*it);
    }

    std::set<HlaPhysicalInterfaceValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaPhysicalInterfaceValueListener(*it);
    }

    instance->setCreateAttributes(
        std::shared_ptr<std::wstring >(new std::wstring(name)),
        timeStamp
    );
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    return instance;
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaPhysicalInterface(physicalInterface, _hlaWorld->getCurrentTime(), _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaPhysicalInterface(physicalInterface, timestamp, _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaPhysicalInterface(physicalInterface, _hlaWorld->getCurrentTime(), logicalTime, true);
}

HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::deleteLocalHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaPhysicalInterface(physicalInterface, timestamp, logicalTime, true);
}



HlaPhysicalInterfacePtr HlaPhysicalInterfaceManagerImpl::deleteHlaPhysicalInterface(HlaPhysicalInterfacePtr physicalInterface, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime, bool checkLocal )
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (physicalInterface->isRemoved() || (checkLocal && !physicalInterface->isLocal())) {
        return HlaPhysicalInterfacePtr();
    }

    ObjectInstanceHandlePtr instanceHandle = ((HlaPhysicalInterfaceImpl*)physicalInterface.get())->getObjectInstanceHandle();
    std::vector<char> encodedInstanceHandle =   ((HlaPhysicalInterfaceImpl*)physicalInterface.get())->getEncodedHlaObjectInstanceHandle();
    std::wstring instanceName = ((HlaPhysicalInterfaceImpl*)physicalInterface.get())->getHlaInstanceName();
    _objectManager->deleteObjectInstance(*instanceHandle, timestamp, logicalTime);

    HlaPhysicalInterfaceImplPtr physicalInterfaceImpl;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        _hlaInstanceNameMap.erase(instanceName);
        _encodedHlaInstanceHandleMap.erase(encodedInstanceHandle);

        if (physicalInterface->isLocal()) {
            physicalInterfaceImpl = _localInstances[instanceHandle];
            _localInstances.erase(instanceHandle);
        } else {
            physicalInterfaceImpl = _remoteInstances[instanceHandle];
            _remoteInstances.erase(instanceHandle);
        }

        if (physicalInterfaceImpl->hasName()) {
            _getByNameCache.remove(physicalInterfaceImpl->getName());
        }
    }

    physicalInterfaceImpl->setRemoved();
    fireDeleted(physicalInterfaceImpl, timestamp, logicalTime);
    return physicalInterface;
}

void HlaPhysicalInterfaceManagerImpl::addHlaPhysicalInterfaceManagerListener(HlaPhysicalInterfaceManagerListenerPtr managerListener) {
    _physicalInterfaceManagerListeners.add(managerListener);
}

void HlaPhysicalInterfaceManagerImpl::removeHlaPhysicalInterfaceManagerListener(HlaPhysicalInterfaceManagerListenerPtr managerListener) {
    _physicalInterfaceManagerListeners.remove(managerListener);
}

void HlaPhysicalInterfaceManagerImpl::addHlaPhysicalInterfaceDefaultInstanceListener(HlaPhysicalInterfaceListenerPtr listener) {
   _defaultInstanceListeners.add(listener);
}

void HlaPhysicalInterfaceManagerImpl::addHlaPhysicalInterfaceDefaultInstanceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.add(valueListener);
}

void HlaPhysicalInterfaceManagerImpl::removeHlaPhysicalInterfaceDefaultInstanceListener(HlaPhysicalInterfaceListenerPtr listener) {
   _defaultInstanceListeners.remove(listener);
}

void HlaPhysicalInterfaceManagerImpl::removeHlaPhysicalInterfaceDefaultInstanceValueListener(HlaPhysicalInterfaceValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.remove(valueListener);
}

void HlaPhysicalInterfaceManagerImpl::setEnabled(bool enabled) {
    _optional = false;
    _enabled = enabled;
}

void HlaPhysicalInterfaceManagerImpl::setEnabledIfAvailableInFom() {
    _optional = true;
    _enabled = true;
}

bool HlaPhysicalInterfaceManagerImpl::isEnabled() {
    return _objectClassHandle.get() != NULL;
}

HlaPhysicalInterfaceImplPtr HlaPhysicalInterfaceManagerImpl::createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId) {
    return HlaPhysicalInterfaceImplPtr(new HlaPhysicalInterfaceImpl(_hlaWorld, this, objectInstanceHandle, isLocal, federateId));
}

void HlaPhysicalInterfaceManagerImpl::checkInitializedFired(HlaPhysicalInterfaceImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (!instance->isInitializedFired() && instance->isInitialized()) {
        instance->setInitializedFired();
        fireInitialized(instance, timeStamp, logicalTime);
    }
}

void HlaPhysicalInterfaceManagerImpl::fireDiscovered(HlaPhysicalInterfacePtr instance, HlaTimeStampPtr timeStamp) {
    std::set<HlaPhysicalInterfaceManagerListenerPtr> listeners = _physicalInterfaceManagerListeners.getListeners();
    for (std::set<HlaPhysicalInterfaceManagerListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalInterfaceManagerListener::hlaPhysicalInterfaceDiscovered, *it, instance, timeStamp);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalInterfaceManagerImpl::updateAttributeValues(HlaPhysicalInterfaceImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    _objectManager->updateAttributeValues(*objectInstanceHandle, attributes, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaPhysicalInterfaceManagerImpl::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) {
    InstanceMap::const_iterator iter;
    HlaPhysicalInterfaceImplPtr instance;
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

void HlaPhysicalInterfaceManagerImpl::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaPhysicalInterfaceManagerImpl::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaPhysicalInterfaceManagerImpl::save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) {
    if (_localInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save local instances");
    }
    if (_remoteInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save remote instances");
    }
}

void HlaPhysicalInterfaceManagerImpl::restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) {
    clearAllInstances(false);
}

