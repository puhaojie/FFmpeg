#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "XLog.h"
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
    de->Open("/sdcard/4.avi");

    ObsTest * obsTest =new ObsTest();
    de->AddObs(obsTest);
    //线程中读取
    de->Start();
    XSleep(3000);
    de->Stop();


    return env->NewStringUTF(hello.c_str());
}
