#pragma once
#include "Character.hpp"

constexpr int O_HITPOINTS = 150;
constexpr int O_SPEED = 8;

class OldNinja : public Ninja
{
public:
    OldNinja(const std::string &name, const Point &position)
    : Ninja(name, position,O_HITPOINTS, O_SPEED) {}
};