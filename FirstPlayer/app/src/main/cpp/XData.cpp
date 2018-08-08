//
// Created by LB on 2018/8/8.
//

#include <cstdlib>
extern "C"{
    #include <libavformat/avformat.h>
}

#include "XData.h"

// 清理
void XData::Drop()
{
    if (!data )
        return;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}