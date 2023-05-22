#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include "Character.hpp"

namespace ariel
{

}

class Cowboy : public Character
{
protected:
    int bullet_amount;

public:
    Cowboy(const std::string &name, const Point &position);
    ~Cowboy();

    void shoot(Character *c);
    bool hasboolets() const;
    void reload();
    void attack(Character &other) const override;
    std::string print() const override;
};

class Ninja : public Character
{
public:
    int speed;
    Ninja(const std::string &name, const Point &position, int speed);

    void slash(Character *c);
    ~Ninja();

    void move(const Character *dest);
    void attack(Character &other) const override;
    std::string print() const override;
};

class YoungNinja : public Ninja
{
public:
    YoungNinja(const std::string &name, const Point &position) : Ninja(name, position, 5) {}
};

class TrainedNinja : public Ninja
{
public:
    TrainedNinja(const std::string &name, const Point &position);
};

class OldNinja : public Ninja
{
public:
    OldNinja(const std::string &name, const Point &position);
};

class Team
{
public:
    std::vector<Character *> fighters;
    Character *leader;

    Team(Character *leader);
    ~Team();
    Team &operator=(const Team &other);

    void add(Character *fighter);
    void attack(Team *enemyTeam);
    int stillAlive() const;
    void print() const;
};

class Team2 : public Team
{
public:
    Team2(Character *leader);
    Team2 &operator=(const Team2 &other);
    void attack(Team *enemyTeam);
    void print() const;
};

class SmartTeam : public Team
{
public:
    SmartTeam(Character *leader);
    SmartTeam &operator=(const SmartTeam &other);
    void attack(Team *enemyTeam);
    void print() const;
};