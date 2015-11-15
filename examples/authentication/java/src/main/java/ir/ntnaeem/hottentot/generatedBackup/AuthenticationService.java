//package ir.ntnaeem.hottentot.generated;
package ir.ntnaeem.hottentot.generatedBackup;

import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import ir.ntnaeem.hottentot.runtime.Service;

public interface AuthenticationService extends Service{
    Token authenticate(Credential credential) throws TcpClientConnectException, TcpClientWriteException, TcpClientReadException, Exception;
}
