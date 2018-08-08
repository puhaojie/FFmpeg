//
// Created by LB on 2018/8/8.
//

#ifndef FIRSTPLAYER_XLOG_H
#define FIRSTPLAYER_XLOG_H


class XLog {

};

#ifdef ANDROID
#include <android/log.h>
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"XPlay",__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,"XPlay",__VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,"XPlay",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"XPlay",__VA_ARGS__)

#else
#define LOGD(...) printf("XPlay",__VA_ARGS__)
#define LOGW(...) printf("XPlay",__VA_ARGS__)
#define LOGI(...) printf("XPlay",__VA_ARGS__)
#define LOGE(...) printf("XPlay",__VA_ARGS__)
#endif


#endif //FIRSTPLAYER_XLOG_H
