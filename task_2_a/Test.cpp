#include "doctest.h"          // A testing framework
#include "sources/player.hpp" // Player class header file
#include "sources/game.hpp"   // Game class header file
#include <stdexcept> // Exception classes

TEST_CASE("check initilization")
{
    // Check if creating a new player does not throw an exception
    CHECK_NOTHROW(Player("Alice"));
    CHECK_NOTHROW(Player("Bob")); // TODO to change to not throws

    // Create two players and check if creating a new game with them throws an exception
    Player p1("Alice");
    Player p2("Bob");
    CHECK_THROWS(Game(p1, p2));
}

TEST_CASE("empty deck scenario")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); // Create a new game with two players

    // Play all the turns and check if it throws an exception
    game.playAll();
    CHECK_THROWS(game.playTurn());
}

TEST_CASE("stack size test")
{
    Player p1("Alice");
    Player p2("Bob");
    Game game(p1, p2); // Create a new game with two players

    // Check if the initial stack size of both players is correct
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);

    // Play all the turns and check if it throws an exception
    CHECK_THROWS(game.playAll());

    // Check if the final stack size of both players is correct
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}

TEST_CASE("card taken test")
{
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2); // Create a new game with two players

    // Check if the initial number of cards taken by both players is zero
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);

    // Play all the turns
    game.playAll();

    // Check if the total number of cards taken by both players is equal to 52
    CHECK((p2.cardesTaken() + p2.cardesTaken()) == 52);
}

TEST_CASE("turn test")
{
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2); // Create a new game with two players

    // Play one turn and check if the stack size is the same for both players
    game.playTurn();
    CHECK(p1.stacksize() == p2.stacksize());

    // Check if one of the players has taken cards and the other has not, or both have taken all the cards
    bool b = ((p1.cardesTaken() > 0) && (p2.cardesTaken() == 0) && (p1.stacksize() == 26 - (int)(p1.cardesTaken() / 2))) ||
             ((p2.cardesTaken() > 0) && (p1.cardesTaken() == 0) && (p2.stacksize() == 26 - (int)(p2.cardesTaken() / 2))) ||
             ((p1.cardesTaken() == 26) && (p2.cardesTaken() == 26));
    CHECK(b);
}

TEST_CASE("early print test")
{
    Player p1("Alice");
    Player p2("Bob");

    // Create a Game object with the two players
    Game game(p1, p2);

    // Check that attempting to print the winner or last turn of the game throws an exception, since the game has not finished yet
    CHECK_THROWS(game.printWiner());
    CHECK_THROWS(game.printLastTurn());
}

TEST_CASE("check prints")
{
    Player p1("Alice");
    Player p2("Bob");

    // Create a Game object with the two players
    Game game(p1, p2);

    // Play the game until it is finished
    game.playAll();

    // Check that all of the print functions can be called without throwing an exception, since the game has finished
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
    CHECK_NOTHROW(game.printWiner());
}