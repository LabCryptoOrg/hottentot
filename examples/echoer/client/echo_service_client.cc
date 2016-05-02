/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 05-02-2016 05:00:47
 * Name: echo_service_client.h
 * Description:
 *   This file contains a sample client.
 ******************************************************************/

#include <iostream>

#include <org/labcrypto/hottentot/runtime/configuration.h>
#include <org/labcrypto/hottentot/runtime/logger.h>
#include <org/labcrypto/hottentot/runtime/proxy/proxy_runtime.h>

#include "../gen/request_message.h"
#include "../gen/response_message.h"
#include "../gen/proxy/echo_service.h"
#include "../gen/proxy/echo_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::org::labcrypto::hottentot::runtime::Logger::Init();  
    ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "Proxy runtime is initialized." << std::endl;
    }
    ::ir::ntnaeem::hottentot::examples::echoer::proxy::EchoService *proxy = 
      ::ir::ntnaeem::hottentot::examples::echoer::proxy::EchoServiceProxyBuilder::Create("127.0.0.1", 2000);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "Proxy object is created." << std::endl;
    }
    // ====================================================
    ::ir::ntnaeem::hottentot::examples::echoer::RequestMessage req;
    req.SetName("Kamran");
    ::ir::ntnaeem::hottentot::examples::echoer::ResponseMessage resp;
    proxy->EchoMessage(req, resp);
    std::cout << resp.GetMessage() << std::endl;
    // ====================================================
    ::ir::ntnaeem::hottentot::examples::echoer::proxy::EchoServiceProxyBuilder::Destroy(proxy);
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "Proxy object is destroyed." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::proxy::ProxyRuntime::Shutdown();
    if (::org::labcrypto::hottentot::runtime::Configuration::Verbose()) {
      ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "Proxy runtime is shutdown." << std::endl;
    }
    ::org::labcrypto::hottentot::runtime::Logger::Shutdown();  
  } catch (...) {
    ::org::labcrypto::hottentot::runtime::Logger::GetOut() << "Error." << std::endl;
    return 1;
  }
  return 0;
}
