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
final class HlaPhysicalInterfaceImpl implements HlaPhysicalInterface {


   private static final String NAME_ATTRIBUTE_NAME = "name";
   private static final String PARENT_NAME_ATTRIBUTE_NAME = "parent_name";
   private static final String POSITION_ATTRIBUTE_NAME = "position";
   private static final String ATTITUDE_ATTRIBUTE_NAME = "attitude";

   public static final Set<String> HLA_ATTRIBUTE_NAMES = new SetAdapter<String>()
         .append(NAME_ATTRIBUTE_NAME)
         .append(PARENT_NAME_ATTRIBUTE_NAME)
         .append(POSITION_ATTRIBUTE_NAME)
         .append(ATTITUDE_ATTRIBUTE_NAME)
         .unmodifiableSet();


   private final HlaWorldImpl _hlaWorld;
   private final HlaPhysicalInterfaceManagerImpl _objectClassManager;
   private final ObjectInstanceHandle _objectInstanceHandle;
   private final boolean _isLocal;
   private final HlaFederateId _createdByFederate;

   private final Object _attributesLock = new Object();
   private final Object _sendLock = new Object();

   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _nameAttribute = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<String> _parentNameAttribute = new AttributeValue<String>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<double[/* 3 */]> _positionAttribute = new AttributeValue<double[/* 3 */]>();
   /* @GuardedBy("_attributesLock") */
   private final AttributeValue<AttitudeQuaternion> _attitudeAttribute = new AttributeValue<AttitudeQuaternion>();

   private final Set<HlaPhysicalInterfaceValueListener> _valueListeners = new CopyOnWriteArraySet<HlaPhysicalInterfaceValueListener>();
   private final Set<HlaPhysicalInterfaceListener> _listeners = new CopyOnWriteArraySet<HlaPhysicalInterfaceListener>();

   private volatile boolean _initializeFired = false;
   private volatile boolean _removed = false;

   HlaPhysicalInterfaceImpl(HlaWorldImpl hlaWorld, HlaPhysicalInterfaceManagerImpl objectClassManager, ObjectInstanceHandle objectInstanceHandle, boolean local, HlaFederateId producingFederate) {
      _hlaWorld = hlaWorld;
      _objectClassManager = objectClassManager;
      _objectInstanceHandle = objectInstanceHandle;
      _isLocal = local;
      _createdByFederate = producingFederate;
   }

   /*
    * HlaPhysicalInterface interface impl
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

   public boolean hasParentName() {
      synchronized (_attributesLock) {
         updateParentName();
         return _parentNameAttribute.hasValue();
      }
   }

   public String getParentName() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateParentName();
         if (_parentNameAttribute.hasValue()) {
            return _parentNameAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'parentName' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public String getParentName(String defaultValue) {
      synchronized (_attributesLock) {
         updateParentName();
         if (_parentNameAttribute.hasValue()) {
            return _parentNameAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getParentNameTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateParentName();
         if (_parentNameAttribute.hasValue()) {
            return _parentNameAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'parentName' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateParentName() {
      byte[] encodedValue = _parentNameAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._hLAunicodeStringDecoder.decode(encodedValue);
               _parentNameAttribute.setDecodedValue(_objectClassManager._hLAunicodeStringDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._hLAunicodeStringDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + PARENT_NAME_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._hLAunicodeStringDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + PARENT_NAME_ATTRIBUTE_NAME, encodedValue, t));
            _parentNameAttribute.clearEncodedValue();
         }
      }
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

   public boolean hasAttitude() {
      synchronized (_attributesLock) {
         updateAttitude();
         return _attitudeAttribute.hasValue();
      }
   }

   public AttitudeQuaternion getAttitude() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateAttitude();
         if (_attitudeAttribute.hasValue()) {
            return _attitudeAttribute.getValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'attitude' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   public AttitudeQuaternion getAttitude(AttitudeQuaternion defaultValue) {
      synchronized (_attributesLock) {
         updateAttitude();
         if (_attitudeAttribute.hasValue()) {
            return _attitudeAttribute.getValueForUser();
         }
      }
      return defaultValue;
   }

   public HlaTimeStamped<AttitudeQuaternion> getAttitudeTimeStamped() throws HlaValueNotSetException {
      synchronized (_attributesLock) {
         updateAttitude();
         if (_attitudeAttribute.hasValue()) {
            return _attitudeAttribute.getTimestampedValueForUser();
         }
      }
      throw new HlaValueNotSetException("Attribute 'attitude' not set for instance " + _objectInstanceHandle.getObjectInstanceName());
   }

   /* @GuardedBy("_attributesLock") */
   private void updateAttitude() {
      byte[] encodedValue = _attitudeAttribute.getEncodedValue();
      if (encodedValue != null) {
         try {
            synchronized (_objectClassManager._decodersLock) {
               _objectClassManager._attitudeQuaternionEncoderDecoder.decode(encodedValue);
               _attitudeAttribute.setDecodedValue(_objectClassManager._attitudeQuaternionEncoderDecoder.getValue());

               if (HlaTuning.VERIFY_RECEIVED_DATA_LENGTH && _objectClassManager._attitudeQuaternionEncoderDecoder.getEncodedLength() != encodedValue.length) {
                  _hlaWorld.postException(
                     new HlaDecodeException("Failed to decode " + ATTITUDE_ATTRIBUTE_NAME + ". " +
                                                  "Invalid data length " + encodedValue.length + ", expected " + _objectClassManager._attitudeQuaternionEncoderDecoder.getEncodedLength(),
                                                  encodedValue));
               }
            }
         } catch (Throwable t) {
            _hlaWorld.postException(new HlaDecodeException("Failed to decode " + ATTITUDE_ATTRIBUTE_NAME, encodedValue, t));
            _attitudeAttribute.clearEncodedValue();
         }
      }
   }

