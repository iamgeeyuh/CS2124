/*
    Name: Jia Huang
    Assignment: hw07
*/

#ifndef CHAD_H
#define CHAD_H

#include "noble.h"

namespace WarriorCraft{

    class Chad: public Noble{ //battles with own strength

        public:
            
            Chad(const std::string& name, double strength);

            double get_strength() const; //gets strength

            void battle_cry() const; //battle cry
            void gets_damaged(double dmg); //gets damaged

            void display(std::ostream& os) const;

        private:

            double strength;

    };

}

#endif