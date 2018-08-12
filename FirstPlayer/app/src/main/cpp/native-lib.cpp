#include <jni.h>
#include <string>

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "IPlayerProxy.h"

static IPlayerProxy *player = NULL;

extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm,void *res){

//    FFPlayerBuilder::Get()->InitHard(vm);
//    player = IPlayerProxy::Get()->BuilderPlayer();
    IPlayerProxy::Get()->Init(vm);

//    IPlayerProxy::Get()->Open("/sdcard/4.avi");
//    IPlayerProxy::Get()->Start();
//
//    XSleep(2000);


    return JNI_VERSION_1_4;
}


// 窗口的初始化
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {


    //显示窗口初始化
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
//    if (player)
    IPlayerProxy::Get()->InitView(nwin);
//    XEGL *egl = XEGL::Get();
//    egl->Init(nwin);
//    XShader shader;
//    shader.Init();
}


// 开始播放
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_PlayActivity_Open(JNIEnv *env, jobject instance, jstring url_) {
    const char *url = env->GetStringUTFChars(url_, 0);

    IPlayerProxy::Get()->Open(url);
    IPlayerProxy::Get()->Start();
//
    env->ReleaseStringUTFChars(url_, url);
}


extern "C"
JNIEXPORT jdouble JNICALL
Java_com_phj_player_MainActivity_PlayPos(JNIEnv *env, jobject instance) {


    return IPlayerProxy::Get()->PlayPos();

}



extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_MainActivity_Seek(JNIEnv *env, jobject instance, jdouble pos) {

    IPlayerProxy::Get()->Seek(pos);

}

extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_XPlay_PlayOrPause(JNIEnv *env, jobject instance) {

    IPlayerProxy::Get()->SetPause(!IPlayerProxy::Get()->IsPause());

}