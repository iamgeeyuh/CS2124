/*
    Name: Jia Huang
    Assignment: rec08
    Description: Contains class Course and its method prototypes
*/

#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly{

    class Student;

    class Course{

        friend std::ostream& operator << (std::ostream& os, const Course& course);

        public:
            Course(const std::string& course_name);
            const std::string& get_name() const; //gets name
            bool add_student(Student*); //add student to vector if student not already in vector
            void remove_students(); //remove all students from vector

        private:
            size_t find_student(const std::string& name) const; //find index of student in vector

            std::string name;
            std::vector<Student*> students;

    };

};

#endif