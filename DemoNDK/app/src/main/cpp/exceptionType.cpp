#include <jni.h>
#include "logUtil.h"
#include "common.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniExceptionType_doit(JNIEnv *env, jobject thiz) {

    jclass exceptionClass = env->FindClass("com/cakes/demondk/jni/JniExceptionType");
    if (nullptr == exceptionClass) {
        LOGE("JniExceptionType_doit() -- error: nullptr == exceptionClass");
        return;
    }
    jmethodID initMid = env->GetMethodID(exceptionClass, "<init>", "()V");
    if (nullptr == initMid) {
        LOGE("JniExceptionType_doit() -- error: nullptr == initMid");
        return;
    }

    jobject obj = env->NewObject(exceptionClass, initMid);
    if (nullptr == obj) {
        LOGE("JniExceptionType_doit() -- error: nullptr == obj");
        return;
    }

    jmethodID callbackMid = env->GetMethodID(exceptionClass, "callback", "()V");
    if (nullptr == callbackMid) {
        LOGE("JniExceptionType_doit() -- error: nullptr == callbackMid");
        return;
    }

    env->CallVoidMethod(obj, callbackMid);
    jthrowable throwable = env->ExceptionOccurred();
    if (throwable) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        jclass newExCls = env->FindClass("java/lang/IllegalAccessException");
        if (NULL == newExCls) {
            LOGW("JniExceptionType_doit() -- error: nullptr == newExCls");
            return;
        }
        env->ThrowNew(newExCls, "Thrown from C++ code");
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniExceptionType_nativeThrowException(JNIEnv *env, jobject thiz) {
    throwByName(env, "java/lang/IllegalArgumentException", "native throw exception");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniExceptionType_nativeInvokeJavaException(JNIEnv *env, jobject thiz) {

    jclass exceptionClass = env->FindClass("com/cakes/demondk/jni/JniExceptionType");
    jmethodID initMid = env->GetMethodID(exceptionClass, "<init>", "()V");
    jobject obj = env->NewObject(exceptionClass, initMid);

    jmethodID operateMid = env->GetMethodID(exceptionClass, "operation", "()I");
    env->CallIntMethod(obj, operateMid);

    jthrowable exc = env->ExceptionOccurred();
//    jboolean  result = env->ExceptionCheck();

    if (exc) {
        env->ExceptionDescribe();
        // 这才是关键不让应用崩溃的代码
        env->ExceptionClear();
        // 发生异常了要记得释放资源
        env->DeleteLocalRef(exceptionClass);
        env->DeleteLocalRef(obj);
    }
}