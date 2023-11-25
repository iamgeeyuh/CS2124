#include <iostream>
#include <vector>
#include <string>
using namespace std;

void add_one(int some_int){
    some_int++;
}

int main(){
    int x = 17;
    add_one(x);
    cout << x << endl;
}