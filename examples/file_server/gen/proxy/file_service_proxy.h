/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 11-01-2016 11:34:13
 * Name: file_service_proxy.h
 * Description:
 *   This file contains definition of the proxy class.
 ***************************************************************/

#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_FILE_SERVER__PROXY__FILE_SERVICE_PROXY_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_FILE_SERVER__PROXY__FILE_SERVICE_PROXY_H_

#include <stdint.h>
#include <string>

#include <naeem/hottentot/runtime/types/primitives.h>
#include <naeem/hottentot/runtime/proxy/proxy.h>

#include "../file_service.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace file {
namespace server {

namespace proxy {
  class FileServiceProxy : public ::ir::ntnaeem::hottentot::examples::file::server::FileService, 
    public ::naeem::hottentot::runtime::proxy::Proxy {
  public:
    FileServiceProxy(std::string host, uint32_t port) 
      : ::naeem::hottentot::runtime::proxy::Proxy(host, port) {}
    virtual ~FileServiceProxy() {}
  public:
    virtual void UploadFile(::naeem::hottentot::runtime::types::Utf8String &fileName, ::naeem::hottentot::runtime::types::ByteArray &content);
    virtual void FileExists(::naeem::hottentot::runtime::types::Utf8String &fileName, ::naeem::hottentot::runtime::types::Boolean &);
    virtual void DownloadFile(::naeem::hottentot::runtime::types::Utf8String &fileName, ::naeem::hottentot::runtime::types::ByteArray &);
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE server
} // END OF NAMESPACE file
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif