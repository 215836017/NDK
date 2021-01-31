package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.jni.JniArrayType;

public class ArrayTypeActivity extends AppCompatActivity {

    private final String TAG = "ArrayTypeActivity";

    private JniArrayType jniArrayType = new JniArrayType();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_array_type);

        findViewById(R.id.array_type_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testArrayType();
            }
        });
    }

    private void testArrayType() {

    }
}