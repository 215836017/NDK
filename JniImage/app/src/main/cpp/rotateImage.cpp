#include <jni.h>
#include <android/bitmap.h>
#include <cstring>

#include "logUtil.h"

jobject getBitmap(JNIEnv *env, uint32_t width, uint32_t height);

extern "C"
JNIEXPORT jobject JNICALL
Java_com_cakes_jniimage_rotate_RotateImageUtil_rotateBitmap(JNIEnv *env, jobject thiz,
                                                            jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

    LOGI("RotateImageUtil_rotateBitmap() -- width = %d", bitmapInfo.width);
    LOGI("RotateImageUtil_rotateBitmap() -- height = %d", bitmapInfo.height);

    void *bitmapPixels;
    AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels);  // 拿到像素内容
    uint32_t newWidth = bitmapInfo.height;
    uint32_t newHeight = bitmapInfo.width;

    LOGI("RotateImageUtil_rotateBitmap() -- 1111111");
    uint32_t *newBitmapPixels = new uint32_t[newWidth * newHeight];

    int index = 0;
    LOGI("RotateImageUtil_rotateBitmap() -- 222222");
    for (int x = newWidth-1; x > 0; --x) {
        for (int y = 0; y < newHeight-1; ++y) {
            uint32_t pixel = ((uint32_t *) bitmapPixels)[index++];
            newBitmapPixels[newWidth * y + x] = pixel;
        }
    }
    LOGI("RotateImageUtil_rotateBitmap() -- 33333333");
    AndroidBitmap_unlockPixels(env, bitmap);

    jobject newBitmap = getBitmap(env, newWidth, newHeight);
    LOGI("RotateImageUtil_rotateBitmap() -- 44444444");
    void *resultBitmapPixels;
    AndroidBitmap_lockPixels(env, newBitmap, &resultBitmapPixels);
    int pixelsCount = newWidth * newHeight;
    memcpy((uint32_t *) resultBitmapPixels, newBitmapPixels, sizeof(uint32_t) * pixelsCount);
    LOGI("RotateImageUtil_rotateBitmap() -- 5555555555555");
    AndroidBitmap_unlockPixels(env, newBitmap);

    delete[] newBitmapPixels;
    return newBitmap;

}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_cakes_jniimage_rotate_RotateImageUtil_convertBitmap(JNIEnv *env, jobject thiz,
                                                             jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;
    int ret;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return NULL;
    }

    // 读取 bitmap 的像素内容到 native 内存
    void *bitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }

    uint32_t newWidth = bitmapInfo.width;
    uint32_t newHeight = bitmapInfo.height;

    uint32_t *newBitmapPixels = new uint32_t[newWidth * newHeight];

    int whereToGet = 0;

    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; x++) {
            uint32_t pixel = ((uint32_t *) bitmapPixels)[whereToGet++];
            newBitmapPixels[newWidth * (newHeight - 1 - y) + x] = pixel;
        }
    }

    jobject newBitmap = getBitmap(env, newWidth, newHeight);

    void *resultBitmapPixels;

    if ((ret = AndroidBitmap_lockPixels(env, newBitmap, &resultBitmapPixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }

    int pixelsCount = newWidth * newHeight;

    memcpy((uint32_t *) resultBitmapPixels, newBitmapPixels, sizeof(uint32_t) * pixelsCount);

    AndroidBitmap_unlockPixels(env, newBitmap);

    delete[] newBitmapPixels;

    return newBitmap;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_com_cakes_jniimage_rotate_RotateImageUtil_mirrorBitmap(JNIEnv *env, jobject thiz,
                                                            jobject bitmap) {
    AndroidBitmapInfo bitmapInfo;

    LOGI("RotateImageUtil_mirrorBitmap() -- width = %d", bitmapInfo.width);
    LOGI("RotateImageUtil_mirrorBitmap() -- height = %d", bitmapInfo.height);

    int ret;
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &bitmapInfo)) < 0) {
        LOGE("RotateImageUtil_mirrorBitmap() error =%d", ret);
        return NULL;
    }

    // 读取 bitmap 的像素内容到 native 内存
    // AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels);  // 拿到像素内容
    void *bitmapPixels;
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &bitmapPixels)) < 0) {
        LOGE("RotateImageUtil_mirrorBitmap() failed ! error=%d", ret);
        return NULL;
    }

    uint32_t newWidth = bitmapInfo.width;
    uint32_t newHeight = bitmapInfo.height;
    uint32_t *newBitmapPixels = new uint32_t[newWidth * newHeight];

    int index = 0;
    for (int y = 0; y < newHeight; y++) {
        for (int x = newWidth - 1; x >= 0; x--) {
            uint32_t pixel = ((uint32_t *) bitmapPixels)[index++];
            newBitmapPixels[newWidth * y + x] = pixel;
        }
    }
    AndroidBitmap_unlockPixels(env, bitmap);

    jobject newBitmap = getBitmap(env, newWidth, newHeight);
    void *resultBitmapPixels;

    if ((ret = AndroidBitmap_lockPixels(env, newBitmap, &resultBitmapPixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return NULL;
    }
    int pixelsCount = newWidth * newHeight;
    memcpy((uint32_t *) resultBitmapPixels, newBitmapPixels, sizeof(uint32_t) * pixelsCount);
    AndroidBitmap_unlockPixels(env, newBitmap);

    delete[] newBitmapPixels;

    return newBitmap;
}

jobject getBitmap(JNIEnv *env, uint32_t width, uint32_t height) {

    jclass bitmapClass = env->FindClass("android/graphics/Bitmap");
    if (NULL == bitmapClass) {
        LOGE("getBitmap() -- error: NULL == bitmapClass");
        return nullptr;
    }

    // 使用AndroidStudio自动生成的方法签名在模拟器上运行会崩溃
//    jmethodID bitmapConstruct = env->GetStaticMethodID(bitmapClass, "createBitmap",
//                                                       "(IILandroid/graphics/Bitmap/Config;)Landroid/graphics/Bitmap;");

    jmethodID bitmapConstruct = env->GetStaticMethodID(bitmapClass,
                                                       "createBitmap",
                                                       "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;");

    jclass bitmapConfigClass = env->FindClass("android/graphics/Bitmap$Config");
    if (NULL == bitmapConfigClass) {
        LOGE("getBitmap() -- error: NULL == bitmapConfigClass");
        return nullptr;
    }
//    jmethodID configMethod = env->GetStaticMethodID(bitmapConfigClass, "valueOf",
//                                                    "(Ljava/lang/String;)Landroid/graphics/Bitmap/Config;");
    jmethodID configMethod = env->GetStaticMethodID(
            bitmapConfigClass, "valueOf",
            "(Ljava/lang/String;)Landroid/graphics/Bitmap$Config;");
    jstring configName = env->NewStringUTF("ARGB_8888");
    jobject objectConfig = env->CallStaticObjectMethod(bitmapConfigClass, configMethod,
                                                       configName);

    jobject objectBitmap = env->CallStaticObjectMethod(bitmapClass, bitmapConstruct, width,
                                                       height,
                                                       objectConfig);

    return objectBitmap;

}