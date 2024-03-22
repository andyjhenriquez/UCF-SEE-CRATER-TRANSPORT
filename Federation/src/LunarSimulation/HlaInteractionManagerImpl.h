/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAINTERACTIONMANAGERIMPL_H
#define DEVELOPER_STUDIO_HLAINTERACTIONMANAGERIMPL_H

#include <mutex>

#include <string>

#include <LunarSimulation/datatypes/ForceVector.h>
#include <LunarSimulation/datatypes/MTRMode.h>
#include <LunarSimulation/datatypes/PositionVector.h>
#include <LunarSimulation/datatypes/VelocityVector.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include <string>
#include <vector>
#include "datatypes/ForceVectorEncoder.h"
#include "datatypes/MTRModeEncoder.h"
#include "datatypes/PositionVectorEncoder.h"
#include "datatypes/VelocityVectorEncoder.h"

#include <LunarSimulation/HlaInteractionManager.h>
#include "AbstractInteractionClassManager.h"
#include "ImplPointers.h"
#include "DualMap.h"
#include "ListenerSet.h"


namespace LunarSimulation {
    class RtiInteractionManager;
    class HlaWorldImpl;

    class HlaInteractionManagerImpl : public AbstractInteractionClassManager , public HlaInteractionManager {

    private:
        RtiInteractionManager* const _interactionManager;
        HlaWorldImpl* const _hlaWorld;

        DualMap<std::wstring, InteractionClassHandlePtr> _interactions;
        ListenerSet<HlaInteractionListenerPtr> _interactionListeners;
        std::set<HlaInteractionManager::Interaction> _enabled;
        std::set<HlaInteractionManager::Interaction> _optional;

        DualMap<HlaInteractionManager::Interaction, std::wstring, DualMapComparator<std::wstring> > _interactionNames;

        mutable std::mutex _encoderLock;
        EncodingHelpers::HLAboolean _hLAbooleanEncoder;
        EncodingHelpers::HLAboolean _hLAbooleanDecoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEEncoder;
        EncodingHelpers::HLAfloat64LE _hLAfloat64LEDecoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderEncoder;
        LunarSimulation::PositionVectorEncoder _positionVectorEncoderDecoder;
        LunarSimulation::VelocityVectorEncoder _velocityVectorEncoderEncoder;
        LunarSimulation::VelocityVectorEncoder _velocityVectorEncoderDecoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringEncoder;
        EncodingHelpers::HLAunicodeString _hLAunicodeStringDecoder;
        LunarSimulation::ForceVectorEncoder _forceVectorEncoderEncoder;
        LunarSimulation::ForceVectorEncoder _forceVectorEncoderDecoder;
        LunarSimulation::MTRModeEncoder _mTRModeEncoderEncoder;
        LunarSimulation::MTRModeEncoder _mTRModeEncoderDecoder;

    public:
        HlaInteractionManagerImpl(RtiInteractionManager *interactionManager, HlaWorldImpl *hlaWorld);
        
        bool isEnabled(const std::wstring& interactionClassName);
        bool isOptional(const std::wstring& interactionClassName);

