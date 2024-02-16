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

#include "HlaDynamicalEntityManagerImpl.h"

#include <functional>

#include <LunarSimulation/HlaDynamicalEntityManagerListener.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaDynamicalEntityImpl.h"
#include "HlaWorldImpl.h"
#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"


using namespace LunarSimulation;
using namespace std;

static wchar_t HLA_OBJECT_CLASS_NAME[] = L"HLAobjectRoot.PhysicalEntity.DynamicalEntity";

HlaDynamicalEntityManagerImpl::HlaDynamicalEntityManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld)
:
_objectManager(objectManager),
_hlaWorld(hlaWorld),
_enabled(true),
_optional(false)
{
    _objectManager->addManager(this, wstring(HLA_OBJECT_CLASS_NAME));
}


bool HlaDynamicalEntityManagerImpl::isEnabled(const std::wstring& objectClassName) {
    return _enabled;
}

bool HlaDynamicalEntityManagerImpl::isOptional(const std::wstring& objectClassName) {
    return _optional;
}

void HlaDynamicalEntityManagerImpl::connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _objectClassHandle = ObjectClassHandlePtr(objectClassHandle.clone());
    RtiDriver::NameSet attributeNames = HlaDynamicalEntityImpl::getAttributes();
    _objectManager->publish(*_objectClassHandle, attributeNames);
    _objectManager->subscribe(*_objectClassHandle, attributeNames);
}
void HlaDynamicalEntityManagerImpl::clearAllInstances(bool doFireDeleted) {
    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    HlaDynamicalEntityImplPtr instance;

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

void HlaDynamicalEntityManagerImpl::disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) {
    _objectClassHandle.reset();
    clearAllInstances(true);
}

