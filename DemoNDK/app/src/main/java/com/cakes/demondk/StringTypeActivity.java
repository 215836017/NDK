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
                testStringType();
            }
        });
    }

    private void testStringType() {

        String result1 = jniStringType.getAndReleaseString("hello String");
        LogUtil.d(TAG, "testBaseType() -- result1 = " + result1);

        String result2 = jniStringType.reverseString("aaa_bbb");
        LogUtil.i(TAG, "testBaseType() -- result2 = " + result2);

        String result3 = jniStringType.getHalfString("a123456b");
        LogUtil.w(TAG, "testBaseType() -- result3 = " + result3);
    }
}