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
 
#ifndef _NAEEM_HOTTENTOT_RUNTIME_PROXY__TCP_CLIENT_H_
#define _NAEEM_HOTTENTOT_RUNTIME_PROXY__TCP_CLIENT_H_

#include <stdint.h>
#include <string>


namespace naeem {
  namespace hottentot {
    namespace runtime {
      namespace proxy {
        class TcpClient {
        public:
          TcpClient(std::string host,
                    uint32_t port)
            : host_(host),
              port_(port) {
          }
          virtual ~TcpClient() {}
        public:
          virtual bool Connect() = 0;
          virtual void Write(unsigned char *         /* data */,
                             uint32_t                /* Length */) = 0;
          virtual uint32_t Read(unsigned char *      /* Buffer */,
                                uint32_t             /* Buffer length */) = 0;
          virtual void Close() = 0;
          virtual int GetRemoteSocketFD() = 0;
        protected:
          std::string host_;
          uint16_t port_;
        };
      }
    }
  }
}

#endif