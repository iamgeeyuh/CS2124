/*
    Name: Jia Huang
    Assignment: hw07
*/

#include "chad.h"
using namespace std;

namespace WarriorCraft{

    Chad::Chad(const string& name, double strength):
        strength(strength), Noble(name){}

    double Chad::get_strength() const{ //gets strength
        return strength;
    }

    void Chad::battle_cry() const{ //battle cry
        cout << "Ugh!" << endl;
    }

    void Chad::gets_damaged(double dmg){ //gets damaged
        strength *= dmg;
    }

    void Chad::display(ostream& os) const{
        Noble::display(os);
        os << " has strength " << strength;
    }

}