/***********************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 05:11:23
 * Name: calculator_service_request_handler.h
 * Description:
 *   This file contains definition of service's request handler class.
 ***********************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__CALCULATOR_SERVICE_REQUEST_HANDLER_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__SERVICE__CALCULATOR_SERVICE_REQUEST_HANDLER_H_

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <string>

#include <org/labcrypto/hottentot/runtime/service/request_handler.h>


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {
namespace service {
  class CalculatorServiceRequestHandler : public ::org::labcrypto::hottentot::runtime::service::RequestHandler {
  public:
    CalculatorServiceRequestHandler(::org::labcrypto::hottentot::runtime::service::Service *service)
      : ::org::labcrypto::hottentot::runtime::service::RequestHandler(service) {
    }
    virtual ~CalculatorServiceRequestHandler() {}
  public:
    virtual void HandleRequest(::org::labcrypto::hottentot::runtime::Request &request,
                                                   ::org::labcrypto::hottentot::runtime::Response &response);
  };
} // END OF NAMESPACE service
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif