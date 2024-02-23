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

#include "HlaExecutionConfigurationAttributesImpl.h"
#include <map>

using namespace LunarSimulation;

static  std::map<HlaExecutionConfigurationAttributes::Attribute, std::wstring> insertNames() {
    std::map<HlaExecutionConfigurationAttributes::Attribute, std::wstring> nameMap;
    nameMap[HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME] = L"root_frame_name";
    nameMap[HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH] = L"scenario_time_epoch";
    nameMap[HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE] = L"current_execution_mode";
    nameMap[HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE] = L"next_execution_mode";
    nameMap[HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME] = L"next_mode_scenario_time";
    nameMap[HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME] = L"next_mode_cte_time";
    nameMap[HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP] = L"least_common_time_step";
    return nameMap;
}

static  std::map<std::wstring, HlaExecutionConfigurationAttributes::Attribute> insertAttributes() {
    std::map<std::wstring, HlaExecutionConfigurationAttributes::Attribute> attributeMap;
    attributeMap[L"root_frame_name"] = HlaExecutionConfigurationAttributes::ROOT_FRAME_NAME;
    attributeMap[L"scenario_time_epoch"] = HlaExecutionConfigurationAttributes::SCENARIO_TIME_EPOCH;
    attributeMap[L"current_execution_mode"] = HlaExecutionConfigurationAttributes::CURRENT_EXECUTION_MODE;
    attributeMap[L"next_execution_mode"] = HlaExecutionConfigurationAttributes::NEXT_EXECUTION_MODE;
    attributeMap[L"next_mode_scenario_time"] = HlaExecutionConfigurationAttributes::NEXT_MODE_SCENARIO_TIME;
    attributeMap[L"next_mode_cte_time"] = HlaExecutionConfigurationAttributes::NEXT_MODE_CTE_TIME;
    attributeMap[L"least_common_time_step"] = HlaExecutionConfigurationAttributes::LEAST_COMMON_TIME_STEP;
    return attributeMap;
}

static std::map<HlaExecutionConfigurationAttributes::Attribute, std::wstring> _nameMap = insertNames();
static std::map<std::wstring, HlaExecutionConfigurationAttributes::Attribute> _attributeMap = insertAttributes();

bool HlaExecutionConfigurationAttributesImpl::hasRootFrameName() {
   return _rootFrameName.hasValue();
}

