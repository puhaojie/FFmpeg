//
// Created by LB on 2018/8/8.
//

#ifndef FIRSTPLAYER_IOBSERBER_H
#define FIRSTPLAYER_IOBSERBER_H

#include "XData.h"
#include "vector"
#include "mutex"
#include "XThread.h"

//观察者和主体
class IObserver : public XThread{
public:
    // 更新 子类不一定实现
    virtual void Update(XData data){};

    virtual void AddObs(IObserver *obs);

    virtual void Notify(XData data);

protected:
    std::vector<IObserver*> obss;//集合对象

    std::mutex mux; //互斥变量
};


#endif //FIRSTPLAYER_IOBSERBER_H
