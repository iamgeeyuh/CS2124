/*
    Name: Jia Huang
    Assignment: hw07
*/

#include "protector.h"
#include "lord.h"
using namespace std;

namespace WarriorCraft{

    ostream& operator << (ostream& os, const Protector& protector){
        protector.display(os);
        return os;
    }

    Protector::Protector(const string& name, double strength):
        name(name), strength(strength), boss(nullptr){}

    bool Protector::is_hired() const{ //is hired?
        return (boss != nullptr);
    }

    double Protector::get_strength() const{ //get strength
        return strength;
    }

    void Protector::battle_cry() const{ //battle cry
        cout << name << " says: Take that in the name of my lord, " << boss->get_name() << endl;
    }

    void Protector::dies(){ //dies
        strength = 0;
    }

    void Protector::gets_damaged(double dmg){ //gets damaged
        strength *= dmg;
    }
    
    void Protector::hired(Lord& lord){ //gets hired
        boss = &lord;
    }

    void Protector::fired(){ //gets fired
        boss = nullptr;
    }

    void Protector::quits(){ //leaves boss
        boss->quit(this);
        boss = nullptr;
    }

    void Protector::display(ostream& os) const{
        os << name << ": " << strength << endl;
    }

}