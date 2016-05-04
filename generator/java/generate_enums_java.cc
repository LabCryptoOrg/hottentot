/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 LabCrypto Org.
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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANindent_ILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <sys/stat.h>

#include <map>
#include <sstream>

#include "java_generator.h"

#include "../hot.h"
#include "../string_helper.h"
#include "../os.h" 
#include "../type_helper.h" 
#include "../runtime.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace java {
  void
  JavaGenerator::GenerateEnums(::naeem::hottentot::generator::ds::Module *pModule) {
    //TODO make struct for PDT arg and return type in methods
    for (int i = 0; i < pModule->enums_.size(); i++) {
      ::naeem::hottentot::generator::ds::Enum *pEnum = pModule->enums_.at(i);
      std::string basePackageName = pModule->package_;
      std::string replacableEnumTmpStr = enumTmpStr_;
      ::naeem::hottentot::generator::common::Runtime::enums_.push_back(pEnum);
      std::map<uint16_t, std::string>::iterator it;
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableEnumTmpStr, 
        "[%BASE_PACKAGE_NAME%]", 
        basePackageName, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableEnumTmpStr, 
        "[%INDENT%]", 
        indent_, 
        1
      );
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableEnumTmpStr, 
        "[%ENUM_NAME%]", 
        pEnum->GetName(),
        1
      );
      std::string membersStr = "";
      uint8_t mapCounter = 1;
      for (std::map<uint16_t, std::string>::iterator it = pEnum->revItems_.begin();
           it != pEnum->revItems_.end();
           ++it) {
        std::string itemName = it->second;
        uint16_t itemValue = it->first;
        std::stringstream itemValueStr;
        itemValueStr << itemValue;
        membersStr += indent_ +  itemName + "((short) " + itemValueStr.str() +  ")";
        if (mapCounter != pEnum->revItems_.size()) {
          membersStr += ",\n";
        } else {
          membersStr += ";";
        }
        mapCounter++;
      }
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableEnumTmpStr, 
        "[%MEMBERS%]", 
        membersStr, 
        1
      );
      std::string deserializeMethodBodyStr = "";
      for (std::map<uint16_t, std::string>::iterator it = pEnum->revItems_.begin();
           it != pEnum->revItems_.end();
           ++it) {
        std::string itemName = it->second;
        uint16_t itemValue = it->first;
        std::stringstream itemValueStr;
        itemValueStr << itemValue;
        deserializeMethodBodyStr += indent_ + indent_ +  
                                    "if(value == " + itemValueStr.str() +  "){\n";
        deserializeMethodBodyStr += indent_ + indent_ + indent_ +   
                                    "return " + pEnum->GetName() + "." + itemName + ";\n";
        deserializeMethodBodyStr += indent_ + indent_ + "}\n";
      }
      ::naeem::hottentot::generator::common::StringHelper::Replace (
        replacableEnumTmpStr, 
        "[%DESERIALIZE_METHOD_BODY%]", 
        deserializeMethodBodyStr, 
        1
      );  
      std::string path = outDir_ + "/" + pEnum->GetName().c_str() + ".java";
      ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableEnumTmpStr);
    }
  }
} // END NAMESPACE java
} // END NAMESPACE generator
} // END NAMESPACE hottentot
} // END NAMESPACE labcrypto
} // END NAMESPACE org