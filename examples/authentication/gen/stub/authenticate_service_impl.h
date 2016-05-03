/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 02-05-2016 05:18:41
 * Name: authenticate_service_impl.h
 * Description:
 *   This file contains definitions of sample stub.
 ******************************************************************/
 
#ifndef _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_IMPL_H_
#define _NAEEM_HOTTENTOT_EXAMPLES_AUTH__AUTHENTICATE_SERVICE_IMPL_H_

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

#include "../service/abstract_authenticate_service.h"


namespace naeem {
namespace hottentot {
namespace examples {
namespace auth {
  class AuthenticateServiceImpl : public ::naeem::hottentot::examples::auth::service::AbstractAuthenticateService {
  public:
    AuthenticateServiceImpl() {}
    virtual ~AuthenticateServiceImpl() {}
  public:
    virtual void OnInit();
    virtual void OnShutdown();
    virtual void Authenticate(
      ::naeem::hottentot::examples::auth::Credential &credential, 
      ::naeem::hottentot::examples::auth::Token &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    );
    virtual void F(
      ::org::labcrypto::hottentot::Utf8String &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    );
    virtual void G(
      ::org::labcrypto::hottentot::Int32 &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    );
    virtual void H(
      ::org::labcrypto::hottentot::ByteArray &out, 
      ::org::labcrypto::hottentot::runtime::service::HotContext &hotContext
    );
  };
} // END OF NAMESPACE auth
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE naeem

#endif