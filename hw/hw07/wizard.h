/*
    Name: Jia Huang
    Assignment: hw07
*/

#ifndef WIZARD_H
#define WIZARD_H

#include "protector.h"

namespace WarriorCraft{

    class Wizard: public Protector{ //battles with magic

        public:

            Wizard(const std::string& name, double strength);

            void battle_cry() const;

    };

}

#endif