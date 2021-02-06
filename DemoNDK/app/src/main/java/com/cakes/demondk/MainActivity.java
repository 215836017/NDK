package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    private Intent intent = new Intent();

    public void mainBtnClick(View view) {
        switch (view.getId()) {
            case R.id.base_type:
                intent.setClass(this, BaseTypeActivity.class);
                break;

            case R.id.string_type:
                intent.setClass(this, StringTypeActivity.class);
                break;

            case R.id.array_type:
                intent.setClass(this, ArrayTypeActivity.class);
                break;

            case R.id.filed_type:
                intent.setClass(this, FiledTypeActivity.class);
                break;

            case R.id.method_type:
                intent.setClass(this, MethodTypeActivity.class);
                break;

            case R.id.construct_type:
                intent.setClass(this, ConstructTypeActivity.class);
                break;

            case R.id.jni_onLoad_type:
                intent.setClass(this, JniOnLoadActivity.class);
                break;

            case R.id.jni_callback_type:
                intent.setClass(this, JniCallbackActivity.class);
                break;
        }

        startActivity(intent);
    }
}