//
// Created by Administrator on 2024/9/6.
//

#include "./cxx/ffi.h"
#include <cstring>

jobject QuickJSWrapper::toJavaObject(JNIEnv *env, jobject thiz, JSValueConst& this_obj, JSValueConst& value) const{
    jobject result;
    switch (JS_VALUE_GET_NORM_TAG(value)) {
        case JS_TAG_EXCEPTION: {
            result = nullptr;
            break;
        }

        case JS_TAG_STRING: {
            result = toJavaString(env, context, value);
            break;
        }

        case JS_TAG_BOOL: {
            jvalue v;
            v.z = static_cast<jboolean>(JS_VALUE_GET_BOOL(value));
            result = env->CallStaticObjectMethodA(booleanClass, booleanValueOf, &v);
            break;
        }

        case JS_TAG_INT: {
            jvalue v;
            v.j = static_cast<jint>(JS_VALUE_GET_INT(value));
            result = env->CallStaticObjectMethodA(integerClass, integerValueOf, &v);
            break;
        }

        case JS_TAG_BIG_INT: {
            int64_t e;
            JS_ToBigInt64(context, &e, value);
            jvalue v;
            v.j = e;
            result = env->CallStaticObjectMethodA(longClass, longValueOf, &v);
            break;
        }

        case JS_TAG_FLOAT64: {
            jvalue v;
            double d = JS_VALUE_GET_FLOAT64(value);
            bool isInteger = floor(d) == d;
            if (isInteger) {
                v.j = static_cast<jlong>(d);
                result = env->CallStaticObjectMethodA(longClass, longValueOf, &v);
            } else {
                v.d = static_cast<jdouble>(d);
                result = env->CallStaticObjectMethodA(doubleClass, doubleValueOf, &v);
            }
            break;
        }

        case JS_TAG_OBJECT: {
            auto value_ptr = reinterpret_cast<jlong>(JS_VALUE_GET_PTR(value));
            jobject creatorObj = env->CallObjectMethod(thiz, creatorM);
            if (JS_IsFunction(context, value)) {
                auto obj_ptr = reinterpret_cast<jlong>(JS_VALUE_GET_PTR(this_obj));
                result = env->CallObjectMethod(creatorObj, newFunctionM, thiz, value_ptr, obj_ptr);
            } else if (JS_IsArray(context, value)) {
                result = env->CallObjectMethod(creatorObj, newArrayM, thiz, value_ptr);
            } else {
                result = env->CallObjectMethod(creatorObj, newObjectM, thiz, value_ptr);
            }
            env->DeleteLocalRef(creatorObj);
            break;
        }

        default:
            result = nullptr;
            break;
    }

    return result;
}

int main(){
    printf("Hello Quick JS");
    JSRuntime *pJsRuntime = jsNewRuntime(0,0);
    JSContext  *jsContext = jsNewContext(pJsRuntime);
    const char* jsRunValue = "var a = 10";
    JSValue *value = jsEval(jsContext,jsRunValue, strlen(jsRunValue),"test.js",0);
    const char* jsJsonValue = "{User-Agent: jianpian-android/360, JPAUTH: y261ow7kF2dtzlxh1GS9EB8nbTxNmaK/QQIAjctlKiEv, Referer: www.jianpianapp.com}";
    JSValue *value1 = jsJsonParse(jsContext,jsJsonValue, strlen(jsJsonValue));
    return 0;

}