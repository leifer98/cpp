#pragma once
#include "Character.hpp"

constexpr int Y_HITPOINTS = 100;
constexpr int Y_SPEED = 14;

class YoungNinja : public Ninja
{
public:
    YoungNinja(const std::string &name, const Point &position) 
    : Ninja(name, position,Y_HITPOINTS, Y_SPEED) {}
};
