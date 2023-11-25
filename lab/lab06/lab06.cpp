/*
     Name: Jia Huang
     Assignment: rec06
     Description: Program simulating lab grading 
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//section with time slot to be assigned to a TA
class Section{

     friend ostream& operator << (ostream& os, const Section& section);

     public:
          //this_day and this_hour constructs Time 
          Section(const string& this_name, const string& this_day, unsigned this_hour):
               name(this_name), time(Time{this_day, this_hour}){}

          //student's weekly lab record
          class Record{

               friend ostream& operator << (ostream& os, const Record& record);

               public:
                    //grades initializes as 14 weeks of absences
                    Record(const string& this_name):
                         name(this_name), grades(14, -1){}

                    //getters
                    const string& get_name() const{return name;}

                    void addGrade(int grade, int week){ //adds grade to student's record
                         grades[week-1] = grade;
                    }

               private:
                    string name;
                    vector<int> grades;
          };

          void addStudent(const string& name){records.push_back(new Record(name));} //adds new student record
          void addGrade(const string& name, int grade, int week){ //calls record to add grade to student's record
               for (Record* ptr: records){
                    //find student
                    if (ptr->get_name() == name){
                         ptr->addGrade(grade, week); //call record
                         break;
                    }
               }
          }

          //copy constructor
          Section(const Section& section): 
               name(section.name), 
               time(section.time){
               //copy vector
               for (size_t ind = 0; ind != section.records.size(); ind++){
                    records.push_back(new Record(*section.records[ind]));
               }
          }

          //destructor
          ~Section(){
               cout << "Section " << name << " is being deleted" << endl;
               for (Record* ptr: records){
                    cout << "Deleting " << ptr->get_name() << endl;
                    delete ptr;
               }
               records.clear();
          }

     private:

          //section's time slot
          class Time{

               friend ostream& operator << (ostream& os, const Time& time);

               public:
                    Time(const string& this_day, unsigned this_hour): 
                         day(this_day), hour(this_hour){}

               private:
                    string day;
                    unsigned hour;
          };

          friend ostream& operator << (ostream& os, const Time& time);

          Time time;
          string name;
          vector<Record*> records; 

};

class LabWorker{

     friend ostream& operator << (ostream& os, const LabWorker& worker);

     public:
          LabWorker(const string& this_name):
               name(this_name), section(nullptr){}
          
          void addSection(Section& section){this->section = &section;} //assign section
          void addGrade(const string& name, int grade, int week){ //call section to add grade to record
               section->addGrade(name, grade, week); //call section
          }

     private:
          string name;
          Section* section;

};

//time ostream operator
ostream& operator << (ostream& os, const Section::Time& time){
     os << " Time slot: [Day: " << time.day << ", Start time: ";
     //am times
     if (time.hour <= 12){
          os << time.hour << "am], ";
     }
     //pm times
     else{
          os << time.hour - 12 << "pm], ";
     }
     return os;
}

//record ostream operator
ostream& operator << (ostream& os, const Section::Record& record){
     os << "Name: " << record.name << ", Grades: ";
     for (int grade: record.grades){
          os << grade << " ";
     }
     os << endl;
     return os;
}

//section ostream operator
ostream& operator << (ostream& os, const Section& section){
     os << "Section: " << section.name << section.time << "Students: ";
     //if lab records are empty
     if (section.records.size() == 0){
          os << "None" << endl;
     }
     else{
          os << endl;
          for (Section::Record* ptr: section.records){
               os << *ptr;
          }
     }
     return os;
}

//lab worker ostream operator
ostream& operator << (ostream& os, const LabWorker& worker){
     if (!worker.section){
          os << worker.name << " does not have a section" << endl;
     }
     else{
          os << worker.name << " has " << *worker.section;
     }
     return os;
}

// Test code
void doNothing(Section sec){ 
     cout << sec << endl; 
}

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
    

} // main
