/*
    Name: Jia Huang
    Assignment: HW02
    Description: A program to battle warriors and keep track of their health
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Warrior{
    string name;
    int strength;
};

void create_warrior(vector<Warrior>& party, const string& name, const int strength); //creates and adds new warrior struct to vector
void status(vector<Warrior>& party); //prints status of current warriors
void battle(vector<Warrior>& party, const string& warrior_one, const string& warrior_two); //battle two warriors
size_t find_warrior(vector<Warrior>& party, const string& warrior_name); //finds the index of a warrior in a vector of warriors
bool already_dead(const Warrior& warrior_one, const Warrior& warrior_two); //prints out appropriate message if warriors are dead before battle begins
void damage(Warrior& warrior_one, Warrior& warrior_two); //changes stats of warriors based on battle
void print_outcome(const Warrior& warrior_one, const Warrior& warrior_two); //prints the outcome of the battle

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
            string name;
            int strength;
            file >> name >> strength;
            create_warrior(party, name, strength);
        }
        //status command
        else if (command == "Status"){
            status(party);
        }
        //battle command
        else{
            string warrior_one;
            string warrior_two;
            file >> warrior_one >> warrior_two;
            battle(party, warrior_one, warrior_two);
        }
    }
    file.close();
    return 0;
}

/*
    creates and adds new warrior struct to vector

    parameters:
        vector<warrior>& party: vector of warriors where new warrior will be added
        string& name: name of new warrior
        int strength: strength of new warrior
    return:
        nothing
*/
void create_warrior(vector<Warrior>& party, const string& name, const int strength){
    //create new warrior
    Warrior warrior;
    warrior.name = name;
    warrior.strength = strength;
    //add warrior to party
    party.push_back(warrior);
}

/*
    prints status of current warriors

    parameters:
        vector<Warrior>& party: vector of warriors to print out
    return:
        nothing
*/
void status(vector<Warrior>& party){
    cout << "There are: " << party.size() << " warrior(s)" << endl;
    for (Warrior& warrior: party){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength << endl;
    }
}

/*
    battle two warriors

    parameters:
        vector<Warrior>& party: party of warriors
        string& warrior_name_one: name of first warrior
        string& warrior_name_two: name of second warrior
    return:
        nothing
*/
void battle(vector<Warrior>& party, const string& warrior_name_one, const string& warrior_name_two){
    cout << warrior_name_one << " battles " << warrior_name_two << endl;
    //identify battling warriors in party
    size_t index_one = find_warrior(party, warrior_name_one);
    size_t index_two = find_warrior(party, warrior_name_two);
    //end battle if warriors are already dead
    if (already_dead(party[index_one], party[index_two])){
        return;
    }
    //warriors are alive and able to fight
    damage(party[index_one], party[index_two]);
    print_outcome(party[index_one], party[index_two]);

}

/*
    finds the index of a warrior in a vector of warriors

    parameters:
        vector<Warriors>& party: vector of warriors to search through
        string& warrior_name: name of warrior to find in 'party'
    return:
        size_t: index of warrior in 'party'
*/
size_t find_warrior(vector<Warrior>& party, const string& warrior_name){
    for (size_t i = 0; i < party.size(); i++){
        if (warrior_name == party[i].name){
            return i;
        }
    }
    //will never return 0 because warrior_name is always in the party
    return 0;
}

/*
    prints out appropriate message if warriors are dead before battle begins

    parameters:
        Warrior& warrior_one: first warrior
        Warrior& warrior_two: second warrior
    return:
        true if at least one warrior is dead
        false if none are dead
*/
bool already_dead(const Warrior& warrior_one, const Warrior& warrior_two){
    //both are dead
    if (warrior_one.strength == 0 && warrior_two.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return true;
    }
    //one is dead
    else if (warrior_one.strength == 0){
        cout << "He's dead, " << warrior_two.name << endl;
        return true;
    }
    else if (warrior_two.strength == 0){
        cout << "He's dead, " << warrior_one.name << endl;
        return true;
    }
    //both are alive
    return false;
}

/*
    changes stats of warriors based on battle

    paraneters:
        Warrior& warrior_one: first warrior in battle
        Warrior& warrior_two: second warrior in battle
    return:
        nothing
*/
void damage(Warrior& warrior_one, Warrior& warrior_two){
    //both warriors are damaged
    int strength_one = warrior_one.strength;
    warrior_one.strength -= warrior_two.strength;
    warrior_two.strength -= strength_one;
    //set strength to 0 if dead
    if (warrior_one.strength < 0){
        warrior_one.strength = 0;
    }
    if (warrior_two.strength < 0){
        warrior_two.strength = 0;
    }
}

/*
    prints the outcome of the battle

    parameters:
        Warrior& warrior_one: first warrior
        Warrior& warrior_two: second warrior
    return:
        nothing
*/
void print_outcome(const Warrior& warrior_one, const Warrior& warrior_two){
    //both die
    if (warrior_one.strength == 0 && warrior_two.strength == 0){
        cout << "Mutual Annihilation: " << warrior_one.name << " and " << warrior_two.name << " die at each other's hands" << endl;
    }
    //one dies
    else if (warrior_one.strength == 0){
        cout << warrior_two.name << " defeats " << warrior_one.name << endl;
    }
    else{
        cout << warrior_one.name << " defeats " << warrior_two.name << endl;
    }
}