//
// Created by LB on 2018/8/9.
//

#include "GLVideoView.h"
#include "XTexture.h"

void GLVideoView::SetRender(void *win){
    view = win;
}


void GLVideoView::Render(XData data){

    if (!view)
        return;
    if (!txt){
        txt = XTexture::Create();
        txt->Init(view); // 第一次需要进行初始化
    }
    txt->Draw(data.datas,data.width,data.height);
}