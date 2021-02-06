package com.cakes.demondk.jni;

import com.cakes.demondk.bean.Dog;

public class JniFiledType extends JniBaseType {

    public native void accessInstanceFiled(Dog dog);

    public native void accessStaticField(Dog dog);

}
