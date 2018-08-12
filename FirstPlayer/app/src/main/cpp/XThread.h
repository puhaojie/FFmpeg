//
// Created by LB on 2018/8/8.
//

#ifndef FIRSTPLAYER_XTHREAD_H
#define FIRSTPLAYER_XTHREAD_H
//SLEEP (毫秒级别)
void XSleep(int mis);


// 使用C++11的线程库实现
class XThread {
public:
    // 启动线程
    virtual bool Start();

    virtual void SetPause(bool isP);
    // 通过控制isExit安全停止线程（不一定成功）
    virtual void Stop();

    virtual bool IsPause()
    {
        isPausing = isPause;
        return isPause;
    }

    // 入口主函数
    virtual void Main(){} // 子类不一定实现这个函数，所以不写成程序函数
protected:
    bool isRunning = false;//是否正在运行
    bool isExit = false;//是否停止
    bool isPause = false;
    bool isPausing = false;
private:
    void ThreadMain();
};


#endif //FIRSTPLAYER_XTHREAD_H
