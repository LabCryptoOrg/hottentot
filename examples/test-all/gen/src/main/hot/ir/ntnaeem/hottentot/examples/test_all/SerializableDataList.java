/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date:
 * Name:
 * Description:
 ******************************************************************/
package ir.ntnaeem.hottentot.examples.test_all;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.labcrypto.hottentot.*;
import org.labcrypto.hottentot.helper.DataLengthByteArrayMaker;
import org.labcrypto.hottentot.helper.ByteArrayToInteger;


public class SerializableDataList {

  private List<byte[]> dataList;

  public SerializableDataList() {
    dataList = new ArrayList<byte[]>();
  }

  public List<byte[]> getDataList() {
    return dataList;
  }

  public void setDataList(List<byte[]> dataList) {
    this.dataList = dataList;
  }

  public byte[] serialize() {
    if (dataList.size() != 0) {
      int counter = 0;
      int dataLength = 0;
      //calculate serializeddataListLength
      for (byte[] data : dataList) {
        _Data _Data = new _Data( data );
        byte[] serializedData = _Data.serialize();
        byte[] dataLengthByteArray =
          DataLengthByteArrayMaker.getByteArray(serializedData.length);
        dataLength += dataLengthByteArray.length + serializedData.length;
      }
      byte[] serializedDataList = new byte[dataLength];
      for (byte[] data : dataList) {
        _Data _Data = new _Data( data );
        byte[] serializedData = _Data.serialize();
        int serializedDataLength = serializedData.length;
        byte[] dataLengthByteArray =
          DataLengthByteArrayMaker.getByteArray(serializedDataLength);
        System.arraycopy(dataLengthByteArray, 0, serializedDataList, counter, dataLengthByteArray.length);
        counter += dataLengthByteArray.length;
        System.arraycopy(serializedData, 0, serializedDataList, counter, serializedData.length);
        counter += serializedData.length;
      }
      return serializedDataList;
    }
    return new byte[0];
  }

  public byte[] serializeWithLength() {
    byte[] serializedBytes = serialize();
    byte[] dataLengthInBytes = DataLengthByteArrayMaker.getByteArray(serializedBytes.length);
    byte[] output = new byte[serializedBytes.length + dataLengthInBytes.length];
    int c = 0;
    for(int i = 0 ; i < dataLengthInBytes.length ; i++){
      output[c++] = dataLengthInBytes[i];
    }
    for(int i = 0 ; i < serializedBytes.length ; i++){
      output[c++] = serializedBytes[i];
    }
    return output;
  }

  public void deserialize(byte[] serializedDataList) {
    if(serializedDataList.length != 0){
      int counter = 0;
      int serializedDataByteArrayLength = 0 ;
      while (true) {
        if (counter == serializedDataList.length) {
          break;
        }
        int firstLengthByte = serializedDataList[counter];
        int numOfByteForLength = 1;
        if ((firstLengthByte & 0x80) == 0) {
          serializedDataByteArrayLength = serializedDataList[counter];
        } else {
          counter++;
          numOfByteForLength = firstLengthByte & 0x0f;
          byte[] serializedDataLengthByteArray = new byte[numOfByteForLength];
          int serializedDataWrapperLengthByteArrayCounter = 0;
          for (int i = counter; i < counter + numOfByteForLength; i++) {
            serializedDataLengthByteArray[serializedDataWrapperLengthByteArrayCounter++] = serializedDataList[i];
          }
          serializedDataByteArrayLength = ByteArrayToInteger.getInt(serializedDataLengthByteArray);
        }
        counter += numOfByteForLength;
        byte[] dataByteArray = new byte[serializedDataByteArrayLength];
        int dataByteArrayCounter = 0;
        for (int i = counter; i < counter + serializedDataByteArrayLength; i++) {
          dataByteArray[dataByteArrayCounter++] = serializedDataList[i];
        }
        counter += serializedDataByteArrayLength;
        _Data _Data = new _Data();
        _Data.deserialize(dataByteArray);
        dataList.add(_Data.getValue());
      }
    }
  }
}