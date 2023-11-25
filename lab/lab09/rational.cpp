/*
    Name: Jia Huang
    Assignment: rec09
    Description: Contains definitions for class Rational
*/

#include "rational.h"
using namespace std;

namespace CS2124{

    //constructor
    Rational::Rational(int num, int den): //rational
        num(num), den(den){
            normalize();} //normalize initial rational

    //normalize
    void Rational::normalize(){ //normalize rational
        //find gcd
        int gcd = find_gcd();
        //reduce to smallest fraction
        num /= gcd;
        den /= gcd;
        //check for negative in den
        if (den < 0){
            den *= -1;
            num *= -1;
        }
    }

    int Rational::find_gcd() const { //find gcd
        int denom = abs(den);
        int numer = abs(num);
        while (denom != 0) {
            int temp = numer % denom;
            numer = denom;
            denom = temp;
        }
        return numer;
    }

    //iostream
    ostream& operator << (ostream& os, const Rational& rhs){
        os << rhs.num << '/' << rhs.den << endl;
        return os;
    }

    istream& operator >> (istream& is, Rational& rhs){
        char slash;
        is >> rhs.num >> slash >> rhs.den;
        rhs.normalize(); //normalize input
        return is;
    }

    //addition
    Rational& Rational::operator += (const Rational& rhs){
        num = (num*rhs.den) + (rhs.num*den); //add numerator
        den *= rhs.den; //match denominator
        normalize();
        return *this;
    }

    Rational operator + (const Rational& lhs, const Rational& rhs){
        Rational sum(lhs);
        sum += rhs;
        return sum;
    }

    //compare
    bool operator == (const Rational& lhs, const Rational& rhs){
        return (lhs.num == rhs.num) && (lhs.den == rhs.den);
    }

    bool operator < (const Rational& lhs, const Rational& rhs){
        //find numerator when denominator is the same
        int l_num = (lhs.num*rhs.den);
        int r_num = (rhs.num*lhs.den);
        return l_num < r_num;
    }

    bool operator != (const Rational& lhs, const Rational& rhs){
        return !(lhs == rhs);
    }

    bool operator <= (const Rational& lhs, const Rational& rhs){
        return (lhs < rhs) || (lhs == rhs);
    }

    bool operator > (const Rational& lhs, const Rational& rhs){
        return !(lhs <= rhs);
    }

    bool operator >= (const Rational& lhs, const Rational& rhs){
        return !(lhs < rhs);
    }

    //increment
    Rational& Rational::operator ++ (){
        num += den;
        return *this;
    }

    Rational Rational:: operator ++ (int dummy){
        Rational original(*this);
        num += den;
        return original;
    }

    //decrement
    Rational& operator -- (Rational& lhs){
        Rational sub(-1);
        lhs += sub;
        return lhs;
    }

    Rational operator -- (Rational& lhs, int dummy){
        Rational original(lhs);
        Rational sub(-1);
        lhs += sub;
        return original;
    }

    //if
    Rational::operator bool() const{
        return num != 0;
    }

}