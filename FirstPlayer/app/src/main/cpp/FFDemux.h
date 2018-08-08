//
// Created by LB on 2018/8/8.
// .h 头文件 用于定义
//

#ifndef FIRSTPLAYER_FFDEMUX_H
#define FIRSTPLAYER_FFDEMUX_H


#include "IDemux.h"
struct AVFormatContext; // 直接使用声明
// 基于FFmpeg的解码
class FFDemux : public IDemux{
public:
    //打开文件 或者流媒体
    virtual bool Open(const char *url);
    //读取一帧数据  数据由调用者清理
    virtual XData Read();

    FFDemux();

private:
    AVFormatContext *ic = 0; // c++11 的一个坑，与构造方法是否有无参数有关
};


#endif //FIRSTPLAYER_FFDEMUX_H
