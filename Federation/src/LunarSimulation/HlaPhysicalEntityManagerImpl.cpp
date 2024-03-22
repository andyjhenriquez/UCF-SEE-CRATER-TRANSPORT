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

#include "HlaPhysicalEntityManagerImpl.h"

#include <functional>

#include <LunarSimulation/HlaPhysicalEntityManagerListener.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaPhysicalEntityImpl.h"
#include "HlaWorldImpl.h"
#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"

#include <string>

using namespace LunarSimulation;
using namespace std;

static wchar_t HLA_OBJECT_CLASS_NAME[] = L"HLAobjectRoot.PhysicalEntity";

HlaPhysicalEntityManagerImpl::HlaPhysicalEntityManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld)
:
_objectManager(objectManager),
_hlaWorld(hlaWorld),
_enabled(true),
_optional(false)
{
    _objectManager->addManager(this, wstring(HLA_OBJECT_CLASS_NAME));
    _getByNameCache.set_function(std::bind(&HlaPhysicalEntityManagerImpl::findByName, this, std::placeholders::_1));
}


bool HlaPhysicalEntityManagerImpl::isEnabled(const std::wstring& objectClassName) {
    return _enabled;
}

bool HlaPhysicalEntityManagerImpl::isOptional(const std::wstring& objectClassName) {
    return _optional;
}

void HlaPhysicalEntityManagerImpl::connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _objectClassHandle = ObjectClassHandlePtr(objectClassHandle.clone());
    RtiDriver::NameSet attributeNames = HlaPhysicalEntityImpl::getAttributes();
    _objectManager->publish(*_objectClassHandle, attributeNames);
    _objectManager->subscribe(*_objectClassHandle, attributeNames);
}
void HlaPhysicalEntityManagerImpl::clearAllInstances(bool doFireDeleted) {
    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    HlaPhysicalEntityImplPtr instance;

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

void HlaPhysicalEntityManagerImpl::disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) {
    _objectClassHandle.reset();
    clearAllInstances(true);
}

