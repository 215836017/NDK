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
JNIEXPORT jbyte JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniByte(JNIEnv *env, jobject thiz, jbyte b) {
    LOGD("from java, byte is %d", b);
    jbyte result = b + 2;
    return result;
}

extern "C"
JNIEXPORT jchar JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniChar(JNIEnv *env, jobject thiz, jchar ch) {
    LOGD("from java, char is %c", ch);
    jchar result = ch + 2;
    return result;
}

extern "C"
JNIEXPORT jshort JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniShort(JNIEnv *env, jobject thiz, jshort num) {
    LOGD("from java, short is %d", num);
    jshort result = num + 2;
    return result;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniInt(JNIEnv *env, jobject thiz, jint num) {
    LOGD("from java, int is %d", num);
    jint result = num + 2;
    return result;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniLong(JNIEnv *env, jobject thiz, jlong num) {
    LOGD("from java, long is %d", num);
    jlong result = num + 2;
    return result;
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniFloat(JNIEnv *env, jobject thiz, jfloat num) {
    LOGD("from java, float is %f", num);
    jfloat result = num + 2;
    return result;
}

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniDouble(JNIEnv *env, jobject thiz, jdouble num) {
    LOGD("from java, double is %f", num);
    jdouble result = num + 2;
    return result;
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_cakes_demondk_jni_JniBaseType_callJniBoolean(JNIEnv *env, jobject thiz, jboolean b) {
    LOGD("from java, boolean is %d", b);
    jboolean result = !b;
    return result;
}