#pragma once
#include <iostream>
using namespace std;

class Player {
    string name;
    int stack_size;
    int cards_taken;

public:
    Player(); 
    Player(string str); 
    
    int stacksize();  
    int cardesTaken();  
    void set_stack_size(int num) {this->stack_size = num;}
    void set_cards_taken(int num) {this->cards_taken = num;}
    string getName() const { return this->name; }
};