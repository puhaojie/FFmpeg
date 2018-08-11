//
// Created by LB on 2018/8/9.
//
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavcodec/jni.h>
}

#include "FFDecode.h"

void FFDecode::InitHard(void *vm) {
    av_jni_set_java_vm(vm,0);
}

// 打开解码器
bool FFDecode::Open(XParameter para,bool isHard) {

    if (!para.para) return false;
    AVCodecParameters *p = para.para;

    //1、查找解码器
    AVCodec *cd = NULL;

    LOGI("avcodec_find_decoder %d success", p->codec_id);
    if (isHard){
        cd = avcodec_find_decoder_by_name("h264_mediacodec");
        if (!cd) {
            cd = avcodec_find_decoder(p->codec_id);
        }
    } else {
        cd = avcodec_find_decoder(p->codec_id);
    }
    if (!cd) {
        LOGE("avcodec_find_decoder %d failed", p->codec_id);
        return false;
    }
    //2、创建解码上下文
    //解码器初始化
    codec = avcodec_alloc_context3(cd);
    // 复制参数
    avcodec_parameters_to_context(codec, p);
    codec->thread_count = 8; //8线程解码
    int re = avcodec_open2(codec, 0, 0);
    if (re != 0) {
        char buf[1024] = {0};
        av_strerror(re, buf, sizeof(buf) - 1);
        LOGE("avcodec_open2 failed");
        return false;
    }
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO){
        isAudio = false;
    } else if (codec->codec_type == AVMEDIA_TYPE_AUDIO){
        isAudio = true;
    }
    LOGI("avcodec_open2  success；isAudio = %d",isAudio);
    return true;
}

// 发送包给线程解码
bool FFDecode::SendPackage(XData pkt) {
    if (pkt.size <= 0 || !pkt.data) return false;

    if (!codec) { // 可能存在多线程访问的现象
        return false;
    }
    int re = avcodec_send_packet(codec, (const AVPacket *) pkt.data);
    if (re != 0) {
        LOGE("avcodec_send_packet failed");
        return false;
    }
    return true;
}

//从线程中获取解码结果
XData FFDecode::RecvFrame() {
    if (!codec) { // 可能存在多线程访问的现象
        return XData();
    }
    if (!frame) { // frame作为成员变量
        frame = av_frame_alloc();
    }

    int re = avcodec_receive_frame(codec, frame);
    if (re != 0) {
//        char buf[1024] = {0};
//        av_strerror(re,buf, sizeof(buf)-1);
//        LOGE("avcodec_receive_frame failed %d %s",re,buf);
        return XData();
    }
    XData d;
    d.data = (unsigned char *) frame;
    if (codec->codec_type == AVMEDIA_TYPE_VIDEO) //判断视频
    {
        d.size = (frame->linesize[0]+frame->linesize[1]+frame->linesize[2])*(frame->height);
        d.width = frame->width;
        d.height = frame ->height;
    }
    else {
        d.size = av_get_bytes_per_sample((AVSampleFormat) frame->format) * frame->nb_samples * 2; //样本字节数*单通道样本数*通道数
    }
    d.format = frame->format;
    if (!isAudio)
        LOGE("data format is %d",frame->format);

    memcpy(d.datas,frame->data, sizeof(d.datas));
    return d;
}


