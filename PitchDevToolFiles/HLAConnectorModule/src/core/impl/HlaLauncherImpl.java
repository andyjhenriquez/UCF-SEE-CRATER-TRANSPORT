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
import core.*;
import core.exceptions.*;
import core.datatypes.ToStringBuilder;
import core.impl.utils.AttributeValue;
import core.impl.utils.Equals;
import core.impl.utils.NameValueMap;
import core.impl.utils.SetAdapter;
import core.impl.utils.ParameterValue;

import se.pitch.ral.api.ObjectInstanceHandle;

import java.util.*;
import java.util.concurrent.CopyOnWriteArraySet;


/* @ThreadSafe */
final class HlaLauncherImpl implements HlaLauncher {


   private static final String POSITION_ATTRIBUTE_NAME = "position";
   private static final String MASS_ATTRIBUTE_NAME = "mass";
   private static final String ENERGY_ATTRIBUTE_NAME = "energy";
   private static final String NAME_ATTRIBUTE_NAME = "name";
   private static final String TYPE_ATTRIBUTE_NAME = "type";
   private static final String STATUS_ATTRIBUTE_NAME = "status";
   private static final String PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME = "parent_reference_frame";
   private static final String STATE_ATTRIBUTE_NAME = "state";
   private static final String ACCELERATION_ATTRIBUTE_NAME = "acceleration";
   private static final String ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME = "rotational_acceleration";
   private static final String CENTER_OF_MASS_ATTRIBUTE_NAME = "center_of_mass";
   private static final String BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME = "body_wrt_structural";

   public static final Set<String> HLA_ATTRIBUTE_NAMES = new SetAdapter<String>()
         .append(POSITION_ATTRIBUTE_NAME)
         .append(MASS_ATTRIBUTE_NAME)
         .append(ENERGY_ATTRIBUTE_NAME)
         .append(NAME_ATTRIBUTE_NAME)
         .append(TYPE_ATTRIBUTE_NAME)
         .append(STATUS_ATTRIBUTE_NAME)
         .append(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME)
         .append(STATE_ATTRIBUTE_NAME)
         .append(ACCELERATION_ATTRIBUTE_NAME)
         .append(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME)
         .append(CENTER_OF_MASS_ATTRIBUTE_NAME)
         .append(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME)
         .unmodifiableSet();


   private final HlaWorldImpl _hlaWorld;
   private final HlaLauncherManagerImpl _objectClassManager;
   private final ObjectInstanceHandle _objectInstanceHandle;
   private final boolean _isLocal;
   private final HlaFederateId _createdByFederate;

   private final Object _attributesLock = new Object();
   private final Object _sendLock = new Object();

   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _positionAttribute = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _massAttribute = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<Double> _energyAttribute = new AttributeValue<Double>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _nameAttribute = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _typeAttribute = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _statusAttribute = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _parentReferenceFrameAttribute = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<SpaceTimeCoordinateState> _stateAttribute = new AttributeValue<SpaceTimeCoordinateState>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _accelerationAttribute = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _rotationalAccelerationAttribute = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _centerOfMassAttribute = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<AttitudeQuaternion> _bodyWrtStructuralAttribute = new AttributeValue<AttitudeQuaternion>();

   private final Set<HlaLauncherValueListener> _valueListeners = new CopyOnWriteArraySet<HlaLauncherValueListener>();
   private final Set<HlaLauncherListener> _listeners = new CopyOnWriteArraySet<HlaLauncherListener>();

   private volatile boolean _initializeFired = false;
   private volatile boolean _removed = false;

   HlaLauncherImpl(HlaWorldImpl hlaWorld, HlaLauncherManagerImpl objectClassManager, ObjectInstanceHandle objectInstanceHandle, boolean local, HlaFederateId producingFederate) {
      _hlaWorld = hlaWorld;
      _objectClassManager = objectClassManager;
      _objectInstanceHandle = objectInstanceHandle;
      _isLocal = local;
      _createdByFederate = producingFederate;
   }

   /*
    * HlaLauncher interface impl
    */

   public boolean isLocal() {
      return _isLocal;
   }

   public boolean isInitialized() {
      return true;
   }

   public boolean isWithinInterest() {
      return !_removed;
   }

   public boolean isRemoved() {
      return _removed;
   }

   public boolean hasPosition() {
      synchronized (_attributesLock) {
         updatePosition();
         return _positionAttribute.hasValue();
      }
   }

