/*
    Name: Jia Huang
    Assignment: hw07
*/

#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <vector>
#include <string>

namespace WarriorCraft{

    class Lord;

    class Protector{ //battles for Nobles

        public:

            Protector(const std::string& name, double strength);

            virtual bool is_hired() const; //is hired?
            virtual double get_strength() const; //get strength

            virtual void battle_cry() const = 0; //battle cry
            virtual void dies(); //dies
            virtual void gets_damaged(double dmg); //gets damaged

            virtual void quits(); //leaves boss
            virtual void hired(Lord& lord); //gets hired
            virtual void fired(); //gets fired

            virtual void display(std::ostream& os) const; //output operator

        private:

            std::string name;
            double strength;
            Lord* boss;
            
    };

    std::ostream& operator << (std::ostream& os, const Protector& protector);
}

#endif