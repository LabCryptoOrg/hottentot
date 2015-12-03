/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 03-12-2015 11:21:04
 * Name: calculator_service_impl.h
 * Description:
 *   This file contains definitions of sample stub.
 ******************************************************************/
 
#ifndef _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__CALCULATOR_SERVICE_IMPL_H_
#define _IR_NTNAEEM_HOTTENTOT_EXAMPLES_CALC__CALCULATOR_SERVICE_IMPL_H_

#include <stdint.h>
#include <string>

#include "../service/abstract_calculator_service.h"


namespace ir {
namespace ntnaeem {
namespace hottentot {
namespace examples {
namespace calc {
  class CalculatorServiceImpl : public ::ir::ntnaeem::hottentot::examples::calc::service::AbstractCalculatorService {
  public:
    CalculatorServiceImpl() {}
    virtual ~CalculatorServiceImpl() {}
  public:
    virtual ::naeem::hottentot::runtime::types::UInt16 Add(::naeem::hottentot::runtime::types::UInt16 a, ::naeem::hottentot::runtime::types::UInt16 b);
    virtual ::naeem::hottentot::runtime::types::Int16 Mul(::naeem::hottentot::runtime::types::Int16 a, ::naeem::hottentot::runtime::types::Int16 b);
  };
} // END OF NAMESPACE calc
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE ntnaeem
} // END OF NAMESPACE ir

#endif