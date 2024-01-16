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

import core.datatypes.ExecutionMode;
import core.HlaExecutionConfigurationUpdater;
import core.HlaExecutionConfigurationListener;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.exceptions.*;
import core.impl.utils.AttributeValue;
import core.HlaExecutionConfigurationAttributes; 

import java.util.EnumMap;
import java.util.EnumSet;
import java.util.concurrent.atomic.AtomicBoolean;


/* @ThreadSafe */
final class HlaExecutionConfigurationUpdaterImpl implements HlaExecutionConfigurationUpdater {
   private final AtomicBoolean _updateSent = new AtomicBoolean(false);
   private final Object _attributesLock = new Object();

   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _rootFrameName = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _scenarioTimeEpoch = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<ExecutionMode> _currentExecutionMode = new AttributeValue<ExecutionMode>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<ExecutionMode> _nextExecutionMode = new AttributeValue<ExecutionMode>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _nextModeScenarioTime = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _nextModeCteTime = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Long> _leastCommonTimeStep = new AttributeValue<Long>();

   private final HlaExecutionConfigurationImpl _instance;


   HlaExecutionConfigurationUpdaterImpl(HlaExecutionConfigurationImpl instance) {
      _instance = instance;
   }

   public HlaExecutionConfigurationUpdaterImpl setRootFrameName(String value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _rootFrameName.setValueFromUser(value);
      }
      return this;
   }

   public HlaExecutionConfigurationUpdaterImpl setScenarioTimeEpoch(double value) {
      synchronized (_attributesLock) {
         _scenarioTimeEpoch.setValueFromUser(value);
      }
      return this;
   }

   public HlaExecutionConfigurationUpdaterImpl setCurrentExecutionMode(ExecutionMode value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _currentExecutionMode.setValueFromUser(value);
      }
      return this;
   }

   public HlaExecutionConfigurationUpdaterImpl setNextExecutionMode(ExecutionMode value) {
      if (value == null) {
         throw new NullPointerException();
      }
      synchronized (_attributesLock) {
         _nextExecutionMode.setValueFromUser(value);
      }
      return this;
   }

   public HlaExecutionConfigurationUpdaterImpl setNextModeScenarioTime(double value) {
      synchronized (_attributesLock) {
         _nextModeScenarioTime.setValueFromUser(value);
      }
      return this;
   }

   public HlaExecutionConfigurationUpdaterImpl setNextModeCteTime(double value) {
      synchronized (_attributesLock) {
         _nextModeCteTime.setValueFromUser(value);
      }
      return this;
   }

   public HlaExecutionConfigurationUpdaterImpl setLeastCommonTimeStep(long value) {
      synchronized (_attributesLock) {
         _leastCommonTimeStep.setValueFromUser(value);
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

      EnumMap<HlaExecutionConfigurationAttributes.Attribute, Object> attributeUpdates =
            new EnumMap<HlaExecutionConfigurationAttributes.Attribute, Object>(HlaExecutionConfigurationAttributes.Attribute.class);
      EnumSet<HlaExecutionConfigurationAttributes.Attribute> sendAttributes = EnumSet.noneOf(HlaExecutionConfigurationAttributes.Attribute.class);

      synchronized (_attributesLock) {
         if (_rootFrameName.hasValue()) {
            attributeUpdates.put(HlaExecutionConfigurationAttributes.Attribute.ROOT_FRAME_NAME, _rootFrameName.getValue());
         }
         if (_scenarioTimeEpoch.hasValue()) {
            attributeUpdates.put(HlaExecutionConfigurationAttributes.Attribute.SCENARIO_TIME_EPOCH, _scenarioTimeEpoch.getValue());
         }
         if (_currentExecutionMode.hasValue()) {
            attributeUpdates.put(HlaExecutionConfigurationAttributes.Attribute.CURRENT_EXECUTION_MODE, _currentExecutionMode.getValue());
         }
         if (_nextExecutionMode.hasValue()) {
            attributeUpdates.put(HlaExecutionConfigurationAttributes.Attribute.NEXT_EXECUTION_MODE, _nextExecutionMode.getValue());
         }
         if (_nextModeScenarioTime.hasValue()) {
            attributeUpdates.put(HlaExecutionConfigurationAttributes.Attribute.NEXT_MODE_SCENARIO_TIME, _nextModeScenarioTime.getValue());
         }
         if (_nextModeCteTime.hasValue()) {
            attributeUpdates.put(HlaExecutionConfigurationAttributes.Attribute.NEXT_MODE_CTE_TIME, _nextModeCteTime.getValue());
         }
         if (_leastCommonTimeStep.hasValue()) {
            attributeUpdates.put(HlaExecutionConfigurationAttributes.Attribute.LEAST_COMMON_TIME_STEP, _leastCommonTimeStep.getValue());
         }
      }

      _instance.applyUpdate(attributeUpdates, sendAttributes, timestamp, logicalTime);
   }
}
