package com.cakes.demondk.bean;

public class Bird extends Animal {

    public Bird(String name) {
        super(name);
    }

    @Override
    public String getName() {
        return "My name is " + name;
    }
}
