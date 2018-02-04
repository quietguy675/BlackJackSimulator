#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "blackjack.h" // for HandResults


class Player
{
private:
    char getUserInput(Hand &hand);
protected:
    std::vector<Hand> m_hands;
    int getPlayerCut(int num_cards);
    int m_num_hands = 1;
public:
    Player(int num_hands = 1);

    void deal(Deck &deck);

    int getTotal(int index = 0);

    HandResults play(Deck &deck);
    void doSplit(Hand &hand, Deck &deck);
    HandResults getResult(int index = 0);
    void doCut(Deck &deck);
    void printHand();
    void printHand(int index);
    void clearHands();
    int getNumHands();
};

class Dealer : public Player
{
public:
    Dealer();

    const Card& getUpCard();
    HandResults play(Deck &deck);
};

#endif
