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
   File: HLAopaqueData.h
***********************************************************************/
#ifndef DS_DRIVER_RTI_HLAopaqueData_h_
#define DS_DRIVER_RTI_HLAopaqueData_h_

#include "DataElement.h"

namespace EncodingHelpers {
   // Forward Declarations
   class VariableLengthData;
   class HLAopaqueDataImplementation;

   // Interface for the HLAopaqueData basic data element
   class RTIDRIVER_EXPORT HLAopaqueData : public EncodingHelpers::DataElement
   {
   public:

      // Constructor: Default
      // Uses internal memory
      HLAopaqueData ();

      // Constructor: Initial Value
      // Uses internal memory
      HLAopaqueData (
         const Octet* inData,
         size_t dataSize);

      // Constructor: Use external memory with buffer and data of given lengths.
      // This instance changes or reflects changes to contents of external memory.
      // Changes to external memory are reflected in subsequent encodings.
      // Changes to encoder (i.e., set or decode) are reflected in external memory.
      // Caller is responsible for ensuring that the external memory is
      // valid for the lifetime of this object or until this object acquires
      // new memory through setDataPointer.
      // Buffer length indicates size of memory; data length indicates size of
      // data stored in memory.
      // Exception is thrown for null memory or zero buffer size.
      HLAopaqueData (
         Octet** inData,
         size_t bufferSize,
         size_t dataSize)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Constructor: Copy
      // Uses internal memory
      HLAopaqueData (
         HLAopaqueData const & rhs);

     explicit HLAopaqueData(const std::vector<char> in);

      // Caller is free to delete rhs.
      virtual ~HLAopaqueData();

      // Return a new copy of the DataElement
      virtual DataElement* clone () const;

      // Return the encoding of this element in a VariableLengthData
      virtual VariableLengthData encode () const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Encode this element into an existing VariableLengthData
      virtual void encode (
         VariableLengthData& inData) const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Encode this element and append it to a buffer.
      virtual void encodeInto (
         std::vector<Octet>& buffer) const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Decode this element from the RTI's VariableLengthData.
      virtual void decode (
         VariableLengthData const & inData)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Decode this element starting at the index in the provided buffer
      virtual size_t decodeFrom (
         std::vector<Octet> const & buffer,
         size_t index)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return the size in bytes of this element's encoding.
      virtual size_t getEncodedLength () const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return the octet boundary of this element.
      virtual unsigned int getOctetBoundary () const;

      // Return the length of the contained buffer
      virtual size_t bufferLength () const;

      // Return the length of the data stored in the buffer
      virtual size_t dataLength () const;

      // Change memory to use given external memory
      // Changes to this instance will be reflected in external memory
      // Caller is responsible for ensuring that the data that is
      // pointed to is valid for the lifetime of this object, or past
      // the next time this object is given new data.
      // Buffer length indicates size of memory; data length indicates size of
      // data stored in memory.
      // Exception is thrown for null memory or zero buffer size.
      virtual void setDataPointer (
         Octet** inData,
         size_t bufferSize,
         size_t dataSize)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Set the data to be encoded.
      virtual void set(
         const Octet* inData,
         size_t dataSize);

      // Return a reference to the contained array
      virtual const Octet* get () const;

       // Conversion operator to std::vector<char>
      // Value returned is from encoded data.
     operator std::vector<char>() const;

   private:

      // Assignment Operator not allowed
      HLAopaqueData& operator=(
         HLAopaqueData const & rhs);

   protected:

      HLAopaqueDataImplementation* _impl;
   };
}

#endif // DS_DRIVER_RTI_HLAopaqueData_h_
