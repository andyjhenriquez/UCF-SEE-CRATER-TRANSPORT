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
import core.HlaPayloadUpdater;
import core.HlaPayloadListener;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.AttributeValue;
import core.HlaPayloadAttributes; 

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.concurrent.atomic.AtomicBoolean;


/* @ThreadSafe */
final class HlaPayloadUpdaterImpl implements HlaPayloadUpdater {
   private final AtomicBoolean _updateSent = new AtomicBoolean(false);
   private final Object _attributesLock = new Object();

   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _position = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _velocity = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _health = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _force = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _torque = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _mass = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _massRate = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 9 */]> _inertia = new AttributeValue<double[/* 9 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 9 */]> _inertiaRate = new AttributeValue<double[/* 9 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _name = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _type = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _status = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _parentReferenceFrame = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<SpaceTimeCoordinateState> _state = new AttributeValue<SpaceTimeCoordinateState>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _acceleration = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _rotationalAcceleration = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _centerOfMass = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<AttitudeQuaternion> _bodyWrtStructural = new AttributeValue<AttitudeQuaternion>();

   private final HlaPayloadImpl _instance;


   HlaPayloadUpdaterImpl(HlaPayloadImpl instance) {
      _instance = instance;
   }

   public HlaPayloadUpdaterImpl setPosition(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _position.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setVelocity(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _velocity.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setHealth(double value) {
      synchronized (_attributesLock) {
         _health.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setForce(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _force.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setTorque(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _torque.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setMass(double value) {
      synchronized (_attributesLock) {
         _mass.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setMassRate(double value) {
      synchronized (_attributesLock) {
         _massRate.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setInertia(double[/* 9 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _inertia.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setInertiaRate(double[/* 9 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _inertiaRate.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _name.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setType(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _type.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setStatus(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _status.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setParentReferenceFrame(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _parentReferenceFrame.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setState(SpaceTimeCoordinateState value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _state.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setAcceleration(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _acceleration.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setRotationalAcceleration(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _rotationalAcceleration.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setCenterOfMass(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _centerOfMass.setValueFromUser(value);
      }
      return this;
   }

   public HlaPayloadUpdaterImpl setBodyWrtStructural(AttitudeQuaternion value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _bodyWrtStructural.setValueFromUser(value);
      }
      return this;
   }


   public void sendUpdate() throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException {
      try {
         sendUpdate(null, null);
      } catch (HlaInvalidLogicalTimeException e) {
         //can not happen with null logicalTime
      }
   }

   public void sendUpdate(HlaTimeStamp timestamp) throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaSaveInProgressException, HlaRestoreInProgressException {
      try {
         sendUpdate(timestamp, null);
      } catch (HlaInvalidLogicalTimeException e) {
         //can not happen with null logicalTime
      }
   }

   public void sendUpdate(HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInvalidLogicalTimeException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      sendUpdate(null, logicalTime);
   }

   public void sendUpdate(HlaTimeStamp timestamp, HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInvalidLogicalTimeException, HlaUpdaterReusedException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      if (!_instance.isLocal()) {
         throw new HlaAttributeNotOwnedException("Can not change remote object");
      }
      if (_updateSent.getAndSet(true)) {
         throw new HlaUpdaterReusedException("Update already sent");
      }

      EnumMap<HlaPayloadAttributes.Attribute, Object> attributeUpdates =
            new EnumMap<HlaPayloadAttributes.Attribute, Object>(HlaPayloadAttributes.Attribute.class);
      EnumSet<HlaPayloadAttributes.Attribute> sendAttributes = EnumSet.noneOf(HlaPayloadAttributes.Attribute.class);

      synchronized (_attributesLock) {
         if (_position.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.POSITION, _position.getValue());
         }
         if (_velocity.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.VELOCITY, _velocity.getValue());
         }
         if (_health.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.HEALTH, _health.getValue());
         }
         if (_force.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.FORCE, _force.getValue());
         }
         if (_torque.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.TORQUE, _torque.getValue());
         }
         if (_mass.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.MASS, _mass.getValue());
         }
         if (_massRate.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.MASS_RATE, _massRate.getValue());
         }
         if (_inertia.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.INERTIA, _inertia.getValue());
         }
         if (_inertiaRate.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.INERTIA_RATE, _inertiaRate.getValue());
         }
         if (_name.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.NAME, _name.getValue());
         }
         if (_type.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.TYPE, _type.getValue());
         }
         if (_status.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.STATUS, _status.getValue());
         }
         if (_parentReferenceFrame.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.PARENT_REFERENCE_FRAME, _parentReferenceFrame.getValue());
         }
         if (_state.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.STATE, _state.getValue());
         }
         if (_acceleration.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.ACCELERATION, _acceleration.getValue());
         }
         if (_rotationalAcceleration.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.ROTATIONAL_ACCELERATION, _rotationalAcceleration.getValue());
         }
         if (_centerOfMass.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.CENTER_OF_MASS, _centerOfMass.getValue());
         }
         if (_bodyWrtStructural.hasValue()) {
            attributeUpdates.put(HlaPayloadAttributes.Attribute.BODY_WRT_STRUCTURAL, _bodyWrtStructural.getValue());
         }
      }

      _instance.applyUpdate(attributeUpdates, sendAttributes, timestamp, logicalTime);
   }
}
