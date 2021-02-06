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
     * �β��У�
     *   jclass  ��Ӧ��Java�еľ�̬����
     *   jobject ��Ӧ��Java�еĶ��󷽷�
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

    //��������һ��ָ����ʽ
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
// TODO ����Ҫ��ʹ�����˱������ͷ��ڴ�
//    env->ReleaseIntArrayElements(int_array, intArray, 0);
//    return sum;

    // ������������������ʽ
    jint intBuf[length];
    env->GetIntArrayRegion(int_array, 0, length, intBuf);
    for (int i = 0; i < length; i++) {
        sum += intBuf[i];
    }
    LOGI("JniArrayType_intArraySum() -- sum = %d", sum);
    // TODO ����Ҫ��ʹ�����˱������ͷ��ڴ�
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
    // ʹ�� setIntArrayRegion ����ֵ
    env->SetIntArrayRegion(intArray, 0, num, intBuf);

    return intArray;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_cakes_demondk_jni_JniArrayType_getTwoDimensionalArray(JNIEnv *env, jclass thiz,
                                                               jint size) {
    // ����һ����������
    jobjectArray result;
    // �ҵ����������о���Ķ�������
    jclass intArrayCls = env->FindClass("[I");  // [I ��int��������
    if (NULL == intArrayCls) {
        return NULL;
    }
    // �൱�ڳ�ʼ��һ���������飬��ָ���Ķ�������
    result = env->NewObjectArray(size, intArrayCls, NULL);
    if (NULL == result) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        // ��������������������ݵĻ�����
        jint tmp[256];
        // ����һ����������
        jintArray iarr = env->NewIntArray(size);
        if (NULL == iarr) {
            return NULL;
        }
        for (int j = 0; j < size; ++j) {
            tmp[j] = i + j;
        }
        // �����������������
        env->SetIntArrayRegion(iarr, 0, size, tmp);
        // ����������ָ��λ��������ݣ�������ݾ���һ��һά��������
        env->SetObjectArrayElement(result, i, iarr);
        // �ͷžֲ�����
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
    // ���Ӧ���ֶ�����
    jfieldID fieldIdName = env->GetFieldID(classAnimal, "name", "Ljava/lang/String;");
    // ����ֶξ����ֵ
    jstring jstr;
    // ���ֶξ���ֵת���� C/C++ �ַ���
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