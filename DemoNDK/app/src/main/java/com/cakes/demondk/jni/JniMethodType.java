package com.cakes.demondk.jni;

import com.cakes.demondk.bean.Cat;

public class JniMethodType extends BaseJNI {

    public static native void callInstanceMethod(Cat cat);

    public static native void callStaticMethod(Cat cat);
}
