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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <iostream>
#include <fstream>

#include "cc_generator.h"
#include "type_helper.h"

#include "templates/templates.h"
 
#include "../hot.h"
#include "../service.h"
#include "../method.h"
#include "../module.h"
#include "../argument.h"
#include "../struct.h"
#include "../declaration.h"
#include "../os.h"
#include "../string_helper.h"
#include "../datetime_helper.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace generator {
namespace cc {
  void
  CCGenerator::GenerateEnums (
    std::vector< ::org::labcrypto::hottentot::generator::Module*> modules,
    ::org::labcrypto::hottentot::generator::GenerationConfig &generationConfig,
    std::map<std::string, std::string> &templates
  ) {
    std::string indent = generationConfig.GetIndentString();
    /*
     * Making needed variables and assigning values to them
     */
    std::string enumsFilePath = generationConfig.GetOutDir() + "/enums.h";
    
    /*
     * Making real values
     */
    std::vector<std::string> totalPackageTokens;
    std::string namespacesAndEnums = "";
    for (uint32_t i = 0; i < modules.size(); i++) {
      ::org::labcrypto::hottentot::generator::Module *module = modules[i];
      std::string ns = "::" + 
        ::org::labcrypto::hottentot::generator::StringHelper::Concat ( 
          ::org::labcrypto::hottentot::generator::StringHelper::Split (
            module->GetPackage(), 
            '.'
          ), 
          "::"
        );
      std::vector<std::string> packageTokens = 
        ::org::labcrypto::hottentot::generator::StringHelper::Split (
          module->GetPackage(), 
          '.'
        );
      totalPackageTokens.insert(totalPackageTokens.end(), packageTokens.begin(), packageTokens.end());
      std::string namespacesStart = "";
      for (uint32_t i = 0; i < packageTokens.size(); i++) {
        namespacesStart += "namespace " + 
          ::org::labcrypto::hottentot::generator::StringHelper::MakeLowerCase(packageTokens[i]) + " {\r\n";
      }
      std::string namespacesEnd = "";
      for (int32_t i = packageTokens.size() - 1; i >= 0; i--) {
        namespacesEnd += "} // END OF NAMESPACE " + packageTokens[i] + "\r\n";
      }
      namespacesStart = ::org::labcrypto::hottentot::generator::StringHelper::Trim(namespacesStart);
      namespacesEnd = ::org::labcrypto::hottentot::generator::StringHelper::Trim(namespacesEnd);
      std::string enums = "";
      
      for (uint32_t i = 0; i < module->enums_.size(); i++) {
        enums += indent + "enum " + module->enums_[i]->GetName() + " {\r\n";
        std::map<uint16_t, std::string>::iterator finalItemIter = module->enums_[i]->revItems_.end();
        --finalItemIter;
        for (std::map<uint16_t, std::string>::iterator it = module->enums_[i]->revItems_.begin();
             it != module->enums_[i]->revItems_.end();
             it++) {
          std::stringstream ss;
          ss << indent << indent << "k" << 
            module->enums_[i]->GetName() << "___" << 
              it->second << " = " << it->first;
          if (it != finalItemIter) {
            ss << ",";
          }
          ss << std::endl;
          enums += ss.str();
        }
        enums += indent + "};\r\n";
      }
      namespacesAndEnums += namespacesStart + "\r\n" + enums + namespacesEnd;
    }
    /*
     * Filling templates with real values
     */
    std::map<std::string, std::string> params;
    params.insert(std::pair<std::string, std::string>("GENERATION_DATE", 
      ::org::labcrypto::hottentot::generator::DateTimeHelper::GetCurrentDateTime()));
    params.insert(std::pair<std::string, std::string>("FILENAME", "enums.h"));
    params.insert(std::pair<std::string, std::string>("HEADER_GUARD", "_" +
      ::org::labcrypto::hottentot::generator::StringHelper::MakeScreamingSnakeCase (
        totalPackageTokens
      ) + "__ENUMS_H_"));
    params.insert(std::pair<std::string, std::string>("NAMESPACES_AND_ENUMS", namespacesAndEnums));
    params.insert(std::pair<std::string, std::string>("INDENT", indent));
    std::string enumsTemplate = templates["enums"];
    for (std::map<std::string, std::string>::iterator it = params.begin();
         it != params.end();
         ++it) {
      enumsTemplate = 
        ::org::labcrypto::hottentot::generator::StringHelper::Replace (
          enumsTemplate, 
          "[[[" + it->first + "]]]", 
          it->second
        );
    }
    /*
     * Writing final results to files
     */
    std::fstream f;
    f.open(enumsFilePath.c_str(), std::fstream::out | std::fstream::binary);
    f << enumsTemplate;
    f.close();
  }
}
}
}
}
}