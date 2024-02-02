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
import core.HlaLauncherUpdater;
import core.HlaLauncherListener;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.AttributeValue;
import core.HlaLauncherAttributes; 

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.concurrent.atomic.AtomicBoolean;


/* @ThreadSafe */
final class HlaLauncherUpdaterImpl implements HlaLauncherUpdater {
   private final AtomicBoolean _updateSent = new AtomicBoolean(false);
   private final Object _attributesLock = new Object();

   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _position = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _mass = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _energy = new AttributeValue<Double>();
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

   private final HlaLauncherImpl _instance;


   HlaLauncherUpdaterImpl(HlaLauncherImpl instance) {
      _instance = instance;
   }

   public HlaLauncherUpdaterImpl setPosition(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _position.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setMass(double value) {
      synchronized (_attributesLock) {
         _mass.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setEnergy(double value) {
      synchronized (_attributesLock) {
         _energy.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _name.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setType(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _type.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setStatus(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _status.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setParentReferenceFrame(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _parentReferenceFrame.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setState(SpaceTimeCoordinateState value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _state.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setAcceleration(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _acceleration.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setRotationalAcceleration(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _rotationalAcceleration.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setCenterOfMass(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _centerOfMass.setValueFromUser(value);
      }
      return this;
   }

   public HlaLauncherUpdaterImpl setBodyWrtStructural(AttitudeQuaternion value) {
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

      EnumMap<HlaLauncherAttributes.Attribute, Object> attributeUpdates =
            new EnumMap<HlaLauncherAttributes.Attribute, Object>(HlaLauncherAttributes.Attribute.class);
      EnumSet<HlaLauncherAttributes.Attribute> sendAttributes = EnumSet.noneOf(HlaLauncherAttributes.Attribute.class);

      synchronized (_attributesLock) {
         if (_position.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.POSITION, _position.getValue());
         }
         if (_mass.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.MASS, _mass.getValue());
         }
         if (_energy.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.ENERGY, _energy.getValue());
         }
         if (_name.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.NAME, _name.getValue());
         }
         if (_type.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.TYPE, _type.getValue());
         }
         if (_status.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.STATUS, _status.getValue());
         }
         if (_parentReferenceFrame.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.PARENT_REFERENCE_FRAME, _parentReferenceFrame.getValue());
         }
         if (_state.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.STATE, _state.getValue());
         }
         if (_acceleration.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.ACCELERATION, _acceleration.getValue());
         }
         if (_rotationalAcceleration.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.ROTATIONAL_ACCELERATION, _rotationalAcceleration.getValue());
         }
         if (_centerOfMass.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.CENTER_OF_MASS, _centerOfMass.getValue());
         }
         if (_bodyWrtStructural.hasValue()) {
            attributeUpdates.put(HlaLauncherAttributes.Attribute.BODY_WRT_STRUCTURAL, _bodyWrtStructural.getValue());
         }
      }

      _instance.applyUpdate(attributeUpdates, sendAttributes, timestamp, logicalTime);
   }
}
