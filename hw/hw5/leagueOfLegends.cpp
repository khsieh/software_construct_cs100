//LeagueOfLegends.cpp
/*
 * Course: CS 100 Fall 2013
 *
 * First Name: <Kevin>
 * Last Name: <Hsieh>
 * Username: <khsie003>
 * email address: <khsie003@ucr.edu>
 *
 *
 * Assignment: <Homework #5>
 *
 * I hereby certify that the contents of this file represent
 * my own original individual work. Nowhere herein is there
 * code from any outside resources such as another individual,
 * a website, or publishings unless specifically designated as
 * permissible by the instructor or TA.
 */  
 
#include <iostream>
#include "leagueOfLegends.h"

int main(){
    Champion * Team[3];
    Team[0] = new Ryze(446,750,55,305);
    Team[1] = new Jinx(500,245,187,0);
    Team[2] = new Dr_Mundo(675,0,60,10);
    
    cout << Team[0]->attack() 
         << " damages to a enemy champion!" << endl;
    
    cout << Team[1]->attack() 
         << " damages to a enemy champion!" << endl;
         
    cout << Team[2]->attack() 
         << " damages to a enemy champion!" << endl;
    
    delete Team[0];
    delete Team[1];
    delete Team[2];
    
    return 0;
}
