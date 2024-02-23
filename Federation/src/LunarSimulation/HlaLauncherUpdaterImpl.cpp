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

#include "HlaLauncherUpdaterImpl.h"

#include <map>


#include <LunarSimulation/HlaLauncherAttributes.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include "HlaLogicalTimeImpl.h"

using namespace std;
using namespace LunarSimulation;

void HlaLauncherUpdaterImpl::setPosition(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _position.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaLauncherUpdaterImpl::setMass(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _mass.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaLauncherUpdaterImpl::setEnergy(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _energy.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaLauncherUpdaterImpl::setName(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _name.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaLauncherUpdaterImpl::setType(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _type.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaLauncherUpdaterImpl::setStatus(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _status.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaLauncherUpdaterImpl::setParentReferenceFrame(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _parentReferenceFrame.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaLauncherUpdaterImpl::setState(const LunarSimulation::SpaceTimeCoordinateState& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _state.setValue(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState >(new LunarSimulation::SpaceTimeCoordinateState(value)));
}

void HlaLauncherUpdaterImpl::setAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _acceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaLauncherUpdaterImpl::setRotationalAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _rotationalAcceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaLauncherUpdaterImpl::setCenterOfMass(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _centerOfMass.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaLauncherUpdaterImpl::setBodyWrtStructural(const LunarSimulation::AttitudeQuaternion& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _bodyWrtStructural.setValue(std::shared_ptr<LunarSimulation::AttitudeQuaternion >(new LunarSimulation::AttitudeQuaternion(value)));
}


void HlaLauncherUpdaterImpl::sendUpdate()
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(HlaTimeStampPtr(), HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaLauncherUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaLauncherUpdaterImpl::sendUpdate(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   sendUpdate(HlaTimeStampPtr(), logicalTime);
}

void HlaLauncherUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   if (!_instance->isLocal()) {
      throw HlaAttributeNotOwnedException("Can not change remote object");
   }

   HlaLauncherImpl::AttributeMap attributeUpdates;
   {
      std::lock_guard<std::mutex> lock(_attributesLock);
      if (_updateSent) {
         throw HlaUpdaterReusedException("Update already sent");
      }
      _updateSent = true;

      if (_position.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::POSITION] = _position.getValue();
      }
      if (_mass.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::MASS] = _mass.getValue();
      }
      if (_energy.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::ENERGY] = _energy.getValue();
      }
      if (_name.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::NAME] = _name.getValue();
      }
      if (_type.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::TYPE] = _type.getValue();
      }
      if (_status.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::STATUS] = _status.getValue();
      }
      if (_parentReferenceFrame.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrame.getValue();
      }
      if (_state.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::STATE] = _state.getValue();
      }
      if (_acceleration.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::ACCELERATION] = _acceleration.getValue();
      }
      if (_rotationalAcceleration.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::ROTATIONAL_ACCELERATION] = _rotationalAcceleration.getValue();
      }
      if (_centerOfMass.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::CENTER_OF_MASS] = _centerOfMass.getValue();
      }
      if (_bodyWrtStructural.hasValue()) {
         attributeUpdates[HlaLauncherAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructural.getValue();
      }
      _instance->applyUpdate(attributeUpdates, timeStamp, logicalTime);
   }
}
