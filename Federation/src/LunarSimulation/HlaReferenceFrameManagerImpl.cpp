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

#include "HlaReferenceFrameManagerImpl.h"

#include <functional>

#include <LunarSimulation/HlaReferenceFrameManagerListener.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaReferenceFrameImpl.h"
#include "HlaWorldImpl.h"
#include "ObjectManager.h"
#include "HlaLogicalTimeImpl.h"


using namespace LunarSimulation;
using namespace std;

static wchar_t HLA_OBJECT_CLASS_NAME[] = L"HLAobjectRoot.ReferenceFrame";

HlaReferenceFrameManagerImpl::HlaReferenceFrameManagerImpl(ObjectManager *objectManager, HlaWorldImpl* hlaWorld)
:
_objectManager(objectManager),
_hlaWorld(hlaWorld),
_enabled(true),
_optional(false)
{
    _objectManager->addManager(this, wstring(HLA_OBJECT_CLASS_NAME));
}


bool HlaReferenceFrameManagerImpl::isEnabled(const std::wstring& objectClassName) {
    return _enabled;
}

bool HlaReferenceFrameManagerImpl::isOptional(const std::wstring& objectClassName) {
    return _optional;
}

void HlaReferenceFrameManagerImpl::connected(const RtiDriver::ObjectClassHandle& objectClassHandle, const std::wstring& objectClassName)
THROW_SPEC (HlaFomException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    _objectClassHandle = ObjectClassHandlePtr(objectClassHandle.clone());
    RtiDriver::NameSet attributeNames = HlaReferenceFrameImpl::getAttributes();
    _objectManager->publish(*_objectClassHandle, attributeNames);
    _objectManager->subscribe(*_objectClassHandle, attributeNames);
}
void HlaReferenceFrameManagerImpl::clearAllInstances(bool doFireDeleted) {
    HlaTimeStampPtr timeStamp = _hlaWorld->getCurrentTime();
    HlaReferenceFrameImplPtr instance;

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

void HlaReferenceFrameManagerImpl::disconnected(const RtiDriver::ObjectClassHandle& objectClassHandle) {
    _objectClassHandle.reset();
    clearAllInstances(true);
}

void HlaReferenceFrameManagerImpl::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
    ObjectInstanceHandlePtr oihPtr(objectInstanceHandle.clone());
    HlaReferenceFrameImplPtr instance = createObjectInstance(oihPtr, false, federateId);

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);
        _hlaInstanceNameMap[instance->getHlaInstanceName()] = instance;
        _encodedHlaInstanceHandleMap[instance->getEncodedHlaObjectInstanceHandle()]= instance;
        _remoteInstances[oihPtr] = instance;
    }

    fireDiscovered(instance, timeStamp);

    std::set<HlaReferenceFrameListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaReferenceFrameListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaReferenceFrameListener(*it);
    }

    std::set<HlaReferenceFrameValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaReferenceFrameValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaReferenceFrameValueListener(*it);
    }
    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    if (_hlaWorld->getTuning()->REQUEST) {
        struct MyRunner {
            static void run(HlaReferenceFrameImplPtr instance,
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

void HlaReferenceFrameManagerImpl::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    InstanceMap::const_iterator iter;
    HlaReferenceFrameImplPtr instance;
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

void HlaReferenceFrameManagerImpl::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaReferenceFrameImplPtr instance;
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

void HlaReferenceFrameManagerImpl::fireDeleted(HlaReferenceFrameImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaReferenceFrameManagerListenerPtr> listeners = _referenceFrameManagerListeners.getListeners();
    for (std::set<HlaReferenceFrameManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
           std::function<void()> callback = std::bind(&HlaReferenceFrameManagerListener::hlaReferenceFrameDeleted, *iter, instance, timeStamp, logicalTime);
           _hlaWorld->postNotification(callback);
    }
}
void HlaReferenceFrameManagerImpl::fireInitialized(HlaReferenceFrameImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaReferenceFrameManagerListenerPtr> listeners = _referenceFrameManagerListeners.getListeners();
    for (std::set<HlaReferenceFrameManagerListenerPtr>::iterator iter = listeners.begin(); iter != listeners.end(); iter++) {
        std::function<void()> callback = std::bind(&HlaReferenceFrameManagerListener::hlaReferenceFrameInitialized, *iter, instance, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}

std::vector<HlaReferenceFramePtr> HlaReferenceFrameManagerImpl::getHlaReferenceFrames() {
    return getAllHlaReferenceFrames();
}

std::vector<HlaReferenceFramePtr> HlaReferenceFrameManagerImpl::getAllHlaReferenceFrames() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaReferenceFramePtr> res;
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

std::vector<HlaReferenceFramePtr> HlaReferenceFrameManagerImpl::getLocalHlaReferenceFrames() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaReferenceFramePtr> res;
    res.reserve(_localInstances.size());
    for (InstanceMap::const_iterator iter = _localInstances.begin(); iter != _localInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

std::vector<HlaReferenceFramePtr> HlaReferenceFrameManagerImpl::getRemoteHlaReferenceFrames() {
    std::lock_guard<std::mutex> lock(_instancesLock);
    std::vector<HlaReferenceFramePtr> res;
    res.reserve(_remoteInstances.size());
    for (InstanceMap::const_iterator iter = _remoteInstances.begin(); iter != _remoteInstances.end(); ++iter) {
            res.push_back(iter->second);
    }
    return res;
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::getReferenceFrameByHlaInstanceName(const std::wstring& hlaInstanceName) {
    std::unique_lock<std::mutex> lock(_instancesLock);

    HlaInstanceNameMap::iterator i = _hlaInstanceNameMap.find(hlaInstanceName);
    if (i != _hlaInstanceNameMap.end()) {
        return i->second;
    }

    return HlaReferenceFramePtr();
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::getReferenceFrameByHlaInstanceHandle(const std::vector<char>& encodedHlaInstanceHandle) {
    std::lock_guard<std::mutex> lock(_instancesLock);

    EncodedHlaInstanceHandleMap::iterator i = _encodedHlaInstanceHandleMap.find(encodedHlaInstanceHandle);
    if (i != _encodedHlaInstanceHandleMap.end()) {
        return i->second;
    }

    return HlaReferenceFramePtr();
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::createLocalHlaReferenceFrame(
      ) THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return createLocalInstance(L""
        );
    } catch (HlaInstanceNameInUseException) {
        //can not happen with empty hlaInstanceName
        return HlaReferenceFramePtr();
    }
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::createLocalHlaReferenceFrame(const std::wstring& hlaInstanceName
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


HlaReferenceFramePtr HlaReferenceFrameManagerImpl::createLocalInstance(
      const std::wstring& hlaInstanceName
   ) THROW_SPEC (HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
                 HlaNotConnectedException, HlaInternalException, HlaRtiException,
                 HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!_objectClassHandle) {
        throw HlaNotConnectedException(L"Not connected");
    }
    HlaReferenceFrameImplPtr instance;
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

    std::set<HlaReferenceFrameListenerPtr> listenersSet = _defaultInstanceListeners.getListeners();
    for (std::set<HlaReferenceFrameListenerPtr>::iterator it = listenersSet.begin(); it != listenersSet.end(); ++it) {
       instance->addHlaReferenceFrameListener(*it);
    }

    std::set<HlaReferenceFrameValueListenerPtr> valueListenersSet = _defaultInstanceValueListeners.getListeners();
    for (std::set<HlaReferenceFrameValueListenerPtr>::iterator it = valueListenersSet.begin(); it != valueListenersSet.end(); ++it) {
       instance->addHlaReferenceFrameValueListener(*it);
    }

    checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl::getInvalid());

    return instance;
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaReferenceFrame(referenceFrame, _hlaWorld->getCurrentTime(), _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    try {
        return deleteHlaReferenceFrame(referenceFrame, timestamp, _hlaWorld->getDefaultSendTime(), true);
    } catch (HlaInvalidLogicalTimeException& e) {
        throw HlaInternalException(L"Failed to delete instance with default Logical Time: " + e.what_w());
    }
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaReferenceFrame(referenceFrame, _hlaWorld->getCurrentTime(), logicalTime, true);
}

HlaReferenceFramePtr HlaReferenceFrameManagerImpl::deleteLocalHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    return deleteHlaReferenceFrame(referenceFrame, timestamp, logicalTime, true);
}



HlaReferenceFramePtr HlaReferenceFrameManagerImpl::deleteHlaReferenceFrame(HlaReferenceFramePtr referenceFrame, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime, bool checkLocal )
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    if (referenceFrame->isRemoved() || (checkLocal && !referenceFrame->isLocal())) {
        return HlaReferenceFramePtr();
    }

    ObjectInstanceHandlePtr instanceHandle = ((HlaReferenceFrameImpl*)referenceFrame.get())->getObjectInstanceHandle();
    std::vector<char> encodedInstanceHandle =   ((HlaReferenceFrameImpl*)referenceFrame.get())->getEncodedHlaObjectInstanceHandle();
    std::wstring instanceName = ((HlaReferenceFrameImpl*)referenceFrame.get())->getHlaInstanceName();
    _objectManager->deleteObjectInstance(*instanceHandle, timestamp, logicalTime);

    HlaReferenceFrameImplPtr referenceFrameImpl;

    {
        std::lock_guard<std::mutex> instanceLock(_instancesLock);

        _hlaInstanceNameMap.erase(instanceName);
        _encodedHlaInstanceHandleMap.erase(encodedInstanceHandle);

        if (referenceFrame->isLocal()) {
            referenceFrameImpl = _localInstances[instanceHandle];
            _localInstances.erase(instanceHandle);
        } else {
            referenceFrameImpl = _remoteInstances[instanceHandle];
            _remoteInstances.erase(instanceHandle);
        }

    }

    referenceFrameImpl->setRemoved();
    fireDeleted(referenceFrameImpl, timestamp, logicalTime);
    return referenceFrame;
}

void HlaReferenceFrameManagerImpl::addHlaReferenceFrameManagerListener(HlaReferenceFrameManagerListenerPtr managerListener) {
    _referenceFrameManagerListeners.add(managerListener);
}

void HlaReferenceFrameManagerImpl::removeHlaReferenceFrameManagerListener(HlaReferenceFrameManagerListenerPtr managerListener) {
    _referenceFrameManagerListeners.remove(managerListener);
}

void HlaReferenceFrameManagerImpl::addHlaReferenceFrameDefaultInstanceListener(HlaReferenceFrameListenerPtr listener) {
   _defaultInstanceListeners.add(listener);
}

void HlaReferenceFrameManagerImpl::addHlaReferenceFrameDefaultInstanceValueListener(HlaReferenceFrameValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.add(valueListener);
}

void HlaReferenceFrameManagerImpl::removeHlaReferenceFrameDefaultInstanceListener(HlaReferenceFrameListenerPtr listener) {
   _defaultInstanceListeners.remove(listener);
}

void HlaReferenceFrameManagerImpl::removeHlaReferenceFrameDefaultInstanceValueListener(HlaReferenceFrameValueListenerPtr valueListener) {
   _defaultInstanceValueListeners.remove(valueListener);
}

void HlaReferenceFrameManagerImpl::setEnabled(bool enabled) {
    _optional = false;
    _enabled = enabled;
}

void HlaReferenceFrameManagerImpl::setEnabledIfAvailableInFom() {
    _optional = true;
    _enabled = true;
}

bool HlaReferenceFrameManagerImpl::isEnabled() {
    return _objectClassHandle.get() != NULL;
}

HlaReferenceFrameImplPtr HlaReferenceFrameManagerImpl::createObjectInstance(ObjectInstanceHandlePtr objectInstanceHandle, bool isLocal, const HlaFederateIdImplPtr federateId) {
    return HlaReferenceFrameImplPtr(new HlaReferenceFrameImpl(_hlaWorld, this, objectInstanceHandle, isLocal, federateId));
}

void HlaReferenceFrameManagerImpl::checkInitializedFired(HlaReferenceFrameImplPtr instance, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    if (!instance->isInitializedFired() && instance->isInitialized()) {
        instance->setInitializedFired();
        fireInitialized(instance, timeStamp, logicalTime);
    }
}

void HlaReferenceFrameManagerImpl::fireDiscovered(HlaReferenceFramePtr instance, HlaTimeStampPtr timeStamp) {
    std::set<HlaReferenceFrameManagerListenerPtr> listeners = _referenceFrameManagerListeners.getListeners();
    for (std::set<HlaReferenceFrameManagerListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaReferenceFrameManagerListener::hlaReferenceFrameDiscovered, *it, instance, timeStamp);
        _hlaWorld->postNotification(callback);
    }
}

void HlaReferenceFrameManagerImpl::updateAttributeValues(HlaReferenceFrameImplPtr instance, ObjectInstanceHandlePtr objectInstanceHandle, const RtiDriver::NameValueMap& attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    _objectManager->updateAttributeValues(*objectInstanceHandle, attributes, timeStamp, logicalTime);
    checkInitializedFired(instance, timeStamp, logicalTime);
}

void HlaReferenceFrameManagerImpl::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes, HlaTimeStampPtr timeStamp) {
    InstanceMap::const_iterator iter;
    HlaReferenceFrameImplPtr instance;
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

void HlaReferenceFrameManagerImpl::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaReferenceFrameManagerImpl::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const std::set<std::wstring>& attributes) {}

void HlaReferenceFrameManagerImpl::save(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaSaveFederateException) {
    if (_localInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save local instances");
    }
    if (_remoteInstances.size() != 0) {
        throw HlaSaveFederateException(L"Unable to save remote instances");
    }
}

void HlaReferenceFrameManagerImpl::restore(const RtiDriver::ObjectClassHandle& objectClassHandle) THROW_SPEC(HlaRestoreFederateException) {
    clearAllInstances(false);
}

