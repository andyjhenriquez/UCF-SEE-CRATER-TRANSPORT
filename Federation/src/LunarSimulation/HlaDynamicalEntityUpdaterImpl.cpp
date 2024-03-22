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

#include "HlaDynamicalEntityUpdaterImpl.h"

#include <map>


#include <LunarSimulation/HlaDynamicalEntityAttributes.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include "HlaLogicalTimeImpl.h"

using namespace std;
using namespace LunarSimulation;

void HlaDynamicalEntityUpdaterImpl::setForce(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _force.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaDynamicalEntityUpdaterImpl::setTorque(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _torque.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaDynamicalEntityUpdaterImpl::setMass(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _mass.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaDynamicalEntityUpdaterImpl::setMassRate(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _massRate.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaDynamicalEntityUpdaterImpl::setInertia(const std::vector</* 9 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _inertia.setValue(std::shared_ptr<std::vector</* 9 */ double > >(new std::vector</* 9 */ double >(value)));
}

void HlaDynamicalEntityUpdaterImpl::setInertiaRate(const std::vector</* 9 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _inertiaRate.setValue(std::shared_ptr<std::vector</* 9 */ double > >(new std::vector</* 9 */ double >(value)));
}

void HlaDynamicalEntityUpdaterImpl::sendName()
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _name.setValue(std::shared_ptr<std::wstring >(new std::wstring(_instance->getName())));
}

void HlaDynamicalEntityUpdaterImpl::setType(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _type.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaDynamicalEntityUpdaterImpl::setStatus(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _status.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaDynamicalEntityUpdaterImpl::setParentReferenceFrame(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _parentReferenceFrame.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaDynamicalEntityUpdaterImpl::setState(const LunarSimulation::SpaceTimeCoordinateState& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _state.setValue(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState >(new LunarSimulation::SpaceTimeCoordinateState(value)));
}

void HlaDynamicalEntityUpdaterImpl::setAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _acceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaDynamicalEntityUpdaterImpl::setRotationalAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _rotationalAcceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaDynamicalEntityUpdaterImpl::setCenterOfMass(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _centerOfMass.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaDynamicalEntityUpdaterImpl::setBodyWrtStructural(const LunarSimulation::AttitudeQuaternion& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _bodyWrtStructural.setValue(std::shared_ptr<LunarSimulation::AttitudeQuaternion >(new LunarSimulation::AttitudeQuaternion(value)));
}


void HlaDynamicalEntityUpdaterImpl::sendUpdate()
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(HlaTimeStampPtr(), HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaDynamicalEntityUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaDynamicalEntityUpdaterImpl::sendUpdate(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   sendUpdate(HlaTimeStampPtr(), logicalTime);
}

void HlaDynamicalEntityUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   if (!_instance->isLocal()) {
      throw HlaAttributeNotOwnedException("Can not change remote object");
   }

   HlaDynamicalEntityImpl::AttributeMap attributeUpdates;
   {
      std::lock_guard<std::mutex> lock(_attributesLock);
      if (_updateSent) {
         throw HlaUpdaterReusedException("Update already sent");
      }
      _updateSent = true;

      if (_force.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::FORCE] = _force.getValue();
      }
      if (_torque.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::TORQUE] = _torque.getValue();
      }
      if (_mass.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::MASS] = _mass.getValue();
      }
      if (_massRate.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::MASS_RATE] = _massRate.getValue();
      }
      if (_inertia.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::INERTIA] = _inertia.getValue();
      }
      if (_inertiaRate.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::INERTIA_RATE] = _inertiaRate.getValue();
      }
      if (_name.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::NAME] = _name.getValue();
      }
      if (_type.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::TYPE] = _type.getValue();
      }
      if (_status.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::STATUS] = _status.getValue();
      }
      if (_parentReferenceFrame.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrame.getValue();
      }
      if (_state.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::STATE] = _state.getValue();
      }
      if (_acceleration.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::ACCELERATION] = _acceleration.getValue();
      }
      if (_rotationalAcceleration.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::ROTATIONAL_ACCELERATION] = _rotationalAcceleration.getValue();
      }
      if (_centerOfMass.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::CENTER_OF_MASS] = _centerOfMass.getValue();
      }
      if (_bodyWrtStructural.hasValue()) {
         attributeUpdates[HlaDynamicalEntityAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructural.getValue();
      }
      _instance->applyUpdate(attributeUpdates, timeStamp, logicalTime);
   }
}
