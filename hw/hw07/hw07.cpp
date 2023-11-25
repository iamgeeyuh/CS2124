/*
    Name: Jia Huang
    Assignment: hw07
    Description: A program simulating nobles fighting each other with armies of warriors
*/

#include "noble.h"
#include "lord.h"
#include "chad.h"
#include "protector.h"
#include "warrior.h"
#include "wizard.h"
#include "archer.h"
#include "swordsman.h"
using namespace WarriorCraft;

using namespace std;

int main(){

    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    Chad randy("Randolf the Elder", 250); 	
    joe.battle(randy);	
    joe.battle(sam);	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    Chad barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hires(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);

}