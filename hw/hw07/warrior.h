/*
    Name: Jia Huang
    Assignmnet: hw07
*/

#ifndef WARRIOR_H
#define WARRIOR_H

#include "protector.h"

namespace WarriorCraft{

    class Warrior: public Protector{ //battles with melee

        public:

            Warrior(const std::string& name, double strength);

            virtual void battle_cry() const = 0;

    };

}

#endif