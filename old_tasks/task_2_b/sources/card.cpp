#include "card.hpp"

Card::Card(CardType type, CardNumber number)
    : m_type(type), m_number(number)
{
}

string Card::toString()
{
    string numberString;
    switch (m_number)
    {
    case Ace:
        numberString = "Ace";
        break;
    case Two:
        numberString = "2";
        break;
    case Three:
        numberString = "3";
        break;
    case Four:
        numberString = "4";
        break;
    case Five:
        numberString = "5";
        break;
    case Six:
        numberString = "6";
        break;
    case Seven:
        numberString = "7";
        break;
    case Eight:
        numberString = "8";
        break;
    case Nine:
        numberString = "9";
        break;
    case Ten:
        numberString = "10";
        break;
    case Jack:
        numberString = "Jack";
        break;
    case Queen:
        numberString = "Queen";
        break;
    case King:
        numberString = "King";
        break;
    }

    string typeString;
    switch (m_type)
    {
    case Hearts:
        typeString = "Hearts";
        break;
    case Diamonds:
        typeString = "Diamonds";
        break;
    case Clubs:
        typeString = "Clubs";
        break;
    case Spades:
        typeString = "Spades";
        break;
    }

    return numberString + " of " + typeString;
}
