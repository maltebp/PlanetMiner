#pragma once

#include <time.h>
#include <iostream>

void fsleep(float time){
    float dec = time - (int)time;
    long decL = ((long) (dec*1000)) * 1000L; 
    struct timespec time1, time2;
    time1.tv_sec = (int) time;
    time2.tv_nsec = decL;
    
    std::cout<<"Ms: "<<decL/1000000.<<std::endl;

    nanosleep( &time1, &time2 );
}