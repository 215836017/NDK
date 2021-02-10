package com.cakes.demondk.jni;

public class JniExceptionType extends BaseJNI {

    public native void doit() throws IllegalArgumentException;

    public native void nativeThrowException() throws IllegalArgumentException;

    /**
     * Native 代码调用 Java 时发生了异常，并不会处理
     */
    public native void nativeInvokeJavaException();

    /**
     * 由 Native 来调用该函数，由于 除数为 0 ，引发异常，在 Native 代码中清除这次异常
     */
    private int operation() {
        return 2 / 0;
    }

    /**
     * Native 调用  Java 方式时，导致异常了并不会立即终止 Native 方法的执行
     */
    private void callback() throws NullPointerException {
        throw new NullPointerException("CatchThrow.callback by Native Code");
    }
}
