#include "doctest.h" // A testing framework
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

#include "sources/Team.hpp" //no need for other includes

#define LIMIT 30

TEST_CASE("check initilization")
{
    CHECK_NOTHROW(Point a(32.3, 44), b(1.3, 3.5));
    Point a(32.3, 44), b(1.3, 3.5);
    CHECK_NOTHROW(new Cowboy("Tom", a));
    Cowboy *tom = new Cowboy("Tom", a);
    CHECK_NOTHROW(new OldNinja("sushi", b));
    OldNinja *sushi = new OldNinja("sushi", b);
    CHECK_NOTHROW(new TrainedNinja("sushi", b));
    TrainedNinja *sushi2 = new TrainedNinja("sushi", b);
    CHECK_NOTHROW(new YoungNinja("sushi", b));
    YoungNinja *sushi3 = new YoungNinja("sushi", b);

    CHECK_NOTHROW(Team team_A(tom));
    Team team_A(tom);

    CHECK_NOTHROW(Team2 team_B(sushi));
    Team2 team_B(sushi);

    CHECK_NOTHROW(SmartTeam team_C(sushi2));
    SmartTeam team_C(sushi2);
}

TEST_CASE("general")
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
}

TEST_CASE("Point class")
{
    Point a(10.0, 20.0);
    Point b(15.0, 30.0);

    // Check distance calculation
    CHECK(std::abs(a.distance(b) - 14.142) < 0.001);
    CHECK(std::abs(b.distance(a) - 14.142) < 0.001);

    // Check moveTowards method
    Point c = a.moveTowards(b, 5.0);
    CHECK(std::abs(c.x - 12.071) < 0.001);
    CHECK(std::abs(c.y - 24.142) < 0.001);

    // Check print method
    std::ostringstream oss;
    a.print();
    CHECK(oss.str() == "Point(10.000, 20.000)");
}

TEST_CASE("Character class")
{
    Point a(10.0, 20.0);
    Point b(15.0, 30.0);

    Cowboy tom("Tom", a);
    OldNinja sushi("Sushi", b);
    TrainedNinja hikari("Hikari", b);
    YoungNinja yogi("Yogi", b);

    // Check hit and isAlive methods
    tom.hit(20);
    CHECK(tom.getHitPoints() == 90);
    CHECK(tom.isAlive() == true);

    sushi.hit(200);
    CHECK(sushi.getHitPoints() == 0);
    CHECK(sushi.isAlive() == false);

    // Check attack method
    tom.attack(sushi);
    CHECK(sushi.getHitPoints() == 0);

    // Check print method
    std::ostringstream oss;
    oss << "C : Tom  90 (10.000, 20.000)\n";
    CHECK(tom.print() == oss.str());

    oss.str("");
    oss << "N : (Sushi) (15.000, 30.000)\n";
    CHECK(sushi.print() == oss.str());
}

TEST_CASE("Cowboy class")
{
    Point a(10.0, 20.0);
    Point b(15.0, 30.0);

    Cowboy tom("Tom", a);
    OldNinja sushi("Sushi", b);

    // Check shoot method
    tom.shoot(&sushi);
    CHECK(sushi.getHitPoints() == 100);

    // Check hasbullets method
    CHECK(tom.hasboolets() == true);

    // Check reload method
    tom.reload();
    CHECK(tom.hasboolets() == false);

    // Check shooting without bullets
    tom.shoot(&sushi);
    CHECK(sushi.getHitPoints() == 100);
}

TEST_CASE("Ninja class")
{
    Point a(10.0, 20.0);
    Point b(15.0, 30.0);

    OldNinja sushi("Sushi", a);
    TrainedNinja hikari("Hikari", b);

    // Check slash method
    sushi.slash(&hikari);
    CHECK(hikari.getHitPoints() == 110);

    // Check move method
    sushi.move(&hikari);
    CHECK(std::abs(sushi.getLocation().x - 15.0) < 0.001);
    CHECK(std::abs(sushi.getLocation().y - 30.0) < 0.001);
}

TEST_CASE("YoungNinja class")
{
    Point a(10.0, 20.0);
    YoungNinja yogi("Yogi", a);

    // Check initial hit points
    CHECK(yogi.getHitPoints() == 100);

    // Check speed
    CHECK(yogi.speed == 14);
}

TEST_CASE("TrainedNinja class")
{
    Point a(10.0, 20.0);
    TrainedNinja hikari("Hikari", a);

    // Check initial hit points
    CHECK(hikari.getHitPoints() == 120);

    // Check speed
    CHECK(hikari.speed == 12);
}

TEST_CASE("OldNinja class")
{
    Point a(10.0, 20.0);
    OldNinja sushi("Sushi", a);

    // Check initial hit points
    CHECK(sushi.getHitPoints() == 150);

    // Check speed
    CHECK(sushi.speed == 8);
}