void HlaPhysicalEntityManagerImpl::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
    ObjectInstanceHandlePtr oihPtr(objectInstanceHandle.clone());
    HlaPhysicalEntityImplPtr instance = createObjectInstance(oihPtr, false, federateId);

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
        _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()]= instance;
        _remoteInstances[oihPtr] = instance;
    }

    fireDiscovered(instance, timeStamp);

    std::set<HlaPhysicalEntityListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaPhysicalEntityListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaPhysicalEntityListener(*it);
    }

    std::set<HlaPhysicalEntityValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaPhysicalEntityValueListener(*it);
    }
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    if (_hlaWorld->getTuning()->REQUEST) {
        struct MyRunner {
            static void run(HlaPhysicalEntityImplPtr instance,
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

void HlaPhysicalEntityManagerImpl::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    InstanceMap::const_iterator iter;
    HlaPhysicalEntityImplPtr instance;
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

void HlaPhysicalEntityManagerImpl::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaPhysicalEntityImplPtr instance;
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

void HlaPhysicalEntityManagerImpl::fireDeleted(HlaPhysicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPhysicalEntityManagerListenerPtr> listeners = _physicalEntityManagerListeners.getListeners();
    for (std::set<HlaPhysicalEntityManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
           std::function<void()> callback = std::bind(&HlaPhysicalEntityManagerListener::hlaPhysicalEntityDeleted, *iter, instance, timeStamp, logicalTime);
           _hlaWorld->postNotification(callback);
    }
}
void HlaPhysicalEntityManagerImpl::fireInitialized(HlaPhysicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPhysicalEntityManagerListenerPtr> listeners = _physicalEntityManagerListeners.getListeners();
    for (std::set<HlaPhysicalEntityManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityManagerListener::hlaPhysicalEntityInitialized, *iter, instance, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

std::vector<HlaPhysicalEntityPtr> HlaPhysicalEntityManagerImpl::getHlaPhysicalEntitys() {
    return getAllHlaPhysicalEntitys();
}

std::vector<HlaPhysicalEntityPtr> HlaPhysicalEntityManagerImpl::getAllHlaPhysicalEntitys() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPhysicalEntityPtr> res;
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

std::vector<HlaPhysicalEntityPtr> HlaPhysicalEntityManagerImpl::getLocalHlaPhysicalEntitys() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPhysicalEntityPtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator iter = _localInstances.begin(); iter != _localInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

std::vector<HlaPhysicalEntityPtr> HlaPhysicalEntityManagerImpl::getRemoteHlaPhysicalEntitys() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPhysicalEntityPtr> res;
    res.reserve(_remoteInstances.size());
    for (InstanceMap::const_iterator iter = _remoteInstances.begin(); iter != _remoteInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

HlaPhysicalEntityImplPtr HlaPhysicalEntityManagerImpl::findByName(std::wstring name) {
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
    return HlaPhysicalEntityImplPtr();
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::getPhysicalEntityByName(std::wstring name) {
    {
        std::lock_guard<std::mutex> lock(_instancesLock);
        // implicit call to findByName if not found in cache
        HlaPhysicalEntityImplPtr cachedInstance = _getByNameCache(name, _localInstances.size() + _remoteInstances.size());

        if (cachedInstance && (cachedInstance->isRemoved() || cachedInstance->getName() != name)) {
            _getByNameCache.remove(name);
            // retry after releasing lock
        } else {
            return cachedInstance;
        }
    }

    return getPhysicalEntityByName(name);
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::getPhysicalEntityByHlaInstanceName(const std::wstring& hlaInstanceName) {
    std::unique_lock<std::mutex> lock(_instancesLock);

    HlaInstanceNameMap::iterator i = _hlaInstanceNameMap.find(hlaInstanceName);
    if (i != _hlaInstanceNameMap.end()) {
        return i->second;
    }

    return HlaPhysicalEntityPtr();
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::getPhysicalEntityByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) {
    std::lock_guard<std::mutex> lock(_instancesLock);

    EncodedHlaInstanceHandleMap::iterator i = _encodedHlaInstanceHandleMap.find(encodedHlaInstanceHandle);
    if (i != _encodedHlaInstanceHandleMap.end()) {
        return i->second;
    }

    return HlaPhysicalEntityPtr();
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::createLocalHlaPhysicalEntity(
      std::wstring name
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return createLocalInstance(L"",
                                   name
        );
    } catch (HlaInstanceNameInUseException) {
        //can not happen with empty hlaInstanceName
        return HlaPhysicalEntityPtr();
    }
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::createLocalHlaPhysicalEntity(const std::wstring& hlaInstanceName,
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


HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::createLocalInstance(
      const std::wstring& hlaInstanceName,
      const std::wstring& name
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }
    HlaPhysicalEntityImplPtr instance;
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

    std::set<HlaPhysicalEntityListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaPhysicalEntityListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaPhysicalEntityListener(*it);
    }

    std::set<HlaPhysicalEntityValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaPhysicalEntityValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaPhysicalEntityValueListener(*it);
    }

    instance->setCreateAttributes(
        std::shared_ptr<std::wstring >(new std::wstring(name)),
        timeStamp
    );
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    return instance;
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaPhysicalEntity(physicalEntity, _hlaWorld->getCurrentTime(), _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaPhysicalEntity(physicalEntity, timestamp, _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaPhysicalEntity(physicalEntity, _hlaWorld->getCurrentTime(), logicalTime, true);
}

HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::deleteLocalHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaPhysicalEntity(physicalEntity, timestamp, logicalTime, true);
}



HlaPhysicalEntityPtr HlaPhysicalEntityManagerImpl::deleteHlaPhysicalEntity(HlaPhysicalEntityPtr physicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime, bool checkLocal )
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (physicalEntity->isRemoved() || (checkLocal && !physicalEntity->isLocal())) {
        return HlaPhysicalEntityPtr();
    }

    ObjectInstanceHandlePtr instanceHandle = ((HlaPhysicalEntityImpl*)physicalEntity.get())->getObjectInstanceHandle();
    std::vector<char> encodedInstanceHandle =   ((HlaPhysicalEntityImpl*)physicalEntity.get())->getEncodedHlaObjectInstanceHandle();
    std::wstring instanceName = ((HlaPhysicalEntityImpl*)physicalEntity.get())->getHlaInstanceName();
    _objectManager->deleteObjectInstance(*instanceHandle, timestamp, logicalTime);

    HlaPhysicalEntityImplPtr physicalEntityImpl;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        _hlaInstanceNameMap.erase(instanceName);
        _encodedHlaInstanceHandleMap.erase(encodedInstanceHandle);

        if (physicalEntity->isLocal()) {
            physicalEntityImpl = _localInstances[instanceHandle];
            _localInstances.erase(instanceHandle);
        } else {
            physicalEntityImpl = _remoteInstances[instanceHandle];
            _remoteInstances.erase(instanceHandle);
        }

        if (physicalEntityImpl->hasName()) {
            _getByNameCache.remove(physicalEntityImpl->getName());
        }
    }

    physicalEntityImpl->setRemoved();
    fireDeleted(physicalEntityImpl, timestamp, logicalTime);
    return physicalEntity;
}

void HlaPhysicalEntityManagerImpl::addHlaPhysicalEntityManagerListener(HlaPhysicalEntityManagerListenerPtr managerListener) {
    _physicalEntityManagerListeners.add(managerListener);
}

void HlaPhysicalEntityManagerImpl::removeHlaPhysicalEntityManagerListener(HlaPhysicalEntityManagerListenerPtr managerListener) {
    _physicalEntityManagerListeners.remove(managerListener);
}

void HlaPhysicalEntityManagerImpl::addHlaPhysicalEntityDefaultInstanceListener(HlaPhysicalEntityListenerPtr listener) {
   _defaultInstanceListeners.add(listener);
}

void HlaPhysicalEntityManagerImpl::addHlaPhysicalEntityDefaultInstanceValueListener(HlaPhysicalEntityValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.add(valueListener);
}

void HlaPhysicalEntityManagerImpl::removeHlaPhysicalEntityDefaultInstanceListener(HlaPhysicalEntityListenerPtr listener) {
   _defaultInstanceListeners.remove(listener);
}

void HlaPhysicalEntityManagerImpl::removeHlaPhysicalEntityDefaultInstanceValueListener(HlaPhysicalEntityValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.remove(valueListener);
}

void HlaPhysicalEntityManagerImpl::setEnabled(bool enabled) {
    _optional = false;
    _enabled = enabled;
}

void HlaPhysicalEntityManagerImpl::setEnabledIfAvailableInFom() {
    _optional = true;
    _enabled = true;
}

bool HlaPhysicalEntityManagerImpl::isEnabled() {
    return _objectClassHandle.get() != NULL;
}

HlaPhysicalEntityImplPtr HlaPhysicalEntityManagerImpl::createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId) {
    return HlaPhysicalEntityImplPtr(new HlaPhysicalEntityImpl(_hlaWorld, this, objectInstanceHandle, isLocal, federateId));
}

void HlaPhysicalEntityManagerImpl::checkInitializedFired(HlaPhysicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (!instance->isInitializedFired() && instance->isInitialized()) {
        instance->setInitializedFired();
        fireInitialized(instance, timeStamp, logicalTime);
    }
}

void HlaPhysicalEntityManagerImpl::fireDiscovered(HlaPhysicalEntityPtr instance, HlaTimeStampPtr timeStamp) {
    std::set<HlaPhysicalEntityManagerListenerPtr> listeners = _physicalEntityManagerListeners.getListeners();
    for (std::set<HlaPhysicalEntityManagerListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPhysicalEntityManagerListener::hlaPhysicalEntityDiscovered, *it, instance, timeStamp);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPhysicalEntityManagerImpl::updateAttributeValues(HlaPhysicalEntityImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    _objectManager->updateAttributeValues(*objectInstanceHandle, attributes, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaPhysicalEntityManagerImpl::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) {
    InstanceMap::const_iterator iter;
    HlaPhysicalEntityImplPtr instance;
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

void HlaPhysicalEntityManagerImpl::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaPhysicalEntityManagerImpl::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaPhysicalEntityManagerImpl::save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) {
    if (_localInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save local instances");
    }
    if (_remoteInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save remote instances");
    }
}

void HlaPhysicalEntityManagerImpl::restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) {
    clearAllInstances(false);
}

