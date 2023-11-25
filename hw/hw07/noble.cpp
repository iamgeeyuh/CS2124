/*
    Name: Jia Huang
    Assignment: hw07
*/

#include "noble.h"
using namespace std;

namespace WarriorCraft{

    ostream& operator << (ostream& os, const Noble& noble){
        noble.display(os);
        return os;
    }

    Noble::Noble(const string& name):
        name(name), alive(true){}

    const string& Noble::get_name() const{ //gets name
        return name;
    }

    bool Noble::is_alive() const{ //is alive?
        return alive;
    }

    void Noble::battle(Noble& foe){ //nobles battle
        cout << name << " battles " << foe.name << endl;
        if (already_dead(foe)){ //check if either is dead
            return;
        }
        battle_cry();
        foe.battle_cry();
        attack(foe);
        outcome(foe);
    }

    void Noble::dies(){ //noble dies
        alive = false;
    }

    bool Noble::already_dead(const Noble& foe) const{ //check aliveness of nobles before battle
        if (!alive){
            if (!foe.is_alive()){ //both dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
                return true;
            }
            //ally is dead
            foe.battle_cry();
            cout << "He's dead, " << foe.name << endl;
            return true;
        }
        if (!foe.is_alive()){ //foe is dead
        battle_cry();
            cout << "He's dead, " << name << endl;
            return true;
        }
        //both alive
        return false;
    }

    void Noble::attack(Noble& foe){
        double ally_str = get_strength();
        double foe_str = foe.get_strength();
        if (ally_str == foe_str){ //both die
            dies();
            foe.dies();
            return;
        }
        if (ally_str > foe_str){ //foe dies
            foe.dies();
            gets_damaged(1-(foe_str/ally_str));
            return;
        }
        //ally dies
        dies();
        foe.gets_damaged(1-(ally_str/foe_str));
    }

    void Noble::outcome(const Noble& foe) const{
        if (!alive){
            if (!foe.is_alive()){ //both die
                cout << "Mutual Annihilation: " << name << " and " << foe.get_name() << " die at each other's hands" << endl;
                return;
            }
            //ally dies
            cout << foe.get_name() << " defeats " << name << endl;
            return;
        }
        if (!foe.is_alive()){ //foe dies
            cout << name << " defeats " << foe.get_name() << endl;
        }
    }

    void Noble::display(ostream& os) const{
        os << name;
    }

}
