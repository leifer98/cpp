#include "game.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Game::Game(Player &player1, Player &player2)
    : player1(&player1), player2(&player2), sub_turn_counter(0), turn_counter(0),
      draw_counter(0), p1_wins_counter(0), p2_wins_counter(0), log("")
{
    player1.set_cards_taken(0);
    player2.set_cards_taken(0);
    devide_cards(); // deal cards to players
}

void Game::devide_cards()
{
    // create deck
    std::vector<Card> deck;
    for (int i = CardType::Hearts; i <= CardType::Spades; ++i)
    {
        for (int j = CardNumber::Ace; j <= CardNumber::King; ++j)
        {
            Card card(static_cast<CardType>(i), static_cast<CardNumber>(j));
            deck.push_back(card);
        }
    }

    // deal cards to players
    for (int i = 0; i < 26; i++)
    {
        srand(time(NULL));
        std::vector<Card>::size_type rand_index = static_cast<std::vector<Card>::size_type>(rand()) % deck.size(); // choose a random index from remaining deck
        p1_hand.push_back(deck[rand_index]);                                                                       // give the card to player 1
        deck.erase(deck.begin() + static_cast<std::vector<Card>::difference_type>(rand_index));                    // remove the card from the deck
        rand_index = static_cast<std::vector<Card>::size_type>(rand()) % deck.size();                              // choose another random index from remaining deck
        p2_hand.push_back(deck[rand_index]);                                                                       // give the card to player 2
        deck.erase(deck.begin() + static_cast<std::vector<Card>::difference_type>(rand_index));                    // remove the card from the deck
    }

    player1->set_stack_size(p1_hand.size());
    player2->set_stack_size(p2_hand.size());
}

void Game::playTurn()
{
    if (player1->stacksize() == 0 || player2->stacksize() == 0)
    {
        throw std::runtime_error("Game finished!");
    }
    if (player1 == player2)
    {
        throw std::runtime_error("Players are the same!");
    }

    // increment turn counter
    turn_counter++;
    last_turn = "";
    int deck_counter = 0;

    while (player1->stacksize() != 0 && player2->stacksize() != 0)
    {
        sub_turn_counter++;

        // get top cards
        Card p1_top = p1_hand.back();
        Card p2_top = p2_hand.back();

        // remove top cards
        p1_hand.pop_back();
        p2_hand.pop_back();

        // update stack sizes
        player1->set_stack_size(p1_hand.size());
        player2->set_stack_size(p2_hand.size());

        deck_counter += 2;
        last_turn += player1->getName() + " played " + p1_top.toString() + " " + player2->getName() + " played " + p2_top.toString() + ". ";

        // compare card numbers
        if ((p1_top.getNumber() == 1 && p2_top.getNumber() > 2) ||
            (p1_top.getNumber() > p2_top.getNumber() && p2_top.getNumber() != 1) ||
            (p1_top.getNumber() == 2 && p2_top.getNumber() == 1))
        {
            // player 1 wins
            p1_wins_counter += 1;
            player1->set_cards_taken(player1->cardesTaken() + deck_counter);
            last_turn += player1->getName() + " wins.";
            break;
        }
        else if ((p2_top.getNumber() == 1 && p1_top.getNumber() > 2) ||
                 (p1_top.getNumber() < p2_top.getNumber() && p1_top.getNumber() != 1) ||
                 (p2_top.getNumber() == 2 && p1_top.getNumber() == 1))
        {
            // player 2 wins
            p2_wins_counter += 1;
            player2->set_cards_taken(player2->cardesTaken() + deck_counter);
            last_turn += player2->getName() + " wins.";
            break;
        }
        else
        {
            // draw
            draw_counter++;
            last_turn += "Draw. ";

            if (player1->stacksize() == 0 || player2->stacksize() == 0)
            {
                player1->set_cards_taken(player1->cardesTaken() + (deck_counter / 2));
                player2->set_cards_taken(player2->cardesTaken() + (deck_counter / 2));

                break;
            }
            else if (player1->stacksize() == 1 || player2->stacksize() == 1)
            {
                // remove top cards
                p1_hand.pop_back();
                p2_hand.pop_back();

                // update stack sizes
                player1->set_stack_size(p1_hand.size());
                player2->set_stack_size(p2_hand.size());

                deck_counter += 2;

                player1->set_cards_taken(player1->cardesTaken() + (deck_counter / 2));
                player2->set_cards_taken(player2->cardesTaken() + (deck_counter / 2));

                break;
            }
            else
            {
                // remove top cards
                p1_hand.pop_back();
                p2_hand.pop_back();

                // update stack sizes
                player1->set_stack_size(p1_hand.size());
                player2->set_stack_size(p2_hand.size());

                deck_counter += 2;
            }
        }
    }
    // add last turn to log
    log += last_turn + "\n";
}

void Game::playAll()
{
    while (!p1_hand.empty() && !p2_hand.empty())
    {
        playTurn();
    }
}

void Game::printLastTurn()
{
    cout << "Last turn: " << last_turn << endl;
}

void Game::printWiner()
{
    if (!p1_hand.empty() || !p2_hand.empty())
    {
        cout << "Game is not finished yet!";
        return;
    }
    cout << "The winner is: ";
    if (player1->cardesTaken() > player2->cardesTaken())
    {
        cout << player1->getName() << endl;
    }
    else if (player1->cardesTaken() < player2->cardesTaken())
    {
        cout << player2->getName() << endl;
    }
    else
    {
        cout << "Draw" << endl;
    }
}

void Game::printLog()
{
    cout << "Game log:" << endl
         << log << endl;
}

void Game::printStats()
{
    cout << "Game stats:" << endl;
    cout << "Turns played: " << turn_counter << endl;
    cout << "Sub-turns played: " << sub_turn_counter << endl;
    cout << "Draws: " << draw_counter << endl;

    double draw_rate = ((double)draw_counter / sub_turn_counter) * 100;

    cout << "Total draw rate: " << draw_rate << "%" << endl;
    cout << "Player 1 wins: " << p1_wins_counter << endl;
    cout << "Player 2 wins: " << p2_wins_counter << endl;
    cout << "Player 1 win rate: " << ((double)p1_wins_counter / (double)turn_counter) << endl;
    cout << "Player 2 win rate: " << ((double)p2_wins_counter / (double)turn_counter) << endl;
    cout << "Cards taken by " << player1->getName() << ": " << player1->cardesTaken() << endl;
    cout << "Cards taken by " << player2->getName() << ": " << player2->cardesTaken() << endl;
}
