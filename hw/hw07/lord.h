/*
    Name: Jia Huang
    Assignment: hw07
*/

#ifndef LORD_H
#define LORD_H

#include "noble.h"

namespace WarriorCraft{

    class Protector;

    class Lord: public Noble{ //battles with army

        public:

            Lord(const std::string& name);

            double get_strength() const; //get strength

            void battle_cry() const; //battle cry
            void dies(); //dies
            void gets_damaged(double dmg); //gets damaged
    
            bool hires(Protector& prot); //hire a protector
            bool fires(Protector& prot); //fire a protector
            void quit(const Protector* prot); //protector quits

            void display(std::ostream& os) const; //output operator

        private:

            size_t find_protector(const Protector* prot) const;
            void remove(size_t ind);

            std::vector<Protector*> army;

    };

}

#endif