
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



string createStatusMsg(){
    ostringstream ss;
    ss<<"Resources: "<<resourceStack.getResources()<<endl;
    ss<<"Gatherers: "<<gatherers.size();
    return ss.str();
}

int main(){

    string result = ""; 

    while(true){
        vector<string> args = updateTerminal(result, createStatusMsg());
        result = ""; 
        if(args.size() > 0 ){
            if(args[0] == "exit") break;
            if(args[0] == "buy"){
                gatherers.push_back( new Gatherer(TYPE_SIMPLE_BOT, resourceStack)  );
            }
            if(args[0] == "res"){
                std::ostringstream ss;
                ss<<"You have "<<resourceStack.getResources()<<" resources";
                result = ss.str();
            }
        }
    }
    return 0;
}