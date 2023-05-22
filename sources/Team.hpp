#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include "Character.hpp"
#include "Cowboy.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include "YoungNinja.hpp"

namespace ariel
{

}

class Team
{
public:
    std::vector<Character *> fighters;
    Character *captain;

    Team(Character *captain);
    Team(const Team &other);     // Copy constructor
    Team(Team &&other) noexcept; // Move constructor
    Team &operator=(const Team &other);
    Team &operator=(Team &&other) noexcept; // Move assignment operator
    ~Team();

    void add(Character *fighter);
    void attack(Team *enemyTeam);
    int stillAlive() const;
    void print() const;
};