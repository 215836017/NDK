#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "threadType.h"


pthread_mutex_t mutex;
pthread_cond_t cond;

pthread_t waitHandler;
pthread_t notifyHandler;

int flag = 0;

void *waitThread(void *) {
    LOGI("waitThread() ---  111111...");
    pthread_mutex_lock(&mutex);  // 拿到锁
    while (flag == 0) {
        LOGI("waitThread() ---  waitting...");
        pthread_cond_wait(&cond, &mutex);  // 一直等待，知道cond条件被满足
    }
    LOGI("waitThread() ---  2222222...");
    pthread_mutex_unlock(&mutex); // 释放锁

    pthread_exit(0);
}

void *notifyThread(void *) {
    LOGI("notifyThread() ---  111111...");
    pthread_mutex_lock(&mutex);
    flag = 1;
    LOGI("notifyThread() ---  22222， flag = %d", flag);
    pthread_mutex_unlock(&mutex);
    LOGI("notifyThread() ---  33333...");
    pthread_cond_signal(&cond);  // 唤醒一直等待的，拥有cond变量的线程

    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_waitNativeThread(JNIEnv *env, jobject thiz) {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&waitHandler, NULL, waitThread, NULL);  // 创建并启动wait线程
}


extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_notifyNativeThread(JNIEnv *env, jobject thiz) {
    pthread_create(&notifyHandler, NULL, notifyThread, NULL);  // 创建并启动notify线程
}

