/*
    Name: Jia Huang
    Assignment: hw07
*/

#include "wizard.h"
using namespace std;

namespace WarriorCraft{

    Wizard::Wizard(const string& name, double strength):
        Protector(name, strength){}

    void Wizard::battle_cry() const{
        cout << "POOF!" << endl;
    }

}