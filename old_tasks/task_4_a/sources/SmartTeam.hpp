#pragma once
#include "Team.hpp"

class SmartTeam : public Team
{
public:
    SmartTeam(Character *leader);
    void attack(Team *enemyTeam);
    int calculateAttackerDamage(Character* enemyFighter);
};