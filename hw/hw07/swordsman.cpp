/*
    Name: Jia Huang
    Assignment: hw07
*/  

#include "swordsman.h"
using namespace std;

namespace WarriorCraft{

    Swordsman::Swordsman(const string& name, double strength):
        Warrior(name, strength){}

    void Swordsman::battle_cry() const{
        cout << "CLANG! ";
        Warrior::battle_cry();
    }

}