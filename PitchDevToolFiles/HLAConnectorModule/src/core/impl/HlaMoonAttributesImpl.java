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
import core.HlaMoonAttributes;
import core.HlaTimeStamped;
import core.exceptions.HlaValueNotSetException;
import core.impl.utils.AttributeValue;

/* @Immutable */
final class HlaMoonAttributesImpl implements HlaMoonAttributes {

   private final AttributeValue<String> _name;
   private final AttributeValue<String> _parentName;
   private final AttributeValue<SpaceTimeCoordinateState> _state;

   HlaMoonAttributesImpl(
      AttributeValue<String> name,
      AttributeValue<String> parentName,
      AttributeValue<SpaceTimeCoordinateState> state
   ) {
      _name = new AttributeValue<String>(name);
      _parentName = new AttributeValue<String>(parentName);
      _state = new AttributeValue<SpaceTimeCoordinateState>(state);
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

   public boolean hasState() {
      return _state.hasValue();
   }

   public SpaceTimeCoordinateState getState() throws HlaValueNotSetException {
      if (_state.hasValue()) {
         return _state.getValue();
      }
      throw new HlaValueNotSetException("Attribute 'state' not set");
   }

   public SpaceTimeCoordinateState getState(SpaceTimeCoordinateState defaultValue) {
      if (_state.hasValue()) {
         return _state.getValue();
      }
      return defaultValue;
   }

   public HlaTimeStamped<SpaceTimeCoordinateState> getStateTimeStamped() throws HlaValueNotSetException {
      if (_state.hasValue()) {
         return _state.getTimestampedValueForUser();
      }
      throw new HlaValueNotSetException("Attribute 'state' not set");
   }

}
