//
// Created by LB on 2018/8/9.
//

#ifndef FIRSTPLAYER_XPARAMETER_H
#define FIRSTPLAYER_XPARAMETER_H


struct AVCodecParameters; //既然只作为指针，只处理成申明即可

class XParameter {
public:
    AVCodecParameters *para = 0;
};


#endif //FIRSTPLAYER_XPARAMETER_H
