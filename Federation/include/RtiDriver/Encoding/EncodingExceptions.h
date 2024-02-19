/***********************************************************************
   The IEEE hereby grants a general, royalty-free license to copy, distribute,
   display and make derivative works from this material, for all purposes,
   provided that any use of the material contains the following
   attribution: "Reprinted with permission from IEEE 1516.1(TM)-2009".
   Should you require additional information, contact the Manager, Standards
   Intellectual Property, IEEE Standards Association (stds-ipr@ieee.org).
***********************************************************************/
/***********************************************************************
   IEEE 1516.1 High Level Architecture Interface Specification C++ API
   File: EncodingExceptions.h
***********************************************************************/
#ifndef DS_DRIVER_RTI_EncodingExceptions_H_
#define DS_DRIVER_RTI_EncodingExceptions_H_

#include "SpecificConfig.h"
#include "EncodingConfig.h"

#include <string>

/*
 * The usage of non-empty exception specifications are disabled by default.
 * They can be enabled by defining RTI_DRIVER_USE_THROW_SPEC.
 *
 * Note that Microsoft Visual C++ compilers ignore non-empty exception specifications,
 * https://docs.microsoft.com/en-us/cpp/cpp/nonstandard-behavior#function-exception-specifiers
 */

#if defined(RTI_DRIVER_USE_THROW_SPEC)
    #define RTI_DRIVER_THROW_SPEC       throw
#else
    #define RTI_DRIVER_THROW_SPEC(...)
#endif


namespace EncodingHelpers {

   class RTIDRIVER_EXPORT EncoderException
   {
   public:
      explicit EncoderException(std::wstring const & message) RTI_DRIVER_THROW_SPEC()
         : _msg(L"EncoderException: " + message)
      {}
      
      std::wstring what() const
         RTI_DRIVER_THROW_SPEC()
      {
         return _msg;
      }

   private:
      std::wstring _msg;
   };
}

#endif // DS_DRIVER_RTI_EncodingExceptions_H_
