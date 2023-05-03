#include "player.hpp"

Player::Player() {
    name = "";
    stack_size = 0;
    cards_taken = 0;
}

Player::Player(string str) {
    name = str;
    stack_size = 0;
    cards_taken = 0;
}

int Player::stacksize() {
    return stack_size;
}

int Player::cardesTaken() {
    return cards_taken;
}