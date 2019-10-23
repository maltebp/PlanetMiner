
#include "gatherer.hpp"

#include <unistd.h>
#include <iostream>

#include "mysleep.hpp"

std::vector<GathererType*> GathererType::allTypes;

void GathererType::resetAllUpgrades(){
    for( GathererType* type : allTypes){
        type->upgradeLevel = 0;
    }
}

GathererType::GathererType(std::string name, std::string commandKey, unsigned int cost, float gatheringAmount, float  gatheringFreq){
    this->name = name; 
    this->commandKey = commandKey;
    this->cost = cost;
    this->gatheringAmount = gatheringAmount;
    this->gatheringFreq = gatheringFreq;
    allTypes.push_back(this); 
}

float GathererType::adjustedGatheringAmount() const{
    float baseAmount = gatheringAmount;
    float upgradeAmount = baseAmount * upgradeLevel * UPGRADE_EFFECT_INC;
    return baseAmount + upgradeAmount;
}


int GathererType::calcUpgradeCost() const{
    float baseCost = cost * UPGRADE_COST_FACTOR;
    float levelCost = (1+ upgradeLevel * UPGRADE_COST_INC_FACTOR);
    return baseCost * levelCost;
}


Gatherer::Gatherer(const GathererType& type, ResourceStack& resourceStack) : m_type(type),  m_resourceStack(resourceStack){
    pthread_create(&m_thread, NULL, threadCallback, this );
}

Gatherer::~Gatherer(){
    std::cout<<"destroying gatherer"<<std::endl;
    pthread_cancel(m_thread);
}

void* Gatherer::threadCallback( void* gathererPtr ){
    ((Gatherer*) gathererPtr)->gatheringLoop();
}

void Gatherer::gatheringLoop(){
    while(true){
        fsleep(m_type.gatheringFreq * m_gatheringSpeed);
        m_resourceStack.addResources(m_type.adjustedGatheringAmount());
    }
}
