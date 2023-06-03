#pragma once
#include "Team.hpp"

class Team2 : public Team
{
public:
    Team2(Character *leader);
    void add(Character *fighter);
    
};