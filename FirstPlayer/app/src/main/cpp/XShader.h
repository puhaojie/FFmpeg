//
// Created by LB on 2018/8/9.
//

#ifndef FIRSTPLAYER_XSHADER_H
#define FIRSTPLAYER_XSHADER_H


class XShader {
public:
    virtual bool Init();

    // 获取材质 并映射到内存
    virtual void GetTexture(unsigned int index,int width,int height,unsigned char *buf);

    virtual void Draw();
protected:
    // 保存变量 用于清理
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0}; //材质
};


#endif //FIRSTPLAYER_XSHADER_H
