#include <unistd.h>
#include <time.h>

int gettimeofday(struct timeval *tv,struct timezone *tz){
    (void)tz; // TODO : timezone support
    struct timespec ts;
    int ret = clock_gettime(CLOCK_REALTIME,&ts);
    if(ret < 0)return ret;
    if(tv){
        tv->tv_sec  = ts.tv_sec;
        tv->tv_usec = ts.tv_nsec / 1000;
    }
    return 0;
}
