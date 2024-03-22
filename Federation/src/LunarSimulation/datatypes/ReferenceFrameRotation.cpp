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

#include <LunarSimulation/datatypes/ReferenceFrameRotation.h>

#include "../StringUtil.h"

using namespace LunarSimulation;

namespace LunarSimulation {

   bool operator ==(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r) {
      return
         l.attitudeQuaternion == r.attitudeQuaternion &&
         l.angularVelocity == r.angularVelocity 
   ;
   }

   bool operator !=(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r) {
      return !(l == r);
   }

   bool operator <(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r) {
      if (l.attitudeQuaternion < r.attitudeQuaternion)
         return true;
      else if (l.attitudeQuaternion > r.attitudeQuaternion)
         return false;
      if (l.angularVelocity < r.angularVelocity)
         return true;
      else if (l.angularVelocity > r.angularVelocity)
         return false;
      return false;
   }

   bool operator >(const LunarSimulation::ReferenceFrameRotation& l, const LunarSimulation::ReferenceFrameRotation& r) {
      if (l.attitudeQuaternion > r.attitudeQuaternion)
         return true;
      else if (l.attitudeQuaternion < r.attitudeQuaternion)
         return false;
      if (l.angularVelocity > r.angularVelocity)
         return true;
      else if (l.angularVelocity < r.angularVelocity)
         return false;
      return false;
   }

   std::wostream  & operator << (std::wostream& ws, const LunarSimulation::ReferenceFrameRotation& data) {
      ws << L"<ReferenceFrameRotation:" <<
         L" attitudeQuaternion=" << data.attitudeQuaternion <<
         L" angularVelocity=" << data.angularVelocity <<
      L">";
      return ws;
   }
   std::ostream  & operator << (std::ostream& s, const LunarSimulation::ReferenceFrameRotation& data) {
      s << "<ReferenceFrameRotation:" <<
         " attitudeQuaternion=" << data.attitudeQuaternion <<
         " angularVelocity=" << data.angularVelocity <<
      ">";
      return s;
   }
}

