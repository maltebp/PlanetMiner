
#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sstream>

#include "input.hpp"
#include "gatherer.hpp"
#include "resource_stack.hpp"

using namespace std;

bool run = true;

ResourceStack resourceStack;

vector<Gatherer*> gatherers;

time_t remainingTime;

void endGame(){
    cout<<"Game over!"<<endl;
    exit(0); 
}


void* startCountdownCb(void* time){
    remainingTime = (time_t) time;

    while(remainingTime > 0 ){
        struct timespec time1, time2;
        time1.tv_sec = 1;
        nanosleep( &time1, &time2 );
        remainingTime--;
    }

    endGame();
}

void startCountDown(time_t time){
    pthread_t thread;
    pthread_create(&thread, NULL, startCountdownCb, (void*) time);
}


string createStatusMsg(){
    ostringstream ss;
    ss<<"Time remaining: "<<remainingTime<<" seconds"<<endl<<endl;
    ss<<"Resources: "<<resourceStack.getResources()<<endl;
    ss<<"Gatherers: "<<gatherers.size();
    return ss.str();
}


int main(){

    startCountDown(60);
    string result = ""; 

    while(true){
        vector<string> args = updateTerminal(result, createStatusMsg());
        result = ""; 
        if(args.size() > 0 ){
            if(args[0] == "exit") break;
            if(args[0] == "buy"){
                gatherers.push_back( new Gatherer(TYPE_SIMPLE_BOT, resourceStack)  );
            }
        }
    }
    return 0;
}