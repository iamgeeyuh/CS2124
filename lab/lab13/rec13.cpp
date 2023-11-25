/*
    Name: Jia Huang
    Assignment: lab13
    Description: Doubly Linked List
*/

#include <cstdlib>
#include <iostream>
using namespace std;

class List{

    friend ostream& operator << (ostream& os, const List& rhs){
        Node* curr = rhs.header->next;
        while (curr->next){
            os << curr->data << " ";
            curr = curr->next;
        }
        return os;
    }

    struct Node{

        Node(int data = 0, Node* next = nullptr, Node* prev = nullptr):
            data(data), next(next), prev(prev){}

        int data;
        Node* next;
        Node* prev;

    };

    public:

        class Iterator{

            friend List;

            friend bool operator == (const Iterator& lhs, const Iterator& rhs){
                return lhs.node == rhs.node;
            }

            friend bool operator != (const Iterator& lhs, const Iterator& rhs){
                return lhs.node != rhs.node;
            }

            public:
                Iterator(Node* node):
                    node(node){}

                Iterator& operator ++ (){
                    node = node->next;
                    return *this;
                }

                Iterator& operator -- (){
                    node = node->prev;
                    return *this;
                }

                int& operator * () const {
                    return node->data;
                }

            private:
                Node* node;

        };

        List():
            header(new Node()), trailer(new Node()), len(0){
                header->next = trailer;
                trailer->prev = header;
        }
        
        void push_back(int data){
            Node* node = new Node(data); 
            Node* prev = trailer->prev;
            //insert node between prev and trailer
            prev->next = node;
            node->prev = prev;
            node->next = trailer;
            trailer->prev = node;
            //increase size
            len += 1;
        }

        int pop_back(){
            //size error
            if (len == 0){
                cerr << "ERROR: List is empty.";
                exit(1);
            }
            Node* node = trailer->prev;
            Node* prev = node->prev;
            int data = node->data;
            //delete node from heap
            delete node;
            node = nullptr;
            //connect trailer and the node before popped node
            trailer->prev = prev;
            prev->next = trailer;
            //decrease size
            len -= 1;
            //return node data
            return data;
        }

        void push_front(int data){
            Node* node = new Node(data);
            Node* next = header->next;
            //insert node between header and node
            header->next = node;
            node->prev = header;
            node->next = next;
            next->prev = node;
            len += 1;
        }

        int pop_front(){
            //size error
            if (len == 0){
                cerr << "ERROR: List is empty.";
                exit(1);
            }
            Node* node = header->next;
            Node* next = node->next;
            int data = node->data;
            //delete node from heap
            delete node;
            node = nullptr;
            //connect header and the node after popped node
            header->next = next;
            next->prev = header;
            //decrease size
            len -= 1;
            //return node data
            return data;
        }

        int& front(){
            //size error
            if (len == 0){
                return header->data;
            }
            return header->next->data;
        }

        int front() const{
            //size error
            if (len == 0){
                return header->data;
            }
            return header->next->data;
        }

        int& back(){
            //size error
            if (len == 0){
                return trailer->data;
            }
            return trailer->prev->data;
        }

        int back() const{
            //size error
            if (len == 0){
                return trailer->data;
            }
            return trailer->prev->data;
        }

        size_t size() const{
            return len;
        }

        void clear(){
            Node* curr = header->next;
            //stops at trailer
            while (curr->next){
                curr = curr->next;
                //delete everything between header and trailer
                delete curr->prev;
            }
            //reset member variables
            header->next = trailer;
            trailer->prev = header;
            len = 0;
        }

        int operator[] (size_t index) const{
            if (index >= len){
                cerr << "ERROR: Index out of range.";
            }
            Node* curr = header->next;
            int count = 0; //index 0
            while (count != index){ //stops at index-1
                curr = curr->next;
                count += 1;
            }
            return curr->data;
        }

        int& operator [] (size_t index) {
            if (index >= len){
                cerr << "ERROR: Index out of range.";
            }
            Node* curr = header->next;
            int count = 0; //index 0
            while (count != index){ //stops at index-1
                curr = curr->next;
                count += 1;
            }
            return curr->data;
        }

        Iterator begin(){
            return Iterator(header->next);
        }

        Iterator end(){
            return Iterator(trailer);
        }

        Iterator insert(Iterator iter, int data){
            Node* node = new Node(data, iter.node, iter.node->prev);
            iter.node->prev->next = node;
            iter.node->prev = node;
            len += 1;
            return Iterator(node);
        }

        Iterator erase(Iterator iter){
            if (iter.node == header || iter.node == trailer){
                return iter;
            }
            iter.node->prev->next = iter.node->next;
            iter.node->next->prev = iter.node->prev;
            Iterator result(iter.node->next);
            delete iter.node;
            len -= 1;
            return result;
        }

    private:
        Node* header;
        Node* trailer;
        size_t len;

};

void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

int main(){

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

}