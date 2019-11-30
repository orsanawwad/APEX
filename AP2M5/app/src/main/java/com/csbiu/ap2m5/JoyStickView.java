package com.csbiu.ap2m5;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.View;

/**
 * Joystick module.
 */
public class JoyStickView extends View {

    //Listener to update movement.
    private OnJoyStickMoveListener jCallback;

    private Paint jPaintCircle;
    private Paint jPaintCircleButton;

    //Center point
    private int jCenterX;
    private int jCenterY;

    //Current point of joystick
    private int jCurrentX;
    private int jCurrentY;

    //Joystick holder radius
    private int jCircleRadius;
    //Joystick button radius.
    private int jCircleRadiusButton;

    //The interface to implement on usage.
    public interface OnJoyStickMoveListener {
        void OnJoyStickMove(double aileron, double elevator);
    }

    public JoyStickView(Context context) {
        super(context);
    }

    public JoyStickView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);

        //Setup painters.
        jPaintCircle = new Paint();
        jPaintCircle.setAntiAlias(true);
        jPaintCircle.setColor(Color.parseColor("#0D47A1"));
        jPaintCircle.setStyle(Paint.Style.FILL);

        jPaintCircleButton = new Paint();
        jPaintCircleButton.setAntiAlias(true);
        jPaintCircleButton.setColor(Color.BLACK);
        jPaintCircleButton.setStyle(Paint.Style.FILL);
    }

    public JoyStickView(Context context, @Nullable AttributeSet attrs,
                        int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public JoyStickView(Context context, @Nullable AttributeSet attrs,
                        int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }


    //Draw two circles
    @Override
    protected void onDraw(Canvas canvas) {
        // Draw the background
        canvas.drawCircle(jCenterX, jCenterY, jCircleRadius, jPaintCircle);

        // Draw the circle border
        canvas.drawCircle(jCurrentX, jCurrentY, jCircleRadiusButton, jPaintCircleButton);
    }

    //Called after rotations.
    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        setupPosition();
        jCircleRadius = w/2 - 120;
        jCircleRadiusButton = 100;
    }

    //Occurs when a screen touch/drag happens
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        //Get current point
        jCurrentX = (int) event.getX();
        jCurrentY = (int) event.getY();

        //If user stops using the screen, reset to center.
        if (event.getAction() == MotionEvent.ACTION_UP) {
            resetToCenter();
        }

        //Get current radius from center.
        double abs = Math.sqrt(Math.pow(jCurrentX - jCenterX, 2)
                + Math.pow(jCurrentY - jCenterY, 2));

        int padding = 20; //To achieve perfect normalizing
        //Check if the radius goes above joystick holder radius, if so bring it back to place
        if (abs > jCircleRadius + padding) {
            jCurrentX = (int) ((jCurrentX - jCenterX) * (jCircleRadius + padding) / abs + jCenterX);
            jCurrentY = (int) ((jCurrentY - jCenterY) * (jCircleRadius + padding)  / abs + jCenterY);
        }

        //Update client about movement.
        if (jCallback != null)
            jCallback.OnJoyStickMove(getNormalizedX(), getNormalizedY());

        //Redraw screen
        invalidate();

        return true;
    }

    //Setup center.
    private void setupPosition() {
        // get the center of view to position circle
        jCenterX = jCurrentX = getWidth() / 2;
        jCenterY = jCurrentY = getWidth() / 2;
    }

    //Reset to center
    public void resetToCenter() {
        jCurrentX = jCenterX;
        jCurrentY = jCenterY;
    }

    //Normalize current X position to (-1,1) range
    public double getNormalizedX() {
        double value = Math.round((jCurrentX-jCircleRadiusButton)*100.0f/(getWidth()-jCircleRadiusButton*2));
        return (value*2 - 100)/100;
    }

    //Normalize current Y position to (-1,1) range
    public double getNormalizedY() {
        double value = Math.round((jCurrentY-jCircleRadiusButton)*100.0f/(getHeight()-jCircleRadiusButton*2));
        return (value*2 - 100)/100;
    }

    //Joystick listener setting.
    public void setOnJoyStickMoveListener(OnJoyStickMoveListener jCallback) {
        this.jCallback = jCallback;
    }
}