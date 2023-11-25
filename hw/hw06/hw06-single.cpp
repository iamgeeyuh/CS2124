/*
    Name: Jia Huang
    Assignment: hw06
    Description: A program simulating nobles fighting each other with armies of warriors
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Noble;

//warrior to be hired to noble's army
class Warrior{

    friend ostream& operator << (ostream& os, const Warrior& warrior);

    public:
        //warrior starts unemployed
        Warrior(const string& this_name, double this_strength);

        //getters
        bool is_hired() const; //gets hired status
        const string& get_name() const; //gets name
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
        string name;
        double strength;
        Noble* boss;

};

//noble with army of warriors to fight
class Noble{
    
    friend ostream& operator << (ostream& os, const Noble& noble);

    public:
        //noble starts alive and with army of 0
        Noble(const string& this_name);

        //getters
        const string& get_name() const; //gets name
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
        string name;
        vector<Warrior*> army;
        bool alive;

};

int main(){

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha 
	 << cheetah.is_hired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha 
	 << wizard.is_hired() << endl;
    cout << "===============================================\n\n";

}

//warrior

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

//noble 

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