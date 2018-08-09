#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "XLog.h"
#include "IDecode.h"
#include "FFDecode.h"

class ObsTest : public IObserver{
public:
    void Update(XData data){
        LOGI("ObsTest Update %d",data.size);
    }
};
extern "C"
JNIEXPORT jstring



JNICALL
Java_com_phj_player_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    IDemux *de = new FFDemux();
    de->Open("/sdcard/a.mp4");

//    ObsTest * obsTest =new ObsTest();


    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

//    IDecode *adecode = new FFDecode();
//    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
//    de->AddObs(adecode);

    //线程中读取
    de->Start();
    vdecode->Start();
//    adecode->Start();
//    XSleep(3000);
//    de->Stop();


    return env->NewStringUTF(hello.c_str());
}
