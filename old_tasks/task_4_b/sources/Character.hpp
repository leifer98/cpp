#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include "Point.hpp"

class Character
{

public:
    bool isTeamMate;
    std::string name;
    Point position;
    int hitPoints;

    Character(const std::string &name, const Point &position, int hitPoints);

    Character(const Character &other);
    Character(Character &&other) noexcept;              // Move constructor
    Character &operator=(const Character &other);
    Character &operator=(Character &&other) noexcept;   // Move assignment operator

    virtual ~Character();

    double distance(const Character *other) const
    {
        return position.distance(other->position);
    }

    void hit(int damage);
    std::string getName() const { return name; }
    Point getLocation() const { return position; }
    int getHitPoints() const { return hitPoints; }
    bool isAlive() const;

    virtual void attack(Character &other) = 0;
    virtual std::string print() const = 0;
};

class Ninja : public Character
{
public:
    int speed;
    Ninja(const std::string &name, const Point &position, int hitpoints, int speed);

    void slash(Character *chara);
    ~Ninja() override;

    Ninja(const Ninja &other);
    Ninja(Ninja &&other) noexcept;                   // Move constructor
    Ninja &operator=(const Ninja &other);
    Ninja &operator=(Ninja &&other) noexcept;        // Move assignment operator

    void move(const Character *dest);
    void attack(Character &other) override;
    std::string print() const override;
};