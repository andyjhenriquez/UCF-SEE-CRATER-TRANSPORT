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

#include "HlaPhysicalEntityUpdaterImpl.h"

#include <map>


#include <LunarSimulation/HlaPhysicalEntityAttributes.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include "HlaLogicalTimeImpl.h"

using namespace std;
using namespace LunarSimulation;

void HlaPhysicalEntityUpdaterImpl::sendName()
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _name.setValue(std::shared_ptr<std::wstring >(new std::wstring(_instance->getName())));
}

void HlaPhysicalEntityUpdaterImpl::setType(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _type.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPhysicalEntityUpdaterImpl::setStatus(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _status.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPhysicalEntityUpdaterImpl::setParentReferenceFrame(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _parentReferenceFrame.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPhysicalEntityUpdaterImpl::setState(const LunarSimulation::SpaceTimeCoordinateState& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _state.setValue(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState >(new LunarSimulation::SpaceTimeCoordinateState(value)));
}

void HlaPhysicalEntityUpdaterImpl::setAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _acceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPhysicalEntityUpdaterImpl::setRotationalAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _rotationalAcceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPhysicalEntityUpdaterImpl::setCenterOfMass(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _centerOfMass.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPhysicalEntityUpdaterImpl::setBodyWrtStructural(const LunarSimulation::AttitudeQuaternion& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _bodyWrtStructural.setValue(std::shared_ptr<LunarSimulation::AttitudeQuaternion >(new LunarSimulation::AttitudeQuaternion(value)));
}


void HlaPhysicalEntityUpdaterImpl::sendUpdate()
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(HlaTimeStampPtr(), HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaPhysicalEntityUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaPhysicalEntityUpdaterImpl::sendUpdate(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   sendUpdate(HlaTimeStampPtr(), logicalTime);
}

void HlaPhysicalEntityUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   if (!_instance->isLocal()) {
      throw HlaAttributeNotOwnedException("Can not change remote object");
   }

   HlaPhysicalEntityImpl::AttributeMap attributeUpdates;
   {
      std::lock_guard<std::mutex> lock(_attributesLock);
      if (_updateSent) {
         throw HlaUpdaterReusedException("Update already sent");
      }
      _updateSent = true;

      if (_name.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::NAME] = _name.getValue();
      }
      if (_type.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::TYPE] = _type.getValue();
      }
      if (_status.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::STATUS] = _status.getValue();
      }
      if (_parentReferenceFrame.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrame.getValue();
      }
      if (_state.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::STATE] = _state.getValue();
      }
      if (_acceleration.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::ACCELERATION] = _acceleration.getValue();
      }
      if (_rotationalAcceleration.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::ROTATIONAL_ACCELERATION] = _rotationalAcceleration.getValue();
      }
      if (_centerOfMass.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::CENTER_OF_MASS] = _centerOfMass.getValue();
      }
      if (_bodyWrtStructural.hasValue()) {
         attributeUpdates[HlaPhysicalEntityAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructural.getValue();
      }
      _instance->applyUpdate(attributeUpdates, timeStamp, logicalTime);
   }
}
