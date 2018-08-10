//
// Created by LB on 2018/8/10.
//

#ifndef FIRSTPLAYER_IRESAMPLE_H
#define FIRSTPLAYER_IRESAMPLE_H


#include "XParameter.h"
#include "IObserver.h"

class IResample : public IObserver{
public:
    virtual bool Open(XParameter in,XParameter out=XParameter()) = 0;
    virtual XData Resample(XData indata) = 0; // 重采样出来的数据
    virtual void Update(XData data);
    int outChannels = 2;
    int outFormat = 1;
};


#endif //FIRSTPLAYER_IRESAMPLE_H
