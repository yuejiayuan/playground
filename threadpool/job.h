#ifndef __JOB_H__
#define __JOB_H__
//
// Created by yuejiayuan on 2021/4/4.
//

typedef struct YJob YJob;
struct YJob {
    void (*func)(void* data);
    void* data;

    YJob* prev;
    YJob* next;
};
#endif


