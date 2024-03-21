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

#include <LunarSimulation/datatypes/ReferenceFrameTranslation.h>

#include "../StringUtil.h"

using namespace LunarSimulation;

namespace LunarSimulation {

   bool operator ==(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r) {
      return
         l.position == r.position &&
         l.velocity == r.velocity 
   ;
   }

   bool operator !=(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r) {
      return !(l == r);
   }

   bool operator <(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r) {
      if (l.position < r.position)
         return true;
      else if (l.position > r.position)
         return false;
      if (l.velocity < r.velocity)
         return true;
      else if (l.velocity > r.velocity)
         return false;
      return false;
   }

   bool operator >(const LunarSimulation::ReferenceFrameTranslation& l, const LunarSimulation::ReferenceFrameTranslation& r) {
      if (l.position > r.position)
         return true;
      else if (l.position < r.position)
         return false;
      if (l.velocity > r.velocity)
         return true;
      else if (l.velocity < r.velocity)
         return false;
      return false;
   }

   std::wostream  & operator << (std::wostream& ws, const LunarSimulation::ReferenceFrameTranslation& data) {
      ws << L"<ReferenceFrameTranslation:" <<
         L" position=" << data.position <<
         L" velocity=" << data.velocity <<
      L">";
      return ws;
   }
   std::ostream  & operator << (std::ostream& s, const LunarSimulation::ReferenceFrameTranslation& data) {
      s << "<ReferenceFrameTranslation:" <<
         " position=" << data.position <<
         " velocity=" << data.velocity <<
      ">";
      return s;
   }
}