        void connected(const RtiDriver::InteractionClassHandle& interactionClassHandle, const std::wstring& interactionClassName)
            THROW_SPEC (HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void disconnected(const LunarSimulation::InteractionClassHandlePtr interactionClassHandle);
        
        void sendHLAinteractionRoot (
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendHLAinteractionRoot (
            HlaTimeStampPtr timeStamp
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendHLAinteractionRoot (
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendHLAinteractionRoot (
            HlaTimeStampPtr timeStamp,
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);


        HlaHLAinteractionRootInteractionPtr getHlaHLAinteractionRootInteraction();
        void sendHLAinteractionRootParams(HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void sendHLAinteractionRootParams(HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        
        void sendStartStop (
            bool haltSimulation,
            bool exitSimulation
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendStartStop (
            bool haltSimulation,
            bool exitSimulation,
            HlaTimeStampPtr timeStamp
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendStartStop (
            bool haltSimulation,
            bool exitSimulation,
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendStartStop (
            bool haltSimulation,
            bool exitSimulation,
            HlaTimeStampPtr timeStamp,
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);


        HlaStartStopInteractionPtr getHlaStartStopInteraction();
        void sendStartStopParams(HlaStartStopParametersPtr parameters, HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void sendStartStopParams(HlaStartStopParametersPtr parameters, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        
        void sendLoadScenario (
            double moonFriction,
            std::vector</* 3 */ double > roverInitialPosition,
            double roverHealth,
            double roverMass,
            double payloadMass,
            std::vector</* 3 */ double > launchSpeedVector,
            std::vector</* 3 */ double > roverStartPosition,
            std::wstring simulationScenario,
            std::vector</* 3 */ double > launcherPosition,
            std::vector</* 3 */ double > launchForce
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendLoadScenario (
            double moonFriction,
            std::vector</* 3 */ double > roverInitialPosition,
            double roverHealth,
            double roverMass,
            double payloadMass,
            std::vector</* 3 */ double > launchSpeedVector,
            std::vector</* 3 */ double > roverStartPosition,
            std::wstring simulationScenario,
            std::vector</* 3 */ double > launcherPosition,
            std::vector</* 3 */ double > launchForce,
            HlaTimeStampPtr timeStamp
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendLoadScenario (
            double moonFriction,
            std::vector</* 3 */ double > roverInitialPosition,
            double roverHealth,
            double roverMass,
            double payloadMass,
            std::vector</* 3 */ double > launchSpeedVector,
            std::vector</* 3 */ double > roverStartPosition,
            std::wstring simulationScenario,
            std::vector</* 3 */ double > launcherPosition,
            std::vector</* 3 */ double > launchForce,
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendLoadScenario (
            double moonFriction,
            std::vector</* 3 */ double > roverInitialPosition,
            double roverHealth,
            double roverMass,
            double payloadMass,
            std::vector</* 3 */ double > launchSpeedVector,
            std::vector</* 3 */ double > roverStartPosition,
            std::wstring simulationScenario,
            std::vector</* 3 */ double > launcherPosition,
            std::vector</* 3 */ double > launchForce,
            HlaTimeStampPtr timeStamp,
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);


        HlaLoadScenarioInteractionPtr getHlaLoadScenarioInteraction();
        void sendLoadScenarioParams(HlaLoadScenarioParametersPtr parameters, HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void sendLoadScenarioParams(HlaLoadScenarioParametersPtr parameters, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);
        
        void sendModeTransitionRequest (
            MTRMode::MTRMode executionMode
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendModeTransitionRequest (
            MTRMode::MTRMode executionMode,
            HlaTimeStampPtr timeStamp
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendModeTransitionRequest (
            MTRMode::MTRMode executionMode,
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void sendModeTransitionRequest (
            MTRMode::MTRMode executionMode,
            HlaTimeStampPtr timeStamp,
            HlaLogicalTimePtr logicalTime
        ) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);


        HlaModeTransitionRequestInteractionPtr getHlaModeTransitionRequestInteraction();
        void sendModeTransitionRequestParams(HlaModeTransitionRequestParametersPtr parameters, HlaTimeStampPtr timestamp) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException);
        void sendModeTransitionRequestParams(HlaModeTransitionRequestParametersPtr parameters, HlaTimeStampPtr timestamp, HlaLogicalTimePtr logicalTime) THROW_SPEC (HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaInvalidLogicalTimeException, HlaSaveInProgressException, HlaRestoreInProgressException);

        void addHlaInteractionListener(HlaInteractionListenerPtr);
        void removeHlaInteractionListener(HlaInteractionListenerPtr);
        
        std::wstring getHlaName(HlaInteractionManager::Interaction interaction);
        bool find(HlaInteractionManager::Interaction& interaction, std::wstring interactionHlaName);
        void setEnabled(bool enabled, HlaInteractionManager::Interaction interaction);
        void setEnabled(bool enabled, std::set<HlaInteractionManager::Interaction> interactions);
        void setEnabledIfAvailableInFom(std::set<HlaInteractionManager::Interaction> interactions);
        bool isEnabled(HlaInteractionManager::Interaction interaction);
        HlaFederateIdImplPtr getFederateIdImpl();

        /*
         * AbstractInteractionClassManager impl
         */
        void receiveInteraction(const RtiDriver::InteractionClassHandle& interactionClassHandle, const RtiDriver::NameValueMap& parameters,
            const HlaFederateIdImplPtr producingFederate, HlaTimeStampPtr hlaTimeStamp, HlaLogicalTimeImplPtr logicalTime);


    private:



        void postLengthException(const std::wstring& interactionName, const std::wstring& parameterName, const std::size_t expectedSize, const bool includeData, const std::vector<char> & data);
        void postDecodeException(const std::wstring& interactionName, const std::wstring& parameterName, const std::wstring& message, const bool includeData, const std::vector<char> & data);

        void decodeAndFireStartStop(
            const RtiDriver::NameValueMap& parameters,
            const HlaFederateIdImplPtr producingFederate,
            HlaTimeStampPtr hlaTimeStamp,
            HlaLogicalTimePtr logicalTime);

        void decodeAndFireLoadScenario(
            const RtiDriver::NameValueMap& parameters,
            const HlaFederateIdImplPtr producingFederate,
            HlaTimeStampPtr hlaTimeStamp,
            HlaLogicalTimePtr logicalTime);

        void decodeAndFireModeTransitionRequest(
            const RtiDriver::NameValueMap& parameters,
            const HlaFederateIdImplPtr producingFederate,
            HlaTimeStampPtr hlaTimeStamp,
            HlaLogicalTimePtr logicalTime);


        void fireHLAinteractionRoot(
            bool local,
            HlaTimeStampPtr hlaTimeStamp,
            HlaLogicalTimePtr logicalTime);

        void fireStartStop(
            bool local,
            HlaStartStopParametersPtr parameters,
            HlaTimeStampPtr hlaTimeStamp,
            HlaLogicalTimePtr logicalTime);

        void fireLoadScenario(
            bool local,
            HlaLoadScenarioParametersPtr parameters,
            HlaTimeStampPtr hlaTimeStamp,
            HlaLogicalTimePtr logicalTime);

        void fireModeTransitionRequest(
            bool local,
            HlaModeTransitionRequestParametersPtr parameters,
            HlaTimeStampPtr hlaTimeStamp,
            HlaLogicalTimePtr logicalTime);
    };
}
#endif
