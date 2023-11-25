//Jia Huang
//lab02
//A program implementing Conway's Game of Life

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    //initialize world
    string line;
    vector<string> world;
    ifstream life("life.txt");

    if (!life){
        cerr << "Could not open file" << endl;
        exit(1);
    }
    while (life >> line){
        world.push_back(line);
    }
    life.close();

    cout << "Initial world" << endl;
    for (size_t i = 0; i < world.size(); i++){
        cout << world[i] << endl;
    }
    cout << "===========================" << endl;

    vector<string> status = world;
    size_t col_start = 0;
    size_t col_end = world[0].size() - 1;
    size_t row_start = 0;
    size_t row_end = world.size() - 1;

    //compute next generation
    for (int i = 1; i < 11; i++){
        for (size_t r = 0; r < world.size(); r++){
            for (size_t c = 0; c < world[r].size(); c++){
                int count = 0;
                if (r != row_start){
                    if (world[r-1][c] == '*'){
                    count++;
                    }
                }
                if (r != row_end){
                    if (world[r+1][c] == '*'){
                    count++;
                    }
                }
                if (r != row_start && c != col_start){
                    if (world[r-1][c-1] == '*'){
                    count++;
                    }
                }
                if (c != col_start){
                    if (world[r][c-1] == '*'){
                    count++;
                    }
                }
                if (r != row_end && c != col_start){
                    if (world[r+1][c-1] == '*'){
                    count++;
                    }
                }
                if (r != row_start && c != col_end){
                    if (world[r-1][c+1] == '*'){
                    count++;
                    }
                }
                if (c != col_end){
                    if (world[r][c+1] == '*'){
                    count++;
                    }
                }
                if (r != row_end && c != col_end){
                    if (world[r+1][c+1] == '*'){
                    count++;
                    }
                }
                if (world[r][c] == '*'){
                    if (count == 2 || count == 3){
                        status[r][c] = '*';
                    }
                    else{
                        status[r][c] = '-';
                    }
                }
                else if (count == 3){
                    status[r][c] = '*';
                }
                else{
                    status[r][c] = '-';
                }
            }
        }

        //print generation
        world = status;
        cout << "Generation: " << i << endl;
        for (size_t i = 0; i < world.size(); i++){
            cout << world[i] << endl;
        }
        cout << "====================" << endl;
    }
    return 0;
}
    


