/*
    Name: Jia Huang
    Assignemnt: hw06
    Description: Contains the class Noble and its method prototypes
*/

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{

    class Warrior;

    class Noble{
    
    friend std::ostream& operator << (std::ostream& os, const Noble& noble);

        public:
            //noble starts alive and with army of 0
            Noble(const std::string& this_name);

            //getters
            const std::string& get_name() const; //gets name
            bool is_alive() const; //gets life status
            double get_strength() const; //gets total strength of army

            //employment
            bool hire(Warrior& warrior); //hires warrior
            bool fire(Warrior& warrior); //fires warrior
            void runaway(Warrior* warrior); //warrior runs away

            //battle
            void battle(Noble& foe); //battles two nobles
            void damage(double dmg); //damages army
            void die(); //noble and army dies


        private:
            //employment
            size_t find_warrior(Warrior* warrior) const; //finds warrior in army
            void remove_warrior(size_t ind); //removes warrior from army

            //battle
            bool already_dead(const Noble& foe) const; //returns if nobles are dead before battle
            void attack(Noble& foe); //nobles attack each other

            //member variables
            std::string name;
            std::vector<Warrior*> army;
            bool alive;

    };

};

#endif