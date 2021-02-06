#include <jni.h>
#include <string>

#include "logUtil.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniFiledType_accessInstanceFiled(JNIEnv *env, jobject thiz,
                                                            jobject dog) {
    jfieldID jfieldId;
    jstring jStr;
    const char *str;

    jclass classDog = env->GetObjectClass(dog);
    jfieldId = env->GetFieldID(classDog, "name", "Ljava/lang/String;");
    if (NULL == jfieldId) {
        LOGE("JniFiledType_accessInstanceFiled() -- error: NULL == jfieldId");
        return;
    }

    jStr = static_cast<jstring>(env->GetObjectField(dog, jfieldId));
    str = env->GetStringUTFChars(jStr, NULL);
    if (NULL == str) {
        LOGE("JniFiledType_accessInstanceFiled() -- error: NULL == str");
        return;
    }
    LOGD("JniFiledType_accessInstanceFiled() -- str is %s", str);
    env->ReleaseStringUTFChars(jStr, str);

    jStr = env->NewStringUTF("newName");
    if (NULL == jStr) {
        return;
    }
    env->SetObjectField(dog, jfieldId, jStr);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniFiledType_accessStaticField(JNIEnv *env, jobject thiz, jobject dog) {

    jfieldID jfieldId;
    jint age;

    jclass classDog = env->GetObjectClass(dog);
    jfieldId = env->GetStaticFieldID(classDog, "age", "I");
    if (NULL == jfieldId) {
        LOGE("JniFiledType_accessStaticField() -- error: NULL == jfieldId");
        return;
    }

    age = env->GetStaticIntField(classDog, jfieldId);
    LOGI("JniFiledType_accessStaticField() -- age = %d", age);

    env->SetStaticIntField(classDog, jfieldId, 30);
}