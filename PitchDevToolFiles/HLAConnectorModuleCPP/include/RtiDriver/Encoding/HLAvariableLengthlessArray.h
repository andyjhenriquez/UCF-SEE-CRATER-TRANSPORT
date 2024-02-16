/***********************************************************************
   The IEEE hereby grants a general, royalty-free license to copy, distribute,
   display and make derivative works from this material, for all purposes,
   provided that any use of the material contains the following
   attribution: "Reprinted with permission from IEEE 1516.1(TM)-2009".
   Should you require additional information, contact the Manager, Standards
   Intellectual Property, IEEE Standards Association (stds-ipr@ieee.org).
***********************************************************************/
#ifndef DS_DRIVER_RTI_HLAvariableLengthlessArray_h_
#define DS_DRIVER_RTI_HLAvariableLengthlessArray_h_

#include "DataElement.h"

namespace EncodingHelpers {
   // Forward Declarations
   class VariableLengthData;
   class HLAvariableLengthlessArrayImplementation;

   // Interface for the HLAvariableArray complex data element
   class RTIDRIVER_EXPORT HLAvariableLengthlessArray : public EncodingHelpers::DataElement
   {
   public:

      // Constructor which accepts a prototype element
      // that specifies the type of elements to be stored in the array.
      // A clone of the given element works as a seed.
      explicit HLAvariableLengthlessArray (
         const DataElement& prototype );

      // Copy Constructor
      HLAvariableLengthlessArray (
         HLAvariableLengthlessArray const & rhs);

      // Destructor
      virtual ~HLAvariableLengthlessArray ();

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

      // Decode this element from the RTI's VariableLengthData with the specified number of elements.
      virtual void decode (
         VariableLengthData const & inData,
         int elements)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Decode this element starting at the index in the provided buffer
      virtual size_t decodeFrom (
         std::vector<Octet> const & buffer,
         size_t index)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Decode this element starting at the index in the provided buffer with the specified number of elements
      virtual size_t decodeFrom (
         std::vector<Octet> const & buffer,
         size_t index,
         int elements)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return the size in bytes of this element's encoding.
      virtual size_t getEncodedLength () const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return the octet boundary of this element.
      virtual unsigned int getOctetBoundary () const;

      // Return the number of elements in this variable array.
      virtual size_t size () const;

      virtual void resize(size_t size);

      // Return true if given element is same type as this; otherwise, false.
      virtual bool isSameTypeAs(
         DataElement const& inData ) const;

      // Return true if given element matches prototype of array.
      virtual bool hasPrototypeSameTypeAs(DataElement const& dataElement ) const;

      // Adds a copy of the given element instance to this array
      // Element must match prototype.
      virtual void addElement (
         const DataElement& dataElement)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Adds the given element instance to this variable array
      // Element must match prototype.
      // Caller is responsible for ensuring that the external memory is
      // valid for the lifetime of this object or until the indexed element
      // acquires new memory through the set method.
      // Null pointer results in an exception.
      virtual void addElementPointer (
         DataElement* dataElement)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Sets the indexed element to a copy of the given element instance.
      // Element must match prototype.
      // If indexed element uses external memory, the memory will be modified.
      virtual void set (
         size_t index,
         const DataElement& dataElement)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Sets the indexed element to the given element instance.
      // Element must match prototype.
      // Null pointer results in an exception.
      // Caller is responsible for ensuring that the external memory is
      // valid for the lifetime of this object or until the indexed element
      // acquires new memory through this call.
      virtual void setElementPointer (
         size_t index,
         DataElement* dataElement)
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return a const reference to the element instance at the specified index.
      // Must use set to change element.
      virtual const DataElement& get (
         size_t index) const
         RTI_DRIVER_THROW_SPEC(EncoderException);

      // Return a const reference to the element instance at the specified index.
      // Must use set to change element.
      DataElement const& operator [](size_t index) const
         RTI_DRIVER_THROW_SPEC(EncoderException);
   private:

      // Default Constructor not allowed
      HLAvariableLengthlessArray ();

      // Assignment Operator not allowed
      HLAvariableLengthlessArray& operator=(
         HLAvariableLengthlessArray const & rhs);

   protected:

      HLAvariableLengthlessArrayImplementation* _impl;
   };
}

#endif // DS_DRIVER_RTI_HLAvariableLengthlessArray_h_
