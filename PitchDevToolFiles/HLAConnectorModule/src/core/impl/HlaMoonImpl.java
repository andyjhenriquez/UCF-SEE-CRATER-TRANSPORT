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
final class HlaMoonImpl implements HlaMoon {


   private static final String NAME_ATTRIBUTE_NAME = "name";
   private static final String PARENT_NAME_ATTRIBUTE_NAME = "parent_name";
   private static final String STATE_ATTRIBUTE_NAME = "state";

   public static final Set<String> HLA_ATTRIBUTE_NAMES = new SetAdapter<String>()
         .append(NAME_ATTRIBUTE_NAME)
         .append(PARENT_NAME_ATTRIBUTE_NAME)
         .append(STATE_ATTRIBUTE_NAME)
         .unmodifiableSet();


   private final HlaWorldImpl _hlaWorld;
   private final HlaMoonManagerImpl _objectClassManager;
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
   private final AttributeValue<SpaceTimeCoordinateState> _stateAttribute = new AttributeValue<SpaceTimeCoordinateState>();

   private final Set<HlaMoonValueListener> _valueListeners = new CopyOnWriteArraySet<HlaMoonValueListener>();
   private final Set<HlaMoonListener> _listeners = new CopyOnWriteArraySet<HlaMoonListener>();

   private volatile boolean _initializeFired = false;
   private volatile boolean _removed = false;

   HlaMoonImpl(HlaWorldImpl hlaWorld, HlaMoonManagerImpl objectClassManager, ObjectInstanceHandle objectInstanceHandle, boolean local, HlaFederateId producingFederate) {
      _hlaWorld = hlaWorld;
      _objectClassManager = objectClassManager;
      _objectInstanceHandle = objectInstanceHandle;
      _isLocal = local;
      _createdByFederate = producingFederate;
   }

   /*
    * HlaMoon interface impl
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

   public HlaFederateId getProducingFederate() {
      return _createdByFederate;
   }

   public HlaFederateId getLastProducingFederate(HlaMoonAttributes.Attribute attribute) {
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
            case STATE:
               if (_stateAttribute.hasLastProducingFederate()) {
                  return _stateAttribute.getLastProducingFederate();
               }
         }
      }
      return new HlaFederateIdImpl(null);
   }

   public HlaMoonAttributes getHlaMoonAttributes() {
      synchronized (_attributesLock) {
         updateName();
         updateParentName();
         updateState();
         return new HlaMoonAttributesImpl(
            _nameAttribute,
            _parentNameAttribute,
            _stateAttribute
         );
      }
   }

   public HlaMoonUpdater getHlaMoonUpdater() {
      return new HlaMoonUpdaterImpl(this);
   }

   public String getHlaInstanceName() {
      return _objectInstanceHandle.getObjectInstanceName();
   }

   public byte[] getEncodedHlaObjectInstanceHandle() {
      return _objectInstanceHandle.getEncodedHandle();
   }

   public ObjectClassType getClassType() {
      return ObjectClassType.MOON;
   }


   public void addHlaMoonValueListener(HlaMoonValueListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _valueListeners.add(listener);
   }

   public void removeHlaMoonValueListener(HlaMoonValueListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _valueListeners.remove(listener);
   }

   public void addHlaMoonListener(HlaMoonListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.add(listener);
   }

   public void removeHlaMoonListener(HlaMoonListener listener) {
       if (listener == null) {
           throw new NullPointerException();
       }
      _listeners.remove(listener);
   }

   /*
    * Functions used by HlaMoonManagerImpl
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
            sendAttributes(getAttributeEnum(attributes), getHlaMoonAttributes(), hlaTimeStamp, HlaLogicalTimeImpl.INVALID);
         }
      } catch (HlaBaseException e) {
         //ignore
      } catch (HlaBaseRuntimeException e) {
         //ignore
      }
   }

   Set<String> getUnsetAttributeNames() {
      Set<String> unsetAttributes = new HashSet<String>(HLA_ATTRIBUTE_NAMES.size());
      HlaMoonAttributes attributes = getHlaMoonAttributes();
      if (!attributes.hasName()) {
         unsetAttributes.add(NAME_ATTRIBUTE_NAME);
      }
      if (!attributes.hasParentName()) {
         unsetAttributes.add(PARENT_NAME_ATTRIBUTE_NAME);
      }
      if (!attributes.hasState()) {
         unsetAttributes.add(STATE_ATTRIBUTE_NAME);
      }
      return unsetAttributes;
   }

   @SuppressWarnings ({ "UnnecessaryContinue" })
   void reflectAttributeValues(NameValueMap attributes, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      Set<HlaMoonAttributes.Attribute> attributesUpdated = EnumSet.noneOf(HlaMoonAttributes.Attribute.class);

      synchronized (_attributesLock) {
         for (Map.Entry<String, byte[]> newAttribute : attributes.entrySet()) {
            String attributeName = newAttribute.getKey();
            byte[] attributeValue = newAttribute.getValue();

            HlaMoonAttributes.Attribute attribute = HlaMoonAttributes.Attribute.find(attributeName);
            if (attribute == null) {
               continue;
            }

            switch (attribute) {
               case NAME: {
                  attributesUpdated.add(HlaMoonAttributes.Attribute.NAME);

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
                  attributesUpdated.add(HlaMoonAttributes.Attribute.PARENT_NAME);

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
               case STATE: {
                  attributesUpdated.add(HlaMoonAttributes.Attribute.STATE);

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
            }
         }
      }

      fireAttributesUpdated(attributesUpdated, timeStamp, logicalTime);
   }



   /*
    * Functions used by HlaMoonUpdaterImpl
    */

