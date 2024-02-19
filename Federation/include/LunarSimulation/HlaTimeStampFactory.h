/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLATIMESTAMPFACTORY_H
#define DEVELOPER_STUDIO_HLATIMESTAMPFACTORY_H

#ifdef _WIN32
#pragma warning( disable : 4290 )
#endif

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaTimeStamp.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
    /**
    * A factory class for creating HlaTimeStamps
    */
    class HlaTimeStampFactory : private LunarSimulation::noncopyable {
    public:
        /**
        * Create a timestamp for the current time.
        *
        * @return A timestamp for the current time.
        */
        LIBAPI virtual HlaTimeStampPtr create() = 0;

        /**
        * Create a timestamp from a user supplied tag.
        * If the timestamp is not based on the user supplied tag it may be ignored.
        *
        * @param userSuppliedTag the user supplied tag that represents the current time
        *
        * @return A timestamp for the time represented by the user supplied tag.
        */
        LIBAPI virtual HlaTimeStampPtr create(const RtiDriver::VariableLengthData& userSuppliedTag);

        /**
        * Create a timestamp based on a reference timestamp and an offset
        *
        * @param reference the timestamp to use as a reference
        * @param offset    the offset in seconds
        *
        * @return A timestamp calculated from reference and offset.
        */
        LIBAPI virtual HlaTimeStampPtr create(const HlaTimeStampPtr reference, double offset);

        /**
        * Get the predefined HlaTimeStampFactory with the supplied name.
        *
        * @param name Name of the predefined HlaTimeStampFactory
        *
        * @return The predefined HlaTimeStampFactory or <code>null</code>.
        */
        LIBAPI static HlaTimeStampFactoryPtr getHlaTimeStampFactory(const std::wstring& name);

        LIBAPI virtual ~HlaTimeStampFactory() {}

        class AbstractTimeStamp;
    };

    /**
    * Class for creating AbstractTimeStamps
    */
    class HlaTimeStampFactory::AbstractTimeStamp : public HlaTimeStamp {
    public: 

        /** 
        * Get a 64 bit representation of the timestamp.
        * 
        * @return uint64 representation of the timestamp.
        */
        LIBAPI virtual unsigned long long getValue() const = 0;

        /** 
        * Get a wstring representation of the timestamp
        * 
        * @return a wstring representation of this timestamp
        */
        LIBAPI virtual std::wstring toString() const = 0;

        /**
        * Get user supplied tag to send for this timestamp.
        *
        * @return The user supplied tag to send for this timestamp.
        */
        LIBAPI virtual RtiDriver::VariableLengthData getUserSuppliedTag() const {
            return RtiDriver::VariableLengthData();
        }

        /**
        * Calculates the time since an other timestamp.
        *
        * @param timestamp The previous timestamp
        *
        * @return The time in seconds
        */
        LIBAPI virtual double secondsSince(HlaTimeStampPtr timestamp) const = 0;

    };

    /**
    * Empty timestamp.
    */
    class EmptyTimeStamp : public HlaTimeStampFactory::AbstractTimeStamp {
    public:
        LIBAPI unsigned long long getValue() const {
            return 0;
        }

        LIBAPI std::wstring toString() const {
            return L"-";
        }

        LIBAPI double secondsSince(HlaTimeStampPtr timestamp) const {
            return 0.0;
        }

    };

    /**
    * Create a factory that will generate empty timestamps.
    */
    class EmptyTimeStampFactory : public HlaTimeStampFactory {
    public:
        LIBAPI HlaTimeStampPtr create() {
            return HlaTimeStampPtr(new EmptyTimeStamp());
        }
    };

    /**
    * System clock timestamp.
    */
    class SystemClockTimeStamp : public HlaTimeStampFactory::AbstractTimeStamp {
    private:
        const unsigned long long _value;

    public:
      /**
       * Create a system clock timestamp for the current time.
       */
        LIBAPI SystemClockTimeStamp();

        /**
        * Get a 64 bit representation of the timestamp.
        * The time is in milliseconds (since midnight, January 1, 1970 UTC).
        *
        * @return uint64 representation of the timestamp.
        */
        LIBAPI unsigned long long getValue() const {
            return _value;
        }

        std::wstring toString() const;

        /**
        * Calculates the time since an other timestamp.
        *
        * @param timestamp The previous timestamp
        *
        * @return The time in seconds
        */
        LIBAPI double secondsSince(HlaTimeStampPtr timestamp) const;

    };

    /**
    * Create a factory that will generate timestamps based on system clock.
    */
    class SystemClockTimeStampFactory : public HlaTimeStampFactory {
    public:
        LIBAPI HlaTimeStampPtr create();
    };

    /**
    * RPR timestamp impl
    */
    class RprTimeStamp : public HlaTimeStampFactory::AbstractTimeStamp {
    private:
        bool _valid;
        bool _absolute;
        unsigned long long _micros;
        const HlaTimeStampPtr _arrivalTime;

    public:
        /**
        * Create a absolute RprTimeStamp for the current time.
        */
        LIBAPI RprTimeStamp();

        /**
        * Create a relative RprTimeStamp for the current time.
        *
        * @param startupTimeMilli the startup time in millis
        */
        LIBAPI RprTimeStamp(unsigned long long startupTimeMilli);

        /**
        * Create a RprTimeStamp based on a parameter.
        *
        * @param micros the timestamp value
        * @param absolute true if absolute timestamp
        */
        LIBAPI RprTimeStamp(unsigned long long micros, bool absolute);

        /**
        * Create an RprTimeStamp from a user supplied tag.
        *
        * @param userSuppliedTag the user supplied tag
        */
        LIBAPI RprTimeStamp(const RtiDriver::VariableLengthData& userSuppliedTag);

        /**
        * Function to check if the timestamp is valid.
        *
        * @return True if the timestamp is valid, false if not.
        */
        LIBAPI bool isValid() {
            return _valid;
        }

        /**
        * Function to check if the timestamp uses relative or absolute time.
        *
        * @return True if absolute time, false if not.
        */
        LIBAPI bool isAbsolute() {
            return _absolute;
        }

        /**
        * Function to check if the timestamp has a specified arrival time.
        *
        * @return True if arrival time is specified, false if not
        */
        LIBAPI bool hasArrivalTime() {
            return _arrivalTime.get() != 0;
        }

        /**
        * Gets the arrival time if it is specified, otherwise returns currentTime
        *
        * @return The arrival time if it is specified, otherwise the currentTime.
        */
        LIBAPI HlaTimeStampPtr getArrivalTime() {
            return hasArrivalTime() ? _arrivalTime : HlaTimeStampPtr(this);
        }

        /**
        * Get a 64 bit representation of the timestamp.
        * The time is in microseconds (since the last hour).
        *
        * @return uint64 representation of the timestamp.
        */
        LIBAPI unsigned long long getValue() const {
            return _micros;
        }

        LIBAPI RtiDriver::VariableLengthData getUserSuppliedTag() const;

        LIBAPI std::wstring toString() const;

        /**
        * Calculates the time since an other timestamp.
        *
        * @param timestamp The previous timestamp
        *
        * @return The time in seconds
        */
        LIBAPI double secondsSince(HlaTimeStampPtr timestamp) const;

    };

    /**
    * Create a factory that will generate absolute RPR FOM timestamps.
    */
    class RprAbsoluteFactory : public HlaTimeStampFactory {
    public:
        /**
        * Create an absolute RprTimeStamp.
        *
        * @param micros the timestamp value
        */
        LIBAPI HlaTimeStampPtr create(unsigned long long micros) {
            return HlaTimeStampPtr(new RprTimeStamp(micros, true));
        }

        LIBAPI HlaTimeStampPtr create() {
            return HlaTimeStampPtr(new RprTimeStamp());
        }

        LIBAPI HlaTimeStampPtr create(const HlaTimeStampPtr reference, double offset) {
            unsigned long long when = reference->getValue() + (unsigned long long)(1E+6 * offset);
            return HlaTimeStampPtr(new RprTimeStamp(when, true));
        }

        LIBAPI HlaTimeStampPtr create(const RtiDriver::VariableLengthData& userSuppliedTag) {
            return HlaTimeStampPtr(new RprTimeStamp(userSuppliedTag));
        }
    };

    /**
    * Create a factory that will generate relative RPR FOM timestamps.
    */
    class RprRelativeFactory : public HlaTimeStampFactory {
    public:
        /**
        * Create a factory that will generate relative RPR FOM timestamps, using the current time as startup time.
        */
        LIBAPI RprRelativeFactory();

        /**
        * Create a factory that will generate relative RPR FOM timestamps, using the supplied startup time.
        *
        * @param startupTime the startupTime in millis
        */
        LIBAPI RprRelativeFactory(unsigned long long startupTime) :
            _startupTime(startupTime) {
        }

        /**
        * Create a relative RprTimeStamp.
        *
        * @param micros the timestamp value
        */
        LIBAPI HlaTimeStampPtr create(unsigned long long micros) {
            return HlaTimeStampPtr(new RprTimeStamp(micros, false));
        }

        LIBAPI HlaTimeStampPtr create() {
            return HlaTimeStampPtr(new RprTimeStamp(_startupTime));
        }

        LIBAPI HlaTimeStampPtr create(const HlaTimeStampPtr reference, double offset) {
            unsigned long long when = reference->getValue() + (unsigned long long)(1E+6 * offset);
            return HlaTimeStampPtr(new RprTimeStamp(when, false));
        }

        LIBAPI HlaTimeStampPtr create(const RtiDriver::VariableLengthData& userSuppliedTag) {
            return HlaTimeStampPtr(new RprTimeStamp(userSuppliedTag));
        }

        /**
        * Get the startup time for relative RPR FOM timestamps.
        *
        * @return The startup time for relative RPR FOM timestamps.
        */
        LIBAPI unsigned long long getStartupTime() {
            return _startupTime;
        }
        

    private:
        const unsigned long long _startupTime;
    };
}
#endif
