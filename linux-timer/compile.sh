#/usr/bin/bash
g++ linux_timer_epoll.c -o linux_timer_epoll -lrt
gcc linux_timer_thread.c -o linux_timer_thread -lrt
