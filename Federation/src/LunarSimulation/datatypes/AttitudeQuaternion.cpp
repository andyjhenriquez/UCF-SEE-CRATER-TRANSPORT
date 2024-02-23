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

#include <LunarSimulation/datatypes/AttitudeQuaternion.h>

#include "../StringUtil.h"

using namespace LunarSimulation;

namespace LunarSimulation {

   bool operator ==(const LunarSimulation::AttitudeQuaternion& l, const LunarSimulation::AttitudeQuaternion& r) {
      return
         l.scalar == r.scalar &&
         l.vector == r.vector 
   ;
   }

   bool operator !=(const LunarSimulation::AttitudeQuaternion& l, const LunarSimulation::AttitudeQuaternion& r) {
      return !(l == r);
   }

   bool operator <(const LunarSimulation::AttitudeQuaternion& l, const LunarSimulation::AttitudeQuaternion& r) {
      if (l.scalar < r.scalar)
         return true;
      else if (l.scalar > r.scalar)
         return false;
      if (l.vector < r.vector)
         return true;
      else if (l.vector > r.vector)
         return false;
      return false;
   }

   bool operator >(const LunarSimulation::AttitudeQuaternion& l, const LunarSimulation::AttitudeQuaternion& r) {
      if (l.scalar > r.scalar)
         return true;
      else if (l.scalar < r.scalar)
         return false;
      if (l.vector > r.vector)
         return true;
      else if (l.vector < r.vector)
         return false;
      return false;
   }

   std::wostream  & operator << (std::wostream& ws, const LunarSimulation::AttitudeQuaternion& data) {
      ws << L"<AttitudeQuaternion:" <<
         L" scalar=" << data.scalar <<
         L" vector=" << data.vector <<
      L">";
      return ws;
   }
   std::ostream  & operator << (std::ostream& s, const LunarSimulation::AttitudeQuaternion& data) {
      s << "<AttitudeQuaternion:" <<
         " scalar=" << data.scalar <<
         " vector=" << data.vector <<
      ">";
      return s;
   }
}

