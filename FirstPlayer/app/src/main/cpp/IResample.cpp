//
// Created by LB on 2018/8/10.
//
#include "IResample.h"

void IResample::Update(XData data)
{
    XData d = this->Resample(data);
    if(d.size > 0)
    {
        this->Notify(d);
    }
}