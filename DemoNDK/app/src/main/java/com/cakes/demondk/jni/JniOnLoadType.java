package com.cakes.demondk.jni;

public class JniOnLoadType extends BaseJNI {

    public native String getMessage();

    public native int plus(int x, int y);
}
