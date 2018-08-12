//
// Created by LB on 2018/8/9.
//

#include <android/native_window.h>
#include <EGL/egl.h>
#include <mutex>
#include "XEGL.h"
#include "XLog.h"

class CXEGL : public XEGL {
public:
    EGLDisplay display = EGL_NO_DISPLAY; // 保存 用于销毁
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;
    std::mutex mux;

    virtual void Draw(){
        mux.lock();
        if(display == EGL_NO_DISPLAY || surface == EGL_NO_SURFACE)
        {
            mux.unlock();
            return;
        }
        eglSwapBuffers(display,surface);
        mux.unlock();
    }

    virtual void Close()
    {
        mux.lock();
        if(display == EGL_NO_DISPLAY)
        {
            mux.unlock();
            return;
        }
        eglMakeCurrent(display,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);

        if(surface != EGL_NO_SURFACE)
            eglDestroySurface(display,surface);
        if(context != EGL_NO_CONTEXT)
            eglDestroyContext(display,context);

        eglTerminate(display);

        display = EGL_NO_DISPLAY;
        surface = EGL_NO_SURFACE;
        context = EGL_NO_CONTEXT;
        mux.unlock();
    }

    virtual bool Init(void *win) {
        ANativeWindow *nwin = (ANativeWindow *) win;
        Close();
        //初始化EGL
        mux.lock();
        // 1、获取EGLDisplay对象 显示设备
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY)
        {
            mux.unlock();
            return false;
        }

        LOGI("eglGetDisplay success");
        // 2、eglInitialize
        if (EGL_TRUE != eglInitialize(display, 0, 0)) {
            mux.unlock();
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
            mux.unlock();
            return false;
        }
        LOGI("eglChooseConfig success");
        surface = eglCreateWindowSurface(display, config, nwin, NULL);

        //4、创建并打开EGL上下文
        const EGLint ctxAttr[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};
        context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
        if (context == EGL_NO_CONTEXT) {
            mux.unlock();
            return false;
        }
        LOGI("eglCreateContext success");
        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            mux.unlock();
            return false;
        }
        mux.unlock();
        LOGI("全部步骤成功 eglMakeCurrent success");
        return true;
    }
};


XEGL *XEGL::Get() {
    static CXEGL egl;
    return &egl;
}