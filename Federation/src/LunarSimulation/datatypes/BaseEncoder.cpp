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

#ifdef _WIN32
#pragma warning( disable : 4290)
#endif

#include "BaseEncoder.h"

namespace LunarSimulation {

    LunarSimulation::AccelerationVectorEncoder BaseEncoder::createAccelerationVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::AccelerationVectorEncoder(dt);
    }

    LunarSimulation::AccelerationVectorEncoder BaseEncoder::createAccelerationVector() {
       return LunarSimulation::AccelerationVectorEncoder();
    }

    LunarSimulation::AngularAccelerationVectorEncoder BaseEncoder::createAngularAccelerationVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::AngularAccelerationVectorEncoder(dt);
    }

    LunarSimulation::AngularAccelerationVectorEncoder BaseEncoder::createAngularAccelerationVector() {
       return LunarSimulation::AngularAccelerationVectorEncoder();
    }

    LunarSimulation::AngularVelocityVectorEncoder BaseEncoder::createAngularVelocityVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::AngularVelocityVectorEncoder(dt);
    }

    LunarSimulation::AngularVelocityVectorEncoder BaseEncoder::createAngularVelocityVector() {
       return LunarSimulation::AngularVelocityVectorEncoder();
    }

    LunarSimulation::ForceVectorEncoder BaseEncoder::createForceVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::ForceVectorEncoder(dt);
    }

    LunarSimulation::ForceVectorEncoder BaseEncoder::createForceVector() {
       return LunarSimulation::ForceVectorEncoder();
    }

    EncodingHelpers::HLAunicodeString BaseEncoder::createHLAunicodeString(const std::wstring& dt) {
       return EncodingHelpers::HLAunicodeString(dt);
    }

    EncodingHelpers::HLAunicodeString BaseEncoder::createHLAunicodeString() {
       return EncodingHelpers::HLAunicodeString();
    }

    LunarSimulation::InertiaMatrixEncoder BaseEncoder::createInertiaMatrix(const std::vector</* 9 */ double >& dt) {
       return LunarSimulation::InertiaMatrixEncoder(dt);
    }

    LunarSimulation::InertiaMatrixEncoder BaseEncoder::createInertiaMatrix() {
       return LunarSimulation::InertiaMatrixEncoder();
    }

    LunarSimulation::InertiaRateMatrixEncoder BaseEncoder::createInertiaRateMatrix(const std::vector</* 9 */ double >& dt) {
       return LunarSimulation::InertiaRateMatrixEncoder(dt);
    }

    LunarSimulation::InertiaRateMatrixEncoder BaseEncoder::createInertiaRateMatrix() {
       return LunarSimulation::InertiaRateMatrixEncoder();
    }

    LunarSimulation::PositionVectorEncoder BaseEncoder::createPositionVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::PositionVectorEncoder(dt);
    }

    LunarSimulation::PositionVectorEncoder BaseEncoder::createPositionVector() {
       return LunarSimulation::PositionVectorEncoder();
    }

    LunarSimulation::TorqueVectorEncoder BaseEncoder::createTorqueVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::TorqueVectorEncoder(dt);
    }

    LunarSimulation::TorqueVectorEncoder BaseEncoder::createTorqueVector() {
       return LunarSimulation::TorqueVectorEncoder();
    }

    LunarSimulation::VectorEncoder BaseEncoder::createVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::VectorEncoder(dt);
    }

    LunarSimulation::VectorEncoder BaseEncoder::createVector() {
       return LunarSimulation::VectorEncoder();
    }

    LunarSimulation::VelocityVectorEncoder BaseEncoder::createVelocityVector(const std::vector</* 3 */ double >& dt) {
       return LunarSimulation::VelocityVectorEncoder(dt);
    }

    LunarSimulation::VelocityVectorEncoder BaseEncoder::createVelocityVector() {
       return LunarSimulation::VelocityVectorEncoder();
    }

    LunarSimulation::ExecutionModeEncoder BaseEncoder::createExecutionMode(const LunarSimulation::ExecutionMode::ExecutionMode& dt) {
       return LunarSimulation::ExecutionModeEncoder(dt);
    }

    LunarSimulation::ExecutionModeEncoder BaseEncoder::createExecutionMode() {
       return LunarSimulation::ExecutionModeEncoder();
    }

    EncodingHelpers::HLAboolean BaseEncoder::createHLAboolean(const bool& dt) {
       return EncodingHelpers::HLAboolean(dt);
    }

    EncodingHelpers::HLAboolean BaseEncoder::createHLAboolean() {
       return EncodingHelpers::HLAboolean();
    }

    LunarSimulation::MTRModeEncoder BaseEncoder::createMTRMode(const LunarSimulation::MTRMode::MTRMode& dt) {
       return LunarSimulation::MTRModeEncoder(dt);
    }

    LunarSimulation::MTRModeEncoder BaseEncoder::createMTRMode() {
       return LunarSimulation::MTRModeEncoder();
    }

    LunarSimulation::AttitudeQuaternionEncoder BaseEncoder::createAttitudeQuaternion(const LunarSimulation::AttitudeQuaternion& dt) {
       return LunarSimulation::AttitudeQuaternionEncoder(dt);
    }

    LunarSimulation::AttitudeQuaternionEncoder BaseEncoder::createAttitudeQuaternion() {
       return LunarSimulation::AttitudeQuaternionEncoder();
    }

    LunarSimulation::ReferenceFrameRotationEncoder BaseEncoder::createReferenceFrameRotation(const LunarSimulation::ReferenceFrameRotation& dt) {
       return LunarSimulation::ReferenceFrameRotationEncoder(dt);
    }

    LunarSimulation::ReferenceFrameRotationEncoder BaseEncoder::createReferenceFrameRotation() {
       return LunarSimulation::ReferenceFrameRotationEncoder();
    }

    LunarSimulation::ReferenceFrameTranslationEncoder BaseEncoder::createReferenceFrameTranslation(const LunarSimulation::ReferenceFrameTranslation& dt) {
       return LunarSimulation::ReferenceFrameTranslationEncoder(dt);
    }

    LunarSimulation::ReferenceFrameTranslationEncoder BaseEncoder::createReferenceFrameTranslation() {
       return LunarSimulation::ReferenceFrameTranslationEncoder();
    }

    LunarSimulation::SpaceTimeCoordinateStateEncoder BaseEncoder::createSpaceTimeCoordinateState(const LunarSimulation::SpaceTimeCoordinateState& dt) {
       return LunarSimulation::SpaceTimeCoordinateStateEncoder(dt);
    }

    LunarSimulation::SpaceTimeCoordinateStateEncoder BaseEncoder::createSpaceTimeCoordinateState() {
       return LunarSimulation::SpaceTimeCoordinateStateEncoder();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createAcceleration(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createAcceleration() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createAngularAcceleration(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createAngularAcceleration() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createAngularRate(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createAngularRate() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createEnergy(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createEnergy() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createForce(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createForce() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createHealth(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createHealth() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAinteger64BE BaseEncoder::createHLAinteger64Time(const long long& dt) {
       return EncodingHelpers::HLAinteger64BE(dt);
    }

    EncodingHelpers::HLAinteger64BE BaseEncoder::createHLAinteger64Time() {
       return EncodingHelpers::HLAinteger64BE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createLength(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createLength() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMass(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMass() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMassMomentOfInertia(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMassMomentOfInertia() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMassMomentOfInertiaRate(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMassMomentOfInertiaRate() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMassRate(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createMassRate() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createScalar(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createScalar() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createTime(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createTime() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createTorque(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createTorque() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createVelocity(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createVelocity() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createHLAfloat64LE(const double& dt) {
       return EncodingHelpers::HLAfloat64LE(dt);
    }

    EncodingHelpers::HLAfloat64LE BaseEncoder::createHLAfloat64LE() {
       return EncodingHelpers::HLAfloat64LE();
    }

    EncodingHelpers::HLAinteger16LE BaseEncoder::createHLAinteger16LE(const short& dt) {
       return EncodingHelpers::HLAinteger16LE(dt);
    }

    EncodingHelpers::HLAinteger16LE BaseEncoder::createHLAinteger16LE() {
       return EncodingHelpers::HLAinteger16LE();
    }

    EncodingHelpers::HLAinteger64BE BaseEncoder::createHLAinteger64BE(const long long& dt) {
       return EncodingHelpers::HLAinteger64BE(dt);
    }

    EncodingHelpers::HLAinteger64BE BaseEncoder::createHLAinteger64BE() {
       return EncodingHelpers::HLAinteger64BE();
    }

}
