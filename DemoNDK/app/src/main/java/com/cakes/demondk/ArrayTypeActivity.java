package com.cakes.demondk;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;

import com.cakes.demondk.bean.Animal;
import com.cakes.demondk.jni.JniArrayType;

public class ArrayTypeActivity extends AppCompatActivity {

    private final String TAG = "ArrayTypeActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_array_type);

        findViewById(R.id.array_type_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                testArrayType();
            }
        });
    }

    private void testArrayType() {
        LogUtil.i(TAG, "testArrayType() -- 11111111");
        int[] intArray = JniArrayType.getIntArray(3);
        LogUtil.i(TAG, "len of JniArrayType.getIntArray is: " + intArray.length);
        for (int i : intArray) {
            LogUtil.i(TAG, "testArrayType() value = " + i);
        }

        LogUtil.i(TAG, "testArrayType() -- 22222222222");
        int[] sumArray = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int sum = JniArrayType.intArraySum(sumArray, sumArray.length);
        LogUtil.d(TAG, "testArrayType() -- sum = " + sum);

        LogUtil.i(TAG, "testArrayType() -- 333333333");
        int[][] result = JniArrayType.getTwoDimensionalArray(3);
        LogUtil.i(TAG, "len of result = " + result.length + ", len of line = " + result[0].length);
        for (int[] line : result) {
            LogUtil.i(TAG, "test one line:");
            for (int value : line) {
                LogUtil.w(TAG, "value = " + value);
            }
        }

        LogUtil.e(TAG, "testArrayType() -- 4444444 call JniArrayType.printAnimalsName()...");
        Animal[] animals = {new Animal("animal_a"),
                new Animal("animal_b"),
                new Animal("animal_c"),
                new Animal("animal_d")};
        JniArrayType.printAnimalsName(animals);

        LogUtil.d(TAG, "testArrayType() -- 5555555 call JniArrayType.primitiveTypeArray()...");
        int[] testInt = {0, 1, 2, 3, 4};
        float[] testFloat = {0, 1, 2, 3, 4};
        double[] testDouble = {0, 1, 2, 3, 4};
        short[] testShort = {0, 1, 2, 3, 4};
        long[] testLong = {0, 1, 2, 3, 4};
        boolean[] testBool = {false, false, true, true};
        char[] testChar = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
        byte[] testByte = {0, 1, 2, 3, 4};
        JniArrayType.primitiveTypeArray(testInt, testFloat, testDouble,
                testShort, testLong, testBool, testChar, testByte);
    }
}