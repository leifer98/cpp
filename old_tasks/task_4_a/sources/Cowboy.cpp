#include "Cowboy.hpp"

Cowboy::Cowboy(const std::string &name, const Point &position)
    : Character(name, position, 110), bullet_amount(6)
{
    // Implementation placeholder
}

Cowboy::~Cowboy() {}

Cowboy::Cowboy(const Cowboy &other)
    : Character(other), bullet_amount(other.bullet_amount)
{
    // Copy constructor implementation
}

Cowboy::Cowboy(Cowboy &&other) noexcept
    : Character(std::move(other)), bullet_amount(other.bullet_amount)
{
    // Move constructor implementation
}

Cowboy &Cowboy::operator=(const Cowboy &other)
{
    if (this != &other)
    {
        Character::operator=(other);
        bullet_amount = other.bullet_amount;
    }
    return *this;
}

Cowboy &Cowboy::operator=(Cowboy &&other) noexcept
{
    if (this != &other)
    {
        Character::operator=(std::move(other));
        bullet_amount = other.bullet_amount;
    }
    return *this;
}

void Cowboy::shoot(Character *c)
{

    if (c != nullptr && isAlive() && bullet_amount > 0 && c != this)
    {
        if (!c->isAlive())
        {
            throw std::runtime_error("target is dead!");
        }

        bullet_amount--;
        c->hit(10);
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

bool Cowboy::hasboolets() const
{
    return bullet_amount > 0;
}

void Cowboy::reload()
{
    if (!isAlive())
        throw std::runtime_error("Dead cowboy can not reload!");
    else
        bullet_amount = 6;
}

void Cowboy::attack(Character &other)
{
    shoot(&other);
}

std::string Cowboy::print() const
{
    return "Cowboy: " + getName() + " (" + std::to_string(getHitPoints()) + " HP)";
}