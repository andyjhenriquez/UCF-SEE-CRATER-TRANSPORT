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
final class HlaLauncherManagerImpl extends AbstractObjectClassManager implements HlaLauncherManager {

   private static final String HLA_OBJECT_CLASS_NAME = "HLAobjectRoot.PhysicalEntity.Launcher";

   private final ObjectManager _objectManager;
   private final HlaWorldImpl _worldImpl;
   private final Object _localCreationInProgressLock = new Object();

   private volatile boolean _enabled = true;
   private volatile boolean _optional = false;
   private ObjectClassHandle _objectClassHandle = null;

   private final Map<String, HlaLauncherImpl> _hlaInstanceNameMap = new ConcurrentHashMap<String, HlaLauncherImpl>();
   private final Map<ByteBuffer, HlaLauncherImpl> _encodedHlaInstanceHandleMap = new ConcurrentHashMap<ByteBuffer, HlaLauncherImpl>();
   private final Map<ObjectInstanceHandle, HlaLauncherImpl> _localInstances =
         new ConcurrentHashMap<ObjectInstanceHandle, HlaLauncherImpl>();
   private final Map<ObjectInstanceHandle, HlaLauncherImpl> _remoteInstances =
         new ConcurrentHashMap<ObjectInstanceHandle, HlaLauncherImpl>();

   private final Set<HlaLauncherManagerListener> _listeners =
         new CopyOnWriteArraySet<HlaLauncherManagerListener>();

   private final Set<HlaLauncherValueListener> _defaultInstanceValueListeners =
         new CopyOnWriteArraySet<HlaLauncherValueListener>();
   private final Set<HlaLauncherListener> _defaultInstanceListeners =
         new CopyOnWriteArraySet<HlaLauncherListener>();

   /*
    * Share encoders and decoders for HlaLauncherImpl
    */
   protected final Object _encodersLock = new Object();
   protected final Object _decodersLock = new Object();
   /* @GuardedBy("_encodersLock") */
   protected final PositionVectorEncoder _positionVectorEncoderEncoder = new PositionVectorEncoder();
   /* @GuardedBy("_decodersLock") */
   protected final PositionVectorEncoder _positionVectorEncoderDecoder = new PositionVectorEncoder();
   /* @GuardedBy("_encodersLock") */
   protected final HLAfloat64LE _hLAfloat64LEEncoder = BaseEncoder.createHLAfloat64LE();
   /* @GuardedBy("_decodersLock") */
   protected final HLAfloat64LE _hLAfloat64LEDecoder = BaseEncoder.createHLAfloat64LE();
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

   HlaLauncherManagerImpl(HlaWorldImpl world, ObjectManager objectManager) {
      _objectManager = objectManager;
      _worldImpl = world;

      _objectManager.addManager(this, HLA_OBJECT_CLASS_NAME);
   }

   /*
    * HlaLauncherManager interface impl
    */

   public List<HlaLauncher> getHlaLaunchers() {
      return getAllHlaLaunchers();
   }

   public List<HlaLauncher> getAllHlaLaunchers() {
      List<HlaLauncher> list = new ArrayList<HlaLauncher>(_localInstances.size() + _remoteInstances.size());
      list.addAll(_localInstances.values());
      list.addAll(_remoteInstances.values());
      return list;
   }

   public List<HlaLauncher> getLocalHlaLaunchers() {
      return new ArrayList<HlaLauncher>(_localInstances.values());
   }

   public List<HlaLauncher> getRemoteHlaLaunchers() {
      return new ArrayList<HlaLauncher>(_remoteInstances.values());
   }

   public HlaLauncherImpl getLauncherByHlaInstanceName(String hlaInstanceName) {
      return _hlaInstanceNameMap.get(hlaInstanceName);
   }

   public HlaLauncher getLauncherByHlaInstanceHandle(byte[] encodedHlaInstanceHandle) {
      return _encodedHlaInstanceHandleMap.get(ByteBuffer.wrap(encodedHlaInstanceHandle));
   }

