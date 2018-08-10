//
// Created by LB on 2018/8/9.
//

#ifndef FIRSTPLAYER_GLVIDEOVIEW_H
#define FIRSTPLAYER_GLVIDEOVIEW_H


#include "XData.h"
#include "IVideoView.h"

class XTexture; //申明


class GLVideoView : public IVideoView {
public:
    virtual void SetRender(void *win);

    virtual void Render(XData data);

protected:
    void * view = 0; // 窗体
    XTexture *txt = 0;
};


#endif //FIRSTPLAYER_GLVIDEOVIEW_H
