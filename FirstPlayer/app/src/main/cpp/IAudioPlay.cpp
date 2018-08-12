//
// Created by LB on 2018/8/10.
//

#include "IAudioPlay.h"
#include "XLog.h"
void IAudioPlay::Clear()
{
    framesMutex.lock();
    while(!frames.empty())
    {
        frames.front().Drop();
        frames.pop_front();
    }
    framesMutex.unlock();
}

XData IAudioPlay::GetData()
{
    XData d;

    isRunning = true;
    while(!isExit)
    {
        if (IsPause()){
            XSleep(2);
            continue;
        }
        framesMutex.lock();
        if(!frames.empty())
        {
            d = frames.front();
            frames.pop_front();
            framesMutex.unlock();
            pts = d.pts;
            return d;
        }
        framesMutex.unlock();
        XSleep(1);
    }
    isRunning = false;
    return d;
}
void IAudioPlay::Update(XData data)
{
//    LOGE("IAudioPlay::Update %d",data.size);
    //压入缓冲队列
    if(data.size<=0|| !data.data) return;
    while(!isExit)
    {
        framesMutex.lock();
        if(frames.size() > maxFrame)
        {
            framesMutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesMutex.unlock();
        break;
    }
}