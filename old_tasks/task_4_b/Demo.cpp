/**
 * Demo file for the exercise on binary tree
 *
 * @author Evgeny Hershkovitch Neiterman
 * @since 2023-03
 */
#include "sources/Character.hpp"
#include "sources/OldNinja.hpp"
#include "sources/YoungNinja.hpp"
#include "sources/TrainedNinja.hpp"
#include "sources/Cowboy.hpp"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"
#include <random>
#include <chrono>
#include <iostream>
using namespace std;

#include "sources/Team.hpp"  //no need for other includes
#include "sources/Team2.hpp" //no need for other includes

using namespace ariel;

//<--------------------Helper Functions-------------------->
// https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
double random_float(double min = -100, double max = 100)
{
   std::default_random_engine generator(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
   std::uniform_real_distribution<double> distribution(min, max);

   return distribution(generator);
}

auto create_yninja = [](double x = random_float(), double y = random_float())
{
   return new YoungNinja{"Bob", Point{x, y}};
};

auto create_tninja = [](double x = random_float(), double y = random_float())
{
   return new TrainedNinja{"Bob", Point{x, y}};
};

auto create_oninja = [](double x = random_float(), double y = random_float())
{
   return new OldNinja{"Bob", Point{x, y}};
};

auto create_cowboy = [](double x = random_float(), double y = random_float())
{
   std::uniform_int_distribution<int> distribution(1, 10000);
   std::random_device rd;
   std::mt19937 generator(rd());
   int randomNumber = distribution(generator);
   std::string name = "Bob" + std::to_string(randomNumber);
   return new Cowboy{name, Point{x, y}};
};

auto random_char(double x = random_float(), double y = random_float()) -> Character *
{
   int flag = static_cast<int>(random_float()) % 4;

   if (flag == 0)
      return create_cowboy(x, y);

   if (flag == 1)
      return create_yninja(x, y);

   if (flag == 2)
      return create_tninja(x, y);

   return create_oninja(x, y);
}

auto simulate_battle = [](Team &team, Team &team2)
{
   int i = 0;
   while (team.stillAlive() && team2.stillAlive())
   {
      if (i % 2 == 0)
      {
         team.attack(&team2);
      }
      else
      {
         team2.attack(&team);
      }
      i++;
   }
};

auto multi_attack = [](int n, Team &attacker, Team &defender)
{
   for (int i = 0; i < n; i++)
   {
      if (defender.stillAlive())
      {
         attacker.attack(&defender);
      }
      attacker.print();
      defender.print();
   }
};

int main()
{
   Point a(32.3, 44), b(1.3, 3.5);
   assert(a.distance(b) == b.distance(a));
   Cowboy *tom = new Cowboy("Tom", a);
   OldNinja *sushi = new OldNinja("sushi", b);
   tom->shoot(sushi);
   cout << tom->print() << endl;

   sushi->move(tom);
   sushi->slash(tom);

   Team team_A(tom);
   team_A.add(new YoungNinja("Yogi", Point(64, 57)));

   // Team b(tom); should throw tom is already in team a

   Team team_B(sushi);
   team_B.add(new TrainedNinja("Hikari", Point(12, 81)));

   while (team_A.stillAlive() > 0 && team_B.stillAlive() > 0)
   {
      team_A.attack(&team_B);
      team_B.attack(&team_A);
      team_A.print();
      team_B.print();
   }

   if (team_A.stillAlive() > 0)
      cout << "winner is team_A" << endl;
   else
      cout << "winner is team_B" << endl;

   return 0; // no memory issues. Team should free the memory of its members. both a and b teams are on the stack.
}