   public double[/* 3 */] getPosition() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updatePosition();
         if (_positionAttribute.hasValue()) {
            return _positionAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'position' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public double[/* 3 */] getPosition(double[/* 3 */] defaultValue) {
      synchronized (_attributesLock) {
         updatePosition();
         if (_positionAttribute.hasValue()) {
            return _positionAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getPositionTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updatePosition();
         if (_positionAttribute.hasValue()) {
            return _positionAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'position' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updatePosition() {
      byte[] encodedValue = _positionAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._positionVectorEncoderDecoder.decode(encodedValue);
               _positionAttribute.setDecodedValue(_objectClassManager._positionVectorEncoderDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._positionVectorEncoderDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + POSITION_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._positionVectorEncoderDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + POSITION_ATTRIBUTE_NAME, encodedValue, t));
            _positionAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasMass() {
      synchronized (_attributesLock) {
         updateMass();
         return _massAttribute.hasValue();
      }
   }

   public double getMass() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateMass();
         if (_massAttribute.hasValue()) {
            return _massAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'mass' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public double getMass(double defaultValue) {
      synchronized (_attributesLock) {
         updateMass();
         if (_massAttribute.hasValue()) {
            return _massAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<Double> getMassTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateMass();
         if (_massAttribute.hasValue()) {
            return _massAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'mass' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateMass() {
      byte[] encodedValue = _massAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._hLAfloat64LEDecoder.decode(encodedValue);
               _massAttribute.setDecodedValue(_objectClassManager._hLAfloat64LEDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._hLAfloat64LEDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + MASS_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._hLAfloat64LEDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + MASS_ATTRIBUTE_NAME, encodedValue, t));
            _massAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasEnergy() {
      synchronized (_attributesLock) {
         updateEnergy();
         return _energyAttribute.hasValue();
      }
   }

   public double getEnergy() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateEnergy();
         if (_energyAttribute.hasValue()) {
            return _energyAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'energy' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public double getEnergy(double defaultValue) {
      synchronized (_attributesLock) {
         updateEnergy();
         if (_energyAttribute.hasValue()) {
            return _energyAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<Double> getEnergyTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateEnergy();
         if (_energyAttribute.hasValue()) {
            return _energyAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'energy' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateEnergy() {
      byte[] encodedValue = _energyAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._hLAfloat64LEDecoder.decode(encodedValue);
               _energyAttribute.setDecodedValue(_objectClassManager._hLAfloat64LEDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._hLAfloat64LEDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + ENERGY_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._hLAfloat64LEDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + ENERGY_ATTRIBUTE_NAME, encodedValue, t));
            _energyAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasName() {
      synchronized (_attributesLock) {
         updateName();
         return _nameAttribute.hasValue();
      }
   }

   public String getName() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateName();
         if (_nameAttribute.hasValue()) {
            return _nameAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'name' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public String getName(String defaultValue) {
      synchronized (_attributesLock) {
         updateName();
         if (_nameAttribute.hasValue()) {
            return _nameAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getNameTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateName();
         if (_nameAttribute.hasValue()) {
            return _nameAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'name' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateName() {
      byte[] encodedValue = _nameAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._hLAunicodeStringDecoder.decode(encodedValue);
               _nameAttribute.setDecodedValue(_objectClassManager._hLAunicodeStringDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._hLAunicodeStringDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + NAME_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._hLAunicodeStringDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + NAME_ATTRIBUTE_NAME, encodedValue, t));
            _nameAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasType() {
      synchronized (_attributesLock) {
         updateType();
         return _typeAttribute.hasValue();
      }
   }

   public String getType() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateType();
         if (_typeAttribute.hasValue()) {
            return _typeAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'type' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public String getType(String defaultValue) {
      synchronized (_attributesLock) {
         updateType();
         if (_typeAttribute.hasValue()) {
            return _typeAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getTypeTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateType();
         if (_typeAttribute.hasValue()) {
            return _typeAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'type' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateType() {
      byte[] encodedValue = _typeAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._hLAunicodeStringDecoder.decode(encodedValue);
               _typeAttribute.setDecodedValue(_objectClassManager._hLAunicodeStringDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._hLAunicodeStringDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + TYPE_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._hLAunicodeStringDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + TYPE_ATTRIBUTE_NAME, encodedValue, t));
            _typeAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasStatus() {
      synchronized (_attributesLock) {
         updateStatus();
         return _statusAttribute.hasValue();
      }
   }

   public String getStatus() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateStatus();
         if (_statusAttribute.hasValue()) {
            return _statusAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'status' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public String getStatus(String defaultValue) {
      synchronized (_attributesLock) {
         updateStatus();
         if (_statusAttribute.hasValue()) {
            return _statusAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getStatusTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateStatus();
         if (_statusAttribute.hasValue()) {
            return _statusAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'status' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateStatus() {
      byte[] encodedValue = _statusAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._hLAunicodeStringDecoder.decode(encodedValue);
               _statusAttribute.setDecodedValue(_objectClassManager._hLAunicodeStringDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._hLAunicodeStringDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + STATUS_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._hLAunicodeStringDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + STATUS_ATTRIBUTE_NAME, encodedValue, t));
            _statusAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasParentReferenceFrame() {
      synchronized (_attributesLock) {
         updateParentReferenceFrame();
         return _parentReferenceFrameAttribute.hasValue();
      }
   }

   public String getParentReferenceFrame() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateParentReferenceFrame();
         if (_parentReferenceFrameAttribute.hasValue()) {
            return _parentReferenceFrameAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'parentReferenceFrame' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public String getParentReferenceFrame(String defaultValue) {
      synchronized (_attributesLock) {
         updateParentReferenceFrame();
         if (_parentReferenceFrameAttribute.hasValue()) {
            return _parentReferenceFrameAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getParentReferenceFrameTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateParentReferenceFrame();
         if (_parentReferenceFrameAttribute.hasValue()) {
            return _parentReferenceFrameAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'parentReferenceFrame' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateParentReferenceFrame() {
      byte[] encodedValue = _parentReferenceFrameAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._hLAunicodeStringDecoder.decode(encodedValue);
               _parentReferenceFrameAttribute.setDecodedValue(_objectClassManager._hLAunicodeStringDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._hLAunicodeStringDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._hLAunicodeStringDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME, encodedValue, t));
            _parentReferenceFrameAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasState() {
      synchronized (_attributesLock) {
         updateState();
         return _stateAttribute.hasValue();
      }
   }

   public SpaceTimeCoordinateState getState() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateState();
         if (_stateAttribute.hasValue()) {
            return _stateAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'state' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public SpaceTimeCoordinateState getState(SpaceTimeCoordinateState defaultValue) {
      synchronized (_attributesLock) {
         updateState();
         if (_stateAttribute.hasValue()) {
            return _stateAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<SpaceTimeCoordinateState> getStateTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateState();
         if (_stateAttribute.hasValue()) {
            return _stateAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'state' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateState() {
      byte[] encodedValue = _stateAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._spaceTimeCoordinateStateEncoderDecoder.decode(encodedValue);
               _stateAttribute.setDecodedValue(_objectClassManager._spaceTimeCoordinateStateEncoderDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._spaceTimeCoordinateStateEncoderDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + STATE_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._spaceTimeCoordinateStateEncoderDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + STATE_ATTRIBUTE_NAME, encodedValue, t));
            _stateAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasAcceleration() {
      synchronized (_attributesLock) {
         updateAcceleration();
         return _accelerationAttribute.hasValue();
      }
   }

   public double[/* 3 */] getAcceleration() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateAcceleration();
         if (_accelerationAttribute.hasValue()) {
            return _accelerationAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'acceleration' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public double[/* 3 */] getAcceleration(double[/* 3 */] defaultValue) {
      synchronized (_attributesLock) {
         updateAcceleration();
         if (_accelerationAttribute.hasValue()) {
            return _accelerationAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getAccelerationTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateAcceleration();
         if (_accelerationAttribute.hasValue()) {
            return _accelerationAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'acceleration' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateAcceleration() {
      byte[] encodedValue = _accelerationAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._accelerationVectorEncoderDecoder.decode(encodedValue);
               _accelerationAttribute.setDecodedValue(_objectClassManager._accelerationVectorEncoderDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._accelerationVectorEncoderDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + ACCELERATION_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._accelerationVectorEncoderDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + ACCELERATION_ATTRIBUTE_NAME, encodedValue, t));
            _accelerationAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasRotationalAcceleration() {
      synchronized (_attributesLock) {
         updateRotationalAcceleration();
         return _rotationalAccelerationAttribute.hasValue();
      }
   }

   public double[/* 3 */] getRotationalAcceleration() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateRotationalAcceleration();
         if (_rotationalAccelerationAttribute.hasValue()) {
            return _rotationalAccelerationAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'rotationalAcceleration' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public double[/* 3 */] getRotationalAcceleration(double[/* 3 */] defaultValue) {
      synchronized (_attributesLock) {
         updateRotationalAcceleration();
         if (_rotationalAccelerationAttribute.hasValue()) {
            return _rotationalAccelerationAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getRotationalAccelerationTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateRotationalAcceleration();
         if (_rotationalAccelerationAttribute.hasValue()) {
            return _rotationalAccelerationAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'rotationalAcceleration' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateRotationalAcceleration() {
      byte[] encodedValue = _rotationalAccelerationAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._angularAccelerationVectorEncoderDecoder.decode(encodedValue);
               _rotationalAccelerationAttribute.setDecodedValue(_objectClassManager._angularAccelerationVectorEncoderDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._angularAccelerationVectorEncoderDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._angularAccelerationVectorEncoderDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME, encodedValue, t));
            _rotationalAccelerationAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasCenterOfMass() {
      synchronized (_attributesLock) {
         updateCenterOfMass();
         return _centerOfMassAttribute.hasValue();
      }
   }

   public double[/* 3 */] getCenterOfMass() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateCenterOfMass();
         if (_centerOfMassAttribute.hasValue()) {
            return _centerOfMassAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'centerOfMass' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public double[/* 3 */] getCenterOfMass(double[/* 3 */] defaultValue) {
      synchronized (_attributesLock) {
         updateCenterOfMass();
         if (_centerOfMassAttribute.hasValue()) {
            return _centerOfMassAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getCenterOfMassTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateCenterOfMass();
         if (_centerOfMassAttribute.hasValue()) {
            return _centerOfMassAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'centerOfMass' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateCenterOfMass() {
      byte[] encodedValue = _centerOfMassAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._positionVectorEncoderDecoder.decode(encodedValue);
               _centerOfMassAttribute.setDecodedValue(_objectClassManager._positionVectorEncoderDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._positionVectorEncoderDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + CENTER_OF_MASS_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._positionVectorEncoderDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + CENTER_OF_MASS_ATTRIBUTE_NAME, encodedValue, t));
            _centerOfMassAttribute.clearEncodedValue();
         }
      }
   }

   public boolean hasBodyWrtStructural() {
      synchronized (_attributesLock) {
         updateBodyWrtStructural();
         return _bodyWrtStructuralAttribute.hasValue();
      }
   }

   public AttitudeQuaternion getBodyWrtStructural() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateBodyWrtStructural();
         if (_bodyWrtStructuralAttribute.hasValue()) {
            return _bodyWrtStructuralAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'bodyWrtStructural' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public AttitudeQuaternion getBodyWrtStructural(AttitudeQuaternion defaultValue) {
      synchronized (_attributesLock) {
         updateBodyWrtStructural();
         if (_bodyWrtStructuralAttribute.hasValue()) {
            return _bodyWrtStructuralAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<AttitudeQuaternion> getBodyWrtStructuralTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateBodyWrtStructural();
         if (_bodyWrtStructuralAttribute.hasValue()) {
            return _bodyWrtStructuralAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'bodyWrtStructural' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateBodyWrtStructural() {
      byte[] encodedValue = _bodyWrtStructuralAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._attitudeQuaternionEncoderDecoder.decode(encodedValue);
               _bodyWrtStructuralAttribute.setDecodedValue(_objectClassManager._attitudeQuaternionEncoderDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._attitudeQuaternionEncoderDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._attitudeQuaternionEncoderDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME, encodedValue, t));
            _bodyWrtStructuralAttribute.clearEncodedValue();
         }
      }
   }

   public HlaFederateId getProducingFederate() {
      return _createdByFederate;
   }

   public HlaFederateId getLastProducingFederate(HlaLauncherAttributes.Attribute attribute) {
      synchronized (_attributesLock) {
         switch (attribute) {
            case POSITION:
               if (_positionAttribute.hasLastProducingFederate()) {
                  return _positionAttribute.getLastProducingFederate();
               }
            case MASS:
               if (_massAttribute.hasLastProducingFederate()) {
                  return _massAttribute.getLastProducingFederate();
               }
            case ENERGY:
               if (_energyAttribute.hasLastProducingFederate()) {
                  return _energyAttribute.getLastProducingFederate();
               }
            case NAME:
               if (_nameAttribute.hasLastProducingFederate()) {
                  return _nameAttribute.getLastProducingFederate();
               }
            case TYPE:
               if (_typeAttribute.hasLastProducingFederate()) {
                  return _typeAttribute.getLastProducingFederate();
               }
            case STATUS:
               if (_statusAttribute.hasLastProducingFederate()) {
                  return _statusAttribute.getLastProducingFederate();
               }
            case PARENT_REFERENCE_FRAME:
               if (_parentReferenceFrameAttribute.hasLastProducingFederate()) {
                  return _parentReferenceFrameAttribute.getLastProducingFederate();
               }
            case STATE:
               if (_stateAttribute.hasLastProducingFederate()) {
                  return _stateAttribute.getLastProducingFederate();
               }
            case ACCELERATION:
               if (_accelerationAttribute.hasLastProducingFederate()) {
                  return _accelerationAttribute.getLastProducingFederate();
               }
            case ROTATIONAL_ACCELERATION:
               if (_rotationalAccelerationAttribute.hasLastProducingFederate()) {
                  return _rotationalAccelerationAttribute.getLastProducingFederate();
               }
            case CENTER_OF_MASS:
               if (_centerOfMassAttribute.hasLastProducingFederate()) {
                  return _centerOfMassAttribute.getLastProducingFederate();
               }
            case BODY_WRT_STRUCTURAL:
               if (_bodyWrtStructuralAttribute.hasLastProducingFederate()) {
                  return _bodyWrtStructuralAttribute.getLastProducingFederate();
               }
         }
      }
      return new HlaFederateIdImpl(null);
   }

   public HlaLauncherAttributes getHlaLauncherAttributes() {
      synchronized (_attributesLock) {
         updatePosition();
         updateMass();
         updateEnergy();
         updateName();
         updateType();
         updateStatus();
         updateParentReferenceFrame();
         updateState();
         updateAcceleration();
         updateRotationalAcceleration();
         updateCenterOfMass();
         updateBodyWrtStructural();
         return new HlaLauncherAttributesImpl(
            _positionAttribute,
            _massAttribute,
            _energyAttribute,
            _nameAttribute,
            _typeAttribute,
            _statusAttribute,
            _parentReferenceFrameAttribute,
            _stateAttribute,
            _accelerationAttribute,
            _rotationalAccelerationAttribute,
            _centerOfMassAttribute,
            _bodyWrtStructuralAttribute
         );
      }
   }

   public HlaLauncherUpdater getHlaLauncherUpdater() {
      return new HlaLauncherUpdaterImpl(this);
   }

   public String getHlaInstanceName() {
      return _objectInstanceHandle.getObjectInstanceName();
   }

   public byte[] getEncodedHlaObjectInstanceHandle() {
      return _objectInstanceHandle.getEncodedHandle();
   }

   public ObjectClassType getClassType() {
      return ObjectClassType.LAUNCHER;
   }


   public void addHlaLauncherValueListener(HlaLauncherValueListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _valueListeners.add(listener);
   }

   public void removeHlaLauncherValueListener(HlaLauncherValueListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _valueListeners.remove(listener);
   }

   public void addHlaLauncherListener(HlaLauncherListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.add(listener);
   }

   public void removeHlaLauncherListener(HlaLauncherListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.remove(listener);
   }

   /*
    * Functions used by HlaLauncherManagerImpl
    */

   boolean isInitializedFired() {
      return _initializeFired;
   }

   void setInitializedFired() {
      _initializeFired = true;
   }

   ObjectInstanceHandle getObjectInstanceHandle() {
      return _objectInstanceHandle;
   }

   void setRemoved() {
      _removed = true;
      _valueListeners.clear();
      _listeners.clear();
   }


   void provideAttributeValueUpdate(Set<String> attributes, HlaTimeStamp hlaTimeStamp) {
      try {
         synchronized (_sendLock) {
            sendAttributes(getAttributeEnum(attributes), getHlaLauncherAttributes(), hlaTimeStamp, HlaLogicalTimeImpl.INVALID);
         }
      } catch (HlaBaseException e) {
         //ignore
      } catch (HlaBaseRuntimeException e) {
         //ignore
      }
   }

   Set<String> getUnsetAttributeNames() {
      Set<String> unsetAttributes = new HashSet<String>(HLA_ATTRIBUTE_NAMES.size());
      HlaLauncherAttributes attributes = getHlaLauncherAttributes();
      if (!attributes.hasPosition()) {
         unsetAttributes.add(POSITION_ATTRIBUTE_NAME);
      }
      if (!attributes.hasMass()) {
         unsetAttributes.add(MASS_ATTRIBUTE_NAME);
      }
      if (!attributes.hasEnergy()) {
         unsetAttributes.add(ENERGY_ATTRIBUTE_NAME);
      }
      if (!attributes.hasName()) {
         unsetAttributes.add(NAME_ATTRIBUTE_NAME);
      }
      if (!attributes.hasType()) {
         unsetAttributes.add(TYPE_ATTRIBUTE_NAME);
      }
      if (!attributes.hasStatus()) {
         unsetAttributes.add(STATUS_ATTRIBUTE_NAME);
      }
      if (!attributes.hasParentReferenceFrame()) {
         unsetAttributes.add(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME);
      }
      if (!attributes.hasState()) {
         unsetAttributes.add(STATE_ATTRIBUTE_NAME);
      }
      if (!attributes.hasAcceleration()) {
         unsetAttributes.add(ACCELERATION_ATTRIBUTE_NAME);
      }
      if (!attributes.hasRotationalAcceleration()) {
         unsetAttributes.add(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME);
      }
      if (!attributes.hasCenterOfMass()) {
         unsetAttributes.add(CENTER_OF_MASS_ATTRIBUTE_NAME);
      }
      if (!attributes.hasBodyWrtStructural()) {
         unsetAttributes.add(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME);
      }
      return unsetAttributes;
   }

   @SuppressWarnings ({ "UnnecessaryContinue" })
   void reflectAttributeValues(NameValueMap attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      Set<HlaLauncherAttributes.Attribute> attributesUpdated = EnumSet.noneOf(HlaLauncherAttributes.Attribute.class);

      synchronized (_attributesLock) {
         for (Map.Entry<String, byte[]> newAttribute : attributes.entrySet()) {
            String attributeName = newAttribute.getKey();
            byte[] attributeValue = newAttribute.getValue();

            HlaLauncherAttributes.Attribute attribute = HlaLauncherAttributes.Attribute.find(attributeName);
            if (attribute == null) {
               continue;
            }

            switch (attribute) {
               case POSITION: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.POSITION);

                  if (_valueListeners.isEmpty()) {
                     _positionAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updatePosition();
                     AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_positionAttribute);

                     _positionAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updatePosition();
                     if (_positionAttribute.hasValue()) {
                        firePositionUpdated(_positionAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.POSITION, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case MASS: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.MASS);

                  if (_valueListeners.isEmpty()) {
                     _massAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateMass();
                     AttributeValue<Double> oldValue = new AttributeValue<Double>(_massAttribute);

                     _massAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateMass();
                     if (_massAttribute.hasValue()) {
                        fireMassUpdated(_massAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.MASS, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case ENERGY: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.ENERGY);

                  if (_valueListeners.isEmpty()) {
                     _energyAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateEnergy();
                     AttributeValue<Double> oldValue = new AttributeValue<Double>(_energyAttribute);

                     _energyAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateEnergy();
                     if (_energyAttribute.hasValue()) {
                        fireEnergyUpdated(_energyAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.ENERGY, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case NAME: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.NAME);

                  if (_valueListeners.isEmpty()) {
                     _nameAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateName();
                     AttributeValue<String> oldValue = new AttributeValue<String>(_nameAttribute);

                     _nameAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateName();
                     if (_nameAttribute.hasValue()) {
                        fireNameUpdated(_nameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.NAME, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case TYPE: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.TYPE);

                  if (_valueListeners.isEmpty()) {
                     _typeAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateType();
                     AttributeValue<String> oldValue = new AttributeValue<String>(_typeAttribute);

                     _typeAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateType();
                     if (_typeAttribute.hasValue()) {
                        fireTypeUpdated(_typeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.TYPE, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case STATUS: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.STATUS);

                  if (_valueListeners.isEmpty()) {
                     _statusAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateStatus();
                     AttributeValue<String> oldValue = new AttributeValue<String>(_statusAttribute);

                     _statusAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateStatus();
                     if (_statusAttribute.hasValue()) {
                        fireStatusUpdated(_statusAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.STATUS, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case PARENT_REFERENCE_FRAME: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.PARENT_REFERENCE_FRAME);

                  if (_valueListeners.isEmpty()) {
                     _parentReferenceFrameAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateParentReferenceFrame();
                     AttributeValue<String> oldValue = new AttributeValue<String>(_parentReferenceFrameAttribute);

                     _parentReferenceFrameAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateParentReferenceFrame();
                     if (_parentReferenceFrameAttribute.hasValue()) {
                        fireParentReferenceFrameUpdated(_parentReferenceFrameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.PARENT_REFERENCE_FRAME, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case STATE: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.STATE);

                  if (_valueListeners.isEmpty()) {
                     _stateAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateState();
                     AttributeValue<SpaceTimeCoordinateState> oldValue = new AttributeValue<SpaceTimeCoordinateState>(_stateAttribute);

                     _stateAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateState();
                     if (_stateAttribute.hasValue()) {
                        fireStateUpdated(_stateAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.STATE, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case ACCELERATION: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.ACCELERATION);

                  if (_valueListeners.isEmpty()) {
                     _accelerationAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateAcceleration();
                     AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_accelerationAttribute);

                     _accelerationAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateAcceleration();
                     if (_accelerationAttribute.hasValue()) {
                        fireAccelerationUpdated(_accelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.ACCELERATION, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case ROTATIONAL_ACCELERATION: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.ROTATIONAL_ACCELERATION);

                  if (_valueListeners.isEmpty()) {
                     _rotationalAccelerationAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateRotationalAcceleration();
                     AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_rotationalAccelerationAttribute);

                     _rotationalAccelerationAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateRotationalAcceleration();
                     if (_rotationalAccelerationAttribute.hasValue()) {
                        fireRotationalAccelerationUpdated(_rotationalAccelerationAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.ROTATIONAL_ACCELERATION, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case CENTER_OF_MASS: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.CENTER_OF_MASS);

                  if (_valueListeners.isEmpty()) {
                     _centerOfMassAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateCenterOfMass();
                     AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_centerOfMassAttribute);

                     _centerOfMassAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateCenterOfMass();
                     if (_centerOfMassAttribute.hasValue()) {
                        fireCenterOfMassUpdated(_centerOfMassAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.CENTER_OF_MASS, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case BODY_WRT_STRUCTURAL: {
                  attributesUpdated.add(HlaLauncherAttributes.Attribute.BODY_WRT_STRUCTURAL);

                  if (_valueListeners.isEmpty()) {
                     _bodyWrtStructuralAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateBodyWrtStructural();
                     AttributeValue<AttitudeQuaternion> oldValue = new AttributeValue<AttitudeQuaternion>(_bodyWrtStructuralAttribute);

                     _bodyWrtStructuralAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateBodyWrtStructural();
                     if (_bodyWrtStructuralAttribute.hasValue()) {
                        fireBodyWrtStructuralUpdated(_bodyWrtStructuralAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.BODY_WRT_STRUCTURAL, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
            }
         }
      }

      fireAttributesUpdated(attributesUpdated, timeStamp, logicalTime);
   }



   /*
    * Functions used by HlaLauncherUpdaterImpl
    */

   void applyUpdate(EnumMap<HlaLauncherAttributes.Attribute, Object> attributeMap,
                    EnumSet<HlaLauncherAttributes.Attribute> sendAttributes,
                    HlaTimeStamp timestamp,
                    HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInvalidLogicalTimeException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      if (timestamp == null) {
         timestamp = _hlaWorld.getCurrentTime();
      }
      if (logicalTime == null) {
         logicalTime = _hlaWorld.getDefaultSendTime();
      }
      synchronized (_sendLock) {
         HlaLauncherAttributes attributes = applyUpdate(attributeMap, timestamp, logicalTime, _hlaWorld.getFederateId());
         sendAttributes.addAll(addDefaultSendAttributes(attributeMap.keySet()));
         sendAttributes(sendAttributes, attributes, timestamp, logicalTime);
      }
   }


   /*
    * Private functions
    */

   private Set<HlaLauncherAttributes.Attribute> addDefaultSendAttributes(Set<HlaLauncherAttributes.Attribute> attributes) {
      return attributes;
   }

   private void firePositionUpdated(final double[/* 3 */] value, AttributeValue<double[/* 3 */]> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final double[/* 3 */] oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.positionUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireMassUpdated(final double value, AttributeValue<Double> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final double oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.massUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireEnergyUpdated(final double value, AttributeValue<Double> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final double oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.energyUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireNameUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.nameUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireTypeUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.typeUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireStatusUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.statusUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireParentReferenceFrameUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.parentReferenceFrameUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireStateUpdated(final SpaceTimeCoordinateState value, AttributeValue<SpaceTimeCoordinateState> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final SpaceTimeCoordinateState oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.stateUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireAccelerationUpdated(final double[/* 3 */] value, AttributeValue<double[/* 3 */]> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final double[/* 3 */] oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.accelerationUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireRotationalAccelerationUpdated(final double[/* 3 */] value, AttributeValue<double[/* 3 */]> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final double[/* 3 */] oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.rotationalAccelerationUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireCenterOfMassUpdated(final double[/* 3 */] value, AttributeValue<double[/* 3 */]> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final double[/* 3 */] oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.centerOfMassUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireBodyWrtStructuralUpdated(final AttitudeQuaternion value, AttributeValue<AttitudeQuaternion> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      final boolean oldValid = previous.hasValue();
      final AttitudeQuaternion oldValue = oldValid ? previous.getValue() : value;

      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.bodyWrtStructuralUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireAttributesUpdated(final Set<HlaLauncherAttributes.Attribute> attributes, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaLauncher instance = this;
      for (final HlaLauncherListener listener : _listeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               listener.attributesUpdated(instance, attributes, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireProducingFederateUpdatedIfChanged(final HlaLauncherAttributes.Attribute attribute, final HlaFederateId oldProducingFederate, final HlaFederateId newProducingFederate, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      if (Equals.isEquals(oldProducingFederate, newProducingFederate)) {
         return;
      }

      final HlaLauncher instance = this;
      for (final HlaLauncherValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.producingFederateUpdated(instance, attribute, oldProducingFederate, newProducingFederate, timeStamp, logicalTime);
            }
         });
      }
   }

   @SuppressWarnings ({ "UnnecessaryContinue" })
   private Set<HlaLauncherAttributes.Attribute> getAttributeEnum(Set<String> attributeNames) {
      Set<HlaLauncherAttributes.Attribute> ret = EnumSet.noneOf(HlaLauncherAttributes.Attribute.class);

      for (String attributeName : attributeNames) {
         HlaLauncherAttributes.Attribute attribute = HlaLauncherAttributes.Attribute.find(attributeName);
         if (attribute != null) {
            ret.add(attribute);
         }
      }
      return ret;
   }

   /* @GuardedBy("_sendLock") */
   private HlaLauncherAttributes applyUpdate(EnumMap<HlaLauncherAttributes.Attribute, Object> attributeUpdates, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      HlaLauncherAttributes ret;

      synchronized (_attributesLock) {
         for (Map.Entry<HlaLauncherAttributes.Attribute, Object> attributeUpdate : attributeUpdates.entrySet()) {
            switch (attributeUpdate.getKey()) {
               case POSITION: {
                  updatePosition();
                  AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_positionAttribute);

                  double[/* 3 */] value = (double[/* 3 */])attributeUpdate.getValue();
                  _positionAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  firePositionUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.POSITION, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case MASS: {
                  updateMass();
                  AttributeValue<Double> oldValue = new AttributeValue<Double>(_massAttribute);

                  double value = (Double)attributeUpdate.getValue();
                  _massAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireMassUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.MASS, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case ENERGY: {
                  updateEnergy();
                  AttributeValue<Double> oldValue = new AttributeValue<Double>(_energyAttribute);

                  double value = (Double)attributeUpdate.getValue();
                  _energyAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireEnergyUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.ENERGY, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case NAME: {
                  updateName();
                  AttributeValue<String> oldValue = new AttributeValue<String>(_nameAttribute);

                  String value = (String)attributeUpdate.getValue();
                  _nameAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireNameUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.NAME, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case TYPE: {
                  updateType();
                  AttributeValue<String> oldValue = new AttributeValue<String>(_typeAttribute);

                  String value = (String)attributeUpdate.getValue();
                  _typeAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireTypeUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.TYPE, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case STATUS: {
                  updateStatus();
                  AttributeValue<String> oldValue = new AttributeValue<String>(_statusAttribute);

                  String value = (String)attributeUpdate.getValue();
                  _statusAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireStatusUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.STATUS, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case PARENT_REFERENCE_FRAME: {
                  updateParentReferenceFrame();
                  AttributeValue<String> oldValue = new AttributeValue<String>(_parentReferenceFrameAttribute);

                  String value = (String)attributeUpdate.getValue();
                  _parentReferenceFrameAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireParentReferenceFrameUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.PARENT_REFERENCE_FRAME, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case STATE: {
                  updateState();
                  AttributeValue<SpaceTimeCoordinateState> oldValue = new AttributeValue<SpaceTimeCoordinateState>(_stateAttribute);

                  SpaceTimeCoordinateState value = (SpaceTimeCoordinateState)attributeUpdate.getValue();
                  _stateAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireStateUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.STATE, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case ACCELERATION: {
                  updateAcceleration();
                  AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_accelerationAttribute);

                  double[/* 3 */] value = (double[/* 3 */])attributeUpdate.getValue();
                  _accelerationAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireAccelerationUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.ACCELERATION, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case ROTATIONAL_ACCELERATION: {
                  updateRotationalAcceleration();
                  AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_rotationalAccelerationAttribute);

                  double[/* 3 */] value = (double[/* 3 */])attributeUpdate.getValue();
                  _rotationalAccelerationAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireRotationalAccelerationUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.ROTATIONAL_ACCELERATION, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case CENTER_OF_MASS: {
                  updateCenterOfMass();
                  AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_centerOfMassAttribute);

                  double[/* 3 */] value = (double[/* 3 */])attributeUpdate.getValue();
                  _centerOfMassAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireCenterOfMassUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.CENTER_OF_MASS, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case BODY_WRT_STRUCTURAL: {
                  updateBodyWrtStructural();
                  AttributeValue<AttitudeQuaternion> oldValue = new AttributeValue<AttitudeQuaternion>(_bodyWrtStructuralAttribute);

                  AttitudeQuaternion value = (AttitudeQuaternion)attributeUpdate.getValue();
                  _bodyWrtStructuralAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireBodyWrtStructuralUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.BODY_WRT_STRUCTURAL, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
            }
         }
         ret = getHlaLauncherAttributes();
      }

      if (!attributeUpdates.isEmpty()) {
         fireAttributesUpdated(attributeUpdates.keySet(), timeStamp, logicalTime);
      }

      return ret;
   }

   /* @GuardedBy("_sendLock") */
   private void sendAttributes(Set<HlaLauncherAttributes.Attribute> attributes, HlaLauncherAttributes attributeValues, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      NameValueMap attributeValueMap = new NameValueMap();

      synchronized (_objectClassManager._encodersLock) {
         for (HlaLauncherAttributes.Attribute attribute : attributes) {
            switch (attribute) {
               case POSITION:
                  if (attributeValues.hasPosition()) {
                     try {
                        _objectClassManager._positionVectorEncoderEncoder.setValue(attributeValues.getPosition());
                        attributeValueMap.put(POSITION_ATTRIBUTE_NAME, _objectClassManager._positionVectorEncoderEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + POSITION_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case MASS:
                  if (attributeValues.hasMass()) {
                     try {
                        _objectClassManager._hLAfloat64LEEncoder.setValue(attributeValues.getMass());
                        attributeValueMap.put(MASS_ATTRIBUTE_NAME, _objectClassManager._hLAfloat64LEEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + MASS_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case ENERGY:
                  if (attributeValues.hasEnergy()) {
                     try {
                        _objectClassManager._hLAfloat64LEEncoder.setValue(attributeValues.getEnergy());
                        attributeValueMap.put(ENERGY_ATTRIBUTE_NAME, _objectClassManager._hLAfloat64LEEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + ENERGY_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case NAME:
                  if (attributeValues.hasName()) {
                     try {
                        _objectClassManager._hLAunicodeStringEncoder.setValue(attributeValues.getName());
                        attributeValueMap.put(NAME_ATTRIBUTE_NAME, _objectClassManager._hLAunicodeStringEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + NAME_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case TYPE:
                  if (attributeValues.hasType()) {
                     try {
                        _objectClassManager._hLAunicodeStringEncoder.setValue(attributeValues.getType());
                        attributeValueMap.put(TYPE_ATTRIBUTE_NAME, _objectClassManager._hLAunicodeStringEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + TYPE_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case STATUS:
                  if (attributeValues.hasStatus()) {
                     try {
                        _objectClassManager._hLAunicodeStringEncoder.setValue(attributeValues.getStatus());
                        attributeValueMap.put(STATUS_ATTRIBUTE_NAME, _objectClassManager._hLAunicodeStringEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + STATUS_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case PARENT_REFERENCE_FRAME:
                  if (attributeValues.hasParentReferenceFrame()) {
                     try {
                        _objectClassManager._hLAunicodeStringEncoder.setValue(attributeValues.getParentReferenceFrame());
                        attributeValueMap.put(PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME, _objectClassManager._hLAunicodeStringEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + PARENT_REFERENCE_FRAME_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case STATE:
                  if (attributeValues.hasState()) {
                     try {
                        _objectClassManager._spaceTimeCoordinateStateEncoderEncoder.setValue(attributeValues.getState());
                        attributeValueMap.put(STATE_ATTRIBUTE_NAME, _objectClassManager._spaceTimeCoordinateStateEncoderEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + STATE_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case ACCELERATION:
                  if (attributeValues.hasAcceleration()) {
                     try {
                        _objectClassManager._accelerationVectorEncoderEncoder.setValue(attributeValues.getAcceleration());
                        attributeValueMap.put(ACCELERATION_ATTRIBUTE_NAME, _objectClassManager._accelerationVectorEncoderEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + ACCELERATION_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case ROTATIONAL_ACCELERATION:
                  if (attributeValues.hasRotationalAcceleration()) {
                     try {
                        _objectClassManager._angularAccelerationVectorEncoderEncoder.setValue(attributeValues.getRotationalAcceleration());
                        attributeValueMap.put(ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME, _objectClassManager._angularAccelerationVectorEncoderEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + ROTATIONAL_ACCELERATION_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case CENTER_OF_MASS:
                  if (attributeValues.hasCenterOfMass()) {
                     try {
                        _objectClassManager._positionVectorEncoderEncoder.setValue(attributeValues.getCenterOfMass());
                        attributeValueMap.put(CENTER_OF_MASS_ATTRIBUTE_NAME, _objectClassManager._positionVectorEncoderEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + CENTER_OF_MASS_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
               case BODY_WRT_STRUCTURAL:
                  if (attributeValues.hasBodyWrtStructural()) {
                     try {
                        _objectClassManager._attitudeQuaternionEncoderEncoder.setValue(attributeValues.getBodyWrtStructural());
                        attributeValueMap.put(BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME, _objectClassManager._attitudeQuaternionEncoderEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + BODY_WRT_STRUCTURAL_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
            }
         }
      }

      if (!attributeValueMap.isEmpty()) {
         _objectClassManager.updateAttributeValues(this, _objectInstanceHandle, attributeValueMap, timestamp, logicalTime);
      }
   }
}
