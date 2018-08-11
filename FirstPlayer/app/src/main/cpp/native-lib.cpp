#include <jni.h>
#include <string>

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "IPlayerProxy.h"

static IPlayerPorxy *player = NULL;

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm,void *res){

//    FFPlayerBuilder::Get()->InitHard(vm);
//    player = IPlayerProxy::Get()->BuilderPlayer();
    IPlayerPorxy::Get()->Init(vm);

    IPlayerPorxy::Get()->Open("/sdcard/1080.mp4");
    IPlayerPorxy::Get()->Start();
    return JNI_VERSION_1_4;
}


extern "C"
JNIEXPORT jstring



JNICALL
Java_com_phj_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";


    return env->NewStringUTF(hello.c_str());
}


// 窗口的初始化
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {


    //显示窗口初始化
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
//    if (player)
        IPlayerPorxy::Get()->InitView(nwin);
//    XEGL *egl = XEGL::Get();
//    egl->Init(nwin);
//    XShader shader;
//    shader.Init();
}