package com.cakes.demondk.jni;

public class JniBaseType extends BaseJNI {

    public native byte callJniByte(byte b);

    public native char callJniChar(char ch);

    public native short callJniShort(short num);

    public native int callJniInt(int num);

    public native long callJniLong(long num);

    public native float callJniFloat(float num);

    public native double callJniDouble(double num);

    public native boolean callJniBoolean(boolean b);
}
