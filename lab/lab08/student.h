/*
    Name: Jia Huang
    Assignment: rec08
    Description: Contains class Student and its method prototypes
*/

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly{

    class Course;

    class Student{

        friend std::ostream& operator << (std::ostream& os, const Student& student);

        public:
            Student(const std::string& name);
            const std::string& get_name() const; //get name
            bool add_course(Course*); //add course to vector if it does not exist already

            void remove_course(Course*); //remove from course

        private:
            size_t find_course(const std::string& name) const; //find index of course

            std::string name;
            std::vector<Course*> courses;

    };

};

#endif