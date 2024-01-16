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

import core.datatypes.MTRMode;
import core.impl.encoders.MTRModeEncoder;
import core.*;
import core.datatypes.ToStringBuilder;
import core.exceptions.*;
import core.impl.fed.AbstractInteractionClassManager;
import core.impl.fed.FederateInteractionManager;
import core.impl.utils.*;

import se.pitch.ral.api.InteractionClassHandle;

import java.util.*;
import java.util.concurrent.CopyOnWriteArraySet;


/* @ThreadSafe */
final class HlaInteractionManagerImpl extends AbstractInteractionClassManager implements HlaInteractionManager {

   /* @GuardedBy("this") */
   private final MTRModeEncoder _mTRModeEncoderEncoder = new MTRModeEncoder();
   private final MTRModeEncoder _mTRModeEncoderDecoder = new MTRModeEncoder();


   public class HlaHLAinteractionRootInteractionImpl implements HlaHLAinteractionRootInteraction {
      private final Object _lock = new Object();


      public void sendInteraction() throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendHLAinteractionRootParams(null);
      }

      public void sendInteraction(HlaTimeStamp timestamp) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendHLAinteractionRootParams(timestamp);
      }

      public void sendInteraction(HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendHLAinteractionRootParams(null, logicalTime);
      }

      public void sendInteraction(HlaTimeStamp timestamp, HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendHLAinteractionRootParams(timestamp, logicalTime);
      }
   }

   public HlaHLAinteractionRootInteractionImpl getHlaHLAinteractionRootInteraction() {
      return new HlaHLAinteractionRootInteractionImpl();
   }


   public class HlaStartStopInteractionImpl implements HlaStartStopInteraction {
      private final Object _lock = new Object();


      public void sendInteraction() throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendStartStopParams(null);
      }

      public void sendInteraction(HlaTimeStamp timestamp) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendStartStopParams(timestamp);
      }

      public void sendInteraction(HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendStartStopParams(null, logicalTime);
      }

      public void sendInteraction(HlaTimeStamp timestamp, HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendStartStopParams(timestamp, logicalTime);
      }
   }

   public HlaStartStopInteractionImpl getHlaStartStopInteraction() {
      return new HlaStartStopInteractionImpl();
   }

   private static final class HlaModeTransitionRequestParametersImpl implements HlaModeTransitionRequestParameters {
      private final ParameterValue<MTRMode> _executionMode;
      private final HlaFederateId _producingFederate;
      private final boolean _isWithinInterest;

      private HlaModeTransitionRequestParametersImpl(
         ParameterValue<MTRMode> executionMode,
         HlaFederateId producingFederate,
         boolean isWithinInterest
      ) {
         _executionMode = new ParameterValue<MTRMode>(executionMode);
         _producingFederate = producingFederate;
         _isWithinInterest = isWithinInterest;
      }

      public boolean hasExecution_mode() {
         return _executionMode.hasValue();
      }

      public MTRMode getExecution_mode() throws HlaValueNotSetException {
         if (_executionMode.hasValue()) {
            return _executionMode.getValue();
         }
         throw new HlaValueNotSetException("Parameter 'executionMode' not set");
      }

      public MTRMode getExecution_mode(MTRMode defaultValue) {
         if (_executionMode.hasValue()) {
            return _executionMode.getValue();
         }
         return defaultValue;
      }

      @Override
      public HlaFederateId getProducingFederate() {
         return _producingFederate;
      }

      @Override
      public boolean isWithinInterest() {
         return _isWithinInterest;
      }

      @Override
      public String toString() {
         ToStringBuilder sb = new ToStringBuilder("HlaModeTransitionRequestParameters");
         if (hasExecution_mode()) {
            sb.append("execution_mode", getExecution_mode());
         }
         return sb.getToString();
      }
   }

   public class HlaModeTransitionRequestInteractionImpl implements HlaModeTransitionRequestInteraction {
      private final Object _lock = new Object();
      /* @GuardedBy("_lock") */
      private final ParameterValue<MTRMode> _executionMode;

      private HlaModeTransitionRequestInteractionImpl() {
         _executionMode = new ParameterValue<MTRMode>();
      }

      public HlaModeTransitionRequestParametersImpl build(HlaFederateId producingFederate) {
         synchronized (_lock) {
            return new HlaModeTransitionRequestParametersImpl(
               _executionMode,
               producingFederate,
               true
            );
         }
      }

      private HlaModeTransitionRequestParametersImpl build() {
         return build(HlaInteractionManagerImpl.this._hlaWorld.getFederateId());
      }

      public HlaModeTransitionRequestInteractionImpl setExecution_mode(MTRMode value) {
         if (value == null) {
            throw new NullPointerException();
         }
         synchronized (_lock) {
            _executionMode.setValueFromUser(value);
         }
         return this;
      }

      public void sendInteraction() throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendModeTransitionRequestParams(build(), null);
      }

      public void sendInteraction(HlaTimeStamp timestamp) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendModeTransitionRequestParams(build(), timestamp);
      }

      public void sendInteraction(HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendModeTransitionRequestParams(build(), null, logicalTime);
      }

      public void sendInteraction(HlaTimeStamp timestamp, HlaLogicalTime logicalTime) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
         HlaInteractionManagerImpl.this.sendModeTransitionRequestParams(build(), timestamp, logicalTime);
      }
   }

   public HlaModeTransitionRequestInteractionImpl getHlaModeTransitionRequestInteraction() {
      return new HlaModeTransitionRequestInteractionImpl();
   }

   private static class InteractionInfo {
      private final boolean _local;
      private final boolean _remote;

      public InteractionInfo(boolean local, boolean remote) {
         _local = local;
         _remote = remote;
      }

      public boolean isLocal() {
         return _local;
      }

      public boolean isRemote() {
         return _remote;
      }
   }

   private static final String HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME = "HLAinteractionRoot";
   private static final String START_STOP_INTERACTION_CLASS_NAME = "HLAinteractionRoot.Start_Stop";
   private static final String MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME = "HLAinteractionRoot.ModeTransitionRequest";

   private static final Map<String, InteractionInfo> INTERACTIONS = new MapAdapter<String, InteractionInfo>()
         .append(HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME, new InteractionInfo(true, true))
         .append(START_STOP_INTERACTION_CLASS_NAME, new InteractionInfo(true, true))
         .append(MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME, new InteractionInfo(true, true))
         .unmodifiableMap();


   private final FederateInteractionManager _interactionManager;
   private final HlaWorldImpl _hlaWorld;

   private final DualMap<String, InteractionClassHandle> _interactions =
      new DualMap<String, InteractionClassHandle>(3);

   private final Set<HlaInteractionListener> _listeners = new CopyOnWriteArraySet<HlaInteractionListener>();
   private final Set<Interaction> _enabled = EnumSet.allOf(Interaction.class);
   private final Set<Interaction> _optional = EnumSet.noneOf(Interaction.class);


   HlaInteractionManagerImpl(FederateInteractionManager interactionManager, HlaWorldImpl hlaWorld) {
      _interactionManager = interactionManager;
      _hlaWorld = hlaWorld;

      for (String name : INTERACTIONS.keySet()) {
         _interactionManager.addManager(this, name);
      }
   }

   /*
    * HlaInteractionManager interface impl
    */


   public void sendHLAinteractionRoot(
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaHLAinteractionRootInteractionImpl interaction = getHlaHLAinteractionRootInteraction();
      interaction.sendInteraction();
   }

   public void sendHLAinteractionRoot(
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaHLAinteractionRootInteractionImpl interaction = getHlaHLAinteractionRootInteraction();
      interaction.sendInteraction(timeStamp);
   }

   public void sendHLAinteractionRoot(
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaHLAinteractionRootInteractionImpl interaction = getHlaHLAinteractionRootInteraction();
      interaction.sendInteraction(logicalTime);
   }

   public void sendHLAinteractionRoot(
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaHLAinteractionRootInteractionImpl interaction = getHlaHLAinteractionRootInteraction();
      interaction.sendInteraction(timeStamp, logicalTime);
   }

   public void sendHLAinteractionRootParams(
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
   try {
         sendHLAinteractionRootParams(
            timeStamp,
            null
         );
      } catch (HlaInvalidLogicalTimeException e) {
         //can not happen with null logicalTime
      }
   }

   public void sendHLAinteractionRootParams(
      HlaTimeStamp timestamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      InteractionClassHandle handle = _interactions.get(HLAINTERACTION_ROOT_INTERACTION_CLASS_NAME);

      if (handle == null) {
         throw new HlaNotConnectedException("Not connected");
      }

      HlaTimeStamp hlaTimeStamp = timestamp != null ? timestamp : _hlaWorld.getCurrentTime();
      HlaLogicalTime hlaLogicalTime = logicalTime != null ? logicalTime : _hlaWorld.getDefaultSendTime();
      NameValueMap nameValueMap = new NameValueMap(0);
      synchronized (this) {
      }

      _interactionManager.sendInteraction(handle, nameValueMap, hlaTimeStamp, hlaLogicalTime);

      fireHLAinteractionRootInteraction(
         true,
         hlaTimeStamp,
         hlaLogicalTime
      );
   }


   public void sendStartStop(
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaStartStopInteractionImpl interaction = getHlaStartStopInteraction();
      interaction.sendInteraction();
   }

   public void sendStartStop(
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaStartStopInteractionImpl interaction = getHlaStartStopInteraction();
      interaction.sendInteraction(timeStamp);
   }

   public void sendStartStop(
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaStartStopInteractionImpl interaction = getHlaStartStopInteraction();
      interaction.sendInteraction(logicalTime);
   }

   public void sendStartStop(
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaStartStopInteractionImpl interaction = getHlaStartStopInteraction();
      interaction.sendInteraction(timeStamp, logicalTime);
   }

   public void sendStartStopParams(
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
   try {
         sendStartStopParams(
            timeStamp,
            null
         );
      } catch (HlaInvalidLogicalTimeException e) {
         //can not happen with null logicalTime
      }
   }

   public void sendStartStopParams(
      HlaTimeStamp timestamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      InteractionClassHandle handle = _interactions.get(START_STOP_INTERACTION_CLASS_NAME);

      if (handle == null) {
         throw new HlaNotConnectedException("Not connected");
      }

      HlaTimeStamp hlaTimeStamp = timestamp != null ? timestamp : _hlaWorld.getCurrentTime();
      HlaLogicalTime hlaLogicalTime = logicalTime != null ? logicalTime : _hlaWorld.getDefaultSendTime();
      NameValueMap nameValueMap = new NameValueMap(0);
      synchronized (this) {
      }

      _interactionManager.sendInteraction(handle, nameValueMap, hlaTimeStamp, hlaLogicalTime);

      fireStartStopInteraction(
         true,
         hlaTimeStamp,
         hlaLogicalTime
      );
   }


   public void sendModeTransitionRequest(
      MTRMode executionMode
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaModeTransitionRequestInteractionImpl interaction = getHlaModeTransitionRequestInteraction();
      interaction.setExecution_mode(executionMode);
      interaction.sendInteraction();
   }

   public void sendModeTransitionRequest(
      MTRMode executionMode,
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaModeTransitionRequestInteractionImpl interaction = getHlaModeTransitionRequestInteraction();
      interaction.setExecution_mode(executionMode);
      interaction.sendInteraction(timeStamp);
   }

   public void sendModeTransitionRequest(
      MTRMode executionMode,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaModeTransitionRequestInteractionImpl interaction = getHlaModeTransitionRequestInteraction();
      interaction.setExecution_mode(executionMode);
      interaction.sendInteraction(logicalTime);
   }

   public void sendModeTransitionRequest(
      MTRMode executionMode,
      HlaTimeStamp timeStamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      HlaModeTransitionRequestInteractionImpl interaction = getHlaModeTransitionRequestInteraction();
      interaction.setExecution_mode(executionMode);
      interaction.sendInteraction(timeStamp, logicalTime);
   }

   public void sendModeTransitionRequestParams(
      HlaModeTransitionRequestParameters parameters,
      HlaTimeStamp timeStamp
   ) throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
   try {
         sendModeTransitionRequestParams(
            parameters,
            timeStamp,
            null
         );
      } catch (HlaInvalidLogicalTimeException e) {
         //can not happen with null logicalTime
      }
   }

   public void sendModeTransitionRequestParams(
      HlaModeTransitionRequestParameters parameters,
      HlaTimeStamp timestamp,
      HlaLogicalTime logicalTime
   ) throws HlaNotConnectedException, HlaFomException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      InteractionClassHandle handle = _interactions.get(MODE_TRANSITION_REQUEST_INTERACTION_CLASS_NAME);

      if (handle == null) {
         throw new HlaNotConnectedException("Not connected");
      }

      HlaTimeStamp hlaTimeStamp = timestamp != null ? timestamp : _hlaWorld.getCurrentTime();
      HlaLogicalTime hlaLogicalTime = logicalTime != null ? logicalTime : _hlaWorld.getDefaultSendTime();
      NameValueMap nameValueMap = new NameValueMap(1);
      synchronized (this) {
         if (parameters.hasExecution_mode()) {
            try {
               _mTRModeEncoderEncoder.setValue(parameters.getExecution_mode());
               nameValueMap.put("execution_mode",
                                _mTRModeEncoderEncoder.toByteArray(),
                                false);
            } catch (Throwable t) {
               _hlaWorld.postException(new HlaDecodeException("Failed to encode execution_mode", t));
            }
         }
      }

      _interactionManager.sendInteraction(handle, nameValueMap, hlaTimeStamp, hlaLogicalTime);

      fireModeTransitionRequestInteraction(
         true,
         parameters,
         hlaTimeStamp,
         hlaLogicalTime
      );
   }

   public void addHlaInteractionListener(HlaInteractionListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.add(listener);
   }

   public void removeHlaInteractionListener(HlaInteractionListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.remove(listener);
   }


   public void setEnabled(boolean enabled, Interaction interaction) {
      setEnabled(enabled, EnumSet.of(interaction));
   }

   public void setEnabled(boolean enabled, Set<Interaction> interactions) {
      _optional.removeAll(interactions);
      if (enabled) {
         _enabled.addAll(interactions);
      } else {
         _enabled.removeAll(interactions);
      }
   }

   public void setEnabledIfAvailableInFom(Set<Interaction> interactions) {
      _optional.addAll(interactions);
      _enabled.addAll(interactions);
   }

   public boolean isEnabled(Interaction interaction) {
      return _interactions.get(interaction.getHlaName()) != null;
   }

   /*
    * AbstractInteractionClassManager impl
    */

   @Override
   public void receiveInteraction(InteractionClassHandle interactionClassHandle, NameValueMap parameters, HlaTimeStamp hlaTimeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      String interactionName = _interactions.getByValue(interactionClassHandle);
      if (interactionName == null) {
         _hlaWorld.postException(new HlaInternalException("Received unknown interaction: " + interactionClassHandle));
         return;
      }

      Interaction interaction = Interaction.find(interactionName);
      if (interaction == null) {
         _hlaWorld.postException(new HlaInternalException("Received unknown interaction: " + interactionName));
         return;
      }

      switch (interaction) {
         case HLAINTERACTION_ROOT: {
            receiveHLAinteractionRoot(parameters, hlaTimeStamp, logicalTime, producingFederate);
            return;
         }
         case START_STOP: {
            receiveStartStop(parameters, hlaTimeStamp, logicalTime, producingFederate);
            return;
         }
         case MODE_TRANSITION_REQUEST: {
            receiveModeTransitionRequest(parameters, hlaTimeStamp, logicalTime, producingFederate);
            return;
         }
      }
      _hlaWorld.postException(new HlaInternalException("Received unknown interaction: " + interactionName));
   }

   @Override
   public boolean isEnabled(String interactionClassName) {
      Interaction interaction = Interaction.find(interactionClassName);
      return interaction != null && _enabled.contains(interaction);
   }

   @Override
   public boolean isOptional(String interactionClassName) {
      Interaction interaction = Interaction.find(interactionClassName);
      return interaction != null && _optional.contains(interaction);
   }

   @Override
   public void connected(InteractionClassHandle interactionClassHandle, String interactionClassName)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      _interactions.put(interactionClassName, interactionClassHandle);

      InteractionInfo interactionInfo = INTERACTIONS.get(interactionClassName);
      if (interactionInfo == null) {
         return;
      }

      if (interactionInfo.isLocal()) {
         _interactionManager.publish(interactionClassHandle);
      }

      if (interactionInfo.isRemote()) {
         _interactionManager.subscribe(interactionClassHandle);
      }
   }

   @Override
   public void disconnected(InteractionClassHandle interactionClassHandle) {
      _interactions.removeByValue(interactionClassHandle);
   }


   /*
    * Private functions
    */

   private void receiveHLAinteractionRoot(NameValueMap parameters, HlaTimeStamp hlaTimeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      byte[] interactionData;
      fireHLAinteractionRootInteraction(
         false,
         hlaTimeStamp,
         logicalTime
      );
   }

   private void receiveStartStop(NameValueMap parameters, HlaTimeStamp hlaTimeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      byte[] interactionData;
      fireStartStopInteraction(
         false,
         hlaTimeStamp,
         logicalTime
      );
   }

   private void receiveModeTransitionRequest(NameValueMap parameters, HlaTimeStamp hlaTimeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      HlaModeTransitionRequestInteractionImpl interaction = getHlaModeTransitionRequestInteraction();
      byte[] interactionData;
      interactionData = parameters.get("execution_mode");
      if (interactionData != null) {
         try {
            _mTRModeEncoderDecoder.decode(interactionData);
            interaction.setExecution_mode(_mTRModeEncoderDecoder.getValue());

            if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _mTRModeEncoderDecoder.getEncodedLength() != interactionData.length) {
               _hlaWorld.postException(
                  new HlaDecodeException("Failed to decode execution_mode. " +
                                         "Invalid data length " + interactionData.length + ", expected " + _mTRModeEncoderDecoder.getEncodedLength(),
                                         interactionData));
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode execution_mode", interactionData, t));
         }
      }

      fireModeTransitionRequestInteraction(
         false,
         interaction.build(producingFederate),
         hlaTimeStamp,
         logicalTime
      );
   }


   private void fireHLAinteractionRootInteraction(
      final boolean local,
      final HlaTimeStamp hlaTimeStamp,
      final HlaLogicalTime hlaLogicalTime
   ) {
      for (final HlaInteractionListener listener : _listeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               listener.hLAinteractionRoot(
                  local,
                  hlaTimeStamp,
                  hlaLogicalTime
               );
            }
         });
      }
   }

   private void fireStartStopInteraction(
      final boolean local,
      final HlaTimeStamp hlaTimeStamp,
      final HlaLogicalTime hlaLogicalTime
   ) {
      for (final HlaInteractionListener listener : _listeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               listener.startStop(
                  local,
                  hlaTimeStamp,
                  hlaLogicalTime
               );
            }
         });
      }
   }

   private void fireModeTransitionRequestInteraction(
      final boolean local,
      final HlaModeTransitionRequestParameters parameters,
      final HlaTimeStamp hlaTimeStamp,
      final HlaLogicalTime hlaLogicalTime
   ) {
      for (final HlaInteractionListener listener : _listeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               listener.modeTransitionRequest(
                  local,
                  parameters,
                  hlaTimeStamp,
                  hlaLogicalTime
               );
            }
         });
      }
   }

}
