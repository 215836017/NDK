package com.cakes.jniimage.rotate;

import android.graphics.Bitmap;

public class RotateImageUtil {

    static {
        System.loadLibrary("rotateImage");
    }

    /*** 顺时针旋转 90° 的操作 */
    public native Bitmap rotateBitmap(Bitmap bitmap);

    public native Bitmap convertBitmap(Bitmap bitmap);

    public native Bitmap mirrorBitmap(Bitmap bitmap);

}
