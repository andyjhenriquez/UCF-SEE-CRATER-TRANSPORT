/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include <LunarSimulation/HlaPacer.h>
#include <LunarSimulation/HlaPointers.h>

#include "TimeUtility.h"

using namespace LunarSimulation;


class SourcePacer : public HlaPacer {
public:
   SourcePacer(unsigned long long frameLengthNs, SourcePtr source) : _frameLengthNs(frameLengthNs), _source(source) {
      initialize(0);
   }

   bool initialize(unsigned long long initialFrame) {
      _frame = initialFrame;
      return _source->initialize(_frameLengthNs * initialFrame);
   }

   bool pace() {
      _frame++;

      unsigned long long nextFrameStartNs = _frame * _frameLengthNs;
      long long sleepNs = nextFrameStartNs - _source->getNanosecondsSinceInitialize();
      if (sleepNs < 0) {
         return false;
      }

      TimeUtility::sleep(sleepNs / NANOS_PER_MILLIS);
      return true;
   }

   unsigned long long getNanosecondsSinceInitialize() const {
      return _source->getNanosecondsSinceInitialize();
   }

   unsigned long long getFrame() const {
      return _frame;
   }

private:
   const unsigned long long _frameLengthNs;
   const HlaPacer::SourcePtr _source;
   unsigned long long _frame;
};


/* Time source using TimeUtility.getCurrentTimeMillis(). */
class MillisSource : public HlaPacer::Source {
public:
   MillisSource() : _startTimeMs(0) {
   }

   bool initialize(unsigned long long offsetNs) {
      _startTimeMs = TimeUtility::getCurrentTimeMillis() - (offsetNs / HlaPacer::NANOS_PER_MILLIS);
      return true;
   }

   unsigned long long getNanosecondsSinceInitialize() const {
      return HlaPacer::NANOS_PER_MILLIS * (TimeUtility::getCurrentTimeMillis() - _startTimeMs);
   }

private:
   unsigned long long _startTimeMs;
};

HlaPacerPtr HlaPacer::create(unsigned long long frameLengthNs) {
   return HlaPacer::create(frameLengthNs, HlaPacer::SourcePtr(new MillisSource()));
}

HlaPacerPtr HlaPacer::create(unsigned long long frameLengthNs, HlaPacer::SourcePtr source) {
   return HlaPacerPtr(new SourcePacer(frameLengthNs, source));
}
