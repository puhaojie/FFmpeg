//
// Created by LB on 2018/8/10.
//

#ifndef FIRSTPLAYER_SLAUDIOPLAY_H
#define FIRSTPLAYER_SLAUDIOPLAY_H


#include "IAudioPlay.h"


class SLAudioPlay: public IAudioPlay
{
public:
    virtual bool StartPlay(XParameter out);
    void PlayCall(void *bufq);
    SLAudioPlay();
    virtual ~SLAudioPlay();
protected:
    unsigned char *buf = 0;
};

#endif //FIRSTPLAYER_SLAUDIOPLAY_H
