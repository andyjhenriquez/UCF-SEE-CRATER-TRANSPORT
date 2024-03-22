/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAPACER_H
#define DEVELOPER_STUDIO_HLAPACER_H

#include <LunarSimulation/HlaPointers.h>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {
   /**
    * Utility class to support pacing to wall clock time, or any other time source.
    */
   class HlaPacer : private LunarSimulation::noncopyable {
   public:

      /**
       * Interface for a custom time source.
       */
      class Source : private LunarSimulation::noncopyable {
      public:
         /**
          * Initialize the time source.
          *
          * @param offsetNs start offset, in nanoseconds.
          *
          * @return if the time source was initialized.
          */
         LIBAPI virtual bool initialize(unsigned long long offsetNs) = 0;

         /**
          * Get number of nanoseconds [ns] since the time source was initialized.
          *
          * @return the number of nanoseconds [ns] since the time source was initialized.
          */
         LIBAPI virtual unsigned long long getNanosecondsSinceInitialize() const = 0;

         LIBAPI virtual ~Source() {}
      };
      typedef std::shared_ptr<Source> SourcePtr; /**< Pointer (shared_ptr) to the abstract class Source. */

      /**
       * Initialize or restart the pacer.
       *
       * @param initialFrame the initial frame
       *
       * @return <code>true</code> if the pacer was initialized, <code>false</code> otherwise
       */
      LIBAPI virtual bool initialize(unsigned long long initialFrame) = 0;

      /**
       * Pace the pacer to the next frame.
       *
       * @return <code>false</code> on frame overrun, <code>true</code> otherwise.
       */
      LIBAPI virtual bool pace() = 0;

      /**
       * Get the time in nanoseconds [ns] since the pacer was created or initialized.
       *
       * @return the time in nanoseconds [ns] since the pacer was created or initialized.
       */
      LIBAPI virtual unsigned long long getNanosecondsSinceInitialize() const = 0;

      /**
       * Get the number of the current frame.
       *
       * @return the number of the current frame.
       */
      LIBAPI virtual unsigned long long getFrame() const = 0;

      LIBAPI virtual ~HlaPacer() {}

      static const unsigned long long NANOS_PER_MILLIS = 1000 * 1000;              /**< Nanoseconds per millisecond. */
      static const unsigned long long NANOS_PER_SECOND = 1000 * NANOS_PER_MILLIS;  /**< Nanoseconds per second. */

      /**
       * Create a pacer with the default time source.
       *
       * @param frameLengthNs length of a frame, in <code>ns</code>
       *
       * @return the pacer
       */
      LIBAPI static HlaPacerPtr create(unsigned long long frameLengthNs);

      /**
       * Create a pacer with a custom time source.
       *
       * @param frameLengthNs length of a frame, in <code>ns</code>
       * @param source the time source
       *
       * @return the pacer
       */
      LIBAPI static HlaPacerPtr create(unsigned long long frameLengthNs, HlaPacer::SourcePtr source);
   };
}
#endif
