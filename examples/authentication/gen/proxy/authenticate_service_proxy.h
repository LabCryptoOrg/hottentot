/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 05:18:41
 * Name: authenticate_service_proxy.h
 * Description:
 *   This file contains definition of the proxy class.
 ***************************************************************/

#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__PROXY__AUTHENTICATE_SERVICE_PROXY_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__PROXY__AUTHENTICATE_SERVICE_PROXY_H_

#ifdef _MSC_VER
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#include <string>

#include <org/labcrypto/hottentot/primitives.h>
#include <org/labcrypto/hottentot/runtime/proxy/proxy.h>

#include "authenticate_service.h"
#include "../enums.h"


namespace naeem {
namespace hottentot {
namespace examples {
namespace auth {
class Credential;
class User;
class Token;
namespace proxy {
  class AuthenticateServiceProxy : public AuthenticateService, 
    public ::org::labcrypto::hottentot::runtime::proxy::Proxy {
  public:
    AuthenticateServiceProxy(std::string host, uint32_t port) 
      : ::org::labcrypto::hottentot::runtime::proxy::Proxy(host, port) {}
    virtual ~AuthenticateServiceProxy() {}
  public:
    virtual void Authenticate(
      ::naeem::hottentot::examples::auth::Credential &credential, 
      ::naeem::hottentot::examples::auth::Token &out
    );
    virtual void F(
      ::org::labcrypto::hottentot::Utf8String &out
    );
    virtual void G(
      ::org::labcrypto::hottentot::Int32 &out
    );
    virtual void H(
      ::org::labcrypto::hottentot::ByteArray &out
    );
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE auth
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE naeem

#endif