#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>

class Point
{

public:
    double x; // x coordinate
    double y; // y coordinate
    // constructor
    Point(double x_coord, double y_coord);

    // compute distance between two points
    double distance(Point other) const;

    // print point coordinates
    void print() const;

    // move towards a destination point
    Point moveTowards(Point dest, double distance) const;
};

class Character
{
public:
    Character(const std::string& name, const Point& position, int hitPoints)
        : name(name), position(position), hitPoints(hitPoints) {}
    
    Character(const Character& other)
        : name(other.name), position(other.position), hitPoints(other.hitPoints) {}
    
    virtual ~Character() {}
    
    Character& operator=(const Character& other)
    {
        if (this != &other) {
            name = other.name;
            position = other.position;
            hitPoints = other.hitPoints;
        }
        return *this;
    }

    std::string getName() const { return name; }
    Point getLocation() const { return position; }
    int getHitPoints() const { return hitPoints; }
    bool isAlive() const { return hitPoints > 0; }

    double distance(const Character& other) const
    {
        return position.distance(other.position);
    }

    void hit(int damage)
    {
        hitPoints -= damage;
        if (hitPoints < 0) {
            hitPoints = 0;
        }
    }

    virtual std::string print() const = 0;

protected:
    std::string name;
    Point position;
    int hitPoints;
};

class Cowboy : public Character
{
public:
    Cowboy(const std::string &name, const Point &position);

    void shoot(Character *c);
    bool hasbullets() const;
    void reload();
    std::string print() const override;

protected:
    int bullet_amount;
};

Cowboy::Cowboy(const std::string &name, const Point &position)
    : Character(name, position, 100), bullet_amount(6) {}

void Cowboy::shoot(Character *c)
{
    if (bullet_amount > 0) {
        std::cout << name << " shoots at " << c->getName() << std::endl;
        c->hit(20);
        bullet_amount--;
    }
    else {
        std::cout << name << " is out of bullets" << std::endl;
    }
}

bool Cowboy::hasbullets() const
{
    return bullet_amount > 0;
}

void Cowboy::reload()
{
    bullet_amount = 6;
}

std::string Cowboy::print() const
{
    return "Cowboy " + name + " at (" + std::to_string(position.x) + ", " + std::to_string(position.y) + "), " +
           std::to_string(hitPoints) + " hit points, " + std::to_string(bullet_amount) + " bullets left";
}


class Ninja : public Character
{
public:
    int speed;
    Ninja(const std::string &name, const Point &position, int speed);

    void slash(Character *c);
    ~Ninja();
    string print();

};

class YoungNinja : public Ninja
{
public:
    YoungNinja(const std::string &name, const Point &position);
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

namespace ariel
{

}