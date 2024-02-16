/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONUPDATERIMPL_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONUPDATERIMPL_H

#include <mutex>
#include <memory>

#include <LunarSimulation/HlaExecutionConfigurationUpdater.h>
#include "AttributeValue.h"
#include "HlaExecutionConfigurationImpl.h"

namespace LunarSimulation {

    class HlaExecutionConfigurationUpdaterImpl : public HlaExecutionConfigurationUpdater , public std::enable_shared_from_this<HlaExecutionConfigurationUpdaterImpl> {

    private:
        mutable std::mutex _attributesLock;

        AttributeValue<std::wstring > _rootFrameName;
        AttributeValue<double > _scenarioTimeEpoch;
        AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > _currentExecutionMode;
        AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > _nextExecutionMode;
        AttributeValue<double > _nextModeScenarioTime;
        AttributeValue<double > _nextModeCteTime;
        AttributeValue<long long > _leastCommonTimeStep;

        HlaExecutionConfigurationImplPtr _instance;
        bool _updateSent;

    public:
        explicit HlaExecutionConfigurationUpdaterImpl(HlaExecutionConfigurationImplPtr instance) :
            _instance(instance),
            _updateSent(false)
        {}

        void setRootFrameName(const std::wstring& rootFrameName);
        void setScenarioTimeEpoch(const double& scenarioTimeEpoch);
        void setCurrentExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& currentExecutionMode);
        void setNextExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& nextExecutionMode);
        void setNextModeScenarioTime(const double& nextModeScenarioTime);
        void setNextModeCteTime(const double& nextModeCteTime);
        void setLeastCommonTimeStep(const long long& leastCommonTimeStep);

        void sendUpdate()
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendUpdate(HlaTimeStampPtr timestamp)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendUpdate(HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendUpdate(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

    };
}
#endif
