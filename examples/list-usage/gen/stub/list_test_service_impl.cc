/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 12-01-2016 06:33:40
 * Name: list_test_service_impl.cc
 * Description:
 *   This file contains empty implementation of sample stub.
 ******************************************************************/
 
#include <naeem/hottentot/runtime/utils.h>
 #include <naeem/hottentot/runtime/logger.h>

#include "list_test_service_impl.h"




namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace listtest {
  void
  ListTestServiceImpl::AddNames(list<string> &names) {
    ::naeem::hottentot::runtime::Logger::GetOut() << "ListTestServiceImpl::AddNames() is called." << std::endl;
    // TODO
  }
  void
  ListTestServiceImpl::GetNames(list<string> &out) {
    ::naeem::hottentot::runtime::Logger::GetOut() << "ListTestServiceImpl::GetNames() is called." << std::endl;
    // TODO
  }
} // END OF NAMESPACE listtest
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir