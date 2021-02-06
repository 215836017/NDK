package com.cakes.demondk.jni;

import com.cakes.demondk.model.ICallbackMethod;
import com.cakes.demondk.model.IThreadCallback;

public class JniCallbakcType extends BaseJNI {

    public native void nativeCallback(ICallbackMethod callbackMethod);

    public native void nativeThreadCallback(IThreadCallback threadCallback);

}
