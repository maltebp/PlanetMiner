#pragma once

#include <pthread.h>
#include <string>
#include <vector>

#include "resource_stack.hpp"


const float UPGRADE_EFFECT_INC = 0.1;
const float UPGRADE_COST_FACTOR = 10;
const float UPGRADE_COST_INC_FACTOR = 2;

class GathererType{

    public:
        static std::vector<GathererType*> allTypes;
        static void resetAllUpgrades();

    public:
        std::string name;
        std::string commandKey;
        unsigned int cost;
        float gatheringAmount;
        unsigned int gatheringFreq;
        unsigned int upgradeLevel = 0;
        
        GathererType(std::string name, std::string commandKey, unsigned int cost, float gatheringAmount, unsigned int gatheringFreq);
        void upgrade();
};



class Gatherer{

    private:
        /* This prevents you from copying the gatherer, meaning it can only
            be passed by reference */
        Gatherer(Gatherer*);

        pthread_t m_thread;
        const GathererType& m_type;
        ResourceStack& m_resourceStack;

        float m_gatheringEffect = 1;
        float m_gatheringSpeed = 1;
        
        void gatheringLoop();

        static void* threadCallback( void* arg );

    public:
        Gatherer(const GathererType& type, ResourceStack& resourceStack);
        ~Gatherer();
};


const GathererType TYPE_SIMPLE_BOT(
    "Simple Bot",
    "sb",
    15,
    5,
    3
);
