#include<jni.h>
#include<string>
#include "json/json.h"

#define XONGFUNC(name)Java_com_example_roy_jniproject_##name
extern "C" JNIEXPORT
jstring JNICALL

XONGFUNC(MainActivity_jniTest)(JNIEnv *env,jclass thiz){
 std::string hello = "Hello,jni";
 return env -> NewStringUTF(hello.c_str());
}


/**
 * 生成json
 */
extern "C" JNIEXPORT
jstring JNICALL
XONGFUNC(MainActivity_jniMakeJson)(JNIEnv *env,jclass thiz,jstring jname,jstring jage,jstring jsex){
    Json::Value root;
    const char *name = env->GetStringUTFChars(jname, NULL);
    const char *age = env->GetStringUTFChars(jage, NULL);
    const char *sex = env->GetStringUTFChars(jsex, NULL);
    root["name"] = name;
    root["age"] = age;
    root["sex"] = sex;
    env->ReleaseStringUTFChars(jname, name);
    env->ReleaseStringUTFChars(jage, age);
    env->ReleaseStringUTFChars(jsex, sex);
    return env->NewStringUTF(root.toStyledString().c_str());
}


/**
 * 解析json
 */
extern "C" JNIEXPORT
jstring JNICALL
XONGFUNC(MainActivity_jniParseJson)(JNIEnv *env, jclass thiz,
                                  jstring jjson)
{
    const char *json_str = env->GetStringUTFChars(jjson, NULL);
    std::string out_str;
    Json::CharReaderBuilder b;
    Json::CharReader *reader(b.newCharReader());
    Json::Value root;
    JSONCPP_STRING errs;
    bool ok = reader->parse(json_str, json_str + std::strlen(json_str), &root, &errs);
    if (ok && errs.size() == 0) {
        std::string name = root["name"].asString();
        std::string age = root["age"].asString();
        std::string sex = root["sex"].asString();

        out_str = "name: " + name + "\nage: " + age + "\nsex:" + sex + "\n";
    }
    env->ReleaseStringUTFChars(jjson, json_str);
    return env->NewStringUTF(out_str.c_str());
}