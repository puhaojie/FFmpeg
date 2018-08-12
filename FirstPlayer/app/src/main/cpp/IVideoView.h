//
// Created by LB on 2018/8/9.
// 视频播放，为了适配作用的接口

#ifndef FIRSTPLAYER_IVIDEOVIEW_H
#define FIRSTPLAYER_IVIDEOVIEW_H


#include "XData.h"
#include "IObserver.h"

class IVideoView : public IObserver{
public:
    virtual void SetRender(void *win) = 0;
    virtual void Render(XData data) = 0;
    virtual void Update(XData data);
    virtual void Close() = 0;
};


#endif //FIRSTPLAYER_IVIDEOVIEW_H
