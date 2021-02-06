#include <jni.h>
#include <pthread.h>
#include <bits/pthread_types.h>

#include "logUtil.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniCallbakcType_nativeCallback(JNIEnv *env, jobject thiz,
                                                          jobject callback_method) {
    // todo 申明 interface 和 class 的方式是相同的
    jclass jcls = env->GetObjectClass(callback_method);
    if (NULL == jcls) {
        LOGE("JniCallbakcType_nativeCallback() -- error: NULL == jcls");
        return;
    }

    jmethodID methodId = env->GetMethodID(jcls, "callbackMethod", "()V");
    if (NULL == methodId) {
        LOGE("JniCallbakcType_nativeCallback() -- error: NULL == methodId");
        return;
    }

    env->CallVoidMethod(callback_method, methodId);

}

static jobject threadObject;
static jclass threadClass;
static jmethodID threadMethod;

void *threadCallback(void *) {

}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniCallbakcType_nativeThreadCallback(JNIEnv *env, jobject thiz,
                                                                jobject thread_callback) {

    LOGI("JniCallbakcType_nativeThreadCallback() -- 11111111111 TODO: 线程内容待学习...");
//    env->NewGlobalRef(thread_callback);
//    threadClass = env->GetObjectClass(thread_callback);
//    if (NULL == threadClass) {
//        LOGE("JniCallbakcType_nativeThreadCallback() -- error: NULL == threadClass");
//        return;
//    }
//    threadMethod = env->GetMethodID(threadClass, "threadCallback", "()V");
//
//    pthread_t handle;
//    pthread_create(&handle, nullptr, threadCallback, nullptr);
}