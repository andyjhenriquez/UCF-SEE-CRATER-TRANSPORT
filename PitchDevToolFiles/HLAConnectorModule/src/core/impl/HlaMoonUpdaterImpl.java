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

import core.datatypes.SpaceTimeCoordinateState;
import core.HlaMoonUpdater;
import core.HlaMoonListener;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.AttributeValue;
import core.HlaMoonAttributes; 

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.concurrent.atomic.AtomicBoolean;


/* @ThreadSafe */
final class HlaMoonUpdaterImpl implements HlaMoonUpdater {
   private final AtomicBoolean _updateSent = new AtomicBoolean(false);
   private final Object _attributesLock = new Object();

   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _name = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _parentName = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<SpaceTimeCoordinateState> _state = new AttributeValue<SpaceTimeCoordinateState>();

   private final HlaMoonImpl _instance;


   HlaMoonUpdaterImpl(HlaMoonImpl instance) {
      _instance = instance;
   }

   public HlaMoonUpdaterImpl setName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _name.setValueFromUser(value);
      }
      return this;
   }

   public HlaMoonUpdaterImpl setParentName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _parentName.setValueFromUser(value);
      }
      return this;
   }

   public HlaMoonUpdaterImpl setState(SpaceTimeCoordinateState value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _state.setValueFromUser(value);
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

      EnumMap<HlaMoonAttributes.Attribute, Object> attributeUpdates =
            new EnumMap<HlaMoonAttributes.Attribute, Object>(HlaMoonAttributes.Attribute.class);
      EnumSet<HlaMoonAttributes.Attribute> sendAttributes = EnumSet.noneOf(HlaMoonAttributes.Attribute.class);

      synchronized (_attributesLock) {
         if (_name.hasValue()) {
            attributeUpdates.put(HlaMoonAttributes.Attribute.NAME, _name.getValue());
         }
         if (_parentName.hasValue()) {
            attributeUpdates.put(HlaMoonAttributes.Attribute.PARENT_NAME, _parentName.getValue());
         }
         if (_state.hasValue()) {
            attributeUpdates.put(HlaMoonAttributes.Attribute.STATE, _state.getValue());
         }
      }

      _instance.applyUpdate(attributeUpdates, sendAttributes, timestamp, logicalTime);
   }
}
