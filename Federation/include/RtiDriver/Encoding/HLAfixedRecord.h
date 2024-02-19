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
   File: HLAfixedRecord.h
***********************************************************************/
#ifndef DS_DRIVER_RTI_HLAfixedRecord_h_
#define DS_DRIVER_RTI_HLAfixedRecord_h_

#include "DataElement.h"

namespace EncodingHelpers {
   // Forward Declarations
   class VariableLengthData;
   class HLAfixedRecordImplementation;

   // Interface for the HLAfixedRecord complex data element
   class RTIDRIVER_EXPORT HLAfixedRecord : public EncodingHelpers::DataElement
   {
   public:

      // Default Constructor
      HLAfixedRecord ();

      // Copy Constructor
      HLAfixedRecord (
         HLAfixedRecord const & rhs);

      // Destructor
      virtual ~HLAfixedRecord ();

      // Return a new copy of the DataElement
      virtual DataElement* clone () const;

      // Encode this element into a new VariableLengthData
      virtual VariableLengthData encode () const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Encode this element into an existing VariableLengthData
      virtual void encode (
         VariableLengthData& inData) const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Encode this element and append it to a buffer
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

      // Return the size in bytes of this record's encoding.
      virtual size_t getEncodedLength () const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return the octet boundary of this element.
      virtual unsigned int getOctetBoundary () const;

      // Return true if given element is same type as this; otherwise, false.
      virtual bool isSameTypeAs(
         DataElement const& inData ) const;

      // Return true if given element is same type as the indexed element;
      // otherwise, false.
      virtual bool hasElementSameTypeAs(size_t index,
         DataElement const& inData ) const;

      // Return the number of elements in this fixed record.
      virtual size_t size () const;

      // Append a copy of the dataElement instance to this fixed record.
      virtual void appendElement (const DataElement& dataElement);

      // Append the dataElement instance to this fixed record.
      // Null pointer results in an exception.
      virtual void appendElementPointer (DataElement* dataElement);

      // Sets the element at the given index to a copy of the given element instance
      // Element must match prototype of existing element at this index.
      virtual void set (size_t index,
         const DataElement& dataElement)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Sets the element at the given index to the given element instance
      // Element must match prototype of existing element at this index.
      // Null pointer results in an exception.
      virtual void setElementPointer (size_t index, DataElement* dataElement)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return a const reference to the element at the specified index.
      // Must use set to change element.
      virtual const DataElement& get (
         size_t index) const
         RTI_DRIVER_THROW_SPEC(EncoderException);

   private:

      // Assignment Operator not allowed
      HLAfixedRecord& operator=(
         HLAfixedRecord const & rhs);

   protected:

      HLAfixedRecordImplementation* _impl;
   };
}

#endif // DS_DRIVER_RTI_HLAfixedRecord_h_