   public HlaFederateId getProducingFederate() {
      return _createdByFederate;
   }

   public HlaFederateId getLastProducingFederate(HlaPhysicalInterfaceAttributes.Attribute attribute) {
      synchronized (_attributesLock) {
         switch (attribute) {
            case NAME:
               if (_nameAttribute.hasLastProducingFederate()) {
                  return _nameAttribute.getLastProducingFederate();
               }
            case PARENT_NAME:
               if (_parentNameAttribute.hasLastProducingFederate()) {
                  return _parentNameAttribute.getLastProducingFederate();
               }
            case POSITION:
               if (_positionAttribute.hasLastProducingFederate()) {
                  return _positionAttribute.getLastProducingFederate();
               }
            case ATTITUDE:
               if (_attitudeAttribute.hasLastProducingFederate()) {
                  return _attitudeAttribute.getLastProducingFederate();
               }
         }
      }
      return new HlaFederateIdImpl(null);
   }

   public HlaPhysicalInterfaceAttributes getHlaPhysicalInterfaceAttributes() {
      synchronized (_attributesLock) {
         updateName();
         updateParentName();
         updatePosition();
         updateAttitude();
         return new HlaPhysicalInterfaceAttributesImpl(
            _nameAttribute,
            _parentNameAttribute,
            _positionAttribute,
            _attitudeAttribute
         );
      }
   }

   public HlaPhysicalInterfaceUpdater getHlaPhysicalInterfaceUpdater() {
      return new HlaPhysicalInterfaceUpdaterImpl(this);
   }

   public String getHlaInstanceName() {
      return _objectInstanceHandle.getObjectInstanceName();
   }

   public byte[] getEncodedHlaObjectInstanceHandle() {
      return _objectInstanceHandle.getEncodedHandle();
   }

   public ObjectClassType getClassType() {
      return ObjectClassType.PHYSICAL_INTERFACE;
   }


   public void addHlaPhysicalInterfaceValueListener(HlaPhysicalInterfaceValueListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _valueListeners.add(listener);
   }

   public void removeHlaPhysicalInterfaceValueListener(HlaPhysicalInterfaceValueListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _valueListeners.remove(listener);
   }

   public void addHlaPhysicalInterfaceListener(HlaPhysicalInterfaceListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.add(listener);
   }

   public void removeHlaPhysicalInterfaceListener(HlaPhysicalInterfaceListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.remove(listener);
   }

