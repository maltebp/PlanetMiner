
#include "gatherer.hpp"

#include <unistd.h>
#include <iostream>

std::vector<GathererType*> GathererType::allTypes;

void GathererType::resetAllUpgrades(){
    for( GathererType* type : allTypes){
        type->upgradeLevel = 0;
    }
}

GathererType::GathererType(std::string name, std::string commandKey, unsigned int cost, float gatheringAmount, unsigned int gatheringFreq){
    this->name = name; 
    this->commandKey = commandKey;
    this->cost = cost;
    this->gatheringAmount = gatheringAmount;
    this->gatheringFreq = gatheringFreq;
    allTypes.push_back(this); 
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
        sleep(m_type.gatheringFreq * m_gatheringSpeed);
        float baseAmount = m_type.gatheringAmount;
        float upgradeAmount = baseAmount * m_type.upgradeLevel * UPGRADE_EFFECT_INC;
        m_resourceStack.addResources( baseAmount + upgradeAmount);
    }
}
