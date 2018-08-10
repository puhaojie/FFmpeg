//
// Created by LB on 2018/8/9.
//

#include "IDecode.h"
#include "XLog.h"


void IDecode::Update(XData data) {
    if (data.size == 0)
        return;
    if (data.isAudio != isAudio) {
        return;
    }

    while (!isExit){
        packsMutex.lock();
        // 多了则阻塞
        if (packs.size() < maxList) {
            packs.push_back(data);
            packsMutex.unlock();
            break;
        }
        packsMutex.unlock();
        XSleep(1);
    }

}

void IDecode::Main() {

    while (!isExit){
        packsMutex.lock();
        if (packs.empty()){
            packsMutex.unlock();
            XSleep(1);
            continue;
        }
        XData pack = packs.front();
        packs.pop_front();
        // 发送数据到解码线程
        if (SendPackage(pack)){
            // 获取解码数据 (一个数据包可能会解码出多个结果)
            while (!isExit){
                XData frame = RecvFrame();
                if (!frame.data) //读不到数据的时候 返回
                    break;
//                LOGI(" 大小 %d",frame.size);
                this->Notify(frame);
            }
        }
        // 自己进行清理工作
        pack.Drop();
        packsMutex.unlock();
    }
}