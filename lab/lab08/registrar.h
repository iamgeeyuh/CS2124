/*
    Name: Jia Huang
    Assignment: rec08
    Description: Contains class registrar and its method prototypes
*/

#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly{

    class Course;

    class Student;

    class Registrar{

        friend std::ostream& operator << (std::ostream& os, const Registrar& registrar);

    public:
        Registrar();
        bool add_course(const std::string&); //add course if it doesn't exist
        bool add_student(const std::string&); //add student if it doesn't exist
        bool enroll_student(const std::string& student_name, //enroll student in course
                            const std::string& course_name); 
        bool cancel_course(const std::string& course_name); //delete course
        void purge(); //delete course and student vector

    private:
        size_t find_student(const std::string&) const; //find index of student
        size_t find_course(const std::string&) const; //find index of course

        std::vector<Course*> courses;
        std::vector<Student*> students;

    };
    
};

#endif