//
// Created by LB on 2018/8/10.
//

#ifndef FIRSTPLAYER_IAUDIOPLAY_H
#define FIRSTPLAYER_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver{
public:
    // 缓冲满之后阻塞
    virtual void Update(XData data);

    virtual bool StartPlay(XParameter out) = 0;

    int maxFrame =100;// 最大缓冲
protected:
    std::list <XData> frames;// 缓冲队列
    std::mutex framesMutex; //音频互斥队列
};


#endif //FIRSTPLAYER_IAUDIOPLAY_H
