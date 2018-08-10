//
// Created by LB on 2018/8/9.
//

#include "XEGL.h"
#include "XShader.h"
#include "XTexture.h"

class CXTexture: public XTexture{
public:
    XShader sh;

    // 初始化 关联EGL Shader
    virtual bool Init(void* win){
        if (!win){
            return false;
        }
        if (!XEGL::Get()->Init(win)){
            return false;
        }
        sh.Init();
        return true;
    }

    virtual void Draw(unsigned char *data[],int width,int height){
        sh.GetTexture(0,width,height,data[0]); // y
        sh.GetTexture(1,width/2,height/2,data[1]); // u
        sh.GetTexture(2,width/2,height/2,data[2]); // v
        sh.Draw();

        XEGL::Get()->Draw();
    }
};


XTexture *XTexture::Create(){

    return new CXTexture();
}
