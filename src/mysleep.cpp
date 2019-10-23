
#include "mysleep.hpp"

void fsleep(float time){
    float dec = time - (int)time;
    long decMs = dec*1000L;
    long decNs = decMs*1000000L;
    struct timespec time1, time2;
    time1.tv_sec = (int) time;
    time1.tv_nsec = decNs;

    nanosleep( &time1, &time2 );
}