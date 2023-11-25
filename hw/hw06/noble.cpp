/*
    Name: Jia Huang
    Assignemnt: hw06
    Description: Contains the class Noble's method definitions
*/

#include "noble.h"
#include "warrior.h"
using namespace std;

namespace WarriorCraft{

    ostream& operator << (ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        //print army
        for (size_t ind = 0; ind != noble.army.size(); ind ++){
            os << *noble.army[ind];
        }
        return os;
    }

    //noble starts alive and with army of 0
    Noble::Noble(const string& this_name):
        name(this_name), alive(true){}

    //getters
    const string& Noble::get_name() const{return name;} //gets name
    bool Noble::is_alive() const{return alive;} //gets life status
    double Noble::get_strength() const{ //gets total strength of army
        double strength = 0;
        //adds each warrior's strength together
        for (size_t ind = 0; ind != army.size(); ind++){
            strength += army[ind]->get_strength();
        }
        return strength;
    }

    //employment
    bool Noble::hire(Warrior& warrior){ //hires warrior
        if (!warrior.is_hired()){ 
            //noble can hire warrior
            army.push_back(&warrior);
            warrior.hire(*this);
            return true;
        }
        //noble cannot hire warrior
        return false;
    }
    bool Noble::fire(Warrior& warrior){ //fires warrior
        //find warrior
        size_t ind = find_warrior(&warrior);
        if (ind == army.size()){ //warrior not in army
            return false;
        }
        //warrior in army
        remove_warrior(ind);
        warrior.fire();
        cout << "You don't work for me anymore " << warrior.get_name() << "! -- " << name << '.' << endl;
        return true;
    }
    void Noble::runaway(Warrior* warrior){
        size_t ind = find_warrior(warrior);
        remove_warrior(ind);
    }

    //battle
    void Noble::battle(Noble& foe){ //battles two nobles
        if (already_dead(foe)){
            return;
        }
        attack(foe);
    }
    void Noble::damage(double dmg){ //damages army
        //damage each warrior in army
        for (size_t ind = 0; ind != army.size(); ind++){
            army[ind]->damage(dmg);
        }
    }
    void Noble::die(){ //noble and army dies
        //noble dies
        alive = false; 
        //each warrior in army dies
        for (size_t ind = 0; ind != army.size(); ind++){
            army[ind]->die();
        }
    }

    //employment
    size_t Noble::find_warrior(Warrior* warrior) const{ //finds warrior in army
        for (size_t ind = 0; ind != army.size(); ind++){
            if (army[ind] == warrior){ 
                //warrior exists
                return ind;
            }
        }
        //warrior not in army
        return army.size();
    }
    void Noble::remove_warrior(size_t ind){ //removes warrior from army
        for (size_t i = ind; i != army.size() - 1; i++){
            //shifts warriors to replace fired warrior
            army[i] = army[i+1];
        }
        army.pop_back();
    }

    //battle
    bool Noble::already_dead(const Noble& foe) const{ //returns if nobles are dead before battle
        cout << name << " battles " << foe.get_name() << endl;
        if (!alive){
            if (!foe.is_alive()){
                //bnth dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
                return true;
            }
            else{
                //only ally dead
                cout << "He's dead, " << foe.get_name() << endl;
                return true;
            }
        }
        if (!foe.is_alive()){
            //only foe dead
            cout << "He's dead, " << name << endl;
            return true;
        }
        //both alive
        return false;
    }
    void Noble::attack(Noble& foe){ //nobles attack each other
        double ally_str = get_strength();
        double foe_str = foe.get_strength();
        if (ally_str == foe_str){
            //both die
            die();
            foe.die();
            cout << "Mutual Annihalation: " << name << " and " << foe.get_name() << " die at each other's hands" << endl;
            return;
        }
        else if (ally_str > foe_str){
            //foe dies
            damage(foe_str / ally_str);
            foe.die();
            cout << name << " defeats " << foe.get_name() << endl;
            return;
        }
        else if (ally_str < foe_str){
            //ally dies
            foe.damage(ally_str / foe_str);
            die();
            cout << foe.get_name() << " defeats " << name << endl;
            return;
        }
    }

};