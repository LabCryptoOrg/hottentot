
/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   
 ******************************************************************/
package example.generated;

import ir.ntnaeem.hottentot.serializerHelper.DataLengthByteArrayMaker;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.List;

public class SerializableTokenList {

  private List<Token> tokenList;

  public SerializableTokenList() {
    tokenList = new ArrayList<Token>();
  }

  public List<Token> getTokenList() {
    return tokenList;
  }

  public void setTokenList(List<Token> tokenList) {
    this.tokenList = tokenList;
  }

  public byte[] serialize() {
    if (tokenList.size() != 0) {
      int serializedTokenLength = tokenList.get(0).serialize().length;
      byte[] tokenLengthByteArray = 
      DataLengthByteArrayMaker.getByteArray(serializedTokenLength);
      byte[] serializedTokenList = new byte[tokenLengthByteArray.length + serializedTokenLength * tokenList.size()];
      System.arraycopy(tokenLengthByteArray, 0, serializedTokenList, 0, tokenLengthByteArray.length);
      int counter = tokenLengthByteArray.length ;
      for (Token token : tokenList) {
        byte[] serializedToken = token.serialize();
        System.arraycopy(serializedToken, 0, serializedTokenList, counter, serializedToken.length);
        counter += serializedToken.length;
      }
      return serializedTokenList;
    }
    return new byte[0];
  }

  public void deserialize(byte[] serializedtokenList) {

    if (serializedtokenList.length != 0) {

      int firstByte = serializedtokenList[0];
      int serializedtokenLength;
      int numOfByteForLength = 1;
      if ((firstByte & 0x80) == 0) {
        serializedtokenLength = serializedtokenList[0];
      } else {
        numOfByteForLength = firstByte & 0x0f;
        byte[] serializedtokenLengthByteArray = new byte[numOfByteForLength];
        for (int i = 1; i <= numOfByteForLength; i++) {
          serializedtokenLengthByteArray[i - 1] = serializedtokenList[i];
        }
        serializedtokenLength = ByteBuffer.wrap(serializedtokenLengthByteArray).getInt();
      }
      //
      int counter = numOfByteForLength;
      byte[] tokenByteArray;
      while(true){
        if(counter == serializedtokenList.length){
          break;
        }
        tokenByteArray = new byte[serializedtokenLength];
        int tokenByteArrayCounter = 0;
        for(int i = counter ; i < counter + serializedtokenLength ; i++){
          tokenByteArray[tokenByteArrayCounter++] = serializedtokenList[i];
        }
        counter += serializedtokenLength;
        Token token = new Token();
        token.deserialize(tokenByteArray);
        tokenList.add(token);
      }
    }
  }
}