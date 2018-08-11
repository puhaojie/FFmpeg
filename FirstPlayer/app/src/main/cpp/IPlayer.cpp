//
// Created by LB on 2018/8/11.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IResample.h"
#include "IDecode.h"
#include "IVideoView.h"
#include "IAudioPlay.h"
#include "XLog.h"

IPlayer *IPlayer::Get(unsigned char index){

    static IPlayer p[256];


    return &p[index];
}

bool IPlayer::Open(const char* path){

//    Close();
    mux.lock();
    //解封装
    if(!demux || !demux->Open(path))
    {
        mux.unlock();
        LOGE("demux->Open %s failed!",path);
        return false;
    }

    //解码 解码可能不需要，如果是解封之后就是原始数据
    if(!vdecode || !vdecode->Open(demux->GetVPara(),isHardDecode))
    {
        LOGE("vdecode->Open %s failed!",path);
    }
    if(!adecode || !adecode->Open(demux->GetAPara()))
    {
        LOGE("adecode->Open %s failed!",path);
    }

    //重采样 有可能不需要，解码后或者解封后可能是直接能播放的数据
    if(outPara.sample_rate <= 0)
        outPara = demux->GetAPara();
    if(!resample || !resample->Open(demux->GetAPara(),outPara))
    {
        LOGE("resample->Open %s failed!",path);
    }
    LOGE("IPlayer::Open success %s",path);
    mux.unlock();
    return true;
}

bool IPlayer::Start(){
    mux.lock();

    if(vdecode)
        vdecode->Start();

    if(!demux || !demux->Start())
    {
        mux.unlock();
        LOGE("demux->Start failed!");
        return false;
    }
    if(adecode)
        adecode->Start();
    if(audioPlay)
        audioPlay->StartPlay(outPara);
    XThread::Start();
    mux.unlock();

    return true;
}


void IPlayer::InitView(void *win){
    if(videoView)
    {
        videoView->SetRender(win);
    }
}