package com.cakes.demondk.jni;

import com.cakes.demondk.bean.Animal;

public class JniConstructType extends BaseJNI {

    public static native String invokeStringConstructors();

    public static native Animal invokeAnimalConstructors();

    // 调用 allocObject 方法来构造一个类
    public static native Animal allocObjectConstructor();

    // 调用父类的方法
    public static native void callSuperMethod();
}
