/*
    Name: Jia Huang
    Assignment: hw08
    Description: Header for Polynomial class
*/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>

class Polynomial{

    friend ostream& std::operator << (ostream& os, const Polynomial& rhs);
    friend bool operator == (const Polynomial& lhs, const Polynomial& rhs);
    friend bool operator != (const Polynomial& lhs, const Polynomial& rhs);
    friend Polynomial& operator + (const Polynomial& lhs, const Polynomial& rhs);

    struct Node{ //node struct

        Node(int data = 0, Node* next = nullptr):
            data(data), next(next){}

        int data;
        Node* next;
    };

    public:
        //constructors
        Polynomial();
        Polynomial(const std::vector<int> terms);

        //copy control
        Polynomial(const Polynomial& rhs);
        ~Polynomial();
        Polynomial& operator = (const Polynomial& rhs);

        Polynomial& operator += (const Polynomial& rhs);

        int eval(int x) const;

    private:
        Node* head;
        int degree;

};

#endif