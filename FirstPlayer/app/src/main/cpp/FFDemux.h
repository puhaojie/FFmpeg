//
// Created by LB on 2018/8/8.
// .h 头文件 用于定义
//

#ifndef FIRSTPLAYER_FFDEMUX_H
#define FIRSTPLAYER_FFDEMUX_H
using namespace std;

#include "IDemux.h"
struct AVFormatContext; // 直接使用声明
// 基于FFmpeg的解码
class FFDemux : public IDemux{
public:
    //打开文件 或者流媒体
    virtual bool Open(const char *url);
    virtual void Close();
    //读取一帧数据  数据由调用者清理
    virtual XData Read();

    //seek 位置 pos 0.0~1.0
    virtual bool Seek(double pos);

    virtual XParameter GetVPara();

    // 获取音频参数
    virtual XParameter GetAPara();

    FFDemux();

private:
    AVFormatContext *ic = 0; // c++11 的一个坑，与构造方法是否有无参数有关
    std::mutex mux;
    // 对应的索引
    int audioStream = 1;
    int videoStream = 0;
};


#endif //FIRSTPLAYER_FFDEMUX_H
