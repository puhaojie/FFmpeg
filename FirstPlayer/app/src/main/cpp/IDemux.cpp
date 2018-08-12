//
// Created by LB on 2018/8/8.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main() {

    while (!isExit){
        if (IsPause()){
            XSleep(2);
            continue;
        }
        XData d = Read();
        if (d.size > 0)
            Notify(d);
        else
            XSleep(2);
//        LOGI("IDemux read size is %d !!", d.size);
    }
}