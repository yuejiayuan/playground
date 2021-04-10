#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"

#define WORKER_COUNT (5)
#define JOBS1_COUNT (8)
#define JOBS2_COUNT (18)

void printjobs_test(YThreadpool* pool);

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

    printjobs_test(pool);

    YThreadpool_destroy(pool);
    free(pool);

    printf("All Completed!\n");
    return 0;
}

void printjobs_test(YThreadpool* pool) {
    printf("multijobs_test() starts\n");

    YJob* jobs1[JOBS1_COUNT];
    int jobs1_id[JOBS1_COUNT];
    for (int i = 0; i < JOBS1_COUNT; i++) {
        jobs1_id[i] = i;
        jobs1[i] = (YJob*)malloc(sizeof(YJob));
        jobs1[i]->func = job_func;
        jobs1[i]->data = &jobs1_id[i];
        YThreadpool_push(pool, jobs1[i]);
    }

    printf("jobs pushed again\n");
    YJob* jobs2[JOBS2_COUNT];
    int jobs2_id[JOBS2_COUNT];
    for (int i = 0; i < JOBS2_COUNT; i++) {
        jobs2_id[i] = 100 + i;  // 便于区分
        jobs2[i] = (YJob*)malloc(sizeof(YJob));
        jobs2[i]->func = job_func;
        jobs2[i]->data = &jobs2_id[i];
        YThreadpool_push(pool, jobs2[i]);
    }

    _sleep(5000);

    for (int i = 0; i < JOBS1_COUNT; i++) {
        free(jobs1[i]);
    }
    for (int i = 0; i < JOBS2_COUNT; i++) {
        free(jobs2[i]);
    }
    printf("multijobs_test() completed\n");
}
