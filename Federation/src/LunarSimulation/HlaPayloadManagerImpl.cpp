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

#include "HlaPayloadManagerImpl.h"

#include <functional>

#include <LunarSimulation/HlaPayloadManagerListener.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaPayloadImpl.h"
#include "HlaWorldImpl.h"
#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"


using namespace LunarSimulation;
using namespace std;

static wchar_t HLA_OBJECT_CLASS_NAME[] = L"HLAobjectRoot.PhysicalEntity.DynamicalEntity.Payload";

HlaPayloadManagerImpl::HlaPayloadManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld)
:
_objectManager(objectManager),
_hlaWorld(hlaWorld),
_enabled(true),
_optional(false)
{
    _objectManager->addManager(this, wstring(HLA_OBJECT_CLASS_NAME));
}


bool HlaPayloadManagerImpl::isEnabled(const std::wstring& objectClassName) {
    return _enabled;
}

bool HlaPayloadManagerImpl::isOptional(const std::wstring& objectClassName) {
    return _optional;
}

void HlaPayloadManagerImpl::connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _objectClassHandle = ObjectClassHandlePtr(objectClassHandle.clone());
    RtiDriver::NameSet attributeNames = HlaPayloadImpl::getAttributes();
    _objectManager->publish(*_objectClassHandle, attributeNames);
    _objectManager->subscribe(*_objectClassHandle, attributeNames);
}
void HlaPayloadManagerImpl::clearAllInstances(bool doFireDeleted) {
    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    HlaPayloadImplPtr instance;

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

void HlaPayloadManagerImpl::disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) {
    _objectClassHandle.reset();
    clearAllInstances(true);
}

void HlaPayloadManagerImpl::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
    ObjectInstanceHandlePtr oihPtr(objectInstanceHandle.clone());
    HlaPayloadImplPtr instance = createObjectInstance(oihPtr, false, federateId);

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
        _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()]= instance;
        _remoteInstances[oihPtr] = instance;
    }

    fireDiscovered(instance, timeStamp);

    std::set<HlaPayloadListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaPayloadListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaPayloadListener(*it);
    }

    std::set<HlaPayloadValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaPayloadValueListener(*it);
    }
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    if (_hlaWorld->getTuning()->REQUEST) {
        struct MyRunner {
            static void run(HlaPayloadImplPtr instance,
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

void HlaPayloadManagerImpl::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    InstanceMap::const_iterator iter;
    HlaPayloadImplPtr instance;
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

void HlaPayloadManagerImpl::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaPayloadImplPtr instance;
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

void HlaPayloadManagerImpl::fireDeleted(HlaPayloadImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPayloadManagerListenerPtr> listeners = _payloadManagerListeners.getListeners();
    for (std::set<HlaPayloadManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
           std::function<void()> callback = std::bind(&HlaPayloadManagerListener::hlaPayloadDeleted, *iter, instance, timeStamp, logicalTime);
           _hlaWorld->postNotification(callback);
    }
}
void HlaPayloadManagerImpl::fireInitialized(HlaPayloadImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaPayloadManagerListenerPtr> listeners = _payloadManagerListeners.getListeners();
    for (std::set<HlaPayloadManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
        std::function<void()> callback = std::bind(&HlaPayloadManagerListener::hlaPayloadInitialized, *iter, instance, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

std::vector<HlaPayloadPtr> HlaPayloadManagerImpl::getHlaPayloads() {
    return getAllHlaPayloads();
}

std::vector<HlaPayloadPtr> HlaPayloadManagerImpl::getAllHlaPayloads() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPayloadPtr> res;
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

std::vector<HlaPayloadPtr> HlaPayloadManagerImpl::getLocalHlaPayloads() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPayloadPtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator iter = _localInstances.begin(); iter != _localInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

std::vector<HlaPayloadPtr> HlaPayloadManagerImpl::getRemoteHlaPayloads() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaPayloadPtr> res;
    res.reserve(_remoteInstances.size());
    for (InstanceMap::const_iterator iter = _remoteInstances.begin(); iter != _remoteInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

HlaPayloadPtr HlaPayloadManagerImpl::getPayloadByHlaInstanceName(const std::wstring& hlaInstanceName) {
    std::unique_lock<std::mutex> lock(_instancesLock);

    HlaInstanceNameMap::iterator i = _hlaInstanceNameMap.find(hlaInstanceName);
    if (i != _hlaInstanceNameMap.end()) {
        return i->second;
    }

    return HlaPayloadPtr();
}

HlaPayloadPtr HlaPayloadManagerImpl::getPayloadByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) {
    std::lock_guard<std::mutex> lock(_instancesLock);

    EncodedHlaInstanceHandleMap::iterator i = _encodedHlaInstanceHandleMap.find(encodedHlaInstanceHandle);
    if (i != _encodedHlaInstanceHandleMap.end()) {
        return i->second;
    }

    return HlaPayloadPtr();
}

HlaPayloadPtr HlaPayloadManagerImpl::createLocalHlaPayload(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return createLocalInstance(L""
        );
    } catch (HlaInstanceNameInUseException) {
        //can not happen with empty hlaInstanceName
        return HlaPayloadPtr();
    }
}

HlaPayloadPtr HlaPayloadManagerImpl::createLocalHlaPayload(const std::wstring& hlaInstanceName
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


HlaPayloadPtr HlaPayloadManagerImpl::createLocalInstance(
      const std::wstring& hlaInstanceName
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }
    HlaPayloadImplPtr instance;
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

    std::set<HlaPayloadListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaPayloadListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaPayloadListener(*it);
    }

    std::set<HlaPayloadValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaPayloadValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaPayloadValueListener(*it);
    }

    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    return instance;
}

HlaPayloadPtr HlaPayloadManagerImpl::deleteLocalHlaPayload(HlaPayloadPtr payload)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaPayload(payload, _hlaWorld->getCurrentTime(), _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaPayloadPtr HlaPayloadManagerImpl::deleteLocalHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaPayload(payload, timestamp, _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaPayloadPtr HlaPayloadManagerImpl::deleteLocalHlaPayload(HlaPayloadPtr payload, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaPayload(payload, _hlaWorld->getCurrentTime(), logicalTime, true);
}

HlaPayloadPtr HlaPayloadManagerImpl::deleteLocalHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaPayload(payload, timestamp, logicalTime, true);
}



HlaPayloadPtr HlaPayloadManagerImpl::deleteHlaPayload(HlaPayloadPtr payload, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime, bool checkLocal )
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (payload->isRemoved() || (checkLocal && !payload->isLocal())) {
        return HlaPayloadPtr();
    }

    ObjectInstanceHandlePtr instanceHandle = ((HlaPayloadImpl*)payload.get())->getObjectInstanceHandle();
    std::vector<char> encodedInstanceHandle =   ((HlaPayloadImpl*)payload.get())->getEncodedHlaObjectInstanceHandle();
    std::wstring instanceName = ((HlaPayloadImpl*)payload.get())->getHlaInstanceName();
    _objectManager->deleteObjectInstance(*instanceHandle, timestamp, logicalTime);

    HlaPayloadImplPtr payloadImpl;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        _hlaInstanceNameMap.erase(instanceName);
        _encodedHlaInstanceHandleMap.erase(encodedInstanceHandle);

        if (payload->isLocal()) {
            payloadImpl = _localInstances[instanceHandle];
            _localInstances.erase(instanceHandle);
        } else {
            payloadImpl = _remoteInstances[instanceHandle];
            _remoteInstances.erase(instanceHandle);
        }

    }

    payloadImpl->setRemoved();
    fireDeleted(payloadImpl, timestamp, logicalTime);
    return payload;
}

void HlaPayloadManagerImpl::addHlaPayloadManagerListener(HlaPayloadManagerListenerPtr managerListener) {
    _payloadManagerListeners.add(managerListener);
}

void HlaPayloadManagerImpl::removeHlaPayloadManagerListener(HlaPayloadManagerListenerPtr managerListener) {
    _payloadManagerListeners.remove(managerListener);
}

void HlaPayloadManagerImpl::addHlaPayloadDefaultInstanceListener(HlaPayloadListenerPtr listener) {
   _defaultInstanceListeners.add(listener);
}

void HlaPayloadManagerImpl::addHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.add(valueListener);
}

void HlaPayloadManagerImpl::removeHlaPayloadDefaultInstanceListener(HlaPayloadListenerPtr listener) {
   _defaultInstanceListeners.remove(listener);
}

void HlaPayloadManagerImpl::removeHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.remove(valueListener);
}

