#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "threadType.h"

void *printThreadHello(void *);

void *printThreadArgs(void *);

void *printThreadJoin(void *);

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
