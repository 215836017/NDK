
#include <jni.h>
#include <pthread.h>
#include "logUtil.h"

#ifndef DEMONDK_THREADTYPE_H
#define DEMONDK_THREADTYPE_H

struct ThreadRunArgs {
    jint id;
    jint result;
};

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_createNativeThread(JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_createNativeThreadWithArgs(JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_testNativeThreadJoin(JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_nativeInit(JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_nativeFree(JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_posixThreads(JNIEnv *, jobject, jint, jint);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_waitNativeThread(JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_notifyNativeThread(JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_produceAndConsumeThread(JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif

#endif //DEMONDK_THREADTYPE_H
