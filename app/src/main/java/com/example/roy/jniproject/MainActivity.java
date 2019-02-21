package com.example.roy.jniproject;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

public class MainActivity extends AppCompatActivity {


    static {
        System.loadLibrary("native_hello");
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Log.e(getPackageName(),jniTest());
        Log.e(getPackageName(),jniMakeJson("小猪","ssdf","0"));
        Log.e(getPackageName(),jniParseJson(jniMakeJson("小猪","ssdf","0")));
    }

    public static native String jniTest();


    //生成json
    public static native String jniMakeJson(String name,String age,String sex);

    //解析json
    public static native String jniParseJson(String jsonString);
}
