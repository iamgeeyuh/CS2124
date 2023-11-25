/*
    Name: Jia Huang
    Assignment: rec08
    Description: Contains definitions for class Student
*/

#include "student.h"
#include "course.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly{

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

};