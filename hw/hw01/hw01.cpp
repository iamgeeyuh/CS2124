/*
    Name: Jia Huang
    Assignment: HW01
    Decodes a message encrypted by the Caesar cypher
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

char decrypt_char(int& rotate, char& encrypted); // decrypts a character
void decrypt_line(int& rotate, string& line); // modifies and decrypts given string

int main(){
    //initalize variables
    int rotate;
    string line;
    vector<string> lines;
    //open file
    ifstream code("encrypted.txt");
    if (!code){
        cerr << "Could not open file";
        exit(1);
    }
    //get rotate
    code >> rotate;
    getline(code, line);
    //add decrypted lines to vector 
    while (getline(code, line)){
        decrypt_line(rotate, line);
        lines.push_back(line);
    }
    //print lines from back to front of the vector to reverse line order
    for (size_t i = lines.size(); i > 0; i--){
        cout << lines[i-1] << endl;
    }
    //close file
    code.close(); 
    return 0;
}

/*
decrypts a character

parameters:
    char& encrypted: character to be decrypted
    int& rotate: number of steps that encrypted character needs to be rotated by

return:
    char: 'encrypted' after rotating 'rotate' steps 
*/
char decrypt_char(int& rotate, char& encrypted){
    //if input is caps, return input
    if (encrypted < 'A' || encrypted > 'Z'){
        return encrypted;
    }
    //else subtract rotate steps from input
    char decrypt = encrypted - rotate;
    //if decrypt is less than A, adjust so it is between A and Z
    if (decrypt < 'A'){
        decrypt = 'Z' - 'A' + decrypt + 1;
    }
    //if decrypt is greater than Z, adjust so it is between A and Z
    if (decrypt > 'Z'){
        decrypt = decrypt - 'Z' + 'A';
    }
    //return decrypted input
    return decrypt;
}

/*
modifies and decrypts given string

parameters:
    int& rotate: number of steps each encrypted character needs to be rotated by
    string& line: modify each element in 'line' to be its decrypted version

return:
    nothing
*/
void decrypt_line(int& rotate, string& line){
    //run each element of line through decrypt_char()
    for (size_t i = 0; i < line.size(); i++){
        line[i] = decrypt_char(rotate, line[i]);
    }
}