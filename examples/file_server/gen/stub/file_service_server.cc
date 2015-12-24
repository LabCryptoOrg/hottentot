/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 25-12-2015 12:31:58
 * Name: file_service_server.cc
 * Description:
 *   This file contains definitions of sample stub.
 ******************************************************************/
 
#include <iostream>

#include <naeem/hottentot/runtime/logger.h>
#include <naeem/hottentot/runtime/service/service_runtime.h>



#include "file_service_impl.h"


int
main(int argc, char **argv) {
  try {
    ::naeem::hottentot::runtime::Logger::Init();
    ::naeem::hottentot::runtime::Logger::GetOut() << "Starting server ..." << std::endl;
    ::naeem::hottentot::runtime::service::ServiceRuntime::Init(argc, argv);
    ::ir::ntnaeem::hottentot::examples::file::server::FileServiceImpl *service =
        new ::ir::ntnaeem::hottentot::examples::file::server::FileServiceImpl;
    ::naeem::hottentot::runtime::service::ServiceRuntime::Register("0.0.0.0", 2000, service);
    ::naeem::hottentot::runtime::service::ServiceRuntime::Start();
  } catch (...) {
    std::cout << "Error." << std::endl;
    return 1;
  }
  return 0;
}
