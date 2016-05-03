/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   This file contains definition of an abstract service class.
 ******************************************************************/
package ir.ntnaeem.hottentot.examples.listtest.hotgen;

import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;
import ir.ntnaeem.hottentot.serializerHelper.PDTDeserializer;
import ir.ntnaeem.hottentot.serializerHelper.ByteArrayToInteger;
import java.util.List;
import java.util.ArrayList;

public class ReportEntry {
  private long date1;
  private String title = "";
  private String body = "";
  public void setDate1(long date1) {
    this.date1 = date1;
  }
  public long getDate1() {
    return date1;
  }
  public void setTitle(String title) {
    this.title = title;
  }
  public String getTitle() {
    return title;
  }
  public void setBody(String body) {
    this.body = body;
  }
  public String getBody() {
    return body;
  }
  @Override 
  public String toString() { 
    return "ReportEntry{" + 
      "date1 = '" + date1 + '\'' + 
      ",title = '" + title + '\'' + 
      ",body = '" + body + '\'' + 
      "}"; 
  }
	
  public byte[] serialize() {
    byte[] serializedDate1 = PDTSerializer.getInt64(date1);
    byte[] serializedTitle = PDTSerializer.getString(title);
    byte[] serializedBody = PDTSerializer.getString(body);
    byte[] output = new byte[serializedDate1.length + serializedTitle.length + serializedBody.length];
    int counter = 0;
    //use a loop for every property
    for (int i = 0; i < serializedDate1.length; i++) {
      output[counter++] = serializedDate1[i];
    }
    for (int i = 0; i < serializedTitle.length; i++) {
      output[counter++] = serializedTitle[i];
    }
    for (int i = 0; i < serializedBody.length; i++) {
      output[counter++] = serializedBody[i];
    }
    return output;
  }
    
  public void deserialize(byte[] serializedByteArray) {
    if(serializedByteArray.length != 0){
      int counter = 0;
      int dataLength = 0;
      int numbersOfBytesForDataLength;
      //do for every property
    //date1 : long
    byte[] date1ByteArray = new byte[8];
    for(int i = 0 ; i < 8 ; i++){
      date1ByteArray[i] = serializedByteArray[counter++];
    }
    setDate1(PDTDeserializer.getInt64(date1ByteArray));
    //title : String
    dataLength = 0;
    if(( serializedByteArray[counter] & 0x80) == 0 ) {
      dataLength = serializedByteArray[counter++];
    }else{
      numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;
      byte[] serializedByteArrayLength = new byte[numbersOfBytesForDataLength];
      for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
        serializedByteArrayLength[i] = serializedByteArray[counter++];
      }
      dataLength = ByteArrayToInteger.getInt(serializedByteArrayLength);
    }
    byte[] titleByteArray = new byte[dataLength];
    System.arraycopy(serializedByteArray,counter,titleByteArray,0,dataLength);
    counter += dataLength;
    setTitle(PDTDeserializer.getString(titleByteArray));
    //body : String
    dataLength = 0;
    if(( serializedByteArray[counter] & 0x80) == 0 ) {
      dataLength = serializedByteArray[counter++];
    }else{
      numbersOfBytesForDataLength = serializedByteArray[counter++] & 0x0f;
      byte[] serializedByteArrayLength = new byte[numbersOfBytesForDataLength];
      for(byte i = 0 ; i < numbersOfBytesForDataLength ; i++){
        serializedByteArrayLength[i] = serializedByteArray[counter++];
      }
      dataLength = ByteArrayToInteger.getInt(serializedByteArrayLength);
    }
    byte[] bodyByteArray = new byte[dataLength];
    System.arraycopy(serializedByteArray,counter,bodyByteArray,0,dataLength);
    counter += dataLength;
    setBody(PDTDeserializer.getString(bodyByteArray));

    }
  }
}