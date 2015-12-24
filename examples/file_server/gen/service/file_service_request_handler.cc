/****************************************************************************
 * Generated by Hottentot CC Generator
 * Date: 25-12-2015 12:31:58
 * Name: file_service_request_handler.cc
 * Description:
 *   This file contains implementation of service's request handler class.
 ****************************************************************************/
 
#include <string.h>

#include <naeem/hottentot/runtime/request.h>
#include <naeem/hottentot/runtime/response.h>

#include "file_service_request_handler.h"
#include "abstract_file_service.h"
#include "../file_service.h"



namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace file {
namespace server {
namespace service {
  void 
  FileServiceRequestHandler::HandleRequest(::naeem::hottentot::runtime::Request &request, ::naeem::hottentot::runtime::Response &response) {
    if (request.GetMethodId() == 1684534004) {
      ::ir::ntnaeem::hottentot::examples::file::server::service::AbstractFileService *serviceObject = 
        dynamic_cast< ::ir::ntnaeem::hottentot::examples::file::server::service::AbstractFileService*>(service_);
      /*
       * Deserialization and making input variables
       */
      ::naeem::hottentot::runtime::types::Utf8String fileName;
      fileName.Deserialize(request.GetArgumentData(0), request.GetArgumentLength(0));
      ::naeem::hottentot::runtime::types::ByteArray content;
      content.Deserialize(request.GetArgumentData(1), request.GetArgumentLength(1));
      /*
       * Calling service method
       */
      serviceObject->UploadFile(fileName, content);
      /*
       * Serializiation of returned object
       */
      uint32_t serializedDataLength = 0;
      unsigned char *serializedData = 0;
      response.SetStatusCode(0);
      response.SetData(serializedData);
      response.SetDataLength(serializedDataLength);
      return;
    }
    if (request.GetMethodId() == 2334478716) {
      ::ir::ntnaeem::hottentot::examples::file::server::service::AbstractFileService *serviceObject = 
        dynamic_cast< ::ir::ntnaeem::hottentot::examples::file::server::service::AbstractFileService*>(service_);
      /*
       * Deserialization and making input variables
       */
      ::naeem::hottentot::runtime::types::Utf8String fileName;
      fileName.Deserialize(request.GetArgumentData(0), request.GetArgumentLength(0));
      /*
       * Calling service method
       */
      ::naeem::hottentot::runtime::types::Boolean result = serviceObject->FileExists(fileName);
      /*
       * Serializiation of returned object
       */
      uint32_t serializedDataLength = 0;
      unsigned char *serializedData = result.Serialize(&serializedDataLength);

      response.SetStatusCode(0);
      response.SetData(serializedData);
      response.SetDataLength(serializedDataLength);
      return;
    }
    if (request.GetMethodId() == 1540637629) {
      ::ir::ntnaeem::hottentot::examples::file::server::service::AbstractFileService *serviceObject = 
        dynamic_cast< ::ir::ntnaeem::hottentot::examples::file::server::service::AbstractFileService*>(service_);
      /*
       * Deserialization and making input variables
       */
      ::naeem::hottentot::runtime::types::Utf8String fileName;
      fileName.Deserialize(request.GetArgumentData(0), request.GetArgumentLength(0));
      /*
       * Calling service method
       */
      ::naeem::hottentot::runtime::types::ByteArray result = serviceObject->DownloadFile(fileName);
      /*
       * Serializiation of returned object
       */
      uint32_t serializedDataLength = 0;
      unsigned char *serializedData = result.Serialize(&serializedDataLength);

      response.SetStatusCode(0);
      response.SetData(serializedData);
      response.SetDataLength(serializedDataLength);
      return;
    }
    char errorMessage[] = "Method not found.";
    response.SetStatusCode(1);
    response.SetData((unsigned char*)errorMessage);
    response.SetDataLength(strlen(errorMessage));
  }
} // END OF NAMESPACE service
} // END OF NAMESPACE server
} // END OF NAMESPACE file
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir