/*
    Name: Jia Huang
    Assignemnt: hw06
    Description: Contains the class Warrior's method definitions
*/

#include "warrior.h"
#include "noble.h"
using namespace std;

namespace WarriorCraft{

    ostream& operator << (ostream& os, const Warrior& warrior){
        os << "    " << warrior.name << ": " << warrior.strength << endl;
        return os;
    }

    //warrior starts unemployed
    Warrior::Warrior(const string& this_name, double this_strength):
        name(this_name), strength(this_strength), boss(nullptr){}

    //getters
    bool Warrior::is_hired() const{return boss != nullptr;} //gets hired status
    const string& Warrior::get_name() const{return name;} //gets name
    double Warrior::get_strength() const{return strength;} // gets strength

    //employment
    void Warrior::hire(Noble& noble){boss = &noble;} //warrior gets hired
    void Warrior::fire(){boss = nullptr;} //warrior gets fired
    void Warrior::runaway(){ //warrior runs away
        if (is_hired()){
            boss->runaway(this); //remove warrior from army
            cout << name << " flees in terror, abandoning his lord, " << boss->get_name() << endl;
            boss = nullptr; //removes boss
        }
    }

    //battle
    void Warrior::die(){strength = 0;} //warrior dies
    void Warrior::damage(double dmg){strength *= (1 - dmg);} //warrior is damaged

};
