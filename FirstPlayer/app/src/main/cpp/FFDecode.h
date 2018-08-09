//
// Created by LB on 2018/8/9.
// ffmpeg的解码实现类

#ifndef FIRSTPLAYER_FFDECODE_H
#define FIRSTPLAYER_FFDECODE_H


#include "IDecode.h"
#include "XLog.h"

struct AVCodecContext;
struct AVFrame;
class FFDecode : public IDecode{
public:
    // 打开解码器
    virtual bool Open(XParameter para);

//    virtual void Update(XData data);

    //future模型
    //发送包到线程解码（不是立刻解码）
    virtual bool SendPackage(XData pkt);

    //从线程中获取解码结果 再次调佣会复用上次空间 线程不安全
    virtual XData RecvFrame();

protected:

    AVCodecContext *codec  = 0;
    AVFrame *frame = 0;
};


#endif //FIRSTPLAYER_FFDECODE_H
