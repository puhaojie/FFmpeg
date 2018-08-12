//
// Created by LB on 2018/8/11.
//


#include "FFPlayerBuilder.h"
#include "IPlayerProxy.h"
void IPlayerProxy::Close()
{
    mux.lock();
    if(player)
        player->Close();
    mux.unlock();
}
void IPlayerProxy::Init(void *vm) {
    mux.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!player)
        player = FFPlayerBuilder::Get()->BuilderPlayer();

    mux.unlock();
}
//获取当前的播放进度 0.0 ~ 1.0
double IPlayerProxy::PlayPos()
{
    double pos = 0.0;
    mux.lock();
    if(player)
    {
        pos = player->PlayPos();
    }
    mux.unlock();
    return pos;
}
bool IPlayerProxy::Seek(double pos)
{
    bool re = false;
    mux.lock();
    if(player)
    {
        re = player->Seek(pos);
    }
    mux.unlock();
    return re;
}

void IPlayerProxy::SetPause(bool isP)
{
    mux.lock();
    if(player)
        player->SetPause(isP);
    mux.unlock();
}

bool IPlayerProxy::IsPause()
{
    bool re = false;
    mux.lock();
    if(player)
        re = player->IsPause();
    mux.unlock();
    return re;
}

bool IPlayerProxy::Open(const char *path) {
    bool re = false;
    mux.lock();
    if (player) {
        player->isHardDecode = isHardDecode;
        re = player->Open(path);
    }

    mux.unlock();
    return re;
}

bool IPlayerProxy::Start() {
    bool re = false;
    mux.lock();
    if (player)
        re = player->Start();
    mux.unlock();
    return re;
}

void IPlayerProxy::InitView(void *win) {
    mux.lock();
    if (player)
    {

        player->InitView(win);
    }
    mux.unlock();
}