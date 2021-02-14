package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.jni.JniThreadType;

public class JniThreadActivity extends AppCompatActivity {

    private final String TAG = "JniThreadActivity";

    private JniThreadType jniThreadType = new JniThreadType();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_thread);

        findViewById(R.id.jni_thread_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testJniThread();
            }
        });
    }

    private void testJniThread() {
        LogUtil.i(TAG, "testJniThread() -- 1111111");
        jniThreadType.createNativeThread();
        LogUtil.i(TAG, "testJniThread() -- 1111111  end end ");

        LogUtil.w(TAG, "testJniThread() -- 222222");
        jniThreadType.nativeInit();
        LogUtil.w(TAG, "testJniThread() -- 222222  end end ");

        LogUtil.d(TAG, "testJniThread() -- 33333");
        jniThreadType.posixThreads(3, 4);
        LogUtil.d(TAG, "testJniThread() -- 33333  end end ");
    }
}