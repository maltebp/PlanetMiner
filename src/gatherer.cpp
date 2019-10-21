
#include "gatherer.hpp"
#include <unistd.h>
#include <iostream>





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
        sleep(m_gatheringSpeed);
        std::cout<<"Gathering"<<std::endl;
    }
}
