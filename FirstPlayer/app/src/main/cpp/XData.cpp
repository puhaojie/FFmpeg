//
// Created by LB on 2018/8/8.
//

#include <cstdlib>
extern "C"{
    #include <libavformat/avformat.h>
}

#include "XData.h"

bool XData::Alloc(int size,const char *d)
{
    Drop();
    type = UCHAR_TYPE;
    if(size <=0)return false;
    this->data = new unsigned char[size];
    if(!this->data) return false;
    if(d)
    {
        memcpy(this->data, d, size);
    }
    this->size = size;
    return true;
}

// 清理
void XData::Drop()
{
    if (!data )
        return;
    if(type == AVPACKET_TYPE)
        av_packet_free((AVPacket **)&data);
    else
        delete data;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}