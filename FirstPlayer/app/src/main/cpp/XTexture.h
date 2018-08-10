//
// Created by LB on 2018/8/9.
// 适配不同平台的材质

#ifndef FIRSTPLAYER_XTEXTURE_H
#define FIRSTPLAYER_XTEXTURE_H


class XTexture {

public:
    static XTexture* Create(); // 接口类
    virtual bool Init(void* win) = 0;
    virtual void Draw(unsigned char *data[],int width,int height) = 0;
};


#endif //FIRSTPLAYER_XTEXTURE_H
