/***************************************************************
 * Generated by Hottentot CC Generator
 * Date: 10-02-2016 11:35:21
 * Name: apache_license_manager_service_proxy.h
 * Description:
 *   This file contains definition of the proxy class.
 ***************************************************************/

#ifndef _ORG_APACHE_TESTS__PROXY__APACHE_LICENSE_MANAGER_SERVICE_PROXY_H_
#define _ORG_APACHE_TESTS__PROXY__APACHE_LICENSE_MANAGER_SERVICE_PROXY_H_

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

#include <naeem/hottentot/runtime/types/primitives.h>
#include <naeem/hottentot/runtime/proxy/proxy.h>

#include "apache_license_manager_service.h"


namespace org {
namespace apache {
namespace tests {
class License;
namespace proxy {
  class ApacheLicenseManagerServiceProxy : public ApacheLicenseManagerService, 
    public ::naeem::hottentot::runtime::proxy::Proxy {
  public:
    ApacheLicenseManagerServiceProxy(std::string host, uint32_t port) 
      : ::naeem::hottentot::runtime::proxy::Proxy(host, port) {}
    virtual ~ApacheLicenseManagerServiceProxy() {}
  public:
    virtual void GetThem(
      ::org::apache::tests::set<License> &out
    );
    virtual void GetMap(
      ::naeem::hottentot::runtime::types::List< ::naeem::hottentot::runtime::types::Utf8String> &names, 
      ::org::apache::tests::set<map<list<int>,string>> &s, 
      ::org::apache::tests::map<list<Person>,asdasdaasdasdsda> &out
    );
  };
} // END OF NAMESPACE proxy
} // END OF NAMESPACE tests
} // END OF NAMESPACE apache
} // END OF NAMESPACE org

#endif