package ir.ntnaeem.hottentot.runtime.protocol;


import ir.ntnaeem.hottentot.runtime.Argument;
import ir.ntnaeem.hottentot.runtime.Request;
import ir.ntnaeem.hottentot.runtime.RequestCallback;
import ir.ntnaeem.hottentot.runtime.Response;
import ir.ntnaeem.hottentot.runtime.ResponseCallback;

import java.io.IOException;
import java.lang.reflect.Array;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.List;

import static java.lang.Math.pow;


public class ProtocolV1 implements Protocol {

    public class RequestProcessor{
        private short currentState = 0;
        private int lStateCounter = 0;
        private int dStateCounter = 0;
        private int lStateLength = 0;
        private int dataLength;
        private byte[] data;


        public void resetStates() {
            currentState = 0;
            lStateCounter = 0;
            dStateCounter = 0;
            lStateLength = 0;
            dataLength = 0;
        }

        public void process(byte[] dataChunk) {
            for (byte b : dataChunk) {
                if (currentState == 0) {
                    if ((b & 0x80) == 0) {
                        dataLength = b;
                        data = new byte[dataLength];
                        currentState = 2;
                    } else {
                        lStateLength = b & 0x0f;
                        currentState = 1;
                    }
                } else if (currentState == 2) {
                    if (dStateCounter < dataLength - 1) {
                        data[dStateCounter++] = b;
                    } else {
                        data[dStateCounter] = b;
                        //TODO use logger
                        System.out.println("request has been read ... ");
                        System.out.println("request data : " +Arrays.toString(data));
                        //
                        Response response = requestCallback.onRequest(deserializeRequestBody(data));

                        try {
                            responseCallback.onResponse(serializeResponse(response));
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                        //reset states
                        resetStates();

                    }
                } else if (currentState == 1) {
                    if (lStateCounter < lStateLength) {
                        if (b < 0) {
                            dataLength += pow(256, (lStateLength - lStateCounter - 1)) * (b + 256);
                        } else {
                            dataLength += pow(256, (lStateLength - lStateCounter - 1)) * b;
                        }
                    } else {
                        currentState = 2;
                        data[dStateCounter++] = b;
                    }
                }
            }
        }
    }

    public class ResponseProcessor {

        private short currentState = 0;
        private int lStateCounter = 0;
        private int dStateCounter = 0;
        private int lStateLength = 0;
        private int dataLength;
        private byte[] data;

        public void resetStates() {
            currentState = 0;
            lStateCounter = 0;
            dStateCounter = 0;
            lStateLength = 0;
            dataLength = 0;
        }

        public void process(byte[] dataChunk) {
            System.out.println("data chunk : "+Arrays.toString(dataChunk));
            for (byte b : dataChunk) {
                if (currentState == 0) {
                    if ((b & 0x80) == 0) {
                        dataLength = b;
                        data = new byte[dataLength];
                        currentState = 2;
                    } else {
                        lStateLength = b & 0x0f;
                        currentState = 1;
                    }
                } else if (currentState == 2) {
                    if (dStateCounter < dataLength - 1) {
                        data[dStateCounter++] = b;
                    } else {
                        data[dStateCounter] = b;
                        //TODO use logger
                        response = deserializeResponseBody(data);
                        isResponseComplete = true;
                        //reset states
                        resetStates();
                    }
                } else if (currentState == 1) {
                    if (lStateCounter < lStateLength) {
                        if (b < 0) {
                            dataLength += pow(256, (lStateLength - lStateCounter - 1)) * (b + 256);
                        } else {
                            dataLength += pow(256, (lStateLength - lStateCounter - 1)) * b;
                        }
                    } else {
                        currentState = 2;
                        data[dStateCounter++] = b;
                    }
                }
            }
        }
    }

    private RequestCallback requestCallback;
    private ResponseCallback responseCallback;
    private Response response;
    private boolean isResponseComplete = false;

    private RequestProcessor requestProcessor;
    private ResponseProcessor responseProcessor;

