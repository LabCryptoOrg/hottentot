/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   
 ******************************************************************/
package example.generated.hotgen;

import ir.ntnaeem.hottentot.runtime.RequestHandler;

public abstract class AbstractSecondService implements SecondService {	
  public RequestHandler makeRequestHandler() {
    return new SecondRequestHandler(this);
  }
  public long getServiceId() {
    return 1595637521L;
  }
}
