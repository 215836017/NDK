package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.bean.Dog;
import com.cakes.demondk.jni.JniFiledType;

public class FiledTypeActivity extends AppCompatActivity {

    private final String TAG = "FiledTypeActivity";

    private JniFiledType jniFiledType = new JniFiledType();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_filed_type);

        findViewById(R.id.filed_type_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testFiledType();
            }
        });
    }

    private void testFiledType() {
        Dog dog = new Dog("daHuang");

        LogUtil.i(TAG, "testFiledType() -- 11111111111");
        jniFiledType.accessInstanceFiled(dog);
        LogUtil.d(TAG, "testFiledType() -- after jniFiledType.accessInstanceFiled(), dog.name = "
                + dog.getName());

        LogUtil.i(TAG, "testFiledType() -- 222222222");
        jniFiledType.accessStaticField(dog);
        LogUtil.d(TAG, "testFiledType() -- after jniFiledType.accessStaticField(), dog.age = "
                + Dog.age);

    }

}