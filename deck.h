#ifndef DECK_H
#define DECK_H
#include <array> // for array
#include "card.h"
#include "blackjack.h" // for NUM_DECKS and CARDS_PER_DECK
 
class Deck
{
private:
    int m_cardIndex=0;
    std::array<Card, NUM_DECKS*CARDS_PER_DECK> m_deck;

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
