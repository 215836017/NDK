#include <jni.h>
#include "logUtil.h"


// 测试JNI_OnLoad()方法，就不需要Java完整路径方法名的写法了
//extern "C"
//JNIEXPORT jstring JNICALL
//Java_com_cakes_demondk_jni_JniOnLoadType_getMessage(JNIEnv *env, jobject thiz) {
//    // TODO: implement getMessage()
//}
//
//extern "C"
//JNIEXPORT jint JNICALL
//Java_com_cakes_demondk_jni_JniOnLoadType_plus(JNIEnv *env, jobject thiz, jint x, jint y) {
//    // TODO: implement plus()
//}

#define JAVA_CLASS "com/cakes/demondk/jni/JniOnLoadType"
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

jstring getMessage(JNIEnv *env, jobject thiz);

jint nativePlus(JNIEnv *env, jobject thiz, jint x, jint y);

static JNINativeMethod gMethods[] = {
        {"getMessage", "()Ljava/lang/String;", (void *) getMessage},
        {"plus",       "(II)I",                (void *) nativePlus}
};

jstring getMessage(JNIEnv *env, jobject thiz) {

    return env->NewStringUTF("this msg from C++");
}


jint nativePlus(JNIEnv *env, jobject thiz, jint x, jint y) {
    return x + y;
}

int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *nativeMethod,
                          int methodNum) {
    jclass jcls;
    jcls = env->FindClass(className);
    if (NULL == jcls) {
        LOGE("registerNativeMethods() --  error: NULL == jcls");
        return JNI_FALSE;
    }
    if (env->RegisterNatives(jcls, nativeMethod, methodNum) < 0) {
        LOGE("registerNativeMethods() --  error: RegisterNatives < 0");
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

// 和threadType.cpp中的JNI_OnLoad()编译时会冲突，故这里注释掉
//JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
//    LOGI("JNI_OnLoad() -- start 1111");
//
//    JNIEnv *env;
//    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
//        return JNI_ERR;
//    }
//
//    int result = registerNativeMethods(env, JAVA_CLASS, gMethods, NELEM(gMethods));
//
//    if (result == JNI_TRUE) {
//        return JNI_VERSION_1_6;
//    }
//
//    return result;
//}

JNIEXPORT void JNI_OnUnload(JavaVM *vm, void *reserved) {
    LOGI("JNI_OnUnload() -- start 1111");
}



