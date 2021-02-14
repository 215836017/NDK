#include <stdio.h>
#include "common.h"
#include "threadType.h"

static JavaVM *gVm = NULL;
static const char *runtimeException = "java/lang/RuntimeException";

static jobject gObj = NULL;
static jmethodID printNativeMsg;
static jmethodID printThreadName;
static pthread_mutex_t mutex;

void *printThreadHello(void *);

void *run(void *);

JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    gVm = vm;

    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_createNativeThread(JNIEnv *env, jobject thiz) {
    pthread_t handler;
    int result = pthread_create(&handler, NULL, printThreadHello, NULL);
    if (0 != result) {
        LOGD("JniThreadType_createNativeThread() -- create thread failed");
    } else {
        LOGD("JniThreadType_createNativeThread() -- create thread success");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_nativeInit(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeInit()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_nativeFree(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeFree()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_posixThreads(JNIEnv *env, jobject thiz, jint num,
                                                      jint iterations) {
    pthread_t *handlers = new pthread_t[num];
    for (int i = 0; i < num; i++) {
        pthread_t thread;
        ThreadRunArgs *threadRunArgs = new ThreadRunArgs;
        threadRunArgs->id = i;
        threadRunArgs->result = i * i;

        // 创建一个线程
        int result = pthread_create(&handlers[i], NULL, run, (void *) threadRunArgs);
        if (0 != result) {
            throwByName(env, runtimeException, "unable to create thread");
        }
    }

    for (int i = 0; i < num; i++) {
        void *result = NULL;
        if (pthread_join(handlers[i], &result) != 0) {
            throwByName(env, runtimeException, "Unable to join thread");
        } else {
            LOGD("return value is %d", result);
            char message[26];
            sprintf(message, "Worker %d returned %d", i, result);
            jstring msg = env->NewStringUTF(message);
            env->CallVoidMethod(gObj, printNativeMsg, msg);
            if (env->ExceptionOccurred() != NULL) {
                return;
            }
        }
    }
}

void *printThreadHello(void *) {
    LOGD("hello thread");
    return NULL;
}

/**
 * 相当于 Thread 的 run 方法
 * @param args
 * @return
 */
void *run(void *args) {

    JNIEnv *env = NULL;
    // 将当前线程添加到 Java 虚拟机上
    ThreadRunArgs *threadRunArgs = (ThreadRunArgs *) args;

    if (gVm->AttachCurrentThread(&env, NULL) == 0) {

        if (pthread_mutex_lock(&mutex) != 0) {
            throwByName(env, runtimeException, "Unable to lock mutex");
        }

        env->CallVoidMethod(gObj, printThreadName);

        if (pthread_mutex_unlock(&mutex)) {
            throwByName(env, runtimeException, "Unable to unlock mutex");
        }
        // 从 Java 虚拟机上分离当前线程
        gVm->DetachCurrentThread();
    }
    return (void *) threadRunArgs->result;
}