   void applyUpdate(EnumMap<HlaMoonAttributes.Attribute, Object> attributeMap,
                    EnumSet<HlaMoonAttributes.Attribute> sendAttributes,
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
         HlaMoonAttributes attributes = applyUpdate(attributeMap, timestamp, logicalTime, _hlaWorld.getFederateId());
         sendAttributes.addAll(addDefaultSendAttributes(attributeMap.keySet()));
         sendAttributes(sendAttributes, attributes, timestamp, logicalTime);
      }
   }


   /*
    * Private functions
    */

   private Set<HlaMoonAttributes.Attribute> addDefaultSendAttributes(Set<HlaMoonAttributes.Attribute> attributes) {
      return attributes;
   }

   private void fireNameUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaMoon instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaMoonValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.nameUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireParentNameUpdated(final String value, AttributeValue<String> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaMoon instance = this;
      final boolean oldValid = previous.hasValue();
      final String oldValue = oldValid ? previous.getValue() : value;

      for (final HlaMoonValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.parentNameUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireStateUpdated(final SpaceTimeCoordinateState value, AttributeValue<SpaceTimeCoordinateState> previous, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaMoon instance = this;
      final boolean oldValid = previous.hasValue();
      final SpaceTimeCoordinateState oldValue = oldValid ? previous.getValue() : value;

      for (final HlaMoonValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.stateUpdated(instance, value, oldValid, oldValue, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireAttributesUpdated(final Set<HlaMoonAttributes.Attribute> attributes, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      final HlaMoon instance = this;
      for (final HlaMoonListener listener : _listeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               listener.attributesUpdated(instance, attributes, timeStamp, logicalTime);
            }
         });
      }
   }

   private void fireProducingFederateUpdatedIfChanged(final HlaMoonAttributes.Attribute attribute, final HlaFederateId oldProducingFederate, final HlaFederateId newProducingFederate, final HlaTimeStamp timeStamp, final HlaLogicalTime logicalTime) {
      if (Equals.isEquals(oldProducingFederate, newProducingFederate)) {
         return;
      }

      final HlaMoon instance = this;
      for (final HlaMoonValueListener valueListener : _valueListeners) {
         _hlaWorld.postNotification(new Runnable() {
            public void run() {
               valueListener.producingFederateUpdated(instance, attribute, oldProducingFederate, newProducingFederate, timeStamp, logicalTime);
            }
         });
      }
   }

   @SuppressWarnings ({ "UnnecessaryContinue" })
   private Set<HlaMoonAttributes.Attribute> getAttributeEnum(Set<String> attributeNames) {
      Set<HlaMoonAttributes.Attribute> ret = EnumSet.noneOf(HlaMoonAttributes.Attribute.class);

      for (String attributeName : attributeNames) {
         HlaMoonAttributes.Attribute attribute = HlaMoonAttributes.Attribute.find(attributeName);
         if (attribute != null) {
            ret.add(attribute);
         }
      }
      return ret;
   }

   /* @GuardedBy("_sendLock") */
   private HlaMoonAttributes applyUpdate(EnumMap<HlaMoonAttributes.Attribute, Object> attributeUpdates, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      HlaMoonAttributes ret;

      synchronized (_attributesLock) {
         for (Map.Entry<HlaMoonAttributes.Attribute, Object> attributeUpdate : attributeUpdates.entrySet()) {
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
               case STATE: {
                  updateState();
                  AttributeValue<SpaceTimeCoordinateState> oldValue = new AttributeValue<SpaceTimeCoordinateState>(_stateAttribute);

                  SpaceTimeCoordinateState value = (SpaceTimeCoordinateState)attributeUpdate.getValue();
                  _stateAttribute.setValue(value, timeStamp, logicalTime, producingFederate);

                  fireStateUpdated(value, oldValue, timeStamp, logicalTime);
                  fireProducingFederateUpdatedIfChanged(Attribute.STATE, oldValue.getLastProducingFederate(), producingFederate, timeStamp, logicalTime);
                  break;
               }
            }
         }
         ret = getHlaMoonAttributes();
      }

      if (!attributeUpdates.isEmpty()) {
         fireAttributesUpdated(attributeUpdates.keySet(), timeStamp, logicalTime);
      }

      return ret;
   }

   /* @GuardedBy("_sendLock") */
   private void sendAttributes(Set<HlaMoonAttributes.Attribute> attributes, HlaMoonAttributes attributeValues, HlaTimeStamp timestamp, HlaLogicalTime logicalTime)
         throws HlaNotConnectedException, HlaAttributeNotOwnedException, HlaInternalException, HlaRtiException, HlaObjectInstanceIsRemovedException, HlaInvalidLogicalTimeException,
                HlaSaveInProgressException, HlaRestoreInProgressException {
      NameValueMap attributeValueMap = new NameValueMap();

      synchronized (_objectClassManager._encodersLock) {
         for (HlaMoonAttributes.Attribute attribute : attributes) {
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
            }
         }
      }

      if (!attributeValueMap.isEmpty()) {
         _objectClassManager.updateAttributeValues(this, _objectInstanceHandle, attributeValueMap, timestamp, logicalTime);
      }
   }
}
