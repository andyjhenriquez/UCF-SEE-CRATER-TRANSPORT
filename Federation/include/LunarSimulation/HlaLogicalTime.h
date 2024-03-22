/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Guidarly Joseph, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALOGICALTIME_H
#define DEVELOPER_STUDIO_HLALOGICALTIME_H

#include <string>

#include <LunarSimulation/HlaLibSettings.h>
#include <LunarSimulation/HlaPointers.h>

namespace LunarSimulation {

   /**
   * A <code>HlaLogicalTime</code> is representation of the logical scenario time within the simulation.
   * Note that the logical time might not be related to wall clock time or the <code>HlaTimeStamp</code>.
   */
   class HlaLogicalTime : private LunarSimulation::noncopyable {

      public:

      /**
      * Enum with order types
      */
      enum OrderType {
         TIME_STAMP_ORDER,
         RECEIVE_ORDER,
         NONE
      };

      /**
      * Check if the logical time is valid.
      *
      * @return If the time is valid
      */
      LIBAPI virtual bool isValid() const = 0;

      /**
      * Get the value of the logical time.
      *
      * @return The logical time as a long long
      */
      LIBAPI virtual long long getValue() const = 0;

      /**
      * Get the order type of the logical time.
      *
      * @return The order type (timestamped, receive order or none)
      */
      LIBAPI virtual OrderType getReceivedOrderType() const = 0;

      /**
      * Check if the logical time was received in timestamp order.
      *
      * @return If the logical time was received in timestamp order.
      */
      LIBAPI virtual bool wasReceivedInTimeStampOrder() const = 0;

      /**
      * Add a value to the logical time.
      *
      * @return A pointer to the new logical time
      */
      LIBAPI virtual HlaLogicalTimePtr add(long long addend) const = 0;

      /**
      * Get a string representation of the logical time
      *
      * @return A string representation of the logical time
      */
      LIBAPI virtual std::wstring toString() const = 0;

      LIBAPI virtual ~HlaLogicalTime() {}
   };
}
#endif
