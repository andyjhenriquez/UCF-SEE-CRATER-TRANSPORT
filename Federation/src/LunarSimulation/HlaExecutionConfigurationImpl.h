/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONIMPL_H
#define DEVELOPER_STUDIO_HLAEXECUTIONCONFIGURATIONIMPL_H

#include <string>
#include <map>

#include <mutex>
#include <memory>

#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaTimeStamped.h>


#include <LunarSimulation/HlaExecutionConfiguration.h>
#include "ImplPointers.h"
#include "AttributeValue.h"
#include "ParameterValue.h"
#include "ListenerSet.h"


namespace LunarSimulation {

    class HlaWorldImpl;
    class HlaExecutionConfigurationManagerImpl;

    class HlaExecutionConfigurationImpl : public HlaExecutionConfiguration , public std::enable_shared_from_this<HlaExecutionConfigurationImpl> {
    private:
        bool _isLocal;
        HlaFederateIdImplPtr _createdByFederate;
        bool _initializeFired;
        bool _removed;
        HlaWorldImpl* _hlaWorld;
        HlaExecutionConfigurationManagerImpl* _objectClassManager;
        ObjectInstanceHandlePtr _objectInstanceHandle;

        ListenerSet<HlaExecutionConfigurationValueListenerPtr> _executionConfigurationValueListeners;
        ListenerSet<HlaExecutionConfigurationListenerPtr> _executionConfigurationListeners;

        mutable std::recursive_mutex _attributesLock;
        mutable std::recursive_mutex _sendLock;

        AttributeValue<std::wstring > _rootFrameNameAttribute;
        AttributeValue<double > _scenarioTimeEpochAttribute;
        AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > _currentExecutionModeAttribute;
        AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode > _nextExecutionModeAttribute;
        AttributeValue<double > _nextModeScenarioTimeAttribute;
        AttributeValue<double > _nextModeCteTimeAttribute;
        AttributeValue<long long > _leastCommonTimeStepAttribute;

    public:
        typedef std::map<HlaExecutionConfigurationAttributes::Attribute, std::shared_ptr<void> > AttributeMap;

        HlaExecutionConfigurationImpl(HlaWorldImpl* hlaWorld, HlaExecutionConfigurationManagerImpl* objectClassManager, ObjectInstanceHandlePtr objectInstanceHandle, bool local, const HlaFederateIdImplPtr federateId) :
            _isLocal(local),
            _createdByFederate(federateId),
            _initializeFired(false),
            _removed(false),
            _hlaWorld(hlaWorld),
            _objectClassManager(objectClassManager),
            _objectInstanceHandle(objectInstanceHandle)
        {}

        ObjectInstanceHandlePtr getObjectInstanceHandle() {
            return _objectInstanceHandle;
        }

        static RtiDriver::NameSet getAttributes();

        bool isInitialized();

        bool isWithinInterest() const;

        bool isInitializedFired() const {
            return _initializeFired;
        }

        void setInitializedFired() {
            _initializeFired = true;
        }

        void setRemoved() {
            _removed = true;
            _executionConfigurationValueListeners.clear();
            _executionConfigurationListeners.clear();
        }

        bool isLocal() const {
            return _isLocal;
        }

        bool isRemoved() const {
            return _removed;
        }

        HlaExecutionConfigurationAttributesPtr getHlaExecutionConfigurationAttributes();

        HlaExecutionConfigurationUpdaterPtr getHlaExecutionConfigurationUpdater();

        std::wstring getHlaInstanceName() const;

        std::vector<char> getEncodedHlaObjectInstanceHandle() const;

        HlaObjectInstanceBase::ObjectClassType getClassType() const {
            return HlaObjectInstanceBase::EXECUTION_CONFIGURATION;
        }

        HlaFederateIdPtr getProducingFederate() const {
            return _createdByFederate;
        }

        HlaFederateIdPtr getLastProducingFederate(HlaExecutionConfigurationAttributes::Attribute attribute);


        void addHlaExecutionConfigurationListener(HlaExecutionConfigurationListenerPtr listener);
        void removeHlaExecutionConfigurationListener(HlaExecutionConfigurationListenerPtr listener);
        void addHlaExecutionConfigurationValueListener(HlaExecutionConfigurationValueListenerPtr valueListener);
        void removeHlaExecutionConfigurationValueListener(HlaExecutionConfigurationValueListenerPtr valueListener);

        bool hasRootFrameName();

