//
// Created by LB on 2018/8/8.
//

#ifndef FIRSTPLAYER_XDATA_H
#define FIRSTPLAYER_XDATA_H


struct XData {
    unsigned char* data = 0;
    int size = 0;
    // 清理工作
    void Drop();
};


#endif //FIRSTPLAYER_XDATA_H
