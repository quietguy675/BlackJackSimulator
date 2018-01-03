#ifndef DECK_H
#define DECK_H
#include <array> // for array
#include "card.h"
 
class Deck
{
private:
    int m_cardIndex=0;
    std::array<Card, 52> m_deck;

    // Generate a random number between min and max (inclusive)
    // Assume srand() has already been called in main()
    int getRandomNumber(int min, int max);

    void swapCard(Card &a, Card &b);
    

public:
    Deck();

    void printDeck() const;

    void shuffleDeck();

    const Card& dealCard();
};

#endif
