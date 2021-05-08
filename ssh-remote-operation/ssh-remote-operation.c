#include <stdio.h>

int main() {
    char ssh[512] = {0};
    /* -t: force pseudo-terminal allocation */
    sprintf(ssh, "ssh -t root@10.3.20.70 \"ls -al\"");
    printf("ssh cmd: %s\n", ssh);
    printf("ssh ret: %d\n", system(ssh));
    return 0;
}