std::wstring HlaExecutionConfigurationAttributesImpl::getRootFrameName()
THROW_SPEC (HlaValueNotSetException) {
   if (_rootFrameName.hasValue()) {
      return *_rootFrameName.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rootFrameName' not set");
}

std::wstring HlaExecutionConfigurationAttributesImpl::getRootFrameName(std::wstring defaultValue) {
   if (_rootFrameName.hasValue()) {
      return *_rootFrameName.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< std::wstring > HlaExecutionConfigurationAttributesImpl::getRootFrameNameTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_rootFrameName.hasValue()) {
      return _rootFrameName.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'rootFrameName' not set");
}

bool HlaExecutionConfigurationAttributesImpl::hasScenarioTimeEpoch() {
   return _scenarioTimeEpoch.hasValue();
}

double HlaExecutionConfigurationAttributesImpl::getScenarioTimeEpoch()
THROW_SPEC (HlaValueNotSetException) {
   if (_scenarioTimeEpoch.hasValue()) {
      return *_scenarioTimeEpoch.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'scenarioTimeEpoch' not set");
}

double HlaExecutionConfigurationAttributesImpl::getScenarioTimeEpoch(double defaultValue) {
   if (_scenarioTimeEpoch.hasValue()) {
      return *_scenarioTimeEpoch.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaExecutionConfigurationAttributesImpl::getScenarioTimeEpochTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_scenarioTimeEpoch.hasValue()) {
      return _scenarioTimeEpoch.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'scenarioTimeEpoch' not set");
}

bool HlaExecutionConfigurationAttributesImpl::hasCurrentExecutionMode() {
   return _currentExecutionMode.hasValue();
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationAttributesImpl::getCurrentExecutionMode()
THROW_SPEC (HlaValueNotSetException) {
   if (_currentExecutionMode.hasValue()) {
      return *_currentExecutionMode.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'currentExecutionMode' not set");
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationAttributesImpl::getCurrentExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue) {
   if (_currentExecutionMode.hasValue()) {
      return *_currentExecutionMode.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > HlaExecutionConfigurationAttributesImpl::getCurrentExecutionModeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_currentExecutionMode.hasValue()) {
      return _currentExecutionMode.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'currentExecutionMode' not set");
}

bool HlaExecutionConfigurationAttributesImpl::hasNextExecutionMode() {
   return _nextExecutionMode.hasValue();
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationAttributesImpl::getNextExecutionMode()
THROW_SPEC (HlaValueNotSetException) {
   if (_nextExecutionMode.hasValue()) {
      return *_nextExecutionMode.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'nextExecutionMode' not set");
}

LunarSimulation::ExecutionMode::ExecutionMode HlaExecutionConfigurationAttributesImpl::getNextExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue) {
   if (_nextExecutionMode.hasValue()) {
      return *_nextExecutionMode.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > HlaExecutionConfigurationAttributesImpl::getNextExecutionModeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_nextExecutionMode.hasValue()) {
      return _nextExecutionMode.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'nextExecutionMode' not set");
}

bool HlaExecutionConfigurationAttributesImpl::hasNextModeScenarioTime() {
   return _nextModeScenarioTime.hasValue();
}

double HlaExecutionConfigurationAttributesImpl::getNextModeScenarioTime()
THROW_SPEC (HlaValueNotSetException) {
   if (_nextModeScenarioTime.hasValue()) {
      return *_nextModeScenarioTime.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'nextModeScenarioTime' not set");
}

double HlaExecutionConfigurationAttributesImpl::getNextModeScenarioTime(double defaultValue) {
   if (_nextModeScenarioTime.hasValue()) {
      return *_nextModeScenarioTime.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaExecutionConfigurationAttributesImpl::getNextModeScenarioTimeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_nextModeScenarioTime.hasValue()) {
      return _nextModeScenarioTime.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'nextModeScenarioTime' not set");
}

bool HlaExecutionConfigurationAttributesImpl::hasNextModeCteTime() {
   return _nextModeCteTime.hasValue();
}

double HlaExecutionConfigurationAttributesImpl::getNextModeCteTime()
THROW_SPEC (HlaValueNotSetException) {
   if (_nextModeCteTime.hasValue()) {
      return *_nextModeCteTime.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'nextModeCteTime' not set");
}

double HlaExecutionConfigurationAttributesImpl::getNextModeCteTime(double defaultValue) {
   if (_nextModeCteTime.hasValue()) {
      return *_nextModeCteTime.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< double > HlaExecutionConfigurationAttributesImpl::getNextModeCteTimeTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_nextModeCteTime.hasValue()) {
      return _nextModeCteTime.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'nextModeCteTime' not set");
}

bool HlaExecutionConfigurationAttributesImpl::hasLeastCommonTimeStep() {
   return _leastCommonTimeStep.hasValue();
}

long long HlaExecutionConfigurationAttributesImpl::getLeastCommonTimeStep()
THROW_SPEC (HlaValueNotSetException) {
   if (_leastCommonTimeStep.hasValue()) {
      return *_leastCommonTimeStep.getValue();
   }
   throw HlaValueNotSetException(L"Attribute 'leastCommonTimeStep' not set");
}

long long HlaExecutionConfigurationAttributesImpl::getLeastCommonTimeStep(long long defaultValue) {
   if (_leastCommonTimeStep.hasValue()) {
      return *_leastCommonTimeStep.getValue();
   }
   return defaultValue;
}

LunarSimulation::HlaTimeStamped< long long > HlaExecutionConfigurationAttributesImpl::getLeastCommonTimeStepTimeStamped()
THROW_SPEC (HlaValueNotSetException) {
   if (_leastCommonTimeStep.hasValue()) {
      return _leastCommonTimeStep.getTimestampedValue();
   }
   throw HlaValueNotSetException(L"Attribute 'leastCommonTimeStep' not set");
}


std::wstring HlaExecutionConfigurationAttributes::getName(Attribute attribute) {
    std::map<HlaExecutionConfigurationAttributes::Attribute, std::wstring>::iterator it = _nameMap.find(attribute);
    if (it != _nameMap.end()) {
        return it->second;
    } else {
        return L"";
    }
}

bool HlaExecutionConfigurationAttributes::find(HlaExecutionConfigurationAttributes::Attribute& attribute, std::wstring name) {
    std::map<std::wstring, HlaExecutionConfigurationAttributes::Attribute>::iterator it = _attributeMap.find(name);
    if (it != _attributeMap.end()) {
        attribute = it->second;
        return true;
    } else {
        return false;
    }
}

