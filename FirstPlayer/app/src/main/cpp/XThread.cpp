//
// Created by LB on 2018/8/8.
//

#include "XThread.h"
#include "thread"
#include "XLog.h"

using namespace std;

// 毫秒级别的sleep
void XSleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

void XThread::SetPause(bool isP)
{
    isPause = isP;
    //等待100毫秒
    for(int i = 0; i < 10; i++)
    {
        if(isPausing == isP)
        {
            break;
        }
        XSleep(10);
    }

}

bool XThread::Start() {
    isExit = false;
    isPause = false;
    // 创建一个线程
    thread th(&XThread::ThreadMain, this);
    th.detach();//放弃对线程的控制
    return true;
}

void XThread::ThreadMain() {
    isRunning = true;
    LOGI("线程函数进入");
    Main();
    LOGI("线程函数退出");
    isRunning = false;
}

void XThread::Stop() {
    isExit = true;
    for (int i = 0; i < 100; ++i) {
        if (!isRunning){
            LOGI("停止线程成功");
            return;
        }
        XSleep(1);
    }
    LOGI("停止线程超时");
}