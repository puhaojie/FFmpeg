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
#include <android/native_window.h>
#include <android/native_window_jni.h>

class ObsTest : public IObserver {
public:
    void Update(XData data) {
        LOGI("ObsTest Update %d", data.size);
    }
};
IVideoView * view;
extern "C"
JNIEXPORT jstring



JNICALL
Java_com_phj_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDemux *de = new FFDemux();
    de->Open("/sdcard/1080.mp4");

//    ObsTest * obsTest =new ObsTest();


    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *adecode = new FFDecode();
    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample  *resample = new FFResample();
    resample->Open(de->GetAPara());
    adecode->AddObs(resample);

    //线程中读取
    de->Start();
    vdecode->Start();
    adecode->Start();
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
    view->SetRender(nwin);
//    XEGL *egl = XEGL::Get();
//    egl->Init(nwin);
//    XShader shader;
//    shader.Init();
}