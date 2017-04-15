//LeagueOfLegends.h
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

#ifndef _LOL_H_
#define _LOL_H_

#include <iostream>

using namespace std;

class Champion{
    protected:
        int health;
        int mana;
        double attack_damage;
        double ability_power;
        Champion(int h, int m, double ad, double ap)
        :health(h), mana(m), attack_damage(ad), ability_power(ap){}
    public:
        virtual ~Champion(){}
        virtual double attack() = 0;
};

class Ryze:public Champion{   
    public:
        Ryze(int h, int m, double ad, double ap)
        :Champion(h,m,ad,ap){}

        double attack(){
            cout << "Ryze does ";
            return 160 + (ability_power * 0.40) + (mana * 0.065);
        }
    
        ~Ryze(){}
};

class Jinx:public Champion{
    public:
        Jinx(int h, int m, double ad, double ap)
        :Champion(h,m,ad,ap){}
        
        double attack(){
            cout << "Jinx does ";
            return 210 + (attack_damage * 1.42);
        }
        
        ~Jinx(){}
};

class Dr_Mundo:public Champion{
    public:
        Dr_Mundo(int h, int m, double ad, double ap)
        :Champion(h,m,ad,ap){}
        
        double attack(){
            cout << "Dr. Mundo does ";
            return 280 + (health * 0.25);
        }
        
        ~Dr_Mundo(){}
};

#endif //_LOL_H_
