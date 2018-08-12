//
// Created by LB on 2018/8/10.
//

extern "C"
{
#include <libswresample/swresample.h>
}

#include "XLog.h"
#include <libavcodec/avcodec.h>
#include "FFResample.h"

bool FFResample::Open(XParameter in,XParameter out)
{

    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(out.channels),
                              AV_SAMPLE_FMT_S16,out.sample_rate,
                              av_get_default_channel_layout(in.para->channels),
                              (AVSampleFormat)in.para->format,in.para->sample_rate,
                              0,0 );

    int re = swr_init(actx);
    if(re != 0)
    {
        LOGE("swr_init failed!");
        return false;
    }
    else
    {
        LOGI("swr_init success!");
    }
    // 成功了赋值
    outChannels = in.para->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    return true;

}

XData FFResample::Resample(XData indata)
{
//    LOGE("indata size is %d",indata.size);
    if(indata.size<=0 || !indata.data) return XData();
    if(!actx)
        return XData();
//    LOGE("indata size is %d",indata.size);
    AVFrame *frame = (AVFrame *)indata.data;

    //输出空间的分配
    XData out;
    // 大小 == 通道数 * 单通道样本数 * 样本大小
    int outsize = outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)outFormat);
    if(outsize <=0)return XData();
    out.Alloc(outsize);
    uint8_t *outArr[2] = {0};
    outArr[0] = out.data;
    int len = swr_convert(actx,outArr,frame->nb_samples,(const uint8_t **)frame->data,frame->nb_samples);
    if(len<=0)
    {
        out.Drop();
        return XData();
    }
    out.pts = indata.pts;
//    LOGE("swr_convert success = %d",len);
    return out;
}