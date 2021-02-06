package com.cakes.demondk.bean;

public class Dog {

    private String name;
    public static int age = 0;

    public Dog(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public static int getAge() {
        return age;
    }

}
