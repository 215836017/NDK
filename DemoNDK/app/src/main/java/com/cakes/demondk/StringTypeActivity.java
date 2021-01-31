package com.cakes.demondk;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.cakes.demondk.jni.JniStringType;

public class StringTypeActivity extends AppCompatActivity {

    private final String TAG = "StringTypeActivity";

    private JniStringType jniStringType = new JniStringType();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_string_type);

        findViewById(R.id.string_type_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testBaseType();
            }
        });
    }

    private void testBaseType() {

        byte b = 10;
        byte resultByte = jniBaseType.callJniByte(b);
        LogUtil.i(TAG, "testBaseType() -- resultByte = " + resultByte);

        char resultChar = jniBaseType.callJniChar('c');
        LogUtil.d(TAG, "testBaseType() -- resultChar = " + resultChar);

        short num = 2;
        short resultShort = jniBaseType.callJniShort(num);
        LogUtil.w(TAG, "testBaseType() -- resultShort = " + resultShort);

        int resultInt = jniBaseType.callJniInt(4);
        LogUtil.i(TAG, "testBaseType() -- resultInt = " + resultInt);

        long resultLong = jniBaseType.callJniLong(6);
        LogUtil.d(TAG, "testBaseType() -- resultLong = " + resultLong);

        float resultFloat = jniBaseType.callJniFloat(8.0f);
        LogUtil.w(TAG, "testBaseType() -- resultFloat = " + resultFloat);

        double resultDouble = jniBaseType.callJniDouble(0.123);
        LogUtil.i(TAG, "testBaseType() -- resultDouble = " + resultDouble);

        boolean resultBoolean = jniBaseType.callJniBoolean(true);
        LogUtil.d(TAG, "testBaseType() -- resultBoolean = " + resultBoolean);
    }
}