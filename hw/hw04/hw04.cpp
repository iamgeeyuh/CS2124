/*
    Name: Jia Huang
    Assignment: hw04
    Description: A game of nobles fighting each other with armies of warriors
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//warrior to be hired by noble
class Warrior{

    friend ostream& operator << (ostream& os, const Warrior& warrior);

    public:
        //initially unemployed
        Warrior(const string& this_name, double this_strength):
            name(this_name), strength(this_strength), hired(false){}

        //getters
        const string& get_name() const{return name;} //gets name
        double get_strength() const{return strength;} //gets strength

        //employment
        bool hire(){ //if not hired, becomes hired
            if (hired){return hired;}
            hired = true;
            return false;
        }
        void fire(){hired = false;} //not hired

        //battle
        void die(){strength = 0;} //strength 0
        void dmg(double dmg_ratio){strength *= (1-dmg_ratio);} //strength damaged

    private:
        string name;
        double strength;
        bool hired;
};

//noble initiates battles with armies of warriors
class Noble{
    
    friend ostream& operator << (ostream& os, const Noble& noble);

    public:
        //army initially 0 warriors
        Noble(const string& this_name):
            name(this_name), alive(true){}

        //getters
        const string& get_name() const{return name;} //gets name
        bool is_alive() const{return alive;} //gets alive
        double get_army_strength() const{ //calculate strength of your army
            double total_str = 0;
            //sum of strength of every warrior
            for (size_t i = 0; i != army.size(); i++){
                total_str += army[i]->get_strength();
            }
            return total_str;
        }

        //employment
        bool hire(Warrior& warrior){ //if warrior not hired, add to army
            if (warrior.hire() || !alive){return false;} //warrior hired or noble is dead
            army.push_back(&warrior);
            return true;
        }
        bool fire(Warrior& warrior){ //if warrior exists in army, remove him
            if (!alive){return false;} //noble is dead
            for (size_t i = 0; i != army.size(); i++){
                //warrior exists
                if (army[i]->get_name() == warrior.get_name()){
                    warrior.fire(); 
                    //remove warrior
                    for (size_t j = i; j != army.size() - 1; j++){
                        army[j] = army[j+1];
                    }
                    army.pop_back();
                    return true;
                }
            }
            //warrior does not exist
            return false;
        }

        //battle
        void battle(Noble& foe){
            cout << name << " battles " << foe.get_name() << endl;
            //check if nobles are alive to fight
            if (already_dead(foe)){
                return;
            }
            fight(foe);
        }
        void die(){ //noble dies
            alive = false;
            //every warrior in army dies
            for (size_t i = 0; i != army.size(); i++){
                army[i]->die();
            }
        }
        void dmg(double dmg_ratio){ //army is damaged
            //every warrior in army is damaged
            for (size_t i = 0; i != army.size(); i++){
                army[i]->dmg(dmg_ratio);
            }
        }

    private:
        string name;
        vector<Warrior*> army;
        bool alive;

        //prints appropriate outcome if nobles are dead
        bool already_dead(const Noble& foe) const{ 
            if (!alive){
                if (!foe.is_alive()){
                    //both dead
                    cout << "Oh, NO! They're both dead! Yuck!" << endl;
                    return true;
                }
                else{
                    //only you're dead
                    cout << "He's dead, " << foe.get_name() << endl;
                    return true;
                }
            }
            else if (!foe.is_alive()){
                //only foe is dead
                cout << "He's dead, " << name << endl;
                return true;
            }
            //both alive
            return false;
        }
        //calculates and applies damage to each army
        void fight(Noble& foe){
            double ally_str = get_army_strength();
            double foe_str = foe.get_army_strength();
            if (ally_str == foe_str){ //both die
                die();
                foe.die();
                cout << "Mutual Annihilation: " << name << " and " << foe.get_name() << " die at each other's hands" << endl;
            }
            else if (ally_str > foe_str){ //foe dies
                foe.die();
                double dmg_ratio = foe_str/ally_str;
                dmg(dmg_ratio);
                cout << name << " defeats " << foe.get_name() << endl;
            }
            else{ //you die
                die();
                double dmg_ratio = ally_str/foe_str;
                foe.dmg(dmg_ratio);
                cout << foe.get_name() << " defeats " << name << endl;
            }
        }
};

//output operator
ostream& operator << (ostream& os, const Warrior& warrior){ //warrior output
    os << "    " << warrior.name << ": " << warrior.strength;
    return os;
}

ostream& operator << (ostream& os, const Noble& noble){ //noble output
    os << noble.name << " has an army of " << noble.army.size();
    //outputs each warrior
    for (size_t i = 0; i != noble.army.size(); i++){ 
        os << endl;
        os << *noble.army[i];
    }
    return os;
}

// Utility functions provided for you, defined below.
void hire(Noble& nob, Warrior& war); //noble hires warrior
void fire(Noble& nob, Warrior& war); //noble fires warrior

int main(){
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    hire(jim, nimoy);
    hire(lance, theGovernator);
    hire(art, wizard);
    hire(lance, dylan);
    hire(linus, lawless);
    hire(billie, mrGreen);
    hire(art, cheetah);
    hire(art, nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    fire(art, cheetah);
    cout << art << endl;    
    fire(lance, nimoy);
    cout << lance << endl;    
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    cout << "==========\n\n";

    cout << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    return 0;
}

//
// Utility functions
//
// hire. Calls Noble's hire method and displays error message on failure.
void hire(Noble& nob, Warrior& war){
    if (!nob.hire(war)){
	    cerr << nob.get_name() << " failed to hire " << war.get_name() << endl;
    }
}

// fire. Calls Noble's fire method, displaying message on succsess and error message on failure
void fire(Noble& nob, Warrior& war){
    if (nob.fire(war)){
	    cout << war.get_name() << ", you don't work for me any more! -- " << nob.get_name() << ".\n";
    } 
    else{
	    cerr << nob.get_name() << " failed to fire " << war.get_name() << endl;
    }
}