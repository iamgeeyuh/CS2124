/*
    Name: Jia Huang
    Assignment: Lab03
    Description: identifies duplicate hydrocarbons and displays their chemical formula and their names
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Hydrocarbon{
        vector<string> names;
        int carbons;
        int hydrogens;
    };

void open_file(ifstream& file); //opens file
void get_data(ifstream& file, vector<Hydrocarbon>& data); //gets data from file
void add_data(vector<Hydrocarbon>& data, int carb, int hydro, string name); //adds appropriate data to vector
size_t find_duplicate(vector<Hydrocarbon>& data, int carb, int hydro); //finds index of duplicate hydrocarb
void sort_data(vector<Hydrocarbon>& data); //sorts vector based on hydrocarb formula
void display_data(vector<Hydrocarbon>& data); //prints vector data
void display_formula(int& carb, int& hydro); //formats and prints hydrocarb formula

int main(){
    //initalize variables
    ifstream file;
    string line;
    vector<Hydrocarbon> data;
    //open file
    open_file(file);
    //extract file data
    get_data(file, data);
    //sort vector of data
    sort_data(data);
    //prints data
    display_data(data);
    //close file
    file.close();
    return 0;
}

/*
    asks user for file name until valid file is opened
    
    parameters:
        ifstream& file: open files in stream

    return:
        nothing
*/
void open_file(ifstream& file){
    //initalize variables
    string file_name;
    //repeats until valid file name is inputed and file is opened
    do{
        file.clear();
        cout << "Please enter your file name: ";
        cin >> file_name;
        file.open(file_name);
    } while (!file);
}

/*
    gets data from file

    parameters:
        ifstream& file: file of hydrocarb names and formula
        vector<Hydrocarbon>& data: add unique hydrocarbon formulas with all of their names to the vector
    
    return:
        nothing
*/
void get_data(ifstream& file, vector<Hydrocarbon>& data){
    //initialize variables
    string name;
    char atom;
    int carb;
    int hydro;
    //extracts name and corresponding carb and hydro nums from file
    while (file >> name >> atom >> carb >> atom >> hydro){
        int duplicate = find_duplicate(data, carb, hydro);
        //no duplicate, add new hydrocarb to data
        if (duplicate == -1){
            add_data(data, carb, hydro, name);
        }
        //duplicate exists, add name to vector of hydrocarb names
        else{
            data[duplicate].names.push_back(name);
        }
    }
}

/*
    creates new Hydrocarbon struct and adds a name, carb, and hydro

    parameters:
        vector<Hydrocarbon>& data: append hydrocarb to 'data' 
        int carb: num of carbs in new struct
        int hydro: num of hydros in new struct
        string name: name of new struct
    return:
        nothing
*/
void add_data(vector<Hydrocarbon>& data, int carb, int hydro, string name){
    Hydrocarbon hydrocarbon;
    hydrocarbon.names.push_back(name);
    hydrocarbon.carbons = carb;
    hydrocarbon.hydrogens = hydro;
    data.push_back(hydrocarbon);
}

/*
    finds index of duplicate hydrocarb in 'data'

    parameters:
        vector<Hydrocarbon>& data: vector of hydrocarbs
        int carb: num of carb in target hydrocarb
        int hydro: num of hydro in target hydrocarb
    
    return:
        if duplicate exists, return index
        if duplicate does not exist, return -1
*/
size_t find_duplicate(vector<Hydrocarbon>& data, int carb, int hydro){
    for (size_t i = 0; i < data.size(); i++){
        if (data[i].carbons == carb && data[i].hydrogens == hydro){
            return i; //hydrocarb exists
        }
    }
    return -1; //hydrocarb does not exist
}

/*
    sorts hydrocarbons in place based on number of carbons and hydrogens

    parameters:
        vector<Hydrocarbon>& data: sorted based on least carbons and hydrogens to most
    return:
        nothing
*/
void sort_data(vector<Hydrocarbon>& data){
    //initialize variables
    bool sorted = false;
    while (sorted == false){
        //sorted = false if any swaps are made
        sorted = true;
        for (size_t i = 1; i < data.size(); i++){
            //swap if carbons are out of order
            if (data[i].carbons < data[i-1].carbons){
                sorted = false;
                Hydrocarbon swap = data[i];
                data[i] = data[i-1];
                data[i-1] = swap;
            }
            //swap if hydrogens are out of order
            else if (data[i].carbons == data[i-1].carbons){
                if (data[i].hydrogens < data[i-1].hydrogens){
                    sorted = false;
                    Hydrocarbon swap = data[i];
                    data[i] = data[i-1];
                    data[i-1] = swap;
                }
            }
        }
    }
}

/*
    displays vector data

    parameters:
        vector<Hydrocarbon>& data: vector to be displayed
    return:
        nothing
*/
void display_data(vector<Hydrocarbon>& data){
    //loops through and prints data in vector
    for (Hydrocarbon i: data){
        display_formula(i.carbons, i.hydrogens);
        for (string j: i.names){
            cout << ' ' << j;
        }
        cout << endl;
    }
}
/*
    formats and prints hydrocarb formula

    parameters: 
        int& carb: num of carbs
        int& hydro: num of hydros
    return:
        nothing
*/

void display_formula(int& carb, int& hydro){
    cout << 'C' << carb << 'H' << hydro;
}