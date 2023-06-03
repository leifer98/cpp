#pragma once
#include "Character.hpp"

constexpr int T_HITPOINTS = 120;
constexpr int T_SPEED = 12;

class TrainedNinja : public Ninja
{
public:
    TrainedNinja(const std::string &name, const Point &position)
    : Ninja(name, position,T_HITPOINTS, T_SPEED) {}
};