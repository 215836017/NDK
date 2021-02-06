package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.jni.JniCallbakcType;
import com.cakes.demondk.model.ICallbackMethod;
import com.cakes.demondk.model.IThreadCallback;

public class JniCallbackActivity extends AppCompatActivity {

    private final String TAG = "JniCallbackActivity";

    private JniCallbakcType jniCallbakcType = new JniCallbakcType();

    private ICallbackMethod callBack = new ICallbackMethod() {

        @Override
        public void callbackMethod() {
            LogUtil.i(TAG, "ICallbackMethod() -- 111111111");
        }
    };

    private IThreadCallback threadCallback = new IThreadCallback() {
        @Override
        public void threadCallback() {
            LogUtil.w(TAG, "IThreadCallback() -- 111111111");
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_callback);

        findViewById(R.id.jni_callback_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testJniCallback();
            }
        });
    }

    private void testJniCallback() {
        LogUtil.i(TAG, "testJniCallback() -- 11111111");
        jniCallbakcType.nativeCallback(callBack);

        LogUtil.w(TAG, "testJniCallback() -- 2222222222222222");
        jniCallbakcType.nativeThreadCallback(threadCallback);
    }
}