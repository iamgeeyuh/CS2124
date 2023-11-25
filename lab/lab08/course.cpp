/*
    Name: Jia Huang
    Assignment: rec08
    Description: Contains definitions for class Course
*/

#include "student.h"
#include "course.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly{

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

};