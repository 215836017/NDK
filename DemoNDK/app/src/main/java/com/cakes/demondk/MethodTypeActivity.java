package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.bean.Cat;
import com.cakes.demondk.jni.JniMethodType;

public class MethodTypeActivity extends AppCompatActivity {

    private final String TAG = "MethodTypeActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_method_type);

        findViewById(R.id.method_type_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testMethodType();
            }
        });
    }

    private void testMethodType() {
        Cat cat = new Cat();

        LogUtil.d(TAG, "testMethodType() -- 111111");
        JniMethodType.callInstanceMethod(cat);

        LogUtil.d(TAG, "testMethodType() -- 22222");
        JniMethodType.callStaticMethod(cat);
    }
}