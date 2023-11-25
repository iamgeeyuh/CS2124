/*
    Name: Jia Huang
    Assignment: rec05
    Description: Series of tasks to learn about pointers and dynamic objects
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Task 16
struct Complex{
    double real;
    double img;
};

//Task 17
class PlainOldClass{
    public:
        PlainOldClass(): x(-72){}
        int getX() const{return x;}
        void setX(int val){x = val;}
    private:
        int x;
};

//Task 18
class PlainOldClassV2{
    public:
        PlainOldClassV2(): x(-72){}
        int getX() const{return x;}
        void setX(int x){this->x = x;}
    private:
        int x;
};

//Task 28
class Colour{
    public:
        Colour(const string& name, unsigned r, unsigned g, unsigned b): name(name), r(r), g(g), b(b){}
        void display() const{
            cout << name << " (RBG: " << r << "," << g << "," << b << ")";
        }
    private:
        string name;
        unsigned r, g, b;
};

//Task 29
class SpeakerSystem{
    public:
        void vibrateSpeakerCones(unsigned signal) const{
            cout << "Playing: " << signal << "Hz sounds..." << endl;
            cout << "Buzz, buzzy, buzzer, bzap!!!\n";
        }
};

class Amplifier{
    public:
        void attachSpeakers(const SpeakerSystem& spkrs){
            if (attachedSpeakers){
                cout << "already have speakers!\n";
            }
            else{
                attachedSpeakers = &spkrs;
            }
        }
        void detachSpeakers(){
            attachedSpeakers = nullptr;
        }
        void playMusic() const{
            if (attachedSpeakers){
                attachedSpeakers->vibrateSpeakerCones(440);
            }
            else{
                cout << "No speakers attached\n";
            }
        }
    private:
        const SpeakerSystem* attachedSpeakers = nullptr;
};

//Task 30
class Person{
    public:
        Person(const string& name): name(name){}
        void movesInWith(Person& newRoommate){
            if (roomie){
                cout << "You already have a roommate!" << endl;
                return;
            }
            if (newRoommate.roomie){
                cout << "They already have a roommate!" << endl;
                return;
            }
            if (&newRoommate == this){
                cout << "You can't be your own roommate!" << endl;
            }
            roomie = &newRoommate;
            newRoommate.roomie = this;
        }
        const string& getName() const{return name;}
        const string& getRoomiesName() const{return roomie->getName();}
    private:
        Person* roomie;
        string name;
};

int main(){

    //Task 2, 3, 4, 5, 6, 7
    int x;
    x = 10;
    cout << "x = " << x << endl;

    //Task 8
    int* p;
    p = &x;
    cout << "p = " << p << endl;

    //Task 9, 10
    //p = 0xeb207ffbf4;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains  " << *p << endl;

    //Task 11
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;

    //Task 12
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    //Task 13
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;

    //Task 14
    double d(33.34);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p = *pD;
    *q = *p;
    //pD = p;
    //p = pD;

    //Task 15
    int joe = 24;
    const int sal = 19;
    int* pI;
    pI = &joe;
    *pI = 234;
    //pI = &sal; int* pI cannot be assigned to const int sal
    *pI = 7623;

    const int* pcI;
    pcI = &joe;
    //*pcI = 234; pcI is const to it points at a var whos value cannot be reassigned
    pcI = &sal;
    //*pcI = 7623; pcI is const to it points at a var whos value cannot be reassigned

    //int* const cpI; constant variables must be initialized
    //int* const cpI(&joe); constant variables cannot be reassigned
    //int* const cpI(&sal); constant variables cannot be reassigned
    //cpI = &joe; constant variables cannot be reassigned
    //*cpI = 234; works
    //cpI = &sal; constant variables cannot be reassigned
    //*cpI = 7623; works

    //const int* const cpcI; constant variables must be initialized
    //const int* const cpI(&joe); constant variables cannot be reassigned
    //const int* const cpI(&sal); constant variables cannot be reassigned
    //cpcI = &joe; constant variables cannot be reassigned
    //*cpcI = 234; cpcI is const to it points at a var whos value cannot be reassigned
    // cpcI = &sal; constant variables cannot be reassigned
    //*cpcI = 7623; pcI is const to it points at a var whos value cannot be reassigned

    //Task 16
    Complex c = {11.23, 45.67};
    Complex* pC(&c);
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

    //Task 17
    PlainOldClass poc;
    PlainOldClass* ppoc(&poc);
    cout << ppoc->getX() << endl;
    ppoc->setX(2837);
    cout << ppoc->getX() << endl;

    //Task 18
    PlainOldClassV2 pocv;  
    PlainOldClassV2* ppocv(&pocv);
    cout << ppocv->getX() << endl;
    ppocv->setX(2837);
    cout << ppocv->getX() << endl;

    //Task 19
    int* pDyn = new int(3);
    *pDyn = 17;
    cout << "The " << *pDyn << " is stored at address " << pDyn << " which is in the heap\n";

    //Task 20
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn << " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn? We can try. This might crash... " << *pDyn << ". Still here?\n";

    //Task 21
    double* pDouble = nullptr;

    //Task 22
    cout << "Can we dereference nullptr? " << *pDyn << endl;
    //cout << "Can we dereference nullptr? " << *pDouble << endl;

    //Task 24
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest;

    //Task 25
    short* pShrt = new short(5);
    delete pShrt;
    //delete pShrt;

    //Task 26
    long jumper = 12238743;
    //delete jumper; only heap objects can be deleted
    long* ptrTolong = &jumper;
    //delete ptrTolong; only heap objects can be deleted
    Complex cmplx;
    //delete cmplx; only heap objects can be deleted

    //Task 27
    vector<Complex*> comp1V;
    Complex* tmpPCmplx;
    for (size_t ndx = 0; ndx < 3; ++ndx){
        tmpPCmplx = new Complex;
        tmpPCmplx->real = ndx;
        tmpPCmplx->img = ndx;
        comp1V.push_back(tmpPCmplx);
    }
    for (size_t ndx = 0; ndx < 3; ++ndx){
        cout << comp1V[ndx]->real << endl;
        cout << comp1V[ndx]->img << endl;
    }
    for (size_t ndx = 0; ndx < 3; ++ndx){
        delete comp1V[ndx];
    }
    comp1V.clear();

    //Task 28
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;
    while (cin >> inputName >> inputR >> inputG >> inputB){
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }
    for (size_t ndx = 0; ndx < colours.size(); ++ndx){
        colours[ndx]->display();
        cout << endl;
    }
    for (size_t ndx = 0; ndx < colours.size(); ++ndx){
        delete colours[ndx];
    }

    //Task 29
    SpeakerSystem spkr;
    Amplifier amp;
    amp.playMusic();
    amp.attachSpeakers(spkr);
    amp.playMusic();
    SpeakerSystem spkr_two;
    amp.attachSpeakers(spkr_two);

    //Task 30
    Person joeBob("Joe Bob"), billyJane("Billy Jane"), janeDoe("Jane Doe");
    joeBob.movesInWith(billyJane);
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
    janeDoe.movesInWith(janeDoe);
    janeDoe.movesInWith(joeBob);
    joeBob.movesInWith(janeDoe);
 }

        

