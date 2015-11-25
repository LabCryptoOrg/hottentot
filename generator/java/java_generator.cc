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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTAB_STR_ILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include "java_generator.h"
#include "../ds/hot.h"
#include <stdint.h>
#include <sys/stat.h>
#include <sstream>
#include "../common/string_helper.h"
#include "../common/os.h" 
#include "templates/byte_arrays/abstractService.h" 
#include "templates/byte_arrays/requestHandler.h" 
#include "templates/byte_arrays/service.h" 
#include "templates/byte_arrays/serviceProxy.h" 
#include "templates/byte_arrays/serviceProxyBuilder.h" 
#include "templates/byte_arrays/struct.h" 

namespace naeem {
    namespace hottentot {
        namespace generator {
            namespace java {

                JavaGenerator::~JavaGenerator() {
                    //TODO change vector to map 

                    // for (int i = 0; i < modules_.size(); i++) {
                    //     ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);
                    //     for (int j = 0; j < pModule->structs_.size(); j++) {
                    //         ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(j);
                    //         for (int k = 0; k < pStruct->declarations_.size(); k++) {
                    //             delete pStruct->declarations_.at(k);
                    //         }
                    //         delete pStruct;
                    //     }
                    //     delete pModule;
                    // }
                }


                JavaGenerator::JavaGenerator() {
                    
                    //MakeStringsFromByteArrays();
                    //ReadTemplateFiles();
                }

                void
                JavaGenerator::MakeTabStr(::naeem::hottentot::generator::GenerationConfig &generationConfig){
                    outDir_ = generationConfig.outDir_;
                    if(generationConfig.IsSpacesUsedInsteadOfTabsForIndentation()) {
                        for (int i = 0; i < generationConfig.GetNumberOfSpacesUsedForIndentation() ; i++) {
                            TAB_STR_ += " ";
                        }
                    }else{
                        TAB_STR_ = "\t";
                    }
                }

                void
                JavaGenerator::Generate(::naeem::hottentot::generator::ds::Hot *hot,
                                        ::naeem::hottentot::generator::GenerationConfig &generationConfig) {
                    MakeTabStr(generationConfig);
                    ::naeem::hottentot::generator::common::Os::MakeDir(outDir_.c_str());
                    modules_ = hot->modules_;
                    for (int i = 0; i < modules_.size(); i++) {
                        ::naeem::hottentot::generator::ds::Module *pModule = modules_.at(i);
                        GenerateStructs(pModule);
                        GenerateAbstractService(pModule);
                        GenerateServiceInterface(pModule);
                        GenerateRequestHandler(pModule);
                        GenerateServiceProxyBuilder(pModule);
                        GenerateServiceProxy(pModule);
                    }
                    std::cout << "Java Generation done." << std::endl;
                }

                std::string
                JavaGenerator::ConvertType(std::string hotType){
                	std::string javaType;
                	if (hotType.compare("string") == 0) {
						javaType = "String";
					} else if (hotType.compare("int8") == 0 ||
					           hotType.compare("uint8") == 0) {
					    javaType = "short";
					} else if (hotType.compare("int16") == 0 ||
					           hotType.compare("uint16") == 0) {
					    javaType = "short";
					} else if (hotType.compare("int32") == 0 ||
					           hotType.compare("uint32") == 0) {
					    javaType = "int";
					} else if (hotType.compare("int64") == 0 ||
					           hotType.compare("uint64") == 0) {
					    javaType = "long";
					}
					return javaType;
                }

                uint32_t
                JavaGenerator::GetTypeLength(std::string type){
                    if (type.compare("int8") == 0 ||
                        type.compare("uint8") == 0) {
                        return 1;
                    } else if (type.compare("int16") == 0 ||
                               type.compare("uint16") == 0) {
                        return 2;
                    } else if (type.compare("int32") == 0 ||
                               type.compare("uint32") == 0) {
                        return 4;
                    } else if (type.compare("int64") == 0 ||
                               type.compare("uint64") == 0) {
                        return 8;
                    }
                }

