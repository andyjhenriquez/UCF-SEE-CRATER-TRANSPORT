package core.impl;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

import core.datatypes.AttitudeQuaternion;
import core.datatypes.SpaceTimeCoordinateState;
import core.HlaPayloadAttributes;
import core.HlaTimeStamped;
import core.exceptions.HlaValueNotSetException;
import core.impl.utils.AttributeValue;

/* @Immutable */
final class HlaPayloadAttributesImpl implements HlaPayloadAttributes {

   private final AttributeValue<double[/* 3 */]> _position;
   private final AttributeValue<double[/* 3 */]> _velocity;
   private final AttributeValue<Double> _health;
   private final AttributeValue<double[/* 3 */]> _force;
   private final AttributeValue<double[/* 3 */]> _torque;
   private final AttributeValue<Double> _mass;
   private final AttributeValue<Double> _massRate;
   private final AttributeValue<double[/* 9 */]> _inertia;
   private final AttributeValue<double[/* 9 */]> _inertiaRate;
   private final AttributeValue<String> _name;
   private final AttributeValue<String> _type;
   private final AttributeValue<String> _status;
   private final AttributeValue<String> _parentReferenceFrame;
   private final AttributeValue<SpaceTimeCoordinateState> _state;
   private final AttributeValue<double[/* 3 */]> _acceleration;
   private final AttributeValue<double[/* 3 */]> _rotationalAcceleration;
   private final AttributeValue<double[/* 3 */]> _centerOfMass;
   private final AttributeValue<AttitudeQuaternion> _bodyWrtStructural;

   HlaPayloadAttributesImpl(
      AttributeValue<double[/* 3 */]> position,
      AttributeValue<double[/* 3 */]> velocity,
      AttributeValue<Double> health,
      AttributeValue<double[/* 3 */]> force,
      AttributeValue<double[/* 3 */]> torque,
      AttributeValue<Double> mass,
      AttributeValue<Double> massRate,
      AttributeValue<double[/* 9 */]> inertia,
      AttributeValue<double[/* 9 */]> inertiaRate,
      AttributeValue<String> name,
      AttributeValue<String> type,
      AttributeValue<String> status,
      AttributeValue<String> parentReferenceFrame,
      AttributeValue<SpaceTimeCoordinateState> state,
      AttributeValue<double[/* 3 */]> acceleration,
      AttributeValue<double[/* 3 */]> rotationalAcceleration,
      AttributeValue<double[/* 3 */]> centerOfMass,
      AttributeValue<AttitudeQuaternion> bodyWrtStructural
   ) {
      _position = new AttributeValue<double[/* 3 */]>(position);
      _velocity = new AttributeValue<double[/* 3 */]>(velocity);
      _health = new AttributeValue<Double>(health);
      _force = new AttributeValue<double[/* 3 */]>(force);
      _torque = new AttributeValue<double[/* 3 */]>(torque);
      _mass = new AttributeValue<Double>(mass);
      _massRate = new AttributeValue<Double>(massRate);
      _inertia = new AttributeValue<double[/* 9 */]>(inertia);
      _inertiaRate = new AttributeValue<double[/* 9 */]>(inertiaRate);
      _name = new AttributeValue<String>(name);
      _type = new AttributeValue<String>(type);
      _status = new AttributeValue<String>(status);
      _parentReferenceFrame = new AttributeValue<String>(parentReferenceFrame);
      _state = new AttributeValue<SpaceTimeCoordinateState>(state);
      _acceleration = new AttributeValue<double[/* 3 */]>(acceleration);
      _rotationalAcceleration = new AttributeValue<double[/* 3 */]>(rotationalAcceleration);
      _centerOfMass = new AttributeValue<double[/* 3 */]>(centerOfMass);
      _bodyWrtStructural = new AttributeValue<AttitudeQuaternion>(bodyWrtStructural);
   }

   public boolean hasPosition() {
      return _position.hasValue();
   }

