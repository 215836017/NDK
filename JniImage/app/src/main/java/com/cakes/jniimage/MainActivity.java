package com.cakes.jniimage;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.cakes.jniimage.rotate.RotateImageActivity;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    private Intent intent = new Intent();

    public void mainBtnClick(View view) {
        if (view.getId() == R.id.main_btn_rotate_iamge) {
            intent.setClass(this, RotateImageActivity.class);
        }

        startActivity(intent);
    }
}