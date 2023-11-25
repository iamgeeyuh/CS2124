/*
    Name: Jia Huang
    Assignment: rec07
    Description: Create a directory of people and their jobs
*/

#include <string>
#include <iostream>
using namespace std;

//Position class
class Position{
    
    friend ostream& operator << (ostream& os, const Position& position){
        os << '[' << position.title << ',' << position.salary << ']';
        return os;
    }

    public:
        Position(const string& this_title, double this_salary):
            title(this_title), salary(this_salary){}

        const string& get_title() const{return title;}
        double get_salary() const{return salary;}
        void change_salary(double new_sal){salary = new_sal;}

    private:
        string title;
        double salary;
};
//Directory class
class Directory{

    //Entry class
    class Entry{

        friend ostream& operator << (ostream& os, const Entry& entry){
            os << entry.name << ' ' << entry.room
               << ' ' << entry.phone << ", " << *entry.pos;
            return os;
        }

        public:
            Entry(const string& this_name, unsigned this_room, unsigned this_phone, Position& position):
                name(this_name), room(this_room), phone(this_phone), pos(&position){}

            const string& get_name() const{return name;}
            unsigned get_phone() const{return phone;}

        private:
            string name;
            unsigned room;
            unsigned phone;
            Position* pos;
    };

    friend ostream& operator << (ostream& os, const Directory& directory){
        os << "Directory: " << directory.company << endl;
        for (size_t ind = 0; ind != directory.size; ind++){
            os << *directory.entries[ind] << endl;
        }
        return os;
    }

    public:
        //default constructor
        Directory(const string& this_company):
            company(this_company), size(0), capacity(0), entries(nullptr){}
                     // company(this_company), size(0), capacity(1), entries(new Entry*[capacity]){}

        //copy constructor
        Directory(const Directory& directory):
            company(directory.company), size(directory.size), capacity(directory.capacity){
                cout << "constructing" << endl;
                entries = new Entry*[capacity];
                for (size_t ind = 0; ind != size; ind++){
                    entries[ind] = new Entry(*directory.entries[ind]);
                }
            }

        //destructor
        ~Directory(){
            cout << "destructing" << endl;
            for (size_t ind = 0; ind != size; ind++){
                delete entries[ind];
                entries[ind] = nullptr;
            }
            delete[] entries;
            entries = nullptr;
        }

        //assignment operator
        Directory& operator = (const Directory& directory){
            cout << "assigning" << endl;
            if (this != &directory){
                //destructing entries
                for (size_t ind = 0; ind != size; ind++){
                    delete entries[ind];
                    entries[ind] = nullptr;
                }
                delete[] entries;
                entries = nullptr;
                //copying members
                company = directory.company;
                capacity = directory.capacity;
                size = directory.size;
                //deep copying entries
                entries = new Entry*[capacity];
                for (size_t ind = 0; ind != size; ind++){
                    entries[ind] = new Entry(*directory.entries[ind]);
                }
            }
            return *this;
        }
        
        void add(const string& name, unsigned room, unsigned ph, Position& pos){
            if (size == capacity){
                if (capacity == 0){
                    capacity = 1;
                    delete [] entries;
                    entries = new Entry*[capacity];
                }
                else{
                    capacity *= 2; //double the capacity
                    Entry** old_entries = entries;
                    entries = new Entry*[capacity];
                    for (size_t ind = 0; ind != size; ind++){
                        entries[ind] = old_entries[ind];
                    }
                    delete [] old_entries;
                }
                
            }
            entries[size] = new Entry(name, room, ph, pos);
            size++;
        }

        unsigned operator[](const string& name){
            for (size_t ind = 0; ind != size; ind++){
                if (entries[ind]->get_name() == name){
                    return entries[ind]->get_phone();
                }
            }
            return 0;
        }

    private:
        Entry** entries;
        size_t size;
        size_t capacity;
        string company;
};

void do_nothing(Directory dir){
    cout << dir << endl;
}

int main(){

    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);

    Directory d("HAL");
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;	// What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << "Directory d:\n" << d << endl;
    cout << "Directory d2:\n" << d2 << endl;

    cout << "Calling doNothing\n";
    do_nothing(d2);
    cout << "Back from doNothing\n";

    // Should display 1592
    cout << d2["Carmack"] << endl;

    Directory d3("IBM");
    d3.add("Torvalds", 628, 3185, techie);
    d3.add("Ritchie", 123, 5813, techie);
    

    d2 = d3;
    // Should display 5813
    cout << d2["Ritchie"] << endl;

    cout << d2 << endl;
}
