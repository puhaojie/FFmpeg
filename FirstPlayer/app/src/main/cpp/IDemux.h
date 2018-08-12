//
// Created by LB on 2018/8/8.
//

#ifndef FIRSTPLAYER_IDEMUX_H
#define FIRSTPLAYER_IDEMUX_H

#include "XData.h"
#include "XThread.h"
#include "IObserver.h"
#include "XParameter.h"

// 解封装接口
class IDemux : public IObserver
{
public:
    //打开文件 或者流媒体
    virtual bool Open(const char *url) = 0; //后面加0 位程序函数 接口的定义
    virtual void Close() = 0;
    // 获取视频参数
    virtual XParameter GetVPara() = 0;

    // 获取音频参数
    virtual XParameter GetAPara() = 0;

    //读取一帧数据  数据由调用者清理
    virtual XData Read() = 0;

    //总时长（毫秒）
    int totalMs = 0;

protected:
    virtual void Main(); // 不让用户访问
};


#endif //FIRSTPLAYER_IDEMUX_H
