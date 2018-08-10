//
// Created by LB on 2018/8/9.
//

#ifndef FIRSTPLAYER_XPARAMETER_H
#define FIRSTPLAYER_XPARAMETER_H


struct AVCodecParameters; //既然只作为指针，只处理成申明即可

class XParameter {
public:
    AVCodecParameters *para = 0;
    int channels = 2; //设置通道数 如单声道的情况
    int sample_rate = 44100;//默认的样本率
};


#endif //FIRSTPLAYER_XPARAMETER_H
