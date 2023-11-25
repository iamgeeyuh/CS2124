/*
    Name: Jia Huang
    Assignemnt: hw06
    Description: Contains the class Warrior and its method prototypes
*/

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>

namespace WarriorCraft{

    class Noble;

    class Warrior{

        friend std::ostream& operator << (std::ostream& os, const Warrior& warrior);

        public:
            //warrior starts unemployed
            Warrior(const std::string& this_name, double this_strength);

            //getters
            bool is_hired() const; //gets hired status
            const std::string& get_name() const; //gets name
            double get_strength() const; // gets strength

            //employment
            void hire(Noble& noble); //warrior gets hired
            void fire(); //warrior gets fired
            void runaway(); //warrior runs away

            //battle
            void die(); //warrior dies
            void damage(double dmg); //warrior is damaged

        private:
            //member variables
            std::string name;
            double strength;
            Noble* boss;

    };

};

#endif