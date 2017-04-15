//curses.cpp
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

using namespace std;

class Unforgivable_Spells{
    protected:
        string effects;
        string light;
        string caster;
        Unforgivable_Spells(string e, string c)
        :effects(e), caster(c){}
    public:
        virtual~Unforgivable_Spells(){}
        virtual void incantation() = 0;
        virtual void getEffect() = 0;
};

class KillingCurse:public Unforgivable_Spells{
    public:
        KillingCurse(string c)
        :Unforgivable_Spells("Instantaneous, painless death.", c){}
       
        void incantation(){
           cout << caster << ": Imperio!" << endl;
        }
        void getEffect(){
            cout << "The effect of the Killing Curse is: " << effects << endl;
        }
        ~KillingCurse(){}
};

class CruciatusCurse:public Unforgivable_Spells{
    public:
        CruciatusCurse(string c)
        :Unforgivable_Spells("Extreme pain, torture.", c){}
        
        void incantation(){
            cout << caster << ": Imperio!" << endl;
        }
        void getEffect(){
            cout << "The effect of the Cruciatus Curse is: " << effects << endl;
        }
        ~CruciatusCurse(){}
};

class ImperiusCurse:public Unforgivable_Spells{
     public:
        ImperiusCurse(string c)
        :Unforgivable_Spells("Total control over the victim.", c){}
        
        void incantation(){
            cout << caster << ": Imperio!" << endl;
        }
        void getEffect(){
            cout << "The effect of the Imperius Curse is: " << effects << endl;
        }
        ~ImperiusCurse(){}
};

int main(){
    
    Unforgivable_Spells * spells [3];
    
    spells[0] = new KillingCurse("Voldemort");
    spells[1] = new CruciatusCurse("Bellatrix");
    spells[2] = new ImperiusCurse("Barty Crouch Jr.");
    
    spells[0] -> incantation();
    cout << endl;
    spells[1] -> incantation();
    cout << endl;
    spells[2] -> incantation();
    cout << endl;
    
    spells[0] -> getEffect();
    cout << endl;
    spells[1] -> getEffect();
    cout << endl;
    spells[2] -> getEffect();
    cout << endl;
    
    delete spells[0];
    delete spells[1];
    delete spells[2];
    
    return 0;
}
