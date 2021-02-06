#include <jni.h>
#include "logUtil.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_cakes_demondk_jni_JniConstructType_invokeStringConstructors(JNIEnv *env, jclass clazz) {

    jclass stringClass;
    jmethodID constructMethodId;

    // 找到Java的String类
    stringClass = env->FindClass("java/lang/String");
    if (NULL == stringClass) {
        LOGE("JniConstructType_invokeStringConstructors()  -- error: NULL == stringClass");
        return NULL;
    }

    // 找到具体的构造方法
    constructMethodId = env->GetMethodID(stringClass, "<init>", "([C)V");
    if (NULL == constructMethodId) {
        LOGE("JniConstructType_invokeStringConstructors()  -- error: NULL == constructMethodId");
        return NULL;
    }

    // 由 C++ 字符串创建一个 Java 字符串
    jstring temp = env->NewStringUTF("this String is form C++");
    // 再从 Java 字符串获得一个字符数组指针，作为 String 构造函数的参数
    const jchar *chars = env->GetStringChars(temp, NULL);
    int len = 10;

    jcharArray charArray = env->NewCharArray(len);
    if (NULL == charArray) {
        LOGE("JniConstructType_invokeStringConstructors()  -- error: NULL == charArray");
        return NULL;
    }
    env->SetCharArrayRegion(charArray, 0, len, chars);

    jstring result = (jstring) env->NewObject(stringClass, constructMethodId, charArray);

    env->DeleteLocalRef(charArray);
    env->DeleteLocalRef(stringClass);

    return result;
}

/**
 * 创建一个 Java 的 Animal 类并返回
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_cakes_demondk_jni_JniConstructType_invokeAnimalConstructors(JNIEnv *env, jclass clazz) {
    jclass animalClass;

    animalClass = env->FindClass("com/cakes/demondk/bean/Animal");
    if (NULL == animalClass) {
        LOGE("JniConstructType_invokeAnimalConstructors() -- error: NULL == animalClass");
        return NULL;
    }

    jmethodID constructMethodId = env->GetMethodID(animalClass, "<init>", "(Ljava/lang/String;)V");
    if (NULL == constructMethodId) {
        LOGE("JniConstructType_invokeAnimalConstructors() -- error: NULL == constructMethodId");
        return NULL;
    }

    jstring arg = env->NewStringUTF("nameFromC");
    jobject result = env->NewObject(animalClass, constructMethodId, arg);

    env->DeleteLocalRef(animalClass);
    return result;
}

/**
 * 通过 AllocObject 方法来创建一个类
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_cakes_demondk_jni_JniConstructType_allocObjectConstructor(JNIEnv *env, jclass clazz) {
    jclass animalClass;
    jmethodID mid;
    jobject result;

    animalClass = env->FindClass("com/cakes/demondk/bean/Animal");
    if (NULL == animalClass) {
        LOGE("JniConstructType_allocObjectConstructor() -- error: NULL == animalClass");
        return NULL;
    }

    mid = env->GetMethodID(animalClass, "<init>", "(Ljava/lang/String;)V");
    if (NULL == mid) {
        LOGE("JniConstructType_allocObjectConstructor() -- error: NULL == mid");
        return NULL;
    }

    result = env->AllocObject(animalClass);
    if (NULL == result) {
        LOGE("JniConstructType_allocObjectConstructor() -- error: NULL == result");
        return NULL;
    }

    jstring name = env->NewStringUTF("name for allocObject");

    // 调用 CallNonvirtualVoidMethod 方法去调用类的构造方法
    env->CallNonvirtualVoidMethod(result, animalClass, mid, name);
    if (env->ExceptionCheck()) {
        env->DeleteLocalRef(result);
        return NULL;
    }

    return result;
}

/**
 * 调用父类的方法
 * 创建一个子类，由子类去调用父类的方法
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniConstructType_callSuperMethod(JNIEnv *env, jclass clazz) {

    jclass birdClass;
    jmethodID birdMethodId;

    // 子类相关
    birdClass = env->FindClass("com/cakes/demondk/bean/Bird");
    if (NULL == birdClass) {
        LOGE("JniConstructType_callSuperMethod() -- error: NULL == birdClass");
        return;
    }

    birdMethodId = env->GetMethodID(birdClass, "<init>", "(Ljava/lang/String;)V");
    if (NULL == birdMethodId) {
        LOGE("JniConstructType_callSuperMethod() -- error: NULL == birdMethodId");
        return;
    }

    jstring birdName = env->NewStringUTF("birdName form C");
    jobject birdObj = env->NewObject(birdClass, birdMethodId, birdName);
    if (NULL == birdObj) {
        LOGE("JniConstructType_callSuperMethod() -- error: NULL == birdObj");
        return;
    }

    // 父类相关
    jclass animalClass;
    jmethodID animalMethodId;

    animalClass = env->FindClass("com/cakes/demondk/bean/Animal");
    if (NULL == animalClass) {
        LOGE("JniConstructType_callSuperMethod() -- error: NULL == animalClass");
        return;
    }

    animalMethodId = env->GetMethodID(animalClass, "getName", "()Ljava/lang/String;");
    if (NULL == animalMethodId) {
        LOGE("JniConstructType_callSuperMethod() -- error: NULL == animalMethodId");
        return;
    }

    jstring animalName = (jstring) env->CallNonvirtualObjectMethod(birdObj, animalClass,
                                                                   animalMethodId);
    if (NULL == animalName) {
        LOGE("JniConstructType_callSuperMethod() -- error: NULL == animalName");
        return;
    }

    LOGW("getName method value is %s", env->GetStringUTFChars(animalName, NULL));

    // 通过子类调用父类的其他方法
    animalMethodId = env->GetMethodID(animalClass, "printAge", "(I)V");
    if (NULL == animalMethodId) {
        LOGE("JniConstructType_callSuperMethod() -- error: NULL == animalMethodId 2222");
        return;
    }
    env->CallNonvirtualVoidMethod(birdObj, animalClass, animalMethodId, 10);

}
