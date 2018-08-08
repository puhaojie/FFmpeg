//
// Created by LB on 2018/8/8.
//

#include "FFDemux.h"
#include "XLog.h"
// 因为FFmpeg是用C写入的所以需要加入extern "C"
extern "C" {
#include "libavformat/avformat.h"
}

//打开文件 或者流媒体
bool FFDemux::Open(const char *url) {
    LOGI("open file %s begin", url);
    int re = avformat_open_input(&ic, url, 0, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        LOGE("open file %s failed, reason %s ", url, buf);
        return false;
    }
    LOGI("open file %s success", url);

    // 读取文件信息
    re = avformat_find_stream_info(ic, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf));
        LOGE("avformat_find_stream_info %s failed, reason %s ", url, buf);
        return false;
    }
    totalMs = (int) ic->duration / (AV_TIME_BASE / 1000); //可能为0
    LOGI("totalMs %d", totalMs);
    return true;
}


//读取一帧数据  数据由调用者清理
XData FFDemux::Read() {
    if (!ic)
        return XData();
    XData d;
    //读取帧数据
    AVPacket *pkt = av_packet_alloc();
    AVFrame *frame = av_frame_alloc();
    int re = av_read_frame(ic, pkt);
    if (re != 0) {
        // 释放空间
        av_packet_free(&pkt);
        return XData();
    }

    d.data = (unsigned char *) pkt;
    d.size = pkt->size;
    return d;
}

FFDemux::FFDemux() {
    static bool isFirst = true;
    if (isFirst) {
        isFirst = false;

        //初始化解封装
        av_register_all();
        //初始化网络
        avformat_network_init();
        // 注册所有的解码器
        avcodec_register_all();
        LOGE("register ffmpeg");
    }
}