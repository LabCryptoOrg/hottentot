/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 15-01-2016 12:20:11
 * Name: list_test_service_client.h
 * Description:
 *   This file contains a sample client.
 ******************************************************************/

#include <iostream>

#include <naeem/hottentot/runtime/configuration.h>
#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>

#include "../message.h"
#include "../list_test_service.h"
#include "../proxy/list_test_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::Logger::Init();  
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy runtime is initialized." << std::endl;
    }
    ::ir::ntnaeem::hottentot::examples::listtest::ListTestService *proxy = 
        ::ir::ntnaeem::hottentot::examples::listtest::proxy::ListTestServiceProxyBuilder::Create("127.0.0.1", 2000);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy object is created." << std::endl;
    }
    ::naeem::hottentot::runtime::types::List< ::ir::ntnaeem::hottentot::examples::listtest::Message&> m;
    proxy->GetMessages(m);
    ::ir::ntnaeem::hottentot::examples::listtest::proxy::ListTestServiceProxyBuilder::Destroy(proxy);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy object is destroyed." << std::endl;
    }
    // Delete allocated objects
  } catch (...) {
    ::naeem::hottentot::runtime::Logger::GetOut() << "Error." << std::endl;
    return 1;
  }
  return 0;
}