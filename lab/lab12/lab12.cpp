/*
    Name: Jia Huang
    Assignment: lab12
    Description: linked lists in c++
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

#include <cstdlib>

struct Node{
    Node(int data = 0, Node* next = nullptr):
        data(data), next(next){}
        int data;
        Node* next;
};

void splice(Node* splice, Node* prior){
    //prior_next
    Node* next = prior->next;
    //prior -> splice
    prior->next = splice;
    Node* curr = splice;
    while (curr->next){ //go to end of splice
        curr = curr->next;
    }
    //prior -> splice -> prior_next
    curr->next = next;
}

const Node* isSublist(const Node* pattern, const Node* target){
    if (!pattern){ //if pattern is nullptr it exists in target
        return target;
    }
    const Node* tar_curr = target;
    while (tar_curr){ //tar_curr goes through each node in target list
        //if tar_curr == start of pattern node then check if the rest of pattern matches the next target nodes
        if (tar_curr->data == pattern->data){ 
            const Node* pat_curr = pattern;
            const Node* check = tar_curr;
            while (pat_curr->data == check->data){ //iter through pattern and target at the same time 
                if (!pat_curr->next){ //we are at the end of pattern and everything has equaled target, so return tar_curr
                    return tar_curr;
                }
                if (!check->next){ //pattern not done iter but target ended, so pattern cannot be in target
                    return nullptr;
                }
                pat_curr = pat_curr->next;
                check = check->next;
            }
        }
        tar_curr = tar_curr->next;
    }
    return nullptr;
}

const Node* sharedListBruteForce(const Node* listA, const Node* listB){
    const Node* A_curr = listA;
    while (A_curr->next){
        const Node* B_curr = listB;
        //check each b with curr a
        while (B_curr->next){
            if (B_curr == A_curr){ 
                return B_curr;
            }
            B_curr = B_curr->next;
        }
        A_curr = A_curr->next;
    }
    return nullptr;
}

const Node* sharedListUsingSet(const Node* listA, const Node* listB){
    unordered_set<const Node*> set;
    const Node* A_curr = listA;
    while (A_curr->next){ //add every node in A to set
        set.insert(A_curr);
        A_curr = A_curr->next;
    }
    const Node* B_curr = listB;
    while (B_curr->next){ //if B node is in set then it exists in both
        if (set.find(B_curr) != set.end()){
            return B_curr;
        }
        B_curr = B_curr->next;
    }
    return nullptr;
}

void listAddHead(Node*& headPtr, int entry);
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);
void match(const Node* target, const Node* pattern);

int main(){

    Node* listOne = listBuild({5,7,9,1});

    Node* listTwo = listBuild({6,3,2});

    cout << "Part One:\n\n";
    cout << "L1: ";
    listPrint(listOne);
    cout << "L2: ";
    listPrint(listTwo);

    Node* target = listOne->next;
    cout << "Target: ";
    listPrint(target);

    cout << "Splicing L2 at target in L1\n";
    splice(listTwo, target);
    cout << "L1: ";
    listPrint(listOne);
    cout << "L2: ";
    listPrint(listTwo);

    listClear(listOne);
    // Since listTwo is now part of listOne, we have already cleared it
    //listClear(listTwo); 

    cout << "=====================\n\n"
         << "Part two: \n\n";

    // Target: 1 2 3 2 3 2 4 5 6
    target = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Target: ";
    listPrint(target);
    cout << endl;

    // Attempt Match: 1
    // Node* m1 = nullptr;
    Node* m1 = listBuild({1});    
    match(target, m1);
    listClear(m1);

    // Attempt Match: 3 9
    // Node* m2 = nullptr;
    Node* m2 = listBuild({3, 9});    
    match(target, m2);
    listClear(m2);

    // Attempt Match: 2 3
    // Node* m3 = nullptr;
    Node* m3 = listBuild({2, 3});    
    match(target, m3);
    listClear(m3);

    // Attempt Match: 2 4 5 6
    Node* m4 = listBuild({2, 4, 5, 6});    
    match(target, m4);
    listClear(m4);

    // Attempt Match: 2 3 2 4
    Node* m5 = listBuild({2, 3, 2, 4});    
    match(target, m5);
    listClear(m5);

    // Attempt Match: 5 6 7
    Node* m6 = listBuild({5, 6, 7});    
    match(target, m6);
    listClear(m6);

    // Attempt Match: 
    m1 = listBuild({6});    
    match(target, m1);
    listClear(m1);

    // Attempt Match: 
    m1 = nullptr;
    match(target, m1);

    cout << "Task Three\n";
    cout << "Target: ";
    listPrint(target);

    cout << "Matching target against self:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target));

    cout << "Matching target against dup of self:\n";
    //Node* dupOfTarget = listDup(target);
    Node* dupOfTarget = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, dupOfTarget));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, dupOfTarget));
    listClear(dupOfTarget);

    cout << "Matching target against part of self from fourth node:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target->next->next->next));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target->next->next->next));
    
    cout << "testing against another list whose fourth node"
         << " matches target's fifth node\n";
    Node* another = target->next->next->next->next;
    listAddHead(another, 7);
    listAddHead(another, 6);
    listAddHead(another, 5);
    cout << "other list:\n";
    listPrint(another);

    cout << "Brute force: ";
    const Node* startOfShared = sharedListBruteForce(target, another);
    listPrint(startOfShared);

    cout << "Using Set:   ";
    startOfShared = sharedListUsingSet(target, another);
    listPrint(startOfShared);

    // Clean up
    listClear(target);
    for (Node* p = another; p != startOfShared; ) {
	Node* pNext = p->next;
        delete p;
	p = pNext;
    }
}

void match(const Node* target, const Node* pattern) {
    cout << "Attempt pattern: ";
    listPrint(pattern);
    const Node* result = isSublist(pattern, target);
    if (result)
        listPrint(result);
    else
        cout << "Failed to match\n";
    cout << endl;
} // match

void listAddHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
} // listAddHead

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* p = headPtr;
    //    while (p != NULL) {
    while (p != nullptr) {
        cout << p->data << ' ';
        // that you know why!
        p = p->next;
    }
    cout << endl;
} // listPrint

// Need to add this to the provided functions
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
} // listClear

Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
} // listBuild
