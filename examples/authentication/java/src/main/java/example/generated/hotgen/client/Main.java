/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   
 ******************************************************************/
package example.generated.hotgen.client;

import example.generated.hotgen.AuthenticationService;
import example.generated.hotgen.AuthenticationServiceProxyBuilder;

import java.io.IOException;

public class Main {
  public static void main(String[] args) throws IOException {
    ir.ntnaeem.hottentot.runtime.config.Config.setMainArgs(args);
    final AuthenticationService proxy = AuthenticationServiceProxyBuilder.create("127.0.0.1", 2000);

  }
}