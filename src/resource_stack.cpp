#include "resource_stack.hpp"


ResourceStack::ResourceStack(long double startingResources){
    m_resources = startingResources;
}

void ResourceStack::addResources(long double amount){
    pthread_mutex_lock(&resource_mutex);
    m_resources += amount; 
    pthread_mutex_unlock(&resource_mutex);   
}

bool ResourceStack::removeResources(long double amount){
    pthread_mutex_lock(&resource_mutex);
    if(m_resources >= amount){
        pthread_mutex_unlock(&resource_mutex);
        m_resources -= amount;
        return true;
    }
    pthread_mutex_unlock(&resource_mutex);
    return false;
}

void ResourceStack::clearResources(){
    pthread_mutex_lock(&resource_mutex);
    m_resources = 0;
    pthread_mutex_unlock(&resource_mutex);
}

long double ResourceStack::getResources(){
    return m_resources;
}