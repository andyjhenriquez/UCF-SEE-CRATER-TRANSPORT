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

import core.impl.encoders.*;
import se.pitch.encoders1516.HLAfloat64LE;
import se.pitch.encoders1516.HLAunicodeString;
import core.*;
import core.exceptions.*;
import core.impl.fed.AbstractObjectClassManager;
import core.impl.fed.ObjectManager;
import core.impl.utils.*;

import se.pitch.ral.api.ObjectInstanceHandle;
import se.pitch.ral.api.ObjectClassHandle;

import java.nio.ByteBuffer;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.CopyOnWriteArraySet;


/* @ThreadSafe */
final class HlaPayloadManagerImpl extends AbstractObjectClassManager implements HlaPayloadManager {

   private static final String HLA_OBJECT_CLASS_NAME = "HLAobjectRoot.PhysicalEntity.DynamicalEntity.Payload";

   private final ObjectManager _objectManager;
   private final HlaWorldImpl _worldImpl;
   private final Object _localCreationInProgressLock = new Object();

   private volatile boolean _enabled = true;
   private volatile boolean _optional = false;
   private ObjectClassHandle _objectClassHandle = null;

   private final Map<String, HlaPayloadImpl> _hlaInstanceNameMap = new ConcurrentHashMap<String, HlaPayloadImpl>();
   private final Map<ByteBuffer, HlaPayloadImpl> _encodedHlaInstanceHandleMap = new ConcurrentHashMap<ByteBuffer, HlaPayloadImpl>();
   private final Map<ObjectInstanceHandle, HlaPayloadImpl> _localInstances =
         new ConcurrentHashMap<ObjectInstanceHandle, HlaPayloadImpl>();
   private final Map<ObjectInstanceHandle, HlaPayloadImpl> _remoteInstances =
         new ConcurrentHashMap<ObjectInstanceHandle, HlaPayloadImpl>();

   private final Set<HlaPayloadManagerListener> _listeners =
         new CopyOnWriteArraySet<HlaPayloadManagerListener>();

   private final Set<HlaPayloadValueListener> _defaultInstanceValueListeners =
         new CopyOnWriteArraySet<HlaPayloadValueListener>();
   private final Set<HlaPayloadListener> _defaultInstanceListeners =
         new CopyOnWriteArraySet<HlaPayloadListener>();

   /*
    * Share encoders and decoders for HlaPayloadImpl
    */
   protected final Object _encodersLock = new Object();
   protected final Object _decodersLock = new Object();
   /* @GuardedBy("_encodersLock") */
   protected final PositionVectorEncoder _positionVectorEncoderEncoder = new PositionVectorEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final PositionVectorEncoder _positionVectorEncoderDecoder = new PositionVectorEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final VelocityVectorEncoder _velocityVectorEncoderEncoder = new VelocityVectorEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final VelocityVectorEncoder _velocityVectorEncoderDecoder = new VelocityVectorEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final HLAfloat64LE _hLAfloat64LEEncoder = BaseEncoder.createHLAfloat64LE();
   /* @GuardedBy("_decodersLock") */
   protected final HLAfloat64LE _hLAfloat64LEDecoder = BaseEncoder.createHLAfloat64LE();
   /* @GuardedBy("_encodersLock") */
   protected final ForceVectorEncoder _forceVectorEncoderEncoder = new ForceVectorEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final ForceVectorEncoder _forceVectorEncoderDecoder = new ForceVectorEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final TorqueVectorEncoder _torqueVectorEncoderEncoder = new TorqueVectorEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final TorqueVectorEncoder _torqueVectorEncoderDecoder = new TorqueVectorEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final InertiaMatrixEncoder _inertiaMatrixEncoderEncoder = new InertiaMatrixEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final InertiaMatrixEncoder _inertiaMatrixEncoderDecoder = new InertiaMatrixEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final InertiaRateMatrixEncoder _inertiaRateMatrixEncoderEncoder = new InertiaRateMatrixEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final InertiaRateMatrixEncoder _inertiaRateMatrixEncoderDecoder = new InertiaRateMatrixEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final HLAunicodeString _hLAunicodeStringEncoder = BaseEncoder.createHLAunicodeString();
   /* @GuardedBy("_decodersLock") */
   protected final HLAunicodeString _hLAunicodeStringDecoder = BaseEncoder.createHLAunicodeString();
   /* @GuardedBy("_encodersLock") */
   protected final SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderEncoder = new SpaceTimeCoordinateStateEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final SpaceTimeCoordinateStateEncoder _spaceTimeCoordinateStateEncoderDecoder = new SpaceTimeCoordinateStateEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final AccelerationVectorEncoder _accelerationVectorEncoderEncoder = new AccelerationVectorEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final AccelerationVectorEncoder _accelerationVectorEncoderDecoder = new AccelerationVectorEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final AngularAccelerationVectorEncoder _angularAccelerationVectorEncoderEncoder = new AngularAccelerationVectorEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final AngularAccelerationVectorEncoder _angularAccelerationVectorEncoderDecoder = new AngularAccelerationVectorEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final AttitudeQuaternionEncoder _attitudeQuaternionEncoderEncoder = new AttitudeQuaternionEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final AttitudeQuaternionEncoder _attitudeQuaternionEncoderDecoder = new AttitudeQuaternionEncoder();

