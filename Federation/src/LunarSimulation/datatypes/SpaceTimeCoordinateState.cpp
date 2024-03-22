/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#include <LunarSimulation/HlaAllHeaders.h>

#include <LunarSimulation/datatypes/SpaceTimeCoordinateState.h>

#include "../StringUtil.h"

using namespace LunarSimulation;

namespace LunarSimulation {

   bool operator ==(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r) {
      return
         l.translationalState == r.translationalState &&
         l.rotationalState == r.rotationalState &&
         l.time == r.time 
   ;
   }

   bool operator !=(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r) {
      return !(l == r);
   }

   bool operator <(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r) {
      if (l.translationalState < r.translationalState)
         return true;
      else if (l.translationalState > r.translationalState)
         return false;
      if (l.rotationalState < r.rotationalState)
         return true;
      else if (l.rotationalState > r.rotationalState)
         return false;
      if (l.time < r.time)
         return true;
      else if (l.time > r.time)
         return false;
      return false;
   }

   bool operator >(const LunarSimulation::SpaceTimeCoordinateState& l, const LunarSimulation::SpaceTimeCoordinateState& r) {
      if (l.translationalState > r.translationalState)
         return true;
      else if (l.translationalState < r.translationalState)
         return false;
      if (l.rotationalState > r.rotationalState)
         return true;
      else if (l.rotationalState < r.rotationalState)
         return false;
      if (l.time > r.time)
         return true;
      else if (l.time < r.time)
         return false;
      return false;
   }

   std::wostream  & operator << (std::wostream& ws, const LunarSimulation::SpaceTimeCoordinateState& data) {
      ws << L"<SpaceTimeCoordinateState:" <<
         L" translationalState=" << data.translationalState <<
         L" rotationalState=" << data.rotationalState <<
         L" time=" << data.time <<
      L">";
      return ws;
   }
   std::ostream  & operator << (std::ostream& s, const LunarSimulation::SpaceTimeCoordinateState& data) {
      s << "<SpaceTimeCoordinateState:" <<
         " translationalState=" << data.translationalState <<
         " rotationalState=" << data.rotationalState <<
         " time=" << data.time <<
      ">";
      return s;
   }
}

