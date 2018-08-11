//
// Created by LB on 2018/8/9.
//

#ifndef FIRSTPLAYER_XSHADER_H
#define FIRSTPLAYER_XSHADER_H
enum XShaderType {
    XSHADER_YUV420P =0,// Y 4 U 1 V 1
    XSHADER_NV12 = 25, // Y 4 UV 1
    XSHADER_NV21 = 26  // Y 4 VU 1
};

class XShader {
public:
    virtual bool Init(XShaderType type = XSHADER_YUV420P);

    // 获取材质 并映射到内存
    virtual void GetTexture(unsigned int index,int width,int height,unsigned char *buf,bool isa = false);

    virtual void Draw();
protected:
    // 保存变量 用于清理
    unsigned int vsh = 0;
    unsigned int fsh = 0;
    unsigned int program = 0;
    unsigned int texts[100] = {0}; //材质
};


#endif //FIRSTPLAYER_XSHADER_H