   HlaPayloadManagerImpl(HlaWorldImpl world, ObjectManager objectManager) {
      _objectManager = objectManager;
      _worldImpl = world;

      _objectManager.addManager(this, HLA_OBJECT_CLASS_NAME);
   }

   /*
    * HlaPayloadManager interface impl
    */

   public List<HlaPayload> getHlaPayloads() {
      return getAllHlaPayloads();
   }

   public List<HlaPayload> getAllHlaPayloads() {
      List<HlaPayload> list = new ArrayList<HlaPayload>(_localInstances.size() + _remoteInstances.size());
      list.addAll(_localInstances.values());
      list.addAll(_remoteInstances.values());
      return list;
   }

   public List<HlaPayload> getLocalHlaPayloads() {
      return new ArrayList<HlaPayload>(_localInstances.values());
   }

   public List<HlaPayload> getRemoteHlaPayloads() {
      return new ArrayList<HlaPayload>(_remoteInstances.values());
   }

   public HlaPayloadImpl getPayloadByHlaInstanceName(String hlaInstanceName) {
      return _hlaInstanceNameMap.get(hlaInstanceName);
   }

   public HlaPayload getPayloadByHlaInstanceHandle(byte[] encodedHlaInstanceHandle) {
      return _encodedHlaInstanceHandleMap.get(ByteBuffer.wrap(encodedHlaInstanceHandle));
   }

   public HlaPayload createLocalHlaPayload(
   ) throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      if (_objectClassHandle == null) {
         throw new HlaNotConnectedException("Not connected");
      }

