#pragma once

#include <pthread.h>
#include <string>
#include "resource_stack.hpp"


typedef struct{
    std::string name;
    unsigned int cost;
    float gatheringAmount;
    unsigned int gatheringFreq;
} GathererType;


class Gatherer{

    private:
        /* This prevents you from copying the gatherer, meaning it can only
            be passed by reference */
        Gatherer(Gatherer*);

        pthread_t m_thread;
        const GathererType& m_type;
        const ResourceStack& m_resourceStack;

        float m_gatheringEffect = 1;
        float m_gatheringSpeed = 1;
        
        void gatheringLoop();

        static void* threadCallback( void* arg );

    public:
        Gatherer(const GathererType& type, ResourceStack& resourceStack);
        ~Gatherer();
};


const GathererType TYPE_SIMPLE_BOT = {
    .name = "Simple Bot",
    .cost = 100,
    .gatheringAmount = 10,
    .gatheringFreq = 5
};
