/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 04:09:32
 * Name: response_message.h
 * Description:
 *   This file contains definition of ResponseMessage class.
 ***************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_ECHOER__RESPONSE_MESSAGE_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_ECHOER__RESPONSE_MESSAGE_H_

#include <string>

#include <org/labcrypto/hottentot/primitives.h>


#include "enums.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace echoer {
  class ResponseMessage : public ::org::labcrypto::hottentot::Serializable {
  public:
    ResponseMessage() {
    }
    ResponseMessage(const ResponseMessage &);
    ResponseMessage(ResponseMessage *);
    virtual ~ResponseMessage() {}
  public:
    inline ::org::labcrypto::hottentot::Utf8String GetMessage() const {
      return message_;
    }
    inline void SetMessage(::org::labcrypto::hottentot::Utf8String message) {
      message_ = message;
    }
  public:
    virtual unsigned char * Serialize(uint32_t * /* Pointer to length */);
    virtual void Deserialize(unsigned char * /* Data */, uint32_t /* Data length */);
  private:
    ::org::labcrypto::hottentot::Utf8String message_;
  };
} // END OF NAMESPACE echoer
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif