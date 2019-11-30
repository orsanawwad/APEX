package com.csbiu.ap2m5;

import android.content.Intent;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

/**
 * Main entry activity.
 */
public class MainActivity extends AppCompatActivity {

    //Element for ip, port and button
    private EditText ipEditText;
    private EditText portEditText;
    private Button connectButton;
    private Boolean isConnected = false;

    /**
     * Entry point.
     * @param savedInstanceState
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //Find views
        setContentView(R.layout.activity_main);
        ipEditText = findViewById(R.id.ip_edittext);
        portEditText = findViewById(R.id.port_edittext);
        connectButton = findViewById(R.id.connect_button);
        connectButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Set to false to prevent connection spamming
                ipEditText.setEnabled(false);
                portEditText.setEnabled(false);
                connectButton.setEnabled(false);
                //Connect asynchronously, note there are 2 different apis depends on which
                //sdk is defined
                if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
                    new ConnectTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,
                            ipEditText.getText().toString(),
                            portEditText.getText().toString());
                else
                    new ConnectTask().execute(
                            ipEditText.getText().toString(),
                            portEditText.getText().toString());

            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        //Set back to false after destroying JoyStickActivity
        this.isConnected = false;
    }

    /**
     * Connection task asynchronously.
     */
    public class ConnectTask extends AsyncTask<String, String, Void> {

        /**
         * Connect to server in background.
         * @param message message[0] ip, message[1] port
         * @return nothing.
         */
        @Override
        protected Void doInBackground(String... message) {

            TcpClient.createInstance(message[0], Integer.parseInt(message[1]),
                    new TcpClient.OnMessageReceived() {
                        //Set a callback function to receive messages back from
                        //TCPCLient and change the UI as per status or start new activity
                        @Override
                        public void messageReceived(String message) {
                            publishProgress(message);
                        }
                    });
            TcpClient.getInstance().run();

            return null;
        }

        /**
         * Update view on status change.
         * @param values [READY,REFUSED,UNKNOWN,FAILED]
         */
        @Override
        protected void onProgressUpdate(String... values) {
            super.onProgressUpdate(values);
            ipEditText.setEnabled(true);
            portEditText.setEnabled(true);
            connectButton.setEnabled(true);
            //If connection succeeded start new activity.
            if(values[0].equals("READY") && !isConnected) {
                isConnected = true;
                Intent myIntent = new Intent(MainActivity.this, JoyStickActivity.class);
                MainActivity.this.startActivity(myIntent);
            }
            //Otherwise display an error dialog with a message.
            else if (values[0].equals("REFUSED")) {
                new AlertDialog.Builder(MainActivity.this)
                        .setTitle("Connection refused.")
                        .setMessage("Please check your port number or if the server is running.")
                        .setPositiveButton(android.R.string.ok, null)
                        .show();
            } else if (values[0].equals("UNKNOWN")) {
                new AlertDialog.Builder(MainActivity.this)
                        .setTitle("Unknown host.")
                        .setMessage("Please check your IP input.")
                        .setPositiveButton(android.R.string.ok, null)
                        .show();
            } else if (values[0].equals("FAILED")) {
                new AlertDialog.Builder(MainActivity.this)
                        .setTitle("Could not connect to server.")
                        .setMessage("Please check your input settings or network settings and try again.")
                        .setPositiveButton(android.R.string.ok, null)
                        .show();
            }
        }
    }
}
