
#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sstream>
#include <map>

#include "input.hpp"
#include "gatherer.hpp"
#include "resource_stack.hpp"
#include "texttable.h"


using namespace std;

bool run = true;

ResourceStack resourceStack(50);

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
    ss<<"Resources: "<<fixed<<setprecision(2)<<resourceStack.getResources()<<" rs"<<endl;
    ss<<"Gatherers: "<<gatherers.size();
    return ss.str();
}


string createErrorMessage(string msg){
    return "\033[31mError: " + msg+"\033[39m"; 
}

string createSuccessMessage(string msg){
    return "\033[32mSuccess: " + msg+"\033[39m"; 
}

const string ERR_WRONG_ARGS = createErrorMessage("Your arguments doesn't fit that command, sir");
const string ERR_UNKNOWN_BOT = createErrorMessage("I don't understand which robot you're refering to, sir");
const string ERR_CANT_AFFORD = createErrorMessage("We don't have enough resources to buy that, sir");
const string SUCC_BOUGHT_GATH = createSuccessMessage("More robots are always welcome, sir");
const string SUCC_UPGRADE = createSuccessMessage("The robots has been ugraded, sir");
const string ERR_UNKNOWN_COMMAND = createErrorMessage("We don't understand that command, sir");

string buyGatherer(vector<string> args){
    
    if( args.size() < 2 || args.size() > 3){
      return ERR_WRONG_ARGS;
    }

    int gatherersToBuy = 1; 

    if( args.size() == 3 ){
        try{
            gatherersToBuy = stoi(args[2]);
        }catch(invalid_argument e){
            return ERR_WRONG_ARGS;
        }
    }

    for( GathererType* type : GathererType::allTypes ){
        if(args[1] == type->commandKey){
            if(resourceStack.removeResources(type->cost * gatherersToBuy)){
                for(int i=0; i<gatherersToBuy; i++){
                    gatherers.push_back(new Gatherer( *type, resourceStack ));
                }
                return SUCC_BOUGHT_GATH;
            }
            return ERR_CANT_AFFORD;
        } 
    }
    return ERR_UNKNOWN_BOT;     
}


string upgradeGatherers(vector<string> args){
       
    if( args.size() != 2){
        return ERR_WRONG_ARGS;
    }

    for( GathererType* type : GathererType::allTypes ){
        if(args[1] == type->commandKey){
            float baseCost = type->cost * UPGRADE_COST_FACTOR;
            float totalCost = baseCost + baseCost * type->upgradeLevel * UPGRADE_COST_INC_FACTOR;
            
           if(resourceStack.removeResources( totalCost )){
                type->upgradeLevel++;
                return SUCC_UPGRADE;
            }
            return ERR_CANT_AFFORD;
        } 
    }
    return ERR_UNKNOWN_BOT;     
}


string store(vector<string> args){
    
    TextTable table('-', ' ', '-');
    table.add("Name ");
    table.add("Cmd Key  ");
    table.add("Cost  ");
    table.add("Effect  ");
    table.add("Upg. Level  ");
    table.add("Upg. Cost  ");
    table.endOfRow();

    for( GathererType* type : GathererType::allTypes ){
        table.add(type->name + "  ");
        table.add("'" + type->commandKey + "'  ");
        table.add(to_string(type->cost));

        ostringstream conversionStream;
        conversionStream<<fixed<<setprecision(2)<<type->adjustedGatheringAmount();
        conversionStream<<" rs / "<<type->gatheringFreq<<" sec.  ";
        table.add(conversionStream.str());
    
        table.add(to_string(type->upgradeLevel));
        table.add(to_string(1000));
        table.endOfRow();
    }
    
    ostringstream msgStream;
    msgStream<<table;
    return "These are the robots that have we work with, sir: \n" + msgStream.str();
}


int main(){

    startCountDown(60);
    string result = ""; 

    while(true){
        vector<string> args = updateTerminal(result, createStatusMsg());
        
        if(args.size() > 0 ){
            result = ""; 
            if(args[0] == "exit") break;
            if(args[0] == "money"){
                if(args.size() == 2){
                    try{
                        resourceStack.addResources( stoi(args[1]) );
                    }catch(invalid_argument e){
                        result=ERR_WRONG_ARGS;
                    }
                }
                
            }
            else if(args[0] == "buy"){
                result = buyGatherer(args);
            }else if(args[0] == "upgrade"){
                result = upgradeGatherers(args);
            }else if(args[0] == "store"){
                result = store(args);
            }else{
                result = ERR_UNKNOWN_COMMAND;
            }
        }
    }
    return 0;
}