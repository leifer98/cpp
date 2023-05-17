#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>

namespace ariel
{

}

class Point
{

public:
    double x; // x coordinate
    double y; // y coordinate
    // constructor
    Point(double x_coord, double y_coord);
    Point();

    // compute distance between two points
    double distance(Point other) const;

    // print point coordinates
    void print() const;

    // move towards a destination point
    Point moveTowards(Point dest, double distance) const;
};

class Character
{
protected:
    std::string name;
    Point position;
    int hitPoints;

public:
    Character(const std::string &name, const Point &position, int hitPoints);

    Character(const Character &other);

    virtual ~Character();

    Character &operator=(const Character &other);
    double distance(const Character &other) const
    {
        return position.distance(other.position);
    }

    void hit(int damage);
    std::string getName() const { return name; }
    Point getLocation() const { return position; }
    int getHitPoints() const { return hitPoints; }
    bool isAlive() const;

    virtual void attack(Character &other) const = 0;
    virtual std::string print() const = 0;
};

class Cowboy : public Character
{
protected:
    int bullet_amount;

public:
    Cowboy(const std::string &name, const Point &position);
    ~Cowboy();

    void shoot(Character *c);
    bool hasbullets() const;
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