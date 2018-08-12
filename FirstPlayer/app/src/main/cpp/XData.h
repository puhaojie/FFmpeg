//
// Created by LB on 2018/8/8.
//

#ifndef FIRSTPLAYER_XDATA_H
#define FIRSTPLAYER_XDATA_H
enum XDataType // 涉及到释放内存的问题
{
    AVPACKET_TYPE = 0,
    UCHAR_TYPE = 1
};

struct XData {
    int type = 0;
    int pts = 0;
    unsigned char* data = 0;
    unsigned char* datas[8] = {0};
    int size = 0;
    bool isAudio = false; // 默认是视频
    int width = 0;
    int height = 0;
    int format = 0; //软硬解码
    bool Alloc(int size,const char *data=0);
    // 清理工作
    void Drop();
};


#endif //FIRSTPLAYER_XDATA_H
