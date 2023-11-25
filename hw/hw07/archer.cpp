/*
    Name: Jia Huang
    Assignemnt: hw07
*/

#include "archer.h"
using namespace std;

namespace WarriorCraft{

    Archer::Archer(const string& name, double strength):
        Warrior(name, strength){}

    void Archer::battle_cry() const{
        cout << "TWANG! ";
        Warrior::battle_cry();
    }

}