TEST_CASE("Team class")
{
    Point a(10.0, 20.0);
    Point b(15.0, 30.0);

    Cowboy tom("Tom", a);
    OldNinja sushi("Sushi", b);
    TrainedNinja hikari("Hikari", b);
    YoungNinja yogi("Yogi", b);

    Team team_A(&tom);
    team_A.add(&yogi);

    Team team_B(&sushi);
    team_B.add(&hikari);

    // Check attack method
    team_A.attack(&team_B);
    CHECK(sushi.getHitPoints() == 80);
    CHECK(hikari.getHitPoints() == 90);

    team_B.attack(&team_A);
    CHECK(tom.getHitPoints() == 80);
    CHECK(yogi.getHitPoints() == 90);

    // Check stillAlive method
    CHECK(team_A.stillAlive() == 2);
    CHECK(team_B.stillAlive() == 2);

    // Check print method
    std::ostringstream oss;
    team_A.print();
    CHECK(oss.str() == "Team A:\nC : Tom  80 (10.000, 20.000)\nN : Yogi  90 (15.000, 30.000)\n");

    oss.str("");
    team_B.print();
    CHECK(oss.str() == "Team B:\nN : (Sushi) (15.000, 30.000)\nN : Hikari  90 (15.000, 30.000)\n");
}

TEST_CASE("Team class add() and stillAlive() methods")
{
    Cowboy *patrick = new Cowboy("Patrick", Point(32.3, 44));
    OldNinja *gohan = new OldNinja("Gohan", Point(1.3, 3.5));
    patrick->shoot(gohan);
    cout << patrick->print() << endl;

    gohan->move(patrick);
    gohan->slash(patrick);

    Team team_A(patrick);
    team_A.add(new YoungNinja("SpongeBob", Point(64, 57)));

    // Team b(tom); should throw tom is already in team a

    Team team_B(gohan);
    team_B.add(new TrainedNinja("Piccolo", Point(12, 81)));

    // Every addition should increase the value returned by stillAlive()
    for (int i = 0; i < 9; i++)
    {
        Ninja *cur1 = new Ninja("Ninja " + std::to_string(i + 1), Point(0, 0), 100, 10);
        Cowboy *cur2 = new Cowboy("Cowboy " + std::to_string(i + 1), Point(0, 0));
        team_A.add(cur1);
        team_B.add(cur2);
        CHECK_EQ(team_A.stillAlive(), i + 2);
        CHECK_EQ(team_B.stillAlive(), i + 2);
    }

    // A team can have at most 10 teammates
    Cowboy *over = new Cowboy("Over", Point(0, 0));

    CHECK_THROWS_AS(team_A.add(over), std::runtime_error);
    CHECK_THROWS_AS(team_B.add(over), std::runtime_error);
    CHECK_NOTHROW(delete over);

    // Clean up dynamically allocated objects
    CHECK_NOTHROW(delete patrick);
    CHECK_NOTHROW(delete gohan);
}

TEST_CASE("Appointings to different teams")
{
    Cowboy *spongebob = new Cowboy("SpongeBob", Point(32.3, 44));
    OldNinja *goku = new OldNinja("Goku", Point(10, 20));
    OldNinja *vegeta = new OldNinja("Vegeta", Point(5, 10));

    Team teamA{spongebob};
    CHECK_THROWS_AS(Team{spongebob}, std::runtime_error);
    CHECK_THROWS_AS(Team2{spongebob}, std::runtime_error);

    Team teamB{goku};
    CHECK_THROWS_AS(Team{goku}, std::runtime_error);
    CHECK_THROWS_AS(Team2{goku}, std::runtime_error);

    // Adding the same character to different teams
    teamA.add(new YoungNinja("Krillin", Point(64, 57)));

    teamA.add(goku);

    CHECK_THROWS_AS(teamB.add(spongebob), std::runtime_error);
    CHECK_THROWS_AS(teamB.add(goku), std::runtime_error);

    // Clean up dynamically allocated objects
    delete spongebob;
    delete goku;
    delete vegeta;
}

TEST_CASE("Ninjas can only slash when distance is less than 1")
{
    OldNinja squidward{"Squidward", Point{0, 0}};
    TrainedNinja patrick{"Patrick", Point{0, 0}};
    YoungNinja sandy{"Sandy", Point{0.5, 0.5}};
    Cowboy spongebob{"SpongeBob", Point{0.5, 0.5}};

    int count = 0;
    while (count < 1)
    {
        squidward.slash(&spongebob);
        sandy.slash(&spongebob);
        count++;
    }

    CHECK(spongebob.isAlive());

    squidward.slash(&spongebob);
    CHECK_FALSE(spongebob.isAlive());

    YoungNinja ninja{"Bob", Point{-0.5, 0.5}}; // Distance from Sandy is exactly one
    OldNinja ninja2{"Bob", Point{2, 2}};

    // These attacks should have no effect
    int i = 0;
    while (i < 20)
    {
        patrick.slash(&ninja2);
        squidward.slash(&ninja2);
        sandy.slash(&ninja2);
        i++;
    }

    count = 0;
    while (count < 1)
    {
        squidward.slash(&ninja);
        sandy.slash(&ninja);
        count++;
    }
    CHECK(ninja.isAlive());
    CHECK(ninja2.isAlive());
}