    public ProtocolV1() {
        requestProcessor = new RequestProcessor();
        responseProcessor = new ResponseProcessor();
    }


    private byte[] getByteArrayFromIntegerDataLength(int dataLength) {
        byte[] byteArray;
        if (dataLength >= 0x80) {
            if (dataLength <= 0xff) {
                //ex 0x81 0xff
                byteArray = new byte[2];
                byteArray[0] = (byte) 0x81;
                byteArray[1] = (byte) dataLength;
            } else if (dataLength <= 0xffff) {
                //ex 0x82 0xff 0xff
                byteArray = new byte[3];
                byteArray[0] = (byte) 0x82;
                byte[] byteBuffer = ByteBuffer.allocate(2).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
            } else if (dataLength <= 0xffffff) {
                //ex 0x83 0xff 0xff 0xff
                byteArray = new byte[4];
                byteArray[0] = (byte) 0x83;
                byte[] byteBuffer = ByteBuffer.allocate(3).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
                byteArray[3] = byteBuffer[2];
            } else {
                //ex 0x84 0xff 0xff 0xff 0xff
                byteArray = new byte[5];
                byteArray[0] = (byte) 0x84;
                byte[] byteBuffer = ByteBuffer.allocate(4).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
                byteArray[3] = byteBuffer[2];
                byteArray[4] = byteBuffer[3];
            }
        } else {
            //ex 0x7f
            byteArray = new byte[1];
            byteArray[0] = (byte) dataLength;
        }
        return byteArray;
    }

    public byte[] serializeRequest(Request request) {
        //tested ! :)
        int counter = 0;
        byte[] byteArrayFromSerializedRequestLength = getByteArrayFromIntegerDataLength(request.getLength());
        byte[] serializedRequest = new byte[request.getLength() + byteArrayFromSerializedRequestLength.length];
        for (byte b : byteArrayFromSerializedRequestLength) {
            serializedRequest[counter++] = b;
        }
        serializedRequest[counter++] = request.getServiceId();
        serializedRequest[counter++] = request.getMethodId();
        if (request.getType().equals(Request.RequestType.Unknown)) {
            serializedRequest[counter++] = 1;
        } else if (request.getType().equals(Request.RequestType.InvokeStatefull)) {
            serializedRequest[counter++] = 2;
        } else if (request.getType().equals(Request.RequestType.InvokeStateless)) {
            serializedRequest[counter++] = 3;
        } else if (request.getType().equals(Request.RequestType.ServiceListQuery)) {
            serializedRequest[counter++] = 4;
        }


        serializedRequest[counter++] = request.getArgumentCount();
        List<Argument> args = request.getArgs();

        for (Argument arg : args) {
            byte[] byteArrayFromArgLength = getByteArrayFromIntegerDataLength(arg.getDataLength());
            for (byte b : byteArrayFromArgLength) {
                serializedRequest[counter++] = b;
            }
            System.out.println(counter);
            for (byte b : arg.getData()) {
                serializedRequest[counter++] = b;
            }
        }
        System.out.println("s request : " + Arrays.toString(serializedRequest));
        return serializedRequest;
    }

