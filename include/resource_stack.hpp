#pragma once

#include <pthread.h>

class ResourceStack{
    
    private:
        pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;
        long double m_resources = 0;

    public:
        ResourceStack(long double startingResources);
        void addResources(long double amount); 
        bool removeResources(long double amount);    
        void clearResources();
        long double getResources();
};