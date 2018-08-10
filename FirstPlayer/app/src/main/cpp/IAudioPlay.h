//
// Created by LB on 2018/8/10.
//

#ifndef FIRSTPLAYER_IAUDIOPLAY_H
#define FIRSTPLAYER_IAUDIOPLAY_H


#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay : public IObserver{
public:
    virtual void Update(XData data);

    virtual bool StartPlay(XParameter out) = 0;

};


#endif //FIRSTPLAYER_IAUDIOPLAY_H
