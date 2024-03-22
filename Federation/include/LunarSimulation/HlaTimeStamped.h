/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */

#ifndef DEVELOPER_STUDIO_HLATIMESTAMPED_H
#define DEVELOPER_STUDIO_HLATIMESTAMPED_H

#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPointers.h>


namespace LunarSimulation {

/**
* A timestamped value.
*/
template <class T> class HlaTimeStamped {
public:
    /**
    * Get the value associated with the timestamp.
    *
    * @return The value associated with the timestamp.
    */
    const T getValue() const {
       return _value;
    }

    /**
    * Get the timestamp associated with the value.
    *
    * @return The timestamp associated with the value.
    */
    const HlaTimeStampPtr getTimeStamp() const {
       return _timeStamp;
    }

    /**
    * Get the logical time associated with the value.
    *
    * @return The logical time associated with the value.
    */
    const HlaLogicalTimePtr getLogicalTime() const {
       return _logicalTime;
    }

    /**
    * Constructor
    *
    * @param value The value associated with the timestamp.
    * @param timeStamp The timestamp associated with the value.
    * @param logicalTime The logical time associated with the value.
    */
    HlaTimeStamped(T value, HlaTimeStampPtr timeStamp, HlaLogicalTimePtr logicalTime) :
       _value(value), _timeStamp(timeStamp), _logicalTime(logicalTime) {
    }

private:
    const T _value;
    const HlaTimeStampPtr _timeStamp;
    const HlaLogicalTimePtr _logicalTime;

};
}
#endif
