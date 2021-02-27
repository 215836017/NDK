package com.cakes.demondk.jni;

import com.cakes.demondk.LogUtil;

public class JniThreadType extends BaseJNI {

    public native void createNativeThread();

    public native void createNativeThreadWithArgs();

    public native void testNativeThreadJoin();

    public native void waitNativeThread();

    public native void notifyNativeThread();

    public native void produceAndConsumeThread();

    /**
     * 打印线程名称，并且模拟耗时任务
     */
    private void printThreadName() {
        LogUtil.d("JniThreadType", "print thread name current thread name is " + Thread.currentThread().getName());
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    /**
     * Native 回到到 Java 的方法，打印当前线程名字
     */
    private void printNativeMsg(String msg) {
        LogUtil.d("JniThreadType", "native msg is " + msg);
        LogUtil.d("JniThreadType", "print native msg current thread name is " + Thread.currentThread().getName());
    }
}