   /*
    * Functions used by HlaPhysicalInterfaceManagerImpl
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
            sendAttributes(getAttributeEnum(attributes), getHlaPhysicalInterfaceAttributes(), hlaTimeStamp, HlaLogicalTimeImpl.INVALID);
         }
      } catch (HlaBaseException e) {
         //ignore
      } catch (HlaBaseRuntimeException e) {
         //ignore
      }
   }

   Set<String> getUnsetAttributeNames() {
      Set<String> unsetAttributes = new HashSet<String>(HLA_ATTRIBUTE_NAMES.size());
      HlaPhysicalInterfaceAttributes attributes = getHlaPhysicalInterfaceAttributes();
      if (!attributes.hasName()) {
         unsetAttributes.add(NAME_ATTRIBUTE_NAME);
      }
      if (!attributes.hasParentName()) {
         unsetAttributes.add(PARENT_NAME_ATTRIBUTE_NAME);
      }
      if (!attributes.hasPosition()) {
         unsetAttributes.add(POSITION_ATTRIBUTE_NAME);
      }
      if (!attributes.hasAttitude()) {
         unsetAttributes.add(ATTITUDE_ATTRIBUTE_NAME);
      }
      return unsetAttributes;
   }

   @SuppressWarnings ({ "UnnecessaryContinue" })
   void reflectAttributeValues(NameValueMap attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      Set<HlaPhysicalInterfaceAttributes.Attribute> attributesUpdated = EnumSet.noneOf(HlaPhysicalInterfaceAttributes.Attribute.class);

      synchronized (_attributesLock) {
         for (Map.Entry<String, byte[]> newAttribute : attributes.entrySet()) {
            String attributeName = newAttribute.getKey();
            byte[] attributeValue = newAttribute.getValue();

            HlaPhysicalInterfaceAttributes.Attribute attribute = HlaPhysicalInterfaceAttributes.Attribute.find(attributeName);
            if (attribute == null) {
               continue;
            }

            switch (attribute) {
               case NAME: {
                  attributesUpdated.add(HlaPhysicalInterfaceAttributes.Attribute.NAME);

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
               case PARENT_NAME: {
                  attributesUpdated.add(HlaPhysicalInterfaceAttributes.Attribute.PARENT_NAME);

                  if (_valueListeners.isEmpty()) {
                     _parentNameAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateParentName();
                     AttributeValue<String> oldValue = new AttributeValue<String>(_parentNameAttribute);

                     _parentNameAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateParentName();
                     if (_parentNameAttribute.hasValue()) {
                        fireParentNameUpdated(_parentNameAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.PARENT_NAME, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
               case POSITION: {
                  attributesUpdated.add(HlaPhysicalInterfaceAttributes.Attribute.POSITION);

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
               case ATTITUDE: {
                  attributesUpdated.add(HlaPhysicalInterfaceAttributes.Attribute.ATTITUDE);

                  if (_valueListeners.isEmpty()) {
                     _attitudeAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);
                  } else {
                     updateAttitude();
                     AttributeValue<AttitudeQuaternion> oldValue = new AttributeValue<AttitudeQuaternion>(_attitudeAttribute);

                     _attitudeAttribute.setEncodedValue(attributeValue, timeStamp, logicalTime, producingFederate);

                     updateAttitude();
                     if (_attitudeAttribute.hasValue()) {
                        fireAttitudeUpdated(_attitudeAttribute.getValue(), oldValue, timeStamp, logicalTime);
                     }
                     fireProducingFederateUpdatedIfChanged(Attribute.ATTITUDE, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  }
                  break;
               }
            }
         }
      }

      fireAttributesUpdated(attributesUpdated, timeStamp, logicalTime);
   }



   /*
    * Functions used by HlaPhysicalInterfaceUpdaterImpl
    */

