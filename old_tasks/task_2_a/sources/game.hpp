#include <iostream>
#include <vector>

#pragma once
#include "card.hpp"
#include "player.hpp"
using namespace std;

namespace ariel {
    
}

class Game {
    Player *player1;
    Player *player2;
    std::vector<Card> p1_hand;
    std::vector<Card> p2_hand;
    std::vector<Card> p1_winnings;
    std::vector<Card> p2_winnings;

    //for stats
    int sub_turn_counter;
    int turn_counter;
    int draw_counter;
    int p1_wins_counter;
    int p2_wins_counter;
    string last_turn;
    string log;

public:
    Game(Player &player1, Player &player2);     
    void playTurn();   
    void printLastTurn();   
    void playAll();   
    void printWiner();   
    void printLog();   
    void printStats();
    void devide_cards();   
};