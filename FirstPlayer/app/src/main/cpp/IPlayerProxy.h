//
// Created by LB on 2018/8/11.
//

#ifndef FIRSTPLAYER_IPLAYERPROXY_H
#define FIRSTPLAYER_IPLAYERPROXY_H



#include "IPlayer.h"
#include <mutex>
class IPlayerProxy: public IPlayer
{
public:
    static IPlayerProxy *Get()
    {
        static IPlayerProxy px;
        return &px;
    }
    virtual double PlayPos();
    virtual bool Seek(double pos);
    void Init(void *vm = 0);
    virtual void Close();
    virtual bool IsPause();
    virtual void SetPause(bool isB);
    virtual bool Open(const char *path);
    virtual bool Start();
    virtual void InitView(void *win);
protected:
    IPlayerProxy(){}
    IPlayer *player = 0;
    std::mutex mux;
};


#endif //FIRSTPLAYER_IPLAYERPROXY_H
