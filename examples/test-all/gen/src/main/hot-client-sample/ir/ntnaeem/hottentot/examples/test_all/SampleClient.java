/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   
 ******************************************************************/
package ir.ntnaeem.hottentot.examples.test_all;

import java.io.IOException;

import ir.ntnaeem.hottentot.examples.test_all.TestService;
import ir.ntnaeem.hottentot.examples.test_all.TestServiceProxyBuilder;



public class SampleClient {
  public static void main(String[] args) throws IOException {
    org.labcrypto.hottentot.runtime.config.Config.setMainArgs(args);
    final TestService testProxy = TestServiceProxyBuilder.create("127.0.0.1", 8080);

    //use server methods on proxies
  }
}