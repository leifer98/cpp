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
    int get_stack_size() const {return this->stack_size;}
    void set_stack_size(int num) {this->stack_size = num;}
    int get_cards_taken() const {return this->cards_taken;}
    void set_cards_taken(int num) {this->cards_taken = num;}
};