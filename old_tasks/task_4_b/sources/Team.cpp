#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <cmath>

#include "Team.hpp"

Team::Team(Character *captain) : captain(captain)
{
    if (captain != nullptr)
    {
        if (captain->isTeamMate)
        {
            throw std::runtime_error("already a team mate");
        }
        fighters.push_back(captain);
        captain->isTeamMate = true;
    }
}

Team::Team(const Team &other)
    : fighters(other.fighters.size()), captain(nullptr)
{
    for (size_t i = 0; i < other.fighters.size(); ++i)
    {
        Character *fighter = other.fighters[i];
        if (fighter != nullptr)
        {
            Character *clone = fighter;
            fighters[i] = clone;
            if (fighter == other.captain)
            {
                captain = clone;
            }
        }
    }
}

Team::Team(Team &&other) noexcept
    : fighters(std::move(other.fighters)), captain(other.captain)
{
    other.captain = nullptr;
}

Team &Team::operator=(const Team &other)
{
    if (this != &other)
    {
        for (Character *fighter : fighters)
        {
            delete fighter;
        }
        fighters.clear();

        captain = nullptr;

        for (Character *fighter : other.fighters)
        {
            if (fighter != nullptr)
            {
                add(fighter);
            }
        }

        if (other.captain != nullptr)
        {
            captain = other.captain;
        }
    }
    return *this;
}

Team &Team::operator=(Team &&other) noexcept
{
    if (this != &other)
    {
        for (Character *fighter : fighters)
        {
            delete fighter;
        }
        fighters.clear();

        fighters = std::move(other.fighters);
        captain = other.captain;

        other.captain = nullptr;
    }
    return *this;
}

Team::~Team()
{
    for (Character *fighter : fighters)
    {
        delete fighter;
    }
    fighters.clear();
}

void Team::add(Character *fighter)
{
    if (fighter != nullptr && fighters.size() < 10)
    {
        if (fighter->isTeamMate)
        {
            throw std::runtime_error("already a team mate");
        }
        // Determine the appropriate position to insert the fighter based on their type
        auto insertPosition = fighters.end(); // Default position is at the end

        if (dynamic_cast<Cowboy *>(fighter) != nullptr)
        {
            // Find the first ninja in the team and insert before it
            for (auto it = fighters.begin(); it != fighters.end(); ++it)
            {
                if (dynamic_cast<Ninja *>(*it) != nullptr)
                {
                    insertPosition = it;
                    break;
                }
            }
        }

        // Insert the fighter at the determined position
        fighters.insert(insertPosition, fighter);
        fighter->isTeamMate = true;
    }
    else
    {
        throw std::runtime_error("Exceeded the maximum limit of 10 fighters");
    }
}

void Team::attack(Team *enemyTeam)
{
    if (enemyTeam == nullptr || this->stillAlive() == 0 || enemyTeam->stillAlive() == 0)
    {
        if (enemyTeam == nullptr)
            throw std::invalid_argument("nullptr sent to function!");
        else if (enemyTeam->stillAlive() == 0)
        {
            throw std::runtime_error("enemy team is dead!");
        }
        else
        {
            throw std::runtime_error("team is dead!");
        }
    }

    // Check if the enemy team leader is alive, if not, select a new leader
    Character *enemyLeader = enemyTeam->captain;
    if (enemyLeader == nullptr || !enemyLeader->isAlive())
    {
        double minDistance = std::numeric_limits<double>::max();
        for (Character *enemyFighter : enemyTeam->fighters)
        {
            if (enemyFighter != nullptr && enemyFighter->isAlive())
            {
                double distance = enemyLeader->distance(enemyFighter);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    enemyTeam->captain = enemyFighter;
                }
            }
        }
    }

    // Check if the current team leader is alive, if not, select a new leader
    if (this->captain == nullptr || !this->captain->isAlive())
    {
        double minDistance = std::numeric_limits<double>::max();
        for (Character *fighter : this->fighters)
        {
            if (fighter != nullptr && fighter->isAlive())
            {
                double distance = this->captain->distance(fighter);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    this->captain = fighter;
                }
            }
        }
    }

    Character *enemy = nullptr;
    double minDistance = std::numeric_limits<double>::max();
    for (Character *enemyFighter : enemyTeam->fighters)
    {
        if (enemyFighter != nullptr && enemyFighter->isAlive())
        {
            double distance = (this->captain)->distance(enemyFighter);
            if (distance < minDistance)
            {
                minDistance = distance;
                enemy = enemyFighter; // Corrected variable assignment
            }
        }
    }

    if (enemy == nullptr || !enemy->isAlive())
    {
        return;
    }

    for (Character *fighter : fighters)
    {
        if (fighter != nullptr && fighter->isAlive())
        {
            if (Cowboy *cowboy = dynamic_cast<Cowboy *>(fighter))
            {
                if (cowboy->hasboolets())
                {
                    cowboy->shoot(enemy);
                }
                else
                {
                    cowboy->reload();
                }
            }
            else if (Ninja *ninja = dynamic_cast<Ninja *>(fighter))
            {
                if (ninja->distance(enemy) < 1.0)
                {
                    ninja->slash(enemy);
                }
                else
                {
                    ninja->move(enemy);
                }
            }

            if (!enemy->isAlive())
            {
                minDistance = std::numeric_limits<double>::max();
                for (Character *enemyFighter : enemyTeam->fighters)
                {
                    if (enemyFighter != nullptr && enemyFighter->isAlive())
                    {
                        double distance = (this->captain)->distance(enemyFighter);
                        if (distance < minDistance)
                        {
                            minDistance = distance;
                            enemy = enemyFighter; // Corrected variable assignment
                        }
                    }
                }

                if (enemy == nullptr || !enemy->isAlive())
                {
                    return;
                }
            }
        }
    }

    enemyLeader = enemyTeam->captain;
    if (enemyLeader == nullptr || !enemyLeader->isAlive())
    {
        double minDistance = std::numeric_limits<double>::max();
        for (Character *enemyFighter : enemyTeam->fighters)
        {
            if (enemyFighter != nullptr && enemyFighter->isAlive())
            {
                double distance = enemyLeader->distance(enemyFighter);
                if (distance < minDistance)
                {
                    minDistance = distance;
                    enemyTeam->captain = enemyFighter;
                }
            }
        }
    }
}

int Team::stillAlive() const
{
    int count = 0;
    for (Character *fighter : fighters)
    {
        if (fighter != nullptr && fighter->isAlive())
        {
            count++;
        }
    }
    return count;
}

void Team::print() const
{
    std::cout << "Team:" << std::endl;
    if (captain != nullptr)
    {
        std::cout << "- captain: " << captain->print() << std::endl;
    }
    for (Character *fighter : fighters)
    {
        if (fighter != nullptr && fighter != captain)
        {
            std::cout << "- Fighter: " << fighter->print() << std::endl;
        }
    }
}
