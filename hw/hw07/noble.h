/*
    Name: Jia Huang
    Assignment: hw07
*/

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{

    class Noble{ //battle each other

        public:

            Noble(const std::string& name);

            virtual double get_strength() const = 0; //get total strength
            virtual const std::string& get_name() const; //gets name
            virtual bool is_alive() const; //is alive?

            virtual void battle(Noble& foe); //battles other nobles
            virtual void battle_cry() const = 0; //battle cry
            virtual void dies(); //dies
            virtual void gets_damaged(double dmg) = 0; //gets damaged

            virtual void display(std::ostream& os) const = 0; //output operator

        private:

            virtual bool already_dead(const Noble& foe) const; //check aliveness of nobles before battle
            virtual void attack(Noble& foe); //compare strength and damage each other
            virtual void outcome(const Noble& foe) const; //displays outcome of battle

            std::string name;
            bool alive;

    };

    std::ostream& operator << (std::ostream& os, const Noble& noble);
}

#endif 