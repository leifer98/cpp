#pragma once
#include "Character.hpp"

class Cowboy : public Character
{
public:
    int bullet_amount;
    Cowboy(const std::string &name, const Point &position);
    ~Cowboy() override;

    Cowboy(const Cowboy &other);
    Cowboy(Cowboy &&other) noexcept;                   // Move constructor
    Cowboy &operator=(const Cowboy &other);
    Cowboy &operator=(Cowboy &&other) noexcept;        // Move assignment operator

    void shoot(Character *chara);
    bool hasboolets() const;
    void reload();
    void attack(Character &other) override;
    std::string print() const override;
};