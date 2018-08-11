//
// Created by LB on 2018/8/9.
//

#include "XEGL.h"
#include "XShader.h"
#include "XTexture.h"

class CXTexture : public XTexture {
public:
    XShader sh;
    XTextureType textureType = XTEXTURE_YUV420P;

    // 初始化 关联EGL Shader
    virtual bool Init(void *win, XTextureType type) {
        if (!win) {
            return false;
        }
        if (!XEGL::Get()->Init(win)) {
            return false;
        }
        sh.Init((XShaderType) type);
        textureType = type;
        return true;
    }

    virtual void Draw(unsigned char *data[], int width, int height) {
        sh.GetTexture(0, width, height, data[0]); // y
        if (textureType == XTEXTURE_YUV420P) {
            sh.GetTexture(1, width / 2, height / 2, data[1], false); // u
            sh.GetTexture(2, width / 2, height / 2, data[2], false); // v
        } else {
            sh.GetTexture(1, width / 2, height / 2, data[1], true); // u
        }

        sh.Draw();

        XEGL::Get()->Draw();
    }
};


XTexture *XTexture::Create() {

    return new CXTexture();
}
