#include "resource_stack.hpp"



ResourceStack::ResourceStack(long double startingResources){
    m_resources = startingResources;
}

void ResourceStack::addResources(long double amount){
    m_resources += amount;    
}

bool ResourceStack::removeResources(long double amount){
    if(m_resources >= amount){
        m_resources -= amount;
        return true;
    }
    return false;
}

void ResourceStack::clearResources(){
    m_resources = 0;
}

long double ResourceStack::getResources(){
    return m_resources;
}