#include <iostream>
#include <vector>
#include <sstream>

#include "input.hpp"


static string errorMsg;


/** Prints prompt message and reads the input of the user
 *  It returns the number of arguments (including command)
 *  given by the user
 *  Source: own project () */
vector<string> getCommand( string promptMsg ){

    vector<string> args;

    cout<<promptMsg;
    cout.flush();

    string input;

    // Read entire line
    getline(cin, input);

    // Split line into arguments seperated by ' '
    stringstream ss(input);

    while( getline(ss, input, ' ')){
        args.push_back(input);
    }
    return args;
}


void displayStatus(){
    cout<<"What is your command?"<<endl;
}


vector<string> updateTerminal(string resultMsg){
    
    system("clear");
    if( !resultMsg.empty() ){
        cout<<resultMsg<<endl;
    }
    displayStatus();
    return getCommand(">");
}


