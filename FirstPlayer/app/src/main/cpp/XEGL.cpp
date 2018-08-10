//
// Created by LB on 2018/8/9.
//

#include <android/native_window.h>
#include <EGL/egl.h>
#include "XEGL.h"
#include "XLog.h"

class CXEGL : public XEGL {
public:
    EGLDisplay display = EGL_NO_DISPLAY; // 保存 用于销毁
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    virtual void Draw(){
        if (display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE){
            return;
        }
        eglSwapBuffers(display,surface);
    }

    virtual bool Init(void *win) {
        ANativeWindow *nwin = (ANativeWindow *) win;

        // 1、获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY)
            return false;
        LOGI("eglGetDisplay success");
        // 2、eglInitialize
        if (EGL_TRUE != eglInitialize(display, 0, 0)) {
            return false;
        }
        LOGI("eglInitialize success");

        // 3、获取配置 并创建Surface
        EGLint configSpec[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };
        EGLConfig config = 0;
        EGLint numConfigs = 0;
        if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &numConfigs)) {
            return false;
        }
        LOGI("eglChooseConfig success");
        surface = eglCreateWindowSurface(display, config, nwin, NULL);

        //4、创建并打开EGL上下文
        const EGLint ctxAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
        if (context == EGL_NO_CONTEXT) {
            return false;
        }
        LOGI("eglCreateContext success");
        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            return false;
        }
        LOGI("全部步骤成功 eglMakeCurrent success");
        return true;
    }
};


XEGL *XEGL::Get() {
    static CXEGL egl;
    return &egl;
}