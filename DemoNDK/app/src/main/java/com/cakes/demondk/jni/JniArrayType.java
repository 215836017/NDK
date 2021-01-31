package com.cakes.demondk.jni;

import com.cakes.demondk.bean.Animal;

public class JniArrayType extends JniBaseType {

    private native void primitiveTypeArray(int[] intArray,
                                           float[] floatArray,
                                           double[] doubleArray,
                                           short[] shortArray,
                                           long[] longArray,
                                           boolean[] boolArray,
                                           char[] charArray,
                                           byte[] byteArray);

    // Java 传递 数组 到 Native 进行数组求和
    private native int intArraySum(int[] intArray, int size);

    // 从 Native 返回基本数据类型数组
    private native int[] getIntArray(int num);

    // 从 Native 返回二维整型数组，相当于是一个一维整型数组，每个数组内容又是数组
    private native int[][] getTwoDimensionalArray(int size);

    private native void printAnimalsName(Animal[] animal);
}
