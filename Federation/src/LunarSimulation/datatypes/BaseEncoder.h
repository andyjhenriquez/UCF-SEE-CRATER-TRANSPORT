/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_DATATYPES_BASEENCODER_H
#define DEVELOPER_STUDIO_DATATYPES_BASEENCODER_H

#include <string>

#include <RtiDriver/Types.h>
#include <RtiDriver/Encoding/BasicDataElements.h>
#include <RtiDriver/Encoding/HLAopaqueData.h>

#include "AccelerationVectorEncoder.h"
#include "AngularAccelerationVectorEncoder.h"
#include "AngularVelocityVectorEncoder.h"
#include "ForceVectorEncoder.h"
#include "InertiaMatrixEncoder.h"
#include "InertiaRateMatrixEncoder.h"
#include "PositionVectorEncoder.h"
#include "TorqueVectorEncoder.h"
#include "VectorEncoder.h"
#include "VelocityVectorEncoder.h"
#include "ExecutionModeEncoder.h"
#include "MTRModeEncoder.h"
#include "AttitudeQuaternionEncoder.h"
#include "ReferenceFrameRotationEncoder.h"
#include "ReferenceFrameTranslationEncoder.h"
#include "SpaceTimeCoordinateStateEncoder.h"

namespace LunarSimulation {
    class BaseEncoder {

    public:
       static LunarSimulation::AccelerationVectorEncoder createAccelerationVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::AccelerationVectorEncoder createAccelerationVector();

       static LunarSimulation::AngularAccelerationVectorEncoder createAngularAccelerationVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::AngularAccelerationVectorEncoder createAngularAccelerationVector();

       static LunarSimulation::AngularVelocityVectorEncoder createAngularVelocityVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::AngularVelocityVectorEncoder createAngularVelocityVector();

       static LunarSimulation::ForceVectorEncoder createForceVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::ForceVectorEncoder createForceVector();

       static EncodingHelpers::HLAunicodeString createHLAunicodeString(const std::wstring& dt);
       static EncodingHelpers::HLAunicodeString createHLAunicodeString();

       static LunarSimulation::InertiaMatrixEncoder createInertiaMatrix(const std::vector</* 9 */ double >& dt);
       static LunarSimulation::InertiaMatrixEncoder createInertiaMatrix();

       static LunarSimulation::InertiaRateMatrixEncoder createInertiaRateMatrix(const std::vector</* 9 */ double >& dt);
       static LunarSimulation::InertiaRateMatrixEncoder createInertiaRateMatrix();

       static LunarSimulation::PositionVectorEncoder createPositionVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::PositionVectorEncoder createPositionVector();

       static LunarSimulation::TorqueVectorEncoder createTorqueVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::TorqueVectorEncoder createTorqueVector();

       static LunarSimulation::VectorEncoder createVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::VectorEncoder createVector();

       static LunarSimulation::VelocityVectorEncoder createVelocityVector(const std::vector</* 3 */ double >& dt);
       static LunarSimulation::VelocityVectorEncoder createVelocityVector();

       static LunarSimulation::ExecutionModeEncoder createExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& dt);
       static LunarSimulation::ExecutionModeEncoder createExecutionMode();

       static LunarSimulation::MTRModeEncoder createMTRMode(const LunarSimulation::MTRMode::MTRMode& dt);
       static LunarSimulation::MTRModeEncoder createMTRMode();

       static LunarSimulation::AttitudeQuaternionEncoder createAttitudeQuaternion(const LunarSimulation::AttitudeQuaternion& dt);
       static LunarSimulation::AttitudeQuaternionEncoder createAttitudeQuaternion();

       static LunarSimulation::ReferenceFrameRotationEncoder createReferenceFrameRotation(const LunarSimulation::ReferenceFrameRotation& dt);
       static LunarSimulation::ReferenceFrameRotationEncoder createReferenceFrameRotation();

       static LunarSimulation::ReferenceFrameTranslationEncoder createReferenceFrameTranslation(const LunarSimulation::ReferenceFrameTranslation& dt);
       static LunarSimulation::ReferenceFrameTranslationEncoder createReferenceFrameTranslation();

       static LunarSimulation::SpaceTimeCoordinateStateEncoder createSpaceTimeCoordinateState(const LunarSimulation::SpaceTimeCoordinateState& dt);
       static LunarSimulation::SpaceTimeCoordinateStateEncoder createSpaceTimeCoordinateState();

       static EncodingHelpers::HLAfloat64LE createAcceleration(const double& dt);
       static EncodingHelpers::HLAfloat64LE createAcceleration();

       static EncodingHelpers::HLAfloat64LE createAngularAcceleration(const double& dt);
       static EncodingHelpers::HLAfloat64LE createAngularAcceleration();

       static EncodingHelpers::HLAfloat64LE createAngularRate(const double& dt);
       static EncodingHelpers::HLAfloat64LE createAngularRate();

       static EncodingHelpers::HLAfloat64LE createEnergy(const double& dt);
       static EncodingHelpers::HLAfloat64LE createEnergy();

       static EncodingHelpers::HLAfloat64LE createForce(const double& dt);
       static EncodingHelpers::HLAfloat64LE createForce();

       static EncodingHelpers::HLAfloat64LE createHealth(const double& dt);
       static EncodingHelpers::HLAfloat64LE createHealth();

       static EncodingHelpers::HLAinteger64BE createHLAinteger64Time(const long long& dt);
       static EncodingHelpers::HLAinteger64BE createHLAinteger64Time();

       static EncodingHelpers::HLAfloat64LE createLength(const double& dt);
       static EncodingHelpers::HLAfloat64LE createLength();

       static EncodingHelpers::HLAfloat64LE createMass(const double& dt);
       static EncodingHelpers::HLAfloat64LE createMass();

       static EncodingHelpers::HLAfloat64LE createMassMomentOfInertia(const double& dt);
       static EncodingHelpers::HLAfloat64LE createMassMomentOfInertia();

       static EncodingHelpers::HLAfloat64LE createMassMomentOfInertiaRate(const double& dt);
       static EncodingHelpers::HLAfloat64LE createMassMomentOfInertiaRate();

       static EncodingHelpers::HLAfloat64LE createMassRate(const double& dt);
       static EncodingHelpers::HLAfloat64LE createMassRate();

       static EncodingHelpers::HLAfloat64LE createScalar(const double& dt);
       static EncodingHelpers::HLAfloat64LE createScalar();

       static EncodingHelpers::HLAfloat64LE createTime(const double& dt);
       static EncodingHelpers::HLAfloat64LE createTime();

       static EncodingHelpers::HLAfloat64LE createTorque(const double& dt);
       static EncodingHelpers::HLAfloat64LE createTorque();

       static EncodingHelpers::HLAfloat64LE createVelocity(const double& dt);
       static EncodingHelpers::HLAfloat64LE createVelocity();

       static EncodingHelpers::HLAfloat64LE createHLAfloat64LE(const double& dt);
       static EncodingHelpers::HLAfloat64LE createHLAfloat64LE();

       static EncodingHelpers::HLAinteger16LE createHLAinteger16LE(const short& dt);
       static EncodingHelpers::HLAinteger16LE createHLAinteger16LE();

       static EncodingHelpers::HLAinteger64BE createHLAinteger64BE(const long long& dt);
       static EncodingHelpers::HLAinteger64BE createHLAinteger64BE();

    };
}
#endif
