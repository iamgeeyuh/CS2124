#include <iostream>
#include <fstream>
#include <string>

int main() {

    std::ifstream integers("integers.txt");
    std::ifstream text("text.txt");
    std::ifstream mixed("mixed.txt");
    if (!integers || !text || !mixed){
        std::cerr << "Could not open file\n";
        std::exit(1);
    }

    std::cout << "Task 3\n" << "========" << std::endl;
    std::cout << "Yay C++!!\n";
    
    std::cout << "Task 4\n" << "========" << std::endl;
    int num;
    int ans = 0;
    while (integers >> num){
        ans += num;
    }
    std::cout << ans << std::endl;

    std::cout << "Task 5\n" << "========" << std::endl;
    std::string word;
    while (text >> word){
        std::cout << word << std::endl;
    }

    std::cout << "Task 6\n" << "========" << std::endl;
    ans = 0;
    while (mixed >> num){
        ans += num;
    }
    std::cout << ans;
    return 0;
}