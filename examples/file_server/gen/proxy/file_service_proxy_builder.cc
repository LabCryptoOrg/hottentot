/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 25-12-2015 12:31:58
 * Name: file_service_proxy_builder.cc
 * Description:
 *   This file contains implementation of the proxy builder class.
 ******************************************************************/

#include "file_service_proxy_builder.h"
#include "file_service_proxy.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace file {
namespace server {
namespace proxy {
  FileService*
  FileServiceProxyBuilder::Create(std::string host, uint32_t port) {
    return new FileServiceProxy(host, port);
  }
  void
  FileServiceProxyBuilder::Destroy(FileService *service) {
    delete service;
  }
} // END OF NAMESPACE proxy
} // END OF NAMESPACE server
} // END OF NAMESPACE file
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir