#pragma once
#include <iostream>

using namespace std;

enum CardNumber
{
    Ace = 1,
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack = 11,
    Queen,
    King
};

enum CardType
{
    Hearts = 1,
    Diamonds,
    Clubs,
    Spades
};

class Card
{
    CardType m_type;
    CardNumber m_number;

public:
    Card(CardType type, CardNumber number);
    CardType getType() { return m_type; }
    CardNumber getNumber() { return m_number; }
};
