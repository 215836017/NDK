
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
    }

    public void threadActBtnClick(View view) {
        if (view.getId() == R.id.jni_thread_button_create) {
            LogUtil.i(TAG, "testJniThread() -- 1111111");
            jniThreadType.createNativeThread();
            LogUtil.i(TAG, "testJniThread() -- 1111111  end end ");

        } else if (view.getId() == R.id.jni_thread_button_create_2) {
            LogUtil.w(TAG, "testJniThread() -- 222222");
            jniThreadType.createNativeThreadWithArgs();
            LogUtil.w(TAG, "testJniThread() -- 222222  end end ");

        } else if (view.getId() == R.id.jni_thread_button_run) {
            LogUtil.w(TAG, "testJniThread() -- 33333");
            jniThreadType.testNativeThreadJoin();
            LogUtil.w(TAG, "testJniThread() -- 33333  end end ");

        } else if (view.getId() == R.id.jni_thread_button_wait) {
            LogUtil.w(TAG, "testJniThread() -- 4444");
            jniThreadType.waitNativeThread();
            LogUtil.w(TAG, "testJniThread() -- 4444  end end ");

        } else if (view.getId() == R.id.jni_thread_button_notify) {
            LogUtil.w(TAG, "testJniThread() -- 55555");
            jniThreadType.notifyNativeThread();
            LogUtil.w(TAG, "testJniThread() -- 55555  end end ");

        } else if (view.getId() == R.id.jni_thread_button_demo) {
            LogUtil.w(TAG, "testJniThread() -- 66666");
            jniThreadType.produceAndConsumeThread();
            LogUtil.w(TAG, "testJniThread() -- 6666666  end end ");
        }
    }

}