                void
                JavaGenerator::ReadTemplateFiles() {
                    ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/struct.template",structTmpStr_);
                    ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/abstractService.template",abstractServiceTmpStr_);
                    ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/service.template",serviceTmpStr_);
                    ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/serviceProxy.template",serviceProxyTmpStr_);
                    ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/serviceProxyBuilder.template",serviceProxyBuilderTmpStr_);
                    ::naeem::hottentot::generator::common::Os::ReadFile("./java/templates/requestHandler.template",requestHandlerTmpStr_);
//			std::cout << "---------------" << std::endl;
//			std::cout << structTmpStr_;
//			std::cout << abstractServiceTmpStr_`//			std::cout << serviceTmpStr_;
//			std::cout << serviceProxyBuilderTmpStr_;
//			std::cout << serviceProxyTmpStr_;
//			std::cout << requestHandlerTmpStr_;
                }

                void
                JavaGenerator::GenerateStructs(::naeem::hottentot::generator::ds::Module *pModule) {
                    //loop on structs in everey module
                    for (int i = 0; i < pModule->structs_.size(); i++) {
                        ::naeem::hottentot::generator::ds::Struct *pStruct = pModule->structs_.at(i);
                        std::string basePackageName = pModule->package_;
                        std::string replacableStructTmpStr = structTmpStr;

                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableStructTmpStr , "[%STRUCT_NAME%]" , pStruct->name_ , 1);
                        // while (replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableStructTmpStr.replace(replacableStructTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                        //                                    basePackageName);
                        // }
                        // while (replacableStructTmpStr.find("[%STRUCT_NAME%]") != std::string::npos) {
                        //     replacableStructTmpStr.replace(replacableStructTmpStr.find("[%STRUCT_NAME%]"), 15,
                        //                                    pStruct->name_);
                        // }
                        std::string declarationStr;
                        std::string getterSetterStr;
                        std::string declarationJavaType;
                        std::string capitalizedDeclarationJavaType;

                        for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
                             = pStruct->declarations_.begin();
                             it != pStruct->declarations_.end();
                             ++it) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
                            declarationJavaType = ConvertType(declarationPtr->type_);
                            capitalizedDeclarationJavaType  = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationJavaType);
                            std::string declarationName = declarationPtr->variable_;
                            std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationPtr->variable_);
                            declarationStr +=
                                    TAB_STR_ + "private " + declarationJavaType + " " + declarationName + ";\n";
                            getterSetterStr += TAB_STR_ + "public void set" + capitalizedDeclarationName + "(" +
                                               declarationJavaType + " " + declarationName + ") {\n";
                            getterSetterStr +=
                                    TAB_STR_ + TAB_STR_ + "this." + declarationName + " = " + declarationName + ";\n";
                            getterSetterStr += TAB_STR_ + "}\n";
                            getterSetterStr +=
                                    TAB_STR_ + "public " + declarationJavaType + " get" + capitalizedDeclarationName +
                                    "() {\n";
                            getterSetterStr += TAB_STR_ + TAB_STR_ + "return " + declarationPtr->variable_ + ";\n";
                            getterSetterStr += TAB_STR_ + "}\n";
                        }
                        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%MEMBERS%]"), 11,
                                                       declarationStr + getterSetterStr);

                        //serilize method
                        std::string serializeMethodStr;
                        for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
                             = pStruct->declarations_.begin();
                             it != pStruct->declarations_.end();
                             ++it) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
                            std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationPtr->variable_);
                            serializeMethodStr += TAB_STR_ + TAB_STR_ + "byte[] serialized" + capitalizedDeclarationName + " = PDTSerializer.get";
                            declarationJavaType = ConvertType(declarationPtr->type_);
                            capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationJavaType);
                            std::string capitalizedDeclarationType  = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationPtr->type_);
                            serializeMethodStr += capitalizedDeclarationType + "(";
                            serializeMethodStr += declarationPtr->variable_ + ");\n";
                        }
                        serializeMethodStr += TAB_STR_ + TAB_STR_ + "byte[] output = new byte[";
                        for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
                             = pStruct->declarations_.begin();
                             it != pStruct->declarations_.end();
                             ++it) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
                            std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationPtr->variable_.c_str());
                            serializeMethodStr += "serialized" + capitalizedDeclarationName + ".length";
                            if (it->first == pStruct->declarations_.size()) {
                                serializeMethodStr += "];\n";
                            } else {
                                serializeMethodStr += " + ";
                            }
                        }

                        serializeMethodStr += TAB_STR_ + TAB_STR_ + "int counter = 0;\n";
                        serializeMethodStr += TAB_STR_ + TAB_STR_ + "//use a loop for every property\n";
                        for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
                             = pStruct->declarations_.begin();
                             it != pStruct->declarations_.end();
                             ++it) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
                            declarationJavaType = ConvertType(declarationPtr->type_);
                            capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationJavaType);
                            std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationPtr->variable_);
                            serializeMethodStr += TAB_STR_ + TAB_STR_ + "for (int i = 0; i < serialized" +
                                                  capitalizedDeclarationName + ".length; i++) {\n";
                            serializeMethodStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "output[counter++] = serialized" +
                                                  capitalizedDeclarationName + "[i];\n";
                            serializeMethodStr += TAB_STR_ + TAB_STR_ + "}\n";
                        }
                        serializeMethodStr += TAB_STR_ + TAB_STR_ + "return output;";
                        //
                        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%SERIALIZE_METHOD_BODY%]"), 25,
                                                       serializeMethodStr);
                        // sample code
                              // byte[] serializedId = PDTSerializer.getInt16(id);
                              // byte[] serializedValue = PDTSerializer.getString(value);
                              // byte[] output = new byte[serializedId.length + serializedValue.length];
                              // int counter = 0;
                              // //use a loop for every property
                              // for (int i = 0; i < serializedId.length; i++) {
                              //     output[counter++] = serializedId[i];
                              // }
                              // for (int i = 0; i < serializedValue.length; i++) {
                              //     output[counter++] = serializedValue[i];
                              // }
                              // return output;


                        // deserialize method
                        std::string deserializeMethodStr;
                        deserializeMethodStr += TAB_STR_ + TAB_STR_ + "int counter = 0;\n";
                        deserializeMethodStr += TAB_STR_ + TAB_STR_ + "int dataLength = 0;\n";
                        deserializeMethodStr += TAB_STR_ + TAB_STR_ + "int numbersOfBytesForDataLength;\n";
                        deserializeMethodStr += TAB_STR_ + TAB_STR_ + "//do for every property\n";
                        for (std::map<uint32_t, ::naeem::hottentot::generator::ds::Declaration*>::iterator it 
                             = pStruct->declarations_.begin();
                             it != pStruct->declarations_.end();
                             ++it) {
                            ::naeem::hottentot::generator::ds::Declaration *declarationPtr = it->second;
                            declarationJavaType = ConvertType(declarationPtr->type_);
                            std::string capitalizedDeclarationType = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationPtr->type_);
                            std::string capitalizedDeclarationName = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationPtr->variable_);
                            deserializeMethodStr += TAB_STR_ + TAB_STR_ + "//" + declarationPtr->variable_ + " : " + declarationJavaType + "\n";
                            if(declarationJavaType.compare("String") == 0) {
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "dataLength = 0;\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "if(serializedByteArray[counter] < 0x80){\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "dataLength = serializedByteArray[counter++];\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "}else{\n";             
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "dataLength += pow(256, numbersOfBytesForDataLength - i - 1) * serializedByteArray[counter++];\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "}\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "}\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[dataLength];\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "System.arraycopy(serializedByteArray,counter," + declarationPtr->variable_.c_str() + "ByteArray,0,dataLength);\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "counter += dataLength;\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "set" + capitalizedDeclarationName + "(PDTDeserializer.get" + capitalizedDeclarationType + "(" + declarationPtr->variable_.c_str() + "ByteArray));\n";
                            }else {
                                uint32_t dataLength = GetTypeLength(declarationPtr->type_.c_str());
                                capitalizedDeclarationJavaType = ::naeem::hottentot::generator::common::StringHelper::MakeUpperCase(declarationJavaType);
                                std::stringstream dataLengthStr;
                                dataLengthStr << dataLength;
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "byte[] " + declarationPtr->variable_.c_str() + "ByteArray = new byte[" + dataLengthStr.str() + "];";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "for(int i = 0 ; i < " + dataLengthStr.str() + " ; i++){\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + declarationPtr->variable_.c_str() + "ByteArray[i] = serializedByteArray[counter++];\n";            
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "}\n";
                                deserializeMethodStr += TAB_STR_ + TAB_STR_ + "set" + capitalizedDeclarationName + "(PDTDeserializer.get" + capitalizedDeclarationType + "(" + declarationPtr->variable_.c_str() + "ByteArray));\n";
                            }
                        }
                        
                        replacableStructTmpStr.replace(replacableStructTmpStr.find("[%DESERIALIZE_METHOD_BODY%]"),27,
                                                        deserializeMethodStr);

                        //deserialize sample code 
                        /*
                        int counter = 0;
                        //do for every property
                        //value : string
                        int dataLength = 0 ;
                        int numbersOfBytesForDataLength;
                        if(serializedToken[counter] < 0x80){
                            dataLength = serializedToken[counter++];
                        }else{
                            numbersOfBytesForDataLength = serializedToken[counter++] & 0x0f;
                            for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
                                dataLength += pow(256, numbersOfBytesForDataLength - i - 1) * serializedToken[counter++];
                            }
                        }
                        byte[] valueByteArray = new byte[dataLength];
                        System.arraycopy(serializedToken,counter,valueByteArray,0,dataLength);
                        counter += dataLength;
                        setValue(PDTDeserializer.getString(valueByteArray));
                        //id : int16
                        byte[] idByteArray = new byte[2];
                        for(int i = 0 ; i < 2 ; i++){
                            idByteArray[i] = serializedToken[counter++];
                        }
                        setId(PDTDeserializer.getInt16(idByteArray));
                        */
                        std::string path = outDir_ + "/" + pStruct->name_.c_str() + ".java";
                        ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableStructTmpStr);
                    }
                }

                void
                JavaGenerator::GenerateAbstractService(::naeem::hottentot::generator::ds::Module *pModule) {
                    //loop for every services
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableAbstractServiceTmpStr;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.template
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        std::string path = outDir_ + "/Abstract" + pService->name_.c_str() + "Service.java";
                        os.open(path.c_str(), std::ios::trunc);
                        replacableAbstractServiceTmpStr = abstractServiceTmpStr;

                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableAbstractServiceTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
                        //get service ID from hot parser
                        std::stringstream ssID;
                        ssID << pService->GetHash();
                        replacableAbstractServiceTmpStr.replace(replacableAbstractServiceTmpStr.find("[%SERVICE_ID%]"),
                                                                14, ssID.str());
                        os.write(replacableAbstractServiceTmpStr.c_str(), replacableAbstractServiceTmpStr.size());
                        os.close();
                    }
                }

                void
                JavaGenerator::GenerateServiceInterface(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableServiceTmpStr;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.template
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        //write service interface
                        std::string replacableServiceTmpStr = serviceTmpStr;
                        //std::cout << outDir_;
                        
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
                        // while (replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                        //                                     basePackageName);
                        // }
                        // while (replacableServiceTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                        //     replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_NAME%]"), 16,
                        //                                     pService->name_);
                        // }
                        std::string serviceMethodsStr;
                        //loop for service methods
                        ::naeem::hottentot::generator::ds::Method *pMethod;
                        for (int i = 0; i < pService->methods_.size(); i++) {
                            pMethod = pService->methods_.at(i);
                            serviceMethodsStr += TAB_STR_ + "" + pMethod->returnType_ + " " + pMethod->name_ + "(";
                            //loop on methods arguments
                            ::naeem::hottentot::generator::ds::Argument *pArg;
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                serviceMethodsStr += pArg->type_ + " " + pArg->variable_;
                                if (i < pMethod->arguments_.size() - 1) {
                                    serviceMethodsStr += ",";
                                }
                            }
                            serviceMethodsStr += ");";
                        };
                        replacableServiceTmpStr.replace(replacableServiceTmpStr.find("[%SERVICE_METHODS%]"), 19,
                                                        serviceMethodsStr);


                        std::string path = outDir_ + "/" + pService->name_.c_str() + "Service.java";
                        ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceTmpStr);
                    }
                }

                void
                JavaGenerator::GenerateServiceProxyBuilder(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableServiceProxyBuilderTmpStr;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        //write abstractService.template
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        std::string replacableServiceProxyBuilderTmpStr;
                        //write service proxy builder
                        replacableServiceProxyBuilderTmpStr = serviceProxyBuilderTmpStr;
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyBuilderTmpStr , "[%SERVICE_NAME%]" , pService->name_ , 1);
                        // while (replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableServiceProxyBuilderTmpStr.replace(
                        //             replacableServiceProxyBuilderTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21,
                        //             basePackageName);
                        // }
                        // while (replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                        //     replacableServiceProxyBuilderTmpStr.replace(
                        //             replacableServiceProxyBuilderTmpStr.find("[%SERVICE_NAME%]"), 16, pService->name_);
                        // }

                        std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxyBuilder.java";
                        ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceProxyBuilderTmpStr);
                    }
                }

                void
                JavaGenerator::GenerateRequestHandler(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string replacableRequestHandlerTmpStr;
                    std::string basePackageName = pModule->package_;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        std::string basePackageName = pModule->package_;
                        pService = pModule->services_.at(i);
                        std::string serviceName = pService->name_;
                        std::string lowerCaseServiceName = pService->name_;
                        lowerCaseServiceName[0] += 32;
                        replacableRequestHandlerTmpStr = requestHandlerTmpStr;



                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableRequestHandlerTmpStr , "[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        // while (replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]") != std::string::npos) {
                        //     replacableRequestHandlerTmpStr.replace(
                        //             replacableRequestHandlerTmpStr.find("[%BASE_PACKAGE_NAME%]"), 21, basePackageName);
                        // }
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableRequestHandlerTmpStr,"[%SERVICE_NAME%]" , pService->name_ , 1);
                        // while (replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]") != std::string::npos) {
                        //     replacableRequestHandlerTmpStr.replace(
                        //             replacableRequestHandlerTmpStr.find("[%SERVICE_NAME%]"), 16, pService->name_);
                        // }
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableRequestHandlerTmpStr,"[%SERVICE_NAME_LOWERCASE%]" , lowerCaseServiceName , 1);

                        ::naeem::hottentot::generator::ds::Method *pMethod;
                        std::string methodConditionStr;

                        for (int i = 0; i < pService->methods_.size(); i++) {
                            pMethod = pService->methods_.at(i);
                            std::string lowerCaseReturnType = pMethod->returnType_;
                            lowerCaseReturnType[0] += 32;
                            //get hashed mehod id
                            std::stringstream ssID;
                            ssID << pMethod->GetHash();
                            methodConditionStr += "if(methodId == " + ssID.str() + "){\n";
                            methodConditionStr +=
                                    TAB_STR_ + TAB_STR_ + TAB_STR_ + "List <Argument> args = request.getArgs();\n";
                            ::naeem::hottentot::generator::ds::Argument *pArg;
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                std::stringstream ssI;
                                ssI << i;
                                methodConditionStr +=
                                        TAB_STR_ + TAB_STR_ + TAB_STR_ + "Argument arg" + ssI.str() + " = args.get(" +
                                        ssI.str() + ");\n";
                                methodConditionStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "byte[] serialized" + pArg->type_;
                                methodConditionStr += " = arg" + ssI.str() + ".getData();\n";
                                methodConditionStr +=
                                        TAB_STR_ + TAB_STR_ + TAB_STR_ + pArg->type_ + " " + pArg->variable_ + " = new " +
                                        pArg->type_ + "();\n";
                                methodConditionStr +=
                                        TAB_STR_ + TAB_STR_ + TAB_STR_ + pArg->variable_ + ".deserialize(serialized" +
                                        pArg->type_ + ");\n";
                            }
                            methodConditionStr +=
                                    TAB_STR_ + TAB_STR_ + TAB_STR_ + pMethod->returnType_ + " " + lowerCaseReturnType +
                                    " = null;\n";
                            methodConditionStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "Response response = new Response();\n";
                            //methodConditionStr += TAB_STR_ + TAB_STR_ + "try{\n";
                            methodConditionStr +=
                                    TAB_STR_ + TAB_STR_ + TAB_STR_ + lowerCaseReturnType + " = " + lowerCaseServiceName +
                                    "Impl." + pMethod->name_ + "(";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                methodConditionStr += pArg->variable_;
                                if (i < pMethod->arguments_.size() - 1) {
                                    methodConditionStr += pArg->variable_ += ",";
                                }
                            }
                            methodConditionStr += ");\n";
                            methodConditionStr +=
                                    TAB_STR_ + TAB_STR_ + TAB_STR_ + "byte[] serialized" + pMethod->returnType_ + " = " +
                                    lowerCaseReturnType + ".serialize();\n";
                            methodConditionStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "response.setStatusCode((byte) 100);\n";
                            methodConditionStr +=
                                    TAB_STR_ + TAB_STR_ + TAB_STR_ + "response.setData(serialized" + pMethod->returnType_ +
                                    ");\n";
                            methodConditionStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "response.setLength(serialized" +
                                                  pMethod->returnType_ + ".length + 1);\n";
                            methodConditionStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "return response;\n";
                            methodConditionStr += TAB_STR_ + TAB_STR_ + "}";

                        }
                        replacableRequestHandlerTmpStr.replace(
                                replacableRequestHandlerTmpStr.find("[%METHOD_CONDITIONS%]"), 21,
                                methodConditionStr);

                        std::string path = outDir_ + "/" + pService->name_.c_str() + "RequestHandler.java";
                        ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableRequestHandlerTmpStr);
                    }
                }

                void
                JavaGenerator::GenerateServiceProxy(::naeem::hottentot::generator::ds::Module *pModule) {
                    ::naeem::hottentot::generator::ds::Service *pService;
                    std::string basePackageName = pModule->package_;
                    for (int i = 0; i < pModule->services_.size(); i++) {
                        std::string replacableServiceProxyStrTmp = serviceProxyTmpStr;
                        pService = pModule->services_.at(i);
                        pService = pModule->services_.at(i);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyStrTmp,"[%BASE_PACKAGE_NAME%]" , basePackageName , 1);
                        ::naeem::hottentot::generator::common::StringHelper::Replace(replacableServiceProxyStrTmp,"[%SERVICE_NAME%]" , pService->name_ , 1);
                        //loop on service methods
                        ::naeem::hottentot::generator::ds::Method *pMethod;
                        std::string methodsStr;
                        for (int i = 0; i < pService->methods_.size(); i++) {
                            pMethod = pService->methods_.at(i);
                            pMethod = pService->methods_.at(i);
                            methodsStr += "public " + pMethod->returnType_ + " " + pMethod->name_ + "(";
                            ::naeem::hottentot::generator::ds::Argument *pArg;
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                methodsStr += pArg->type_ + " " + pArg->variable_;
                                if (i < pMethod->arguments_.size() - 1) {
                                    methodsStr += ",";
                                }
                            }
                            methodsStr += ") { \n";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                methodsStr += TAB_STR_ + TAB_STR_ + "//serialize " + pArg->variable_ + "\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + "byte[] serialized" + pArg->type_ + " = " +
                                              pArg->variable_ + ".serialize();\n";
                            }
                            methodsStr += "\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//make request\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "Request request = new Request();\n";
                            std::stringstream serviceId;
                            serviceId << pService->GetHash();
                            methodsStr += TAB_STR_ + TAB_STR_ + "request.setServiceId(" + serviceId.str() + ");\n";
                            std::stringstream methodId;
                            methodId << pMethod->GetHash();
                            methodsStr += TAB_STR_ + TAB_STR_ + "request.setMethodId(" + methodId.str() + ");\n";
                            std::stringstream argSize;
                            argSize << pMethod->arguments_.size();
                            methodsStr +=
                                    TAB_STR_ + TAB_STR_ + "request.setArgumentCount((byte) " + argSize.str() + ");\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "request.setType(Request.RequestType.";

                            if (pService->serviceType_ == 0) {
                                methodsStr += "InvokeStateless";
                            } else if (pService->serviceType_ == 1) {
                                methodsStr += "InvokeStatefull";
                            }
                            methodsStr += ");\n";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                std::stringstream ssI;
                                pArg = pMethod->arguments_.at(i);
                                ssI << i;
                                methodsStr += TAB_STR_ + TAB_STR_ + "Argument arg" + ssI.str() + " = new Argument();\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + "arg" + ssI.str() + ".setDataLength(" +
                                              pArg->variable_.c_str() + ".serialize().length);\n";
                                methodsStr +=
                                        TAB_STR_ + TAB_STR_ + "arg" + ssI.str() + ".setData(" + pArg->variable_.c_str() +
                                        ".serialize());\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + "request.addArgument(arg" + ssI.str() + ");\n";
                            }
                            //calculate request length
                            methodsStr += TAB_STR_ + TAB_STR_ + "int dataLength = 0;\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//calculate data length for every argument\n";
                            for (int i = 0; i < pMethod->arguments_.size(); i++) {
                                pArg = pMethod->arguments_.at(i);
                                std::string argDataLengthVarName = pArg->variable_ + "DataLength";
                                std::string argDataLengthByteArrayLengthVarName =
                                        pArg->variable_ + "DataLengthByteArrayLength";
                                methodsStr += TAB_STR_ + TAB_STR_ + "//calulate " + argDataLengthVarName + "\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + "int " + argDataLengthVarName + "= serialized" +
                                              pArg->type_ + ".length;\n";
                                methodsStr +=
                                        TAB_STR_ + TAB_STR_ + "int " + argDataLengthByteArrayLengthVarName + " = 1;\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + "if (" + argDataLengthVarName + " >= 0x80) {\n";
                                methodsStr +=
                                        TAB_STR_ + TAB_STR_ + TAB_STR_ + "if (" + argDataLengthVarName + " <= 0xff) {\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "//ex 0x81 0xff\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "" +
                                              argDataLengthByteArrayLengthVarName + " = 2;\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "} else if (" + argDataLengthVarName +
                                              " <= 0xffff) {\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "//ex 0x82 0xff 0xff\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "" +
                                              argDataLengthByteArrayLengthVarName + " = 3;\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "} else if (" + argDataLengthVarName +
                                              " <= 0xffffff) {\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "//ex 0x83 0xff 0xff 0xff\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "" +
                                              argDataLengthByteArrayLengthVarName + " = 4;\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "}\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + "}\n";
                                methodsStr += TAB_STR_ + TAB_STR_ + "dataLength += " + argDataLengthVarName + " + " +
                                              argDataLengthByteArrayLengthVarName + ";\n";
                            }
                            methodsStr += TAB_STR_ + TAB_STR_ + "//\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "request.setLength(4 + dataLength);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//connect to server\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "TcpClient tcpClient = TcpClientFactory.create();\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "try{\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "tcpClient.connect(host, port);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "} catch (TcpClientConnectException e) {\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "throw new HottentotRuntimeException(e);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "}\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//serialize request according to HTNP\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "Protocol protocol = ProtocolFactory.create();\n";
                            methodsStr += TAB_STR_ + TAB_STR_ +
                                          "byte[] serializedRequest = protocol.serializeRequest(request);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//send request\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "try {\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "tcpClient.write(serializedRequest);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "} catch (TcpClientWriteException e) {\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "throw new HottentotRuntimeException(e);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "}\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//read response from server\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "byte[] buffer = new byte[256];\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "while (!protocol.IsResponseComplete()) {\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "byte[] dataChunkRead;\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "try {\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "dataChunkRead = tcpClient.read();\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "} catch (TcpClientReadException e) {\n";
                            methodsStr +=
                                    TAB_STR_ + TAB_STR_ + TAB_STR_ + TAB_STR_ + "throw new HottentotRuntimeException(e);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "}\n";
                            methodsStr +=
                                    TAB_STR_ + TAB_STR_ + TAB_STR_ + "protocol.processDataForResponse(dataChunkRead);\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "}\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//deserialize token part of response\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "Response response = protocol.getResponse();\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//close everything\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "//deserialize " + pMethod->returnType_ +
                                          "part from response\n";
                            std::string lowerCaseReturnType = pMethod->returnType_;
                            lowerCaseReturnType[0] += 32;
                            methodsStr += TAB_STR_ + TAB_STR_ + "" + pMethod->returnType_ + " " + lowerCaseReturnType +
                                          "= null;\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "if (response.getStatusCode() == -1) {\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "//\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "} else {\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "" + lowerCaseReturnType + "= new " +
                                          pMethod->returnType_ + "();\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + TAB_STR_ + "" + lowerCaseReturnType +
                                          ".deserialize(response.getData());\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "}\n";
                            methodsStr += TAB_STR_ + TAB_STR_ + "return " + lowerCaseReturnType + ";\n";
                            methodsStr += TAB_STR_ + "}\n";
                        }
                        replacableServiceProxyStrTmp.replace(replacableServiceProxyStrTmp.find("[%METHODS%]"), 11,
                                                             methodsStr);
                        

                        std::string path = outDir_ + "/" + pService->name_.c_str() + "ServiceProxy.java";
                        ::naeem::hottentot::generator::common::Os::WriteFile(path , replacableServiceProxyStrTmp);
                    }
                }
            }
        }
    }
}
