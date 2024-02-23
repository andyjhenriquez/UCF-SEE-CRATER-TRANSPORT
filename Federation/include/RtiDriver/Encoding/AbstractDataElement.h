/*
 * Copyright (C) 2006-2022 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DS_DRIVER_RTI_AbstractDataElements_h_
#define DS_DRIVER_RTI_AbstractDataElements_h_

#include "DataElement.h"
#include "VariableLengthData.h"

namespace EncodingHelpers {

   class RTIDRIVER_EXPORT AbstractDataElement : public EncodingHelpers::DataElement {
   private:

      virtual EncodingHelpers::DataElement & getEncoder() = 0;
      
      virtual const EncodingHelpers::DataElement & getEncoder() const = 0;

   public:

      // Return a new copy of the DataElement
      virtual DataElement* clone () const = 0;

      // Encode this element into a new VariableLengthData
      virtual EncodingHelpers::VariableLengthData encode() const
         RTI_DRIVER_THROW_SPEC(EncodingHelpers::EncoderException);

      // Encode this element into an existing VariableLengthData
      virtual void encode(EncodingHelpers::VariableLengthData & inData) const
         RTI_DRIVER_THROW_SPEC(EncodingHelpers::EncoderException) ;

      // Encode this element and append it to a buffer
      virtual void encodeInto(std::vector<EncodingHelpers::Octet> & buffer) const
         RTI_DRIVER_THROW_SPEC(EncodingHelpers::EncoderException);

      // Decode this element from the RTI's VariableLengthData.
      virtual void decode(EncodingHelpers::VariableLengthData const & inData)
         RTI_DRIVER_THROW_SPEC(EncodingHelpers::EncoderException);

      // Decode this element starting at the index in the provided buffer
      virtual size_t decodeFrom(std::vector<EncodingHelpers::Octet> const & buffer, size_t index)
         RTI_DRIVER_THROW_SPEC(EncodingHelpers::EncoderException);

      // Return the size in bytes of this element's encoding.
      virtual size_t getEncodedLength() const
         RTI_DRIVER_THROW_SPEC(EncodingHelpers::EncoderException);

      // Return the octet boundary of this element.
      virtual unsigned int getOctetBoundary () const;

      // Return true if given element is same type as this; otherwise, false.
      virtual bool isSameTypeAs(EncodingHelpers::DataElement const & inData ) const;

      // Return a hash of the encoded data
      // Provides mechanism to map DataElement discriminants to variants
      // in VariantRecord.
      virtual EncodingHelpers::Integer64 hash() const;

   };
}

#endif
