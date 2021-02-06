package com.cakes.demondk;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

import com.cakes.demondk.bean.Animal;
import com.cakes.demondk.jni.JniConstructType;

public class ConstructTypeActivity extends AppCompatActivity {

    private final String TAG = "ConstructTypeActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_construct_type);

        findViewById(R.id.construct_type_button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testConstructType();
            }
        });
    }

    private void testConstructType() {

        LogUtil.i(TAG, "testConstructType() -- 1111111");
        String result = JniConstructType.invokeStringConstructors();
        LogUtil.i(TAG, "testConstructType() -- 1111111 result = " + result);

        LogUtil.i(TAG, "testConstructType() -- 222222");
        Animal animal = JniConstructType.invokeAnimalConstructors();
        LogUtil.i(TAG, "testConstructType() -- 222222, animal.getName() = " + animal.getName());

        LogUtil.w(TAG, "testConstructType() -- 3333333333");
        Animal animal1 = JniConstructType.allocObjectConstructor();
        LogUtil.w(TAG, "testConstructType() -- 3333, animal1.getName() = " + animal1.getName());

        LogUtil.e(TAG, "testConstructType() -- 4444444");
        JniConstructType.callSuperMethod();
        LogUtil.e(TAG, "testConstructType() -- 4444444 - end end ");
    }
}