        std::wstring getRootFrameName()
            THROW_SPEC (HlaValueNotSetException);
        std::wstring getRootFrameName(std::wstring defaultValue);

        LunarSimulation::HlaTimeStamped< std::wstring > getRootFrameNameTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasScenarioTimeEpoch();

        double getScenarioTimeEpoch()
            THROW_SPEC (HlaValueNotSetException);
        double getScenarioTimeEpoch(double defaultValue);

        LunarSimulation::HlaTimeStamped< double > getScenarioTimeEpochTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasCurrentExecutionMode();

        LunarSimulation::ExecutionMode::ExecutionMode getCurrentExecutionMode()
            THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::ExecutionMode::ExecutionMode getCurrentExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue);

        LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > getCurrentExecutionModeTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasNextExecutionMode();

        LunarSimulation::ExecutionMode::ExecutionMode getNextExecutionMode()
            THROW_SPEC (HlaValueNotSetException);
        LunarSimulation::ExecutionMode::ExecutionMode getNextExecutionMode(LunarSimulation::ExecutionMode::ExecutionMode defaultValue);

        LunarSimulation::HlaTimeStamped< LunarSimulation::ExecutionMode::ExecutionMode > getNextExecutionModeTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasNextModeScenarioTime();

        double getNextModeScenarioTime()
            THROW_SPEC (HlaValueNotSetException);
        double getNextModeScenarioTime(double defaultValue);

        LunarSimulation::HlaTimeStamped< double > getNextModeScenarioTimeTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasNextModeCteTime();

        double getNextModeCteTime()
            THROW_SPEC (HlaValueNotSetException);
        double getNextModeCteTime(double defaultValue);

        LunarSimulation::HlaTimeStamped< double > getNextModeCteTimeTimeStamped()
            THROW_SPEC (HlaValueNotSetException);

        bool hasLeastCommonTimeStep();

        long long getLeastCommonTimeStep()
            THROW_SPEC (HlaValueNotSetException);
        long long getLeastCommonTimeStep(long long defaultValue);

        LunarSimulation::HlaTimeStamped< long long > getLeastCommonTimeStepTimeStamped()
            THROW_SPEC (HlaValueNotSetException);


        HlaFederateIdImplPtr getFederateIdImpl();

        /*
         * Functions used by HlaExecutionConfigurationUpdaterImpl
         */

        void applyUpdate(const AttributeMap& attributeMap, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime)
            THROW_SPEC (HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void reflectAttributeValues(const RtiDriver::NameValueMap& attributes, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimeImplPtr logicalTime);

        void provideAttributeValueUpdate(const RtiDriver::NameSet& attributes, HlaTimeStampPtr timeStamp);

        RtiDriver::NameSet getUnsetAttributeNames();


    private:

        HlaExecutionConfigurationAttributesImplPtr applyUpdate(const AttributeMap& attributeMap, const HlaFederateIdImplPtr federateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void sendAttributes(const AttributeMap& attributeMap, HlaExecutionConfigurationAttributesImplPtr attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        void fireroot_frame_nameUpdated(std::shared_ptr<std::wstring > value, const AttributeValue<std::wstring >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateRootFrameName();
        void firescenario_time_epochUpdated(std::shared_ptr<double > value, const AttributeValue<double >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateScenarioTimeEpoch();
        void firecurrent_execution_modeUpdated(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > value, const AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateCurrentExecutionMode();
        void firenext_execution_modeUpdated(std::shared_ptr<LunarSimulation::ExecutionMode::ExecutionMode > value, const AttributeValue<LunarSimulation::ExecutionMode::ExecutionMode >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateNextExecutionMode();
        void firenext_mode_scenario_timeUpdated(std::shared_ptr<double > value, const AttributeValue<double >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateNextModeScenarioTime();
        void firenext_mode_cte_timeUpdated(std::shared_ptr<double > value, const AttributeValue<double >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateNextModeCteTime();
        void fireleast_common_time_stepUpdated(std::shared_ptr<long long > value, const AttributeValue<long long >& oldValue, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void updateLeastCommonTimeStep();

        void fireAttributesUpdated(const HlaEnumSet<HlaExecutionConfigurationAttributes::Attribute> & attributes, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);
        void fireProducingFederateUpdated(HlaExecutionConfigurationAttributes::Attribute attribute, const HlaFederateIdImplPtr oldFederateId, const HlaFederateIdImplPtr newFederateId, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime);

        AttributeMap getAttributeMap(const RtiDriver::NameSet& attributeNames);

    };
}
#endif
