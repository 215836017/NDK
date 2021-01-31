#include <jni.h>
#include <string>

#include "logUtil.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniArrayType_primitiveTypeArray(JNIEnv *env, jobject thiz,
                                                           jintArray int_array,
                                                           jfloatArray float_array,
                                                           jdoubleArray double_array,
                                                           jshortArray short_array,
                                                           jlongArray long_array,
                                                           jbooleanArray bool_array,
                                                           jcharArray char_array,
                                                           jbyteArray byte_array) {
// TODO: implement primitiveTypeArray()
}

extern "C"
JNIEXPORT jint JNICALL
        Java_com_cakes_demondk_jni_JniArrayType_intArraySum(JNIEnv *env, jobject thiz, jintArray int_array,
                                                            jint size) {
// TODO: implement intArraySum()
}

extern "C"
JNIEXPORT jintArray JNICALL
        Java_com_cakes_demondk_jni_JniArrayType_getIntArray(JNIEnv *env, jobject thiz, jint num) {
// TODO: implement getIntArray()
}

extern "C"
JNIEXPORT jobjectArray JNICALL
        Java_com_cakes_demondk_jni_JniArrayType_getTwoDimensionalArray(JNIEnv *env, jobject thiz, jint size) {
// TODO: implement getTwoDimensionalArray()
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cakes_demondk_jni_JniArrayType_printAnimalsName(JNIEnv *env, jobject thiz,
                                                         jobjectArray animal) {
// TODO: implement printAnimalsName()
}