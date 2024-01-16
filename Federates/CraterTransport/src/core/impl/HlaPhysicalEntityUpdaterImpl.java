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
import core.HlaPhysicalEntityUpdater;
import core.HlaPhysicalEntityListener;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.AttributeValue;
import core.HlaPhysicalEntityAttributes; 

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.concurrent.atomic.AtomicBoolean;


/* @ThreadSafe */
final class HlaPhysicalEntityUpdaterImpl implements HlaPhysicalEntityUpdater {
   private final AtomicBoolean _updateSent = new AtomicBoolean(false);
   private final Object _attributesLock = new Object();

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

   private final HlaPhysicalEntityImpl _instance;


   HlaPhysicalEntityUpdaterImpl(HlaPhysicalEntityImpl instance) {
      _instance = instance;
   }

   public HlaPhysicalEntityUpdaterImpl setName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _name.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setType(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _type.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setStatus(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _status.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setParentReferenceFrame(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _parentReferenceFrame.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setState(SpaceTimeCoordinateState value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _state.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setAcceleration(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _acceleration.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setRotationalAcceleration(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _rotationalAcceleration.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setCenterOfMass(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _centerOfMass.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalEntityUpdaterImpl setBodyWrtStructural(AttitudeQuaternion value) {
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

      EnumMap<HlaPhysicalEntityAttributes.Attribute, Object> attributeUpdates =
            new EnumMap<HlaPhysicalEntityAttributes.Attribute, Object>(HlaPhysicalEntityAttributes.Attribute.class);
      EnumSet<HlaPhysicalEntityAttributes.Attribute> sendAttributes = EnumSet.noneOf(HlaPhysicalEntityAttributes.Attribute.class);

      synchronized (_attributesLock) {
         if (_name.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.NAME, _name.getValue());
         }
         if (_type.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.TYPE, _type.getValue());
         }
         if (_status.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.STATUS, _status.getValue());
         }
         if (_parentReferenceFrame.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.PARENT_REFERENCE_FRAME, _parentReferenceFrame.getValue());
         }
         if (_state.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.STATE, _state.getValue());
         }
         if (_acceleration.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.ACCELERATION, _acceleration.getValue());
         }
         if (_rotationalAcceleration.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.ROTATIONAL_ACCELERATION, _rotationalAcceleration.getValue());
         }
         if (_centerOfMass.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.CENTER_OF_MASS, _centerOfMass.getValue());
         }
         if (_bodyWrtStructural.hasValue()) {
            attributeUpdates.put(HlaPhysicalEntityAttributes.Attribute.BODY_WRT_STRUCTURAL, _bodyWrtStructural.getValue());
         }
      }

      _instance.applyUpdate(attributeUpdates, sendAttributes, timestamp, logicalTime);
   }
}
