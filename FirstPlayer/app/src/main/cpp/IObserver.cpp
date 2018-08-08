//
// Created by LB on 2018/8/8.
//

#include "IObserver.h"

void IObserver::AddObs(IObserver *obs) {
    if (!obs)
        return;
    mux.lock();
    obss.push_back(obs);
    mux.unlock();
}


void IObserver::Notify(XData data) {
    mux.lock();
    for (int i = 0; i < obss.size(); ++i) {
        obss[i]->Update(data);
    }
    mux.unlock();
}