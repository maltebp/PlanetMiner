#include "resource_stack.hpp"



ResourceStack::ResourceStack(float startingResources){
    m_resources = startingResources;
}

void ResourceStack::addResources(float amount){
    m_resources += amount;    
}

bool ResourceStack::removeResources(float amount){
    if(m_resources >= amount){
        m_resources -= amount;
        return true;
    }
    return false;
}

void ResourceStack::clearResources(){
    m_resources = 0;
}

float ResourceStack::getResources(){
    return m_resources;
}