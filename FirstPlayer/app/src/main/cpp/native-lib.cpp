#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XShader.h"
#include "XEGL.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "IResample.h"
#include "FFResample.h"
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"
#include <android/native_window.h>
#include <android/native_window_jni.h>


IVideoView * view;
extern "C"
JNIEXPORT
jint JNI_OnLoad(JavaVM *vm,void *res){
    FFDecode::InitHard(vm);

    IDemux *de = new FFDemux();
//    de->Open("/sdcard/1080.mp4");

//    ObsTest * obsTest =new ObsTest();


    IDecode *vdecode = new FFDecode();
//    vdecode->Open(de->GetVPara(), true);

    IDecode *adecode = new FFDecode();
//    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample  *resample = new FFResample();
//    XParameter outPara = de->GetAPara();
//    resample->Open(de->GetAPara(),outPara);
    adecode->AddObs(resample);

    IAudioPlay* play = new SLAudioPlay();
//    play->StartPlay(outPara);
    resample->AddObs(play);

    IPlayer::Get()->demux = de;
    IPlayer::Get()->adecode = adecode;
    IPlayer::Get()->vdecode = vdecode;
    IPlayer::Get()->videoView = view;
    IPlayer::Get()->resample = resample;
    IPlayer::Get()->audioPlay = play;
    IPlayer::Get()->Open("/sdcard/1080.mp4");
    IPlayer::Get()->Start();
    //线程中读取
//    de->Start();
//    vdecode->Start();
//    adecode->Start();
    return JNI_VERSION_1_4;
}


extern "C"
JNIEXPORT jstring



JNICALL
Java_com_phj_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

//    XSleep(1000);

//    XSleep(3000);
//    de->Stop();


    return env->NewStringUTF(hello.c_str());
}


// 窗口的初始化
extern "C"
JNIEXPORT void JNICALL
Java_com_phj_player_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {


    //显示窗口初始化
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
    IPlayer::Get()->InitView(nwin);
//    XEGL *egl = XEGL::Get();
//    egl->Init(nwin);
//    XShader shader;
//    shader.Init();
}