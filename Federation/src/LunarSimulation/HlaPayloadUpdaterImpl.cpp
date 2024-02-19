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

#include "HlaPayloadUpdaterImpl.h"

#include <map>


#include <LunarSimulation/HlaPayloadAttributes.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include "HlaLogicalTimeImpl.h"

using namespace std;
using namespace LunarSimulation;

void HlaPayloadUpdaterImpl::setPosition(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _position.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setVelocity(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _velocity.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setHealth(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _health.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaPayloadUpdaterImpl::setForce(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _force.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setTorque(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _torque.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setMass(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _mass.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaPayloadUpdaterImpl::setMassRate(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _massRate.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaPayloadUpdaterImpl::setInertia(const std::vector</* 9 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _inertia.setValue(std::shared_ptr<std::vector</* 9 */ double > >(new std::vector</* 9 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setInertiaRate(const std::vector</* 9 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _inertiaRate.setValue(std::shared_ptr<std::vector</* 9 */ double > >(new std::vector</* 9 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setName(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _name.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPayloadUpdaterImpl::setType(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _type.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPayloadUpdaterImpl::setStatus(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _status.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPayloadUpdaterImpl::setParentReferenceFrame(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _parentReferenceFrame.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaPayloadUpdaterImpl::setState(const LunarSimulation::SpaceTimeCoordinateState& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _state.setValue(std::shared_ptr<LunarSimulation::SpaceTimeCoordinateState >(new LunarSimulation::SpaceTimeCoordinateState(value)));
}

void HlaPayloadUpdaterImpl::setAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _acceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setRotationalAcceleration(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _rotationalAcceleration.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setCenterOfMass(const std::vector</* 3 */ double >& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _centerOfMass.setValue(std::shared_ptr<std::vector</* 3 */ double > >(new std::vector</* 3 */ double >(value)));
}

void HlaPayloadUpdaterImpl::setBodyWrtStructural(const LunarSimulation::AttitudeQuaternion& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _bodyWrtStructural.setValue(std::shared_ptr<LunarSimulation::AttitudeQuaternion >(new LunarSimulation::AttitudeQuaternion(value)));
}


void HlaPayloadUpdaterImpl::sendUpdate()
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(HlaTimeStampPtr(), HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaPayloadUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaPayloadUpdaterImpl::sendUpdate(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   sendUpdate(HlaTimeStampPtr(), logicalTime);
}

void HlaPayloadUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   if (!_instance->isLocal()) {
      throw HlaAttributeNotOwnedException("Can not change remote object");
   }

   HlaPayloadImpl::AttributeMap attributeUpdates;
   {
      std::lock_guard<std::mutex> lock(_attributesLock);
      if (_updateSent) {
         throw HlaUpdaterReusedException("Update already sent");
      }
      _updateSent = true;

      if (_position.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::POSITION] = _position.getValue();
      }
      if (_velocity.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::VELOCITY] = _velocity.getValue();
      }
      if (_health.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::HEALTH] = _health.getValue();
      }
      if (_force.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::FORCE] = _force.getValue();
      }
      if (_torque.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::TORQUE] = _torque.getValue();
      }
      if (_mass.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::MASS] = _mass.getValue();
      }
      if (_massRate.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::MASS_RATE] = _massRate.getValue();
      }
      if (_inertia.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::INERTIA] = _inertia.getValue();
      }
      if (_inertiaRate.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::INERTIA_RATE] = _inertiaRate.getValue();
      }
      if (_name.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::NAME] = _name.getValue();
      }
      if (_type.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::TYPE] = _type.getValue();
      }
      if (_status.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::STATUS] = _status.getValue();
      }
      if (_parentReferenceFrame.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::PARENT_REFERENCE_FRAME] = _parentReferenceFrame.getValue();
      }
      if (_state.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::STATE] = _state.getValue();
      }
      if (_acceleration.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::ACCELERATION] = _acceleration.getValue();
      }
      if (_rotationalAcceleration.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::ROTATIONAL_ACCELERATION] = _rotationalAcceleration.getValue();
      }
      if (_centerOfMass.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::CENTER_OF_MASS] = _centerOfMass.getValue();
      }
      if (_bodyWrtStructural.hasValue()) {
         attributeUpdates[HlaPayloadAttributes::BODY_WRT_STRUCTURAL] = _bodyWrtStructural.getValue();
      }
      _instance->applyUpdate(attributeUpdates, timeStamp, logicalTime);
   }
}
