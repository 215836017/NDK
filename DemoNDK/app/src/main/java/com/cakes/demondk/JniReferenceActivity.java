package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.jni.JniReferenceType;

public class JniReferenceActivity extends AppCompatActivity {

    private final String TAG = "JniReferenceActivity";

    private JniReferenceType jniReferenceType = new JniReferenceType();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_reference);

        findViewById(R.id.jni_reference_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testJniReference();
            }
        });
    }

    private void testJniReference() {
        LogUtil.i(TAG, "testJniReference() -- 11111111");
        jniReferenceType.useWeakGlobalReference();

        // 多次点击测试按钮后就会崩溃
        LogUtil.d(TAG, "testJniReference() -- 22222");
        String result = jniReferenceType.errorCacheUseLocalReference();
        LogUtil.d(TAG, "testJniReference() -- 22222, result = " + result);

        LogUtil.w(TAG, "testJniReference() -- 3333333333");
        // 全局引用
        String result1 = jniReferenceType.cacheWithGlobalReference();
        LogUtil.w(TAG, "testJniReference() -- 3333333333, result1 = " + result1);

        LogUtil.i(TAG, "testJniReference() -- 444444444");
        jniReferenceType.useLocalReferenceManageFuntions();
    }
}