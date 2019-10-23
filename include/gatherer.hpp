#pragma once

#include <pthread.h>
#include <string>
#include <vector>

#include "resource_stack.hpp"


const float UPGRADE_EFFECT_INC = 0.2;
const float UPGRADE_COST_FACTOR = 1;
const float UPGRADE_COST_INC_FACTOR = 1.5;

class GathererType{

    public:
        static std::vector<GathererType*> allTypes;
        static void resetAllUpgrades();

    public:
        std::string name;
        std::string commandKey;
        unsigned int cost;
        float gatheringAmount;
        float gatheringFreq;
        unsigned int upgradeLevel = 0;
        
        GathererType(std::string name, std::string commandKey, unsigned int cost, float gatheringAmount, float gatheringFreq);
        void upgrade();
        float adjustedGatheringAmount() const;
        int calcUpgradeCost() const;
};

///=(($C$15/$D$15)*(1+$B$10*(B$18)))/$B$15
// -((($C$14*($B$10*(C$17)))/$D$14)*($A18))/($B$14*$B$11*(1+$B$10*(B$17-1)))


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
    50,
    1,
    1
);


const GathererType TYPE_ADVANCED_BOT(
    "Advanced Bot",
    "ab",
    1250,
    14,
    0.5
);

const GathererType TYPE_TURBO_MINER(
    "Turbo Miner 1000",
    "tm",
    5000,
    13,
    0.1
);

const GathererType TYPE_BOMB_MINER(
    "Bomb Miner",
    "bm",
    25000,
    3000,
    4
);

const GathererType TYPE_DYNA_MINER(
    "Dyna-Miner",
    "dm",
    125000,
    425,
    0.1
);
