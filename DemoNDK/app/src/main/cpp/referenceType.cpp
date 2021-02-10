#include <jni.h>
#include "logUtil.h"

/**
 * 弱全局引用的使用，要防止弱全局引用在使用时被 GC 回收了
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniReferenceType_useWeakGlobalReference(JNIEnv
                                                                   *env,
                                                                   jobject thiz) {
    static jclass stringClass = NULL;
    if (NULL == stringClass) {
        jclass localRefs = env->FindClass("java/lang/String");
        if (NULL == localRefs) {
            LOGE("JniReferenceType_useWeakGlobalReference() -- error: NULL == localRefs");
            return;
        }
        stringClass = (jclass) env->NewWeakGlobalRef(localRefs);
        if (NULL == stringClass) {
            LOGE("JniReferenceType_useWeakGlobalReference() -- error: NULL == stringClass");
            return;
        }
    }

    static jmethodID stringMid = NULL;
    if (NULL == stringMid) {
        stringMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
        if (NULL == stringMid) {
            LOGE("JniReferenceType_useWeakGlobalReference() -- error: NULL == stringMid");
            return;
        }
    }

    jboolean isGC = env->IsSameObject(stringClass, NULL);
    if (isGC) {
        LOGW("weak reference has been gc");
    } else {
        jstring str = (jstring) env->NewObject(stringClass, stringMid,
                                               env->NewStringUTF("jstring"));
        LOGI("JniReferenceType_useWeakGlobalReference() -- str is %s",
             env->GetStringUTFChars(str, NULL));
    }
}

/**
 * 使用局部引用来缓存static的变量，会导致出现野指针的情况
 */
extern "C"
JNIEXPORT jstring
JNICALL
Java_com_cakes_demondk_jni_JniReferenceType_errorCacheUseLocalReference(JNIEnv *env,
                                                                        jobject
                                                                        thiz) {
    static jmethodID mid = NULL;
    static jclass cls;

    // 局部引用不能使用 static 来缓存，否则函数退出后，自动释放，成为野指针，程序 Crash
    if (NULL == cls) {
        cls = env->FindClass("java/lang/String");
        if (NULL == cls) {
            LOGE("JniReferenceType_errorCacheUseLocalReference() -- error: NULL == cls");
            return NULL;
        }
    } else {
        LOGI("cls is not null but program will crash");
    }

    if (NULL == mid) {
        mid = env->GetMethodID(cls, "<init>", "([C)V");
        if (NULL == mid) {
            LOGE("JniReferenceType_errorCacheUseLocalReference() -- error: NULL == mid");
            return NULL;
        }
    }

    jcharArray charArray = env->NewCharArray(10);
    const jchar *j_char = env->GetStringChars(env->NewStringUTF("errorCacheUseLocalReference"),
                                              NULL);
    env->SetCharArrayRegion(charArray, 0, 10, j_char);
    jstring result = (jstring) env->NewObject(cls, mid, charArray);
    env->DeleteLocalRef(charArray);

    return result;
}

/**
 * 使用全局引用来缓存 static 的变量
 */
extern "C"
JNIEXPORT jstring
JNICALL
Java_com_cakes_demondk_jni_JniReferenceType_cacheWithGlobalReference(JNIEnv *env, jobject
thiz) {
    static jclass stringClass = NULL;
    if (NULL == stringClass) {
        jclass localClass = env->FindClass("java/lang/String");
        if (NULL == localClass) {
            LOGE("JniReferenceType_cacheWithGlobalReference() -- error: NULL== localClass");
            return NULL;
        }
        stringClass = (jclass) env->NewGlobalRef(localClass);
        if (NULL == stringClass) {
            LOGE("JniReferenceType_cacheWithGlobalReference() -- error: NULL== stringClass");
            return NULL;
        }
    } else {
        LOGI("JniReferenceType_cacheWithGlobalReference() -- use stringClass cached");
    }

    static jmethodID stringMid = NULL;
    if (NULL == stringMid) {
        stringMid = env->GetMethodID(stringClass, "<init>", "(Ljava/lang/String;)V");
        if (NULL == stringMid) {
            LOGE("JniReferenceType_cacheWithGlobalReference() -- error: NULL== stringMid");
            return NULL;
        }
    } else {
        LOGI("JniReferenceType_cacheWithGlobalReference() -- use stringMid cached");
    }

    jstring str = env->NewStringUTF("test cacheWithGlobalReference");
    return (jstring) env->NewObject(stringClass, stringMid, str);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniReferenceType_useLocalReferenceManageFuntions(JNIEnv
                                                                            *env,
                                                                            jobject thiz
) {
// TODO: implement useLocalReferenceManageFuntions()
}