    public Request deserializeRequestBody(byte[] serializedRequestBody) {
        //tested :)
        int counter = 0;
        Request request = new Request();
//        byte firstByte = serializedRequest[0];
//        if (((int) firstByte & 0x80) == 0) {
//            request.setLength(serializedRequest[0]);
//            counter++;
//        } else {
//            int numOfByteForLength = (int) firstByte & 0x0f;
//            int requestLength = 0;
//            for (int i = numOfByteForLength; i > 0; i--) {
//                counter++;
//                requestLength += (int) pow(256, (numOfByteForLength - 1)) * serializedRequest[i];
//            }
//            request.setLength(requestLength);
//        }
        System.out.println(Arrays.toString(serializedRequestBody));
        request.setLength(serializedRequestBody.length);
        request.setServiceId(serializedRequestBody[counter++]);
        request.setMethodId(serializedRequestBody[counter++]);
        if (serializedRequestBody[counter] == 1) {
            request.setType(Request.RequestType.Unknown);
        } else if (serializedRequestBody[counter] == 2) {
            request.setType(Request.RequestType.InvokeStatefull);
        } else if (serializedRequestBody[counter] == 3) {
            request.setType(Request.RequestType.InvokeStateless);
        } else if (serializedRequestBody[counter] == 4) {
            request.setType(Request.RequestType.ServiceListQuery);
        }
        counter++;
        request.setArgumentCount(serializedRequestBody[counter++]);
        System.out.println(counter);
        //make arguments
        byte firstByte;
        while (counter < serializedRequestBody.length) {
            Argument arg = new Argument();
            firstByte = serializedRequestBody[counter];
            if (((int) firstByte & 0x80) == 0) {
                int dataLength = serializedRequestBody[counter];
                arg.setDataLength(serializedRequestBody[counter]);
                counter++;
                //fill data
                byte[] data = new byte[dataLength];
                for(int i = 0 ; i < dataLength ; i++){
                    data[i] = serializedRequestBody[counter++];
                }
                arg.setData(data);
            } else {
                int numOfByteForLength = (int) firstByte & 0x0f;
                int dataLength = 0;
                counter++;
                for (int i = numOfByteForLength; i > 0; i--) {
                    counter++;
                    dataLength += (int) pow(256, (numOfByteForLength - 1)) * serializedRequestBody[i];
                }
                arg.setDataLength(dataLength);
                //fill data
                byte[] data = new byte[dataLength];
                for(int i = 0 ; i < dataLength ; i++){

                    data[i] = serializedRequestBody[counter++];
                }
                arg.setData(data);
            }
            request.addArgument(arg);
        }
        return request;
    }

    public Response deserializeResponseBody(byte[] serializedResponseBody) {
        //tested :)
        int counter = 0;
        Response response = new Response();
//        byte firstByte = serializedResponse[0];
//        if (((int) firstByte & 0x80) == 0) {
//            response.setLength(serializedResponse[0]);
//            counter++;
//        } else {
//            int numOfByteForLength = (int) firstByte & 0x0f;
//            int responseLength = 0;
//            for (int i = numOfByteForLength; i > 0; i--) {
//                counter++;
//                responseLength += (int) pow(256, (numOfByteForLength - 1)) * serializedResponse[i];
//            }
//            response.setLength(responseLength);
//        }
        response.setLength(serializedResponseBody.length);
        response.setStatusCode(serializedResponseBody[counter++]);
        byte[] data = new byte[response.getLength() - 1 ];
        for(int i = 0 ; counter < serializedResponseBody.length ; i++){

            data[i] = serializedResponseBody[counter++];
        }
        response.setData(data);
        return response;
    }

    public byte[] serializeResponse(Response response) {
        //tested ! :)
        int counter = 0;
        System.out.println(response);
        byte[] byteArrayFromSerializedResponseLength = getByteArrayFromIntegerDataLength(response.getLength());
        byte[] serializedResponse = new byte[response.getLength() + byteArrayFromSerializedResponseLength.length];
        for (byte b : byteArrayFromSerializedResponseLength) {
            serializedResponse[counter++] = b;
        }
        serializedResponse[counter++] = response.getStatusCode();
        for (byte b : response.getData()) {
            serializedResponse[counter++] = b;
        }
        return serializedResponse;
    }


    public void setResponseCallback(ResponseCallback responseCallback) {
        this.responseCallback = responseCallback;
    }

    public void processDataForRequest(byte[] dataChunk) {
        System.out.println(Arrays.toString(dataChunk));
        requestProcessor.process(dataChunk);
    }

    public void processDataForResponse(byte[] dataChunk) {
        responseProcessor.process(dataChunk);
    }

    public boolean IsResponseComplete() {
        return isResponseComplete;
    }

    public Response getResponse() {
        //TODO
        return response;
    }

    public void setRequestCallback(RequestCallback requestCallback) {
        this.requestCallback = requestCallback;
    }


}
