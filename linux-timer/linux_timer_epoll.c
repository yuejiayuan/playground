#include <sys/timerfd.h>  
#include <sys/epoll.h>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <sys/syscall.h>
using namespace std;

const int EPOLL_SIZE = 10;

int main(int argc, char* argv[])
{
    int tfd, epfd, nfds;
    struct epoll_event event;
    struct epoll_event events[EPOLL_SIZE];
        
    //创建timerfd， CLOCK_REALTIME为绝对时间，TFD_NONBLOCK为非阻塞
    tfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK);  
    if (tfd < 0)
    {
        cerr << "timerfd_create error!" << endl;
        return -1;
    }   
    struct timespec startTime, intervalTime;
    startTime.tv_sec = 0;    
    startTime.tv_nsec = 1;                                //相当于立即到达超时时间
    intervalTime.tv_sec = 3;                             //首次超时后，每三秒超时一次
    intervalTime.tv_nsec = 0;
    struct itimerspec newValue;
    newValue.it_value = startTime;
    newValue.it_interval = intervalTime;
    //设置超时时间，且为相对时间
    if (timerfd_settime(tfd, 0, &newValue, NULL) < 0)
    {
        cerr << "timerfd_settime error!" << endl;
        return -1;
    }
    //用epoll来监听描述符
    epfd = epoll_create(EPOLL_SIZE);
    if (epfd < 0)
    {
        cerr << "epoll_create error!" << endl;
        return -1;
    }

    event.data.fd = tfd;
    event.events = EPOLLIN;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, tfd, &event) < 0)
    {
        cerr << "epoll_ctl error!" << endl;
        return -1;
    }
    
    uint64_t count = 0;
    while (1)
    {
        printf("[THREAD_%5lu] Main Loop...\n", syscall(SYS_gettid));
	usleep(200*1000);  // 0.2秒
        //非阻塞等待
        nfds = epoll_wait(epfd, events, EPOLL_SIZE, 0);
        if (nfds == 0) continue;
        for (int i = 0; i < nfds; i++)
        {
            if (events[i].events & EPOLLIN)
            {
                uint64_t data;
                read(events[i].data.fd, &data, sizeof(uint64_t));
                count += data;
                //cout << "read: " << data << ", timer count: " << count << endl;
                printf("[THREAD_%5lu] read: %lu, timer count: %lu\n", syscall(SYS_gettid), data, count);
            }
        }
    }
    return 0;
}
