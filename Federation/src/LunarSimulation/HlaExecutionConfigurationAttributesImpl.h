/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONATTRIBUTESIMPL_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONATTRIBUTESIMPL_H

#include <string>
#include <vector>

#include <LunarSimulation/datatypes/ExecutionMode.h>
#include <string>

#include <LunarSimulation/HlaExecutionConfigurationAttributes.h>
#include "AttributeValue.h"
#include <LunarSimulation/HlaTimeStamped.h>

namespace LunarSimulation {

    class HlaExecutionConfigurationAttributesImpl : public HlaExecutionConfigurationAttributes {
    public:
        HlaExecutionConfigurationAttributesImpl(
            const AttributeValue<std::wstring >& rootFrameName,
            const AttributeValue<double >& scenarioTimeEpoch,
            const AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode >& currentExecutionMode,
            const AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode >& nextExecutionMode,
            const AttributeValue<double >& nextModeScenarioTime,
            const AttributeValue<double >& nextModeCteTime,
            const AttributeValue<long long >& leastCommonTimeStep
        )
        :
            _rootFrameName(rootFrameName),
            _scenarioTimeEpoch(scenarioTimeEpoch),
            _currentExecutionMode(currentExecutionMode),
            _nextExecutionMode(nextExecutionMode),
            _nextModeScenarioTime(nextModeScenarioTime),
            _nextModeCteTime(nextModeCteTime),
            _leastCommonTimeStep(leastCommonTimeStep)
        {}

        bool hasRootFrameName();
        std::wstring getRootFrameName() THROW_SPEC (HlaValueNotSetException);
        std::wstring getRootFrameName(std::wstring defaultValue);
        LunarSimulation::HlaTimeStamped< std::wstring > getRootFrameNameTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasScenarioTimeEpoch();
        double getScenarioTimeEpoch() THROW_SPEC (HlaValueNotSetException);
        double getScenarioTimeEpoch(double defaultValue);
        LunarSimulation::HlaTimeStamped< double > getScenarioTimeEpochTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasCurrentExecutionMode();
        LunarSimulation::ExecutionMode::ExecutionMode getCurrentExecutionMode() THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::ExecutionMode::ExecutionMode getCurrentExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue);
        LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > getCurrentExecutionModeTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasNextExecutionMode();
        LunarSimulation::ExecutionMode::ExecutionMode getNextExecutionMode() THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::ExecutionMode::ExecutionMode getNextExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue);
        LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > getNextExecutionModeTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasNextModeScenarioTime();
        double getNextModeScenarioTime() THROW_SPEC (HlaValueNotSetException);
        double getNextModeScenarioTime(double defaultValue);
        LunarSimulation::HlaTimeStamped< double > getNextModeScenarioTimeTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasNextModeCteTime();
        double getNextModeCteTime() THROW_SPEC (HlaValueNotSetException);
        double getNextModeCteTime(double defaultValue);
        LunarSimulation::HlaTimeStamped< double > getNextModeCteTimeTimeStamped() THROW_SPEC (HlaValueNotSetException);

        bool hasLeastCommonTimeStep();
        long long getLeastCommonTimeStep() THROW_SPEC (HlaValueNotSetException);
        long long getLeastCommonTimeStep(long long defaultValue);
        LunarSimulation::HlaTimeStamped< long long > getLeastCommonTimeStepTimeStamped() THROW_SPEC (HlaValueNotSetException);
    
    private:
        AttributeValue<std::wstring > _rootFrameName;
        AttributeValue<double > _scenarioTimeEpoch;
        AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > _currentExecutionMode;
        AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > _nextExecutionMode;
        AttributeValue<double > _nextModeScenarioTime;
        AttributeValue<double > _nextModeCteTime;
        AttributeValue<long long > _leastCommonTimeStep;
    };
}
#endif
