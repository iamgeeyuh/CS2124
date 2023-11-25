/*
    Name: Jia Huang
    Assignment: lab10
    Description: 
*/

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial{

    public:

        PrintedMaterial(unsigned pages):
            pages(pages){}

        virtual void display_pages() const = 0;

    private:
        unsigned pages;

};

void PrintedMaterial::display_pages() const{
    cout << pages << endl;
}

class Magazine: public PrintedMaterial{

    public:
        Magazine(unsigned pages):
            PrintedMaterial(pages){}
        
        void display_pages() const{
            PrintedMaterial::display_pages();
        }

    private:

};

class Book: public PrintedMaterial{

    public:
        Book(unsigned pages):
            PrintedMaterial(pages){}

        void display_pages() const{
            PrintedMaterial::display_pages();
        }

    private:

};

class Textbook: public Book{

    public:

        Textbook(unsigned pages, unsigned index):
            Book(pages), index(index){}

        void display_pages() const{
            cout << "Pages: ";
            PrintedMaterial::display_pages();
            cout << "Index Pages: " << index << endl;
        }

    private:
        unsigned index;

};

class Novel: public Book{

    public:
        Novel(unsigned pages):
            Book(pages){}

        void display_pages() const{
            PrintedMaterial::display_pages();
        }

    private:

};

int main() {

    Textbook text(5430, 23);
    Novel novel(213);
    Magazine mag(6);

    text.display_pages();
    novel.display_pages();
    mag.display_pages();
    cout << "===========" << endl;

    vector<PrintedMaterial*> vec;
    vec.push_back(&text);
    vec.push_back(&novel);
    vec.push_back(&mag);

    for (const PrintedMaterial* ptr: vec){
        ptr->display_pages();
    }

}