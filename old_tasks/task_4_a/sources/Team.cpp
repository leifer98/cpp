#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <cmath>

#include "Team.hpp"

Point::Point(double x_coord, double y_coord)
{
    // Implementation placeholder
}

Point::Point()
{
    // Implementation placeholder
}

double Point::distance(Point other) const
{
    // Implementation placeholder
    return 0.0;
}

void Point::print() const
{
    // Implementation placeholder
}

Point Point::moveTowards(Point dest, double distance) const
{
    // Implementation placeholder
    return Point(0.0, 0.0);
}

Character::Character(const std::string &name, const Point &position, int hitPoints)
{
    // Implementation placeholder
}

Character::Character(const Character &other)
{
    // Implementation placeholder
}

Character::~Character()
{
    // Implementation placeholder
}

Character &Character::operator=(const Character &other)
{
    // Implementation placeholder
    return *this;
}

void Character::hit(int damage)
{
    // Implementation placeholder
}

bool Character::isAlive() const
{
    // Implementation placeholder
    return false;
}

Cowboy::Cowboy(const std::string &name, const Point &position)
    : Character(name, position, 0), bullet_amount(0)
{
    // Implementation placeholder
}

Cowboy::~Cowboy()
{
    // Implementation placeholder
}

void Cowboy::shoot(Character *c)
{
    // Implementation placeholder
}

bool Cowboy::hasbullets() const
{
    // Implementation placeholder
    return false;
}

void Cowboy::reload()
{
    // Implementation placeholder
}

void Cowboy::attack(Character &other) const
{
    // Implementation placeholder
}

std::string Cowboy::print() const
{
    // Implementation placeholder
    return "";
}

Ninja::Ninja(const std::string &name, const Point &position, int speed)
    : Character(name, position, 0), speed(speed)
{
    // Implementation placeholder
}

Ninja::~Ninja()
{
    // Implementation placeholder
}

void Ninja::slash(Character *c)
{
    // Implementation placeholder
}

void Ninja::move(const Character *dest)
{
    // Implementation placeholder
}

void Ninja::attack(Character &other) const
{
    // Implementation placeholder
}

std::string Ninja::print() const
{
    // Implementation placeholder
    return "";
}

TrainedNinja::TrainedNinja(const std::string &name, const Point &position)
    : Ninja(name, position, 0)
{
    // Implementation placeholder
}

OldNinja::OldNinja(const std::string &name, const Point &position)
    : Ninja(name, position, 0)
{
    // Implementation placeholder
}

Team::Team(Character *leader) : leader(leader)
{
    // Implementation placeholder
}

Team::~Team()
{
    // Implementation placeholder
}

Team &Team::operator=(const Team &other)
{
    // Implementation placeholder
    return *this;
}

void Team::add(Character *fighter)
{
    // Implementation placeholder
}

void Team::attack(Team *enemyTeam)
{
    // Implementation placeholder
}

int Team::stillAlive() const
{
    // Implementation placeholder
    return 0;
}

void Team::print() const
{
    // Implementation placeholder
}

Team2::Team2(Character *leader) : Team(leader)
{
    // Implementation placeholder
}

Team2 &Team2::operator=(const Team2 &other)
{
    // Implementation placeholder
    return *this;
}

void Team2::attack(Team *enemyTeam)
{
    // Implementation placeholder
}

void Team2::print() const
{
    // Implementation placeholder
}

SmartTeam::SmartTeam(Character *leader) : Team(leader)
{
    // Implementation placeholder
}

SmartTeam &SmartTeam::operator=(const SmartTeam &other)
{
    // Implementation placeholder
    return *this;
}

void SmartTeam::attack(Team *enemyTeam)
{
    // Implementation placeholder
}

void SmartTeam::print() const
{
    // Implementation placeholder
}
