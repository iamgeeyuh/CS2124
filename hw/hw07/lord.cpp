/*
    Name: Jia Huang
    Assignment: hw07
*/

#include "lord.h"
#include "protector.h"
using namespace std;

namespace WarriorCraft{

    Lord::Lord(const string& name):
        Noble(name){}

    double Lord::get_strength() const{ //get strength
        double strength = 0;
        for (size_t i = 0; i != army.size(); i++){ //add the strength of every protector
            strength += army[i]->get_strength();
        }
        return strength;
    }

    void Lord::battle_cry() const{
        for (size_t i = 0; i != army.size(); i++){ //each protector battle cries
            army[i]->battle_cry();
        }
    }

    void Lord::dies(){
        for (size_t i = 0; i != army.size(); i++){ //each protector dies
            army[i]->dies();
        }
        Noble::dies();
    }

    void Lord::gets_damaged(double dmg){ //gets damaged
        for (size_t i = 0; i != army.size(); i++){ //damages each protector in army
            army[i]->gets_damaged(dmg);
        }
    }

    bool Lord::hires(Protector& prot){ //hires protector
        size_t ind = find_protector(&prot);
        if ((ind == army.size()) && (!prot.is_hired())){ //protector not in army and protector not hired
            prot.hired(*this);
            army.push_back(&prot);
            return true;
        }
        return false;
    }
    
    bool Lord::fires(Protector& prot){ //fires protector
        size_t ind = find_protector(&prot);
        if (ind != army.size()){ //remove protector from army
            prot.fired();
            remove(ind);
            return true;
        }
        return false;
    }

    void Lord::quit(const Protector* prot){ //protector quits
        size_t ind = find_protector(prot);
        remove(ind);
    }

    void Lord::display(ostream& os) const{ //output operator
        Noble::display(os);
        os << " has an army of " << army.size() << endl;
        for (size_t i = 0; i != army.size(); i++){
            os << "    " << *army[i];
        }
    }

    size_t Lord::find_protector(const Protector* prot) const{ //find protector index in army
        for (size_t i = 0; i != army.size(); i++){
            if (army[i] == prot){
                return i;
            }
        }
        //protector not in army
        return army.size();
    }

    void Lord::remove(size_t ind){ //remove from army
        for (size_t i = ind; i != army.size()-1; i++){
            army[i] = army[i+1];
        }
        army.pop_back();
    }

}