#include <jni.h>
#include <string>

#include "logUtil.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniArrayType_primitiveTypeArray(JNIEnv *env, jclass thiz,
                                                           jintArray int_array,
                                                           jfloatArray float_array,
                                                           jdoubleArray double_array,
                                                           jshortArray short_array,
                                                           jlongArray long_array,
                                                           jbooleanArray bool_array,
                                                           jcharArray char_array,
                                                           jbyteArray byte_array) {

    /*
     * 形参中：
     *   jclass  对应于Java中的静态方法
     *   jobject 对应于Java中的对象方法
     */

    jint *intArray = env->GetIntArrayElements(int_array, NULL);
    jfloat *floatArray = env->GetFloatArrayElements(float_array, NULL);
    jdouble *doubleArray = env->GetDoubleArrayElements(double_array, NULL);
    jshort *shortArray = env->GetShortArrayElements(short_array, NULL);
    jlong *longArray = env->GetLongArrayElements(long_array, NULL);
    jboolean *booleanArray = env->GetBooleanArrayElements(bool_array, NULL);
    jchar *charArray = env->GetCharArrayElements(char_array, NULL);
    jbyte *byteArray = env->GetByteArrayElements(byte_array, 0);

    int len = 0;
    if (NULL != intArray) {
        len = env->GetArrayLength(int_array);
        for (int i = 0; i < len; i++) {
            LOGW("JniArrayType_primitiveTypeArray() -- i = %d, int value = %d", i, intArray[i]);
        }
    }

    if (NULL != charArray) {
        len = env->GetArrayLength(char_array);
        for (int i = 0; i < len; i++) {
            LOGI("JniArrayType_primitiveTypeArray() -- i = %d, char value = %c", i, charArray[i]);
        }
    }

    env->ReleaseIntArrayElements(int_array, intArray, 0);
    env->ReleaseFloatArrayElements(float_array, floatArray, NULL);
    env->ReleaseDoubleArrayElements(double_array, doubleArray, 0);
    env->ReleaseShortArrayElements(short_array, shortArray, NULL);
    env->ReleaseLongArrayElements(long_array, longArray, 0);
    env->ReleaseBooleanArrayElements(bool_array, booleanArray, NULL);
    env->ReleaseCharArrayElements(char_array, charArray, NULL);
    env->ReleaseByteArrayElements(byte_array, byteArray, NULL);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_cakes_demondk_jni_JniArrayType_intArraySum(JNIEnv *env, jclass thiz,
                                                    jintArray int_array, jint size) {
    jint *intArray;
    int sum = 0;

    //操作方法一：指针形式
    intArray = env->GetIntArrayElements(int_array, NULL);
    if (NULL == intArray) {
        LOGE("null == intArray");
        return -1;
    }

    int length = env->GetArrayLength(int_array);
    LOGD("JniArrayType_intArraySum() -- length = %d", length);

//    for (int i = 0; i < length; i++) {
//        sum += intArray[i];
//    }
//    LOGI("JniArrayType_intArraySum() -- sum = %d", sum);
// TODO 很重要：使用完了别忘了释放内存
//    env->ReleaseIntArrayElements(int_array, intArray, 0);
//    return sum;

    // 操作方法二：数组形式
    jint intBuf[length];
    env->GetIntArrayRegion(int_array, 0, length, intBuf);
    for (int i = 0; i < length; i++) {
        sum += intBuf[i];
    }
    LOGI("JniArrayType_intArraySum() -- sum = %d", sum);
    // TODO 很重要：使用完了别忘了释放内存
    env->ReleaseIntArrayElements(int_array, intArray, 0);
    return sum;

}

extern "C"
JNIEXPORT jintArray JNICALL
Java_com_cakes_demondk_jni_JniArrayType_getIntArray(JNIEnv *env, jclass thiz, jint num) {
    jintArray intArray;
    intArray = env->NewIntArray(num);

    jint intBuf[num];
    for (int i = 0; i < num; i++) {
        intBuf[i] = i * 2;
    }
    // 使用 setIntArrayRegion 来赋值
    env->SetIntArrayRegion(intArray, 0, num, intBuf);

    return intArray;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_cakes_demondk_jni_JniArrayType_getTwoDimensionalArray(JNIEnv *env, jclass thiz,
                                                               jint size) {
    // 声明一个对象数组
    jobjectArray result;
    // 找到对象数组中具体的对象类型
    jclass intArrayCls = env->FindClass("[I");  // [I 是int数组类型
    if (NULL == intArrayCls) {
        return NULL;
    }
    // 相当于初始化一个对象数组，用指定的对象类型
    result = env->NewObjectArray(size, intArrayCls, NULL);
    if (NULL == result) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        // 用来给整型数组填充数据的缓冲区
        jint tmp[256];
        // 声明一个整型数组
        jintArray iarr = env->NewIntArray(size);
        if (NULL == iarr) {
            return NULL;
        }
        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }
        // 给整型数组填充数据
        env->SetIntArrayRegion(iarr, 0, size, tmp);
        // 给对象数组指定位置填充数据，这个数据就是一个一维整型数组
        env->SetObjectArrayElement(result, i, iarr);
        // 释放局部引用
        env->DeleteLocalRef(iarr);
    }

    return result;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniArrayType_printAnimalsName(JNIEnv *env, jclass thiz,
                                                         jobjectArray animals) {
    LOGW("JniArrayType_printAnimalsName() -- to do print filed of class in C");
    jobject animal;
    int len = env->GetArrayLength(animals);

    jclass classAnimal = env->FindClass("com/cakes/demondk/bean/Animal");
    // 类对应的字段描述
    jfieldID fieldIdName = env->GetFieldID(classAnimal, "name", "Ljava/lang/String;");
    // 类的字段具体的值
    jstring jstr;
    // 类字段具体值转换成 C/C++ 字符串
    const char *str;

    for (int i = 0; i < len; i++) {
        animal = env->GetObjectArrayElement(animals, i);
        if (NULL == animal) {
            continue;
        }
        jstr = (jstring) (env->GetObjectField(animal, fieldIdName));
        str = env->GetStringUTFChars(jstr, 0);
        if (NULL == str) {
            continue;
        }
        LOGW("JniArrayType_printAnimalsName() -- name = %s", str);
        env->ReleaseStringUTFChars(jstr, str);
    }

}