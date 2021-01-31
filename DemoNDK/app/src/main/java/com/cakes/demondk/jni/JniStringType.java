package com.cakes.demondk.jni;

public class JniStringType extends JniBaseType {

    // Java 和 Native 字符串的相互转化
    public native String getAndReleaseString(String str);

    // 反转字符串操作
    public native String reverseString(String str);

    // 获得字符串一半内容
    public native String getHalfString(String str);
}
