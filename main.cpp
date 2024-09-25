//
// Created by Administrator on 2024/9/6.
//

#include "./cxx/ffi.h"
#include <cstring>
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