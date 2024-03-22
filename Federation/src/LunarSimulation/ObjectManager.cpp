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

#include <algorithm>

#include "ObjectManager.h"


#include "AbstractObjectClassManager.h"
#include "HlaWorldImpl.h"
#include "FederateManager.h"

using namespace LunarSimulation;
using namespace std;

ObjectManager::ObjectManager(HlaWorldImpl* hlaWorld, FederateManager* federateManager)
: _federateManager(federateManager),
  _hlaWorld(hlaWorld) {}

AbstractObjectClassManager* ObjectManager::getObjectClassManager(const ObjectClassHandlePtr& objectClassHandle) {
   std::lock_guard<std::mutex> lock(_objectClassManagersLock);
   ObjectClassManagers::iterator classManagerIterator = _objectClassManagers.find(objectClassHandle);
   if (classManagerIterator != _objectClassManagers.end()) {
      return classManagerIterator->second;
   }
   return NULL;
}

 ObjectManager::ObjectClassManagers ObjectManager::copyObjectClassManagers() {
   std::lock_guard<std::mutex> lock(_objectClassManagersLock);
   return _objectClassManagers; // Return a copy
}

void ObjectManager::disconnect() {
   // Copy the ObjectClassManagers map so that we can thread safely iterate over it without letting the lock escape out into the object class manager's disconnected call
   ObjectClassManagers objectClassManagersCopy = copyObjectClassManagers();
   for (ObjectClassManagers::iterator it = objectClassManagersCopy.begin(); it != objectClassManagersCopy.end(); it++) {
      AbstractObjectClassManager* objectClassManager = it->second;
      ObjectClassHandlePtr objectClassHandle = it->first;
      objectClassManager->disconnected(*objectClassHandle);
   }
}

void ObjectManager::addManager(AbstractObjectClassManager* manager, const wstring& className) {
   _wannabeManagers.push_back(pair<wstring, AbstractObjectClassManager*>(className, manager));
}

static bool compareStrings(const std::pair<std::wstring, AbstractObjectClassManager*>& p1, const std::pair<std::wstring, AbstractObjectClassManager*>& p2) {
   return p1.first.length() > p2.first.length();
}

void ObjectManager::connected() THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaRtiException, HlaInternalException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   std::sort(_wannabeManagers.begin(), _wannabeManagers.end(), compareStrings);
   for (WannabeManagerList::iterator iter = _wannabeManagers.begin(); iter != _wannabeManagers.end(); ++iter) {
      AbstractObjectClassManager * objectClassManager = iter->second;
      wstring objectClassName = iter->first;
      if (objectClassManager->isEnabled(objectClassName)) {
         try {
            ObjectClassHandlePtr handle = _federateManager->getObjectClassHandle(objectClassName);
            {
               std::lock_guard<std::mutex> lock(_objectClassManagersLock);
               _objectClassManagers[handle] = objectClassManager;
            }
            objectClassManager->connected(*handle,objectClassName);
         } catch (HlaFomException&) {
            if (!objectClassManager->isOptional(objectClassName)) {
               throw;
            }
         }
      }
   }
}

void ObjectManager::subscribe(const RtiDriver::ObjectClassHandle& objectClassHandle, const set<wstring>& attributeNames)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _federateManager->subscribeObjectClassAttributes(objectClassHandle, attributeNames);
}

void ObjectManager::subscribe(const RtiDriver::ObjectClassHandle& objectClassHandle, const set<wstring>& attributeNames, const RegionSetPtr& newRegion, const RegionSetPtr& oldRegion)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _federateManager->subscribeObjectClassAttributes(objectClassHandle, attributeNames, newRegion, oldRegion);
}

void ObjectManager::publish(const RtiDriver::ObjectClassHandle& objectClassHandle, const set<wstring>& attributeNames)
THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _federateManager->publishObjectClassAttributes(objectClassHandle, attributeNames);
}

bool ObjectManager::registerObjectInstanceName(const std::wstring& instanceName)
THROW_SPEC (HlaNotConnectedException, HlaIllegalInstanceNameException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
    std::unique_lock<std::mutex> lock(_registerNameInProgressLock);
    return _federateManager->registerObjectInstanceName(instanceName);
}

ObjectInstanceHandlePtr ObjectManager::createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const wstring& instanceName)
THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   return _federateManager->createObjectInstance(objectClassHandle, instanceName);
}

ObjectInstanceHandlePtr ObjectManager::createObjectInstance(const RtiDriver::ObjectClassHandle& objectClassHandle, const wstring& instanceName, const set<wstring>& attributeNames, const RtiDriver::Region& region)
THROW_SPEC (HlaInstanceNameInUseException, HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   return _federateManager->createObjectInstance(objectClassHandle, instanceName, attributeNames, region);
}

void ObjectManager::discoverObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                           const wstring& instanceName, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp) {
   std::shared_ptr<RtiDriver::ObjectClassHandle> objectClassHandle(objectInstanceHandle.getObjectClassHandle());
   AbstractObjectClassManager* classManager = getObjectClassManager(objectClassHandle);
   if (classManager != NULL) {
      classManager->discoverObjectInstance(objectInstanceHandle, instanceName, federateId, timeStamp);
   } else {
       HlaExceptionPtr ex(new HlaInternalException(L"Failed to find object class manger: " + (const std::wstring &)*objectInstanceHandle.getObjectClassHandle()));
      _hlaWorld->postException(ex);
   }
}

