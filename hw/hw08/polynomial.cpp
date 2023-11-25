/*
    Name: Jia Huang
    Assignment: hw08
    Description: Method definitions for Polynomial class
*/

#include "polynomial.h"
using namespace std;

Polynomial::Polynomial():
    degree(0), head(new Node(0, new Node(0))){}

Polynomial::Polynomial(const vector<int> terms):
    degree(terms.size()-1), head(new Node()){
        Node* curr = head;
        for (size_t i = 0; i != terms.size(); i++){
            curr->next = new Node(terms[i]);
            
        }
    }