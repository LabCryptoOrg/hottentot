/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   
 ******************************************************************/
package ir.ntnaeem.hottentot.examples.test_all;

public class TestServiceProxyBuilder {

  public static TestService create(String host, int port) {
    return new TestServiceProxy(host,port);
  }

  public static void destroy() {
    //TODO
  }
}
