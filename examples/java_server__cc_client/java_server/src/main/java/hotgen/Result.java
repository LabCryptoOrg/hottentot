/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   This file contains definition of an abstract service class.
 ******************************************************************/
package hotgen;

import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.ByteArrayToInteger;

public class Result {
  private byte statusCode;
  public void setStatusCode(byte statusCode) {
    this.statusCode = statusCode;
  }
  public byte getStatusCode() {
    return statusCode;
  }
  @Override 
  public String toString() { 
    return "Result{" + 
      "statusCode = '" + statusCode + '\'' + 
      "}"; 
  }
	
  public byte[] serialize() {
    byte[] serializedStatusCode = PDTSerializer.getInt8(statusCode);
    byte[] output = new byte[serializedStatusCode.length];
    int counter = 0;
    //use a loop for every property
    for (int i = 0; i < serializedStatusCode.length; i++) {
      output[counter++] = serializedStatusCode[i];
    }
    return output;
  }
    
  public void deserialize(byte[] serializedByteArray) {
    if(serializedByteArray.length != 0){
      int counter = 0;
    int dataLength = 0;
    int numbersOfBytesForDataLength;
    //do for every property
    //statusCode : byte
    byte[] statusCodeByteArray = new byte[1];
    for(int i = 0 ; i < 1 ; i++){
      statusCodeByteArray[i] = serializedByteArray[counter++];
    }
    setStatusCode(PDTDeserializer.getInt8(statusCodeByteArray));

    }
  }
}