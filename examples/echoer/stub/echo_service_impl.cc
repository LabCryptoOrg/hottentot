/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 16-01-2016 01:33:10
 * Name: echo_service_impl.cc
 * Description:
 *   This file contains empty implementation of sample stub.
 ******************************************************************/
 
#include <sstream>

#include <org/labcrypto/hottentot/runtime/configuration.h>
#include <org/labcrypto/hottentot/runtime/logger.h>
#include <org/labcrypto/hottentot/runtime/utils.h>

#include "echo_service_impl.h"

#include "../gen/request_message.h"
#include "../gen/response_message.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace echoer {
  void
  EchoServiceImpl::OnInit() {
    // TODO: Called when service is initializing.
  }
  void
  EchoServiceImpl::OnShutdown() {
    // TODO: Called when service is shutting down.
  }
  void
  EchoServiceImpl::EchoMessage (
    ::ir::ntnaeem::hottentot::examples::echoer::RequestMessage &req, 
    ::ir::ntnaeem::hottentot::examples::echoer::ResponseMessage &out,
    ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
  ) {
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "EchoServiceImpl::EchoMessage() is called." << std::endl;
    }
    unsigned char *str = req.GetName().Serialize(NULL);
    std::stringstream ss;
    ss << "Hello " << str << "\r\n";
    ::org::labcrypto::hottentot::Utf8String responseString(ss.str().c_str());
    out.SetMessage(responseString);
    delete [] str;
  }
} // END OF NAMESPACE echoer
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir
