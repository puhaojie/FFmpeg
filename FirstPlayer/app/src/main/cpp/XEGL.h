//
// Created by LB on 2018/8/9.
//

#ifndef FIRSTPLAYER_XEGL_H
#define FIRSTPLAYER_XEGL_H


class XEGL {
public:
    virtual bool Init(void *win) = 0;

    static XEGL *Get();
protected:
    // 单例模式
    XEGL(){}
};


#endif //FIRSTPLAYER_XEGL_H
