package com.csbiu.ap2m5;

import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Serializable;
import java.net.ConnectException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;


/**
 * TCP Client taken from stack overflow (the link in recitation 12 slides) with modifications
 */
public final class TcpClient {

    //Server ip and port
    private String serverIP;
    private int serverPORT;
    // message to send to the server
    private String mServerMessage;
    // sends message received notifications
    private OnMessageReceived mMessageListener = null;
    // while this is true, the server will continue running
    private boolean mRun = false;
    // used to send messages
    private PrintWriter mBufferOut;
    // used to read messages from the server
    private BufferedReader mBufferIn;
    // singleton
    private static TcpClient INSTANCE;
    private Socket socket;

    /**
     * Constructor of the class. OnMessagedReceived listens for the messages received from server
     */
    private TcpClient(String ip, int port, OnMessageReceived listener) {
        this.serverIP = ip;
        this.serverPORT = port;
        mMessageListener = listener;
    }

    /**
     * Create new instance or resetup current instance.
     * @param ip of server.
     * @param port of server.
     * @param listener listener for joystick.
     */
    public static void createInstance(String ip, int port, OnMessageReceived listener) {
        if (INSTANCE == null) {
            INSTANCE = new TcpClient(ip, port, listener);
        } else {
            getInstance().serverIP = ip;
            getInstance().serverPORT = port;
            getInstance().mMessageListener = listener;
        }
    }

    /**
     * Get current instance
     * @return current instance.
     */
    public static TcpClient getInstance() {
        if (INSTANCE == null) {
            throw new RuntimeException("Please run createInstance first");
        }
        return INSTANCE;
    }
    /**
     * Sends the message entered by client to the server
     * @param message text entered by client
     */
    public void sendMessage(String message) {
        if (mBufferOut != null && !mBufferOut.checkError()) {
            mBufferOut.println(message);
            mBufferOut.flush();
        }
    }

    /**
     * Close the connection and release the members
     */
    public void stopClient() {
        Log.d("TCP", "run: Closing connection...");
        sendMessage("quit\r\n");

        mRun = false;

        if (mBufferOut != null) {
            mBufferOut.flush();
            mBufferOut.close();
        }


        if (socket != null) {
            try {
                mBufferIn.close();
                mMessageListener = null;
                mBufferIn = null;
                mBufferOut = null;
                mServerMessage = null;
                socket.close();
            } catch (IOException e) {
                Log.e("TCP", "stopClient: Error stopping client," + e);
            }
            socket = null;
        }
    }

    public void run() {

        mRun = true;

        try {

            Log.d("TCP", "run: Attempting to connect to " + serverIP + ":" + serverPORT);

            InetAddress serverAddr = InetAddress.getByName(serverIP);

            Log.d("TCP", "C: Connecting...");

            //create a socket to make the connection with the server
            if (socket != null) {
                socket.close();
                socket = null;
            }
            socket = new Socket(serverAddr, serverPORT);

            try {

                //sends the message to the server
                mBufferOut = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);

                //receives the message which the server sends back
                mBufferIn = new BufferedReader(new InputStreamReader(socket.getInputStream()));

                //Send back to whoever called run to update the UI.
                mMessageListener.messageReceived("READY");

                while (mRun) {

                    mServerMessage = mBufferIn.readLine();

                    if (mServerMessage != null && mMessageListener != null) {
                        //call the method messageReceived from MyActivity class
                        mMessageListener.messageReceived(mServerMessage);
                    }

                }
                Log.d("TCP", "run: Closing...");

            } catch (Exception e) {
//                Log.e("TCP", "S: Buffer block exception", e);
            }

        }
        //Tell the controller to display the right message.
        catch (UnknownHostException e) {
            mMessageListener.messageReceived("UNKNOWN");
        } catch (ConnectException e){
            mMessageListener.messageReceived("REFUSED");
        } catch (Exception e) {
            Log.e("TCP", "C: Connection error", e);
            mMessageListener.messageReceived("FAILED");
        }

    }

    //Declare the interface. The method messageReceived(String message) will be implemented in the MyActivity
    //class at on asynckTask doInBackground
    public interface OnMessageReceived {
        public void messageReceived(String message);
    }
}