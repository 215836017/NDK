#include <stdio.h>
#include <unistd.h>
#include "common.h"
#include "threadType.h"

pthread_mutex_t dataMutex;
pthread_cond_t dataCond;

pthread_t produceHandler;
pthread_t consumeHandler;

int dataFlag = 0;

void *produceThread(void *) {
    LOGI("produceThread() ---  111111...");

    while (dataFlag <= 10) {
        pthread_mutex_lock(&dataMutex);  // 拿到锁
        dataFlag++;
        LOGI("produceThread() ---  生产了一个物品...");
        if (dataFlag > 0) {
            LOGI("produceThread() ---  等待消费...");
            pthread_cond_signal(&dataCond);
        }

        pthread_mutex_unlock(&dataMutex); // 释放锁

        sleep(2);
    }

    return nullptr;
}

void *consumeThread(void *) {
    LOGI("consumeThread() ---  111111...");

    while (1) {
        pthread_mutex_lock(&dataMutex);

        if (dataFlag > 0) {
            LOGI("consumeThread()  -- 消费物品。。。");
            dataFlag--;
        } else {
            LOGI("consumeThread()  -- 等待物品中。。。");
            pthread_cond_wait(&dataCond, &dataMutex);  // 一直等待
        }

        pthread_mutex_unlock(&dataMutex);

        sleep(1);
    }

    pthread_exit(0);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniThreadType_produceAndConsumeThread(JNIEnv *env, jobject thiz) {

    pthread_mutex_init(&dataMutex, nullptr);
    pthread_cond_init(&dataCond, nullptr);

    pthread_create(&produceHandler, NULL, produceThread, NULL);  // 创建并启动wait线程
    pthread_create(&consumeHandler, NULL, consumeThread, NULL);  // 创建并启动wait线程
}



