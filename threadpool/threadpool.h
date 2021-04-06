#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
//
// Created by yuejiayuan on 2021/4/4.
//
#include "worker.h"
#include "job.h"
#include "utils.h"
#include <string.h>

typedef struct YThreadpool YThreadpool;
struct YThreadpool {
    YJob* jobs;
    YWorker* workers;

    pthread_cond_t jobs_cond;
    pthread_mutex_t jobs_mutex;
};

typedef void* YThreadpoolCallback(void* arg);

static void* YThreadpool_callback(void* arg) {
    YWorker* worker = (YWorker*)arg;

    while (1) {
        pthread_mutex_lock(&worker->pool->jobs_mutex);

        while (worker->pool->jobs == NULL) {
            if (worker->terminate) break;
            pthread_cond_wait(&worker->pool->jobs_cond
                    , &worker->pool->jobs_mutex);
        }

        if (worker->terminate) {
            pthread_mutex_unlock(&worker->pool->jobs_mutex);
            break;
        }

        YJob* job = worker->pool->jobs;
        YLIST_REMOVE(job, worker->pool->jobs);

        pthread_mutex_unlock(&worker->pool->jobs_mutex);

        job->func(job->data);
    }

    free(worker);
    pthread_exit(NULL);
}

int YThreadpool_create(YThreadpool* pool, int worker_cnt, YThreadpoolCallback cb) {
    printf("threadpool create begin\n");

    if (worker_cnt < 1) worker_cnt = 1;
    memset(pool, 0, sizeof(pool));

    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    memcpy(&pool->jobs_cond, blank_cond, sizeof(blank_cond));

    pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&pool->jobs_mutex, blank_mutex, sizeof(blank_mutex));

    for (int i = 0; i < worker_cnt; i++) {
        YWorker* worker = (YWorker*)malloc(sizeof(YWorker));
        if (worker == NULL) {
            perror("malloc worker failed\n");
            return -1;
        }
        memset(worker, 0, sizeof(YWorker));
        worker->pool = pool;

        int ret = pthread_create(&worker->thread_id, NULL, cb, worker);
        if (ret) {
            perror("pthread_create failed\n");
            free(worker);
            return -1;
        }

        YLIST_ADD(worker, pool->workers);
    }

    printf("threadpool create end\n");
    return 0;
}

void YThreadpool_push(YThreadpool* pool, YJob* job) {
    pthread_mutex_lock(&pool->jobs_mutex);

    if (job) {
        YLIST_ADD(job, pool->jobs);
        pthread_cond_signal(&pool->jobs_cond);
    }

    pthread_mutex_unlock(&pool->jobs_mutex);
}

int YThreadpool_destroy(YThreadpool* pool) {
    printf("threadpool destroy begin\n");

    for (YWorker* worker = pool->workers; worker != NULL; worker = worker->next) {
        worker->terminate = 1;
    }

    pthread_mutex_lock(&pool->jobs_mutex);
    pthread_cond_broadcast(&pool->jobs_cond);
    pthread_mutex_unlock(&pool->jobs_mutex);

    printf("threadpool destroy end\n");
}

#endif
