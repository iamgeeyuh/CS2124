/*
    Name: Jia Huang
    Assignment: hw07
*/

#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include "warrior.h"

namespace WarriorCraft{

    class Swordsman: public Warrior{ //battles with swords

        public:

            Swordsman(const std::string& name, double strength);

            void battle_cry() const;

    };

}

#endif