   public HlaLauncher createLocalHlaLauncher(
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


   public HlaLauncher createLocalHlaLauncher(
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


   private HlaLauncher createLocalInstance(
      String hlaInstanceName
   ) throws HlaInstanceNameInUseException, HlaNotConnectedException, HlaInternalException, HlaRtiException,
            HlaSaveInProgressException, HlaRestoreInProgressException {

      HlaLauncherImpl instance;
      synchronized (_localCreationInProgressLock) {
         ObjectInstanceHandle objectInstanceHandle = _objectManager.createObjectInstance(_objectClassHandle, hlaInstanceName);
         instance = createObjectInstance(objectInstanceHandle, true, _worldImpl.getFederateId());
         _localInstances.put(objectInstanceHandle, instance);
         _hlaInstanceNameMap.put(instance.getHlaInstanceName(), instance);
         _encodedHlaInstanceHandleMap.put(ByteBuffer.wrap(instance.getEncodedHlaObjectInstanceHandle()), instance);
      }

      HlaTimeStamp timeStamp = _worldImpl.getCurrentTime();
      fireDiscovered(instance, timeStamp);

      for (HlaLauncherListener instanceListener : _defaultInstanceListeners) {
         instance.addHlaLauncherListener(instanceListener);
      }
      for (HlaLauncherValueListener instanceValueListener : _defaultInstanceValueListeners) {
         instance.addHlaLauncherValueListener(instanceValueListener);
      }

      checkInitializedFired(instance, timeStamp, HlaLogicalTimeImpl.INVALID);

      return instance;
   }

   public HlaLauncher deleteLocalHlaLauncher(HlaLauncher instance)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      try {
         return deleteHlaLauncher(instance, _worldImpl.getCurrentTime(), _worldImpl.getDefaultSendTime(), true);
      } catch (HlaInvalidLogicalTimeException e) {
         throw new HlaInternalException("Failed to delete instance with default Logical Time", e);
      }
   }

   public HlaLauncher deleteLocalHlaLauncher(HlaLauncher instance, HlaTimeStamp timestamp)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      try {
         return deleteHlaLauncher(instance, timestamp, _worldImpl.getDefaultSendTime(), true);
      } catch (HlaInvalidLogicalTimeException e) {
         throw new HlaInternalException("Failed to delete instance with default Logical Time", e);
      }
   }

   public HlaLauncher deleteLocalHlaLauncher(HlaLauncher instance, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      return deleteHlaLauncher(instance, _worldImpl.getCurrentTime(), logicalTime, true);
   }

   public HlaLauncher deleteLocalHlaLauncher(HlaLauncher instance, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      return deleteHlaLauncher(instance, timestamp, logicalTime, true);
   }

   private HlaLauncher deleteHlaLauncher(HlaLauncher instance, HlaTimeStamp timestamp, HlaLogicalTime logicalTime, boolean checkLocal)
         throws HlaNotConnectedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      if (instance.isRemoved() || (checkLocal && !instance.isLocal())) {
         return null;
      }

      HlaLauncherImpl instanceImpl = (HlaLauncherImpl) instance;
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

   public void addHlaLauncherManagerListener(HlaLauncherManagerListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.add(listener);
   }

   public void removeHlaLauncherManagerListener(HlaLauncherManagerListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.remove(listener);
   }


   public void addHlaLauncherDefaultInstanceListener(HlaLauncherListener listener) {
      if (listener == null) {
         throw new NullPointerException();
      }
      _defaultInstanceListeners.add(listener);
   }

