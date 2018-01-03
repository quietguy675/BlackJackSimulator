#include <iostream> // for cout
#include <cassert> // for assert
#include "deck.h" // for deck class
#include "card.h" // for card class


int Deck::getRandomNumber(int min, int max)
{
    // static used for efficiency, so we only calculate this value once
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // evenly distribute the random number across our range
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

 
void Deck::swapCard(Card &a, Card &b)
{
    if (&a == &b)
    {
        std::cout << "lolz, same card dummy\n";
        return;
    }
    Card temp = a;
    a = b;
    b = temp;
}

Deck::Deck() : m_cardIndex(0)
{
    for (int suit = 0; suit < Card::MAX_SUITS; ++suit)
    {
        for (int rank = 0; rank < Card::MAX_RANKS; ++rank)
        {
            m_deck[rank + suit*13] = Card(static_cast<Card::CardRank>(rank),
               static_cast<Card::CardSuit>(suit));
        }
    }
}

void Deck::printDeck() const
{
    for (int i = 0; i < m_deck.size(); ++i)
    {
        m_deck[i].printCard();
        std::cout << " ";
        if ((i+1)%13 == 0)
            std::cout << "\n";
    }
    std::cout << "\n";
}

void Deck::shuffleDeck()
{
    for (int i = 0; i < m_deck.size(); ++i)
    {
        swapCard(m_deck[i],
            m_deck[getRandomNumber(0, m_deck.size() - 1)]);
    }
    m_cardIndex = 0;
}

const Card& Deck::dealCard()
{
    assert(m_cardIndex < 52);
    return m_deck[m_cardIndex++];
}
