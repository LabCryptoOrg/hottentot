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
 
#ifndef _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_H_
#define _ORG_LABCRYPTO_HOTTENTOT_RUNTIME_PROXY__DEFAULT_TCP_CLIENT_H_

#include "tcp_client.h"


namespace org {
namespace labcrypto {
namespace hottentot {
namespace runtime {
namespace proxy {
  class DefaultTcpClient : public TcpClient {
  public:
    DefaultTcpClient(std::string /* Host */,
                     uint32_t    /* Port */);
    virtual ~DefaultTcpClient();
  public:
    virtual bool Connect();
    virtual void Write(unsigned char *         /* data */,
                       uint32_t                /* Length */);
    virtual uint32_t Read(unsigned char *          /* Buffer */,
                          uint32_t                 /* Buffer length */);
    virtual void Close();
    virtual int GetRemoteSocketFD() {
      return socketFD_;
    }
  private:
    int socketFD_;
  };
}
}
}
}
}

#endif