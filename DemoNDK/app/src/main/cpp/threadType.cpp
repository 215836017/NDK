#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "threadType.h"

static JavaVM *gVm = NULL;
static const char *runtimeException = "java/lang/RuntimeException";

static jobject gObj = NULL;
static jmethodID printNativeMsg;
static jmethodID printThreadName;
static pthread_mutex_t mutex;

void *printThreadHello(void *);

void *printThreadArgs(void *);

void *printThreadJoin(void *);

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
    /*
     * 1. printThreadHello()方法相当于 Thread 的 run 方法
     * 2. 在printThreadHello()方法中执行耗时操作
     * 3. pthread_create()返回0表示创建线程成功，创建成功之后会自动调用线程中的方法，这里就是printThreadHello()方法
     */
    if (0 != result) {
        LOGD("JniThreadType_createNativeThread() -- create thread failed");
    } else {
        LOGD("JniThreadType_createNativeThread() -- create thread success");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    pthread_t handler;
    ThreadRunArgs *arg = new ThreadRunArgs;
    arg->id = 2;
    arg->result = 200;
    int result = pthread_create(&handler, NULL, printThreadArgs, arg);
    if (0 != result) {
        LOGD("JniThreadType_createNativeThreadWithArgs() -- create thread failed");
    } else {
        LOGD("JniThreadType_createNativeThreadWithArgs() -- create thread success");
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_testNativeThreadJoin(JNIEnv *env, jobject thiz) {
    pthread_t handler;
    ThreadRunArgs *arg = new ThreadRunArgs;
    arg->id = 22;
    arg->result = 2200;
    int result = pthread_create(&handler, NULL, printThreadJoin, arg);
    if (0 != result) {
        LOGD("JniThreadType_testNativeThreadJoin() -- create thread failed");
    } else {
        LOGD("JniThreadType_testNativeThreadJoin() -- create thread success");
    }

    void *ret = nullptr;
    pthread_join(handler, &ret);  // 会把调用者的线程阻塞
    LOGD("JniThreadType_testNativeThreadJoin() -- ret = %d", ret);
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
    /*
     *  1. pthread_exit() -- 线程的显式退出， 则可不用return了
     *  2. 如果既没有pthread_exit()， 也没有return， 则会崩溃
     */
    pthread_exit(0);
//    return NULL;
}

void *printThreadArgs(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    LOGD("printThreadArgs() -- args->id = %d", args->id);
    LOGD("printThreadArgs() -- args->result = %d", args->result);

    struct timeval begin;
    gettimeofday(&begin, nullptr);
    LOGD("printThreadJoin() -- start time  = %lld", begin.tv_sec);
    sleep(3);  // 模拟耗时操作

    struct timeval end;
    gettimeofday(&end, nullptr);
    LOGD("printThreadJoin() -- end time = %lld", end.tv_sec);
    return nullptr;
}

void *printThreadJoin(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    LOGD("printThreadJoin() -- args->id = %d", args->id);
    LOGD("printThreadJoin() -- args->result = %d", args->result);

    struct timeval begin;
    gettimeofday(&begin, nullptr);
    LOGD("printThreadJoin() -- start time  = %lld", begin.tv_sec);
    sleep(3);  // 模拟耗时操作

    struct timeval end;
    gettimeofday(&end, nullptr);
    LOGD("printThreadJoin() -- end time = %lld", end.tv_sec);

    LOGD("printThreadJoin() --time use = %d", end.tv_sec - begin.tv_sec);

    return reinterpret_cast<void *>(args->result);
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

