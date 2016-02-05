/******************************************************************
 * Generated by Hottentot CC Generator
 * Date: 05-02-2016 09:05:02
 * Name: user.cc
 * Description:
 *   This file contains implementation of User class.
 ******************************************************************/

#include <iostream>
#include <string.h>

#include <naeem/hottentot/runtime/hot_ptr.h>

#include "user.h"


namespace naeem {
namespace hottentot {
namespace examples {
namespace auth {
  unsigned char *
  User::Serialize(uint32_t *length_ptr) {
    uint32_t totalLength = 0;
    uint32_t length0 = 0;
    ::naeem::hottentot::runtime::HotPtr<unsigned char, true> ptr0 = 
      name_.Serialize(&length0);
    if (length0 < 128) {
      totalLength += 1 + length0;
    } else if (length0 < 256) {
      totalLength += 2 + length0;
    } else if (length0 < 256 * 256) {
      totalLength += 3 + length0;
    } else if (length0 < 256 * 256 * 256) {
      totalLength += 3 + length0;
    }
    uint32_t length1 = 0;
    ::naeem::hottentot::runtime::HotPtr<unsigned char, true> ptr1 = 
      family_.Serialize(&length1);
    if (length1 < 128) {
      totalLength += 1 + length1;
    } else if (length1 < 256) {
      totalLength += 2 + length1;
    } else if (length1 < 256 * 256) {
      totalLength += 3 + length1;
    } else if (length1 < 256 * 256 * 256) {
      totalLength += 3 + length1;
    }
    uint32_t length2 = 0;
    ::naeem::hottentot::runtime::HotPtr<unsigned char, true> ptr2 = 
      age_.Serialize(&length2);
    totalLength += length2;
    unsigned char *data = new unsigned char[totalLength];
    uint32_t c = 0;
    if (length0 < 128) {
      data[c] = length0;
      c += 1;
    } else if (length0 < 256) {
      data[c] = 0x81;
      data[c + 1] = length0;
      c += 2;
    } else if (length0 < 256 * 256) {
      data[c] = 0x82;
      data[c + 1] = length0 / 256;
      data[c + 2] = length0 % 256;
      c += 3;
    } else if (length0 < 256 * 256 * 256) {
      data[c] = 0x83;
      data[c + 1] = length0 / (256 * 256);
      data[c + 2] = (length0 - data[c + 1] * (256 * 256)) / 256;
      data[c + 3] = length0 % (256 * 256);
      c += 4;
    }
    unsigned char *data0 = ptr0.Get();
    for (uint32_t i = 0; i < length0; i++) {
      data[c++] = data0[i];
    }
    if (length1 < 128) {
      data[c] = length1;
      c += 1;
    } else if (length1 < 256) {
      data[c] = 0x81;
      data[c + 1] = length1;
      c += 2;
    } else if (length1 < 256 * 256) {
      data[c] = 0x82;
      data[c + 1] = length1 / 256;
      data[c + 2] = length1 % 256;
      c += 3;
    } else if (length1 < 256 * 256 * 256) {
      data[c] = 0x83;
      data[c + 1] = length1 / (256 * 256);
      data[c + 2] = (length1 - data[c + 1] * (256 * 256)) / 256;
      data[c + 3] = length1 % (256 * 256);
      c += 4;
    }
    unsigned char *data1 = ptr1.Get();
    for (uint32_t i = 0; i < length1; i++) {
      data[c++] = data1[i];
    }
    unsigned char *data2 = ptr2.Get();
    for (uint32_t i = 0; i < length2; i++) {
      data[c++] = data2[i];
    }
    if (c != totalLength) {
      std::cout << "Struct Serialization: Inconsistency in length of serialized byte array." << std::endl;
      exit(1);
    };
    if (length_ptr) {
      *length_ptr = totalLength;
    }
    return data;
  }
  void
  User::Deserialize(unsigned char *data, uint32_t length) {
    uint32_t c = 0, elength = 0;
    if ((data[c] & 0x80) == 0) {
      elength = data[c];
      c++;
    } else {
      uint8_t ll = data[c] & 0x0f;
      c++;
      if (ll == 1) {
        elength = data[c];
        c += 1;
      } else if (ll == 2) {
        elength = data[c] * 256 + data[c + 1];
        c += 2;
      } else if (ll == 3) {
        elength = data[c] * 256 * 256 + data[c + 1] * 256 + data[c + 2];
        c += 3;
      }
    }
    name_.Deserialize(data + c, elength);
    c += elength;
    if ((data[c] & 0x80) == 0) {
      elength = data[c];
      c++;
    } else {
      uint8_t ll = data[c] & 0x0f;
      c++;
      if (ll == 1) {
        elength = data[c];
        c += 1;
      } else if (ll == 2) {
        elength = data[c] * 256 + data[c + 1];
        c += 2;
      } else if (ll == 3) {
        elength = data[c] * 256 * 256 + data[c + 1] * 256 + data[c + 2];
        c += 3;
      }
    }
    family_.Deserialize(data + c, elength);
    c += elength;
    age_.Deserialize(data + c, 1);
    c += 1;
    if (c != length) {
      std::cout << "Struct Deserialization: Inconsistency in length of deserialized byte array." << std::endl;
      exit(1);
    };
  }
} // END OF NAMESPACE auth
} // END OF NAMESPACE examples
} // END OF NAMESPACE hottentot
} // END OF NAMESPACE naeem