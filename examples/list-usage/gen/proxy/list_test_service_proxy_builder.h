/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 15-01-2016 12:20:11
 * Name: list_test_service_proxy_builder.h
 * Description:
 *   This file contains definition of the proxy builder class.
 ******************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_LISTTEST__PROXY__LIST_TEST_SERVICE_PROXY_BUILDER_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_LISTTEST__PROXY__LIST_TEST_SERVICE_PROXY_BUILDER_H_

#include <stdint.h>
#include <string>


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace listtest {
class ListTestService;
namespace proxy {
  class ListTestServiceProxyBuilder {
  public:
    static ListTestService* Create(std::string /* host */, uint32_t /* port */);
    static void Destroy(ListTestService *);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE listtest
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif