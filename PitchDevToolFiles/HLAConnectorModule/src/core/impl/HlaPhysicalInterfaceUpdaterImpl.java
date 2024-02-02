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
import core.HlaPhysicalInterfaceUpdater;
import core.HlaPhysicalInterfaceListener;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.AttributeValue;
import core.HlaPhysicalInterfaceAttributes; 

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.concurrent.atomic.AtomicBoolean;


/* @ThreadSafe */
final class HlaPhysicalInterfaceUpdaterImpl implements HlaPhysicalInterfaceUpdater {
   private final AtomicBoolean _updateSent = new AtomicBoolean(false);
   private final Object _attributesLock = new Object();

   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _name = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _parentName = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _position = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<AttitudeQuaternion> _attitude = new AttributeValue<AttitudeQuaternion>();

   private final HlaPhysicalInterfaceImpl _instance;


   HlaPhysicalInterfaceUpdaterImpl(HlaPhysicalInterfaceImpl instance) {
      _instance = instance;
   }

   public HlaPhysicalInterfaceUpdaterImpl setName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _name.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalInterfaceUpdaterImpl setParentName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _parentName.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalInterfaceUpdaterImpl setPosition(double[/* 3 */] value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _position.setValueFromUser(value);
      }
      return this;
   }

   public HlaPhysicalInterfaceUpdaterImpl setAttitude(AttitudeQuaternion value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _attitude.setValueFromUser(value);
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

      EnumMap<HlaPhysicalInterfaceAttributes.Attribute, Object> attributeUpdates =
            new EnumMap<HlaPhysicalInterfaceAttributes.Attribute, Object>(HlaPhysicalInterfaceAttributes.Attribute.class);
      EnumSet<HlaPhysicalInterfaceAttributes.Attribute> sendAttributes = EnumSet.noneOf(HlaPhysicalInterfaceAttributes.Attribute.class);

      synchronized (_attributesLock) {
         if (_name.hasValue()) {
            attributeUpdates.put(HlaPhysicalInterfaceAttributes.Attribute.NAME, _name.getValue());
         }
         if (_parentName.hasValue()) {
            attributeUpdates.put(HlaPhysicalInterfaceAttributes.Attribute.PARENT_NAME, _parentName.getValue());
         }
         if (_position.hasValue()) {
            attributeUpdates.put(HlaPhysicalInterfaceAttributes.Attribute.POSITION, _position.getValue());
         }
         if (_attitude.hasValue()) {
            attributeUpdates.put(HlaPhysicalInterfaceAttributes.Attribute.ATTITUDE, _attitude.getValue());
         }
      }

      _instance.applyUpdate(attributeUpdates, sendAttributes, timestamp, logicalTime);
   }
}
