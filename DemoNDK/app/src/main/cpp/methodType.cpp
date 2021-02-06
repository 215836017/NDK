#include <jni.h>
#include <stdio.h>

#include "logUtil.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniMethodType_callInstanceMethod(JNIEnv *env, jclass clazz,
                                                            jobject cat) {
    jclass classCat = env->GetObjectClass(cat);
    if (NULL == classCat) {
        LOGW("JniMethodType_callInstanceMethod() -- error: NULL == classCat");
        return;
    }

    // 1. 调用不带参数的实例方法
    jmethodID jmethodIdVoid = env->GetMethodID(classCat, "callInstanceVoidMethod", "()V");
    if (NULL == jmethodIdVoid) {
        LOGW("JniMethodType_callInstanceMethod() -- error: NULL == jmethodIdVoid");
        return;
    }
    env->CallVoidMethod(cat, jmethodIdVoid);

    // 2. 调用入参的实例方法
    jmethodID jmethodId = env->GetMethodID(classCat, "callInstanceMethod", "(I)V");
    if (NULL == jmethodId) {
        LOGW("JniMethodType_callInstanceMethod() -- error: NULL == jmethodId");
        return;
    }
    env->CallVoidMethod(cat, jmethodId, 10);

    // 3. 调用入参且有返回值的方法
    jmethodID jmethodIdInt = env->GetMethodID(classCat, "callInstanceIntMethod", "(I)I");
    if (NULL == jmethodIdInt) {
        LOGW("JniMethodType_callInstanceMethod() -- error: NULL == jmethodIdInt");
        return;
    }
    jint result = env->CallIntMethod(cat, jmethodIdInt, 20);
    LOGD("JniMethodType_callInstanceMethod() -- result = %d", result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniMethodType_callStaticMethod(JNIEnv *env, jclass clazz,
                                                          jobject cat) {

    // 1. 调用Java中不带参数的静态方法
    jclass classCat = env->GetObjectClass(cat);
    if (NULL == classCat) {
        LOGW("JniMethodType_callStaticMethod() -- error: NULL == classCat");
        return;
    }
    jmethodID jmethodIdVoid = env->GetStaticMethodID(classCat, "callStaticVoidMethod", "()V");
    if (NULL == jmethodIdVoid) {
        LOGW("JniMethodType_callStaticMethod() -- error: NULL == jmethodIdVoid");
        return;
    }
    env->CallStaticVoidMethod(classCat, jmethodIdVoid);

    // 2. 调用Java中带一个参数的静态方法
    jmethodID jmethodId1 = env->GetStaticMethodID(classCat, "callStaticMethod",
                                                  "(Ljava/lang/String;)Ljava/lang/String;");
    if (NULL == jmethodId1) {
        LOGW("JniMethodType_callStaticMethod() -- error: NULL == jmethodId1");
        return;
    }
    jstring jStr = env->NewStringUTF("test call java method");
    jstring result = (jstring) env->CallStaticObjectMethod(classCat, jmethodId1, jStr);
    const char *strResult = env->GetStringUTFChars(result, NULL);
    LOGI("JniMethodType_callStaticMethod() -- call result = %s", strResult);

    // 3. 调用Java中带有数组参数的静态方法
    jmethodID jmethodId2 = env->GetStaticMethodID(classCat, "callStaticMethod",
                                                  "([Ljava/lang/String;I)Ljava/lang/String;");
    if (NULL == jmethodId2) {
        LOGW("JniMethodType_callStaticMethod() -- error: NULL == jmethodId2");
        return;
    }

    jobjectArray stringArrays;
    jclass strClass = env->FindClass("java/lang/String");
    if (NULL == strClass) {
        LOGW("JniMethodType_callStaticMethod() -- error: NULL == jmethodId2");
        return;
    }
    int arrayLen = 3;
    stringArrays = env->NewObjectArray(arrayLen, strClass, 0);
    if (NULL == stringArrays) {
        LOGW("JniMethodType_callStaticMethod() -- error: NULL == stringArrays");
        return;
    }

    jstring itemValue;
    for (int i = 0; i < arrayLen; i++) {
        itemValue = env->NewStringUTF("itemValue in C - " + i);
        env->SetObjectArrayElement(stringArrays, i, itemValue);
    }
    env->CallStaticObjectMethod(classCat, jmethodId2, stringArrays, 300);
}