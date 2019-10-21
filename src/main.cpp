
#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "input.hpp"
#include "gatherer.hpp"
#include "resource_stack.hpp"

using namespace std;

bool run = true;

ResourceStack resourceStack;

vector<Gatherer*> gatherers;


int main(){

    for(int i=0; i<2; i++){
        gatherers.push_back( new Gatherer(TYPE_SIMPLE_BOT, resourceStack)  );
    }

    while(true){
        sleep(1);
        // vector<string> args = updateTerminal("");
        // if(args.size() > 0 ){
        //     if(args[0] == "exit") break;
        //     if(args[0] == "buy simplerobot"){
                
        //     }
        // }
    }
    return 0;
}