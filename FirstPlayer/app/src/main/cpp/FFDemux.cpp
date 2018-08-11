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
    GetVPara();
    GetAPara();
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

    int re = av_read_frame(ic, pkt);
    if (re != 0) {
        // 释放空间
        av_packet_free(&pkt);
        return XData();
    }

    d.data = (unsigned char *) pkt;
    d.size = pkt->size;
    if (pkt->stream_index == audioStream){
        d.isAudio = true;
    } else if(pkt->stream_index == videoStream){
        d.isAudio = false;
    } else {
        av_packet_free(&pkt);
        return XData();
    }
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

// 获取视频参数
XParameter FFDemux::GetVPara(){
    if (!ic){
        return XParameter();
    }
    // 获取视频流的索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (re < 0){
        return XParameter();
    }
    LOGI("av_find_best_stream  GetVPara XParameter success %d",re);
    videoStream = re;
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    return para;
}

// 获取音频参数
XParameter FFDemux::GetAPara(){
    if (!ic){
        return XParameter();
    }
    // 获取音频流的索引
    int re = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (re < 0){
        return XParameter();
    }
    audioStream = re;
//    LOGI("av_find_best_stream GetAPara XParameter success %d",re);
    XParameter para;
    para.para = ic->streams[re]->codecpar;
    para.sample_rate = ic->streams[re]->codecpar->sample_rate;
    para.channels = ic->streams[re]->codecpar->channels;
    return para;
}