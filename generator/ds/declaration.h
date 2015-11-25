/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifndef _NAEEM_HOTTENTOT_GENERATOR__DS__DECLARATION_H_
#define _NAEEM_HOTTENTOT_GENERATOR__DS__DECLARATION_H_

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
#include <stdlib.h>


namespace naeem {
  namespace hottentot {
    namespace generator {
      namespace java {
        class JavaGenerator;
      };
      namespace cc {
        class CCGenerator;
      };
      namespace ds {
        class Declaration {
          friend class ::naeem::hottentot::generator::cc::CCGenerator;
          friend class ::naeem::hottentot::generator::java::JavaGenerator;
        public:
          Declaration(std::string type = "", 
                      std::string variable = "",
                      std::string ordString = "")
            : type_(type),
              variable_(variable) {
              ord_ = atoi(ordString.substr(4, ordString.size() - 5).c_str());
          }
          virtual ~Declaration() {}
        public:
          inline std::string GetType() const {
            return type_;
          }
          inline void SetType(std::string type) {
            type_ = type;
          }
          inline std::string GetVariable() const {
            return variable_;
          }
          inline void SetVariable(std::string variable) {
            variable_ = variable;
          }
          inline uint32_t GetOrd() const {
            return ord_;
          }
          inline void SetOrd(uint32_t ord) {
            ord_ = ord;
          }
          inline virtual void Display() {
            std::cout << variable_ << ": " << type_ << " with ORD(" << ord_ << ")";
          }
        protected:
          std::string type_;
          std::string variable_;
          uint32_t ord_;
        };
      }
    }
  }
}

#endif