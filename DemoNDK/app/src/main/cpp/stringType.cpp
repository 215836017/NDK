#include <jni.h>
#include <string>

#include "logUtil.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cakes_demondk_jni_JniStringType_getAndReleaseString(JNIEnv *env, jobject thiz,
                                                             jstring name) {
    const char *str = env->GetStringUTFChars(name, 0);
    LOGD("from java, str is %s", str);
    env->ReleaseStringUTFChars(name, str);

    const char *result = "this string is from C";
    return env->NewStringUTF(result);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cakes_demondk_jni_JniStringType_reverseString(JNIEnv *env, jobject thiz, jstring name) {
    const char *str = env->GetStringUTFChars(name, 0);
    LOGI("from java, str is %s", str);

    int length = env->GetStringLength(name);
    char reverseString[length];
    for (int i = 0; i < length; ++i) {
        reverseString[i] = str[length - 1 - i];
    }
    env->ReleaseStringUTFChars(name, str);

    return env->NewStringUTF(reverseString);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cakes_demondk_jni_JniStringType_getHalfString(JNIEnv *env, jobject thiz, jstring name) {
    const char *str = env->GetStringUTFChars(name, 0);
    LOGW("from java, str is %s", str);

    int len = env->GetStringLength(name);
    jchar outputBuf[len / 2];
    // 截取一部分内容放到缓冲区里面去
    env->GetStringRegion(name, 0, len / 2, outputBuf);

    // 再从缓冲区中得到 Java 字符串
    jstring result = env->NewString(outputBuf, len / 2);
    return result;
}