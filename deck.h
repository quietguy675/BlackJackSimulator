#ifndef DECK_H
#define DECK_H
#include <vector> // for vector
#include "card.h"

const int CARDS_PER_DECK = 52;
const int CARDS_PER_SUIT = 13;
 
class Deck
{
private:
    int m_num_decks = 1;
    int m_card_index = 0;
    int m_cards_drawn = 0;
    int m_deck_end_counter = 0;
    std::vector<Card> m_deck;

    // Generate a random number between min and max (inclusive)
    // Assume srand() has already been called in main()
    int getRandomNumber(int min, int max);

    void swapCard(Card &a, Card &b);
    

public:
    Deck(int num_decks = 1);

    void printDeck() const;

    void shuffleDeck();

    const Card& dealCard();

    void playerCut(int cut);

    void dealerCut();

    int getNumCards();

    int getNumCardsLeft();

    bool moreDrawableCards();
};

#endif
