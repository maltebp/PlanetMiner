#include "resource_stack.hpp"




void ResourceStack::addResources(float amount){
    m_resources += amount;    
}

void ResourceStack::removeResources(float amount){
    m_resources -= amount;
}

void ResourceStack::clearResources(){
    m_resources = 0;
}

float ResourceStack::getResources(){
    return m_resources;
}