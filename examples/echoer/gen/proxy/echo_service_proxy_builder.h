/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 10-01-2016 01:51:18
 * Name: echo_service_proxy_builder.h
 * Description:
 *   This file contains definition of the proxy builder class.
 ******************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_ECHOER__PROXY__ECHO_SERVICE_PROXY_BUILDER_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_ECHOER__PROXY__ECHO_SERVICE_PROXY_BUILDER_H_

#include <stdint.h>
#include <string>


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace echoer {
class EchoService;
namespace proxy {
  class EchoServiceProxyBuilder {
  public:
    static EchoService* Create(std::string /* host */, uint32_t /* port */);
    static void Destroy(EchoService *);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE echoer
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif