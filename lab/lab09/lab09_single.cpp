/*
    Name: Jia Huang
    Assignment: rec09
    Description: Calculates rational numbers
*/

#include <iostream>
using namespace std;

class Rational{

    //iostream
    friend ostream& operator << (ostream& os, const Rational& rhs);
    friend istream& operator >> (istream& is, Rational& rhs);

    //compare 
    friend bool operator == (const Rational& lhs, const Rational& rhs);
    friend bool operator < (const Rational& lhs, const Rational& rhs);

    public:
        //constructor
        Rational(int num = 0, int den = 1);

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

int main(){

    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // How does this manage to work?
    // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;

}

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