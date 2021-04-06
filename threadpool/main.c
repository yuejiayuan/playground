#include <stdio.h>
#include <stdlib.h>
#include "threadpool.h"




int main() {
    YThreadpool* pool = (YThreadpool*)malloc(sizeof(YThreadpool));
    if (pool == NULL) {
        perror("malloc pool failed\n");
        exit(-1);
    }

    YThreadpool_create(pool, 5, YThreadpool_callback);

    YThreadpool_destroy(pool);

    free(pool);

    printf("Completed\n");
    return 0;
}
