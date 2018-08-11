//
// Created by LB on 2018/8/9.
// 适配不同平台的材质

#ifndef FIRSTPLAYER_XTEXTURE_H
#define FIRSTPLAYER_XTEXTURE_H
enum XTextureType { // 存储格式问题
    XTEXTURE_YUV420P = 0,// Y 4 U 1 V 1
    XTEXTURE_NV12 = 25, // Y 4 UV 1
    XTEXTURE_NV21 = 26  // Y 4 VU 1
};

class XTexture {

public:
    static XTexture* Create(); // 接口类
    virtual bool Init(void* win,XTextureType type = XTEXTURE_YUV420P) = 0;
    virtual void Draw(unsigned char *data[],int width,int height) = 0;
};


#endif //FIRSTPLAYER_XTEXTURE_H
