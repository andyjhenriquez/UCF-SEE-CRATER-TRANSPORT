/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLAEXCEPTION_H
#define DEVELOPER_STUDIO_HLAEXCEPTION_H

#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <LunarSimulation/HlaLibSettings.h>

namespace LunarSimulation {

   /**
    * Base class for all checked exceptions.
    */
   class HlaException : public std::exception {
   public:

      /**
       * Base constructor
       * @param message string to describe the exception
       */
      LIBAPI HlaException(std::string message) :
         _what(message)
      {}

      LIBAPI virtual ~HlaException() NON_THROWING_SPEC
      {}

      /**
       * Returns the exception description as a c string
       * @return exception description as c string
       */
      LIBAPI const char* what() const NON_THROWING_SPEC;

      /**
       * Returns the exception description as a wstring
       * @return description as wstring
       */
      LIBAPI std::wstring what_w() const NON_THROWING_SPEC;

   private:
      std::string _what;
   };

   /**
   * HlaDecodeException
   */
   class HlaDecodeException : public HlaException {
   public:
       /**
        * Constructor
        * @param message string to describe the exception
        * @param includeData bool to decide if a data dump should be included in message
        * @param in data
        */
       LIBAPI HlaDecodeException(const char* message, const bool includeData = false, const std::vector<char> &in = std::vector<char>(0));

       /**
        * Constructor
        * @param message wstring to describe the exception
        * @param includeData bool to decide if a data dump should be included in message
        *  @param in data
        */
       LIBAPI HlaDecodeException(std::wstring message, const bool includeData = false, const std::vector<char> &in = std::vector<char>(0));
   };



#define DEVSTUDIO_EXCEPTION(A)                                                       \
   /**                                                                                \
    * A                                                                               \
    */                                                                                \
   class A : public HlaException {                                              \
   public:                                                                            \
      /**                                                                             \
       * Constructor                                                                  \
       * @param message string to describe the exception                              \
       */                                                                             \
      LIBAPI A(const char* const message);                                            \
                                                                                      \
      /**                                                                             \
       * Constructor                                                                  \
       * @param message string to describe the exception                              \
       */                                                                             \
      LIBAPI A(std::wstring message);                                                 \
   };

   DEVSTUDIO_EXCEPTION(HlaAttributeNotOwnedException)
   DEVSTUDIO_EXCEPTION(HlaConnectException)
   DEVSTUDIO_EXCEPTION(HlaEncodeException)
   DEVSTUDIO_EXCEPTION(HlaFomException)
   DEVSTUDIO_EXCEPTION(HlaIllegalInstanceNameException)
   DEVSTUDIO_EXCEPTION(HlaInstanceNameInUseException)
   DEVSTUDIO_EXCEPTION(HlaInternalException)
   DEVSTUDIO_EXCEPTION(HlaNotConnectedException)
   DEVSTUDIO_EXCEPTION(HlaRtiException)
   DEVSTUDIO_EXCEPTION(HlaUpdaterReusedException)
   DEVSTUDIO_EXCEPTION(HlaValueNotSetException)
   DEVSTUDIO_EXCEPTION(HlaObjectInstanceIsRemovedException)
   DEVSTUDIO_EXCEPTION(HlaFederateOwnsAttributeException)
   DEVSTUDIO_EXCEPTION(HlaInTimeAdvancingStateException)
   DEVSTUDIO_EXCEPTION(HlaInvalidLicenseException)
   DEVSTUDIO_EXCEPTION(HlaInvalidLogicalTimeException)
   DEVSTUDIO_EXCEPTION(HlaSaveInProgressException)
   DEVSTUDIO_EXCEPTION(HlaRestoreInProgressException)
   DEVSTUDIO_EXCEPTION(HlaSaveFederateException)
   DEVSTUDIO_EXCEPTION(HlaRestoreFederateException)
   DEVSTUDIO_EXCEPTION(HlaInvalidInterestException)
   DEVSTUDIO_EXCEPTION(HlaNormalizerException)
   DEVSTUDIO_EXCEPTION(HlaAttributeAlreadyOwnedException)
   DEVSTUDIO_EXCEPTION(HlaFederateNotAcquiringAttributeException)
   DEVSTUDIO_EXCEPTION(HlaIncompatibleHlaVersionException)
}
#endif