void HlaDynamicalEntityManagerImpl::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
    ObjectInstanceHandlePtr oihPtr(objectInstanceHandle.clone());
    HlaDynamicalEntityImplPtr instance = createObjectInstance(oihPtr, false, federateId);

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
        _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()]= instance;
        _remoteInstances[oihPtr] = instance;
    }

    fireDiscovered(instance, timeStamp);

    std::set<HlaDynamicalEntityListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaDynamicalEntityListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaDynamicalEntityListener(*it);
    }

    std::set<HlaDynamicalEntityValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaDynamicalEntityValueListener(*it);
    }
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    if (_hlaWorld->getTuning()->REQUEST) {
        struct MyRunner {
            static void run(HlaDynamicalEntityImplPtr instance,
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

void HlaDynamicalEntityManagerImpl::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    InstanceMap::const_iterator iter;
    HlaDynamicalEntityImplPtr instance;
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

void HlaDynamicalEntityManagerImpl::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaDynamicalEntityImplPtr instance;
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

void HlaDynamicalEntityManagerImpl::fireDeleted(HlaDynamicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaDynamicalEntityManagerListenerPtr> listeners = _dynamicalEntityManagerListeners.getListeners();
    for (std::set<HlaDynamicalEntityManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
           std::function<void()> callback = std::bind(&HlaDynamicalEntityManagerListener::hlaDynamicalEntityDeleted, *iter, instance, timeStamp, logicalTime);
           _hlaWorld->postNotification(callback);
    }
}
void HlaDynamicalEntityManagerImpl::fireInitialized(HlaDynamicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaDynamicalEntityManagerListenerPtr> listeners = _dynamicalEntityManagerListeners.getListeners();
    for (std::set<HlaDynamicalEntityManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityManagerListener::hlaDynamicalEntityInitialized, *iter, instance, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

std::vector<HlaDynamicalEntityPtr> HlaDynamicalEntityManagerImpl::getHlaDynamicalEntitys() {
    return getAllHlaDynamicalEntitys();
}

std::vector<HlaDynamicalEntityPtr> HlaDynamicalEntityManagerImpl::getAllHlaDynamicalEntitys() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaDynamicalEntityPtr> res;
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

std::vector<HlaDynamicalEntityPtr> HlaDynamicalEntityManagerImpl::getLocalHlaDynamicalEntitys() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaDynamicalEntityPtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator iter = _localInstances.begin(); iter != _localInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

std::vector<HlaDynamicalEntityPtr> HlaDynamicalEntityManagerImpl::getRemoteHlaDynamicalEntitys() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaDynamicalEntityPtr> res;
    res.reserve(_remoteInstances.size());
    for (InstanceMap::const_iterator iter = _remoteInstances.begin(); iter != _remoteInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::getDynamicalEntityByHlaInstanceName(const std::wstring& hlaInstanceName) {
    std::unique_lock<std::mutex> lock(_instancesLock);

    HlaInstanceNameMap::iterator i = _hlaInstanceNameMap.find(hlaInstanceName);
    if (i != _hlaInstanceNameMap.end()) {
        return i->second;
    }

    return HlaDynamicalEntityPtr();
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::getDynamicalEntityByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) {
    std::lock_guard<std::mutex> lock(_instancesLock);

    EncodedHlaInstanceHandleMap::iterator i = _encodedHlaInstanceHandleMap.find(encodedHlaInstanceHandle);
    if (i != _encodedHlaInstanceHandleMap.end()) {
        return i->second;
    }

    return HlaDynamicalEntityPtr();
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::createLocalHlaDynamicalEntity(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return createLocalInstance(L""
        );
    } catch (HlaInstanceNameInUseException) {
        //can not happen with empty hlaInstanceName
        return HlaDynamicalEntityPtr();
    }
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::createLocalHlaDynamicalEntity(const std::wstring& hlaInstanceName
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


HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::createLocalInstance(
      const std::wstring& hlaInstanceName
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }
    HlaDynamicalEntityImplPtr instance;
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

    std::set<HlaDynamicalEntityListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaDynamicalEntityListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaDynamicalEntityListener(*it);
    }

    std::set<HlaDynamicalEntityValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaDynamicalEntityValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaDynamicalEntityValueListener(*it);
    }

    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    return instance;
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaDynamicalEntity(dynamicalEntity, _hlaWorld->getCurrentTime(), _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaDynamicalEntity(dynamicalEntity, timestamp, _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaDynamicalEntity(dynamicalEntity, _hlaWorld->getCurrentTime(), logicalTime, true);
}

HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::deleteLocalHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaDynamicalEntity(dynamicalEntity, timestamp, logicalTime, true);
}



HlaDynamicalEntityPtr HlaDynamicalEntityManagerImpl::deleteHlaDynamicalEntity(HlaDynamicalEntityPtr dynamicalEntity, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime, bool checkLocal )
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (dynamicalEntity->isRemoved() || (checkLocal && !dynamicalEntity->isLocal())) {
        return HlaDynamicalEntityPtr();
    }

    ObjectInstanceHandlePtr instanceHandle = ((HlaDynamicalEntityImpl*)dynamicalEntity.get())->getObjectInstanceHandle();
    std::vector<char> encodedInstanceHandle =   ((HlaDynamicalEntityImpl*)dynamicalEntity.get())->getEncodedHlaObjectInstanceHandle();
    std::wstring instanceName = ((HlaDynamicalEntityImpl*)dynamicalEntity.get())->getHlaInstanceName();
    _objectManager->deleteObjectInstance(*instanceHandle, timestamp, logicalTime);

    HlaDynamicalEntityImplPtr dynamicalEntityImpl;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        _hlaInstanceNameMap.erase(instanceName);
        _encodedHlaInstanceHandleMap.erase(encodedInstanceHandle);

        if (dynamicalEntity->isLocal()) {
            dynamicalEntityImpl = _localInstances[instanceHandle];
            _localInstances.erase(instanceHandle);
        } else {
            dynamicalEntityImpl = _remoteInstances[instanceHandle];
            _remoteInstances.erase(instanceHandle);
        }

    }

    dynamicalEntityImpl->setRemoved();
    fireDeleted(dynamicalEntityImpl, timestamp, logicalTime);
    return dynamicalEntity;
}

void HlaDynamicalEntityManagerImpl::addHlaDynamicalEntityManagerListener(HlaDynamicalEntityManagerListenerPtr managerListener) {
    _dynamicalEntityManagerListeners.add(managerListener);
}

void HlaDynamicalEntityManagerImpl::removeHlaDynamicalEntityManagerListener(HlaDynamicalEntityManagerListenerPtr managerListener) {
    _dynamicalEntityManagerListeners.remove(managerListener);
}

void HlaDynamicalEntityManagerImpl::addHlaDynamicalEntityDefaultInstanceListener(HlaDynamicalEntityListenerPtr listener) {
   _defaultInstanceListeners.add(listener);
}

void HlaDynamicalEntityManagerImpl::addHlaDynamicalEntityDefaultInstanceValueListener(HlaDynamicalEntityValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.add(valueListener);
}

void HlaDynamicalEntityManagerImpl::removeHlaDynamicalEntityDefaultInstanceListener(HlaDynamicalEntityListenerPtr listener) {
   _defaultInstanceListeners.remove(listener);
}

void HlaDynamicalEntityManagerImpl::removeHlaDynamicalEntityDefaultInstanceValueListener(HlaDynamicalEntityValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.remove(valueListener);
}

void HlaDynamicalEntityManagerImpl::setEnabled(bool enabled) {
    _optional = false;
    _enabled = enabled;
}

void HlaDynamicalEntityManagerImpl::setEnabledIfAvailableInFom() {
    _optional = true;
    _enabled = true;
}

bool HlaDynamicalEntityManagerImpl::isEnabled() {
    return _objectClassHandle.get() != NULL;
}

HlaDynamicalEntityImplPtr HlaDynamicalEntityManagerImpl::createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId) {
    return HlaDynamicalEntityImplPtr(new HlaDynamicalEntityImpl(_hlaWorld, this, objectInstanceHandle, isLocal, federateId));
}

void HlaDynamicalEntityManagerImpl::checkInitializedFired(HlaDynamicalEntityImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (!instance->isInitializedFired() && instance->isInitialized()) {
        instance->setInitializedFired();
        fireInitialized(instance, timeStamp, logicalTime);
    }
}

void HlaDynamicalEntityManagerImpl::fireDiscovered(HlaDynamicalEntityPtr instance, HlaTimeStampPtr timeStamp) {
    std::set<HlaDynamicalEntityManagerListenerPtr> listeners = _dynamicalEntityManagerListeners.getListeners();
    for (std::set<HlaDynamicalEntityManagerListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaDynamicalEntityManagerListener::hlaDynamicalEntityDiscovered, *it, instance, timeStamp);
        _hlaWorld->postNotification(callback);
    }
}

void HlaDynamicalEntityManagerImpl::updateAttributeValues(HlaDynamicalEntityImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    _objectManager->updateAttributeValues(*objectInstanceHandle, attributes, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaDynamicalEntityManagerImpl::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) {
    InstanceMap::const_iterator iter;
    HlaDynamicalEntityImplPtr instance;
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

void HlaDynamicalEntityManagerImpl::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaDynamicalEntityManagerImpl::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaDynamicalEntityManagerImpl::save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) {
    if (_localInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save local instances");
    }
    if (_remoteInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save remote instances");
    }
}

void HlaDynamicalEntityManagerImpl::restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) {
    clearAllInstances(false);
}

