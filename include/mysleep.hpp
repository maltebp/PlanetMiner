#pragma once

#include <time.h>

void fsleep(float time){
    float dec = time - (int)time;
    long decL = ((long) (dec*1000)) * 1000L; 
    struct timespec time1, time2;
    time1.tv_sec = (int) time;
    time2.tv_nsec = decL; 
    nanosleep( &time1, &time2 );
}