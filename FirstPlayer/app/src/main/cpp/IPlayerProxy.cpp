//
// Created by LB on 2018/8/11.
//


#include "FFPlayerBuilder.h"
#include "IPlayerProxy.h"

void IPlayerPorxy::Init(void *vm) {
    mux.lock();
    if (vm) {
        FFPlayerBuilder::InitHard(vm);
    }
    if (!player)
        player = FFPlayerBuilder::Get()->BuilderPlayer();

    mux.unlock();
}


bool IPlayerPorxy::Open(const char *path) {
    bool re = false;
    mux.lock();
    if (player) {
        player->isHardDecode = isHardDecode;
        re = player->Open(path);
    }

    mux.unlock();
    return re;
}

bool IPlayerPorxy::Start() {
    bool re = false;
    mux.lock();
    if (player)
        re = player->Start();
    mux.unlock();
    return re;
}

void IPlayerPorxy::InitView(void *win) {
    mux.lock();
    if (player)
        player->InitView(win);
    mux.unlock();
}