void ObjectManager::removeObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
   std::shared_ptr<RtiDriver::ObjectClassHandle> objectClassHandle(objectInstanceHandle.getObjectClassHandle());
   AbstractObjectClassManager* classManager = getObjectClassManager(objectClassHandle);
   if (classManager != NULL) {
      classManager->removeObjectInstance(objectInstanceHandle, timeStamp,logicalTime);
   }
}

void ObjectManager::reflectAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                           const RtiDriver::NameValueMap& attributes,
                                           const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
   std::shared_ptr<RtiDriver::ObjectClassHandle> objectClassHandle(objectInstanceHandle.getObjectClassHandle());
   AbstractObjectClassManager* classManager = getObjectClassManager(objectClassHandle);
   if (classManager != NULL) {
      classManager->reflectAttributeValues(objectInstanceHandle, attributes, federateId, timeStamp, logicalTime);
   } else {
       HlaExceptionPtr ex(new HlaInternalException(L"Failed to find object class manger: " + (const std::wstring &)*objectInstanceHandle.getObjectClassHandle()));
      _hlaWorld->postException(ex);
   }
}

void ObjectManager::attributesInScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const set<wstring>& attributes) {
   std::shared_ptr<RtiDriver::ObjectClassHandle> objectClassHandle(objectInstanceHandle.getObjectClassHandle());
   AbstractObjectClassManager* classManager = getObjectClassManager(objectClassHandle);
   if (classManager != NULL) {
      classManager->attributesInScope(objectInstanceHandle, attributes);
   } else {
      HlaExceptionPtr ex(new HlaInternalException(L"Failed to find object class manger: " + (const std::wstring &)*objectInstanceHandle.getObjectClassHandle()));
      _hlaWorld->postException(ex);
   }
}

void ObjectManager::attributesOutOfScope(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const set<wstring>& attributes) {
   std::shared_ptr<RtiDriver::ObjectClassHandle> objectClassHandle(objectInstanceHandle.getObjectClassHandle());
   AbstractObjectClassManager* classManager = getObjectClassManager(objectClassHandle);
   if (classManager != NULL) {
      classManager->attributesOutOfScope(objectInstanceHandle, attributes);
   } else {
      HlaExceptionPtr ex(new HlaInternalException(L"Failed to find object class manger: " + (const std::wstring &)*objectInstanceHandle.getObjectClassHandle()));
      _hlaWorld->postException(ex);
   }
}

void ObjectManager::updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes,
                                          HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _federateManager->updateAttributeValues(objectInstanceHandle, attributes, timeStamp, logicalTime);
}

void ObjectManager::updateAttributeValues(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameValueMap& attributes,
                                          HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime, const set<wstring>& attributeNames, const RtiDriver::Region& newRegion, const RtiDriver::Region& oldRegion)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _federateManager->updateAttributeValues(objectInstanceHandle, attributes, timeStamp, logicalTime, attributeNames, newRegion, oldRegion);
}

void ObjectManager::deleteObjectInstance(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _federateManager->deleteObjectInstance(objectInstanceHandle, timeStamp,logicalTime);
}

void ObjectManager::provideAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle,
                                                const std::set<std::wstring>& attributes, HlaTimeStampPtr hlaTimeStamp) {
   std::shared_ptr<RtiDriver::ObjectClassHandle> objectClassHandle(objectInstanceHandle.getObjectClassHandle());
   AbstractObjectClassManager* classManager = getObjectClassManager(objectClassHandle);
   // classManager may be missing since provideAttributeValueUpdate is called on a separate thread
   if (classManager != NULL) {
      classManager->provideAttributeValueUpdate(objectInstanceHandle, attributes, hlaTimeStamp);
   }
}

void ObjectManager::requestAttributeValueUpdate(const RtiDriver::ObjectInstanceHandle& objectInstanceHandle, const RtiDriver::NameSet& hlaAttributeNames,
                                                HlaTimeStampPtr currentTime)
THROW_SPEC(HlaInternalException, HlaRtiException, HlaNotConnectedException, HlaSaveInProgressException, HlaRestoreInProgressException) {
   _federateManager->requestAttributeValueUpdate(objectInstanceHandle, hlaAttributeNames, currentTime);
}

void ObjectManager::save() THROW_SPEC(HlaSaveFederateException) {
   // Copy the ObjectClassManagers map so that we can thread safely iterate over it without letting the lock escape out into the object class manager's save call
   ObjectClassManagers objectClassManagersCopy = copyObjectClassManagers();
   for (ObjectClassManagers::iterator it = objectClassManagersCopy.begin(); it != objectClassManagersCopy.end(); it++) {
      AbstractObjectClassManager* objectClassManager = it->second;
      ObjectClassHandlePtr objectClassHandle = it->first;
      objectClassManager->save(*objectClassHandle);
   }
}

void ObjectManager::restore() THROW_SPEC(HlaRestoreFederateException) {
   // Copy the ObjectClassManagers map so that we can thread safely iterate over it without letting the lock escape out into the object class manager's restore call
   ObjectClassManagers objectClassManagersCopy = copyObjectClassManagers();
   for (ObjectClassManagers::iterator it = objectClassManagersCopy.begin(); it != objectClassManagersCopy.end(); it++) {
      AbstractObjectClassManager* objectClassManager = it->second;
      ObjectClassHandlePtr objectClassHandle = it->first;
      objectClassManager->restore(*objectClassHandle);
   }
}

