#include "Team2.hpp"

Team2::Team2(Character *leader) : Team(leader)
{
    // Implementation placeholder
}

void Team2::add(Character *fighter)
{
    if (fighter != nullptr && fighters.size() < 10)
    {
        if (fighter->isTeamMate)
        {
            throw std::runtime_error("already a team mate");
        }
        fighters.push_back(fighter);
    }
    else
    {
        throw std::runtime_error("exceeded the maximum limit of 10 fighters");
    }
}
