package com.cakes.jniimage.rotate;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;

import com.cakes.jniimage.R;

public class RotateImageActivity extends AppCompatActivity {

    private final String TAG = "RotateImageActivity";
    private ImageView imageView;

    private RotateImageUtil rotateImageUtil;
    private Bitmap sourceImage;
    private Bitmap resultImage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rotate_image);

        imageView = findViewById(R.id.image_act_image);
        rotateImageUtil = new RotateImageUtil();
//        sourceImage = ((BitmapDrawable) imageView.getDrawable()).getBitmap();
        sourceImage = BitmapFactory.decodeResource(getResources(), R.drawable.a0);
    }

    public void imageBtnClick(View view) {
        if (view.getId() == R.id.image_act_btn_rotate_90) {
            resultImage = rotateImageUtil.rotateBitmap(sourceImage);
            imageView.setImageBitmap(resultImage);

        } else if (view.getId() == R.id.image_act_btn_convert) {
            resultImage = rotateImageUtil.convertBitmap(sourceImage);
            imageView.setImageBitmap(resultImage);

        } else if (view.getId() == R.id.image_act_btn_mirror) {
            resultImage = rotateImageUtil.mirrorBitmap(sourceImage);
            imageView.setImageBitmap(resultImage);
        }

    }
}