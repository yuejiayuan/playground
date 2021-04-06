#ifndef __WORKER_H__
#define __WORKER_H__
//
// Created by yuejiayuan on 2021/4/4.
//
#include <pthread.h>

struct YThreadpool;
typedef struct YWorker YWorker;
struct YWorker {
    pthread_t thread_id;
    struct YThreadpool* pool;
    int terminate;

    YWorker* prev;
    YWorker* next;
};

#endif
