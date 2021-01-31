#include <jni.h>
#include <string>
#include<android/log.h>

#define TAG "Jni_log" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


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