package com.cakes.demondk.bean;

import com.cakes.demondk.LogUtil;

public class Cat {

    private static final String TAG = "Cat";

    // C++ 调用 Java 的实例方法
    public void callInstanceVoidMethod() {
        LogUtil.i(TAG, "C call method in Java");
    }

    public void callInstanceMethod(int num) {
        LogUtil.d(TAG, "C call method in Java: call instance method and num is " + num);
    }

    public int callInstanceIntMethod(int num) {
        LogUtil.w(TAG, "C call method in Java: call instance method and num is " + num);
        return num + 10;
    }

    // C++ 调用 Java 的类方法
    public static String callStaticMethod(String value) {
        LogUtil.i(TAG, "callStaticMethod() -- value = " + value);

        return "result form Java";
    }

    public static String callStaticMethod(String[] value, int num) {
        if (null != value) {
            LogUtil.d(TAG, "callStaticMethod() -- value.len = " + value.length);
        }
        LogUtil.d(TAG, "callStaticMethod() -- num = " + num);
        return "result form Java";
    }

    public static void callStaticVoidMethod() {
        LogUtil.w(TAG, "C call Java static method...");
    }
}