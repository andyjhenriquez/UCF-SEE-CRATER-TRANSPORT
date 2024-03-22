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

#include "HlaExecutionConfigurationUpdaterImpl.h"

#include <map>


#include <LunarSimulation/HlaExecutionConfigurationAttributes.h>
#include <LunarSimulation/HlaTimeStampFactory.h>
#include "HlaLogicalTimeImpl.h"

using namespace std;
using namespace LunarSimulation;

void HlaExecutionConfigurationUpdaterImpl::setRootFrameName(const std::wstring& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _rootFrameName.setValue(std::shared_ptr<std::wstring >(new std::wstring(value)));
}

void HlaExecutionConfigurationUpdaterImpl::setScenarioTimeEpoch(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _scenarioTimeEpoch.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaExecutionConfigurationUpdaterImpl::setCurrentExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _currentExecutionMode.setValue(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode >(new LunarSimulation::ExecutionMode::ExecutionMode(value)));
}

void HlaExecutionConfigurationUpdaterImpl::setNextExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _nextExecutionMode.setValue(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode >(new LunarSimulation::ExecutionMode::ExecutionMode(value)));
}

void HlaExecutionConfigurationUpdaterImpl::setNextModeScenarioTime(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _nextModeScenarioTime.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaExecutionConfigurationUpdaterImpl::setNextModeCteTime(const double& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _nextModeCteTime.setValue(std::shared_ptr<double >(new double(value)));
}

void HlaExecutionConfigurationUpdaterImpl::setLeastCommonTimeStep(const long long& value)
{
   std::lock_guard<std::mutex> lock(_attributesLock);
   _leastCommonTimeStep.setValue(std::shared_ptr<long long >(new long long(value)));
}


void HlaExecutionConfigurationUpdaterImpl::sendUpdate()
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(HlaTimeStampPtr(), HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaExecutionConfigurationUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   try {
      sendUpdate(timeStamp, HlaLogicalTimePtr());
   } catch (HlaInvalidLogicalTimeException) {
      //can not happen with no logicaltime
   }
}

void HlaExecutionConfigurationUpdaterImpl::sendUpdate(HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   sendUpdate(HlaTimeStampPtr(), logicalTime);
}

void HlaExecutionConfigurationUpdaterImpl::sendUpdate(HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException)
{
   if (!_instance->isLocal()) {
      throw HlaAttributeNotOwnedException("Can not change remote object");
   }

   HlaExecutionConfigurationImpl::AttributeMap attributeUpdates;
   {
      std::lock_guard<std::mutex> lock(_attributesLock);
      if (_updateSent) {
         throw HlaUpdaterReusedException("Update already sent");
      }
      _updateSent = true;

      if (_rootFrameName.hasValue()) {
         attributeUpdates[HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME] = _rootFrameName.getValue();
      }
      if (_scenarioTimeEpoch.hasValue()) {
         attributeUpdates[HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH] = _scenarioTimeEpoch.getValue();
      }
      if (_currentExecutionMode.hasValue()) {
         attributeUpdates[HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE] = _currentExecutionMode.getValue();
      }
      if (_nextExecutionMode.hasValue()) {
         attributeUpdates[HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE] = _nextExecutionMode.getValue();
      }
      if (_nextModeScenarioTime.hasValue()) {
         attributeUpdates[HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME] = _nextModeScenarioTime.getValue();
      }
      if (_nextModeCteTime.hasValue()) {
         attributeUpdates[HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME] = _nextModeCteTime.getValue();
      }
      if (_leastCommonTimeStep.hasValue()) {
         attributeUpdates[HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP] = _leastCommonTimeStep.getValue();
      }
      _instance->applyUpdate(attributeUpdates, timeStamp, logicalTime);
   }
}
