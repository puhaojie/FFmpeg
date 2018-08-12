//
// Created by LB on 2018/8/11.
//

#ifndef FIRSTPLAYER_IPLAYER_H
#define FIRSTPLAYER_IPLAYER_H


#include <mutex>
#include "XThread.h"
#include "XParameter.h"

class IDemux;
class IVideoView;
class IDecode;
class IResample;
class IAudioPlay;

// 继承线程 用来做同步
class IPlayer : public XThread{

public:
    // 通过索引管理对象
    static IPlayer *Get(unsigned char index = 0);

    virtual bool Open(const char* path);
    virtual void Close();

    virtual bool Start();

    virtual void InitView(void *win);

    //是否视频硬解码
    bool isHardDecode = true;

    //音频输出参数配置
    XParameter outPara;

    IDemux *demux = 0;
    IDecode *vdecode = 0;
    IDecode *adecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;

protected:
    // 用作音视频同步 (采用视频同步音频)
    void Main();
    std::mutex mux;
    IPlayer(){};
};


#endif //FIRSTPLAYER_IPLAYER_H
