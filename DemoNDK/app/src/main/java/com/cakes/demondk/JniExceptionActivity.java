package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.jni.JniExceptionType;

public class JniExceptionActivity extends AppCompatActivity {

    private final String TAG = "JniExceptionActivity";
    private JniExceptionType jniExceptionType = new JniExceptionType();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_exception);

        findViewById(R.id.jni_exception_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testJniException();
            }
        });
    }

    private void testJniException() {
        try {
            jniExceptionType.doit();
        } catch (IllegalArgumentException e) {
            LogUtil.e(TAG, "testJniException() -- error: " + e.getMessage());
        }

        jniExceptionType.nativeThrowException();

        jniExceptionType.nativeInvokeJavaException();
    }
}