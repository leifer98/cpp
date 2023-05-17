#include "doctest.h" // A testing framework
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
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
    CHECK(tom.hasbullets() == true);

    // Check reload method
    tom.reload();
    CHECK(tom.hasbullets() == false);

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
