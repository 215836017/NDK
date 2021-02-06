package com.cakes.demondk.bean;

import com.cakes.demondk.LogUtil;

public class Animal {

    protected String name;
    public static int num = 0;

    public Animal(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void printAge(int age) {
        LogUtil.i("Animal", "printAge() -- age = " + age);
    }
}
