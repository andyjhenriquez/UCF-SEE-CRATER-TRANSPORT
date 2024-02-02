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
import core.HlaPhysicalInterfaceAttributes;
import core.HlaTimeStamped;
import core.exceptions.HlaValueNotSetException;
import core.impl.utils.AttributeValue;

/* @Immutable */
final class HlaPhysicalInterfaceAttributesImpl implements HlaPhysicalInterfaceAttributes {

   private final AttributeValue<String> _name;
   private final AttributeValue<String> _parentName;
   private final AttributeValue<double[/* 3 */]> _position;
   private final AttributeValue<AttitudeQuaternion> _attitude;

   HlaPhysicalInterfaceAttributesImpl(
      AttributeValue<String> name,
      AttributeValue<String> parentName,
      AttributeValue<double[/* 3 */]> position,
      AttributeValue<AttitudeQuaternion> attitude
   ) {
      _name = new AttributeValue<String>(name);
      _parentName = new AttributeValue<String>(parentName);
      _position = new AttributeValue<double[/* 3 */]>(position);
      _attitude = new AttributeValue<AttitudeQuaternion>(attitude);
   }

   public boolean hasName() {
      return _name.hasValue();
   }

   public String getName() throws HlaValueNotSetException {
      if (_name.hasValue()) {
         return _name.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'name' not set");
   }

   public String getName(String defaultValue) {
      if (_name.hasValue()) {
         return _name.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getNameTimeStamped() throws HlaValueNotSetException {
      if (_name.hasValue()) {
         return _name.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'name' not set");
   }

   public boolean hasParentName() {
      return _parentName.hasValue();
   }

   public String getParentName() throws HlaValueNotSetException {
      if (_parentName.hasValue()) {
         return _parentName.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'parentName' not set");
   }

   public String getParentName(String defaultValue) {
      if (_parentName.hasValue()) {
         return _parentName.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<String> getParentNameTimeStamped() throws HlaValueNotSetException {
      if (_parentName.hasValue()) {
         return _parentName.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'parentName' not set");
   }

   public boolean hasPosition() {
      return _position.hasValue();
   }

   public double[/* 3 */] getPosition() throws HlaValueNotSetException {
      if (_position.hasValue()) {
         return _position.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'position' not set");
   }

   public double[/* 3 */] getPosition(double[/* 3 */] defaultValue) {
      if (_position.hasValue()) {
         return _position.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<double[/* 3 */]> getPositionTimeStamped() throws HlaValueNotSetException {
      if (_position.hasValue()) {
         return _position.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'position' not set");
   }

   public boolean hasAttitude() {
      return _attitude.hasValue();
   }

   public AttitudeQuaternion getAttitude() throws HlaValueNotSetException {
      if (_attitude.hasValue()) {
         return _attitude.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'attitude' not set");
   }

   public AttitudeQuaternion getAttitude(AttitudeQuaternion defaultValue) {
      if (_attitude.hasValue()) {
         return _attitude.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<AttitudeQuaternion> getAttitudeTimeStamped() throws HlaValueNotSetException {
      if (_attitude.hasValue()) {
         return _attitude.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'attitude' not set");
   }

}
