/******************************************************************
 * Generated by Hottentot JAVA Generator
 * Date: 
 * Name: 
 * Description:
 *   
 ******************************************************************/

package ir.ntnaeem.hottentot.examples.listtest.hotgen;

import ir.ntnaeem.hottentot.runtime.Service;
import java.util.List;

public interface ListTestService extends Service {
  void addNames(List<String> names);
  List<String> getNames();
  List<MessageBox> getMessages();
  void addMessage(MessageBox message);
  void addShortNumbers(List<Short> numbers);
  void addByteNumbers(List<Byte> numbers);

}
