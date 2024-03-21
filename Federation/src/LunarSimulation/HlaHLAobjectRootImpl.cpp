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

#include "HlaHLAobjectRootImpl.h"

#include <RtiDriver/ObjectInstanceHandle.h>
#include <LunarSimulation/HlaTuning.h>
#include "HlaLogicalTimeImpl.h"

#include <LunarSimulation/HlaException.h>
#include <LunarSimulation/HlaHLAobjectRootValueListener.h>
#include "StringUtil.h"
#include "HlaHLAobjectRootManagerImpl.h"
#include "HlaHLAobjectRootAttributesImpl.h"
#include "HlaHLAobjectRootUpdaterImpl.h"
#include "HlaFederateIdImpl.h"
#include "HlaWorldImpl.h"

using namespace LunarSimulation;
using namespace std;


RtiDriver::NameSet HlaHLAobjectRootImpl::getAttributes() {
    RtiDriver::NameSet res;
    return res;
}


bool HlaHLAobjectRootImpl::isInitialized() {
    if (_initializeFired) {
        return true;
    }
    return true;
}

bool HlaHLAobjectRootImpl::isWithinInterest() const {
    return !_removed;
}

HlaHLAobjectRootAttributesPtr HlaHLAobjectRootImpl::getHlaHLAobjectRootAttributes() {
    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    return HlaHLAobjectRootAttributesPtr(new HlaHLAobjectRootAttributesImpl(
));
}

HlaHLAobjectRootUpdaterPtr HlaHLAobjectRootImpl::getHlaHLAobjectRootUpdater() {
    HlaHLAobjectRootUpdater* ptr = new HlaHLAobjectRootUpdaterImpl(shared_from_this());
    return HlaHLAobjectRootUpdaterPtr(ptr);
}

std::wstring HlaHLAobjectRootImpl::getHlaInstanceName() const {
    return _objectInstanceHandle->getObjectInstanceName();
}

std::vector<char> HlaHLAobjectRootImpl::getEncodedHlaObjectInstanceHandle() const {
    return _objectInstanceHandle->getEncodedHandle();
}

HlaFederateIdImplPtr HlaHLAobjectRootImpl::getFederateIdImpl() {
    return _hlaWorld->getFederateIdImpl();
}

/*
* Functions used by HlaHLAobjectRootUpdaterImpl
*/

void HlaHLAobjectRootImpl::applyUpdate(const AttributeMap& attributeUpdate, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
    if (!timeStamp) {
       timeStamp = _hlaWorld->getCurrentTime();
    }
    if (!logicalTime) {
       logicalTime = _hlaWorld->getDefaultSendTime();
    }

    std::lock_guard<std::recursive_mutex> lock(_sendLock);
    HlaHLAobjectRootAttributesImplPtr attributes = applyUpdate(attributeUpdate, _hlaWorld->getFederateIdImpl(), timeStamp, logicalTime);

    sendAttributes(attributeUpdate, attributes, timeStamp, logicalTime);
}

HlaHLAobjectRootAttributesImplPtr  HlaHLAobjectRootImpl::applyUpdate(const AttributeMap& attributeUpdate, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    HlaHLAobjectRootAttributesImplPtr ret;

    HlaEnumSet<HlaHLAobjectRootAttributes::Attribute> attributeUpdateSet(attributeUpdate.size());
    {
        std::lock_guard<std::recursive_mutex> lock(_attributesLock);
        ret = std::dynamic_pointer_cast<HlaHLAobjectRootAttributesImpl>(getHlaHLAobjectRootAttributes());
    }
    attributeUpdateSet.freeze();
    fireAttributesUpdated(attributeUpdateSet, timeStamp, logicalTime);

    return ret;
}

void HlaHLAobjectRootImpl::sendAttributes(const AttributeMap& attributeSet, HlaHLAobjectRootAttributesImplPtr attributeValues, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {

    RtiDriver::NameValueMap attributeValueMap;
    {
        std::unique_lock<std::mutex> lock(_objectClassManager->_encodersLock);
        for (AttributeMap::const_iterator iter = attributeSet.begin(); iter != attributeSet.end(); ++iter) {
        }
    }

    if (!attributeValueMap.empty()) {
       _objectClassManager->updateAttributeValues(shared_from_this(), _objectInstanceHandle, attributeValueMap, timeStamp, logicalTime);
    }
}


void HlaHLAobjectRootImpl::fireAttributesUpdated(const HlaEnumSet<HlaHLAobjectRootAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) {
    std::set<HlaHLAobjectRootListenerPtr> listeners = _hLAobjectRootListeners.getListeners();
    for (std::set<HlaHLAobjectRootListenerPtr>::iterator it = listeners.begin(); it != listeners.end(); ++it) {
        std::function<void()> callback = std::bind(&HlaHLAobjectRootListener::attributesUpdated, *it, shared_from_this(), attributes, timeStamp, logicalTime);
        _hlaWorld->postNotification(callback);
    }
}




void HlaHLAobjectRootImpl::addHlaHLAobjectRootListener(HlaHLAobjectRootListenerPtr listener) {
    _hLAobjectRootListeners.add(listener);
}

void HlaHLAobjectRootImpl::removeHlaHLAobjectRootListener(HlaHLAobjectRootListenerPtr listener) {
    _hLAobjectRootListeners.remove(listener);
}

void HlaHLAobjectRootImpl::addHlaHLAobjectRootValueListener(HlaHLAobjectRootValueListenerPtr valueListener) {
    _hLAobjectRootValueListeners.add(valueListener);
}
                    
void HlaHLAobjectRootImpl::removeHlaHLAobjectRootValueListener(HlaHLAobjectRootValueListenerPtr valueListener) {
    _hLAobjectRootValueListeners.remove(valueListener);
}


void HlaHLAobjectRootImpl::reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime) {
    HlaEnumSet<HlaHLAobjectRootAttributes::Attribute> attributesUpdated(attributes.size());

    attributesUpdated.freeze();
    fireAttributesUpdated(attributesUpdated, timeStamp, logicalTime);
}

void HlaHLAobjectRootImpl::provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp) {
    try {
        std::lock_guard<std::recursive_mutex> lock(_sendLock);
        sendAttributes(getAttributeMap(attributes), std::dynamic_pointer_cast<HlaHLAobjectRootAttributesImpl>(getHlaHLAobjectRootAttributes()), timeStamp, HlaLogicalTimeImpl::getInvalid());
    } catch (HlaException&) { //Ignoring this exception
    }
}

HlaHLAobjectRootImpl::AttributeMap HlaHLAobjectRootImpl::getAttributeMap(const RtiDriver::NameSet& attributeNames) {
    AttributeMap res;

    std::lock_guard<std::recursive_mutex> lock(_attributesLock);
    for (RtiDriver::NameSet::const_iterator iter = attributeNames.begin(); iter != attributeNames.end(); ++iter) {
    }
    return res;
}

RtiDriver::NameSet HlaHLAobjectRootImpl::getUnsetAttributeNames() {
    RtiDriver::NameSet res;
    HlaHLAobjectRootAttributesPtr attributes = getHlaHLAobjectRootAttributes();
    return res;
}


