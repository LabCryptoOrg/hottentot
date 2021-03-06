/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 30-01-2016 08:21:47
 * Name: test_service_client.h
 * Description:
 *   This file contains a sample client.
 ******************************************************************/

#include <iostream>

#include <naeem/hottentot/runtime/configuration.h>
#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/proxy/proxy_runtime.h>
 #include <naeem/hottentot/runtime/utils.h>


 #include <string>

#include "../token.h"
#include "../credential.h"
#include "../data_wrapper.h"
#include "../string_wrapper.h"
#include "../sample_struct.h"
#include "../result.h"
#include "../test_service.h"
#include "../proxy/test_service_proxy_builder.h"


int 
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::Logger::Init();  
    ::naeem::hottentot::runtime::proxy::ProxyRuntime::Init(argc, argv);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy runtime is initialized." << std::endl;
    }
    ::hotgen::TestService *proxy = 
        ::hotgen::proxy::TestServiceProxyBuilder::Create("127.0.0.1", 8000);
    if (::naeem::hottentot::runtime::Configuration::Verbose()) {
      ::naeem::hottentot::runtime::Logger::GetOut() << "Proxy object is created." << std::endl;
    }
    // TODO Do whatever you want with proxy objects.
    //TEST2
    /*
    ::naeem::hottentot::runtime::types::List< ::hotgen::StringWrapper> out;
    proxy->Test2(out);
    std::cout << "SIZE : " << out.Size() << std::endl;
    for(int i = 0 ; i < out.Size() ; i++) {
      std::cout << out.Get(i)->GetValue().ToStdString() << std::endl;
    }
    */
    //TEST4
    /*
    ::hotgen::DataWrapper test4out;
    proxy->Test4(test4out);
    ::naeem::hottentot::runtime::types::ByteArray bytes = test4out.GetDigi();
    std::cout << "test 4 : byte array out length : " << bytes.GetLength() << std::endl;
    ::naeem::hottentot::runtime::Utils::PrintArray("RES", bytes.GetValue(), bytes.GetLength());
    */
    //
    //TEST5
    ::naeem::hottentot::runtime::types::List< ::hotgen::StringWrapper> inputList;
    ::hotgen::StringWrapper *stringWrapper = new ::hotgen::StringWrapper();
    std::string str = "";
    for(int i = 0 ; i < 256 ; i++) {
      str += "a";
    }
    ::naeem::hottentot::runtime::types::Utf8String *utf8str = 
    new  ::naeem::hottentot::runtime::types::Utf8String(str);
    stringWrapper->SetValue(&utf8str);
    inputList.Add(stringWrapper);
    ::hotgen::StringWrapper *stringWrapper2 = new ::hotgen::StringWrapper();
    stringWrapper2->SetValue("a");
    inputList.Add(stringWrapper2);
    ::hotgen::DataWrapper test5out;
    proxy->Test5(inputList,test5out);
    ::naeem::hottentot::runtime::types::ByteArray bytes2 = test5out.GetDigi();
    ::naeem::hottentot::runtime::Utils::PrintArray("RES", bytes2.GetValue(), bytes2.GetLength());
    //
    ::hotgen::proxy::TestServiceProxyBuilder::Destroy(proxy);
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