   public void addHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListener valueListener) {
      if (valueListener == null) {
         throw new NullPointerException();
      }
      _defaultInstanceValueListeners.add(valueListener);
   }

   public void removeHlaLauncherDefaultInstanceListener(HlaLauncherListener listener) {
      if (listener == null) {
         throw new NullPointerException();
      }
      _defaultInstanceListeners.remove(listener);
   }

   public void removeHlaLauncherDefaultInstanceValueListener(HlaLauncherValueListener valueListener) {
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
      final HlaLauncherImpl instance = createObjectInstance(objectInstanceHandle, false, producingFederate);
      _remoteInstances.put(objectInstanceHandle, instance);
      _hlaInstanceNameMap.put(instance.getHlaInstanceName(), instance);
      _encodedHlaInstanceHandleMap.put(ByteBuffer.wrap(instance.getEncodedHlaObjectInstanceHandle()), instance);
      fireDiscovered(instance, timeStamp);

      for (HlaLauncherListener listener : _defaultInstanceListeners) {
         instance.addHlaLauncherListener(listener);
      }
      for (HlaLauncherValueListener listener : _defaultInstanceValueListeners) {
         instance.addHlaLauncherValueListener(listener);
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
      HlaLauncherImpl instance = _remoteInstances.get(objectInstanceHandle);
      if (instance != null) {
         instance.reflectAttributeValues(attributes, timeStamp, logicalTime, producingFederate);
         checkInitializedFired(instance, timeStamp, logicalTime);
      } else {
         _worldImpl.postException(new HlaInternalException("Get reflect for an unknown instance: " + objectInstanceHandle));
      }
   }

   @Override
   public void removeObjectInstance(ObjectInstanceHandle objectInstanceHandle, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {
      HlaLauncherImpl instance = _remoteInstances.remove(objectInstanceHandle);

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

      _objectManager.publish(_objectClassHandle, HlaLauncherImpl.HLA_ATTRIBUTE_NAMES);
      _objectManager.subscribe(_objectClassHandle, HlaLauncherImpl.HLA_ATTRIBUTE_NAMES);
   }

   private void clearAllInstances(boolean doFireDeleted) {
      HlaTimeStamp timeStamp = _worldImpl.getCurrentTime();

      for (Iterator<HlaLauncherImpl> iterator = MapAdapter.concat(_localInstances.values().iterator(), _remoteInstances.values().iterator()); iterator.hasNext();) {
         HlaLauncherImpl instance = iterator.next();
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
      HlaLauncherImpl instance;
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
    * Functions called from HlaLauncherImpl
    */

   void updateAttributeValues(HlaLauncherImpl instance, ObjectInstanceHandle objectInstanceHandle, NameValueMap attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaInternalException, HlaRtiException, HlaAttributeNotOwnedException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      _objectManager.updateAttributeValues(objectInstanceHandle, attributes, timeStamp, logicalTime);

      checkInitializedFired(instance, timeStamp, logicalTime);
   }


   /*
    * Private helpers...
    */

   private HlaLauncherImpl createObjectInstance(ObjectInstanceHandle objectInstanceHandle, boolean isLocal, HlaFederateId producingFederate) {
      return new HlaLauncherImpl(_worldImpl, this, objectInstanceHandle, isLocal, producingFederate);
   }

   private void checkInitializedFired(HlaLauncherImpl instance, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {
      if (!instance.isInitializedFired() && instance.isInitialized()) {
         instance.setInitializedFired();
         fireInitialized(instance, timeStamp, logicalTime);
      }
   }

   private void fireDiscovered(final HlaLauncher instance, final HlaTimeStamp timeStamp) {
      for (final HlaLauncherManagerListener listener : _listeners) {
         _worldImpl.postNotification(new Runnable() {
            public void run() {
               listener.hlaLauncherDiscovered(instance, timeStamp);
            }
         });
      }
   }

   private void fireDeleted(final HlaLauncher instance, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      for (final HlaLauncherManagerListener listener : _listeners) {
         _worldImpl.postNotification(new Runnable() {
            public void run() {
               listener.hlaLauncherDeleted(instance, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireInitialized(final HlaLauncher instance, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      for (final HlaLauncherManagerListener listener : _listeners) {
         _worldImpl.postNotification(new Runnable() {
            public void run() {
               listener.hlaLauncherInitialized(instance, timeStamp, logicalTime);
            }
         });
      }
   }
}