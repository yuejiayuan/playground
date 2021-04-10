#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"

#define WORKER_COUNT (5)
#define JOB_COUNT (10)

void job_func(void* data) {
    int job_id = *((int*)data);
    printf("THIS IS JOB #%d\n", job_id);
}

int main() {
    YThreadpool* pool = (YThreadpool*)malloc(sizeof(YThreadpool));
    if (!pool) {
        perror("malloc pool failed\n");
        exit(-1);
    }

    YThreadpool_create(pool, WORKER_COUNT, YThreadpool_callback);

    YJob* job[JOB_COUNT];
    int job_id[JOB_COUNT];
    for (int i = 0; i < JOB_COUNT; i++) {
        job_id[i] = i;
        job[i] = (YJob*)malloc(sizeof(YJob));
        job[i]->func = job_func;
        job[i]->data = &job_id[i];
        YThreadpool_push(pool, job[i]);
    }

    printf("jobs pushed again\n");
    for (int i = 0; i < JOB_COUNT; i++) {
        YThreadpool_push(pool, job[i]);
    }

    _sleep(5000);
    YThreadpool_destroy(pool);
    free(pool);
    for (int i = 0; i < 5; i++) {
        free(job[i]);
    }
    printf("Completed\n");
    return 0;
}
