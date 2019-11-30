package com.csbiu.ap2m5;

import android.content.Intent;
import android.graphics.Color;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

/**
 * JoyStick activity, the controller that will hold a JoyStick view and update the
 * server.
 */
public class JoyStickActivity extends AppCompatActivity {

    private TcpClient mTcpClient;
    private JoyStickView mJoyStickView;

    /**
     * Joystick controller entry point.
     */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_joystick);
        //Get current tcp instance
        mTcpClient = TcpClient.getInstance();
        mJoyStickView = findViewById(R.id.joystick_view);
        //Set listener to listen to joystick moves.
        mJoyStickView.setOnJoyStickMoveListener(new JoyStickView.OnJoyStickMoveListener() {
            @Override
            public void OnJoyStickMove(double aileron, double elevator) {
                //The (elevator * -1) here is to invert the controller since that's how we're used
                //to in videogames, pull down to fly, pull up to bring the nose down.
                if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
                    new SendMessageTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR,
                            "set /controls/flight/aileron " + aileron + "\r\n" +
                                    "set /controls/flight/elevator " + (elevator * -1) + "\r\n");
                } else {
                    new SendMessageTask().execute(
                            "set /controls/flight/aileron " + aileron + "\r\n" +
                                    "set /controls/flight/elevator " + (elevator * -1) + "\r\n");
                }
                Log.d("JoyStickActivity", "OnJoyStickMove: " + aileron + ", " + elevator);
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();
    }

    /**
     * In case something else destroyed the activity.
     */
    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            new DisconnectTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
        } else {
            new DisconnectTask().execute();
        }
    }

    /**
     * Send message through tcp back to server using background threads.
     */
    public class SendMessageTask extends AsyncTask<String, Void, Void> {

        @Override
        protected Void doInBackground(String... message) {
            Log.d("JoyStickActivity", "onPostExecute: POSTING");
            mTcpClient.sendMessage(message[0]);
            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid) {
            Log.d("JoyStickActivity", "onPostExecute: POSTED");
        }
    }

    /**
     * Disconnect from server task.
     */
    public class DisconnectTask extends AsyncTask<Void, Void, Void> {

        @Override
        protected Void doInBackground(Void... voids) {

            // disconnect
            mTcpClient.stopClient();
            mTcpClient = null;

            return null;
        }

        @Override
        protected void onPostExecute(Void nothing) {
            super.onPostExecute(nothing);
        }
    }
}
