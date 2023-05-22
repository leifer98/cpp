#include <limits>
#include "SmartTeam.hpp"


SmartTeam::SmartTeam(Character *leader) : Team(leader)
{
    // Implementation placeholder
}

int SmartTeam::calculateAttackerDamage(Character* enemyFighter)
{
    int ninjaDamage = 0;
    int cowboyDamage = 0;

    for (Character* fighter : this->fighters)
    {
        if (fighter != nullptr && fighter->isAlive())
        {
            if (Ninja* ninja = dynamic_cast<Ninja*>(fighter))
            {
                if (ninja->distance(enemyFighter) < 1.0)
                {
                    ninjaDamage += 40; // Increment Ninja damage by 40
                }
            }
            else if (Cowboy* cowboy = dynamic_cast<Cowboy*>(fighter))
            {
                if (cowboy->hasboolets())
                {
                    cowboyDamage += 10; // Increment Cowboy damage by 10
                }
            }
        }
    }

    return ninjaDamage + cowboyDamage + 1;
}


void SmartTeam::attack(Team *enemyTeam)
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
    int minEnemyAttacks = std::numeric_limits<int>::max(); // Track the minimum enemy attacks needed to kill an enemy
    bool isTie = false;                                    // Flag to track if there is a tie on the minimum enemy attacks
    for (Character *enemyFighter : enemyTeam->fighters)
    {
        if (enemyFighter != nullptr && enemyFighter->isAlive())
        {
            double distance = (this->captain)->distance(enemyFighter);
            int enemyAttacks = enemyFighter->getHitPoints() / this->calculateAttackerDamage(enemyFighter);
            if (enemyAttacks < minEnemyAttacks)
            {
                minDistance = distance;
                minEnemyAttacks = enemyAttacks;
                enemy = enemyFighter;
                isTie = false; // Reset the tie flag
            }
            else if (enemyAttacks == minEnemyAttacks)
            {
                if (!isTie || distance < minDistance)
                {
                    minDistance = distance;
                    enemy = enemyFighter;
                    isTie = true; // Set the tie flag
                }
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