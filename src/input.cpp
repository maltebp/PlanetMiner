#include <iostream>
#include <vector>
#include <sstream>

#include "input.hpp"


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

vector<string> updateTerminal(string resultMsg, string statusMsg){
    
    system("clear");    
    if( !resultMsg.empty() ){
        cout<<resultMsg<<endl<<endl;
    }
    
    cout<<statusMsg<<endl<<endl;

    cout<<"What is your command?"<<endl;
    return getCommand(">");
}