   void applyUpdate(EnumMap<HlaPhysicalInterfaceAttributes.Attribute, Object> attributeMap,
                    EnumSet<HlaPhysicalInterfaceAttributes.Attribute> sendAttributes,
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
         HlaPhysicalInterfaceAttributes attributes = applyUpdate(attributeMap, timestamp, logicalTime, _hlaWorld.getFederateId());
         sendAttributes.addAll(addDefaultSendAttributes(attributeMap.keySet()));
         sendAttributes(sendAttributes, attributes, timestamp, logicalTime);
      }
   }


   /*
    * Private functions
    */

   private Set<HlaPhysicalInterfaceAttributes.Attribute> addDefaultSendAttributes(Set<HlaPhysicalInterfaceAttributes.Attribute> attributes) {
      return attributes;
   }

   private void fireNameUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaPhysicalInterface instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaPhysicalInterfaceValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.nameUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireParentNameUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaPhysicalInterface instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaPhysicalInterfaceValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.parentNameUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void firePositionUpdated(final double[/* 3 */] value, AttributeValue<double[/* 3 */]> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaPhysicalInterface instance = this;
      final boolean oldValid = previous.hasValue();
      final double[/* 3 */] oldValue = oldValid ? previous.getValue() : value;

      for (final HlaPhysicalInterfaceValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.positionUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireAttitudeUpdated(final AttitudeQuaternion value, AttributeValue<AttitudeQuaternion> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaPhysicalInterface instance = this;
      final boolean oldValid = previous.hasValue();
      final AttitudeQuaternion oldValue = oldValid ? previous.getValue() : value;

      for (final HlaPhysicalInterfaceValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.attitudeUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireAttributesUpdated(final Set<HlaPhysicalInterfaceAttributes.Attribute> attributes, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaPhysicalInterface instance = this;
      for (final HlaPhysicalInterfaceListener listener : _listeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               listener.attributesUpdated(instance, attributes, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireProducingFederateUpdatedIfChanged(final HlaPhysicalInterfaceAttributes.Attribute attribute, final HlaFederateId oldProducingFederate, final HlaFederateId newProducingFederate, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      if (Equals.isEquals(oldProducingFederate, newProducingFederate)) {
         return;
      }

      final HlaPhysicalInterface instance = this;
      for (final HlaPhysicalInterfaceValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.producingFederateUpdated(instance, attribute, oldProducingFederate, newProducingFederate, timeStamp, logicalTime);
            }
         });
      }
   }

   @SuppressWarnings ({ "UnnecessaryContinue" })
   private Set<HlaPhysicalInterfaceAttributes.Attribute> getAttributeEnum(Set<String> attributeNames) {
      Set<HlaPhysicalInterfaceAttributes.Attribute> ret = EnumSet.noneOf(HlaPhysicalInterfaceAttributes.Attribute.class);

      for (String attributeName : attributeNames) {
         HlaPhysicalInterfaceAttributes.Attribute attribute = HlaPhysicalInterfaceAttributes.Attribute.find(attributeName);
         if (attribute != null) {
            ret.add(attribute);
         }
      }
      return ret;
   }

   /* @GuardedBy("_sendLock") */
   private HlaPhysicalInterfaceAttributes applyUpdate(EnumMap<HlaPhysicalInterfaceAttributes.Attribute, Object> attributeUpdates, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      HlaPhysicalInterfaceAttributes ret;

      synchronized (_attributesLock) {
         for (Map.Entry<HlaPhysicalInterfaceAttributes.Attribute, Object> attributeUpdate : attributeUpdates.entrySet()) {
            switch (attributeUpdate.getKey()) {
               case NAME: {
                  updateName();
                  AttributeValue<String> oldValue = new AttributeValue<String>(_nameAttribute);

                  String value = (String)attributeUpdate.getValue();
                  _nameAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireNameUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.NAME, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case PARENT_NAME: {
                  updateParentName();
                  AttributeValue<String> oldValue = new AttributeValue<String>(_parentNameAttribute);

                  String value = (String)attributeUpdate.getValue();
                  _parentNameAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireParentNameUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.PARENT_NAME, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case POSITION: {
                  updatePosition();
                  AttributeValue<double[/* 3 */]> oldValue = new AttributeValue<double[/* 3 */]>(_positionAttribute);

                  double[/* 3 */] value = (double[/* 3 */])attributeUpdate.getValue();
                  _positionAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  firePositionUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.POSITION, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
               case ATTITUDE: {
                  updateAttitude();
                  AttributeValue<AttitudeQuaternion> oldValue = new AttributeValue<AttitudeQuaternion>(_attitudeAttribute);

                  AttitudeQuaternion value = (AttitudeQuaternion)attributeUpdate.getValue();
                  _attitudeAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireAttitudeUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.ATTITUDE, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
            }
         }
         ret = getHlaPhysicalInterfaceAttributes();
      }

      if (!attributeUpdates.isEmpty()) {
         fireAttributesUpdated(attributeUpdates.keySet(), timeStamp, logicalTime);
      }

      return ret;
   }

   /* @GuardedBy("_sendLock") */
   private void sendAttributes(Set<HlaPhysicalInterfaceAttributes.Attribute> attributes, HlaPhysicalInterfaceAttributes attributeValues, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      NameValueMap attributeValueMap = new NameValueMap();

      synchronized (_objectClassManager._encodersLock) {
         for (HlaPhysicalInterfaceAttributes.Attribute attribute : attributes) {
            switch (attribute) {
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
               case PARENT_NAME:
                  if (attributeValues.hasParentName()) {
                     try {
                        _objectClassManager._hLAunicodeStringEncoder.setValue(attributeValues.getParentName());
                        attributeValueMap.put(PARENT_NAME_ATTRIBUTE_NAME, _objectClassManager._hLAunicodeStringEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + PARENT_NAME_ATTRIBUTE_NAME, t));
                     }
                  }
                  break;
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
               case ATTITUDE:
                  if (attributeValues.hasAttitude()) {
                     try {
                        _objectClassManager._attitudeQuaternionEncoderEncoder.setValue(attributeValues.getAttitude());
                        attributeValueMap.put(ATTITUDE_ATTRIBUTE_NAME, _objectClassManager._attitudeQuaternionEncoderEncoder.toByteArray(), false);
                     } catch (Throwable t) {
                        _hlaWorld.postException(new HlaDecodeException("Failed to encode " + ATTITUDE_ATTRIBUTE_NAME, t));
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
