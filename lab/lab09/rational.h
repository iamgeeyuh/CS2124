/*
    Name: Jia Huang
    Assignment: rec09
    Description: Contains class Rational and its method prototypes
*/

#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

namespace CS2124{

    class Rational{

        //iostream
        friend std::ostream& operator << (std::ostream& os, const Rational& rhs);
        friend std::istream& operator >> (std::istream& is, Rational& rhs);

        //compare 
        friend bool operator == (const Rational& lhs, const Rational& rhs);
        friend bool operator < (const Rational& lhs, const Rational& rhs);

        public:
            //constructor
            Rational(int num=0, int den=1);

            //addition
            Rational& operator += (const Rational& rhs);

            //increment
            Rational& operator ++ ();
            Rational operator ++ (int dummy);

            //if
            explicit operator bool() const;

        private:
            //normalize
            void normalize();
            int find_gcd() const;

            int num;
            int den; 

    };

    //compare
    bool operator != (const Rational& lhs, const Rational& rhs);
    bool operator <= (const Rational& lhs, const Rational& rhs);
    bool operator > (const Rational& lhs, const Rational& rhs);
    bool operator >= (const Rational& lhs, const Rational& rhs);

    //addition
    Rational operator + (const Rational& lhs, const Rational& rhs);

    //decrement
    Rational& operator -- (Rational& lhs);
    Rational operator -- (Rational& lhs, int dummy);

}

#endif