   public double[/* 3 */] getPosition() throws HlaValueNotSetException {
      if (_position.hasValue()) {
         return _position.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'position' not set");
   }

   public double[/* 3 */] getPosition(double[/* 3 */] defaultValue) {
      if (_position.hasValue()) {
         return _position.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getPositionTimeStamped() throws HlaValueNotSetException {
      if (_position.hasValue()) {
         return _position.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'position' not set");
   }

   public boolean hasVelocity() {
      return _velocity.hasValue();
   }

   public double[/* 3 */] getVelocity() throws HlaValueNotSetException {
      if (_velocity.hasValue()) {
         return _velocity.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'velocity' not set");
   }

   public double[/* 3 */] getVelocity(double[/* 3 */] defaultValue) {
      if (_velocity.hasValue()) {
         return _velocity.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getVelocityTimeStamped() throws HlaValueNotSetException {
      if (_velocity.hasValue()) {
         return _velocity.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'velocity' not set");
   }

   public boolean hasHealth() {
      return _health.hasValue();
   }

   public double getHealth() throws HlaValueNotSetException {
      if (_health.hasValue()) {
         return _health.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'health' not set");
   }

   public double getHealth(double defaultValue) {
      if (_health.hasValue()) {
         return _health.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<Double> getHealthTimeStamped() throws HlaValueNotSetException {
      if (_health.hasValue()) {
         return _health.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'health' not set");
   }

   public boolean hasForce() {
      return _force.hasValue();
   }

   public double[/* 3 */] getForce() throws HlaValueNotSetException {
      if (_force.hasValue()) {
         return _force.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'force' not set");
   }

   public double[/* 3 */] getForce(double[/* 3 */] defaultValue) {
      if (_force.hasValue()) {
         return _force.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getForceTimeStamped() throws HlaValueNotSetException {
      if (_force.hasValue()) {
         return _force.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'force' not set");
   }

   public boolean hasTorque() {
      return _torque.hasValue();
   }

   public double[/* 3 */] getTorque() throws HlaValueNotSetException {
      if (_torque.hasValue()) {
         return _torque.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'torque' not set");
   }

   public double[/* 3 */] getTorque(double[/* 3 */] defaultValue) {
      if (_torque.hasValue()) {
         return _torque.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getTorqueTimeStamped() throws HlaValueNotSetException {
      if (_torque.hasValue()) {
         return _torque.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'torque' not set");
   }

   public boolean hasMass() {
      return _mass.hasValue();
   }

   public double getMass() throws HlaValueNotSetException {
      if (_mass.hasValue()) {
         return _mass.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'mass' not set");
   }

   public double getMass(double defaultValue) {
      if (_mass.hasValue()) {
         return _mass.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<Double> getMassTimeStamped() throws HlaValueNotSetException {
      if (_mass.hasValue()) {
         return _mass.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'mass' not set");
   }

   public boolean hasMassRate() {
      return _massRate.hasValue();
   }

   public double getMassRate() throws HlaValueNotSetException {
      if (_massRate.hasValue()) {
         return _massRate.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'massRate' not set");
   }

   public double getMassRate(double defaultValue) {
      if (_massRate.hasValue()) {
         return _massRate.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<Double> getMassRateTimeStamped() throws HlaValueNotSetException {
      if (_massRate.hasValue()) {
         return _massRate.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'massRate' not set");
   }

   public boolean hasInertia() {
      return _inertia.hasValue();
   }

   public double[/* 9 */] getInertia() throws HlaValueNotSetException {
      if (_inertia.hasValue()) {
         return _inertia.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'inertia' not set");
   }

   public double[/* 9 */] getInertia(double[/* 9 */] defaultValue) {
      if (_inertia.hasValue()) {
         return _inertia.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 9 */]> getInertiaTimeStamped() throws HlaValueNotSetException {
      if (_inertia.hasValue()) {
         return _inertia.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'inertia' not set");
   }

   public boolean hasInertiaRate() {
      return _inertiaRate.hasValue();
   }

   public double[/* 9 */] getInertiaRate() throws HlaValueNotSetException {
      if (_inertiaRate.hasValue()) {
         return _inertiaRate.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'inertiaRate' not set");
   }

   public double[/* 9 */] getInertiaRate(double[/* 9 */] defaultValue) {
      if (_inertiaRate.hasValue()) {
         return _inertiaRate.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 9 */]> getInertiaRateTimeStamped() throws HlaValueNotSetException {
      if (_inertiaRate.hasValue()) {
         return _inertiaRate.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'inertiaRate' not set");
   }

   public boolean hasName() {
      return _name.hasValue();
   }

   public String getName() throws HlaValueNotSetException {
      if (_name.hasValue()) {
         return _name.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'name' not set");
   }

   public String getName(String defaultValue) {
      if (_name.hasValue()) {
         return _name.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getNameTimeStamped() throws HlaValueNotSetException {
      if (_name.hasValue()) {
         return _name.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'name' not set");
   }

   public boolean hasType() {
      return _type.hasValue();
   }

   public String getType() throws HlaValueNotSetException {
      if (_type.hasValue()) {
         return _type.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'type' not set");
   }

   public String getType(String defaultValue) {
      if (_type.hasValue()) {
         return _type.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getTypeTimeStamped() throws HlaValueNotSetException {
      if (_type.hasValue()) {
         return _type.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'type' not set");
   }

   public boolean hasStatus() {
      return _status.hasValue();
   }

   public String getStatus() throws HlaValueNotSetException {
      if (_status.hasValue()) {
         return _status.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'status' not set");
   }

   public String getStatus(String defaultValue) {
      if (_status.hasValue()) {
         return _status.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getStatusTimeStamped() throws HlaValueNotSetException {
      if (_status.hasValue()) {
         return _status.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'status' not set");
   }

   public boolean hasParentReferenceFrame() {
      return _parentReferenceFrame.hasValue();
   }

   public String getParentReferenceFrame() throws HlaValueNotSetException {
      if (_parentReferenceFrame.hasValue()) {
         return _parentReferenceFrame.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'parentReferenceFrame' not set");
   }

   public String getParentReferenceFrame(String defaultValue) {
      if (_parentReferenceFrame.hasValue()) {
         return _parentReferenceFrame.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getParentReferenceFrameTimeStamped() throws HlaValueNotSetException {
      if (_parentReferenceFrame.hasValue()) {
         return _parentReferenceFrame.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'parentReferenceFrame' not set");
   }

   public boolean hasState() {
      return _state.hasValue();
   }

   public SpaceTimeCoordinateState getState() throws HlaValueNotSetException {
      if (_state.hasValue()) {
         return _state.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'state' not set");
   }

   public SpaceTimeCoordinateState getState(SpaceTimeCoordinateState defaultValue) {
      if (_state.hasValue()) {
         return _state.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<SpaceTimeCoordinateState> getStateTimeStamped() throws HlaValueNotSetException {
      if (_state.hasValue()) {
         return _state.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'state' not set");
   }

   public boolean hasAcceleration() {
      return _acceleration.hasValue();
   }

   public double[/* 3 */] getAcceleration() throws HlaValueNotSetException {
      if (_acceleration.hasValue()) {
         return _acceleration.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'acceleration' not set");
   }

   public double[/* 3 */] getAcceleration(double[/* 3 */] defaultValue) {
      if (_acceleration.hasValue()) {
         return _acceleration.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getAccelerationTimeStamped() throws HlaValueNotSetException {
      if (_acceleration.hasValue()) {
         return _acceleration.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'acceleration' not set");
   }

   public boolean hasRotationalAcceleration() {
      return _rotationalAcceleration.hasValue();
   }

   public double[/* 3 */] getRotationalAcceleration() throws HlaValueNotSetException {
      if (_rotationalAcceleration.hasValue()) {
         return _rotationalAcceleration.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'rotationalAcceleration' not set");
   }

   public double[/* 3 */] getRotationalAcceleration(double[/* 3 */] defaultValue) {
      if (_rotationalAcceleration.hasValue()) {
         return _rotationalAcceleration.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getRotationalAccelerationTimeStamped() throws HlaValueNotSetException {
      if (_rotationalAcceleration.hasValue()) {
         return _rotationalAcceleration.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'rotationalAcceleration' not set");
   }

   public boolean hasCenterOfMass() {
      return _centerOfMass.hasValue();
   }

   public double[/* 3 */] getCenterOfMass() throws HlaValueNotSetException {
      if (_centerOfMass.hasValue()) {
         return _centerOfMass.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'centerOfMass' not set");
   }

   public double[/* 3 */] getCenterOfMass(double[/* 3 */] defaultValue) {
      if (_centerOfMass.hasValue()) {
         return _centerOfMass.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getCenterOfMassTimeStamped() throws HlaValueNotSetException {
      if (_centerOfMass.hasValue()) {
         return _centerOfMass.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'centerOfMass' not set");
   }

   public boolean hasBodyWrtStructural() {
      return _bodyWrtStructural.hasValue();
   }

   public AttitudeQuaternion getBodyWrtStructural() throws HlaValueNotSetException {
      if (_bodyWrtStructural.hasValue()) {
         return _bodyWrtStructural.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'bodyWrtStructural' not set");
   }

   public AttitudeQuaternion getBodyWrtStructural(AttitudeQuaternion defaultValue) {
      if (_bodyWrtStructural.hasValue()) {
         return _bodyWrtStructural.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<AttitudeQuaternion> getBodyWrtStructuralTimeStamped() throws HlaValueNotSetException {
      if (_bodyWrtStructural.hasValue()) {
         return _bodyWrtStructural.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'bodyWrtStructural' not set");
   }

}
