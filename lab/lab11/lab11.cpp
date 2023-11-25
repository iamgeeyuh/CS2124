/*
    Name: Jia Huang
    Assignment: lab11
    Description: A program simulating musicians, orchestras, and their instruments
*/

#include <iostream>
#include <vector>
using namespace std;

class Instrument{ //an instrument

    public:

        virtual void make_sound() const = 0; //every instrument needs to make sound
        virtual void normal() const = 0; //every instrument needs to play normally

};

void Instrument::make_sound() const{
    cout << "To make a sound... ";
}

class Brass: public Instrument{ //a brass instrument

    public: 

        Brass(unsigned size):
            size(size){}

        void make_sound() const{ //every brass makes this sound
            Instrument::make_sound();
            cout << "blow on a mouthpiece of size " << size << endl;
        }

    private:

        unsigned size;

};

class Trumpet: public Brass{ //a trumpet, which is a brass instrument

    public:

        Trumpet(unsigned size):
            Brass(size){}

        void normal() const{
            cout << "Toot";
        } 

};

class Trombone: public Brass{ //a trombone, which is a brass instrument

    public:

        Trombone(unsigned size):
            Brass(size){}

        void normal() const{
            cout << "Blat";
        }

};


class String: public Instrument{ //a string instrument

    public:

        String(unsigned pitch):
            pitch(pitch){}

        void make_sound() const{ //every string makes this sound
            Instrument::make_sound();
            cout << "bow a string with pitch " << pitch << endl;
        }

    private:

        unsigned pitch;
};

class Violin: public String{ //a violin, which is a string instrument

    public:

        Violin(unsigned pitch):
            String(pitch){}

        void normal() const{
            cout << "Screech";
        }
};

class Cello: public String{ //a cello, which is a string instrument

    public:

        Cello(unsigned pitch):
            String(pitch){}

        void normal() const{
            cout << "Squawk";
        }

};

class Percussion: public Instrument{ //a percussion instrument

    public:

        void make_sound() const{ //every percussion makes this sound
            Instrument::make_sound();
            cout << "hit me!" << endl;
        }

};

class Drum: public Percussion{ //a drum, which is a percussion instrument

    public:

        void normal() const{
            cout << "Boom";
        }

};

class Cymbal: public Percussion{ //a cymbal, which is a percussion instrument

    public:

        void normal() const{
            cout << "Crash";
        }

};

class Musician{

    public:

        Musician():
            instr(nullptr){}

        void accept_instr(Instrument* ptr){
            instr = ptr;
        }

        Instrument* return_instr(){
            Instrument* result(instr);
            instr = nullptr;
            return result;
        }

        void test() const{
            if (instr){ 
                instr->make_sound();
            }
            else{
                cerr << "have no instr" << endl;
            }
        }

        void play() const{
            if (instr){ 
                instr->normal();
            }
        }
        
    private:
        Instrument* instr;
    
};

class MILL{ //stores instruments

    public:

        void play() const{ //every instrument in storage makes sound
            for (size_t i = 0; i != storage.size(); i++){
                if (storage[i] != nullptr){
                    storage[i]->make_sound();
                }
            }
        }

        void receive(Instrument& instr){
            instr.make_sound();
            //add instr to storage
            size_t space = find_space();
            if (space == storage.size()){ //add space in storage
                storage.push_back(&instr);
            }   
            else{ //put instr in empty space
                storage[space] = &instr;
            }
        }

        Instrument* lend(){ //lend musician an instrument
            for (size_t i = 0; i != storage.size(); i++){
                if (storage[i] != nullptr){
                    Instrument* ptr = storage[i];
                    storage[i] = nullptr;
                    return ptr;
                }
            }
            return nullptr; //no instr in storage
        }

    private:

        size_t find_space() const{ //find empty space in storage
            for (size_t i = 0; i != storage.size(); i++){
                if (storage[i] == nullptr){
                    return i;
                }
            }
            return storage.size(); //storage is full
        }

        vector<Instrument*> storage;

};

class Orch{

    public:

        void add(Musician& mus){ //adds musician to orch
            orch.push_back(&mus);
        }

        void play() const{ //every musician in orch plays normally
            for (size_t i = 0; i != orch.size(); i++){
                orch[i]->play();
            }
            cout << endl;
        }

    private:

        vector<Musician*> orch;

};

int main(){
    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ----------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
    MILL mill;
  
    cout << "Put the instruments into the MILL ------------------------------\n";
    mill.receive(trpt);
    mill.receive(violin);
    mill.receive(tbone);
    mill.receive(drum);
    mill.receive(cello);
    mill.receive(cymbal);
  
    cout << "Daily test -----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.play();
    cout << endl;
  
    cout << "Define some Musicians-------------------------------------------\n";
    Musician harpo;
    Musician groucho;
  	
    cout << "TESTING: groucho.accept_instr(mill.lend());---------------\n";
    groucho.test();	
    cout << endl;
    groucho.accept_instr(mill.lend());
    cout << endl;
    groucho.test();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.play();
  
    cout << endl << endl;
  
    groucho.test();	
    cout << endl;
    mill.receive(*groucho.return_instr());
    harpo.accept_instr(mill.lend());
    groucho.accept_instr(mill.lend());
    cout << endl;
    groucho.test();
    cout << endl;
    harpo.test();
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.play();
  
    cout << "TESTING: mill.receive(*groucho.return_instr()); ------\n";
  
    // // fifth
    mill.receive(*groucho.return_instr());
    cout << "TESTING: mill.receive(*harpo.return_instr()); ------\n";
    mill.receive(*harpo.return_instr());

  
    cout << endl;
    cout << "dailyTestPlay()" << endl;
    mill.play();
    cout << endl;
  
    cout << endl;


    //
    // PART TWO
    //
    

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.add(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.accept_instr(mill.lend());
    orch.add(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.accept_instr(mill.lend());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.accept_instr(mill.lend());
    orch.add(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receive(*ralph.return_instr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.accept_instr(mill.lend());
    orch.add(jody);

    // morgan gets an instrument from the MIL2
    morgan.accept_instr(mill.lend());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.add(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.accept_instr(mill.lend());

    // ralph gets an instrument from the MIL2
    ralph.accept_instr(mill.lend());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.add(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
}


