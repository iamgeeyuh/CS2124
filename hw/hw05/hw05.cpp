/*
    Name: Jia Huang
    Assignment: hw05
    Description: A program simulating nobles fighting each other with armies of warriors
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//warrior to be hired to noble's army
class Warrior{

    friend ostream& operator << (ostream& os, const Warrior& warrior){
        os << "    " << warrior.name << ": " << warrior.strength << endl;
        return os;
    }

    public:
        //warrior starts unemployed
        Warrior(const string& this_name, double this_strength):
            name(this_name), strength(this_strength), hired(false){}

        //getters
        bool is_hired() const{return hired;} //gets hired status
        const string& get_name() const{return name;} //gets name
        double get_strength() const{return strength;} // gets strength

        //employment
        void hire(){hired = true;} //warrior gets hired
        void fire(){hired = false;} //warrior gets fired

        //battle
        void die(){strength = 0;} //warrior dies
        void damage(double dmg){strength *= (1 - dmg);} //warrior is damaged

    private:
        //member variables
        string name;
        double strength;
        bool hired;

};

//noble with army of warriors to fight
class Noble{
    
    friend ostream& operator << (ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        //print army
        for (size_t ind = 0; ind != noble.army.size(); ind ++){
            os << *noble.army[ind];
        }
        return os;
    }

    public:
        //noble starts alive and with army of 0
        Noble(const string& this_name):
            name(this_name), alive(true){}

        //getters
        const string& get_name() const{return name;} //gets name
        bool is_alive() const{return alive;} //gets life status
        double get_strength() const{ //gets total strength of army
            double strength = 0;
            //adds each warrior's strength together
            for (size_t ind = 0; ind != army.size(); ind++){
                strength += army[ind]->get_strength();
            }
            return strength;
        }

        //employment
        void hire(Warrior& warrior){ //hires warrior
            if (!warrior.is_hired()){ 
                //noble can hire warrior
                army.push_back(&warrior);
                warrior.hire();
                return;
            }
            //noble cannot hire warrior
            cout << "Attempt to hire " << warrior.get_name() << " by " << name << " failed!" << endl;
        }
        void fire(Warrior& warrior){ //fires warrior
            //find warrior
            size_t ind = find_warrior(warrior.get_name());
            if (ind == army.size()){
                //warrior not in army
                cout << "Attempt to fire " << warrior.get_name() << " by " << name << " failed!" << endl;
                return;
            }
            //warrior in army
            remove_warrior(warrior, ind);
            warrior.fire();
            cout << "You don't work for me anymore " << warrior.get_name() << "! -- " << name << '.' << endl;
        }

        //battle
        void battle(Noble& foe){ //battles two nobles
            if (already_dead(foe)){
                return;
            }
            attack(foe);
        }
        void damage(double dmg){ //damages army
            //damage each warrior in army
            for (size_t ind = 0; ind != army.size(); ind++){
                army[ind]->damage(dmg);
            }
        }
        void die(){ //noble and army dies
            //noble dies
            alive = false; 
            //each warrior in army dies
            for (size_t ind = 0; ind != army.size(); ind++){
                army[ind]->die();
            }
        }

    private:
        //employment
        size_t find_warrior(const string& name) const{ //finds warrior in army
            for (size_t ind = 0; ind != army.size(); ind++){
                if (army[ind]->get_name() == name){ 
                    //warrior exists
                    return ind;
                }
            }
            //warrior not in army
            return army.size();
        }
        void remove_warrior(const Warrior& warrior, size_t ind){ //removes warrior from army
            for (size_t i = ind; i != army.size() - 1; i++){
                //shifts warriors to replace fired warrior
                army[i] = army[i+1];
            }
            army.pop_back();
        }

        //battle
        bool already_dead(const Noble& foe) const{ //returns if nobles are dead before battle
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
        void attack(Noble& foe){ //nobles attack each other
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

        //member variables
        string name;
        vector<Warrior*> army;
        bool alive;

};

size_t find_noble(const vector<Noble*>& nobles, const string& name); //returns index of noble in nobles vector
size_t find_warrior(const vector<Warrior*>& warriors, const string& name); //returns index of warrior in warriors vector
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors); //print status of nobles and warriors

int main(){

    string command;
    vector<Noble*> nobles;
    vector<Warrior*> warriors;

    //open file
    ifstream commands("nobleWarriors.txt");
    if (!commands){
        cerr << "Could not open file";
        exit(1);
    }

    //read file
    while (commands >> command){
        //noble command
        if (command == "Noble"){

            string name;
            commands >> name;

            //find if noble exists already
            size_t ind = find_noble(nobles, name);
            if (ind != nobles.size()){
                //noble exists
                cout << "Attempting to create existing noble: " << name << endl;
            }
            //create noble and add to vector
            else{
                nobles.push_back(new Noble(name));
            }
        }
        //warrior command
        else if (command == "Warrior"){
            
            string name;
            double strength;
            commands >> name >> strength;

            //find if warrior exists already
            size_t ind = find_warrior(warriors, name);
            if (ind != warriors.size()){
                //warrior exists
                cout << "Attempting to create existing warrior: " << name << endl;
            }
            //create warrior and add to vector
            else{
                warriors.push_back(new Warrior(name, strength));
            }
        }
        //hire command
        else if (command == "Hire"){

            string warrior;
            string noble;
            commands >> noble >> warrior;

            //find noble
            size_t nob_ind = find_noble(nobles, noble);
            if (nob_ind == nobles.size()){
                //noble doesn't exist
                cout << "Attempting to hire using unknown noble: " << noble << endl;
                continue;
            }
            //find warrior
            size_t war_ind = find_warrior(warriors, warrior);
            if (war_ind == warriors.size()){
                //warrior doesn't exist
                cout << "Attempting to hire using unknown warrior: " << warrior << endl;
                continue;
            }
            //noble hires warrior
            nobles[nob_ind]->hire(*warriors[war_ind]);
        }
        //fire command
        else if (command == "Fire"){

            string noble;
            string warrior;
            commands >> noble >> warrior;

            //find noble
            size_t nob_ind = find_noble(nobles, noble);
            if (nob_ind == nobles.size()){
                //noble doesn't exist
                cout << "Attempting to fire using unknown noble: " << noble << endl;
                continue;
            }
            //find warrior
            size_t war_ind = find_warrior(warriors, warrior);
            if (war_ind == warriors.size()){
                //warrior doesn't exist
                cout << "Attempting to fire using unknown warrior: " << warrior << endl;
                continue;
            }
            //noble fires warrior
            nobles[nob_ind]->fire(*warriors[war_ind]);
        }
        //status command
        else if (command == "Status"){
            status(nobles, warriors);
        }
        //battle command
        else if (command == "Battle"){

            string ally;
            string foe;
            commands >> ally >> foe;

            //find first noble
            size_t a_ind = find_noble(nobles, ally);
            if (a_ind == nobles.size()){
                //noble doesn't exist
                cout << "Attempting to battle using unknown noble: " << ally << endl;
                continue;
            }
            //find second noble
            size_t f_ind = find_noble(nobles, foe);
            if (f_ind == nobles.size()){
                //noble doesn't exist
                cout << "Attempting to battle using unknown noble: " << foe << endl;
                continue;
            }
            //nobles battle
            nobles[a_ind]->battle(*nobles[f_ind]);
        }
        //clear command
        else if (command == "Clear"){
            //clear nobles
            for (size_t ind = 0; ind != nobles.size(); ind++){
                delete nobles[ind];
                nobles[ind] = nullptr;
            }
            nobles.clear();
            //clear warriors
            for (size_t ind = 0; ind != warriors.size(); ind++){
                warriors[ind] = nullptr;
            }
            warriors.clear();
        }
    }
    commands.close();
    return 0;
}

//finds noble in vector and returns index. if noble does not exist, return vector size
size_t find_noble(const vector<Noble*>& nobles, const string& name){
    //find noble
    for (size_t ind = 0; ind != nobles.size(); ind++){
        //noble exists
        if (nobles[ind]->get_name() == name){return ind;}
    }
    //noble doesn't exist
    return nobles.size();
}

//finds warrior in vector and returns index. if warrior does not exist, return vector size
size_t find_warrior(const vector<Warrior*>& warriors, const string& name){
    //find warrior
    for (size_t ind = 0; ind != warriors.size(); ind++){
        //warrior exists
        if (warriors[ind]->get_name() == name){return ind;}
    }
    //warrior doesn't exist
    return warriors.size();

}

//print status of nobles and warriors
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
    cout << "Status\n======\nNobles:\n";
    //print nobles
    for (size_t ind = 0; ind != nobles.size(); ind++){
        cout << *nobles[ind];
    }
    //nobles is empty
    if (nobles.size() == 0){
        cout << "NONE" << endl;
    }
    cout << endl;
    //print unemployed warriors
    cout << "Unemployed Warriors:" << endl;
    bool none = true; //prints NONE if true
    for (size_t ind = 0; ind != warriors.size(); ind++){
        if (!warriors[ind]->is_hired()){
            none = false; //warrior exists so becomes false
            cout << *warriors[ind];
        }
    }
    if (none){
        cout << "NONE" << endl;
    }
}


 