void HlaPayloadManagerImpl::setEnabled(bool enabled) {
    _optional = false;
    _enabled = enabled;
}

void HlaPayloadManagerImpl::setEnabledIfAvailableInFom() {
    _optional = true;
    _enabled = true;
}

bool HlaPayloadManagerImpl::isEnabled() {
    return _objectClassHandle.get() != NULL;
}

HlaPayloadImplPtr HlaPayloadManagerImpl::createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId) {
    return HlaPayloadImplPtr(new HlaPayloadImpl(_hlaWorld, this, objectInstanceHandle, isLocal, federateId));
}

void HlaPayloadManagerImpl::checkInitializedFired(HlaPayloadImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (!instance->isInitializedFired() && instance->isInitialized()) {
        instance->setInitializedFired();
        fireInitialized(instance, timeStamp, logicalTime);
    }
}

void HlaPayloadManagerImpl::fireDiscovered(HlaPayloadPtr instance, HlaTimeStampPtr timeStamp) {
    std::set<HlaPayloadManagerListenerPtr> listeners = _payloadManagerListeners.getListeners();
    for (std::set<HlaPayloadManagerListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaPayloadManagerListener::hlaPayloadDiscovered, *it, instance, timeStamp);
        _hlaWorld->postNotification(callback);
    }
}

void HlaPayloadManagerImpl::updateAttributeValues(HlaPayloadImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    _objectManager->updateAttributeValues(*objectInstanceHandle, attributes, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaPayloadManagerImpl::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) {
    InstanceMap::const_iterator iter;
    HlaPayloadImplPtr instance;
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

void HlaPayloadManagerImpl::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaPayloadManagerImpl::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaPayloadManagerImpl::save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) {
    if (_localInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save local instances");
    }
    if (_remoteInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save remote instances");
    }
}

void HlaPayloadManagerImpl::restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) {
    clearAllInstances(false);
}

