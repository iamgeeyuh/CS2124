/*
    Name: Jia Huang
    Assignment: hw07
*/

#ifndef ARCHER_H
#define ARCHER_H

#include "warrior.h"

namespace WarriorCraft{

    class Archer: public Warrior{ //battles with arrows

        public:

            Archer(const std::string& name, double strength);

            void battle_cry() const; //battle cry

    };

}

#endif