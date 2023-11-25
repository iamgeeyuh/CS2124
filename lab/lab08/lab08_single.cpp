/*
    Name: Jia Huang
    Assignment: rec08
    Description: A program simulating a school registrar with courses and students
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Student;

class Course{

    friend ostream& operator << (ostream& os, const Course& course);

    public:
        Course(const string& course_name);
        const string& get_name() const; //gets name
        bool add_student(Student*); //add student to vector if student not already in vector
        void remove_students(); //remove all students from vector

    private:
        size_t find_student(const string& name) const; //find index of student in vector

        string name;
        vector<Student*> students;

};

class Student{

    friend ostream& operator << (ostream& os, const Student& student);

    public:
        Student(const string& name);
        const string& get_name() const; //get name
        bool add_course(Course*); //add course to vector if it does not exist already

        void remove_course(Course*); //remove from course

    private:
        size_t find_course(const string& name) const; //find index of course

        string name;
        vector<Course*> courses;

};

class Registrar{

    friend ostream& operator << (ostream& os, const Registrar& registrar);

    public:
        Registrar();
        bool add_course(const string&); //add course if it doesn't exist
        bool add_student(const string&); //add student if it doesn't exist
        bool enroll_student(const string& student_name, //enroll student in course
                            const string& course_name); 
        bool cancel_course(const string& course_name); //delete course
        void purge(); //delete course and student vector

    private:
        size_t find_student(const string&) const; //find index of student
        size_t find_course(const string&) const; //find index of course

        vector<Course*> courses;
        vector<Student*> students;

};

int main(){

    Registrar registrar;

    cout << "No courses or students added yet" << endl;
    cout << registrar << endl;

    cout << "AddCourse CS101.001" << endl;
    registrar.add_course("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.add_student("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.add_course("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enroll_student("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enroll_student("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enroll_student("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancel_course("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;

    return 0;
}

/* Course methods*/

ostream& operator << (ostream& os, const Course& course){
    os << course.name << ':';
    //no students
    if (course.students.size() == 0){
        os << " No Students" << endl;
        return os;
    }
    //there are students
    for (size_t i = 0; i != course.students.size(); i++){
        os << ' ' << course.students[i]->get_name();
    }
    os << endl;
    return os;
}

Course::Course(const string& this_name): name(this_name){}

const string& Course::get_name() const{return name;}

bool Course::add_student(Student* student){
    //find index of student
    size_t ind = find_student(student->get_name());
    if (ind == students.size()){ //student not already in vector
        students.push_back(student);
        return true;
    }
    //student already in vector
    return false;
}

void Course::remove_students(){
    for (size_t i = 0; i != students.size(); i++){
        students[i]->remove_course(this); //remove course from student courses
    }
    students.clear();
}

size_t Course:: find_student(const string& name) const{
    for (size_t i = 0; i != students.size(); i++){
        if (students[i]->get_name() == name){ //student found
            return i;
        }
    }
    //student does not exist
    return students.size();
}

/* Student methods*/

ostream& operator << (ostream& os, const Student& student){
    os << student.name << ':';
    //no courses
    if (student.courses.size() == 0){
        os << " No Courses" << endl;
        return os;
    }
    //there are courses
    for (size_t i = 0; i != student.courses.size(); i++){
        os << ' ' << student.courses[i]->get_name();
    }
    os << endl;
    return os;
}

Student::Student(const string& this_name): name(this_name){}

const string& Student::get_name() const{return name;}

bool Student::add_course(Course* course){
    //find index of course
    size_t ind = find_course(course->get_name());
    if (ind == courses.size()){ //course not already in vector
        courses.push_back(course);
        return true;
    }
    //course already in vector
    return false;
}

void Student::remove_course(Course* course){
    //find index of course
    size_t ind = find_course(course->get_name());
    for (size_t i = ind; i != courses.size()-1; i++){
        //offset vector
        courses[i] = courses[i+1];
    }
    //delete last duplicate course
    courses.pop_back();
}

size_t Student::find_course(const string& name) const{
    for (size_t i = 0; i != courses.size(); i++){
        if (courses[i]->get_name() == name){ //course in vector
            return i;
        }
    }
    //course not in vector
    return courses.size();
}

/* Registrar methods*/

ostream& operator << (ostream& os, const Registrar& registrar){
    os << "Registrar's Report" << endl;
    //print courses
    os << "Courses:" << endl;
    for (size_t i = 0; i != registrar.courses.size(); i++){
        os << *registrar.courses[i];
    }
    //print students
    os << "Students:" << endl;
    for (size_t i = 0; i != registrar.students.size(); i++){
        os << *registrar.students[i];
    }
    return os;
}

Registrar::Registrar(){}

bool Registrar::add_course(const string& name){
    //find index of course
    size_t ind = find_course(name);
    if (ind == courses.size()){ //course does not exist
        courses.push_back(new Course(name));
        return true;
    }
    //course already exists
    return false;
}

bool Registrar::add_student(const string& name){
    //find index of course
    size_t ind = find_student(name);
    if (ind == students.size()){ //student does not exist
        students.push_back(new Student(name));
        return true;
    }
    //student already exists
    return false;
}

bool Registrar::enroll_student(const string& student_name,
                               const string& course_name){
    size_t student_ind = find_student(student_name);
        if (student_ind == students.size()){ //student does not exist 
            return false;
        }
    size_t course_ind = find_course(course_name);
        if (course_ind == courses.size()){ //course does not exist 
            return false;
        }
    if (students[student_ind]->add_course(courses[course_ind])){ //successfully enroll student in course
        courses[course_ind]->add_student(students[student_ind]);
        return true;
    }
    //failed to enroll student
    return false;
}

bool Registrar::cancel_course(const string& course){
    size_t ind = find_course(course);
    if (ind != courses.size()){ //course exists
        //delete course
        courses[ind]->remove_students();
        delete courses[ind];
        courses[ind] = nullptr;
        //remove course from courses vector
        for (size_t i = ind; i != courses.size()-1; i++){
            //offset vector
            courses[i] = courses[i+1];
        }
        //remove last duplicate course
        courses.pop_back();
        return true;
    }
    return false;
}

void Registrar::purge(){
    //delete courses
    for (size_t i = 0; i != courses.size(); i++){
        delete courses[i];
        courses[i] = nullptr;
    }
    courses.clear();
    //delete students
    for (size_t i = 0; i != students.size(); i++){
        delete students[i];
        students[i] = nullptr;
    }
    students.clear();
}

size_t Registrar:: find_student(const string& name) const{
    for (size_t i = 0; i != students.size(); i++){
        if (students[i]->get_name() == name){ //student found
            return i;
        }
    }
    //student does not exist
    return students.size();
}

size_t Registrar::find_course(const string& name) const{
    for (size_t i = 0; i != courses.size(); i++){
        if (courses[i]->get_name() == name){ //course in vector
            return i;
        }
    }
    //course not in vector
    return courses.size();
}