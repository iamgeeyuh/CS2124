/*
    Name: Jia Huang
    Assignmnet: hw07
*/

#include "warrior.h"
using namespace std;

namespace WarriorCraft{

    Warrior::Warrior(const string& name, double strength):
        Protector(name, strength){}

    void Warrior::battle_cry() const{
        Protector::battle_cry();
    }

}