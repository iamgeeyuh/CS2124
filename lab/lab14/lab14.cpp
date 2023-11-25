/*
    Name: Jia Huang
    Assignment: lab14
    Description: stl library
*/

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// 16. even class
class Even{

    public:
        Even(int num):
            num(num){}

        bool operator () (){return (num % 2 == 0);} //returns true if num is even

    private:
        int num;

};

void print_list_iter(const list<int>& lst); //prints list with iterator
void print_list_for(const list<int>& lst); //prints list with ranged for
void print_list_even(const list<int>& lst); //prints every other list element
list<int>::const_iterator find_list(const list<int>& lst, int target); //finds index of list element
list<int>::const_iterator find_list_auto(const list<int>& lst, int target); //find index of list element with auto
list<int>::const_iterator find_list_algo(const list<int>& lst, int target); //find index of list element with find
bool is_even(int num); //returns if num is even
list<int>::const_iterator find_list_even(const list<int>& lst); //find index of first even list element
list<int>::const_iterator our_find(list<int>::const_iterator begin, list<int>::const_iterator end, int target); //find index of list element

int main(){

    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";

    vector<int> vec{0, 3, 4, 1, 7};
    for (const int i: vec){
        cout << i;
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";

    list<int> lst{vec.begin(), vec.end()};
    for (const int i: lst){
        cout << i;
    }

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";

    sort(vec.begin(), vec.end());
    for (const int i: vec){
        cout << i;
    }
    cout << endl;
    for (const int i: lst){
        cout << i;
    }

    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";

    for (size_t i = 0; i < vec.size(); i += 2){
        cout << vec[i];
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";

    /*
    for (size_t i = 0; i != lst.size(); i++){
        if (i % 2 == 0){
            cout << lst[i];
        }
    }
    */

    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";

    for (vector<int>::iterator i = vec.begin(); i < vec.end(); i += 2){
        cout << *i;
    }

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";

    bool even = true;
    for (list<int>::iterator i = lst.begin(); i != lst.end(); i++){
        if (even){
            cout << *i;
        }
        even = !even;
    }

    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";

    lst.sort();
    for (list<int>::iterator i = lst.begin(); i != lst.end(); i++){
        cout << *i;
    }

    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    
    print_list_iter(lst);

    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";

    print_list_for(lst);

    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";

    print_list_even(lst);

    cout << "\n=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";

    cout << *find_list(lst, 2) << endl;
    cout << *find_list(lst, 3);

    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";

    cout << *find_list_auto(lst, 2) << endl;
    cout << *find_list_auto(lst, 3);

    cout << "\n=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";

    cout << *find_list_algo(lst, 2) << endl;
    cout << *find_list_algo(lst, 3);

    cout << "\n=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";

    cout << *find_list_even(lst);

    cout << "\n=======\n";

    // 16. Functor
    cout << "Task 16:\n";

    Even two{2};
    cout << two() << endl;
    Even three{3};
    cout << three();


    cout << "\n=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";

    cout << *[](const list<int>& lst){
        return find_if(lst.begin(), lst.end(), is_even);
    }(lst);

    cout << "\n=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";

    int* arr = new int(lst.size());
    copy(lst.begin(), lst.end(), arr);
    for (size_t i = 0; i != lst.size(); i++){
        cout << arr[i] << endl;
    }
    cout << *find(arr, arr + lst.size(), 2) << endl;
    cout << *find(arr, arr + lst.size(), 3);
    delete [] arr;

    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";

    cout << *our_find(lst.begin(), lst.end(), 2) << endl;
    cout << *our_find(lst.begin(), lst.end(), 3);

    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";

    cout << *our_find(lst.begin(), lst.end(), 2) << endl;
    cout << *our_find(lst.begin(), lst.end(), 3);

    cout << "\n=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";

    ifstream ifs("pooh-nopunc.txt");
    vector<string> words;
    string word;

    if (!ifs){
        cerr << "invalid file";
        exit(1);
    }
    while (ifs >> word){
        if (find(words.begin(), words.end(), word) == words.end()){
            words.push_back(word);
        }
    }
    ifs.close();
    cout << "size: " << words.size();
    /*
    for (size_t i = 0; i != words.size(); i++){
        cout << '\n' << words[i];
    }
    */

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";

    ifstream ifb("pooh-nopunc.txt");
    set<string> st;

    if (!ifb){
        cerr << "invalid file";
        exit(1);
    }
    while (ifb >> word){
        st.insert(word);
    }
    ifb.close();

    cout << "size: " << st.size();
    /*
    for (size_t i = 0; i != st.size(); i++){
        cout << '\n' << st[i];
    }
    */

    cout << "\n=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";

    ifstream ifc("pooh-nopunc.txt");
    int pos = 0;
    map<string, vector<int>> word_map;

    if (!ifc){
        cerr << "invalid file";
        exit(1);
    }
    while (ifc >> word){
        pos += 1;
        word_map[word].push_back(pos);
    }
    ifc.close();

    cout << "words: " << word_map.size();
    /*
    for (auto pair: word_map){
        cout << "word: " << pair.first << "| positions: ";
        for (size_t i = 0; i != pair.second.size(); i++){
            cout << pair.second[i] << ' ';
        }
        cout << endl;
    }
    */

    cout << "\n=======\n";
}

// 9. prints list with iterator
void print_list_iter(const list<int>& lst){ 
    
    for (list<int>::const_iterator i = lst.begin(); i != lst.end(); i++){
        cout << *i;
    }

}

// 10. prints list with ranged for
void print_list_for(const list<int>& lst){ 

    for (const int i: lst){
        cout << i;
    }

}

// 11. prints every other list element
void print_list_even(const list<int>& lst){ 

    bool even = true;
    for (auto i = lst.begin(); i != lst.end(); i++){
        if (even){
            cout << *i;
        }
        even = !even;
    }

}

// 12. finds index of list element
list<int>::const_iterator find_list(const list<int>& lst, int target){ 

    for (list<int>::const_iterator i = lst.begin(); i != lst.end(); i++){
        if (*i == target){ //target found
            return i;
        }
    }
    //target not found
    return lst.end();

}

// 13. finds index of list element with auto
list<int>::const_iterator find_list_auto(const list<int>& lst, int target){ 

    for (auto i = lst.begin(); i != lst.end(); i++){
        if (*i == target){ //target found
            return i;
        }       
    }
    //targt not found
    return lst.end();

}

// 14. find index of list element with find
list<int>::const_iterator find_list_algo(const list<int>& lst, int target){

    return find(lst.begin(), lst.end(), target);

} 

// 15. returns if num is even
bool is_even(int num){
    return (num % 2 == 0);
}

// 15. find index of first even list element
list<int>::const_iterator find_list_even(const list<int>& lst){

    return find_if(lst.begin(), lst.end(), is_even);

}

// 19. find index of list element
list<int>::const_iterator our_find(list<int>::const_iterator begin, list<int>::const_iterator end, int target){

    cout << "our_find" << endl;
    for (list<int>::const_iterator i = begin; i != end; i++){
        if (*i == target){ //target found
            return i;
        }
    }
    //target not found
    return end;

}

// 20. find index template
template <typename B, typename T>
B our_find(B start, B stop, T target){

    cout << "our_find template" << endl;
    for (B iter = start; iter != stop; iter++){
        if (*iter == target){ //target found
            return iter;
        }
    }
    //target not found
    return stop;

}