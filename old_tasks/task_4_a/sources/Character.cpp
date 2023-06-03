#include "Character.hpp"

Character::Character(const std::string &name, const Point &position, int hitPoints)
    : name(name), position(position), hitPoints(hitPoints), isTeamMate(false)
{
    // Constructor body
    // Implementation placeholder
}

Character::Character(const Character &other)
    : name(other.name), position(other.position), hitPoints(other.hitPoints), isTeamMate(other.isTeamMate)
{
    // Copy constructor implementation
}

Character::Character(Character &&other) noexcept
    : name(std::move(other.name)), position(std::move(other.position)), hitPoints(other.hitPoints), isTeamMate(other.isTeamMate)
{
    // Move constructor implementation
}

Character &Character::operator=(const Character &other)
{
    if (this != &other)
    {
        name = other.name;
        position = other.position;
        hitPoints = other.hitPoints;
        isTeamMate = other.isTeamMate;
    }
    return *this;
}

Character &Character::operator=(Character &&other) noexcept
{
    if (this != &other)
    {
        name = std::move(other.name);
        position = std::move(other.position);
        hitPoints = other.hitPoints;
        isTeamMate = other.isTeamMate;
    }
    return *this;
}

Character::~Character() {}

void Character::hit(int damage)
{
    if (damage >= 0)
    {
        hitPoints -= damage;
        if (hitPoints < 0)
        {
            hitPoints = 0;
        }
    }
    else
    {
        throw std::invalid_argument("can't hit negative damage!");
    }
}

bool Character::isAlive() const
{
    return hitPoints > 0;
}

Ninja::Ninja(const std::string &name, const Point &position, int hitpoints, int speed)
    : Character(name, position, hitpoints), speed(speed)
{
    // Implementation placeholder
}

void Ninja::slash(Character *c)
{
    if (c != nullptr && isAlive() && distance(c) < 1.0 && c != this)
    {
        if (!c->isAlive())
        {
            throw std::runtime_error("target is dead!");
        }
        c->hit(40);
    }
    else
    {
        if (c == nullptr)
            throw std::invalid_argument("nullptr sent to function!");
        else if (!isAlive())
            throw std::runtime_error("character is dead!");
        else if (c == this)
            throw std::runtime_error("No self harm!");
    }
}

Ninja::~Ninja() {}

Ninja::Ninja(const Ninja &other)
    : Character(other), speed(other.speed)
{
    // Copy constructor implementation
}

Ninja::Ninja(Ninja &&other) noexcept
    : Character(std::move(other)), speed(other.speed)
{
    // Move constructor implementation
}

Ninja &Ninja::operator=(const Ninja &other)
{
    if (this != &other)
    {
        Character::operator=(other);
        speed = other.speed;
    }
    return *this;
}

Ninja &Ninja::operator=(Ninja &&other) noexcept
{
    if (this != &other)
    {
        Character::operator=(std::move(other));
        speed = other.speed;
    }
    return *this;
}

void Ninja::move(const Character *dest)
{
    if (dest != nullptr)
    {
        position = position.moveTowards(dest->getLocation(), speed);
    }
}

void Ninja::attack(Character &other)
{
    slash(&other);
}

std::string Ninja::print() const
{
    return "Ninja: " + getName() + " (" + std::to_string(getHitPoints()) + " HP)";
}
