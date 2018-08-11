//
// Created by LB on 2018/8/10.
//

#include "IAudioPlay.h"
#include "XLog.h"

void IAudioPlay::Update(XData data){
    LOGE("IAudioPlay::Update data size %d",data.size);
    // 压入到缓冲队列（类似视频）
    if (data.size <= 0 || !data.data)
        return;

    while (!isExit){
        framesMutex.lock();
        if (frames.size() > maxFrame)
        {
            framesMutex.unlock();
            XSleep(2);
            continue;
        }
        frames.push_back(data);
        framesMutex.unlock();
        break;
    }


};