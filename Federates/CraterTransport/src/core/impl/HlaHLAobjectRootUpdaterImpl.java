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

import core.HlaHLAobjectRootUpdater;
import core.HlaHLAobjectRootListener;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.AttributeValue;
import core.HlaHLAobjectRootAttributes; 

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.concurrent.atomic.AtomicBoolean;


/* @ThreadSafe */
final class HlaHLAobjectRootUpdaterImpl implements HlaHLAobjectRootUpdater {
   private final AtomicBoolean _updateSent = new AtomicBoolean(false);
   private final Object _attributesLock = new Object();


   private final HlaHLAobjectRootImpl _instance;


   HlaHLAobjectRootUpdaterImpl(HlaHLAobjectRootImpl instance) {
      _instance = instance;
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

      EnumMap<HlaHLAobjectRootAttributes.Attribute, Object> attributeUpdates =
            new EnumMap<HlaHLAobjectRootAttributes.Attribute, Object>(HlaHLAobjectRootAttributes.Attribute.class);
      EnumSet<HlaHLAobjectRootAttributes.Attribute> sendAttributes = EnumSet.noneOf(HlaHLAobjectRootAttributes.Attribute.class);

      synchronized (_attributesLock) {
      }

      _instance.applyUpdate(attributeUpdates, sendAttributes, timestamp, logicalTime);
   }
}
