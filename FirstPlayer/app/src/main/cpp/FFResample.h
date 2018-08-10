//
// Created by LB on 2018/8/10.
//

#ifndef FIRSTPLAYER_FFRESAMPLE_H
#define FIRSTPLAYER_FFRESAMPLE_H



#include "IResample.h"
struct SwrContext;
class FFResample : public IResample{
public:
    virtual bool Open(XParameter in,XParameter out=XParameter());
    virtual XData Resample(XData indata);
protected:
    SwrContext *actx = 0;
};


#endif //FIRSTPLAYER_FFRESAMPLE_H
