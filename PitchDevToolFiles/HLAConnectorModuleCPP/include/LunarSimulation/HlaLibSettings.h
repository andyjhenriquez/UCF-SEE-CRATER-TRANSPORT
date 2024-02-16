/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_HLALIBSETTINGS_H
#define DEVELOPER_STUDIO_HLALIBSETTINGS_H

#if defined(_WIN32)
    #if defined(LIB_EXPORT)
        #define LIBAPI __declspec(dllexport)
    #else
        #if defined(LIB_IMPORT)
            #define LIBAPI __declspec(dllimport)
        #else
            #define LIBAPI
        #endif
    #endif
#else
    #define LIBAPI
#endif

/*
 * Using new C++ 11 API
 */
#define DEVELOPER_STUDIO_CPP_11_API

/*
 * The usage of non-empty exception specifications are disabled by default.
 * They can be enabled by defining DEVELOPER_STUDIO_USE_THROW_SPEC.
 *
 * Note that Microsoft Visual C++ compilers ignore non-empty exception specifications,
 * https://docs.microsoft.com/en-us/cpp/cpp/nonstandard-behavior#function-exception-specifiers
 */

#if defined(DEVELOPER_STUDIO_USE_THROW_SPEC)
    #define THROW_SPEC       throw
#else
    #define THROW_SPEC(...)
#endif

/*
 * Empty or non-throwing dynamic exception specification.
 */
#define NON_THROWING_SPEC noexcept


namespace LunarSimulation {

   /**
    * Make derived classes non-copyable.
    */
   class noncopyable {
   protected:
      noncopyable() = default;
      ~noncopyable() = default;

   private:
      // private copy constructor and assignment operator
      noncopyable(const noncopyable &) = delete;
      const noncopyable & operator=(const noncopyable &) = delete;
   };
}

#endif
