package com.phj.player;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

/**
 * 窗口的载体，绘制
 * @author phj
 * created at 2018/8/9 17:15
 */

public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback {

    public XPlay(Context context, AttributeSet attrs) {
        super( context,attrs );
    }


    @Override
    public void surfaceCreated(SurfaceHolder var1){
        InitView(var1.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder var1, int var2, int var3, int var4){

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder var1){

    }

    public native void InitView(Object surface);
}
