/*
    Name: Jia Huang
    Assignment: rec08
    Description: Contains definitions for class Registrar
*/

#include "registrar.h"
#include "course.h"
#include "student.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace BrooklynPoly{

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

};