      try {
         return createLocalInstance(
            null
         );
      } catch (HlaInstanceNameInUseException e) {
         //can not happen with null hlaInstanceName
         return null;
      }
   }


   public HlaPayload createLocalHlaPayload(
      String hlaInstanceName
   ) throws HlaIllegalInstanceNameException, HlaInstanceNameInUseException,
            HlaNotConnectedException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {
      if (_objectClassHandle == null) {
         throw new HlaNotConnectedException("Not connected");
      }

      //Silently ignore if we could not register object instance name, we might have registered it before
      _objectManager.registerObjectInstanceName(hlaInstanceName);

      return createLocalInstance(
         hlaInstanceName
      );
   }


   private HlaPayload createLocalInstance(
      String hlaInstanceName
   ) throws HlaInstanceNameInUseException, HlaNotConnectedException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {

      HlaPayloadImpl instance;
      synchronized (_localCreationInProgressLock) {
         ObjectInstanceHandle objectInstanceHandle = _objectManager.createObjectInstance(_objectClassHandle, hlaInstanceName);
         instance = createObjectInstance(objectInstanceHandle, true, _worldImpl.getFederateId());
         _localInstances.put(objectInstanceHandle, instance);
         _hlaInstanceNameMap.put(instance.getHlaInstanceName(), instance);
         _encodedHlaInstanceHandleMap.put(ByteBuffer.wrap(instance.getEncodedHlaObjectInstanceHandle()), instance);
      }

      HlaTimeStamp timeStamp = _worldImpl.getCurrentTime();
      fireDiscovered(instance, timeStamp);

      for (HlaPayloadListener instanceListener : _defaultInstanceListeners) {
         instance.addHlaPayloadListener(instanceListener);
      }
      for (HlaPayloadValueListener instanceValueListener : _defaultInstanceValueListeners) {
         instance.addHlaPayloadValueListener(instanceValueListener);
      }

      checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl.INVALID);

      return instance;
   }

   public HlaPayload deleteLocalHlaPayload(HlaPayload instance)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      try {
         return deleteHlaPayload(instance, _worldImpl.getCurrentTime(), _worldImpl.getDefaultSendTime(), true);
      } catch (HlaInvalidLogicalTimeException e) {
         throw new HlaInternalException("Failed to delete instance with default Logical Time", e);
      }
   }

   public HlaPayload deleteLocalHlaPayload(HlaPayload instance, HlaTimeStamp timestamp)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      try {
         return deleteHlaPayload(instance, timestamp, _worldImpl.getDefaultSendTime(), true);
      } catch (HlaInvalidLogicalTimeException e) {
         throw new HlaInternalException("Failed to delete instance with default Logical Time", e);
      }
   }

   public HlaPayload deleteLocalHlaPayload(HlaPayload instance, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      return deleteHlaPayload(instance, _worldImpl.getCurrentTime(), logicalTime, true);
   }

   public HlaPayload deleteLocalHlaPayload(HlaPayload instance, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      return deleteHlaPayload(instance, timestamp, logicalTime, true);
   }

   private HlaPayload deleteHlaPayload(HlaPayload instance, HlaTimeStamp timestamp, HlaLogicalTime logicalTime, boolean checkLocal)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      if (instance.isRemoved() || (checkLocal && !instance.isLocal())) {
         return null;
      }

      HlaPayloadImpl instanceImpl = (HlaPayloadImpl) instance;
      ObjectInstanceHandle instanceHandle = instanceImpl.getObjectInstanceHandle();

      _objectManager.deleteObjectInstance(instanceHandle, timestamp, logicalTime);

      _hlaInstanceNameMap.remove(instance.getHlaInstanceName());
      _encodedHlaInstanceHandleMap.remove(ByteBuffer.wrap(instance.getEncodedHlaObjectInstanceHandle()));

      if (instance.isLocal()) {
         _localInstances.remove(instanceHandle);
      } else {
         _remoteInstances.remove(instanceHandle);
      }
      instanceImpl.setRemoved();
      fireDeleted(instance, timestamp, logicalTime);

      return instance;
   }

   public void addHlaPayloadManagerListener(HlaPayloadManagerListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.add(listener);
   }

   public void removeHlaPayloadManagerListener(HlaPayloadManagerListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.remove(listener);
   }


   public void addHlaPayloadDefaultInstanceListener(HlaPayloadListener listener) {
      if (listener == null) {
         throw new NullPointerException();
      }
      _defaultInstanceListeners.add(listener);
   }

   public void addHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListener valueListener) {
      if (valueListener == null) {
         throw new NullPointerException();
      }
      _defaultInstanceValueListeners.add(valueListener);
   }

   public void removeHlaPayloadDefaultInstanceListener(HlaPayloadListener listener) {
      if (listener == null) {
         throw new NullPointerException();
      }
      _defaultInstanceListeners.remove(listener);
   }

   public void removeHlaPayloadDefaultInstanceValueListener(HlaPayloadValueListener valueListener) {
      if (valueListener == null) {
         throw new NullPointerException();
      }
      _defaultInstanceValueListeners.remove(valueListener);
   }

   public void setEnabled(boolean enabled) {
      _optional = false;
      _enabled = enabled;
   }

   public void setEnabledIfAvailableInFom() {
      _optional = true;
      _enabled = true;
   }

   public boolean isEnabled() {
      return _objectClassHandle != null;
   }

   /*
    * AbstractObjectClassManager impl
    */

   @Override
   public void discoverObjectInstance(final ObjectInstanceHandle objectInstanceHandle, String instanceName, HlaTimeStamp timeStamp, HlaFederateId producingFederate) {
      final HlaPayloadImpl instance = createObjectInstance(objectInstanceHandle, false, producingFederate);
      _remoteInstances.put(objectInstanceHandle, instance);
      _hlaInstanceNameMap.put(instance.getHlaInstanceName(), instance);
      _encodedHlaInstanceHandleMap.put(ByteBuffer.wrap(instance.getEncodedHlaObjectInstanceHandle()), instance);
      fireDiscovered(instance, timeStamp);

      for (HlaPayloadListener listener : _defaultInstanceListeners) {
         instance.addHlaPayloadListener(listener);
      }
      for (HlaPayloadValueListener listener : _defaultInstanceValueListeners) {
         instance.addHlaPayloadValueListener(listener);
      }

      checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl.INVALID);

      if (HlaTuning.REQUEST) {
         _worldImpl.invokeDelay(HlaTuning.REQUEST_MIN_DELAY_MS, HlaTuning.REQUEST_MAX_DELAY_MS, new Runnable() {
            public void run() {
               if (!instance.isRemoved()) {
                  Set<String> unsetAttributes = instance.getUnsetAttributeNames();
                  if (!unsetAttributes.isEmpty()) {
                     try {
                        _objectManager.requestAttributeValueUpdate(objectInstanceHandle, unsetAttributes, _worldImpl.getCurrentTime());
                     } catch (HlaBaseException e) {
                        //ignore
                     } catch (HlaBaseRuntimeException e) {
                        //ignore
                     }
                  }
               }
            }
         });
      }
   }

   @Override
   public void reflectAttributeValues(ObjectInstanceHandle objectInstanceHandle, NameValueMap attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      HlaPayloadImpl instance = _remoteInstances.get(objectInstanceHandle);
      if (instance != null) {
         instance.reflectAttributeValues(attributes, timeStamp, logicalTime, producingFederate);
         checkInitializedFired(instance, timeStamp, logicalTime);
      } else {
         _worldImpl.postException(new HlaInternalException("Get reflect for an unknown instance: " + objectInstanceHandle));
      }
   }

   @Override
   public void removeObjectInstance(ObjectInstanceHandle objectInstanceHandle, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {
      HlaPayloadImpl instance = _remoteInstances.remove(objectInstanceHandle);

      if (instance != null) {
         _hlaInstanceNameMap.remove(instance.getHlaInstanceName());
         _encodedHlaInstanceHandleMap.remove(ByteBuffer.wrap(instance.getEncodedHlaObjectInstanceHandle()));
         instance.setRemoved();
         fireDeleted(instance, timeStamp, logicalTime);
      } else {
         _worldImpl.postException(new HlaInternalException("Get remove for an unknown instance: " + objectInstanceHandle));
      }
   }

   @Override
   public boolean isEnabled(String objectClassName) {
      return _enabled;
   }

   @Override
   public boolean isOptional(String objectClassName) {
      return _optional;
   }

   @Override
   public void connected(ObjectClassHandle objectClassHandle, String objectClassName)
         throws HlaNotConnectedException, HlaFomException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      _objectClassHandle = objectClassHandle;

      _objectManager.publish(_objectClassHandle, HlaPayloadImpl.HLA_ATTRIBUTE_NAMES);
      _objectManager.subscribe(_objectClassHandle, HlaPayloadImpl.HLA_ATTRIBUTE_NAMES);
   }

   private void clearAllInstances(boolean doFireDeleted) {
      HlaTimeStamp timeStamp = _worldImpl.getCurrentTime();

      for (Iterator<HlaPayloadImpl> iterator = MapAdapter.concat(_localInstances.values().iterator(), _remoteInstances.values().iterator()); iterator.hasNext();) {
         HlaPayloadImpl instance = iterator.next();
         iterator.remove();
         instance.setRemoved();
         if (doFireDeleted) {
            fireDeleted(instance, timeStamp, HlaLogicalTimeImpl.INVALID);
         }
      }
      _hlaInstanceNameMap.clear();
      _encodedHlaInstanceHandleMap.clear();
   }

   @Override
   public void disconnected(ObjectClassHandle objectClassHandle) {
      _objectClassHandle = null;
      clearAllInstances(true);
   }

   @Override
   public void provideAttributeValueUpdate(ObjectInstanceHandle objectInstanceHandle, Set<String> attributes, HlaTimeStamp hlaTimeStamp) {
      HlaPayloadImpl instance;
      synchronized (_localCreationInProgressLock) {
         instance = _localInstances.get(objectInstanceHandle);
      }

      // instance may be null since provideAttributeValueUpdate is called on a separate thread
      if (instance != null) {
         instance.provideAttributeValueUpdate(attributes, hlaTimeStamp);
      }
   }

   @Override
   public void attributesInScope(ObjectInstanceHandle objectInstanceHandle, Set<String> attributes) {
   }

   @Override
   public void attributesOutOfScope(ObjectInstanceHandle objectInstanceHandle, Set<String> attributes) {
   }

   @Override
   public void save(ObjectClassHandle objectClassHandle) throws HlaSaveFederateException {
      if (!_localInstances.isEmpty()) {
         throw new HlaSaveFederateException("Unable to save local instances");
      }
      if (!_remoteInstances.isEmpty()) {
         throw new HlaSaveFederateException("Unable to save remote instances");
      }
   }

   @Override
   public void restore(ObjectClassHandle objectClassHandle) {
      clearAllInstances(false);
   }

   /*
    * Functions called from HlaPayloadImpl
    */

   void updateAttributeValues(HlaPayloadImpl instance, ObjectInstanceHandle objectInstanceHandle, NameValueMap attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      _objectManager.updateAttributeValues(objectInstanceHandle, attributes, timeStamp, logicalTime);

      checkInitializedFired(instance, timeStamp, logicalTime);
   }


   /*
    * Private helpers...
    */

   private HlaPayloadImpl createObjectInstance(ObjectInstanceHandle objectInstanceHandle, boolean isLocal, HlaFederateId producingFederate) {
      return new HlaPayloadImpl(_worldImpl, this, objectInstanceHandle, isLocal, producingFederate);
   }

   private void checkInitializedFired(HlaPayloadImpl instance, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {
      if (!instance.isInitializedFired() && instance.isInitialized()) {
         instance.setInitializedFired();
         fireInitialized(instance, timeStamp, logicalTime);
      }
   }

   private void fireDiscovered(final HlaPayload instance, final HlaTimeStamp timeStamp) {
      for (final HlaPayloadManagerListener listener : _listeners) {
         _worldImpl.postNotification(new Runnable() {
            public void run() {
               listener.hlaPayloadDiscovered(instance, timeStamp);
            }
         });
      }
   }

   private void fireDeleted(final HlaPayload instance, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      for (final HlaPayloadManagerListener listener : _listeners) {
         _worldImpl.postNotification(new Runnable() {
            public void run() {
               listener.hlaPayloadDeleted(instance, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireInitialized(final HlaPayload instance, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      for (final HlaPayloadManagerListener listener : _listeners) {
         _worldImpl.postNotification(new Runnable() {
            public void run() {
               listener.hlaPayloadInitialized(instance, timeStamp, logicalTime);
            }
         });
      }
   }
}
