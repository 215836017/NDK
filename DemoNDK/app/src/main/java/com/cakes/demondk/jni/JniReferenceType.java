package com.cakes.demondk.jni;

public class JniReferenceType extends BaseJNI {

    public native void useWeakGlobalReference();

    public native String errorCacheUseLocalReference();

    // 全局引用
    public native String cacheWithGlobalReference();

    public native void useLocalReferenceManageFuntions();
}
