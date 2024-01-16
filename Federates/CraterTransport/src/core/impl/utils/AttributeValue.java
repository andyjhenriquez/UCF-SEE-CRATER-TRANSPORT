package core.impl.utils;

/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
import core.HlaFederateId;
import core.HlaLogicalTime;
import core.HlaTimeStamp;
import core.HlaTimeStamped;

/* @NotThreadSafe */
public final class AttributeValue<T> extends Value<T>{
   private byte[] _encodedValue;  //overrides _value if != null, used for lazy decoding
   private HlaTimeStamp _timeStamp;
   private HlaLogicalTime _logicalTime;
   private HlaFederateId _lastProducingFederate;

   public AttributeValue(AttributeValue<T> attributeValue) {
      super(attributeValue);
      _encodedValue = null;
      _timeStamp = attributeValue.getTimeStamp();
      _logicalTime = attributeValue.getLogicalTime();
      _lastProducingFederate = attributeValue.getLastProducingFederate();
   }

   public AttributeValue() {
      super();
   }

   public void setValue(T value, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      setValue(value);
      _encodedValue = null;
      _timeStamp = timeStamp;
      _logicalTime = logicalTime;
      _lastProducingFederate = producingFederate;
   }

   public void setEncodedValue(byte[] encodedValue, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime, HlaFederateId producingFederate) {
      _encodedValue = encodedValue;
      _timeStamp = timeStamp;
      _logicalTime = logicalTime;
      _lastProducingFederate = producingFederate;
   }

   public void clearEncodedValue() {
      _encodedValue = null;
   }

   public void setDecodedValue(T value) {
      setValue(value);
      _encodedValue = null;
      // keep _timestamp and _lastProducingFederate
   }

   public byte[] getEncodedValue() {
      return _encodedValue;
   }

   public boolean hasLastProducingFederate() {
      return _lastProducingFederate != null;
   }

   public HlaFederateId getLastProducingFederate() {
      return _lastProducingFederate;
   }

   public HlaTimeStamp getTimeStamp() {
      return _timeStamp;
   }

   public HlaLogicalTime getLogicalTime() {
      return _logicalTime;
   }

   private static class TimeStampedImpl<T> implements HlaTimeStamped<T> {
      private final T _value;
      private final HlaTimeStamp _timeStamp;
      private final HlaLogicalTime _logicalTime;

      private TimeStampedImpl(T value, HlaTimeStamp timeStamp, HlaLogicalTime logicalTime) {
         _value = value;
         _timeStamp = timeStamp;
         _logicalTime = logicalTime;
      }

      public T getValue() {
         return _value;
      }

      public HlaTimeStamp getTimeStamp() {
         return _timeStamp;
      }

      public HlaLogicalTime getLogicalTime() {
         return _logicalTime;
      }
   }

   public HlaTimeStamped<T> getTimestampedValueForUser() {
      return new TimeStampedImpl<T>(getValueForUser(), _timeStamp, _logicalTime);
   }
}
