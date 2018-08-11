//
// Created by LB on 2018/8/9.
// 作为音视频解码

#ifndef FIRSTPLAYER_IDECODE_H
#define FIRSTPLAYER_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"
#include <list>

// 解码接口 支持硬解码
class IDecode : public IObserver {
public:
    // 打开解码器 (默认不打开硬解码)
    virtual bool Open(XParameter para,bool isHard = false) = 0;

    // 如果缓冲队列缓冲满了，则阻塞
    virtual void Update(XData data);

    //future模型
    //发送包到线程解码（不是立刻解码）
    virtual bool SendPackage(XData pkt) = 0;

    //从线程中获取解码结果
    virtual XData RecvFrame() = 0;

    bool isAudio = false; //因为对FFmpeg不可见，设置一个bool

    int maxList = 200; //设置缓冲队列中的最大数量

protected:
    virtual void Main();//入口函数

    // 存放所有的缓冲帧
    std::list<XData> packs;

    // 因为是生产者和消费者模型 添加互斥变量
    std::mutex packsMutex;
};


#endif //FIRSTPLAYER_IDECODE_H
