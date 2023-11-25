/*
    Name: Jia Huang
    Assignment: HW03
    Description: A program to battle warriors and keep track of their weapon and strength
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//warrior class with name and weapon
class Warrior{

    ostream& operator << (ostream& os); //prints warrior name, weapon name, and strength

    public:
        //warrior name and strength used to create weapon 
        Warrior(const string& this_name, int this_strength, const string& weapon_name): name(this_name), weapon(Weapon {weapon_name, this_strength}){}
        //methods
        string get_name() const{return name;} //get name
        string get_weapon_name() const{return weapon.get_name();} //get weapon name
        int get_strength() const{return weapon.get_strength();} //get strength

        void battle(Warrior& foe){ //battle two warriors
            cout << name << " battles " << foe.get_name() << endl;
            if (already_dead(foe)){
                return;
            }
            attack(foe);
            outcome(foe);
        }

        bool already_dead(const Warrior& foe) const{ //prints out appropriate message if warriors are dead before battle begins
            if (weapon.get_strength() == 0){
                if (foe.get_strength() == 0){
                    //both are dead
                    cout << "Oh, NO! They're both dead! Yuck!" << endl;
                    return true;
                }
                else{
                    //only you are dead
                    cout << "He's dead, " << foe.get_name() << endl;
                    return true;
                }
            }
            else if (foe.get_strength() == 0){
                //only foe is dead
                cout << "He's dead, " << name << endl;
                return true;
            }
            //both are alive
            return false;
        }

        void attack(Warrior& foe){
            //holds your damage
            int dmg = weapon.get_strength() - foe.get_strength();
            //damage foe
            foe.damage(foe.get_strength() - weapon.get_strength());
            //damage you
            weapon.damage(dmg);
        }

        void damage(const int dmg){weapon.damage(dmg);} //damage weapon strength

        void outcome(const Warrior& foe) const{ //prints outcome of battle
            if (weapon.get_strength() == 0){
                if (foe.get_strength() == 0){
                    //both are dead
                    cout << "Mutual Annihilation: " << name << " and " << foe.get_name() << " die at each other's hands" << endl;
                    return;
                }
                else{
                    //only you are dead
                    cout << foe.get_name() << " defeats " << name << endl;
                    return;
                }
            }
            else if (foe.get_strength() == 0){
                //only foe is dead
                cout << name << " defeats " << foe.get_name() << endl;
                return;
            }
            //both are alive
        }

    private:
        //weapon class with name and strength
        class Weapon{

            public:
                Weapon(const string& this_name, int this_strength): name(this_name), strength(this_strength){}
                //methods
                string get_name() const{return name;} //get name
                int get_strength() const{return strength;} //get strength
                void damage(const int dmg){ //damage strength
                    //weapon is broken
                    if (dmg <= 0){
                        strength = 0;
                    }
                    //weapon still viable
                    else{
                        strength = dmg;
                    }
                }

            private:
                string name; //weapon name
                int strength;
        };
        string name; //warrior name
        Weapon weapon;
};

//warrior class output
ostream& operator << (ostream& os, const Warrior& warrior){
        os << "Warrior: " << warrior.get_name() << ", weapon: " << warrior.get_weapon_name() << ", " << warrior.get_strength() << endl;
        return os;
    }

void create_warrior(vector<Warrior>& party, const string& warrior_name, const string& weapon_name, int strength); //creates new warrior and adds them to party
void status(const vector<Warrior>& party); //prints status of current warriors
size_t find_warrior(const vector<Warrior>& party, const string& name); //finds index of a warrior in party

int main(){
    vector<Warrior> party;
    string command;
    //open file
    ifstream file("warriors.txt");
    if (!file){
        cerr << "Could not open file" << endl;
        exit(1);
    }
    //extract commands from file
    while (file >> command){
        //warrior command
        if (command == "Warrior"){
            string warrior_name;
            string weapon_name;
            int strength;
            file >> warrior_name >> weapon_name >> strength;
            create_warrior(party, warrior_name, weapon_name, strength);
        }
        //status command
        else if (command == "Status"){
            status(party);
        }
        //battle command
        else if (command == "Battle"){
            string warrior_one;
            string warrior_two;
            file >> warrior_one >> warrior_two;
            //identify battling warriors
            size_t ind_one = find_warrior(party, warrior_one);
            size_t ind_two = find_warrior(party, warrior_two);
            party[ind_one].battle(party[ind_two]);
        }
    }
    file.close();
    return 0;
}

/*
    creates and adds new warrior class to vector

    parameters:
        vector<Warrior>& party: vector of existing warriors
        const string& warrior_name: name of new warrior
        const string& weapon_name: name of warrior's weapon
        int strength: strength of new warrior
    return:
        nothing
*/
void create_warrior(vector<Warrior>& party, const string& warrior_name, const string& weapon_name, int strength){
    //creates new warrior class and adds to party vector
    party.push_back(Warrior{warrior_name, strength, weapon_name});
}

/*
    prints status of current warriors

    parameters:
        const vector<Warrior>& party: vector of warriors to print out
    return:
        nothing
*/
void status(const vector<Warrior>& party){
    cout << "There are: " << party.size() << " warrior(s)" << endl;
    //print every existing warrior in party
    for (const Warrior& warrior: party){
        cout << warrior;
    }
}

/*
    finds the index of a warrior in a vector of warriors

    parameters:
        const vector<Warriors>& party: vector of warriors to search through
        const string& warrior_name: name of warrior to find in 'party'
    return:
        size_t: index of warrior in 'party'
*/
size_t find_warrior(const vector<Warrior>& party, const string& name){
    //searches for warrior through party
    for (size_t ind = 0; ind != party.size(); ind++){
        if (party[ind].get_name() == name){
            return ind;
        }
    }
    return party.size();
}