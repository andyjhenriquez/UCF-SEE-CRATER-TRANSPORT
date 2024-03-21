/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLATIMESTAMP_H
#define DEVELOPER_STUDIO_HLATIMESTAMP_H

#include <vector>

#include <RtiDriver/Types.h>

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
    /**
    * A timestamp representing the time the message was created.
    */
    class HlaTimeStamp : private LunarSimulation::noncopyable {

    public:
        /**
        * Get a (64 bit) representation of the timestamp.
        *
        * @return A uint64 representation of the timestamp.
        */
        LIBAPI virtual unsigned long long getValue() const = 0;

        /**
        * Get user supplied tag to send for this timestamp.
        *
        * @return The user supplied tag to send for this timestamp.
        */
        LIBAPI virtual RtiDriver::VariableLengthData getUserSuppliedTag() const = 0;

        /**
        * Calculates the time since an other timestamp.
        *
        * @param timestamp The other timestamp
        *
        * @return The time difference in seconds
        */
        LIBAPI virtual double secondsSince(HlaTimeStampPtr timestamp) const = 0;

        /**
        * Get a wstring representation of the timestamp.
        *
        * @return A wstring representation of the timestamp.
        */
        LIBAPI virtual std::wstring toString() const = 0;

        LIBAPI virtual ~HlaTimeStamp() {}
    };
}
#endif
