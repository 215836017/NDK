package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.jni.JniOnLoadType;

public class JniOnLoadActivity extends AppCompatActivity {

    private final String TAG = "JniOnLoadActivity";
    private JniOnLoadType jniOnLoadType = new JniOnLoadType();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_jni_on_load);

        findViewById(R.id.jni_on_Load_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testJniOnLoad();
            }
        });
    }


    private void testJniOnLoad() {

        LogUtil.i(TAG, "testJniOnLoad() -- 1111111");
        String message = jniOnLoadType.getMessage();
        LogUtil.i(TAG, "testJniOnLoad() -- 1111111, message = " + message);

        LogUtil.w(TAG, "testJniOnLoad() -- 22222222222");
        int plus = jniOnLoadType.plus(10, 20);
        LogUtil.w(TAG, "testJniOnLoad() -- 22222222222, result = " + plus);
    }
}