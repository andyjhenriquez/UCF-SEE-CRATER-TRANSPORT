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

#include "HlaPhysicalInterfaceUpdaterImpl.h"

#include <map>


#include <LunarSimulation/HlaPhysicalInterfaceAttributes.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include "HlaLogicalTimeImpl.h"

using namespace std;
using namespace LunarSimulation;

void HlaPhysicalInterfaceUpdaterImpl::setName(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _name.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPhysicalInterfaceUpdaterImpl::setParentName(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _parentName.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPhysicalInterfaceUpdaterImpl::setPosition(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _position.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPhysicalInterfaceUpdaterImpl::setAttitude(const LunarSimulation::AttitudeQuaternion& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _attitude.setValue(std::shared_ptr<LunarSimulation::AttitudeQuaternion >(new LunarSimulation::AttitudeQuaternion(value)));
}


void HlaPhysicalInterfaceUpdaterImpl::sendUpdate()
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(HlaTimeStampPtr(), HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaPhysicalInterfaceUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaPhysicalInterfaceUpdaterImpl::sendUpdate(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   sendUpdate(HlaTimeStampPtr(), logicalTime);
}

void HlaPhysicalInterfaceUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   if (!_instance->isLocal()) {
      throw HlaAttributeNotOwnedException("Can not change remote object");
   }

   HlaPhysicalInterfaceImpl::AttributeMap attributeUpdates;
   {
      std::lock_guard<std::mutex> lock(_attributesLock);
      if (_updateSent) {
         throw HlaUpdaterReusedException("Update already sent");
      }
      _updateSent = true;

      if (_name.hasValue()) {
         attributeUpdates[HlaPhysicalInterfaceAttributes::NAME] = _name.getValue();
      }
      if (_parentName.hasValue()) {
         attributeUpdates[HlaPhysicalInterfaceAttributes::PARENT_NAME] = _parentName.getValue();
      }
      if (_position.hasValue()) {
         attributeUpdates[HlaPhysicalInterfaceAttributes::POSITION] = _position.getValue();
      }
      if (_attitude.hasValue()) {
         attributeUpdates[HlaPhysicalInterfaceAttributes::ATTITUDE] = _attitude.getValue();
      }
      _instance->applyUpdate(attributeUpdates, timeStamp, logicalTime);
   }
}
